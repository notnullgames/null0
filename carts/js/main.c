#include "../null0.h"
#include "quickjs.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to read file contents
static char *read_file(const char *filename) {
  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
    return NULL;
  }

  struct stat st;
  if (fstat(fd, &st) < 0) {
    close(fd);
    fprintf(stderr, "Error: Cannot stat file '%s'\n", filename);
    return NULL;
  }

  size_t size = st.st_size;
  char *buffer = malloc(size + 1);
  if (!buffer) {
    close(fd);
    fprintf(stderr, "Error: Memory allocation failed\n");
    return NULL;
  }

  ssize_t bytes_read = read(fd, buffer, size);
  close(fd);

  if (bytes_read != size) {
    free(buffer);
    fprintf(stderr, "Error: Failed to read complete file\n");
    return NULL;
  }

  buffer[size] = '\0';
  return buffer;
}

JSContext *ctx;

// Execute JavaScript and handle errors
static int execute_js(const char *code, const char *filename) {
  JSValue result = JS_Eval(ctx, code, strlen(code), filename, JS_EVAL_TYPE_GLOBAL);

  if (JS_IsException(result)) {
    JSValue exception = JS_GetException(ctx);
    const char *error_str = JS_ToCString(ctx, exception);
    fprintf(stderr, "JavaScript Error: %s\n", error_str ? error_str : "Unknown error");
    JS_FreeCString(ctx, error_str);
    JS_FreeValue(ctx, exception);
    JS_FreeValue(ctx, result);
    return -1;
  }

  JS_FreeValue(ctx, result);
  return 0;
}

// TYPE HELPERS

static Color color_from_js(JSContext *ctx, JSValueConst color_obj) {
  Color color = {0, 0, 0, 255}; // Default: black with full alpha

  if (!JS_IsObject(color_obj)) {
    return color;
  }

  JSValue val;
  int32_t component;

  // Get r, g, b, a
  val = JS_GetPropertyStr(ctx, color_obj, "r");
  if (JS_ToInt32(ctx, &component, val) == 0) {
    color.r = component < 0 ? 0 : (component > 255 ? 255 : component);
  }
  JS_FreeValue(ctx, val);

  val = JS_GetPropertyStr(ctx, color_obj, "g");
  if (JS_ToInt32(ctx, &component, val) == 0) {
    color.g = component < 0 ? 0 : (component > 255 ? 255 : component);
  }
  JS_FreeValue(ctx, val);

  val = JS_GetPropertyStr(ctx, color_obj, "b");
  if (JS_ToInt32(ctx, &component, val) == 0) {
    color.b = component < 0 ? 0 : (component > 255 ? 255 : component);
  }
  JS_FreeValue(ctx, val);

  val = JS_GetPropertyStr(ctx, color_obj, "a");
  if (!JS_IsUndefined(val) && JS_ToInt32(ctx, &component, val) == 0) {
    color.a = component < 0 ? 0 : (component > 255 ? 255 : component);
  }
  JS_FreeValue(ctx, val);

  return color;
}

static JSValue js_color_from_native(JSContext *ctx, Color color) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "r", JS_NewInt32(ctx, color.r));
  JS_SetPropertyStr(ctx, obj, "g", JS_NewInt32(ctx, color.g));
  JS_SetPropertyStr(ctx, obj, "b", JS_NewInt32(ctx, color.b));
  JS_SetPropertyStr(ctx, obj, "a", JS_NewInt32(ctx, color.a));
  return obj;
}

static JSValue js_vector_from_native(JSContext *ctx, Vector vec) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "x", JS_NewInt32(ctx, vec.x));
  JS_SetPropertyStr(ctx, obj, "y", JS_NewInt32(ctx, vec.y));
  return obj;
}

static JSValue js_dimensions_from_native(JSContext *ctx, Dimensions dims) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "width", JS_NewInt32(ctx, dims.width));
  JS_SetPropertyStr(ctx, obj, "height", JS_NewInt32(ctx, dims.height));
  return obj;
}

// BINDINGS

// Utilities
static JSValue js_current_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return JS_NewBigUint64(ctx, current_time());
}

static JSValue js_delta_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return JS_NewFloat64(ctx, delta_time());
}

static JSValue js_random_int(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 2)
    return JS_ThrowTypeError(ctx, "random_int() requires min and max");
  int32_t min, max;
  JS_ToInt32(ctx, &min, argv[0]);
  JS_ToInt32(ctx, &max, argv[1]);
  return JS_NewInt32(ctx, random_int(min, max));
}

