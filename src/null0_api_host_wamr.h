// Null0 WAMR native host - generated 2024-01-03T02:28:19.733Z

#pragma once

#include "null0_api.h"
#include "wasm_c_api.h"
#include "wasm_export.h"

wasm_exec_env_t exec_env;
wasm_module_inst_t module_inst;

wasm_function_inst_t cart_update = NULL;
wasm_function_inst_t cart_buttonUp = NULL;
wasm_function_inst_t cart_buttonDown = NULL;
wasm_function_inst_t cart_keyUp = NULL;
wasm_function_inst_t cart_keyDown = NULL;



// UTILITIES

// Log a string
static void wamr_null0_trace(wasm_exec_env_t exec_env, char* str) {
  null0_trace(str);
}

// Get system-time (ms) since unix epoch
static uint64_t wamr_null0_current_time(wasm_exec_env_t exec_env) {
  return null0_current_time();
}

// Get the change in time (seconds) since the last update run
static float wamr_null0_delta_time(wasm_exec_env_t exec_env) {
  return null0_delta_time();
}

// Get a random integer between 2 numbers
static int32_t wamr_null0_random_int(wasm_exec_env_t exec_env, int32_t min, int32_t max) {
  return null0_random_int(min, max);
}

// SOUND

// Load a sound from a file in cart
static uint32_t wamr_null0_load_sound(wasm_exec_env_t exec_env, char* filename) {
  return null0_load_sound(filename);
}

// Play a sound
static void wamr_null0_play_sound(wasm_exec_env_t exec_env, uint32_t sound, bool loop) {
  null0_play_sound(sound, loop);
}

// Stop a sound
static void wamr_null0_stop_sound(wasm_exec_env_t exec_env, uint32_t sound) {
  null0_stop_sound(sound);
}

// Create a new sound-effect from some sfxr params
static uint32_t wamr_null0_new_sfx(wasm_exec_env_t exec_env, SfxParams* params) {
  return null0_new_sfx(params);
}

// Generate randomized preset sfxr params
static void wamr_null0_preset_sfx(wasm_exec_env_t exec_env, SfxParams* params, SfxPresetType type) {
  null0_preset_sfx(params, type);
}

// Randomize sfxr params
static void wamr_null0_randomize_sfx(wasm_exec_env_t exec_env, SfxParams* params, SfxWaveType waveType) {
  null0_randomize_sfx(params, waveType);
}

// Randomly mutate sfxr params
static void wamr_null0_mutate_sfx(wasm_exec_env_t exec_env, SfxParams* params, float range, uint32_t mask) {
  null0_mutate_sfx(params, range, mask);
}

// Create a new sfxr from a .rfx file
static uint32_t wamr_null0_load_sfx(wasm_exec_env_t exec_env, char* filename) {
  return null0_load_sfx(filename);
}

// Unload a sound
static void wamr_null0_unload_sound(wasm_exec_env_t exec_env, uint32_t sound) {
  null0_unload_sound(sound);
}

// INPUT

// Has the key been pressed? (tracks unpress/read correctly)
static bool wamr_null0_key_pressed(wasm_exec_env_t exec_env, pntr_app_key key) {
  return null0_key_pressed(key);
}

// Is the key currently down?
static bool wamr_null0_key_down(wasm_exec_env_t exec_env, pntr_app_key key) {
  return null0_key_down(key);
}

// Has the key been released? (tracks press/read correctly)
static bool wamr_null0_key_released(wasm_exec_env_t exec_env, pntr_app_key key) {
  return null0_key_released(key);
}

// Is the key currently up?
static bool wamr_null0_key_up(wasm_exec_env_t exec_env, pntr_app_key key) {
  return null0_key_up(key);
}

// Has the button been pressed? (tracks unpress/read correctly)
static bool wamr_null0_gamepad_button_pressed(wasm_exec_env_t exec_env, int32_t gamepad, pntr_app_gamepad_button button) {
  return null0_gamepad_button_pressed(gamepad, button);
}

