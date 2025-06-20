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


  // UTILITIES

  // Get system-time (ms) since unix epoch
  static JSValue js_current_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Get the change in time (seconds) since the last update run
  static JSValue js_delta_time(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Get a random integer between 2 numbers
  static JSValue js_random_int(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Get the random-seed
  static JSValue js_random_seed_get(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Set the random-seed
  static JSValue js_random_seed_set(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }

  // SOUND

  // Load a sound from a file in cart
  static JSValue js_load_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Play a sound
  static JSValue js_play_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Stop a sound
  static JSValue js_stop_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Unload a sound
  static JSValue js_unload_sound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }

  // INPUT

  // Has the key been pressed? (tracks unpress/read correctly)
  static JSValue js_key_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Is the key currently down?
  static JSValue js_key_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Has the key been released? (tracks press/read correctly)
  static JSValue js_key_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Is the key currently up?
  static JSValue js_key_up(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Has the button been pressed? (tracks unpress/read correctly)
  static JSValue js_gamepad_button_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Is the button currently down?
  static JSValue js_gamepad_button_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Has the button been released? (tracks press/read correctly)
  static JSValue js_gamepad_button_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Get current position of mouse
  static JSValue js_mouse_position(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Has the button been pressed? (tracks unpress/read correctly)
  static JSValue js_mouse_button_pressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Is the button currently down?
  static JSValue js_mouse_button_down(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Has the button been released? (tracks press/read correctly)
  static JSValue js_mouse_button_released(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Is the button currently up?
  static JSValue js_mouse_button_up(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }

  // GRAPHICS

  // Create a new blank image
  static JSValue js_new_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Copy an image to a new image
  static JSValue js_image_copy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Create an image from a region of another image
  static JSValue js_image_subimage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Clear the screen
  static JSValue js_clear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a single pixel on the screen
  static JSValue js_draw_point(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a line on the screen
  static JSValue js_draw_line(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled rectangle on the screen
  static JSValue js_draw_rectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled triangle on the screen
  static JSValue js_draw_triangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled ellipse on the screen
  static JSValue js_draw_ellipse(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled circle on the screen
  static JSValue js_draw_circle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled polygon on the screen
  static JSValue js_draw_polygon(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled arc on the screen
  static JSValue js_draw_arc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled round-rectangle on the screen
  static JSValue js_draw_rectangle_rounded(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image on the screen
  static JSValue js_draw_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a tinted image on the screen
  static JSValue js_draw_image_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image, rotated, on the screen
  static JSValue js_draw_image_rotated(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image, flipped, on the screen
  static JSValue js_draw_image_flipped(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image, scaled, on the screen
  static JSValue js_draw_image_scaled(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw some text on the screen
  static JSValue js_draw_text(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Save an image to persistant storage
  static JSValue js_save_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Load an image from a file in cart
  static JSValue js_load_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Resize an image, in-place
  static JSValue js_image_resize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Scale an image, in-place
  static JSValue js_image_scale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Replace a color in an image, in-place
  static JSValue js_image_color_replace(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Tint a color in an image, in-place
  static JSValue js_image_color_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Fade a color in an image, in-place
  static JSValue js_image_color_fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Copy a font to a new font
  static JSValue js_font_copy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Scale a font, return a new font
  static JSValue js_font_scale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Load a BMF font from a file in cart
  static JSValue js_load_font_bmf(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Load a BMF font from an image
  static JSValue js_load_font_bmf_from_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Measure the size of some text
  static JSValue js_measure_text(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Meaure an image (use 0 for screen)
  static JSValue js_measure_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Load a TTY font from a file in cart
  static JSValue js_load_font_tty(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Load a TTY font from an image
  static JSValue js_load_font_tty_from_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Load a TTF font from a file in cart
  static JSValue js_load_font_ttf(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Invert the colors in an image, in-place
  static JSValue js_image_color_invert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Calculate a rectangle representing the available alpha border in an image
  static JSValue js_image_alpha_border(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Crop an image, in-place
  static JSValue js_image_crop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Crop an image based on the alpha border, in-place
  static JSValue js_image_alpha_crop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Adjust the brightness of an image, in-place
  static JSValue js_image_color_brightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Flip an image, in-place
  static JSValue js_image_flip(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Change the contrast of an image, in-place
  static JSValue js_image_color_contrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Use an image as an alpha-mask on another image
  static JSValue js_image_alpha_mask(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Create a new image, rotating another image
  static JSValue js_image_rotate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Create a new image of a gradient
  static JSValue js_image_gradient(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Unload an image
  static JSValue js_unload_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Unload a font
  static JSValue js_unload_font(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Clear an image
  static JSValue js_clear_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a single pixel on an image
  static JSValue js_draw_point_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a line on an image
  static JSValue js_draw_line_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled rectangle on an image
  static JSValue js_draw_rectangle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled triangle on an image
  static JSValue js_draw_triangle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled ellipse on an image
  static JSValue js_draw_ellipse_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a circle on an image
  static JSValue js_draw_circle_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled polygon on an image
  static JSValue js_draw_polygon_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a filled round-rectangle on an image
  static JSValue js_draw_rectangle_rounded_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image on an image
  static JSValue js_draw_image_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a tinted image on an image
  static JSValue js_draw_image_tint_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image, rotated, on an image
  static JSValue js_draw_image_rotated_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image, flipped, on an image
  static JSValue js_draw_image_flipped_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw an image, scaled, on an image
  static JSValue js_draw_image_scaled_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw some text on an image
  static JSValue js_draw_text_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) rectangle on the screen
  static JSValue js_draw_rectangle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) triangle on the screen
  static JSValue js_draw_triangle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) ellipse on the screen
  static JSValue js_draw_ellipse_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) circle on the screen
  static JSValue js_draw_circle_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) polygon on the screen
  static JSValue js_draw_polygon_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) arc on the screen
  static JSValue js_draw_arc_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) round-rectangle on the screen
  static JSValue js_draw_rectangle_rounded_outline(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) rectangle on an image
  static JSValue js_draw_rectangle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) triangle on an image
  static JSValue js_draw_triangle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) ellipse on an image
  static JSValue js_draw_ellipse_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) circle on an image
  static JSValue js_draw_circle_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) polygon on an image
  static JSValue js_draw_polygon_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Draw a outlined (with thickness) round-rectangle on an image
  static JSValue js_draw_rectangle_rounded_outline_on_image(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }

  // COLORS

  // Tint a color with another color
  static JSValue js_color_tint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Fade a color
  static JSValue js_color_fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Change the brightness of a color
  static JSValue js_color_brightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Invert a color
  static JSValue js_color_invert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Blend 2 colors together
  static JSValue js_color_alpha_blend(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Change contrast of a color
  static JSValue js_color_contrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }
  // Interpolate colors
  static JSValue js_color_bilinear_interpolate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    return JS_UNDEFINED;
  }

// Set up game engine bindings
static void setup_game_bindings() {
  JSValue global = JS_GetGlobalObject(ctx);

  // Add console.log function
  JSValue console_obj = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, console_obj, "log", JS_NewCFunction(ctx, js_log, "log", 1));
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
