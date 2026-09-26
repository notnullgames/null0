// android glue for the host: where the cart comes from, logging, physical
// joysticks, and the on-screen SNES-style controller.
//
// The controller is drawn with raylib straight over the frame pntr_app just
// rendered (main.c routes EndDrawing through null0_android_draw_controller),
// in the bars around the letterboxed game, and it feeds the cart through
// pntr_app_process_event - the same path a real gamepad takes - so both the
// callbacks (buttonDown/buttonUp) and polling (gamepad_button_down) see it.

#ifdef __ANDROID__

#include "host.h"
#include <android/log.h>
#include <android_native_app_glue.h>
#include <jni.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

struct android_app *GetAndroidApp(void);
void pntr_app_raylib_destination_rect(pntr_app *app, Rectangle *outRect);

// the player the on-screen controller (and stick-as-dpad) presses buttons for
#define NULL0_ANDROID_PLAYER 0

// how far the analog stick has to go to press a dpad direction, and how far
// back it has to come to release it (so it doesn't chatter at the edge)
#define NULL0_STICK_PRESS 0.5f
#define NULL0_STICK_RELEASE 0.35f

static pntr_app *android_app_ptr = NULL;
static bool controller_enabled = true;

// ---------------------------------------------------------------------------
// JNI

static JNIEnv *null0_android_env() {
  struct android_app *app = GetAndroidApp();
  JNIEnv *env = NULL;
  (*app->activity->vm)->AttachCurrentThread(app->activity->vm, &env, NULL);
  return env;
}

// call a no-arg method on the activity (CartActivity) that returns a string
static char *null0_android_activity_string(const char *method) {
  JNIEnv *env = null0_android_env();
  jobject activity = GetAndroidApp()->activity->clazz;
  jclass cls = (*env)->GetObjectClass(env, activity);
  jmethodID m = (*env)->GetMethodID(env, cls, method, "()Ljava/lang/String;");
  if (m == NULL) {
    (*env)->ExceptionClear(env);
    return NULL;
  }
  jstring js = (jstring)(*env)->CallObjectMethod(env, activity, m);
  if (js == NULL) {
    return NULL;
  }
  const char *s = (*env)->GetStringUTFChars(env, js, NULL);
  char *out = strdup(s);
  (*env)->ReleaseStringUTFChars(env, js, s);
  return out;
}

// call a no-arg method on the activity that returns a boolean
static bool null0_android_activity_bool(const char *method, bool fallback) {
  JNIEnv *env = null0_android_env();
  jobject activity = GetAndroidApp()->activity->clazz;
  jclass cls = (*env)->GetObjectClass(env, activity);
  jmethodID m = (*env)->GetMethodID(env, cls, method, "()Z");
  if (m == NULL) {
    (*env)->ExceptionClear(env);
    return fallback;
  }
  return (*env)->CallBooleanMethod(env, activity, m);
}

// stdout/stderr go nowhere on android, so pipe them into logcat - that's
// where printf from the host (and the cart's WASI fd_write) ends up
static int log_pipe[2];

static void *null0_android_log_thread(void *arg) {
  char buf[1024];
  ssize_t n;
  while ((n = read(log_pipe[0], buf, sizeof(buf) - 1)) > 0) {
    if (buf[n - 1] == '\n') {
      n--;
    }
    buf[n] = '\0';
    __android_log_write(ANDROID_LOG_INFO, "null0", buf);
  }
  return NULL;
}

static void null0_android_redirect_logs() {
  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  if (pipe(log_pipe) != 0) {
    return;
  }
  dup2(log_pipe[1], STDOUT_FILENO);
  dup2(log_pipe[1], STDERR_FILENO);
  pthread_t t;
  if (pthread_create(&t, NULL, null0_android_log_thread, NULL) == 0) {
    pthread_detach(t);
  }
}

// the cart to run, handed over by CartActivity (the launcher copies it into
// app storage, so it's always a real file)
char *null0_android_cart_path() {
  null0_android_redirect_logs();
  controller_enabled = null0_android_activity_bool("getShowController", true);
  return null0_android_activity_string("getCartPath");
}

// physfs wants a JNIEnv + Context on android (in place of argv[0]) to find
// the app's own storage
const char *null0_android_physfs_init() {
  static PHYSFS_AndroidInit init;
  init.jnienv = null0_android_env();
  init.context = GetAndroidApp()->activity->clazz;
  return (const char *)&init;
}

// ---------------------------------------------------------------------------
// the on-screen controller