// Is the button currently down?
static bool wamr_null0_gamepad_button_down(wasm_exec_env_t exec_env, int32_t gamepad, pntr_app_gamepad_button button) {
  return null0_gamepad_button_down(gamepad, button);
}

// Has the button been released? (tracks press/read correctly)
static bool wamr_null0_gamepad_button_released(wasm_exec_env_t exec_env, int32_t gamepad, pntr_app_gamepad_button button) {
  return null0_gamepad_button_released(gamepad, button);
}

// Is the button currently up?
static bool wamr_null0_gamepad_button_up(wasm_exec_env_t exec_env, int32_t gamepad, pntr_app_gamepad_button button) {
  return null0_gamepad_button_up(gamepad, button);
}

// Get current position of mouse
static pntr_vector wamr_null0_mouse_position(wasm_exec_env_t exec_env) {
  return null0_mouse_position();
}

// Has the button been pressed? (tracks unpress/read correctly)
static bool wamr_null0_mouse_button_pressed(wasm_exec_env_t exec_env, pntr_app_mouse_button button) {
  return null0_mouse_button_pressed(button);
}

// Is the button currently down?
static bool wamr_null0_mouse_button_down(wasm_exec_env_t exec_env, pntr_app_mouse_button button) {
  return null0_mouse_button_down(button);
}

// Has the button been released? (tracks press/read correctly)
static bool wamr_null0_mouse_button_released(wasm_exec_env_t exec_env, pntr_app_mouse_button button) {
  return null0_mouse_button_released(button);
}

// Is the button currently up?
static bool wamr_null0_mouse_button_up(wasm_exec_env_t exec_env, pntr_app_mouse_button button) {
  return null0_mouse_button_up(button);
}

// GRAPHICS

// Create a new blank image
static uint32_t wamr_null0_new_image(wasm_exec_env_t exec_env, int32_t width, int32_t height, uint32_t color) {
  return null0_new_image(width, height, color);
}

// Copy an image to a new image
static uint32_t wamr_null0_image_copy(wasm_exec_env_t exec_env, uint32_t image) {
  return null0_image_copy(image);
}

// Create an image from a region of another image
static uint32_t wamr_null0_image_subimage(wasm_exec_env_t exec_env, uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  return null0_image_subimage(image, x, y, width, height);
}

// Clear the screen
static void wamr_null0_clear(wasm_exec_env_t exec_env, uint32_t color) {
  null0_clear(color);
}

// Draw a single pixel on the screen
static void wamr_null0_draw_point(wasm_exec_env_t exec_env, int32_t x, int32_t y, uint32_t color) {
  null0_draw_point(x, y, color);
}

// Draw a line on the screen
static void wamr_null0_draw_line(wasm_exec_env_t exec_env, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, uint32_t color) {
  null0_draw_line(startPosX, startPosY, endPosX, endPosY, color);
}

