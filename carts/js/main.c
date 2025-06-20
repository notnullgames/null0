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

static Color color_from_js(JSContext *ctx, JSValueConst color_obj) {
  Color color = {0, 0, 0, 255}; // Default: black with full alpha

  if (!JS_IsObject(color_obj)) {
    return color;
  }

  JSValue val;
  int32_t component;

  // Get r
  val = JS_GetPropertyStr(ctx, color_obj, "r");
  if (JS_ToInt32(ctx, &component, val) == 0) {
    color.r = component < 0 ? 0 : (component > 255 ? 255 : component);
  }
  JS_FreeValue(ctx, val);

  // Get g
  val = JS_GetPropertyStr(ctx, color_obj, "g");
  if (JS_ToInt32(ctx, &component, val) == 0) {
    color.g = component < 0 ? 0 : (component > 255 ? 255 : component);
  }
  JS_FreeValue(ctx, val);

  // Get b
  val = JS_GetPropertyStr(ctx, color_obj, "b");
  if (JS_ToInt32(ctx, &component, val) == 0) {
    color.b = component < 0 ? 0 : (component > 255 ? 255 : component);
  }
  JS_FreeValue(ctx, val);

  // Get a (only if defined)
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

static JSValue js_clear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc < 1) {
    return JS_ThrowTypeError(ctx, "clear() requires a color object");
  }

  Color color = color_from_js(ctx, argv[0]);
  clear(color);

  return JS_UNDEFINED;
}

// Set up game engine bindings
static void setup_game_bindings() {
  JSValue global = JS_GetGlobalObject(ctx);

  // add colors
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

  // Add console.log function
  JSValue console_obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_log, "log", 1));
  JS_SetPropertyStr(ctx, global, "console", console_obj);

  // Add clear function
  JS_SetPropertyStr(ctx, global, "clear", JS_NewCFunction(ctx, js_clear, "clear", 1));

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