typedef enum {
  PAD_UP,
  PAD_DOWN,
  PAD_LEFT,
  PAD_RIGHT,
  PAD_A,
  PAD_B,
  PAD_X,
  PAD_Y,
  PAD_L,
  PAD_R,
  PAD_SELECT,
  PAD_START,
  PAD_COUNT
} PadControl;

static const pntr_app_gamepad_button pad_buttons[PAD_COUNT] = {
  PNTR_APP_GAMEPAD_BUTTON_UP,
  PNTR_APP_GAMEPAD_BUTTON_DOWN,
  PNTR_APP_GAMEPAD_BUTTON_LEFT,
  PNTR_APP_GAMEPAD_BUTTON_RIGHT,
  PNTR_APP_GAMEPAD_BUTTON_A,
  PNTR_APP_GAMEPAD_BUTTON_B,
  PNTR_APP_GAMEPAD_BUTTON_X,
  PNTR_APP_GAMEPAD_BUTTON_Y,
  PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER,
  PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER,
  PNTR_APP_GAMEPAD_BUTTON_SELECT,
  PNTR_APP_GAMEPAD_BUTTON_START};

// where everything is, in screen pixels. recomputed each frame (it's cheap),
// so it always matches the current screen size
typedef struct {
  float unit;
  Vector2 dpad;
  float dpadRadius;
  Vector2 face;
  float faceSpread;
  float faceRadius;
  Rectangle shoulderL;
  Rectangle shoulderR;
  Rectangle select;
  Rectangle start;
} PadLayout;

static bool pad_down[PAD_COUNT];

static void null0_android_touch_replay(pntr_app *app);

// stick-as-dpad state, for the physical joystick
static bool stick_down[4];

static PadLayout null0_pad_layout() {
  PadLayout l = {0};
  float w = (float)GetScreenWidth();
  float h = (float)GetScreenHeight();
  float u = fminf(w, h) / 9.0f;
  l.unit = u;
  l.dpadRadius = 1.5f * u;
  l.faceSpread = 1.05f * u;
  l.faceRadius = 0.55f * u;
  Vector2 shoulder = {2.4f * u, 0.75f * u};
  Vector2 pill = {1.7f * u, 0.55f * u};

  Rectangle game = {0};
  if (android_app_ptr != NULL && android_app_ptr->screen != NULL) {
    pntr_app_raylib_destination_rect(android_app_ptr, &game);
  }

  if (w > h) {
    // landscape: dpad left of the game, buttons right of it, like a handheld.
    // centered in the side bars if they're wide enough, else hugging the edge
    // (drawn over the game, translucent)
    float side = game.x;
    float left = fmaxf(side / 2, l.dpadRadius + 0.5f * u);
    float right = w - fmaxf(side / 2, l.faceSpread + l.faceRadius + 0.5f * u);
    float cy = h * 0.58f;
    l.dpad = (Vector2){left, cy};
    l.face = (Vector2){right, cy};
    l.shoulderL = (Rectangle){left - shoulder.x / 2, 0.5f * u, shoulder.x, shoulder.y};
    l.shoulderR = (Rectangle){right - shoulder.x / 2, 0.5f * u, shoulder.x, shoulder.y};
    l.select = (Rectangle){left - pill.x / 2, h - 0.5f * u - pill.y, pill.x, pill.y};
    l.start = (Rectangle){right - pill.x / 2, h - 0.5f * u - pill.y, pill.x, pill.y};
  } else {
    // portrait: the controller sits in the bar under the game
    float top = game.y + game.height;
    float bottom = h;
    float cy = top + (bottom - top) * 0.45f;
    // keep it on screen if the bar is short (tall game, square-ish screen)
    cy = fminf(cy, h - l.dpadRadius - 1.6f * u);
    float left = l.dpadRadius + 0.6f * u;
    float right = w - (l.faceSpread + l.faceRadius + 0.6f * u);
    l.dpad = (Vector2){left, cy};
    l.face = (Vector2){right, cy};
    float sy = cy - l.dpadRadius - 0.4f * u - shoulder.y;
    l.shoulderL = (Rectangle){0.4f * u, sy, shoulder.x, shoulder.y};
    l.shoulderR = (Rectangle){w - 0.4f * u - shoulder.x, sy, shoulder.x, shoulder.y};
    float py = cy + l.dpadRadius + 0.5f * u;
    l.select = (Rectangle){w / 2 - pill.x - 0.25f * u, py, pill.x, pill.y};
    l.start = (Rectangle){w / 2 + 0.25f * u, py, pill.x, pill.y};
  }
  return l;
}

