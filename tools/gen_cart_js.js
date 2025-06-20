// This will generate the QuickJS cart for making
import { writeFile } from 'node:fs/promises'
import { indent, createApiStream } from './utils.js'

const out = []

function add_colors() {
  const colors = ['LIGHTGRAY', 'GRAY', 'DARKGRAY', 'YELLOW', 'GOLD', 'ORANGE', 'PINK', 'RED', 'MAROON', 'GREEN', 'LIME', 'DARKGREEN', 'SKYBLUE', 'BLUE', 'DARKBLUE', 'PURPLE', 'VIOLET', 'DARKPURPLE', 'BEIGE', 'BROWN', 'DARKBROWN', 'WHITE', 'BLACK', 'BLANK', 'MAGENTA', 'RAYWHITE']
  for (const color of colors) {
    out.push(indent(`JS_SetPropertyStr(ctx, global, "${color}", color_to_js(${color}));`, 2))
  }
}

function add_consts() {
  const consts = ['FILTER_NEARESTNEIGHBOR', 'FILTER_BILINEAR', 'FILTER_SMOOTH', 'KEY_INVALID', 'KEY_SPACE', 'KEY_APOSTROPHE', 'KEY_COMMA', 'KEY_MINUS', 'KEY_PERIOD', 'KEY_SLASH', 'KEY_0', 'KEY_1', 'KEY_2', 'KEY_3', 'KEY_4', 'KEY_5', 'KEY_6', 'KEY_7', 'KEY_8', 'KEY_9', 'KEY_SEMICOLON', 'KEY_EQUAL', 'KEY_A', 'KEY_B', 'KEY_C', 'KEY_D', 'KEY_E', 'KEY_F', 'KEY_G', 'KEY_H', 'KEY_I', 'KEY_J', 'KEY_K', 'KEY_L', 'KEY_M', 'KEY_N', 'KEY_O', 'KEY_P', 'KEY_Q', 'KEY_R', 'KEY_S', 'KEY_T', 'KEY_U', 'KEY_V', 'KEY_W', 'KEY_X', 'KEY_Y', 'KEY_Z', 'KEY_LEFT_BRACKET', 'KEY_BACKSLASH', 'KEY_RIGHT_BRACKET', 'KEY_GRAVE_ACCENT', 'KEY_WORLD_1', 'KEY_WORLD_2', 'KEY_ESCAPE', 'KEY_ENTER', 'KEY_TAB', 'KEY_BACKSPACE', 'KEY_INSERT', 'KEY_DELETE', 'KEY_RIGHT', 'KEY_LEFT', 'KEY_DOWN', 'KEY_UP', 'KEY_PAGE_UP', 'KEY_PAGE_DOWN', 'KEY_HOME', 'KEY_END', 'KEY_CAPS_LOCK', 'KEY_SCROLL_LOCK', 'KEY_NUM_LOCK', 'KEY_PRINT_SCREEN', 'KEY_PAUSE', 'KEY_F1', 'KEY_F2', 'KEY_F3', 'KEY_F4', 'KEY_F5', 'KEY_F6', 'KEY_F7', 'KEY_F8', 'KEY_F9', 'KEY_F10', 'KEY_F11', 'KEY_F12', 'KEY_F13', 'KEY_F14', 'KEY_F15', 'KEY_F16', 'KEY_F17', 'KEY_F18', 'KEY_F19', 'KEY_F20', 'KEY_F21', 'KEY_F22', 'KEY_F23', 'KEY_F24', 'KEY_F25', 'KEY_KP_0', 'KEY_KP_1', 'KEY_KP_2', 'KEY_KP_3', 'KEY_KP_4', 'KEY_KP_5', 'KEY_KP_6', 'KEY_KP_7', 'KEY_KP_8', 'KEY_KP_9', 'KEY_KP_DECIMAL', 'KEY_KP_DIVIDE', 'KEY_KP_MULTIPLY', 'KEY_KP_SUBTRACT', 'KEY_KP_ADD', 'KEY_KP_ENTER', 'KEY_KP_EQUAL', 'KEY_LEFT_SHIFT', 'KEY_LEFT_CONTROL', 'KEY_LEFT_ALT', 'KEY_LEFT_SUPER', 'KEY_RIGHT_SHIFT', 'KEY_RIGHT_CONTROL', 'KEY_RIGHT_ALT', 'KEY_RIGHT_SUPER', 'KEY_MENU', 'GAMEPAD_BUTTON_UNKNOWN', 'GAMEPAD_BUTTON_UP', 'GAMEPAD_BUTTON_RIGHT', 'GAMEPAD_BUTTON_DOWN', 'GAMEPAD_BUTTON_LEFT', 'GAMEPAD_BUTTON_Y', 'GAMEPAD_BUTTON_B', 'GAMEPAD_BUTTON_A', 'GAMEPAD_BUTTON_X', 'GAMEPAD_BUTTON_LEFT_SHOULDER', 'GAMEPAD_BUTTON_LEFT_TRIGGER', 'GAMEPAD_BUTTON_RIGHT_SHOULDER', 'GAMEPAD_BUTTON_RIGHT_TRIGGER', 'GAMEPAD_BUTTON_SELECT', 'GAMEPAD_BUTTON_MENU', 'GAMEPAD_BUTTON_START', 'GAMEPAD_BUTTON_LEFT_THUMB', 'GAMEPAD_BUTTON_RIGHT_THUMB', 'MOUSE_BUTTON_UNKNOWN', 'MOUSE_BUTTON_LEFT', 'MOUSE_BUTTON_RIGHT', 'MOUSE_BUTTON_MIDDLE', 'SCREEN', 'SCREEN_WIDTH', 'SCREEN_HEIGHT', 'FONT_DEFAULT']

  for (const c of consts) {
    out.push(indent(`JS_SetPropertyStr(ctx, global, "${c}", JS_NewInt32(ctx, ${c}));`, 2))
  }
}

