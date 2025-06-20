#include "../null0.h"
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

static int execute_js_file(const char *filename) {
  char *code = read_file(filename);
  if (code == NULL) {
    return -1;
  }
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
      fprintf(stderr, "Error calling %s: %s\n", func_name, error_str ? error_str : "Unknown error");
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
    fprintf(stderr, "Error: Failed to create QuickJS runtime\n");
    return 1;
  }
  ctx = JS_NewContext(rt);
  if (!ctx) {
    fprintf(stderr, "Error: Failed to create QuickJS context\n");
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
      printf("%s\n", str);
      JS_FreeCString(ctx, str);
    }
  }
  return JS_UNDEFINED;
}



// UTILITIES

// Get system-time (ms) since unix epoch
static JSValue js_current_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(current_time());
}
// Get the change in time (seconds) since the last update run
static JSValue js_delta_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(delta_time());
}
// Get a random integer between 2 numbers
static JSValue js_random_int(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(random_int(min, max));
}
// Get the random-seed
static JSValue js_random_seed_get(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(random_seed_get());
}
// Set the random-seed
static JSValue js_random_seed_set(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 random_seed_set(seed);
 return JS_UNDEFINED;
}

// SOUND

// Load a sound from a file in cart
static JSValue js_load_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(load_sound(filename));
}
// Play a sound
static JSValue js_play_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 play_sound(sound, loop);
 return JS_UNDEFINED;
}
// Stop a sound
static JSValue js_stop_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 stop_sound(sound);
 return JS_UNDEFINED;
}
// Unload a sound
static JSValue js_unload_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 unload_sound(sound);
 return JS_UNDEFINED;
}

// INPUT

// Has the key been pressed? (tracks unpress/read correctly)
static JSValue js_key_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(key_pressed(key));
}
// Is the key currently down?
static JSValue js_key_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(key_down(key));
}
// Has the key been released? (tracks press/read correctly)
static JSValue js_key_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(key_released(key));
}
// Is the key currently up?
static JSValue js_key_up(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(key_up(key));
}
// Has the button been pressed? (tracks unpress/read correctly)
static JSValue js_gamepad_button_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(gamepad_button_pressed(gamepad, button));
}
// Is the button currently down?
static JSValue js_gamepad_button_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(gamepad_button_down(gamepad, button));
}
// Has the button been released? (tracks press/read correctly)
static JSValue js_gamepad_button_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(gamepad_button_released(gamepad, button));
}
// Get current position of mouse
static JSValue js_mouse_position(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(mouse_position());
}
// Has the button been pressed? (tracks unpress/read correctly)
static JSValue js_mouse_button_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(mouse_button_pressed(button));
}
// Is the button currently down?
static JSValue js_mouse_button_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(mouse_button_down(button));
}
// Has the button been released? (tracks press/read correctly)
static JSValue js_mouse_button_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(mouse_button_released(button));
}
// Is the button currently up?
static JSValue js_mouse_button_up(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(mouse_button_up(button));
}

// GRAPHICS