// where each face button is, SNES layout: X top, A right, B bottom, Y left
static Vector2 null0_pad_face_pos(PadLayout *l, PadControl c) {
  switch (c) {
  case PAD_X:
    return (Vector2){l->face.x, l->face.y - l->faceSpread};
  case PAD_A:
    return (Vector2){l->face.x + l->faceSpread, l->face.y};
  case PAD_B:
    return (Vector2){l->face.x, l->face.y + l->faceSpread};
  default:
    return (Vector2){l->face.x - l->faceSpread, l->face.y};
  }
}

static Rectangle null0_grow(Rectangle r, float by) {
  return (Rectangle){r.x - by, r.y - by, r.width + by * 2, r.height + by * 2};
}

// mark every control a touch at p is pressing. returns true if it hit any
static bool null0_pad_hit(PadLayout *l, Vector2 p, bool *out) {
  bool hit = false;

  // dpad: 8-way, by angle from the center (so diagonals work), with a
  // small dead zone in the middle
  float dx = p.x - l->dpad.x;
  float dy = p.y - l->dpad.y;
  float dist = sqrtf(dx * dx + dy * dy);
  if (dist < l->dpadRadius * 1.35f) {
    hit = true;
    if (dist > l->dpadRadius * 0.2f) {
      float cx = dx / dist;
      float cy = dy / dist;
      // cos(67.5deg): each direction covers 135deg, so neighbours overlap
      // into the diagonals
      const float edge = 0.38f;
      if (cx > edge)
        out[PAD_RIGHT] = true;
      if (cx < -edge)
        out[PAD_LEFT] = true;
      if (cy > edge)
        out[PAD_DOWN] = true;
      if (cy < -edge)
        out[PAD_UP] = true;
    }
  }

  // face buttons: the hit area is bigger than the drawn button, so a touch
  // between two (B+Y, B+A) presses both, like rolling a thumb on a real pad
  PadControl face[4] = {PAD_A, PAD_B, PAD_X, PAD_Y};
  for (int i = 0; i < 4; i++) {
    Vector2 b = null0_pad_face_pos(l, face[i]);
    float fx = p.x - b.x;
    float fy = p.y - b.y;
    if (fx * fx + fy * fy < (l->unit * 0.85f) * (l->unit * 0.85f)) {
      out[face[i]] = true;
      hit = true;
    }
  }
  // anywhere else in the face-button cluster counts as the controller too,
  // so a near miss doesn't click the game
  float fx = p.x - l->face.x;
  float fy = p.y - l->face.y;
  float faceOuter = l->faceSpread + l->faceRadius * 1.6f;
  if (fx * fx + fy * fy < faceOuter * faceOuter) {
    hit = true;
  }

  float pad = l->unit * 0.3f;
  struct {
    Rectangle r;
    PadControl c;
  } rects[4] = {{l->shoulderL, PAD_L}, {l->shoulderR, PAD_R}, {l->select, PAD_SELECT}, {l->start, PAD_START}};
  for (int i = 0; i < 4; i++) {
    if (CheckCollisionPointRec(p, null0_grow(rects[i].r, pad))) {
      out[rects[i].c] = true;
      hit = true;
    }
  }

  return hit;
}

static void null0_android_button(pntr_app *app, pntr_app_gamepad_button button, bool down) {
  pntr_app_event event = {0};
  event.app = app;
  event.type = down ? PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN : PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP;
  event.gamepad = NULL0_ANDROID_PLAYER;
  event.gamepadButton = button;
  pntr_app_process_event(app, &event);
}

// the physical joystick's left stick, as a dpad. raylib already handles the
// buttons and the hat-dpad, but null0 has no axis API, so without this an
// analog-only controller can't move anything
static void null0_android_stick(pntr_app *app) {
  if (!IsGamepadAvailable(0)) {
    return;
  }
  float x = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
  float y = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
  float value[4] = {-y, y, -x, x};
  pntr_app_gamepad_button buttons[4] = {
    PNTR_APP_GAMEPAD_BUTTON_UP,
    PNTR_APP_GAMEPAD_BUTTON_DOWN,
    PNTR_APP_GAMEPAD_BUTTON_LEFT,
    PNTR_APP_GAMEPAD_BUTTON_RIGHT};
  for (int i = 0; i < 4; i++) {
    bool down = stick_down[i] ? value[i] > NULL0_STICK_RELEASE : value[i] > NULL0_STICK_PRESS;
    if (down != stick_down[i]) {
      stick_down[i] = down;
      null0_android_button(app, buttons[i], down);
    }
  }
}