out.push(`#include "../null0.h"
#include "quickjs.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

JSValue global;
JSContext *ctx;
JSValue callback_params[2] = {};
JSValue func_unload;
JSValue func_update;
JSValue func_buttonUp;
JSValue func_buttonDown;
JSValue func_keyUp;
JSValue func_keyDown;
JSValue func_mouseDown;
JSValue func_mouseUp;
JSValue func_mouseMoved;

static JSValue dimensions_to_js(Dimensions dims) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "width", JS_NewUint32(ctx, dims.width));
  JS_SetPropertyStr(ctx, obj, "height", JS_NewUint32(ctx, dims.height));
  return obj;
}

static JSValue vector_to_js(Vector vec) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "x", JS_NewInt32(ctx, vec.x));
  JS_SetPropertyStr(ctx, obj, "y", JS_NewInt32(ctx, vec.y));
  return obj;
}

static JSValue rectangle_to_js(Rectangle rect) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "x", JS_NewInt32(ctx, rect.x));
  JS_SetPropertyStr(ctx, obj, "y", JS_NewInt32(ctx, rect.y));
  JS_SetPropertyStr(ctx, obj, "width", JS_NewInt32(ctx, rect.width));
  JS_SetPropertyStr(ctx, obj, "height", JS_NewInt32(ctx, rect.height));
  return obj;
}

static JSValue color_to_js(Color color) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "r", JS_NewInt32(ctx, color.r));
  JS_SetPropertyStr(ctx, obj, "g", JS_NewInt32(ctx, color.g));
  JS_SetPropertyStr(ctx, obj, "b", JS_NewInt32(ctx, color.b));
  JS_SetPropertyStr(ctx, obj, "a", JS_NewInt32(ctx, color.a));
  return obj;
}

static int dimensions_from_js(JSValue obj, Dimensions *dims) {
  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");

  if (JS_IsException(width_val) || JS_IsException(height_val)) {
    JS_FreeValue(ctx, width_val);
    JS_FreeValue(ctx, height_val);
    return -1;
  }

  uint32_t width, height;
  if (JS_ToUint32(ctx, &width, width_val) < 0 ||
      JS_ToUint32(ctx, &height, height_val) < 0) {
    JS_FreeValue(ctx, width_val);
    JS_FreeValue(ctx, height_val);
    return -1;
  }

  dims->width = width;
  dims->height = height;

  JS_FreeValue(ctx, width_val);
  JS_FreeValue(ctx, height_val);
  return 0;
}

static int vector_from_js(JSValue obj, Vector *vec) {
  JSValue x_val = JS_GetPropertyStr(ctx, obj, "x");
  JSValue y_val = JS_GetPropertyStr(ctx, obj, "y");

  if (JS_IsException(x_val) || JS_IsException(y_val)) {
    JS_FreeValue(ctx, x_val);
    JS_FreeValue(ctx, y_val);
    return -1;
  }

  int32_t x, y;
  if (JS_ToInt32(ctx, &x, x_val) < 0 ||
      JS_ToInt32(ctx, &y, y_val) < 0) {
    JS_FreeValue(ctx, x_val);
    JS_FreeValue(ctx, y_val);
    return -1;
  }

  vec->x = x;
  vec->y = y;

  JS_FreeValue(ctx, x_val);
  JS_FreeValue(ctx, y_val);
  return 0;
}

static int rectangle_from_js(JSValue obj, Rectangle *rect) {
  JSValue x_val = JS_GetPropertyStr(ctx, obj, "x");
  JSValue y_val = JS_GetPropertyStr(ctx, obj, "y");
  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");

  if (JS_IsException(x_val) || JS_IsException(y_val) ||
      JS_IsException(width_val) || JS_IsException(height_val)) {
    JS_FreeValue(ctx, x_val);
    JS_FreeValue(ctx, y_val);
    JS_FreeValue(ctx, width_val);
    JS_FreeValue(ctx, height_val);
    return -1;
  }

  int32_t x, y, width, height;
  if (JS_ToInt32(ctx, &x, x_val) < 0 ||
      JS_ToInt32(ctx, &y, y_val) < 0 ||
      JS_ToInt32(ctx, &width, width_val) < 0 ||
      JS_ToInt32(ctx, &height, height_val) < 0) {
    JS_FreeValue(ctx, x_val);
    JS_FreeValue(ctx, y_val);
    JS_FreeValue(ctx, width_val);
    JS_FreeValue(ctx, height_val);
    return -1;
  }

  rect->x = x;
  rect->y = y;
  rect->width = width;
  rect->height = height;

  JS_FreeValue(ctx, x_val);
  JS_FreeValue(ctx, y_val);
  JS_FreeValue(ctx, width_val);
  JS_FreeValue(ctx, height_val);
  return 0;
}

static int color_from_js(JSValue obj, Color *color) {
  JSValue r_val = JS_GetPropertyStr(ctx, obj, "r");
  JSValue g_val = JS_GetPropertyStr(ctx, obj, "g");
  JSValue b_val = JS_GetPropertyStr(ctx, obj, "b");
  JSValue a_val = JS_GetPropertyStr(ctx, obj, "a");

  if (JS_IsException(r_val) || JS_IsException(g_val) ||
      JS_IsException(b_val) || JS_IsException(a_val)) {
    JS_FreeValue(ctx, r_val);
    JS_FreeValue(ctx, g_val);
    JS_FreeValue(ctx, b_val);
    JS_FreeValue(ctx, a_val);
    return -1;
  }

  uint32_t r, g, b, a;
  if (JS_ToUint32(ctx, &r, r_val) < 0 || r > 255 ||
      JS_ToUint32(ctx, &g, g_val) < 0 || g > 255 ||
      JS_ToUint32(ctx, &b, b_val) < 0 || b > 255 ||
      JS_ToUint32(ctx, &a, a_val) < 0 || a > 255) {
    JS_FreeValue(ctx, r_val);
    JS_FreeValue(ctx, g_val);
    JS_FreeValue(ctx, b_val);
    JS_FreeValue(ctx, a_val);
    return -1;
  }

  color->r = (uint8_t)r;
  color->g = (uint8_t)g;
  color->b = (uint8_t)b;
  color->a = (uint8_t)a;

  JS_FreeValue(ctx, r_val);
  JS_FreeValue(ctx, g_val);
  JS_FreeValue(ctx, b_val);
  JS_FreeValue(ctx, a_val);
  return 0;
}

void expose_things_to_js();

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

static int execute_js_file(const char *filename) {
  char *code = read_file(filename);
  if (code == NULL) {
    return -1;
  }
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
  free(code);
  JS_FreeValue(ctx, result);
  return 0;
}

int run_func(JSValue func, char* func_name, int argc, JSValue* args) {
  if (JS_IsFunction(ctx, func)) {
    JSValue result = JS_Call(ctx, func, global, argc, args);
    if (JS_IsException(result)) {
      JSValue exception = JS_GetException(ctx);
      const char *error_str = JS_ToCString(ctx, exception);
      fprintf(stderr, "Error calling %s: %s\\n", func_name, error_str ? error_str : "Unknown error");
      JS_FreeCString(ctx, error_str);
      JS_FreeValue(ctx, exception);
    }
    JS_FreeValue(ctx, result);
    return 1;
  }
  return 0;
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
  global = JS_GetGlobalObject(ctx);
  if (execute_js_file("main.js") != 0) {
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    JS_FreeValue(ctx, global);
    return 1;
  }
  JSValue func_load = JS_GetPropertyStr(ctx, global, "load");
  func_unload = JS_GetPropertyStr(ctx, global, "unload");
  func_update = JS_GetPropertyStr(ctx, global, "update");
  func_buttonDown = JS_GetPropertyStr(ctx, global, "buttonDown");
  func_buttonUp = JS_GetPropertyStr(ctx, global, "buttonUp");
  func_keyUp = JS_GetPropertyStr(ctx, global, "keyUp");
  func_keyDown = JS_GetPropertyStr(ctx, global, "keyDown");
  func_mouseUp = JS_GetPropertyStr(ctx, global, "mouseUp");
  func_mouseDown = JS_GetPropertyStr(ctx, global, "mouseDown");
  func_mouseMoved = JS_GetPropertyStr(ctx, global, "mouseMoved");

  expose_things_to_js();

  run_func(func_load, "load", 0, NULL);
  return 0;
}

void update() {
  run_func(func_update, "update", 0, NULL);
}

void unload() {
  run_func(func_unload, "unload", 0, NULL);
}

void buttonUp(GamepadButton button, unsigned int player) {
  JS_ToInt32(ctx, &button, callback_params[0]);
  JS_ToInt32(ctx, &player, callback_params[1]);
  run_func(func_buttonUp, "buttonUp", 2, callback_params);
}

void buttonDown(GamepadButton button, unsigned int player) {
  JS_ToInt32(ctx, &button, callback_params[0]);
  JS_ToInt32(ctx, &player, callback_params[1]);
  run_func(func_buttonDown, "buttonDown", 2, callback_params);
}

void keyUp(Key key) {
  JS_ToInt32(ctx, &key, callback_params[0]);
  run_func(func_keyUp, "keyUp", 1, callback_params);
}

void keyDown(Key key) {
  JS_ToInt32(ctx, &key, callback_params[0]);
  run_func(func_keyDown, "keyDown", 1, callback_params);
}

void mouseDown(unsigned int button) {
  JS_ToInt32(ctx, &button, callback_params[0]);
  run_func(func_mouseDown, "mouseDown", 1, callback_params);
}

void mouseUp(unsigned int button) {
  JS_ToInt32(ctx, &button, callback_params[0]);
  run_func(func_mouseUp, "mouseUp", 1, callback_params);
}

void mouseMoved(float x, float y) {
  JS_ToFloat64(ctx, &x, callback_params[0]);
  JS_ToFloat64(ctx, &y, callback_params[1]);
  run_func(func_mouseMoved, "mouseMoved", 2, callback_params);
}

// BINDINGS
static JSValue js_console_log(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
  if (argc > 0) {
    const char *str = JS_ToCString(ctx, argv[0]);
    if (str) {
      printf("%s\\n", str);
      JS_FreeCString(ctx, str);
    }
  }
  return JS_UNDEFINED;
}

`)

