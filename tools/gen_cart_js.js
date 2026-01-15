// This will generate the QuickJS cart for making
import { writeFile } from 'node:fs/promises'
import { indent, getApi } from './utils.js'

const out = []

function add_colors() {
  const colors = ['LIGHTGRAY', 'GRAY', 'DARKGRAY', 'YELLOW', 'GOLD', 'ORANGE', 'PINK', 'RED', 'MAROON', 'GREEN', 'LIME', 'DARKGREEN', 'SKYBLUE', 'BLUE', 'DARKBLUE', 'PURPLE', 'VIOLET', 'DARKPURPLE', 'BEIGE', 'BROWN', 'DARKBROWN', 'WHITE', 'BLACK', 'BLANK', 'MAGENTA', 'RAYWHITE']
  for (const color of colors) {
    out.push(indent(`JS_SetPropertyStr(ctx, global, "${color}", color_to_js(${color}));`, 2))
  }
}

function add_consts() {
  const consts = ['FILTER_NEARESTNEIGHBOR', 'FILTER_BILINEAR', 'FILTER_SMOOTH', 'KEY_INVALID', 'KEY_SPACE', 'KEY_APOSTROPHE', 'KEY_COMMA', 'KEY_MINUS', 'KEY_PERIOD', 'KEY_SLASH', 'KEY_0', 'KEY_1', 'KEY_2', 'KEY_3', 'KEY_4', 'KEY_5', 'KEY_6', 'KEY_7', 'KEY_8', 'KEY_9', 'KEY_SEMICOLON', 'KEY_EQUAL', 'KEY_A', 'KEY_B', 'KEY_C', 'KEY_D', 'KEY_E', 'KEY_F', 'KEY_G', 'KEY_H', 'KEY_I', 'KEY_J', 'KEY_K', 'KEY_L', 'KEY_M', 'KEY_N', 'KEY_O', 'KEY_P', 'KEY_Q', 'KEY_R', 'KEY_S', 'KEY_T', 'KEY_U', 'KEY_V', 'KEY_W', 'KEY_X', 'KEY_Y', 'KEY_Z', 'KEY_LEFT_BRACKET', 'KEY_BACKSLASH', 'KEY_RIGHT_BRACKET', 'KEY_GRAVE_ACCENT', 'KEY_WORLD_1', 'KEY_WORLD_2', 'KEY_ESCAPE', 'KEY_ENTER', 'KEY_TAB', 'KEY_BACKSPACE', 'KEY_INSERT', 'KEY_DELETE', 'KEY_RIGHT', 'KEY_LEFT', 'KEY_DOWN', 'KEY_UP', 'KEY_PAGE_UP', 'KEY_PAGE_DOWN', 'KEY_HOME', 'KEY_END', 'KEY_CAPS_LOCK', 'KEY_SCROLL_LOCK', 'KEY_NUM_LOCK', 'KEY_PRINT_SCREEN', 'KEY_PAUSE', 'KEY_F1', 'KEY_F2', 'KEY_F3', 'KEY_F4', 'KEY_F5', 'KEY_F6', 'KEY_F7', 'KEY_F8', 'KEY_F9', 'KEY_F10', 'KEY_F11', 'KEY_F12', 'KEY_F13', 'KEY_F14', 'KEY_F15', 'KEY_F16', 'KEY_F17', 'KEY_F18', 'KEY_F19', 'KEY_F20', 'KEY_F21', 'KEY_F22', 'KEY_F23', 'KEY_F24', 'KEY_F25', 'KEY_KP_0', 'KEY_KP_1', 'KEY_KP_2', 'KEY_KP_3', 'KEY_KP_4', 'KEY_KP_5', 'KEY_KP_6', 'KEY_KP_7', 'KEY_KP_8', 'KEY_KP_9', 'KEY_KP_DECIMAL', 'KEY_KP_DIVIDE', 'KEY_KP_MULTIPLY', 'KEY_KP_SUBTRACT', 'KEY_KP_ADD', 'KEY_KP_ENTER', 'KEY_KP_EQUAL', 'KEY_LEFT_SHIFT', 'KEY_LEFT_CONTROL', 'KEY_LEFT_ALT', 'KEY_LEFT_SUPER', 'KEY_RIGHT_SHIFT', 'KEY_RIGHT_CONTROL', 'KEY_RIGHT_ALT', 'KEY_RIGHT_SUPER', 'KEY_MENU', 'GAMEPAD_BUTTON_UNKNOWN', 'GAMEPAD_BUTTON_UP', 'GAMEPAD_BUTTON_RIGHT', 'GAMEPAD_BUTTON_DOWN', 'GAMEPAD_BUTTON_LEFT', 'GAMEPAD_BUTTON_Y', 'GAMEPAD_BUTTON_B', 'GAMEPAD_BUTTON_A', 'GAMEPAD_BUTTON_X', 'GAMEPAD_BUTTON_LEFT_SHOULDER', 'GAMEPAD_BUTTON_LEFT_TRIGGER', 'GAMEPAD_BUTTON_RIGHT_SHOULDER', 'GAMEPAD_BUTTON_RIGHT_TRIGGER', 'GAMEPAD_BUTTON_SELECT', 'GAMEPAD_BUTTON_MENU', 'GAMEPAD_BUTTON_START', 'GAMEPAD_BUTTON_LEFT_THUMB', 'GAMEPAD_BUTTON_RIGHT_THUMB', 'MOUSE_BUTTON_UNKNOWN', 'MOUSE_BUTTON_LEFT', 'MOUSE_BUTTON_RIGHT', 'MOUSE_BUTTON_MIDDLE', 'SCREEN', 'SCREEN_WIDTH', 'SCREEN_HEIGHT', 'FONT_DEFAULT', 'SFX_COIN', 'SFX_LASER', 'SFX_EXPLOSION', 'SFX_POWERUP', 'SFX_HURT', 'SFX_JUMP', 'SFX_SELECT', 'SFX_SYNTH']

  for (const c of consts) {
    out.push(indent(`JS_SetPropertyStr(ctx, global, "${c}", JS_NewInt32(ctx, ${c}));`, 2))
  }
}