// called at the top of every frame. returns false to quit (back button)
bool null0_android_update(pntr_app *app) {
  android_app_ptr = app;

  if (IsKeyPressed(KEY_BACK)) {
    return false;
  }

  null0_android_stick(app);

  // replayed through pntr_app_process_event, which calls host_event again -
  // null0_android_filter_event lets these through
  null0_android_touch_replay(app);

  if (!controller_enabled) {
    return true;
  }

  PadLayout l = null0_pad_layout();
  bool now[PAD_COUNT] = {0};
  int touches = GetTouchPointCount();
  for (int i = 0; i < touches; i++) {
    null0_pad_hit(&l, GetTouchPosition(i), now);
  }

  for (int c = 0; c < PAD_COUNT; c++) {
    if (now[c] != pad_down[c]) {
      pad_down[c] = now[c];
      null0_android_button(app, pad_buttons[c], now[c]);
    }
  }
  return true;
}

// A touch is a mouse with no hover: it lands somewhere new and presses in
// the same instant. pntr_app only tracks the pointer through movement deltas,
// so a tap that doesn't slide never moves it at all, and microui only accepts
// a press on a control it saw hovered on an earlier frame - inside the window
// it saw the pointer over the frame before that (its hover_root). So a
// touch-down is held back: the pointer moves there now, and the press (and a
// release, for a tap quicker than that) is replayed two frames later. That's
// ~33ms, too short to feel.
static bool touch_pending_down = false;
static bool touch_pending_up = false;
// Updates to skip before replaying the press (see above)
static int touch_wait = 0;
static pntr_app_mouse_button touch_button;
// set while we feed pntr_app our own events, which come back through
// null0_android_filter_event and must go straight to the cart
static bool replaying = false;

static void null0_android_mouse(pntr_app *app, pntr_app_event_type type, pntr_app_mouse_button button) {
  pntr_app_event event = {0};
  event.app = app;
  event.type = type;
  event.mouseButton = button;
  event.mouseX = app->mouseX;
  event.mouseY = app->mouseY;
  replaying = true;
  pntr_app_process_event(app, &event);
  replaying = false;
}

// move the pointer to where the touch is, in cart-screen coordinates
static void null0_android_touch_move(pntr_app *app) {
  Rectangle r;
  pntr_app_raylib_destination_rect(app, &r);
  Vector2 p = GetMousePosition();
  pntr_app_event event = {0};
  event.app = app;
  event.type = PNTR_APP_EVENTTYPE_MOUSE_MOVE;
  event.mouseX = (p.x - r.x) * app->screen->width / r.width;
  event.mouseY = (p.y - r.y) * app->screen->height / r.height;
  event.mouseDeltaX = event.mouseX - app->mouseX;
  event.mouseDeltaY = event.mouseY - app->mouseY;
  pntr_app_process_event(app, &event);
}

// replay a held-back touch, one transition per frame
static void null0_android_touch_replay(pntr_app *app) {
  if (touch_wait > 0) {
    touch_wait--;
    return;
  }
  if (touch_pending_down) {
    touch_pending_down = false;
    null0_android_mouse(app, PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN, touch_button);
  } else if (touch_pending_up) {
    touch_pending_up = false;
    null0_android_mouse(app, PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP, touch_button);
  }
}

// called for every event before the cart sees it. a touch that starts on
// the on-screen controller belongs to the controller until it lifts (raylib
// turns the first touch into the mouse, so a thumb on the dpad would also
// click the game). returns true if the event should be dropped
bool null0_android_filter_event(pntr_app_event *event) {
  static bool captured = false;
  pntr_app *app = event->app;

  if (replaying) {
    return false;
  }

  switch (event->type) {
  case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN: {
    PadLayout l = null0_pad_layout();
    bool unused[PAD_COUNT] = {0};
    captured = controller_enabled && null0_pad_hit(&l, GetMousePosition(), unused);
    // pntr_app already marked the button down - undo that, so polling
    // (mouse_button_down, and the gui) doesn't see it either
    app->mouseButtonsDown[event->mouseButton] = false;
    if (!captured) {
      replaying = true;
      null0_android_touch_move(app);
      replaying = false;
      touch_button = event->mouseButton;
      touch_pending_down = true;
      touch_pending_up = false;
      touch_wait = 2;
    }
    return true;
  }
  case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP:
    if (captured) {
      captured = false;
      return true;
    }
    if (touch_pending_down) {
      // lifted before the press was replayed: release after it
      touch_pending_up = true;
      return true;
    }
    return false;
  case PNTR_APP_EVENTTYPE_MOUSE_MOVE:
    return captured;
  default:
    return false;
  }
}

