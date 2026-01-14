#include "null0.h"
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
      // printf("cart.%s() not defined\n", func_name);
    }
    JS_FreeValue(ctx, func);
  } else {
    printf("cart not defined when calling %s\n", func_name);
  }
  JS_FreeValue(ctx, cart);
}

int main(int argc, char* argv[]) {
  rt = JS_NewRuntime();
  ctx = JS_NewContext(rt);
  global = JS_GetGlobalObject(ctx);

  JS_SetMemoryLimit(rt, 0x4000000); // 64 Mb
  JS_SetMaxStackSize(rt, 0x10000); // 64 Kb
  JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
  js_std_add_helpers(ctx, 0, NULL);

  expose_things_to_js();

  // setup std/os globals/modules
  js_init_module_std(ctx, "std");
  js_init_module_os(ctx, "os");
  const char *str = "import * as std from 'std';\n"
    "import * as os from 'os';\n"
    "import * as cart from './main.js';\n"
    "globalThis.cart = cart;\n"
    "globalThis.std = std;\n"
    "globalThis.os = os;\n"
    "cart?.load && cart.load();\n";
  
  JSValue std_val = JS_Eval(ctx, str, strlen(str), "<CART>", JS_EVAL_TYPE_MODULE);
  std_val = js_std_await(ctx, std_val);
  
  if (!JS_IsException(std_val)) {
    js_module_set_import_meta(ctx, std_val, 1, 1);
    std_val = JS_EvalFunction(ctx, std_val);
  } else {
    js_std_dump_error(ctx);
  }

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
  else if (JS_IsBigInt(ctx, val)) {
    // For BigInt, we need to use a different approach
    // Convert to string and parse, or use JS_ToBigInt64 if available
    int64_t signed_result = 0;
    if (JS_ToBigInt64(ctx, &signed_result, val) == 0) {
      result = (uint64_t)signed_result;
    }
  }
  
  return result;
}

static const char* string_from_js(JSValue val) {
  return JS_ToCString(ctx, val);
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

static Vector* vector_array_from_js(JSValue vecArray, uint32_t* lenPointer) {
  // Check if the input is actually an array
  if (!JS_IsArray(ctx, vecArray)) {
    return NULL;
  }

  // Get the array length
  JSValue len_val = JS_GetPropertyStr(ctx, vecArray, "length");
  uint32_t len = 0;
  JS_ToUint32(ctx, &len, len_val);
  JS_FreeValue(ctx, len_val);

  if (len == 0) return NULL;

  *lenPointer = len;

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


static Dimensions dimensions_from_js(JSValue obj) {
  Dimensions dims = {0, 0}; // Default values
  
  JSValue width_val = JS_GetPropertyStr(ctx, obj, "width");
  JSValue height_val = JS_GetPropertyStr(ctx, obj, "height");
  
  JS_ToUint32(ctx, &dims.width, width_val);
  JS_ToUint32(ctx, &dims.height, height_val);
  
  JS_FreeValue(ctx, width_val);
  JS_FreeValue(ctx, height_val);
  return dims;
}

static Rectangle rectangle_from_js(JSValue obj) {
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



// COLORS

// Tint a color with another color.
static JSValue js_color_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Color* ret = color_tint(color_from_js(argv[0]), color_from_js(argv[1]));
 return color_to_js(*ret);
}
// Fade a color.
static JSValue js_color_fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Color* ret = color_fade(color_from_js(argv[0]), f32_from_js(argv[1]));
 return color_to_js(*ret);
}
// Change the brightness of a color.
static JSValue js_color_brightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Color* ret = color_brightness(color_from_js(argv[0]), f32_from_js(argv[1]));
 return color_to_js(*ret);
}
// Invert a color.
static JSValue js_color_invert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Color* ret = color_invert(color_from_js(argv[0]));
 return color_to_js(*ret);
}
// Blend 2 colors together.
static JSValue js_color_alpha_blend(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Color* ret = color_alpha_blend(color_from_js(argv[0]), color_from_js(argv[1]));
 return color_to_js(*ret);
}
// Change contrast of a color.
static JSValue js_color_contrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Color* ret = color_contrast(color_from_js(argv[0]), f32_from_js(argv[1]));
 return color_to_js(*ret);
}
// Interpolate colors.
static JSValue js_color_bilinear_interpolate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Color* ret = color_bilinear_interpolate(color_from_js(argv[0]), color_from_js(argv[1]), color_from_js(argv[2]), color_from_js(argv[3]), f32_from_js(argv[4]), f32_from_js(argv[5]));
 return color_to_js(*ret);
}

// GRAPHICS