// Graphics - Basic Drawing
static JSValue js_clear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 1)
    return JS_ThrowTypeError(ctx, "clear() requires a color");
  Color color = color_from_js(ctx, argv[0]);
  clear(color);
  return JS_UNDEFINED;
}

static JSValue js_draw_point(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 3)
    return JS_ThrowTypeError(ctx, "draw_point() requires x, y, color");
  int32_t x, y;
  JS_ToInt32(ctx, &x, argv[0]);
  JS_ToInt32(ctx, &y, argv[1]);
  Color color = color_from_js(ctx, argv[2]);
  draw_point(x, y, color);
  return JS_UNDEFINED;
}

static JSValue js_draw_line(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 5)
    return JS_ThrowTypeError(ctx, "draw_line() requires startX, startY, endX, endY, color");
  int32_t x1, y1, x2, y2;
  JS_ToInt32(ctx, &x1, argv[0]);
  JS_ToInt32(ctx, &y1, argv[1]);
  JS_ToInt32(ctx, &x2, argv[2]);
  JS_ToInt32(ctx, &y2, argv[3]);
  Color color = color_from_js(ctx, argv[4]);
  draw_line(x1, y1, x2, y2, color);
  return JS_UNDEFINED;
}

static JSValue js_draw_rectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 5)
    return JS_ThrowTypeError(ctx, "draw_rectangle() requires x, y, width, height, color");
  int32_t x, y, w, h;
  JS_ToInt32(ctx, &x, argv[0]);
  JS_ToInt32(ctx, &y, argv[1]);
  JS_ToInt32(ctx, &w, argv[2]);
  JS_ToInt32(ctx, &h, argv[3]);
  Color color = color_from_js(ctx, argv[4]);
  draw_rectangle(x, y, w, h, color);
  return JS_UNDEFINED;
}

static JSValue js_draw_circle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 4)
    return JS_ThrowTypeError(ctx, "draw_circle() requires centerX, centerY, radius, color");
  int32_t x, y, r;
  JS_ToInt32(ctx, &x, argv[0]);
  JS_ToInt32(ctx, &y, argv[1]);
  JS_ToInt32(ctx, &r, argv[2]);
  Color color = color_from_js(ctx, argv[3]);
  draw_circle(x, y, r, color);
  return JS_UNDEFINED;
}

// Input
static JSValue js_key_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 1)
    return JS_ThrowTypeError(ctx, "key_pressed() requires a key");
  int32_t key;
  JS_ToInt32(ctx, &key, argv[0]);
  return JS_NewBool(ctx, key_pressed((Key)key));
}

static JSValue js_key_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 1)
    return JS_ThrowTypeError(ctx, "key_down() requires a key");
  int32_t key;
  JS_ToInt32(ctx, &key, argv[0]);
  return JS_NewBool(ctx, key_down((Key)key));
}

static JSValue js_mouse_position(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  Vector *pos = mouse_position();
  return js_vector_from_native(ctx, *pos);
}

// Images
static JSValue js_load_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 1)
    return JS_ThrowTypeError(ctx, "load_image() requires filename");
  const char *filename = JS_ToCString(ctx, argv[0]);
  if (!filename)
    return JS_ThrowTypeError(ctx, "Invalid filename");
  u32 result = load_image((char *)filename);
  JS_FreeCString(ctx, filename);
  return JS_NewUint32(ctx, result);
}

static JSValue js_draw_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 3)
    return JS_ThrowTypeError(ctx, "draw_image() requires image, x, y");
  u32 img;
  int32_t x, y;
  JS_ToUint32(ctx, &img, argv[0]);
  JS_ToInt32(ctx, &x, argv[1]);
  JS_ToInt32(ctx, &y, argv[2]);
  draw_image(img, x, y);
  return JS_UNDEFINED;
}

// Text
static JSValue js_draw_text(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 5)
    return JS_ThrowTypeError(ctx, "draw_text() requires font, text, x, y, color");
  u32 font;
  int32_t x, y;
  JS_ToUint32(ctx, &font, argv[0]);
  const char *text = JS_ToCString(ctx, argv[1]);
  JS_ToInt32(ctx, &x, argv[2]);
  JS_ToInt32(ctx, &y, argv[3]);
  Color color = color_from_js(ctx, argv[4]);
  draw_text(font, (char *)text, x, y, color);
  JS_FreeCString(ctx, text);
  return JS_UNDEFINED;
}