// ---------------------------------------------------------------------------
// drawing

static Color null0_pad_shade(Color c, bool pressed) {
  if (pressed) {
    return ColorAlpha(ColorBrightness(c, 0.35f), 0.95f);
  }
  return ColorAlpha(c, 0.7f);
}

static void null0_pad_label(const char *text, Vector2 center, float size, Color color) {
  int fontSize = (int)size;
  int tw = MeasureText(text, fontSize);
  DrawText(text, (int)(center.x - tw / 2.0f), (int)(center.y - fontSize / 2.0f), fontSize, color);
}

static void null0_pad_pill(Rectangle r, const char *text, bool pressed, float u) {
  DrawRectangleRounded(r, 1.0f, 8, null0_pad_shade((Color){70, 70, 78, 255}, pressed));
  DrawRectangleRoundedLinesEx(r, 1.0f, 8, 2.0f, ColorAlpha(BLACK, 0.4f));
  null0_pad_label(text, (Vector2){r.x + r.width / 2, r.y + r.height / 2}, u * 0.36f, ColorAlpha(RAYWHITE, 0.85f));
}

void null0_android_draw_controller() {
  if (!controller_enabled) {
    return;
  }
  PadLayout l = null0_pad_layout();
  float u = l.unit;

  // shoulders
  null0_pad_pill(l.shoulderL, "L", pad_down[PAD_L], u * 1.4f);
  null0_pad_pill(l.shoulderR, "R", pad_down[PAD_R], u * 1.4f);

  // dpad: a plus, with each arm lit when pressed
  Color dpad = {50, 50, 56, 255};
  float arm = l.dpadRadius;
  float thick = u * 1.0f;
  Rectangle base = {l.dpad.x - arm, l.dpad.y - thick / 2, arm * 2, thick};
  Rectangle vert = {l.dpad.x - thick / 2, l.dpad.y - arm, thick, arm * 2};
  DrawRectangleRounded(base, 0.25f, 4, null0_pad_shade(dpad, false));
  DrawRectangleRounded(vert, 0.25f, 4, null0_pad_shade(dpad, false));
  Color lit = ColorAlpha(RAYWHITE, 0.35f);
  if (pad_down[PAD_UP])
    DrawRectangleRounded((Rectangle){vert.x, vert.y, thick, arm - thick / 2}, 0.3f, 4, lit);
  if (pad_down[PAD_DOWN])
    DrawRectangleRounded((Rectangle){vert.x, l.dpad.y + thick / 2, thick, arm - thick / 2}, 0.3f, 4, lit);
  if (pad_down[PAD_LEFT])
    DrawRectangleRounded((Rectangle){base.x, base.y, arm - thick / 2, thick}, 0.3f, 4, lit);
  if (pad_down[PAD_RIGHT])
    DrawRectangleRounded((Rectangle){l.dpad.x + thick / 2, base.y, arm - thick / 2, thick}, 0.3f, 4, lit);
  DrawCircleV(l.dpad, thick * 0.22f, ColorAlpha(BLACK, 0.3f));

  // face buttons, in the SNES colors
  struct {
    PadControl c;
    const char *label;
    Color color;
  } face[4] = {
    {PAD_X, "X", (Color){60, 80, 200, 255}},
    {PAD_A, "A", (Color){200, 40, 50, 255}},
    {PAD_B, "B", (Color){230, 180, 30, 255}},
    {PAD_Y, "Y", (Color){40, 150, 70, 255}}};
  DrawCircleV(l.face, l.faceSpread + l.faceRadius * 1.3f, ColorAlpha((Color){40, 40, 46, 255}, 0.35f));
  for (int i = 0; i < 4; i++) {
    Vector2 p = null0_pad_face_pos(&l, face[i].c);
    DrawCircleV(p, l.faceRadius, null0_pad_shade(face[i].color, pad_down[face[i].c]));
    null0_pad_label(face[i].label, p, u * 0.5f, ColorAlpha(RAYWHITE, 0.9f));
  }

  // select + start
  null0_pad_pill(l.select, "SELECT", pad_down[PAD_SELECT], u);
  null0_pad_pill(l.start, "START", pad_down[PAD_START], u);
}

#endif // __ANDROID__
