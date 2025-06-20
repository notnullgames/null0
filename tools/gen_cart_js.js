// This will generate the QuickJS cart for making
import { writeFile } from 'node:fs/promises'
import { indent, createApiStream } from './utils.js'

const out = [
  `#include "../null0.h"
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
    fprintf(stderr, "Error: Cannot open file '%s'\\n", filename);
    return NULL;
  }

  struct stat st;
  if (fstat(fd, &st) < 0) {
    close(fd);
    fprintf(stderr, "Error: Cannot stat file '%s'\\n", filename);
    return NULL;
  }

  size_t size = st.st_size;
  char *buffer = malloc(size + 1);
  if (!buffer) {
    close(fd);
    fprintf(stderr, "Error: Memory allocation failed\\n");
    return NULL;
  }

  ssize_t bytes_read = read(fd, buffer, size);
  close(fd);

  if (bytes_read != size) {
    free(buffer);
    fprintf(stderr, "Error: Failed to read complete file\\n");
    return NULL;
  }

  buffer[size] = '\\0';
  return buffer;
}

JSContext *ctx;

// Execute JavaScript and handle errors
static int execute_js(const char *code, const char *filename) {
  JSValue result = JS_Eval(ctx, code, strlen(code), filename, JS_EVAL_TYPE_GLOBAL);

  if (JS_IsException(result)) {
    JSValue exception = JS_GetException(ctx);
    const char *error_str = JS_ToCString(ctx, exception);
    fprintf(stderr, "JavaScript Error: %s\\n", error_str ? error_str : "Unknown error");
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

static JSValue js_log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc > 0) {
    const char *str = JS_ToCString(ctx, argv[0]);
    if (str) {
      printf("%s\\n", str);
      JS_FreeCString(ctx, str);
    }
  }
  return JS_UNDEFINED;
}
`
]

// TODO: add Date functons
// TODO: add Math functions

const api = createApiStream()

const funcdefs = []

api.on('api', (apiName) => {
  out.push('', indent(`// ${apiName.toUpperCase()}`, 2), '')
})

api.on('function', ({ apiName, funcName, args = {}, returns = 'void', description = '' }) => {
  out.push(indent(`// ${description}`, 2))
  // TODO: build function-binding
  out.push(
    indent(
      `static JSValue js_${funcName}(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  return JS_UNDEFINED;
}`,
      2
    )
  )
  funcdefs.push(`JS_SetPropertyStr(ctx, global, "${funcName}", JS_NewCFunction(ctx, js_${funcName}, "${funcName}", ${Object.keys(args).length}));`)
})