// Game engine API bindings - replace these with your actual engine functions
static JSValue js_log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc > 0) {
    const char *str = JS_ToCString(ctx, argv[0]);
    if (str) {
      printf("%s\n", str);
      JS_FreeCString(ctx, str);
    }
  }
  return JS_UNDEFINED;
}

// Set up game engine bindings
static void setup_game_bindings() {
  JSValue global = JS_GetGlobalObject(ctx);

  // add color constants
  JS_SetPropertyStr(ctx, global, "LIGHTGRAY", js_color_from_native(ctx, LIGHTGRAY));
  JS_SetPropertyStr(ctx, global, "GRAY", js_color_from_native(ctx, GRAY));
  JS_SetPropertyStr(ctx, global, "DARKGRAY", js_color_from_native(ctx, DARKGRAY));
  JS_SetPropertyStr(ctx, global, "YELLOW", js_color_from_native(ctx, YELLOW));
  JS_SetPropertyStr(ctx, global, "GOLD", js_color_from_native(ctx, GOLD));
  JS_SetPropertyStr(ctx, global, "ORANGE", js_color_from_native(ctx, ORANGE));
  JS_SetPropertyStr(ctx, global, "PINK", js_color_from_native(ctx, PINK));
  JS_SetPropertyStr(ctx, global, "RED", js_color_from_native(ctx, RED));
  JS_SetPropertyStr(ctx, global, "MAROON", js_color_from_native(ctx, MAROON));
  JS_SetPropertyStr(ctx, global, "GREEN", js_color_from_native(ctx, GREEN));
  JS_SetPropertyStr(ctx, global, "LIME", js_color_from_native(ctx, LIME));
  JS_SetPropertyStr(ctx, global, "DARKGREEN", js_color_from_native(ctx, DARKGREEN));
  JS_SetPropertyStr(ctx, global, "SKYBLUE", js_color_from_native(ctx, SKYBLUE));
  JS_SetPropertyStr(ctx, global, "BLUE", js_color_from_native(ctx, BLUE));
  JS_SetPropertyStr(ctx, global, "DARKBLUE", js_color_from_native(ctx, DARKBLUE));
  JS_SetPropertyStr(ctx, global, "PURPLE", js_color_from_native(ctx, PURPLE));
  JS_SetPropertyStr(ctx, global, "VIOLET", js_color_from_native(ctx, VIOLET));
  JS_SetPropertyStr(ctx, global, "DARKPURPLE", js_color_from_native(ctx, DARKPURPLE));
  JS_SetPropertyStr(ctx, global, "BEIGE", js_color_from_native(ctx, BEIGE));
  JS_SetPropertyStr(ctx, global, "BROWN", js_color_from_native(ctx, BROWN));
  JS_SetPropertyStr(ctx, global, "DARKBROWN", js_color_from_native(ctx, DARKBROWN));
  JS_SetPropertyStr(ctx, global, "WHITE", js_color_from_native(ctx, WHITE));
  JS_SetPropertyStr(ctx, global, "BLACK", js_color_from_native(ctx, BLACK));
  JS_SetPropertyStr(ctx, global, "BLANK", js_color_from_native(ctx, BLANK));
  JS_SetPropertyStr(ctx, global, "MAGENTA", js_color_from_native(ctx, MAGENTA));
  JS_SetPropertyStr(ctx, global, "RAYWHITE", js_color_from_native(ctx, RAYWHITE));

  // Add key constants
  JS_SetPropertyStr(ctx, global, "KEY_SPACE", JS_NewInt32(ctx, KEY_SPACE));
  JS_SetPropertyStr(ctx, global, "KEY_A", JS_NewInt32(ctx, KEY_A));
  JS_SetPropertyStr(ctx, global, "KEY_W", JS_NewInt32(ctx, KEY_W));
  JS_SetPropertyStr(ctx, global, "KEY_S", JS_NewInt32(ctx, KEY_S));
  JS_SetPropertyStr(ctx, global, "KEY_D", JS_NewInt32(ctx, KEY_D));
  JS_SetPropertyStr(ctx, global, "KEY_ENTER", JS_NewInt32(ctx, KEY_ENTER));
  JS_SetPropertyStr(ctx, global, "KEY_ESCAPE", JS_NewInt32(ctx, KEY_ESCAPE));
  // TODO: add more

  // Screen constants
  JS_SetPropertyStr(ctx, global, "SCREEN", JS_NewInt32(ctx, SCREEN));
  JS_SetPropertyStr(ctx, global, "SCREEN_WIDTH", JS_NewInt32(ctx, SCREEN_WIDTH));
  JS_SetPropertyStr(ctx, global, "SCREEN_HEIGHT", JS_NewInt32(ctx, SCREEN_HEIGHT));
  JS_SetPropertyStr(ctx, global, "FONT_DEFAULT", JS_NewInt32(ctx, FONT_DEFAULT));

  // Add console.log function
  JSValue console_obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_log, "log", 1));
  JS_SetPropertyStr(ctx, global, "console", console_obj);

  // Utilities
  JS_SetPropertyStr(ctx, global, "current_time", JS_NewCFunction(ctx, js_current_time, "currentTime", 0));
  JS_SetPropertyStr(ctx, global, "delta_time", JS_NewCFunction(ctx, js_delta_time, "deltaTime", 0));
  JS_SetPropertyStr(ctx, global, "random_int", JS_NewCFunction(ctx, js_random_int, "randomInt", 2));

  // Graphics
  JS_SetPropertyStr(ctx, global, "clear", JS_NewCFunction(ctx, js_clear, "clear", 1));
  JS_SetPropertyStr(ctx, global, "draw_point", JS_NewCFunction(ctx, js_draw_point, "drawPoint", 3));
  JS_SetPropertyStr(ctx, global, "draw_line", JS_NewCFunction(ctx, js_draw_line, "drawLine", 5));
  JS_SetPropertyStr(ctx, global, "draw_rectangle", JS_NewCFunction(ctx, js_draw_rectangle, "drawRectangle", 5));
  JS_SetPropertyStr(ctx, global, "draw_circle", JS_NewCFunction(ctx, js_draw_circle, "drawCircle", 4));
  JS_SetPropertyStr(ctx, global, "load_image", JS_NewCFunction(ctx, js_load_image, "loadImage", 1));
  JS_SetPropertyStr(ctx, global, "draw_image", JS_NewCFunction(ctx, js_draw_image, "drawImage", 3));
  JS_SetPropertyStr(ctx, global, "draw_text", JS_NewCFunction(ctx, js_draw_text, "drawText", 5));

  // Input
  JS_SetPropertyStr(ctx, global, "key_pressed", JS_NewCFunction(ctx, js_key_pressed, "keyPressed", 1));
  JS_SetPropertyStr(ctx, global, "key_down", JS_NewCFunction(ctx, js_key_down, "keyDown", 1));
  JS_SetPropertyStr(ctx, global, "mouse_position", JS_NewCFunction(ctx, js_mouse_position, "mousePosition", 0));

  JS_FreeValue(ctx, global);
}