// Create a new blank image
static JSValue js_new_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(new_image(width, height, color));
}
// Copy an image to a new image
static JSValue js_image_copy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(image_copy(image));
}
// Create an image from a region of another image
static JSValue js_image_subimage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(image_subimage(image, x, y, width, height));
}
// Clear the screen
static JSValue js_clear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 clear(color);
 return JS_UNDEFINED;
}
// Draw a single pixel on the screen
static JSValue js_draw_point(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_point(x, y, color);
 return JS_UNDEFINED;
}
// Draw a line on the screen
static JSValue js_draw_line(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_line(startPosX, startPosY, endPosX, endPosY, color);
 return JS_UNDEFINED;
}
// Draw a filled rectangle on the screen
static JSValue js_draw_rectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle(posX, posY, width, height, color);
 return JS_UNDEFINED;
}
// Draw a filled triangle on the screen
static JSValue js_draw_triangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle(x1, y1, x2, y2, x3, y3, color);
 return JS_UNDEFINED;
}
// Draw a filled ellipse on the screen
static JSValue js_draw_ellipse(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse(centerX, centerY, radiusX, radiusY, color);
 return JS_UNDEFINED;
}
// Draw a filled circle on the screen
static JSValue js_draw_circle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle(centerX, centerY, radius, color);
 return JS_UNDEFINED;
}
// Draw a filled polygon on the screen
static JSValue js_draw_polygon(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_polygon(points, numPoints, color);
 return JS_UNDEFINED;
}
// Draw a filled arc on the screen
static JSValue js_draw_arc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color);
 return JS_UNDEFINED;
}
// Draw a filled round-rectangle on the screen
static JSValue js_draw_rectangle_rounded(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded(x, y, width, height, cornerRadius, color);
 return JS_UNDEFINED;
}
// Draw an image on the screen
static JSValue js_draw_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image(src, posX, posY);
 return JS_UNDEFINED;
}
// Draw a tinted image on the screen
static JSValue js_draw_image_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_tint(src, posX, posY, tint);
 return JS_UNDEFINED;
}
// Draw an image, rotated, on the screen
static JSValue js_draw_image_rotated(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter);
 return JS_UNDEFINED;
}
// Draw an image, flipped, on the screen
static JSValue js_draw_image_flipped(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
 return JS_UNDEFINED;
}
// Draw an image, scaled, on the screen
static JSValue js_draw_image_scaled(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
 return JS_UNDEFINED;
}
// Draw some text on the screen
static JSValue js_draw_text(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_text(font, text, posX, posY, color);
 return JS_UNDEFINED;
}
// Save an image to persistant storage
static JSValue js_save_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 save_image(image, filename);
 return JS_UNDEFINED;
}
// Load an image from a file in cart
static JSValue js_load_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(load_image(filename));
}
// Resize an image, in-place
static JSValue js_image_resize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_resize(image, newWidth, newHeight, filter);
 return JS_UNDEFINED;
}
// Scale an image, in-place
static JSValue js_image_scale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_scale(image, scaleX, scaleY, filter);
 return JS_UNDEFINED;
}
// Replace a color in an image, in-place
static JSValue js_image_color_replace(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_replace(image, color, replace);
 return JS_UNDEFINED;
}
// Tint a color in an image, in-place
static JSValue js_image_color_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_tint(image, color);
 return JS_UNDEFINED;
}
// Fade a color in an image, in-place
static JSValue js_image_color_fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_fade(image, alpha);
 return JS_UNDEFINED;
}
// Copy a font to a new font
static JSValue js_font_copy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(font_copy(font));
}
// Scale a font, return a new font
static JSValue js_font_scale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(font_scale(font, scaleX, scaleY, filter));
}
// Load a BMF font from a file in cart
static JSValue js_load_font_bmf(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(load_font_bmf(filename, characters));
}
// Load a BMF font from an image
static JSValue js_load_font_bmf_from_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(load_font_bmf_from_image(image, characters));
}
// Measure the size of some text
static JSValue js_measure_text(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(measure_text(font, text, textLength));
}
// Meaure an image (use 0 for screen)
static JSValue js_measure_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(measure_image(image));
}
// Load a TTY font from a file in cart
static JSValue js_load_font_tty(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(load_font_tty(filename, glyphWidth, glyphHeight, characters));
}
// Load a TTY font from an image
static JSValue js_load_font_tty_from_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(load_font_tty_from_image(image, glyphWidth, glyphHeight, characters));
}
// Load a TTF font from a file in cart
static JSValue js_load_font_ttf(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(load_font_ttf(filename, fontSize));
}
// Invert the colors in an image, in-place
static JSValue js_image_color_invert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_invert(image);
 return JS_UNDEFINED;
}
// Calculate a rectangle representing the available alpha border in an image
static JSValue js_image_alpha_border(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(image_alpha_border(image, threshold));
}
// Crop an image, in-place
static JSValue js_image_crop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_crop(image, x, y, width, height);
 return JS_UNDEFINED;
}
// Crop an image based on the alpha border, in-place
static JSValue js_image_alpha_crop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_alpha_crop(image, threshold);
 return JS_UNDEFINED;
}
// Adjust the brightness of an image, in-place
static JSValue js_image_color_brightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_brightness(image, factor);
 return JS_UNDEFINED;
}
// Flip an image, in-place
static JSValue js_image_flip(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_flip(image, horizontal, vertical);
 return JS_UNDEFINED;
}
// Change the contrast of an image, in-place
static JSValue js_image_color_contrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_color_contrast(image, contrast);
 return JS_UNDEFINED;
}
// Use an image as an alpha-mask on another image
static JSValue js_image_alpha_mask(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 image_alpha_mask(image, alphaMask, posX, posY);
 return JS_UNDEFINED;
}
// Create a new image, rotating another image
static JSValue js_image_rotate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(image_rotate(image, degrees, filter));
}
// Create a new image of a gradient
static JSValue js_image_gradient(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(image_gradient(width, height, topLeft, topRight, bottomLeft, bottomRight));
}
// Unload an image
static JSValue js_unload_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 unload_image(image);
 return JS_UNDEFINED;
}
// Unload a font
static JSValue js_unload_font(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 unload_font(font);
 return JS_UNDEFINED;
}
// Clear an image
static JSValue js_clear_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 clear_image(destination, color);
 return JS_UNDEFINED;
}
// Draw a single pixel on an image
static JSValue js_draw_point_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_point_on_image(destination, x, y, color);
 return JS_UNDEFINED;
}
// Draw a line on an image
static JSValue js_draw_line_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color);
 return JS_UNDEFINED;
}
// Draw a filled rectangle on an image
static JSValue js_draw_rectangle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_on_image(destination, posX, posY, width, height, color);
 return JS_UNDEFINED;
}
// Draw a filled triangle on an image
static JSValue js_draw_triangle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color);
 return JS_UNDEFINED;
}
// Draw a filled ellipse on an image
static JSValue js_draw_ellipse_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color);
 return JS_UNDEFINED;
}
// Draw a circle on an image
static JSValue js_draw_circle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle_on_image(destination, centerX, centerY, radius, color);
 return JS_UNDEFINED;
}
// Draw a filled polygon on an image
static JSValue js_draw_polygon_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_polygon_on_image(destination, points, numPoints, color);
 return JS_UNDEFINED;
}
// Draw a filled round-rectangle on an image
static JSValue js_draw_rectangle_rounded_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color);
 return JS_UNDEFINED;
}
// Draw an image on an image
static JSValue js_draw_image_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_on_image(destination, src, posX, posY);
 return JS_UNDEFINED;
}
// Draw a tinted image on an image
static JSValue js_draw_image_tint_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_tint_on_image(destination, src, posX, posY, tint);
 return JS_UNDEFINED;
}
// Draw an image, rotated, on an image
static JSValue js_draw_image_rotated_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter);
 return JS_UNDEFINED;
}
// Draw an image, flipped, on an image
static JSValue js_draw_image_flipped_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
 return JS_UNDEFINED;
}
// Draw an image, scaled, on an image
static JSValue js_draw_image_scaled_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
 return JS_UNDEFINED;
}
// Draw some text on an image
static JSValue js_draw_text_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_text_on_image(destination, font, text, posX, posY, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) rectangle on the screen
static JSValue js_draw_rectangle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_outline(posX, posY, width, height, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) triangle on the screen
static JSValue js_draw_triangle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) ellipse on the screen
static JSValue js_draw_ellipse_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) circle on the screen
static JSValue js_draw_circle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle_outline(centerX, centerY, radius, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) polygon on the screen
static JSValue js_draw_polygon_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_polygon_outline(points, numPoints, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) arc on the screen
static JSValue js_draw_arc_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) round-rectangle on the screen
static JSValue js_draw_rectangle_rounded_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) rectangle on an image
static JSValue js_draw_rectangle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) triangle on an image
static JSValue js_draw_triangle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) ellipse on an image
static JSValue js_draw_ellipse_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) circle on an image
static JSValue js_draw_circle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) polygon on an image
static JSValue js_draw_polygon_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_polygon_outline_on_image(destination, points, numPoints, thickness, color);
 return JS_UNDEFINED;
}
// Draw a outlined (with thickness) round-rectangle on an image
static JSValue js_draw_rectangle_rounded_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, color);
 return JS_UNDEFINED;
}