// Create a new blank image.
static JSValue js_new_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(new_image(i32_from_js(argv[0]), i32_from_js(argv[1]), color_from_js(argv[2])));
}
// Copy an image to a new image.
static JSValue js_image_copy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(image_copy(u32_from_js(argv[0])));
}
// Create an image from a region of another image.
static JSValue js_image_subimage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(image_subimage(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4])));
}
// Clear the screen.
static JSValue js_clear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 clear(color_from_js(argv[0]));
 return JS_UNDEFINED;
}
// Draw a single pixel on the screen.
static JSValue js_draw_point(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_point(i32_from_js(argv[0]), i32_from_js(argv[1]), color_from_js(argv[2]));
 return JS_UNDEFINED;
}
// Draw a line on the screen.
static JSValue js_draw_line(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_line(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Draw a filled rectangle on the screen.
static JSValue js_draw_rectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Draw a filled triangle on the screen.
static JSValue js_draw_triangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw a filled ellipse on the screen.
static JSValue js_draw_ellipse(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Draw a filled circle on the screen.
static JSValue js_draw_circle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), color_from_js(argv[3]));
 return JS_UNDEFINED;
}
// Draw a filled polygon on the screen.
static JSValue js_draw_polygon(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 size_t outlen = 0;
 draw_polygon(vector_array_from_js(argv[0], &outlen), outlen, color_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Draw a filled arc on the screen.
static JSValue js_draw_arc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_arc(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw a filled round-rectangle on the screen.
static JSValue js_draw_rectangle_rounded(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw an image on the screen.
static JSValue js_draw_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]));
 return JS_UNDEFINED;
}
// Draw a tinted image on the screen.
static JSValue js_draw_image_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_tint(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), color_from_js(argv[3]));
 return JS_UNDEFINED;
}
// Draw an image, rotated, on the screen.
static JSValue js_draw_image_rotated(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_rotated(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), f32_from_js(argv[5]), i32_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw an image, flipped, on the screen.
static JSValue js_draw_image_flipped(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_flipped(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), bool_from_js(argv[3]), bool_from_js(argv[4]), bool_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw an image, scaled, on the screen.
static JSValue js_draw_image_scaled(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_scaled(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), f32_from_js(argv[5]), f32_from_js(argv[6]), i32_from_js(argv[7]));
 return JS_UNDEFINED;
}
// Draw some text on the screen.
static JSValue js_draw_text(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_text(u32_from_js(argv[0]), string_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Save an image to persistant storage.
static JSValue js_save_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 save_image(u32_from_js(argv[0]), string_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Load an image from a file in cart.
static JSValue js_load_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(load_image(string_from_js(argv[0])));
}
// Resize an image, return copy.
static JSValue js_image_resize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(image_resize(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3])));
}
// Scale an image, return copy.
static JSValue js_image_scale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(image_scale(u32_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), i32_from_js(argv[3])));
}
// Replace a color in an image, in-place.
static JSValue js_image_color_replace(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_replace(u32_from_js(argv[0]), color_from_js(argv[1]), color_from_js(argv[2]));
 return JS_UNDEFINED;
}
// Tint a color in an image, in-place.
static JSValue js_image_color_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_tint(u32_from_js(argv[0]), color_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Fade a color in an image, in-place.
static JSValue js_image_color_fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_fade(u32_from_js(argv[0]), f32_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Copy a font to a new font.
static JSValue js_font_copy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(font_copy(u32_from_js(argv[0])));
}
// Scale a font, return a new font.
static JSValue js_font_scale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(font_scale(u32_from_js(argv[0]), f32_from_js(argv[1]), f32_from_js(argv[2]), i32_from_js(argv[3])));
}
// Load a BMF font from a file in cart.
static JSValue js_load_font_bmf(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(load_font_bmf(string_from_js(argv[0]), string_from_js(argv[1])));
}
// Load a BMF font from an image.
static JSValue js_load_font_bmf_from_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(load_font_bmf_from_image(u32_from_js(argv[0]), string_from_js(argv[1])));
}
// Measure the size of some text.
static JSValue js_measure_text(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Dimensions* ret = measure_text(u32_from_js(argv[0]), string_from_js(argv[1]), i32_from_js(argv[2]));
 return dimensions_to_js(*ret);
}
// Meaure an image (use 0 for screen).
static JSValue js_measure_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Dimensions* ret = measure_image(u32_from_js(argv[0]));
 return dimensions_to_js(*ret);
}
// Load a TTY font from a file in cart.
static JSValue js_load_font_tty(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(load_font_tty(string_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), string_from_js(argv[3])));
}
// Load a TTY font from an image.
static JSValue js_load_font_tty_from_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(load_font_tty_from_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), string_from_js(argv[3])));
}
// Load a TTF font from a file in cart.
static JSValue js_load_font_ttf(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(load_font_ttf(string_from_js(argv[0]), i32_from_js(argv[1])));
}
// Invert the colors in an image, in-place.
static JSValue js_image_color_invert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_invert(u32_from_js(argv[0]));
 return JS_UNDEFINED;
}
// Calculate a rectangle representing the available alpha border in an image.
static JSValue js_image_alpha_border(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return rectangle_to_js(image_alpha_border(u32_from_js(argv[0]), f32_from_js(argv[1])));
}
// Crop an image, in-place.
static JSValue js_image_crop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_crop(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Crop an image based on the alpha border, in-place.
static JSValue js_image_alpha_crop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_alpha_crop(u32_from_js(argv[0]), f32_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Adjust the brightness of an image, in-place.
static JSValue js_image_color_brightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_brightness(u32_from_js(argv[0]), f32_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Flip an image, in-place.
static JSValue js_image_flip(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_flip(u32_from_js(argv[0]), bool_from_js(argv[1]), bool_from_js(argv[2]));
 return JS_UNDEFINED;
}
// Change the contrast of an image, in-place.
static JSValue js_image_color_contrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_contrast(u32_from_js(argv[0]), f32_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Use an image as an alpha-mask on another image.
static JSValue js_image_alpha_mask(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_alpha_mask(u32_from_js(argv[0]), u32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]));
 return JS_UNDEFINED;
}
// Create a new image, rotating another image.
static JSValue js_image_rotate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(image_rotate(u32_from_js(argv[0]), f32_from_js(argv[1]), i32_from_js(argv[2])));
}
// Create a new image of a gradient.
static JSValue js_image_gradient(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(image_gradient(i32_from_js(argv[0]), i32_from_js(argv[1]), color_from_js(argv[2]), color_from_js(argv[3]), color_from_js(argv[4]), color_from_js(argv[5])));
}
// Unload an image.
static JSValue js_unload_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 unload_image(u32_from_js(argv[0]));
 return JS_UNDEFINED;
}
// Unload a font.
static JSValue js_unload_font(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 unload_font(u32_from_js(argv[0]));
 return JS_UNDEFINED;
}
// Clear an image.
static JSValue js_clear_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 clear_image(u32_from_js(argv[0]), color_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Draw a single pixel on an image.
static JSValue js_draw_point_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_point_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), color_from_js(argv[3]));
 return JS_UNDEFINED;
}
// Draw a line on an image.
static JSValue js_draw_line_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_line_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw a filled rectangle on an image.
static JSValue js_draw_rectangle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw a filled triangle on an image.
static JSValue js_draw_triangle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), i32_from_js(argv[6]), color_from_js(argv[7]));
 return JS_UNDEFINED;
}
// Draw a filled ellipse on an image.
static JSValue js_draw_ellipse_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw a circle on an image.
static JSValue js_draw_circle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Draw a filled polygon on an image.
static JSValue js_draw_polygon_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 size_t outlen = 0;
 draw_polygon_on_image(u32_from_js(argv[0]), vector_array_from_js(argv[1], &outlen), outlen, color_from_js(argv[2]));
 return JS_UNDEFINED;
}
// Draw a filled round-rectangle on an image.
static JSValue js_draw_rectangle_rounded_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw an image on an image.
static JSValue js_draw_image_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_on_image(u32_from_js(argv[0]), u32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]));
 return JS_UNDEFINED;
}
// Draw a tinted image on an image.
static JSValue js_draw_image_tint_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_tint_on_image(u32_from_js(argv[0]), u32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Draw an image, rotated, on an image.
static JSValue js_draw_image_rotated_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_rotated_on_image(u32_from_js(argv[0]), u32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), f32_from_js(argv[4]), f32_from_js(argv[5]), f32_from_js(argv[6]), i32_from_js(argv[7]));
 return JS_UNDEFINED;
}
// Draw an image, flipped, on an image.
static JSValue js_draw_image_flipped_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_flipped_on_image(u32_from_js(argv[0]), u32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), bool_from_js(argv[4]), bool_from_js(argv[5]), bool_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw an image, scaled, on an image.
static JSValue js_draw_image_scaled_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_scaled_on_image(u32_from_js(argv[0]), u32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), f32_from_js(argv[4]), f32_from_js(argv[5]), f32_from_js(argv[6]), f32_from_js(argv[7]), i32_from_js(argv[8]));
 return JS_UNDEFINED;
}
// Draw some text on an image.
static JSValue js_draw_text_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_text_on_image(u32_from_js(argv[0]), u32_from_js(argv[1]), string_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) rectangle on the screen.
static JSValue js_draw_rectangle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_outline(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) triangle on the screen.
static JSValue js_draw_triangle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle_outline(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), i32_from_js(argv[6]), color_from_js(argv[7]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) ellipse on the screen.
static JSValue js_draw_ellipse_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse_outline(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) circle on the screen.
static JSValue js_draw_circle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle_outline(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), color_from_js(argv[4]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) polygon on the screen.
static JSValue js_draw_polygon_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 size_t outlen = 0;
 draw_polygon_outline(vector_array_from_js(argv[0], &outlen), outlen, i32_from_js(argv[1]), color_from_js(argv[2]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) arc on the screen.
static JSValue js_draw_arc_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_arc_outline(i32_from_js(argv[0]), i32_from_js(argv[1]), f32_from_js(argv[2]), f32_from_js(argv[3]), f32_from_js(argv[4]), i32_from_js(argv[5]), i32_from_js(argv[6]), color_from_js(argv[7]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) round-rectangle on the screen.
static JSValue js_draw_rectangle_rounded_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded_outline(i32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) rectangle on an image.
static JSValue js_draw_rectangle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_outline_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) triangle on an image.
static JSValue js_draw_triangle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle_outline_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), i32_from_js(argv[6]), i32_from_js(argv[7]), color_from_js(argv[8]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) ellipse on an image.
static JSValue js_draw_ellipse_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse_outline_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), color_from_js(argv[6]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) circle on an image.
static JSValue js_draw_circle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle_outline_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), color_from_js(argv[5]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) polygon on an image.
static JSValue js_draw_polygon_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 size_t outlen = 0;
 draw_polygon_outline_on_image(u32_from_js(argv[0]), vector_array_from_js(argv[1], &outlen), outlen, i32_from_js(argv[2]), color_from_js(argv[3]));
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) round-rectangle on an image.
static JSValue js_draw_rectangle_rounded_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded_outline_on_image(u32_from_js(argv[0]), i32_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), i32_from_js(argv[6]), color_from_js(argv[7]));
 return JS_UNDEFINED;
}

