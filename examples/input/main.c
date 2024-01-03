// simple native example of drawing

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_PIXELFORMAT_RGBA
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

bool buttons[] = {
    false,
    false,  // GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
    false,  // GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
    false,  // GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
    false,  // GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
    false,  // GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    false,  // GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    false,  // GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    false,  // GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    false,  // GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
    false,  // GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
    false,  // GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
    false,  // GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
    false,  // GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
    false,  // GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    false,  // GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
    false,  // GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
    false,  // GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
};

uint32_t images[16];
uint32_t bg;

void cart_main() {
  null0_trace("Hello from input.");

  images[0] = null0_load_image("assets/bg.png");
  images[1] = null0_load_image("assets/up.png");
  images[2] = null0_load_image("assets/right.png");
  images[3] = null0_load_image("assets/down.png");
  images[4] = null0_load_image("assets/left.png");
  images[5] = null0_load_image("assets/y.png");
  images[6] = null0_load_image("assets/b.png");
  images[7] = null0_load_image("assets/a.png");
  images[8] = null0_load_image("assets/x.png");
  images[9] = null0_load_image("assets/l1.png");
  images[11] = null0_load_image("assets/r1.png");
  images[13] = null0_load_image("assets/select.png");
  images[15] = null0_load_image("assets/start.png");

  bg = null0_image_gradient(320, 240, NULL0_BLUE, NULL0_BLUE, NULL0_GREEN, NULL0_GREEN);
}

bool cart_update() {
  null0_clear(NULL0_BLACK);
  
  null0_draw_image(bg, 0, 0);
  null0_draw_image(images[0], 0, 47);

  for (int i = 1; i < 16; i++) {
    if (buttons[i]) {
      null0_draw_image(images[i], 0, 0);
    }
  }

  return true;
}

void cart_buttonDown(pntr_app_gamepad_button button) {
  buttons[button] = true;
}

void cart_buttonUp(pntr_app_gamepad_button button) {
  buttons[button] = false;
}

bool Init(pntr_app* app) {
  if (!null0_load_cart("examples/input")) {
    printf("Could not initialize\n");
    null0_unload();
    return false;
  }
  cart_main();
  return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
  null0_update(app, screen);
  cart_update();
  return true;
}

void Event(pntr_app* app, pntr_app_event* event) {
  if (event->type == PNTR_APP_EVENTTYPE_KEY_DOWN) {
    cart_buttonDown(null0_button_map_key(event->key));
  }
  if (event->type == PNTR_APP_EVENTTYPE_KEY_UP) {
    cart_buttonUp(null0_button_map_key(event->key));
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN) {
    cart_buttonDown(event->gamepadButton);
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP) {
    cart_buttonUp(event->gamepadButton);
  }
}


pntr_app Main(int argc, char* argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif
  return (pntr_app){
      .width = 320,
      .height = 240,
      .title = "null0",
      .init = Init,
      .update = Update,
      .event = Event,
      .fps = 60};
}