const returnMap = {}

const argTypes = {}

const api = createApiStream()

const funcs = []

api.on('api', (apiName) => {
  out.push('', `// ${apiName.toUpperCase()}`, '')
})

api.on('end', async () => {
  out.push('void expose_things_to_js() {')
  add_colors()
  out.push('')
  add_consts()
  out.push('')

  out.push(
    indent(`JSValue console_obj = JS_NewObject(ctx);
JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_console_log, "log", 1));
JS_SetPropertyStr(ctx, global, "console", console_obj);
`)
  )
  out.push(...funcs)
  out.push('}')

  await writeFile('carts/js/main.c', out.join('\n'))
})

api.on('function', ({ apiName, funcName, args = {}, returns = 'void', description = '' }) => {
  funcs.push(indent(`JS_SetPropertyStr(ctx, global, "${funcName}", JS_NewCFunction(ctx, js_${funcName}, "${funcName}", ${Object.keys(args).length}));`, 2))
  out.push(`// ${description}`)
  out.push(`static JSValue js_${funcName}(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {`)

  let i = -1
  for (const [name, type] of Object.entries(args)) {
    i++
    if (argTypes[type]) {
      out.push(indent(`//`))
    }
  }

  if (returns === 'void') {
    out.push(indent(`${funcName}(${Object.keys(args).join(', ')});\nreturn JS_UNDEFINED;`))
  } else {
    out.push(indent(`return ${returnMap[returns]}(${funcName}(${Object.keys(args).join(', ')}));`))
  }
  out.push('}')
})