// INPUT

// Has the key been pressed? (tracks unpress/read correctly.)
static JSValue js_key_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(key_pressed(i32_from_js(argv[0])));
}
// Is the key currently down?
static JSValue js_key_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(key_down(i32_from_js(argv[0])));
}
// Has the key been released? (tracks press/read correctly.)
static JSValue js_key_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(key_released(i32_from_js(argv[0])));
}
// Is the key currently up?
static JSValue js_key_up(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(key_up(i32_from_js(argv[0])));
}
// Has the button been pressed? (tracks unpress/read correctly.)
static JSValue js_gamepad_button_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(gamepad_button_pressed(i32_from_js(argv[0]), i32_from_js(argv[1])));
}
// Is the button currently down?
static JSValue js_gamepad_button_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(gamepad_button_down(i32_from_js(argv[0]), i32_from_js(argv[1])));
}
// Has the button been released? (tracks press/read correctly.)
static JSValue js_gamepad_button_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(gamepad_button_released(i32_from_js(argv[0]), i32_from_js(argv[1])));
}
// Get current position of mouse.
static JSValue js_mouse_position(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 Vector* ret = mouse_position();
 return vector_to_js(*ret);
}
// Has the button been pressed? (tracks unpress/read correctly.)
static JSValue js_mouse_button_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(mouse_button_pressed(i32_from_js(argv[0])));
}
// Is the button currently down?
static JSValue js_mouse_button_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(mouse_button_down(i32_from_js(argv[0])));
}
// Has the button been released? (tracks press/read correctly.)
static JSValue js_mouse_button_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(mouse_button_released(i32_from_js(argv[0])));
}
// Is the button currently up?
static JSValue js_mouse_button_up(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return bool_to_js(mouse_button_up(i32_from_js(argv[0])));
}

// SOUND

// Load a sound from a file in cart.
static JSValue js_load_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(load_sound(string_from_js(argv[0])));
}
// Play a sound.
static JSValue js_play_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 play_sound(u32_from_js(argv[0]), bool_from_js(argv[1]));
 return JS_UNDEFINED;
}
// Stop a sound.
static JSValue js_stop_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 stop_sound(u32_from_js(argv[0]));
 return JS_UNDEFINED;
}
// Unload a sound.
static JSValue js_unload_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 unload_sound(u32_from_js(argv[0]));
 return JS_UNDEFINED;
}
// Speak some text and return a sound. Set things to 0 for defaults.
static JSValue js_tts_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(tts_sound(string_from_js(argv[0]), bool_from_js(argv[1]), i32_from_js(argv[2]), i32_from_js(argv[3]), i32_from_js(argv[4]), i32_from_js(argv[5]), bool_from_js(argv[6])));
}
// Create Sfx sound.
static JSValue js_sfx_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u32_to_js(sfx_sound(sfx_params_from_js(argv[0])));
}
// Create Sfx parameters.
static JSValue js_sfx_generate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 SfxParams* ret = sfx_generate(i32_from_js(argv[0]));
 return sfx_params_to_js(*ret);
}

// TYPES


// UTILITIES