// Call a JavaScript function if it exists
static void call_js_function(const char *func_name) {
  JSValue global = JS_GetGlobalObject(ctx);
  JSValue func = JS_GetPropertyStr(ctx, global, func_name);

  if (JS_IsFunction(ctx, func)) {
    JSValue result = JS_Call(ctx, func, global, 0, NULL);
    if (JS_IsException(result)) {
      JSValue exception = JS_GetException(ctx);
      const char *error_str = JS_ToCString(ctx, exception);
      fprintf(stderr, "Error calling %s: %s\n", func_name, error_str ? error_str : "Unknown error");
      JS_FreeCString(ctx, error_str);
      JS_FreeValue(ctx, exception);
    }
    JS_FreeValue(ctx, result);
  }

  JS_FreeValue(ctx, func);
  JS_FreeValue(ctx, global);
}

int main(int argc, char **argv) {
  JSRuntime *rt = JS_NewRuntime();

  if (!rt) {
    fprintf(stderr, "Error: Failed to create QuickJS runtime\n");
    return 1;
  }
  ctx = JS_NewContext(rt);
  if (!ctx) {
    fprintf(stderr, "Error: Failed to create QuickJS context\n");
    JS_FreeRuntime(rt);
    return 1;
  }

  char *js_code = read_file("main.js");
  if (!js_code) {
    fprintf(stderr, "Error: Failed to load main.js\n");
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 1;
  }

  if (execute_js(js_code, "main.js") < 0) {
    free(js_code);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 1;
  }

  free(js_code);
  setup_game_bindings();

  call_js_function("load");
}

void update() {
  call_js_function("update");
}

void unload() {
  call_js_function("unload");
}