out.push(`#include "null0.h"
#include "quickjs.h"
#include "quickjs-libc.h"

JSRuntime *rt;
JSContext *ctx;
JSValue global;
JSValue args[2];

void expose_things_to_js();

// callback something in cart
void cart(const char* func_name, JSValue* args, int argc) {
  JSValue cart = JS_GetPropertyStr(ctx, global, "cart");
  if (!JS_IsUndefined(cart)) {
    JSValue func = JS_GetPropertyStr(ctx, cart, func_name);
    if (JS_IsFunction(ctx, func)) {
      JSValue result = JS_Call(ctx, func, cart, argc, args);
      if (JS_IsException(result)) {
        js_std_dump_error(ctx);
      }
      JS_FreeValue(ctx, result);
    } else {
      // printf("cart.%s() not defined\\n", func_name);
    }
    JS_FreeValue(ctx, func);
  } else {
    printf("cart not defined when calling %s\\n", func_name);
  }
  JS_FreeValue(ctx, cart);
}

int main(int argc, char* argv[]) {
  rt = JS_NewRuntime();
  ctx = JS_NewContext(rt);
  global = JS_GetGlobalObject(ctx);

  JS_SetMemoryLimit(rt, 0x4000000); // 64 Mb
  JS_SetMaxStackSize(rt, 0x10000); // 64 Kb
  JS_SetModuleLoaderFunc2(rt, NULL, js_module_loader, NULL, NULL);
  js_std_add_helpers(ctx, 0, NULL);

  expose_things_to_js();

  // setup std/os globals/modules
  js_init_module_std(ctx, "std");
  js_init_module_os(ctx, "os");
  const char *str = "import * as std from 'std';\\n"
    "import * as os from 'os';\\n"
    "import * as cart from './main.js';\\n"
    "globalThis.cart = cart;\\n"
    "globalThis.std = std;\\n"
    "globalThis.os = os;\\n"
    "cart?.load && cart.load();\\n";
  
  JSValue std_val = JS_Eval(ctx, str, strlen(str), "<CART>", JS_EVAL_TYPE_MODULE);
  
  if (!JS_IsException(std_val)) {
    js_module_set_import_meta(ctx, std_val, true, true);
    std_val = JS_EvalFunction(ctx, std_val);
  } else {
    js_std_dump_error(ctx);
  }
  
  std_val = js_std_await(ctx, std_val);

  JS_FreeValue(ctx, std_val);
}

void update() {
  cart("update", NULL, 0);
  fflush(stdout);
}

void buttonDown(GamepadButton button, unsigned int player) {
  args[0] = JS_NewInt32(ctx, (int)button);
  args[1] = JS_NewUint32(ctx, player);
  cart("buttonDown", args, 2);
}

void buttonUp(GamepadButton button, unsigned int player) {
  args[0] = JS_NewInt32(ctx, (int)button);
  args[1] = JS_NewUint32(ctx, player);
  cart("buttonUp", args, 2);
}

void keyUp(Key key) {
  args[0] = JS_NewInt32(ctx, (int)key);
  cart("keyUp", args, 1);
}

void keyDown(Key key) {
  args[0] = JS_NewInt32(ctx, (int)key);
  cart("keyDown", args, 1);
}

void mouseDown(unsigned int button) {
  args[0] = JS_NewUint32(ctx, button);
  cart("mouseDown", args, 1);
}

void mouseUp(unsigned int button) {
  args[0] = JS_NewUint32(ctx, button);
  cart("mouseUp", args, 1);
}

void mouseMoved(float x, float y) {
  args[0] = JS_NewFloat64(ctx, x);
  args[1] = JS_NewFloat64(ctx, y);
  cart("mouseMoved", args, 2);
}

void unload() {
  cart("unload", NULL, 0);
  // TODO: cleanup quickjs runtime vars, too
}


// type-converters

static JSValue bool_to_js(bool value) {
  return JS_NewBool(ctx, value);
}

static JSValue i32_to_js(int32_t value) {
  return JS_NewInt32(ctx, value);
}

static JSValue u32_to_js(uint32_t value) {
  return JS_NewUint32(ctx, value);
}

static JSValue f32_to_js(float value) {
  return JS_NewFloat64(ctx, (double)value);
}

static JSValue u64_to_js(uint64_t value) {
  // For values that fit in a regular number, use that
  if (value <= 0x1FFFFFFFFFFFFF) { // 2^53 - 1 (safe integer range)
    return JS_NewFloat64(ctx, (double)value);
  }
  // For larger values, use BigInt
  return JS_NewBigInt64(ctx, (int64_t)value);
}

static bool bool_from_js(JSValue val) {
  return JS_ToBool(ctx, val);
}

static int32_t i32_from_js(JSValue val) {
  int32_t result = 0;
  JS_ToInt32(ctx, &result, val);
  return result;
}

static uint32_t u32_from_js(JSValue val) {
  uint32_t result = 0;
  JS_ToUint32(ctx, &result, val);
  return result;
}

static float f32_from_js(JSValue val) {
  double result = 0.0;
  JS_ToFloat64(ctx, &result, val);
  return (float)result;
}

static uint64_t u64_from_js(JSValue val) {
  uint64_t result = 0;
  
  // Try to convert as regular number first (for small values)
  if (JS_IsNumber(val)) {
    double d;
    if (JS_ToFloat64(ctx, &d, val) == 0) {
      result = (uint64_t)d;
    }
  }
  // Handle BigInt values
  else if (JS_IsBigInt(val)) {
    // For BigInt, we need to use a different approach
    // Convert to string and parse, or use JS_ToBigInt64 if available
    int64_t signed_result = 0;
    if (JS_ToBigInt64(ctx, &signed_result, val) == 0) {
      result = (uint64_t)signed_result;
    }
  }
  
  return result;
}

static char* string_from_js(JSValue val) {
  return (char*)JS_ToCString(ctx, val);
}

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

static Vector* vector_array_from_js(JSValue vecArray, size_t* lenPointer) {
  // Check if the input is actually an array
  if (!JS_IsArray(vecArray)) {
    return NULL;
  }

  // Get the array length
  JSValue len_val = JS_GetPropertyStr(ctx, vecArray, "length");
  uint32_t len = 0;
  JS_ToUint32(ctx, &len, len_val);
  JS_FreeValue(ctx, len_val);

  if (len == 0) return NULL;

  *lenPointer = (size_t)len;

  // Allocate memory for the Vector array (caller must free)
  Vector *vecs = malloc(len * sizeof(Vector));
  if (!vecs) return NULL;

  // Convert each element
  for (uint32_t i = 0; i < len; i++) {
    JSValue val = JS_GetPropertyUint32(ctx, vecArray, i);
    
    if (JS_IsObject(val)) {
      JSValue x_val = JS_GetPropertyStr(ctx, val, "x");
      JSValue y_val = JS_GetPropertyStr(ctx, val, "y");
      
      JS_ToInt32(ctx, &vecs[i].x, x_val);
      JS_ToInt32(ctx, &vecs[i].y, y_val);
      
      JS_FreeValue(ctx, x_val);
      JS_FreeValue(ctx, y_val);
    } else {
      vecs[i].x = 0;
      vecs[i].y = 0;
    }
    
    JS_FreeValue(ctx, val);
  }

  return vecs;
}


__attribute__((unused)) static Dimensions dimensions_from_js(JSValue obj) {
  Dimensions dims = {0, 0}; // Default values

  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");

  JS_ToUint32(ctx, &dims.width, width_val);
  JS_ToUint32(ctx, &dims.height, height_val);

  JS_FreeValue(ctx, width_val);
  JS_FreeValue(ctx, height_val);
  return dims;
}

__attribute__((unused)) static Rectangle rectangle_from_js(JSValue obj) {
  Rectangle rect = {0, 0, 0, 0}; // Default values

  JSValue x_val = JS_GetPropertyStr(ctx, obj, "x");
  JSValue y_val = JS_GetPropertyStr(ctx, obj, "y");
  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");

  JS_ToInt32(ctx, &rect.x, x_val);
  JS_ToInt32(ctx, &rect.y, y_val);
  JS_ToInt32(ctx, &rect.width, width_val);
  JS_ToInt32(ctx, &rect.height, height_val);

  JS_FreeValue(ctx, x_val);
  JS_FreeValue(ctx, y_val);
  JS_FreeValue(ctx, width_val);
  JS_FreeValue(ctx, height_val);
  return rect;
}

static Color color_from_js(JSValue obj) {
  Color color = {0, 0, 0, 255}; // Default to opaque black
  
  JSValue r_val = JS_GetPropertyStr(ctx, obj, "r");
  JSValue g_val = JS_GetPropertyStr(ctx, obj, "g");
  JSValue b_val = JS_GetPropertyStr(ctx, obj, "b");
  JSValue a_val = JS_GetPropertyStr(ctx, obj, "a");
  
  uint32_t r, g, b, a;
  if (JS_ToUint32(ctx, &r, r_val) >= 0 && r <= 255) color.r = (uint8_t)r;
  if (JS_ToUint32(ctx, &g, g_val) >= 0 && g <= 255) color.g = (uint8_t)g;
  if (JS_ToUint32(ctx, &b, b_val) >= 0 && b <= 255) color.b = (uint8_t)b;
  if (JS_ToUint32(ctx, &a, a_val) >= 0 && a <= 255) color.a = (uint8_t)a;
  
  JS_FreeValue(ctx, r_val);
  JS_FreeValue(ctx, g_val);
  JS_FreeValue(ctx, b_val);
  JS_FreeValue(ctx, a_val);
  return color;
}

static SfxParams sfx_params_from_js(JSValue obj) {
  SfxParams params = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  JSValue randSeed_val = JS_GetPropertyStr(ctx, obj, "randSeed");
  JSValue waveType_val = JS_GetPropertyStr(ctx, obj, "waveType");
  JSValue attackTime_val = JS_GetPropertyStr(ctx, obj, "attackTime");
  JSValue sustainTime_val = JS_GetPropertyStr(ctx, obj, "sustainTime");
  JSValue sustainPunch_val = JS_GetPropertyStr(ctx, obj, "sustainPunch");
  JSValue decayTime_val = JS_GetPropertyStr(ctx, obj, "decayTime");
  JSValue startFrequency_val = JS_GetPropertyStr(ctx, obj, "startFrequency");
  JSValue minFrequency_val = JS_GetPropertyStr(ctx, obj, "minFrequency");
  JSValue slide_val = JS_GetPropertyStr(ctx, obj, "slide");
  JSValue deltaSlide_val = JS_GetPropertyStr(ctx, obj, "deltaSlide");
  JSValue vibratoDepth_val = JS_GetPropertyStr(ctx, obj, "vibratoDepth");
  JSValue vibratoSpeed_val = JS_GetPropertyStr(ctx, obj, "vibratoSpeed");
  JSValue changeAmount_val = JS_GetPropertyStr(ctx, obj, "changeAmount");
  JSValue changeSpeed_val = JS_GetPropertyStr(ctx, obj, "changeSpeed");
  JSValue squareDuty_val = JS_GetPropertyStr(ctx, obj, "squareDuty");
  JSValue dutySweep_val = JS_GetPropertyStr(ctx, obj, "dutySweep");
  JSValue repeatSpeed_val = JS_GetPropertyStr(ctx, obj, "repeatSpeed");
  JSValue phaserOffset_val = JS_GetPropertyStr(ctx, obj, "phaserOffset");
  JSValue phaserSweep_val = JS_GetPropertyStr(ctx, obj, "phaserSweep");
  JSValue lpfCutoff_val = JS_GetPropertyStr(ctx, obj, "lpfCutoff");
  JSValue lpfCutoffSweep_val = JS_GetPropertyStr(ctx, obj, "lpfCutoffSweep");
  JSValue lpfResonance_val = JS_GetPropertyStr(ctx, obj, "lpfResonance");
  JSValue hpfCutoff_val = JS_GetPropertyStr(ctx, obj, "hpfCutoff");
  JSValue hpfCutoffSweep_val = JS_GetPropertyStr(ctx, obj, "hpfCutoffSweep");

  JS_ToUint32(ctx, &params.randSeed, randSeed_val);
  JS_ToInt32(ctx, &params.waveType, waveType_val);
  JS_ToFloat64(ctx, (double*)&params.attackTime, attackTime_val);
  JS_ToFloat64(ctx, (double*)&params.sustainTime, sustainTime_val);
  JS_ToFloat64(ctx, (double*)&params.sustainPunch, sustainPunch_val);
  JS_ToFloat64(ctx, (double*)&params.decayTime, decayTime_val);
  JS_ToFloat64(ctx, (double*)&params.startFrequency, startFrequency_val);
  JS_ToFloat64(ctx, (double*)&params.minFrequency, minFrequency_val);
  JS_ToFloat64(ctx, (double*)&params.slide, slide_val);
  JS_ToFloat64(ctx, (double*)&params.deltaSlide, deltaSlide_val);
  JS_ToFloat64(ctx, (double*)&params.vibratoDepth, vibratoDepth_val);
  JS_ToFloat64(ctx, (double*)&params.vibratoSpeed, vibratoSpeed_val);
  JS_ToFloat64(ctx, (double*)&params.changeAmount, changeAmount_val);
  JS_ToFloat64(ctx, (double*)&params.changeSpeed, changeSpeed_val);
  JS_ToFloat64(ctx, (double*)&params.squareDuty, squareDuty_val);
  JS_ToFloat64(ctx, (double*)&params.dutySweep, dutySweep_val);
  JS_ToFloat64(ctx, (double*)&params.repeatSpeed, repeatSpeed_val);
  JS_ToFloat64(ctx, (double*)&params.phaserOffset, phaserOffset_val);
  JS_ToFloat64(ctx, (double*)&params.phaserSweep, phaserSweep_val);
  JS_ToFloat64(ctx, (double*)&params.lpfCutoff, lpfCutoff_val);
  JS_ToFloat64(ctx, (double*)&params.lpfCutoffSweep, lpfCutoffSweep_val);
  JS_ToFloat64(ctx, (double*)&params.lpfResonance, lpfResonance_val);
  JS_ToFloat64(ctx, (double*)&params.hpfCutoff, hpfCutoff_val);
  JS_ToFloat64(ctx, (double*)&params.hpfCutoffSweep, hpfCutoffSweep_val);

  JS_FreeValue(ctx, randSeed_val);
  JS_FreeValue(ctx, waveType_val);
  JS_FreeValue(ctx, attackTime_val);
  JS_FreeValue(ctx, sustainTime_val);
  JS_FreeValue(ctx, sustainPunch_val);
  JS_FreeValue(ctx, decayTime_val);
  JS_FreeValue(ctx, startFrequency_val);
  JS_FreeValue(ctx, minFrequency_val);
  JS_FreeValue(ctx, slide_val);
  JS_FreeValue(ctx, deltaSlide_val);
  JS_FreeValue(ctx, vibratoDepth_val);
  JS_FreeValue(ctx, vibratoSpeed_val);
  JS_FreeValue(ctx, changeAmount_val);
  JS_FreeValue(ctx, changeSpeed_val);
  JS_FreeValue(ctx, squareDuty_val);
  JS_FreeValue(ctx, dutySweep_val);
  JS_FreeValue(ctx, repeatSpeed_val);
  JS_FreeValue(ctx, phaserOffset_val);
  JS_FreeValue(ctx, phaserSweep_val);
  JS_FreeValue(ctx, lpfCutoff_val);
  JS_FreeValue(ctx, lpfCutoffSweep_val);
  JS_FreeValue(ctx, lpfResonance_val);
  JS_FreeValue(ctx, hpfCutoff_val);
  JS_FreeValue(ctx, hpfCutoffSweep_val);

  return params;
}

static JSValue sfx_params_to_js(SfxParams params) {
  JSValue obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, obj, "randSeed", JS_NewUint32(ctx, params.randSeed));
  JS_SetPropertyStr(ctx, obj, "waveType", JS_NewInt32(ctx, params.waveType));
  JS_SetPropertyStr(ctx, obj, "attackTime", JS_NewFloat64(ctx, params.attackTime));
  JS_SetPropertyStr(ctx, obj, "sustainTime", JS_NewFloat64(ctx, params.sustainTime));
  JS_SetPropertyStr(ctx, obj, "sustainPunch", JS_NewFloat64(ctx, params.sustainPunch));
  JS_SetPropertyStr(ctx, obj, "decayTime", JS_NewFloat64(ctx, params.decayTime));
  JS_SetPropertyStr(ctx, obj, "startFrequency", JS_NewFloat64(ctx, params.startFrequency));
  JS_SetPropertyStr(ctx, obj, "minFrequency", JS_NewFloat64(ctx, params.minFrequency));
  JS_SetPropertyStr(ctx, obj, "slide", JS_NewFloat64(ctx, params.slide));
  JS_SetPropertyStr(ctx, obj, "deltaSlide", JS_NewFloat64(ctx, params.deltaSlide));
  JS_SetPropertyStr(ctx, obj, "vibratoDepth", JS_NewFloat64(ctx, params.vibratoDepth));
  JS_SetPropertyStr(ctx, obj, "vibratoSpeed", JS_NewFloat64(ctx, params.vibratoSpeed));
  JS_SetPropertyStr(ctx, obj, "changeAmount", JS_NewFloat64(ctx, params.changeAmount));
  JS_SetPropertyStr(ctx, obj, "changeSpeed", JS_NewFloat64(ctx, params.changeSpeed));
  JS_SetPropertyStr(ctx, obj, "squareDuty", JS_NewFloat64(ctx, params.squareDuty));
  JS_SetPropertyStr(ctx, obj, "dutySweep", JS_NewFloat64(ctx, params.dutySweep));
  JS_SetPropertyStr(ctx, obj, "repeatSpeed", JS_NewFloat64(ctx, params.repeatSpeed));
  JS_SetPropertyStr(ctx, obj, "phaserOffset", JS_NewFloat64(ctx, params.phaserOffset));
  JS_SetPropertyStr(ctx, obj, "phaserSweep", JS_NewFloat64(ctx, params.phaserSweep));
  JS_SetPropertyStr(ctx, obj, "lpfCutoff", JS_NewFloat64(ctx, params.lpfCutoff));
  JS_SetPropertyStr(ctx, obj, "lpfCutoffSweep", JS_NewFloat64(ctx, params.lpfCutoffSweep));
  JS_SetPropertyStr(ctx, obj, "lpfResonance", JS_NewFloat64(ctx, params.lpfResonance));
  JS_SetPropertyStr(ctx, obj, "hpfCutoff", JS_NewFloat64(ctx, params.hpfCutoff));
  JS_SetPropertyStr(ctx, obj, "hpfCutoffSweep", JS_NewFloat64(ctx, params.hpfCutoffSweep));
  return obj;
}

// BINDINGS

`)