// Get system-time (ms) since unix epoch.
static JSValue js_current_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u64_to_js(current_time());
}
// Get the change in time (seconds) since the last update run.
static JSValue js_delta_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return f32_to_js(delta_time());
}
// Get a random integer between 2 numbers.
static JSValue js_random_int(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return i32_to_js(random_int(i32_from_js(argv[0]), i32_from_js(argv[1])));
}
// Get the random-seed.
static JSValue js_random_seed_get(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return u64_to_js(random_seed_get());
}
// Set the random-seed.
static JSValue js_random_seed_set(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 random_seed_set(u64_from_js(argv[0]));
 return JS_UNDEFINED;
}
void expose_things_to_js() {
  JS_SetPropertyStr(ctx, global, "LIGHTGRAY", color_to_js(LIGHTGRAY));
  JS_SetPropertyStr(ctx, global, "GRAY", color_to_js(GRAY));
  JS_SetPropertyStr(ctx, global, "DARKGRAY", color_to_js(DARKGRAY));
  JS_SetPropertyStr(ctx, global, "YELLOW", color_to_js(YELLOW));
  JS_SetPropertyStr(ctx, global, "GOLD", color_to_js(GOLD));
  JS_SetPropertyStr(ctx, global, "ORANGE", color_to_js(ORANGE));
  JS_SetPropertyStr(ctx, global, "PINK", color_to_js(PINK));
  JS_SetPropertyStr(ctx, global, "RED", color_to_js(RED));
  JS_SetPropertyStr(ctx, global, "MAROON", color_to_js(MAROON));
  JS_SetPropertyStr(ctx, global, "GREEN", color_to_js(GREEN));
  JS_SetPropertyStr(ctx, global, "LIME", color_to_js(LIME));
  JS_SetPropertyStr(ctx, global, "DARKGREEN", color_to_js(DARKGREEN));
  JS_SetPropertyStr(ctx, global, "SKYBLUE", color_to_js(SKYBLUE));
  JS_SetPropertyStr(ctx, global, "BLUE", color_to_js(BLUE));
  JS_SetPropertyStr(ctx, global, "DARKBLUE", color_to_js(DARKBLUE));
  JS_SetPropertyStr(ctx, global, "PURPLE", color_to_js(PURPLE));
  JS_SetPropertyStr(ctx, global, "VIOLET", color_to_js(VIOLET));
  JS_SetPropertyStr(ctx, global, "DARKPURPLE", color_to_js(DARKPURPLE));
  JS_SetPropertyStr(ctx, global, "BEIGE", color_to_js(BEIGE));
  JS_SetPropertyStr(ctx, global, "BROWN", color_to_js(BROWN));
  JS_SetPropertyStr(ctx, global, "DARKBROWN", color_to_js(DARKBROWN));
  JS_SetPropertyStr(ctx, global, "WHITE", color_to_js(WHITE));
  JS_SetPropertyStr(ctx, global, "BLACK", color_to_js(BLACK));
  JS_SetPropertyStr(ctx, global, "BLANK", color_to_js(BLANK));
  JS_SetPropertyStr(ctx, global, "MAGENTA", color_to_js(MAGENTA));
  JS_SetPropertyStr(ctx, global, "RAYWHITE", color_to_js(RAYWHITE));

  JS_SetPropertyStr(ctx, global, "FILTER_NEARESTNEIGHBOR", JS_NewInt32(ctx, FILTER_NEARESTNEIGHBOR));
  JS_SetPropertyStr(ctx, global, "FILTER_BILINEAR", JS_NewInt32(ctx, FILTER_BILINEAR));
  JS_SetPropertyStr(ctx, global, "FILTER_SMOOTH", JS_NewInt32(ctx, FILTER_SMOOTH));
  JS_SetPropertyStr(ctx, global, "KEY_INVALID", JS_NewInt32(ctx, KEY_INVALID));
  JS_SetPropertyStr(ctx, global, "KEY_SPACE", JS_NewInt32(ctx, KEY_SPACE));
  JS_SetPropertyStr(ctx, global, "KEY_APOSTROPHE", JS_NewInt32(ctx, KEY_APOSTROPHE));
  JS_SetPropertyStr(ctx, global, "KEY_COMMA", JS_NewInt32(ctx, KEY_COMMA));
  JS_SetPropertyStr(ctx, global, "KEY_MINUS", JS_NewInt32(ctx, KEY_MINUS));
  JS_SetPropertyStr(ctx, global, "KEY_PERIOD", JS_NewInt32(ctx, KEY_PERIOD));
  JS_SetPropertyStr(ctx, global, "KEY_SLASH", JS_NewInt32(ctx, KEY_SLASH));
  JS_SetPropertyStr(ctx, global, "KEY_0", JS_NewInt32(ctx, KEY_0));
  JS_SetPropertyStr(ctx, global, "KEY_1", JS_NewInt32(ctx, KEY_1));
  JS_SetPropertyStr(ctx, global, "KEY_2", JS_NewInt32(ctx, KEY_2));
  JS_SetPropertyStr(ctx, global, "KEY_3", JS_NewInt32(ctx, KEY_3));
  JS_SetPropertyStr(ctx, global, "KEY_4", JS_NewInt32(ctx, KEY_4));
  JS_SetPropertyStr(ctx, global, "KEY_5", JS_NewInt32(ctx, KEY_5));
  JS_SetPropertyStr(ctx, global, "KEY_6", JS_NewInt32(ctx, KEY_6));
  JS_SetPropertyStr(ctx, global, "KEY_7", JS_NewInt32(ctx, KEY_7));
  JS_SetPropertyStr(ctx, global, "KEY_8", JS_NewInt32(ctx, KEY_8));
  JS_SetPropertyStr(ctx, global, "KEY_9", JS_NewInt32(ctx, KEY_9));
  JS_SetPropertyStr(ctx, global, "KEY_SEMICOLON", JS_NewInt32(ctx, KEY_SEMICOLON));
  JS_SetPropertyStr(ctx, global, "KEY_EQUAL", JS_NewInt32(ctx, KEY_EQUAL));
  JS_SetPropertyStr(ctx, global, "KEY_A", JS_NewInt32(ctx, KEY_A));
  JS_SetPropertyStr(ctx, global, "KEY_B", JS_NewInt32(ctx, KEY_B));
  JS_SetPropertyStr(ctx, global, "KEY_C", JS_NewInt32(ctx, KEY_C));
  JS_SetPropertyStr(ctx, global, "KEY_D", JS_NewInt32(ctx, KEY_D));
  JS_SetPropertyStr(ctx, global, "KEY_E", JS_NewInt32(ctx, KEY_E));
  JS_SetPropertyStr(ctx, global, "KEY_F", JS_NewInt32(ctx, KEY_F));
  JS_SetPropertyStr(ctx, global, "KEY_G", JS_NewInt32(ctx, KEY_G));
  JS_SetPropertyStr(ctx, global, "KEY_H", JS_NewInt32(ctx, KEY_H));
  JS_SetPropertyStr(ctx, global, "KEY_I", JS_NewInt32(ctx, KEY_I));
  JS_SetPropertyStr(ctx, global, "KEY_J", JS_NewInt32(ctx, KEY_J));
  JS_SetPropertyStr(ctx, global, "KEY_K", JS_NewInt32(ctx, KEY_K));
  JS_SetPropertyStr(ctx, global, "KEY_L", JS_NewInt32(ctx, KEY_L));
  JS_SetPropertyStr(ctx, global, "KEY_M", JS_NewInt32(ctx, KEY_M));
  JS_SetPropertyStr(ctx, global, "KEY_N", JS_NewInt32(ctx, KEY_N));
  JS_SetPropertyStr(ctx, global, "KEY_O", JS_NewInt32(ctx, KEY_O));
  JS_SetPropertyStr(ctx, global, "KEY_P", JS_NewInt32(ctx, KEY_P));
  JS_SetPropertyStr(ctx, global, "KEY_Q", JS_NewInt32(ctx, KEY_Q));
  JS_SetPropertyStr(ctx, global, "KEY_R", JS_NewInt32(ctx, KEY_R));
  JS_SetPropertyStr(ctx, global, "KEY_S", JS_NewInt32(ctx, KEY_S));
  JS_SetPropertyStr(ctx, global, "KEY_T", JS_NewInt32(ctx, KEY_T));
  JS_SetPropertyStr(ctx, global, "KEY_U", JS_NewInt32(ctx, KEY_U));
  JS_SetPropertyStr(ctx, global, "KEY_V", JS_NewInt32(ctx, KEY_V));
  JS_SetPropertyStr(ctx, global, "KEY_W", JS_NewInt32(ctx, KEY_W));
  JS_SetPropertyStr(ctx, global, "KEY_X", JS_NewInt32(ctx, KEY_X));
  JS_SetPropertyStr(ctx, global, "KEY_Y", JS_NewInt32(ctx, KEY_Y));
  JS_SetPropertyStr(ctx, global, "KEY_Z", JS_NewInt32(ctx, KEY_Z));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_BRACKET", JS_NewInt32(ctx, KEY_LEFT_BRACKET));
  JS_SetPropertyStr(ctx, global, "KEY_BACKSLASH", JS_NewInt32(ctx, KEY_BACKSLASH));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_BRACKET", JS_NewInt32(ctx, KEY_RIGHT_BRACKET));
  JS_SetPropertyStr(ctx, global, "KEY_GRAVE_ACCENT", JS_NewInt32(ctx, KEY_GRAVE_ACCENT));
  JS_SetPropertyStr(ctx, global, "KEY_WORLD_1", JS_NewInt32(ctx, KEY_WORLD_1));
  JS_SetPropertyStr(ctx, global, "KEY_WORLD_2", JS_NewInt32(ctx, KEY_WORLD_2));
  JS_SetPropertyStr(ctx, global, "KEY_ESCAPE", JS_NewInt32(ctx, KEY_ESCAPE));
  JS_SetPropertyStr(ctx, global, "KEY_ENTER", JS_NewInt32(ctx, KEY_ENTER));
  JS_SetPropertyStr(ctx, global, "KEY_TAB", JS_NewInt32(ctx, KEY_TAB));
  JS_SetPropertyStr(ctx, global, "KEY_BACKSPACE", JS_NewInt32(ctx, KEY_BACKSPACE));
  JS_SetPropertyStr(ctx, global, "KEY_INSERT", JS_NewInt32(ctx, KEY_INSERT));
  JS_SetPropertyStr(ctx, global, "KEY_DELETE", JS_NewInt32(ctx, KEY_DELETE));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT", JS_NewInt32(ctx, KEY_RIGHT));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT", JS_NewInt32(ctx, KEY_LEFT));
  JS_SetPropertyStr(ctx, global, "KEY_DOWN", JS_NewInt32(ctx, KEY_DOWN));
  JS_SetPropertyStr(ctx, global, "KEY_UP", JS_NewInt32(ctx, KEY_UP));
  JS_SetPropertyStr(ctx, global, "KEY_PAGE_UP", JS_NewInt32(ctx, KEY_PAGE_UP));
  JS_SetPropertyStr(ctx, global, "KEY_PAGE_DOWN", JS_NewInt32(ctx, KEY_PAGE_DOWN));
  JS_SetPropertyStr(ctx, global, "KEY_HOME", JS_NewInt32(ctx, KEY_HOME));
  JS_SetPropertyStr(ctx, global, "KEY_END", JS_NewInt32(ctx, KEY_END));
  JS_SetPropertyStr(ctx, global, "KEY_CAPS_LOCK", JS_NewInt32(ctx, KEY_CAPS_LOCK));
  JS_SetPropertyStr(ctx, global, "KEY_SCROLL_LOCK", JS_NewInt32(ctx, KEY_SCROLL_LOCK));
  JS_SetPropertyStr(ctx, global, "KEY_NUM_LOCK", JS_NewInt32(ctx, KEY_NUM_LOCK));
  JS_SetPropertyStr(ctx, global, "KEY_PRINT_SCREEN", JS_NewInt32(ctx, KEY_PRINT_SCREEN));
  JS_SetPropertyStr(ctx, global, "KEY_PAUSE", JS_NewInt32(ctx, KEY_PAUSE));
  JS_SetPropertyStr(ctx, global, "KEY_F1", JS_NewInt32(ctx, KEY_F1));
  JS_SetPropertyStr(ctx, global, "KEY_F2", JS_NewInt32(ctx, KEY_F2));
  JS_SetPropertyStr(ctx, global, "KEY_F3", JS_NewInt32(ctx, KEY_F3));
  JS_SetPropertyStr(ctx, global, "KEY_F4", JS_NewInt32(ctx, KEY_F4));
  JS_SetPropertyStr(ctx, global, "KEY_F5", JS_NewInt32(ctx, KEY_F5));
  JS_SetPropertyStr(ctx, global, "KEY_F6", JS_NewInt32(ctx, KEY_F6));
  JS_SetPropertyStr(ctx, global, "KEY_F7", JS_NewInt32(ctx, KEY_F7));
  JS_SetPropertyStr(ctx, global, "KEY_F8", JS_NewInt32(ctx, KEY_F8));
  JS_SetPropertyStr(ctx, global, "KEY_F9", JS_NewInt32(ctx, KEY_F9));
  JS_SetPropertyStr(ctx, global, "KEY_F10", JS_NewInt32(ctx, KEY_F10));
  JS_SetPropertyStr(ctx, global, "KEY_F11", JS_NewInt32(ctx, KEY_F11));
  JS_SetPropertyStr(ctx, global, "KEY_F12", JS_NewInt32(ctx, KEY_F12));
  JS_SetPropertyStr(ctx, global, "KEY_F13", JS_NewInt32(ctx, KEY_F13));
  JS_SetPropertyStr(ctx, global, "KEY_F14", JS_NewInt32(ctx, KEY_F14));
  JS_SetPropertyStr(ctx, global, "KEY_F15", JS_NewInt32(ctx, KEY_F15));
  JS_SetPropertyStr(ctx, global, "KEY_F16", JS_NewInt32(ctx, KEY_F16));
  JS_SetPropertyStr(ctx, global, "KEY_F17", JS_NewInt32(ctx, KEY_F17));
  JS_SetPropertyStr(ctx, global, "KEY_F18", JS_NewInt32(ctx, KEY_F18));
  JS_SetPropertyStr(ctx, global, "KEY_F19", JS_NewInt32(ctx, KEY_F19));
  JS_SetPropertyStr(ctx, global, "KEY_F20", JS_NewInt32(ctx, KEY_F20));
  JS_SetPropertyStr(ctx, global, "KEY_F21", JS_NewInt32(ctx, KEY_F21));
  JS_SetPropertyStr(ctx, global, "KEY_F22", JS_NewInt32(ctx, KEY_F22));
  JS_SetPropertyStr(ctx, global, "KEY_F23", JS_NewInt32(ctx, KEY_F23));
  JS_SetPropertyStr(ctx, global, "KEY_F24", JS_NewInt32(ctx, KEY_F24));
  JS_SetPropertyStr(ctx, global, "KEY_F25", JS_NewInt32(ctx, KEY_F25));
  JS_SetPropertyStr(ctx, global, "KEY_KP_0", JS_NewInt32(ctx, KEY_KP_0));
  JS_SetPropertyStr(ctx, global, "KEY_KP_1", JS_NewInt32(ctx, KEY_KP_1));
  JS_SetPropertyStr(ctx, global, "KEY_KP_2", JS_NewInt32(ctx, KEY_KP_2));
  JS_SetPropertyStr(ctx, global, "KEY_KP_3", JS_NewInt32(ctx, KEY_KP_3));
  JS_SetPropertyStr(ctx, global, "KEY_KP_4", JS_NewInt32(ctx, KEY_KP_4));
  JS_SetPropertyStr(ctx, global, "KEY_KP_5", JS_NewInt32(ctx, KEY_KP_5));
  JS_SetPropertyStr(ctx, global, "KEY_KP_6", JS_NewInt32(ctx, KEY_KP_6));
  JS_SetPropertyStr(ctx, global, "KEY_KP_7", JS_NewInt32(ctx, KEY_KP_7));
  JS_SetPropertyStr(ctx, global, "KEY_KP_8", JS_NewInt32(ctx, KEY_KP_8));
  JS_SetPropertyStr(ctx, global, "KEY_KP_9", JS_NewInt32(ctx, KEY_KP_9));
  JS_SetPropertyStr(ctx, global, "KEY_KP_DECIMAL", JS_NewInt32(ctx, KEY_KP_DECIMAL));
  JS_SetPropertyStr(ctx, global, "KEY_KP_DIVIDE", JS_NewInt32(ctx, KEY_KP_DIVIDE));
  JS_SetPropertyStr(ctx, global, "KEY_KP_MULTIPLY", JS_NewInt32(ctx, KEY_KP_MULTIPLY));
  JS_SetPropertyStr(ctx, global, "KEY_KP_SUBTRACT", JS_NewInt32(ctx, KEY_KP_SUBTRACT));
  JS_SetPropertyStr(ctx, global, "KEY_KP_ADD", JS_NewInt32(ctx, KEY_KP_ADD));
  JS_SetPropertyStr(ctx, global, "KEY_KP_ENTER", JS_NewInt32(ctx, KEY_KP_ENTER));
  JS_SetPropertyStr(ctx, global, "KEY_KP_EQUAL", JS_NewInt32(ctx, KEY_KP_EQUAL));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_SHIFT", JS_NewInt32(ctx, KEY_LEFT_SHIFT));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_CONTROL", JS_NewInt32(ctx, KEY_LEFT_CONTROL));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_ALT", JS_NewInt32(ctx, KEY_LEFT_ALT));
  JS_SetPropertyStr(ctx, global, "KEY_LEFT_SUPER", JS_NewInt32(ctx, KEY_LEFT_SUPER));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_SHIFT", JS_NewInt32(ctx, KEY_RIGHT_SHIFT));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_CONTROL", JS_NewInt32(ctx, KEY_RIGHT_CONTROL));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_ALT", JS_NewInt32(ctx, KEY_RIGHT_ALT));
  JS_SetPropertyStr(ctx, global, "KEY_RIGHT_SUPER", JS_NewInt32(ctx, KEY_RIGHT_SUPER));
  JS_SetPropertyStr(ctx, global, "KEY_MENU", JS_NewInt32(ctx, KEY_MENU));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_UNKNOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_UNKNOWN));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_UP", JS_NewInt32(ctx, GAMEPAD_BUTTON_UP));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_DOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_DOWN));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_Y", JS_NewInt32(ctx, GAMEPAD_BUTTON_Y));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_B", JS_NewInt32(ctx, GAMEPAD_BUTTON_B));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_A", JS_NewInt32(ctx, GAMEPAD_BUTTON_A));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_X", JS_NewInt32(ctx, GAMEPAD_BUTTON_X));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_SHOULDER", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_SHOULDER));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_TRIGGER", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_TRIGGER));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_SHOULDER", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_SHOULDER));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_TRIGGER", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_TRIGGER));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_SELECT", JS_NewInt32(ctx, GAMEPAD_BUTTON_SELECT));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_MENU", JS_NewInt32(ctx, GAMEPAD_BUTTON_MENU));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_START", JS_NewInt32(ctx, GAMEPAD_BUTTON_START));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_LEFT_THUMB", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_THUMB));
  JS_SetPropertyStr(ctx, global, "GAMEPAD_BUTTON_RIGHT_THUMB", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_THUMB));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_UNKNOWN", JS_NewInt32(ctx, MOUSE_BUTTON_UNKNOWN));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_LEFT", JS_NewInt32(ctx, MOUSE_BUTTON_LEFT));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_RIGHT", JS_NewInt32(ctx, MOUSE_BUTTON_RIGHT));
  JS_SetPropertyStr(ctx, global, "MOUSE_BUTTON_MIDDLE", JS_NewInt32(ctx, MOUSE_BUTTON_MIDDLE));
  JS_SetPropertyStr(ctx, global, "SCREEN", JS_NewInt32(ctx, SCREEN));
  JS_SetPropertyStr(ctx, global, "SCREEN_WIDTH", JS_NewInt32(ctx, SCREEN_WIDTH));
  JS_SetPropertyStr(ctx, global, "SCREEN_HEIGHT", JS_NewInt32(ctx, SCREEN_HEIGHT));
  JS_SetPropertyStr(ctx, global, "FONT_DEFAULT", JS_NewInt32(ctx, FONT_DEFAULT));
  JS_SetPropertyStr(ctx, global, "SFX_COIN", JS_NewInt32(ctx, SFX_COIN));
  JS_SetPropertyStr(ctx, global, "SFX_LASER", JS_NewInt32(ctx, SFX_LASER));
  JS_SetPropertyStr(ctx, global, "SFX_EXPLOSION", JS_NewInt32(ctx, SFX_EXPLOSION));
  JS_SetPropertyStr(ctx, global, "SFX_POWERUP", JS_NewInt32(ctx, SFX_POWERUP));
  JS_SetPropertyStr(ctx, global, "SFX_HURT", JS_NewInt32(ctx, SFX_HURT));
  JS_SetPropertyStr(ctx, global, "SFX_JUMP", JS_NewInt32(ctx, SFX_JUMP));
  JS_SetPropertyStr(ctx, global, "SFX_SELECT", JS_NewInt32(ctx, SFX_SELECT));
  JS_SetPropertyStr(ctx, global, "SFX_SYNTH", JS_NewInt32(ctx, SFX_SYNTH));

  JS_SetPropertyStr(ctx, global, "color_tint", JS_NewCFunction(ctx, js_color_tint, "color_tint", 2));
  JS_SetPropertyStr(ctx, global, "color_fade", JS_NewCFunction(ctx, js_color_fade, "color_fade", 2));
  JS_SetPropertyStr(ctx, global, "color_brightness", JS_NewCFunction(ctx, js_color_brightness, "color_brightness", 2));
  JS_SetPropertyStr(ctx, global, "color_invert", JS_NewCFunction(ctx, js_color_invert, "color_invert", 1));
  JS_SetPropertyStr(ctx, global, "color_alpha_blend", JS_NewCFunction(ctx, js_color_alpha_blend, "color_alpha_blend", 2));
  JS_SetPropertyStr(ctx, global, "color_contrast", JS_NewCFunction(ctx, js_color_contrast, "color_contrast", 2));
  JS_SetPropertyStr(ctx, global, "color_bilinear_interpolate", JS_NewCFunction(ctx, js_color_bilinear_interpolate, "color_bilinear_interpolate", 6));
  JS_SetPropertyStr(ctx, global, "new_image", JS_NewCFunction(ctx, js_new_image, "new_image", 3));
  JS_SetPropertyStr(ctx, global, "image_copy", JS_NewCFunction(ctx, js_image_copy, "image_copy", 1));
  JS_SetPropertyStr(ctx, global, "image_subimage", JS_NewCFunction(ctx, js_image_subimage, "image_subimage", 5));
  JS_SetPropertyStr(ctx, global, "clear", JS_NewCFunction(ctx, js_clear, "clear", 1));
  JS_SetPropertyStr(ctx, global, "draw_point", JS_NewCFunction(ctx, js_draw_point, "draw_point", 3));
  JS_SetPropertyStr(ctx, global, "draw_line", JS_NewCFunction(ctx, js_draw_line, "draw_line", 5));
  JS_SetPropertyStr(ctx, global, "draw_rectangle", JS_NewCFunction(ctx, js_draw_rectangle, "draw_rectangle", 5));
  JS_SetPropertyStr(ctx, global, "draw_triangle", JS_NewCFunction(ctx, js_draw_triangle, "draw_triangle", 7));
  JS_SetPropertyStr(ctx, global, "draw_ellipse", JS_NewCFunction(ctx, js_draw_ellipse, "draw_ellipse", 5));
  JS_SetPropertyStr(ctx, global, "draw_circle", JS_NewCFunction(ctx, js_draw_circle, "draw_circle", 4));
  JS_SetPropertyStr(ctx, global, "draw_polygon", JS_NewCFunction(ctx, js_draw_polygon, "draw_polygon", 3));
  JS_SetPropertyStr(ctx, global, "draw_arc", JS_NewCFunction(ctx, js_draw_arc, "draw_arc", 7));
  JS_SetPropertyStr(ctx, global, "draw_rectangle_rounded", JS_NewCFunction(ctx, js_draw_rectangle_rounded, "draw_rectangle_rounded", 6));
  JS_SetPropertyStr(ctx, global, "draw_image", JS_NewCFunction(ctx, js_draw_image, "draw_image", 3));
  JS_SetPropertyStr(ctx, global, "draw_image_tint", JS_NewCFunction(ctx, js_draw_image_tint, "draw_image_tint", 4));
  JS_SetPropertyStr(ctx, global, "draw_image_rotated", JS_NewCFunction(ctx, js_draw_image_rotated, "draw_image_rotated", 7));
  JS_SetPropertyStr(ctx, global, "draw_image_flipped", JS_NewCFunction(ctx, js_draw_image_flipped, "draw_image_flipped", 6));
  JS_SetPropertyStr(ctx, global, "draw_image_scaled", JS_NewCFunction(ctx, js_draw_image_scaled, "draw_image_scaled", 8));
  JS_SetPropertyStr(ctx, global, "draw_text", JS_NewCFunction(ctx, js_draw_text, "draw_text", 5));
  JS_SetPropertyStr(ctx, global, "save_image", JS_NewCFunction(ctx, js_save_image, "save_image", 2));
  JS_SetPropertyStr(ctx, global, "load_image", JS_NewCFunction(ctx, js_load_image, "load_image", 1));
  JS_SetPropertyStr(ctx, global, "image_resize", JS_NewCFunction(ctx, js_image_resize, "image_resize", 4));
  JS_SetPropertyStr(ctx, global, "image_scale", JS_NewCFunction(ctx, js_image_scale, "image_scale", 4));
  JS_SetPropertyStr(ctx, global, "image_color_replace", JS_NewCFunction(ctx, js_image_color_replace, "image_color_replace", 3));
  JS_SetPropertyStr(ctx, global, "image_color_tint", JS_NewCFunction(ctx, js_image_color_tint, "image_color_tint", 2));
  JS_SetPropertyStr(ctx, global, "image_color_fade", JS_NewCFunction(ctx, js_image_color_fade, "image_color_fade", 2));
  JS_SetPropertyStr(ctx, global, "font_copy", JS_NewCFunction(ctx, js_font_copy, "font_copy", 1));
  JS_SetPropertyStr(ctx, global, "font_scale", JS_NewCFunction(ctx, js_font_scale, "font_scale", 4));
  JS_SetPropertyStr(ctx, global, "load_font_bmf", JS_NewCFunction(ctx, js_load_font_bmf, "load_font_bmf", 2));
  JS_SetPropertyStr(ctx, global, "load_font_bmf_from_image", JS_NewCFunction(ctx, js_load_font_bmf_from_image, "load_font_bmf_from_image", 2));
  JS_SetPropertyStr(ctx, global, "measure_text", JS_NewCFunction(ctx, js_measure_text, "measure_text", 3));
  JS_SetPropertyStr(ctx, global, "measure_image", JS_NewCFunction(ctx, js_measure_image, "measure_image", 1));
  JS_SetPropertyStr(ctx, global, "load_font_tty", JS_NewCFunction(ctx, js_load_font_tty, "load_font_tty", 4));
  JS_SetPropertyStr(ctx, global, "load_font_tty_from_image", JS_NewCFunction(ctx, js_load_font_tty_from_image, "load_font_tty_from_image", 4));
  JS_SetPropertyStr(ctx, global, "load_font_ttf", JS_NewCFunction(ctx, js_load_font_ttf, "load_font_ttf", 2));
  JS_SetPropertyStr(ctx, global, "image_color_invert", JS_NewCFunction(ctx, js_image_color_invert, "image_color_invert", 1));
  JS_SetPropertyStr(ctx, global, "image_alpha_border", JS_NewCFunction(ctx, js_image_alpha_border, "image_alpha_border", 2));
  JS_SetPropertyStr(ctx, global, "image_crop", JS_NewCFunction(ctx, js_image_crop, "image_crop", 5));
  JS_SetPropertyStr(ctx, global, "image_alpha_crop", JS_NewCFunction(ctx, js_image_alpha_crop, "image_alpha_crop", 2));
  JS_SetPropertyStr(ctx, global, "image_color_brightness", JS_NewCFunction(ctx, js_image_color_brightness, "image_color_brightness", 2));
  JS_SetPropertyStr(ctx, global, "image_flip", JS_NewCFunction(ctx, js_image_flip, "image_flip", 3));
  JS_SetPropertyStr(ctx, global, "image_color_contrast", JS_NewCFunction(ctx, js_image_color_contrast, "image_color_contrast", 2));
  JS_SetPropertyStr(ctx, global, "image_alpha_mask", JS_NewCFunction(ctx, js_image_alpha_mask, "image_alpha_mask", 4));
  JS_SetPropertyStr(ctx, global, "image_rotate", JS_NewCFunction(ctx, js_image_rotate, "image_rotate", 3));
  JS_SetPropertyStr(ctx, global, "image_gradient", JS_NewCFunction(ctx, js_image_gradient, "image_gradient", 6));
  JS_SetPropertyStr(ctx, global, "unload_image", JS_NewCFunction(ctx, js_unload_image, "unload_image", 1));
  JS_SetPropertyStr(ctx, global, "unload_font", JS_NewCFunction(ctx, js_unload_font, "unload_font", 1));
  JS_SetPropertyStr(ctx, global, "clear_image", JS_NewCFunction(ctx, js_clear_image, "clear_image", 2));
  JS_SetPropertyStr(ctx, global, "draw_point_on_image", JS_NewCFunction(ctx, js_draw_point_on_image, "draw_point_on_image", 4));
  JS_SetPropertyStr(ctx, global, "draw_line_on_image", JS_NewCFunction(ctx, js_draw_line_on_image, "draw_line_on_image", 6));
  JS_SetPropertyStr(ctx, global, "draw_rectangle_on_image", JS_NewCFunction(ctx, js_draw_rectangle_on_image, "draw_rectangle_on_image", 6));
  JS_SetPropertyStr(ctx, global, "draw_triangle_on_image", JS_NewCFunction(ctx, js_draw_triangle_on_image, "draw_triangle_on_image", 8));
  JS_SetPropertyStr(ctx, global, "draw_ellipse_on_image", JS_NewCFunction(ctx, js_draw_ellipse_on_image, "draw_ellipse_on_image", 6));
  JS_SetPropertyStr(ctx, global, "draw_circle_on_image", JS_NewCFunction(ctx, js_draw_circle_on_image, "draw_circle_on_image", 5));
  JS_SetPropertyStr(ctx, global, "draw_polygon_on_image", JS_NewCFunction(ctx, js_draw_polygon_on_image, "draw_polygon_on_image", 4));
  JS_SetPropertyStr(ctx, global, "draw_rectangle_rounded_on_image", JS_NewCFunction(ctx, js_draw_rectangle_rounded_on_image, "draw_rectangle_rounded_on_image", 7));
  JS_SetPropertyStr(ctx, global, "draw_image_on_image", JS_NewCFunction(ctx, js_draw_image_on_image, "draw_image_on_image", 4));
  JS_SetPropertyStr(ctx, global, "draw_image_tint_on_image", JS_NewCFunction(ctx, js_draw_image_tint_on_image, "draw_image_tint_on_image", 5));
  JS_SetPropertyStr(ctx, global, "draw_image_rotated_on_image", JS_NewCFunction(ctx, js_draw_image_rotated_on_image, "draw_image_rotated_on_image", 8));
  JS_SetPropertyStr(ctx, global, "draw_image_flipped_on_image", JS_NewCFunction(ctx, js_draw_image_flipped_on_image, "draw_image_flipped_on_image", 7));
  JS_SetPropertyStr(ctx, global, "draw_image_scaled_on_image", JS_NewCFunction(ctx, js_draw_image_scaled_on_image, "draw_image_scaled_on_image", 9));
  JS_SetPropertyStr(ctx, global, "draw_text_on_image", JS_NewCFunction(ctx, js_draw_text_on_image, "draw_text_on_image", 6));
  JS_SetPropertyStr(ctx, global, "draw_rectangle_outline", JS_NewCFunction(ctx, js_draw_rectangle_outline, "draw_rectangle_outline", 6));
  JS_SetPropertyStr(ctx, global, "draw_triangle_outline", JS_NewCFunction(ctx, js_draw_triangle_outline, "draw_triangle_outline", 8));
  JS_SetPropertyStr(ctx, global, "draw_ellipse_outline", JS_NewCFunction(ctx, js_draw_ellipse_outline, "draw_ellipse_outline", 6));
  JS_SetPropertyStr(ctx, global, "draw_circle_outline", JS_NewCFunction(ctx, js_draw_circle_outline, "draw_circle_outline", 5));
  JS_SetPropertyStr(ctx, global, "draw_polygon_outline", JS_NewCFunction(ctx, js_draw_polygon_outline, "draw_polygon_outline", 4));
  JS_SetPropertyStr(ctx, global, "draw_arc_outline", JS_NewCFunction(ctx, js_draw_arc_outline, "draw_arc_outline", 8));
  JS_SetPropertyStr(ctx, global, "draw_rectangle_rounded_outline", JS_NewCFunction(ctx, js_draw_rectangle_rounded_outline, "draw_rectangle_rounded_outline", 7));
  JS_SetPropertyStr(ctx, global, "draw_rectangle_outline_on_image", JS_NewCFunction(ctx, js_draw_rectangle_outline_on_image, "draw_rectangle_outline_on_image", 7));
  JS_SetPropertyStr(ctx, global, "draw_triangle_outline_on_image", JS_NewCFunction(ctx, js_draw_triangle_outline_on_image, "draw_triangle_outline_on_image", 9));
  JS_SetPropertyStr(ctx, global, "draw_ellipse_outline_on_image", JS_NewCFunction(ctx, js_draw_ellipse_outline_on_image, "draw_ellipse_outline_on_image", 7));
  JS_SetPropertyStr(ctx, global, "draw_circle_outline_on_image", JS_NewCFunction(ctx, js_draw_circle_outline_on_image, "draw_circle_outline_on_image", 6));
  JS_SetPropertyStr(ctx, global, "draw_polygon_outline_on_image", JS_NewCFunction(ctx, js_draw_polygon_outline_on_image, "draw_polygon_outline_on_image", 5));
  JS_SetPropertyStr(ctx, global, "draw_rectangle_rounded_outline_on_image", JS_NewCFunction(ctx, js_draw_rectangle_rounded_outline_on_image, "draw_rectangle_rounded_outline_on_image", 8));
  JS_SetPropertyStr(ctx, global, "key_pressed", JS_NewCFunction(ctx, js_key_pressed, "key_pressed", 1));
  JS_SetPropertyStr(ctx, global, "key_down", JS_NewCFunction(ctx, js_key_down, "key_down", 1));
  JS_SetPropertyStr(ctx, global, "key_released", JS_NewCFunction(ctx, js_key_released, "key_released", 1));
  JS_SetPropertyStr(ctx, global, "key_up", JS_NewCFunction(ctx, js_key_up, "key_up", 1));
  JS_SetPropertyStr(ctx, global, "gamepad_button_pressed", JS_NewCFunction(ctx, js_gamepad_button_pressed, "gamepad_button_pressed", 2));
  JS_SetPropertyStr(ctx, global, "gamepad_button_down", JS_NewCFunction(ctx, js_gamepad_button_down, "gamepad_button_down", 2));
  JS_SetPropertyStr(ctx, global, "gamepad_button_released", JS_NewCFunction(ctx, js_gamepad_button_released, "gamepad_button_released", 2));
  JS_SetPropertyStr(ctx, global, "mouse_position", JS_NewCFunction(ctx, js_mouse_position, "mouse_position", 0));
  JS_SetPropertyStr(ctx, global, "mouse_button_pressed", JS_NewCFunction(ctx, js_mouse_button_pressed, "mouse_button_pressed", 1));
  JS_SetPropertyStr(ctx, global, "mouse_button_down", JS_NewCFunction(ctx, js_mouse_button_down, "mouse_button_down", 1));
  JS_SetPropertyStr(ctx, global, "mouse_button_released", JS_NewCFunction(ctx, js_mouse_button_released, "mouse_button_released", 1));
  JS_SetPropertyStr(ctx, global, "mouse_button_up", JS_NewCFunction(ctx, js_mouse_button_up, "mouse_button_up", 1));
  JS_SetPropertyStr(ctx, global, "load_sound", JS_NewCFunction(ctx, js_load_sound, "load_sound", 1));
  JS_SetPropertyStr(ctx, global, "play_sound", JS_NewCFunction(ctx, js_play_sound, "play_sound", 2));
  JS_SetPropertyStr(ctx, global, "stop_sound", JS_NewCFunction(ctx, js_stop_sound, "stop_sound", 1));
  JS_SetPropertyStr(ctx, global, "unload_sound", JS_NewCFunction(ctx, js_unload_sound, "unload_sound", 1));
  JS_SetPropertyStr(ctx, global, "tts_sound", JS_NewCFunction(ctx, js_tts_sound, "tts_sound", 7));
  JS_SetPropertyStr(ctx, global, "sfx_sound", JS_NewCFunction(ctx, js_sfx_sound, "sfx_sound", 1));
  JS_SetPropertyStr(ctx, global, "sfx_generate", JS_NewCFunction(ctx, js_sfx_generate, "sfx_generate", 1));
  JS_SetPropertyStr(ctx, global, "current_time", JS_NewCFunction(ctx, js_current_time, "current_time", 0));
  JS_SetPropertyStr(ctx, global, "delta_time", JS_NewCFunction(ctx, js_delta_time, "delta_time", 0));
  JS_SetPropertyStr(ctx, global, "random_int", JS_NewCFunction(ctx, js_random_int, "random_int", 2));
  JS_SetPropertyStr(ctx, global, "random_seed_get", JS_NewCFunction(ctx, js_random_seed_get, "random_seed_get", 0));
  JS_SetPropertyStr(ctx, global, "random_seed_set", JS_NewCFunction(ctx, js_random_seed_set, "random_seed_set", 1));
}