// Draw a filled rectangle on the screen
static void wamr_null0_draw_rectangle(wasm_exec_env_t exec_env, int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {
  null0_draw_rectangle(posX, posY, width, height, color);
}

// Draw a filled triangle on the screen
static void wamr_null0_draw_triangle(wasm_exec_env_t exec_env, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {
  null0_draw_triangle(x1, y1, x2, y2, x3, y3, color);
}

// Draw a filled ellipse on the screen
static void wamr_null0_draw_ellipse(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {
  null0_draw_ellipse(centerX, centerY, radiusX, radiusY, color);
}

// Draw a filled circle on the screen
static void wamr_null0_draw_circle(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {
  null0_draw_circle(centerX, centerY, radius, color);
}

// Draw a filled polygon on the screen
static void wamr_null0_draw_polygon(wasm_exec_env_t exec_env, pntr_vector* points, int32_t numPoints, uint32_t color) {
  null0_draw_polygon(points, numPoints, color);
}

// Draw several lines on the screen
static void wamr_null0_draw_polyline(wasm_exec_env_t exec_env, pntr_vector* points, int32_t numPoints, uint32_t color) {
  null0_draw_polyline(points, numPoints, color);
}

// Draw a filled arc on the screen
static void wamr_null0_draw_arc(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, uint32_t color) {
  null0_draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color);
}

// Draw a filled round-rectangle on the screen
static void wamr_null0_draw_rectangle_rounded(wasm_exec_env_t exec_env, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {
  null0_draw_rectangle_rounded(x, y, width, height, cornerRadius, color);
}

// Draw an image on the screen
static void wamr_null0_draw_image(wasm_exec_env_t exec_env, uint32_t src, int32_t posX, int32_t posY) {
  null0_draw_image(src, posX, posY);
}

// Draw a tinted image on the screen
static void wamr_null0_draw_image_tint(wasm_exec_env_t exec_env, uint32_t src, int32_t posX, int32_t posY, uint32_t tint) {
  null0_draw_image_tint(src, posX, posY, tint);
}

// Draw an image, rotated, on the screen
static void wamr_null0_draw_image_rotated(wasm_exec_env_t exec_env, uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {
  null0_draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter);
}

// Draw an image, flipped, on the screen
static void wamr_null0_draw_image_flipped(wasm_exec_env_t exec_env, uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  null0_draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

// Draw an image, scaled, on the screen
static void wamr_null0_draw_image_scaled(wasm_exec_env_t exec_env, uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {
  null0_draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

// Draw some text on the screen
static void wamr_null0_draw_text(wasm_exec_env_t exec_env, uint32_t font, char* text, int32_t posX, int32_t posY, uint32_t color) {
  null0_draw_text(font, text, posX, posY, color);
}

// Save an image to persistant storage
static void wamr_null0_save_image(wasm_exec_env_t exec_env, uint32_t image, char* filename) {
  null0_save_image(image, filename);
}

// Load an image from a file in cart
static uint32_t wamr_null0_load_image(wasm_exec_env_t exec_env, char* filename) {
  return null0_load_image(filename);
}

// Resize an image, in-place
static void wamr_null0_image_resize(wasm_exec_env_t exec_env, uint32_t image, int32_t newWidth, int32_t newHeight, int32_t offsetX, int32_t offsetY, uint32_t fill) {
  null0_image_resize(image, newWidth, newHeight, offsetX, offsetY, fill);
}

// Scale an image, in-place
static void wamr_null0_image_scale(wasm_exec_env_t exec_env, uint32_t image, float scaleX, float scaleY, pntr_filter filter) {
  null0_image_scale(image, scaleX, scaleY, filter);
}

// Replace a color in an image, in-place
static void wamr_null0_image_color_replace(wasm_exec_env_t exec_env, uint32_t image, uint32_t color, uint32_t replace) {
  null0_image_color_replace(image, color, replace);
}

// Tint a color in an image, in-place
static void wamr_null0_image_color_tint(wasm_exec_env_t exec_env, uint32_t image, uint32_t color) {
  null0_image_color_tint(image, color);
}

// Fade a color in an image, in-place
static void wamr_null0_image_color_fade(wasm_exec_env_t exec_env, uint32_t image, float alpha) {
  null0_image_color_fade(image, alpha);
}

// Copy a font to a new font
static uint32_t wamr_null0_font_copy(wasm_exec_env_t exec_env, uint32_t font) {
  return null0_font_copy(font);
}

// Scale a font, return a new font
static uint32_t wamr_null0_font_scale(wasm_exec_env_t exec_env, uint32_t font, float scaleX, float scaleY, pntr_filter filter) {
  return null0_font_scale(font, scaleX, scaleY, filter);
}

// Load a BMF font from a file in cart
static uint32_t wamr_null0_load_font_bmf(wasm_exec_env_t exec_env, char* filename, char* characters) {
  return null0_load_font_bmf(filename, characters);
}

// Load a BMF font from an image
static uint32_t wamr_null0_load_font_bmf_from_image(wasm_exec_env_t exec_env, uint32_t image, char* characters) {
  return null0_load_font_bmf_from_image(image, characters);
}

// Measure the size of some text
static pntr_vector wamr_null0_measure_text(wasm_exec_env_t exec_env, uint32_t font, char* text) {
  return null0_measure_text(font, text);
}

// Meaure an image (use 0 for screen)
static pntr_vector wamr_null0_measure_image(wasm_exec_env_t exec_env, uint32_t image) {
  return null0_measure_image(image);
}

// Load a TTY font from a file in cart
static uint32_t wamr_null0_load_font_tty(wasm_exec_env_t exec_env, char* filename, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return null0_load_font_tty(filename, glyphWidth, glyphHeight, characters);
}

// Load a TTY font from an image
static uint32_t wamr_null0_load_font_tty_from_image(wasm_exec_env_t exec_env, uint32_t image, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return null0_load_font_tty_from_image(image, glyphWidth, glyphHeight, characters);
}

// Load a TTF font from a file in cart
static uint32_t wamr_null0_load_font_ttf(wasm_exec_env_t exec_env, char* filename, int32_t fontSize) {
  return null0_load_font_ttf(filename, fontSize);
}

// Invert the colors in an image, in-place
static void wamr_null0_image_color_invert(wasm_exec_env_t exec_env, uint32_t image) {
  null0_image_color_invert(image);
}

// Calculate a rectangle representing the available alpha border in an image
static pntr_rectangle wamr_null0_image_alpha_border(wasm_exec_env_t exec_env, uint32_t image, float threshold) {
  return null0_image_alpha_border(image, threshold);
}

// Crop an image, in-place
static void wamr_null0_image_crop(wasm_exec_env_t exec_env, uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  null0_image_crop(image, x, y, width, height);
}

// Crop an image based on the alpha border, in-place
static void wamr_null0_image_alpha_crop(wasm_exec_env_t exec_env, uint32_t image, float threshold) {
  null0_image_alpha_crop(image, threshold);
}

// Adjust the brightness of an image, in-place
static void wamr_null0_image_color_brightness(wasm_exec_env_t exec_env, uint32_t image, float factor) {
  null0_image_color_brightness(image, factor);
}

// Flip an image, in-place
static void wamr_null0_image_flip(wasm_exec_env_t exec_env, uint32_t image, bool horizontal, bool vertical) {
  null0_image_flip(image, horizontal, vertical);
}

// Change the contrast of an image, in-place
static void wamr_null0_image_color_contrast(wasm_exec_env_t exec_env, uint32_t image, float contrast) {
  null0_image_color_contrast(image, contrast);
}

// Use an image as an alpha-mask on another image
static void wamr_null0_image_alpha_mask(wasm_exec_env_t exec_env, uint32_t image, uint32_t alphaMask, int32_t posX, int32_t posY) {
  null0_image_alpha_mask(image, alphaMask, posX, posY);
}

// Create a new image, rotating another image
static uint32_t wamr_null0_image_rotate(wasm_exec_env_t exec_env, uint32_t image, float degrees, pntr_filter filter) {
  return null0_image_rotate(image, degrees, filter);
}

// Create a new image of a gradient
static uint32_t wamr_null0_image_gradient(wasm_exec_env_t exec_env, int32_t width, int32_t height, uint32_t topLeft, uint32_t topRight, uint32_t bottomLeft, uint32_t bottomRight) {
  return null0_image_gradient(width, height, topLeft, topRight, bottomLeft, bottomRight);
}

// Unload an image
static void wamr_null0_unload_image(wasm_exec_env_t exec_env, uint32_t image) {
  null0_unload_image(image);
}

// Unload a font
static void wamr_null0_unload_font(wasm_exec_env_t exec_env, uint32_t font) {
  null0_unload_font(font);
}

// Clear an image
static void wamr_null0_clear_on_image(wasm_exec_env_t exec_env, uint32_t destination, uint32_t color) {
  null0_clear_on_image(destination, color);
}

// Draw a single pixel on an image
static void wamr_null0_draw_point_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t x, int32_t y, uint32_t color) {
  null0_draw_point_on_image(destination, x, y, color);
}

// Draw a line on an image
static void wamr_null0_draw_line_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, uint32_t color) {
  null0_draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color);
}

// Draw a filled rectangle on an image
static void wamr_null0_draw_rectangle_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {
  null0_draw_rectangle_on_image(destination, posX, posY, width, height, color);
}

// Draw a filled triangle on an image
static void wamr_null0_draw_triangle_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {
  null0_draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color);
}

// Draw a filled ellipse on an image
static void wamr_null0_draw_ellipse_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {
  null0_draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color);
}

// Draw a circle on an image
static void wamr_null0_draw_circle_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {
  null0_draw_circle_on_image(destination, centerX, centerY, radius, color);
}

// Draw a filled polygon on an image
static void wamr_null0_draw_polygon_on_image(wasm_exec_env_t exec_env, uint32_t destination, pntr_vector* points, int32_t numPoints, uint32_t color) {
  null0_draw_polygon_on_image(destination, points, numPoints, color);
}

// Draw several lines on an image
static void wamr_null0_draw_polyline_on_image(wasm_exec_env_t exec_env, uint32_t destination, pntr_vector* points, int32_t numPoints, uint32_t color) {
  null0_draw_polyline_on_image(destination, points, numPoints, color);
}

// Draw a filled round-rectangle on an image
static void wamr_null0_draw_rectangle_rounded_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {
  null0_draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color);
}

// Draw an image on an image
static void wamr_null0_draw_image_on_image(wasm_exec_env_t exec_env, uint32_t destination, uint32_t src, int32_t posX, int32_t posY) {
  null0_draw_image_on_image(destination, src, posX, posY);
}

// Draw a tinted image on an image
static void wamr_null0_draw_image_tint_on_image(wasm_exec_env_t exec_env, uint32_t destination, uint32_t src, int32_t posX, int32_t posY, uint32_t tint) {
  null0_draw_image_tint_on_image(destination, src, posX, posY, tint);
}

// Draw an image, rotated, on an image
static void wamr_null0_draw_image_rotated_on_image(wasm_exec_env_t exec_env, uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {
  null0_draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter);
}

// Draw an image, flipped, on an image
static void wamr_null0_draw_image_flipped_on_image(wasm_exec_env_t exec_env, uint32_t destination, uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  null0_draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

// Draw an image, scaled, on an image
static void wamr_null0_draw_image_scaled_on_image(wasm_exec_env_t exec_env, uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {
  null0_draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

// Draw some text on an image
static void wamr_null0_draw_text_on_image(wasm_exec_env_t exec_env, uint32_t destination, uint32_t font, char* text, int32_t posX, int32_t posY, uint32_t color) {
  null0_draw_text_on_image(destination, font, text, posX, posY, color);
}

// Draw a 1px outlined rectangle on the screen
static void wamr_null0_draw_rectangle_outline(wasm_exec_env_t exec_env, int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {
  null0_draw_rectangle_outline(posX, posY, width, height, color);
}

// Draw a 1px outlined triangle on the screen
static void wamr_null0_draw_triangle_outline(wasm_exec_env_t exec_env, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {
  null0_draw_triangle_outline(x1, y1, x2, y2, x3, y3, color);
}

// Draw a 1px outlined ellipse on the screen
static void wamr_null0_draw_ellipse_outline(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {
  null0_draw_ellipse_outline(centerX, centerY, radiusX, radiusY, color);
}

// Draw a 1px outlined circle on the screen
static void wamr_null0_draw_circle_outline(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {
  null0_draw_circle_outline(centerX, centerY, radius, color);
}

// Draw a 1px outlined polygon on the screen
static void wamr_null0_draw_polygon_outline(wasm_exec_env_t exec_env, pntr_vector* points, int32_t numPoints, uint32_t color) {
  null0_draw_polygon_outline(points, numPoints, color);
}

// Draw a 1px outlined arc on the screen
static void wamr_null0_draw_arc_outline(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, uint32_t color) {
  null0_draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, color);
}

// Draw a 1px outlined round-rectangle on the screen
static void wamr_null0_draw_rectangle_rounded_outline(wasm_exec_env_t exec_env, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {
  null0_draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, color);
}

// Draw a 1px outlined rectangle on an image
static void wamr_null0_draw_rectangle_outline_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {
  null0_draw_rectangle_outline_on_image(destination, posX, posY, width, height, color);
}

// Draw a 1px outlined triangle on an image
static void wamr_null0_draw_triangle_outline_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {
  null0_draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, color);
}

// Draw a 1px outlined ellipse on an image
static void wamr_null0_draw_ellipse_outline_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {
  null0_draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, color);
}

// Draw a 1px outlined circle on an image
static void wamr_null0_draw_circle_outline_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {
  null0_draw_circle_outline_on_image(destination, centerX, centerY, radius, color);
}

// Draw a 1px outlined polygon on an image
static void wamr_null0_draw_polygon_outline_on_image(wasm_exec_env_t exec_env, uint32_t destination, pntr_vector* points, int32_t numPoints, uint32_t color) {
  null0_draw_polygon_outline_on_image(destination, points, numPoints, color);
}

// Draw a 1px outlined round-rectangle on an image
static void wamr_null0_draw_rectangle_rounded_outline_on_image(wasm_exec_env_t exec_env, uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {
  null0_draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, color);
}

// FILESYSTEM

// Read a file from cart
static unsigned char* wamr_null0_file_read(wasm_exec_env_t exec_env, char* filename, uint32_t* bytesRead) {
  return null0_file_read(filename, bytesRead);
}

// Write a file to persistant storage
static bool wamr_null0_file_write(wasm_exec_env_t exec_env, char* filename, unsigned char* data, uint32_t byteSize) {
  return null0_file_write(filename, data, byteSize);
}

// Embed memory as a file
static bool wamr_null0_file_embed(wasm_exec_env_t exec_env, char* filename, unsigned char* data, uint32_t byteSize) {
  return null0_file_embed(filename, data, byteSize);
}

// COLORS

// Tint a color with another color
static uint32_t wamr_null0_color_tint(wasm_exec_env_t exec_env, uint32_t color, uint32_t tint) {
  return null0_color_tint(color, tint);
}

// Fade a color
static uint32_t wamr_null0_color_fade(wasm_exec_env_t exec_env, uint32_t color, float alpha) {
  return null0_color_fade(color, alpha);
}

// Change the brightness of a color
static uint32_t wamr_null0_color_brightness(wasm_exec_env_t exec_env, uint32_t color, float factor) {
  return null0_color_brightness(color, factor);
}

// Invert a color
static uint32_t wamr_null0_color_invert(wasm_exec_env_t exec_env, uint32_t color) {
  return null0_color_invert(color);
}

// Blend 2 colors together
static uint32_t wamr_null0_color_alpha_blend(wasm_exec_env_t exec_env, uint32_t dst, uint32_t src) {
  return null0_color_alpha_blend(dst, src);
}

// color_contrast
static uint32_t wamr_null0_color_contrast(wasm_exec_env_t exec_env, uint32_t color, float contrast) {
  return null0_color_contrast(color, contrast);
}

// Interpolate colors
static uint32_t wamr_null0_color_bilinear_interpolate(wasm_exec_env_t exec_env, uint32_t color00, uint32_t color01, uint32_t color10, uint32_t color11, float coordinateX, float coordinateY) {
  return null0_color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY);
}

bool null0_init_wamr(char* filename) {
  if (filename == NULL) {
    return false;
  }
  
  if (!null0_load_cart(filename)) {
    return false;
  }

  unsigned int bytesRead = 0;
  unsigned char* wasmBytes;

  wasmBytes = null0_file_read("/main.wasm", &bytesRead);

  return true;
}

  
// call when an event happens
void null0_event_wamr(pntr_app_event* event) {
}

// call on each frame
bool null0_upate_wamr(pntr_app* app, pntr_image* screen) {
  null0_update(app, screen);
  return true;
}

// call when your game exits
void null0_unload_wamr() {
  null0_unload();
}