// functions to map return value into value that js-engine can handle
const returnMap = {
  // Wrapper functions for primitives
  bool: 'bool_to_js',
  i32: 'i32_to_js',
  f32: 'f32_to_js',
  u64: 'u64_to_js',

  // Resource references
  Sound: 'u32_to_js',
  Image: 'u32_to_js',
  Font: 'u32_to_js',

  // Custom struct converters
  Vector: 'vector_to_js',
  Dimensions: 'dimensions_to_js',
  Rectangle: 'rectangle_to_js',
  Color: 'color_to_js',
  SfxParams: 'sfx_params_to_js'
}

// these types are pointers when returned from C
const returnRef = ['Vector', 'Dimensions', 'Color', 'SfxParams']

// functions to map args from js into something C can handle
const argTypes = {
  // Wrapper functions for primitives
  bool: 'bool_from_js',
  i32: 'i32_from_js',
  f32: 'f32_from_js',
  u64: 'u64_from_js',
  string: 'string_from_js',

  // Resource references and enums
  Sound: 'u32_from_js',
  Image: 'u32_from_js',
  Font: 'u32_from_js',
  ImageFilter: 'i32_from_js',
  Key: 'i32_from_js',
  GamepadButton: 'i32_from_js',
  MouseButton: 'i32_from_js',
  SfxPresetType: 'i32_from_js',

  // Custom struct converters
  Color: 'color_from_js',
  'Vector[]': 'vector_array_from_js',
  SfxParams: 'sfx_params_from_js'
}