api.on('end', async () => {
  const colors = ['LIGHTGRAY', 'GRAY', 'DARKGRAY', 'YELLOW', 'GOLD', 'ORANGE', 'PINK', 'RED', 'MAROON', 'GREEN', 'LIME', 'DARKGREEN', 'SKYBLUE', 'BLUE', 'DARKBLUE', 'PURPLE', 'VIOLET', 'DARKPURPLE', 'BEIGE', 'BROWN', 'DARKBROWN', 'WHITE', 'BLACK', 'BLANK', 'MAGENTA', 'RAYWHITE']

  const consts = ['FILTER_NEARESTNEIGHBOR', 'FILTER_BILINEAR', 'FILTER_SMOOTH', 'KEY_INVALID', 'KEY_SPACE', 'KEY_APOSTROPHE', 'KEY_COMMA', 'KEY_MINUS', 'KEY_PERIOD', 'KEY_SLASH', 'KEY_0', 'KEY_1', 'KEY_2', 'KEY_3', 'KEY_4', 'KEY_5', 'KEY_6', 'KEY_7', 'KEY_8', 'KEY_9', 'KEY_SEMICOLON', 'KEY_EQUAL', 'KEY_A', 'KEY_B', 'KEY_C', 'KEY_D', 'KEY_E', 'KEY_F', 'KEY_G', 'KEY_H', 'KEY_I', 'KEY_J', 'KEY_K', 'KEY_L', 'KEY_M', 'KEY_N', 'KEY_O', 'KEY_P', 'KEY_Q', 'KEY_R', 'KEY_S', 'KEY_T', 'KEY_U', 'KEY_V', 'KEY_W', 'KEY_X', 'KEY_Y', 'KEY_Z', 'KEY_LEFT_BRACKET', 'KEY_BACKSLASH', 'KEY_RIGHT_BRACKET', 'KEY_GRAVE_ACCENT', 'KEY_WORLD_1', 'KEY_WORLD_2', 'KEY_ESCAPE', 'KEY_ENTER', 'KEY_TAB', 'KEY_BACKSPACE', 'KEY_INSERT', 'KEY_DELETE', 'KEY_RIGHT', 'KEY_LEFT', 'KEY_DOWN', 'KEY_UP', 'KEY_PAGE_UP', 'KEY_PAGE_DOWN', 'KEY_HOME', 'KEY_END', 'KEY_CAPS_LOCK', 'KEY_SCROLL_LOCK', 'KEY_NUM_LOCK', 'KEY_PRINT_SCREEN', 'KEY_PAUSE', 'KEY_F1', 'KEY_F2', 'KEY_F3', 'KEY_F4', 'KEY_F5', 'KEY_F6', 'KEY_F7', 'KEY_F8', 'KEY_F9', 'KEY_F10', 'KEY_F11', 'KEY_F12', 'KEY_F13', 'KEY_F14', 'KEY_F15', 'KEY_F16', 'KEY_F17', 'KEY_F18', 'KEY_F19', 'KEY_F20', 'KEY_F21', 'KEY_F22', 'KEY_F23', 'KEY_F24', 'KEY_F25', 'KEY_KP_0', 'KEY_KP_1', 'KEY_KP_2', 'KEY_KP_3', 'KEY_KP_4', 'KEY_KP_5', 'KEY_KP_6', 'KEY_KP_7', 'KEY_KP_8', 'KEY_KP_9', 'KEY_KP_DECIMAL', 'KEY_KP_DIVIDE', 'KEY_KP_MULTIPLY', 'KEY_KP_SUBTRACT', 'KEY_KP_ADD', 'KEY_KP_ENTER', 'KEY_KP_EQUAL', 'KEY_LEFT_SHIFT', 'KEY_LEFT_CONTROL', 'KEY_LEFT_ALT', 'KEY_LEFT_SUPER', 'KEY_RIGHT_SHIFT', 'KEY_RIGHT_CONTROL', 'KEY_RIGHT_ALT', 'KEY_RIGHT_SUPER', 'KEY_MENU', 'GAMEPAD_BUTTON_UNKNOWN', 'GAMEPAD_BUTTON_UP', 'GAMEPAD_BUTTON_RIGHT', 'GAMEPAD_BUTTON_DOWN', 'GAMEPAD_BUTTON_LEFT', 'GAMEPAD_BUTTON_Y', 'GAMEPAD_BUTTON_B', 'GAMEPAD_BUTTON_A', 'GAMEPAD_BUTTON_X', 'GAMEPAD_BUTTON_LEFT_SHOULDER', 'GAMEPAD_BUTTON_LEFT_TRIGGER', 'GAMEPAD_BUTTON_RIGHT_SHOULDER', 'GAMEPAD_BUTTON_RIGHT_TRIGGER', 'GAMEPAD_BUTTON_SELECT', 'GAMEPAD_BUTTON_MENU', 'GAMEPAD_BUTTON_START', 'GAMEPAD_BUTTON_LEFT_THUMB', 'GAMEPAD_BUTTON_RIGHT_THUMB', 'MOUSE_BUTTON_UNKNOWN', 'MOUSE_BUTTON_LEFT', 'MOUSE_BUTTON_RIGHT', 'MOUSE_BUTTON_MIDDLE', 'SCREEN', 'SCREEN_WIDTH', 'SCREEN_HEIGHT', 'FONT_DEFAULT']

  out.push(`
// Set up game engine bindings
static void setup_game_bindings() {
  JSValue global = JS_GetGlobalObject(ctx);

  // Add console.log function
  JSValue console_obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_log, "log", 1));
  JS_SetPropertyStr(ctx, global, "console", console_obj);

${indent(funcdefs.join('\n'), 2)}
`)

  for (const color of colors) {
    out.push(indent(`JS_SetPropertyStr(ctx, global, "${color}", js_color_from_native(ctx, ${color}));`, 2))
  }

  out.push('')

  for (const c of consts) {
    out.push(indent(`JS_SetPropertyStr(ctx, global, "${c}", JS_NewInt32(ctx, ${c}));`, 2))
  }

  out.push(`
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
      fprintf(stderr, "Error calling %s: %s\\n", func_name, error_str ? error_str : "Unknown error");
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
    fprintf(stderr, "Error: Failed to create QuickJS runtime\\n");
    return 1;
  }
  ctx = JS_NewContext(rt);
  if (!ctx) {
    fprintf(stderr, "Error: Failed to create QuickJS context\\n");
    JS_FreeRuntime(rt);
    return 1;
  }

  char *js_code = read_file("main.js");
  if (!js_code) {
    fprintf(stderr, "Error: Failed to load main.js\\n");
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
`)

  // TODO: add event-callbacks

  await writeFile('carts/js/main.c', out.join('\n'))
})

api.on('error', (e) => {
  console.error(e)
})