// COLORS

// Tint a color with another color
static JSValue js_color_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(color_tint(color, tint));
}
// Fade a color
static JSValue js_color_fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(color_fade(color, alpha));
}
// Change the brightness of a color
static JSValue js_color_brightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(color_brightness(color, factor));
}
// Invert a color
static JSValue js_color_invert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(color_invert(color));
}
// Blend 2 colors together
static JSValue js_color_alpha_blend(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(color_alpha_blend(dst, src));
}
// Change contrast of a color
static JSValue js_color_contrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(color_contrast(color, contrast));
}
// Interpolate colors
static JSValue js_color_bilinear_interpolate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
 return undefined(color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY));
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

 JSValue console_obj = JS_NewObject(ctx);
 JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_console_log, "log", 1));
 JS_SetPropertyStr(ctx, global, "console", console_obj);
 
  JS_SetPropertyStr(ctx, global, "current_time", JS_NewCFunction(ctx, js_current_time, "current_time", 0));
  JS_SetPropertyStr(ctx, global, "delta_time", JS_NewCFunction(ctx, js_delta_time, "delta_time", 0));
  JS_SetPropertyStr(ctx, global, "random_int", JS_NewCFunction(ctx, js_random_int, "random_int", 2));
  JS_SetPropertyStr(ctx, global, "random_seed_get", JS_NewCFunction(ctx, js_random_seed_get, "random_seed_get", 0));
  JS_SetPropertyStr(ctx, global, "random_seed_set", JS_NewCFunction(ctx, js_random_seed_set, "random_seed_set", 1));
  JS_SetPropertyStr(ctx, global, "load_sound", JS_NewCFunction(ctx, js_load_sound, "load_sound", 1));
  JS_SetPropertyStr(ctx, global, "play_sound", JS_NewCFunction(ctx, js_play_sound, "play_sound", 2));
  JS_SetPropertyStr(ctx, global, "stop_sound", JS_NewCFunction(ctx, js_stop_sound, "stop_sound", 1));
  JS_SetPropertyStr(ctx, global, "unload_sound", JS_NewCFunction(ctx, js_unload_sound, "unload_sound", 1));
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
  JS_SetPropertyStr(ctx, global, "color_tint", JS_NewCFunction(ctx, js_color_tint, "color_tint", 2));
  JS_SetPropertyStr(ctx, global, "color_fade", JS_NewCFunction(ctx, js_color_fade, "color_fade", 2));
  JS_SetPropertyStr(ctx, global, "color_brightness", JS_NewCFunction(ctx, js_color_brightness, "color_brightness", 2));
  JS_SetPropertyStr(ctx, global, "color_invert", JS_NewCFunction(ctx, js_color_invert, "color_invert", 1));
  JS_SetPropertyStr(ctx, global, "color_alpha_blend", JS_NewCFunction(ctx, js_color_alpha_blend, "color_alpha_blend", 2));
  JS_SetPropertyStr(ctx, global, "color_contrast", JS_NewCFunction(ctx, js_color_contrast, "color_contrast", 2));
  JS_SetPropertyStr(ctx, global, "color_bilinear_interpolate", JS_NewCFunction(ctx, js_color_bilinear_interpolate, "color_bilinear_interpolate", 6));
}