// TODO: I could build a lot of the above code with constants/enums/structs/scalars/callbacks

const funcs = []

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

for (const [apiName, apiObj] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    funcs.push(indent(`JS_SetPropertyStr(ctx, global, "${funcName}", JS_NewCFunction(ctx, js_${funcName}, "${funcName}", ${Object.keys(args).length}));`, 2))
    out.push(`// ${description}`)
    out.push(`static JSValue js_${funcName}(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {`)

    let hasArray = false

    let mappedArgs = Object.keys(args).map((name, id) => {
      const type = args[name]
      if (type.includes('[]')) {
        hasArray = id + 1
        return `${argTypes[type]}(argv[${id}], &outlen)`
      } else {
        return `${argTypes[type]}(argv[${hasArray ? id - 1 : id}])`
      }
    })

    if (hasArray) {
      out.push(indent(`size_t outlen = 0;`))
      mappedArgs = mappedArgs.filter((v, i) => i != hasArray)
      mappedArgs.splice(hasArray, 0, 'outlen')
    }

    if (returns === 'void') {
      out.push(indent(`${funcName}(${mappedArgs.join(', ')});\nreturn JS_UNDEFINED;`))
    } else {
      if (returnRef.includes(returns)) {
        out.push(indent(`${returns}* ret = ${funcName}(${mappedArgs.join(', ')});`))
        out.push(indent(`return ${returnMap[returns]}(*ret);`))
      } else {
        out.push(indent(`return ${returnMap[returns]}(${funcName}(${mappedArgs.join(', ')}));`))
      }
    }
    out.push('}')
  }
}

out.push('void expose_things_to_js() {')
add_colors()
out.push('')
add_consts()
out.push('', ...funcs, '}')

await writeFile('tools/docker/quickjs-cart.c', out.join('\n'))
