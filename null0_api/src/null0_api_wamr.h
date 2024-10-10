// this is the WAMR wrapper, for loading wasm on native

#include "null0_api.h"
#include "wasm_c_api.h"
#include "wasm_export.h"

wasm_exec_env_t exec_env;
wasm_module_inst_t module_inst;

// these callbacks are from the cart
wasm_function_inst_t cart_update = NULL;
wasm_function_inst_t cart_unload = NULL;
wasm_function_inst_t cart_buttonUp = NULL;
wasm_function_inst_t cart_buttonDown = NULL;
wasm_function_inst_t cart_keyUp = NULL;
wasm_function_inst_t cart_keyDown = NULL;

// over the WASM barrier I use RGBA always, so this converts in/out

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Null0WasmColor;

// translate outgoing color value over wasm
void color_from_pntr_to_wasm(pntr_color c, Null0WasmColor* colorOut) {
  colorOut->r = c.rgba.r;
  colorOut->g = c.rgba.g;
  colorOut->b = c.rgba.b;
  colorOut->a = c.rgba.a;
}

// translate incoming color value over wasm
pntr_color color_from_wasm_to_pntr(Null0WasmColor c) {
  return pntr_new_color(c.r, c.g, c.b, c.a);
}

// translate outgoing vector/dimensions value over wasm
void vector_from_pntr_to_wasm(pntr_vector v, pntr_vector* vOut) {
  memcpy(vOut, &v, sizeof(pntr_vector));
}

// translate outgoing rect value over wasm
void rect_from_pntr_to_wasm(pntr_rectangle r, pntr_rectangle* rOut) {
  memcpy(rOut, &r, sizeof(pntr_rectangle));
}

// translate outgoing FileInfo value over wasm
void fileinfo_from_physfs_to_wasm(PHYSFS_Stat f, PHYSFS_Stat* fOut) {
  memcpy(fOut, &f, sizeof(PHYSFS_Stat));
}

// translate outgoing SfxParams value over wasm
void params_from_sfx_to_wasm(SfxParams* s, SfxParams* sOut) {
  memcpy(sOut, s, sizeof(SfxParams));
}

// Read a file from cart (or local persistant)
static uint32_t wamr_null0_file_read(wasm_exec_env_t exec_env, char* filename, uint32_t* bytesRead) {
  char* bytes = null0_file_read(filename, bytesRead);
  return wasm_runtime_module_dup_data(module_inst, bytes, *bytesRead);
}

// Get the user's writable dir (where file writes or appends go)
static uint32_t wamr_null0_get_write_dir(wasm_exec_env_t exec_env) {
  char* d = null0_get_write_dir();
  int s = strlen(d);
  d[s] = 0;
  return wasm_runtime_module_dup_data(module_inst, d, s + 1);
}

// | GENERATED |

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
static float32_t wamr_null0_delta_time(wasm_exec_env_t exec_env) {
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
static void wamr_null0_play_sound(wasm_exec_env_t exec_env, int32_t sound, bool loop) {
  null0_play_sound(sound, loop);
}

// Stop a sound
static void wamr_null0_stop_sound(wasm_exec_env_t exec_env, int32_t sound) {
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
static void wamr_null0_randomize_sfx(wasm_exec_env_t exec_env, SfxParams* params, enum SfxWaveType waveType) {
  null0_randomize_sfx(params, waveType);
}

// Randomly mutate sfxr params
static void wamr_null0_mutate_sfx(wasm_exec_env_t exec_env, SfxParams* params, float32_t range, uint32_t mask) {
  null0_mutate_sfx(params, range, mask);
}

// Create a new sfxr from a .rfx file
static void wamr_null0_load_sfx(wasm_exec_env_t exec_env, SfxParams* params, char* filename) {
  SfxParams p = {};
  null0_load_sfx(&p, filename);
  memcpy(params, &p, sizeof(SfxParams));
}

// Unload a sound
static void wamr_null0_unload_sound(wasm_exec_env_t exec_env, int32_t sound) {
  null0_unload_sound(sound);
}

// INPUT

// Has the key been pressed? (tracks unpress/read correctly)
static bool wamr_null0_key_pressed(wasm_exec_env_t exec_env, int32_t key) {
  return null0_key_pressed(key);
}

// Is the key currently down?
static bool wamr_null0_key_down(wasm_exec_env_t exec_env, int32_t key) {
  return null0_key_down(key);
}

// Has the key been released? (tracks press/read correctly)
static bool wamr_null0_key_released(wasm_exec_env_t exec_env, int32_t key) {
  return null0_key_released(key);
}

// Is the key currently up?
static bool wamr_null0_key_up(wasm_exec_env_t exec_env, int32_t key) {
  return null0_key_up(key);
}

// Has the button been pressed? (tracks unpress/read correctly)
static bool wamr_null0_gamepad_button_pressed(wasm_exec_env_t exec_env, int32_t gamepad, int32_t button) {
  return null0_gamepad_button_pressed(gamepad, button);
}

// Is the button currently down?
static bool wamr_null0_gamepad_button_down(wasm_exec_env_t exec_env, int32_t gamepad, int32_t button) {
  return null0_gamepad_button_down(gamepad, button);
}

// Has the button been released? (tracks press/read correctly)
static bool wamr_null0_gamepad_button_released(wasm_exec_env_t exec_env, int32_t gamepad, int32_t button) {
  return null0_gamepad_button_released(gamepad, button);
}

// Get current position of mouse
static void wamr_null0_mouse_position(wasm_exec_env_t exec_env, pntr_vector* outVectorValue) {
  vector_from_pntr_to_wasm(null0_mouse_position(), outVectorValue);
}

// Has the button been pressed? (tracks unpress/read correctly)
static bool wamr_null0_mouse_button_pressed(wasm_exec_env_t exec_env, int32_t button) {
  return null0_mouse_button_pressed(button);
}

// Is the button currently down?
static bool wamr_null0_mouse_button_down(wasm_exec_env_t exec_env, int32_t button) {
  return null0_mouse_button_down(button);
}

// Has the button been released? (tracks press/read correctly)
static bool wamr_null0_mouse_button_released(wasm_exec_env_t exec_env, int32_t button) {
  return null0_mouse_button_released(button);
}

// Is the button currently up?
static bool wamr_null0_mouse_button_up(wasm_exec_env_t exec_env, int32_t button) {
  return null0_mouse_button_up(button);
}

// GRAPHICS

// Create a new blank image
static uint32_t wamr_null0_new_image(wasm_exec_env_t exec_env, int32_t width, int32_t height, Null0WasmColor* color) {
  return null0_new_image(width, height, color_from_wasm_to_pntr(*color));
}

// Copy an image to a new image
static uint32_t wamr_null0_image_copy(wasm_exec_env_t exec_env, int32_t image) {
  return null0_image_copy(image);
}

// Create an image from a region of another image
static uint32_t wamr_null0_image_subimage(wasm_exec_env_t exec_env, int32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  return null0_image_subimage(image, x, y, width, height);
}

// Clear the screen
static void wamr_null0_clear(wasm_exec_env_t exec_env, Null0WasmColor* color) {
  null0_clear(color_from_wasm_to_pntr(*color));
}

// Draw a single pixel on the screen
static void wamr_null0_draw_point(wasm_exec_env_t exec_env, int32_t x, int32_t y, Null0WasmColor* color) {
  null0_draw_point(x, y, color_from_wasm_to_pntr(*color));
}

// Draw a line on the screen
static void wamr_null0_draw_line(wasm_exec_env_t exec_env, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, Null0WasmColor* color) {
  null0_draw_line(startPosX, startPosY, endPosX, endPosY, color_from_wasm_to_pntr(*color));
}

// Draw a filled rectangle on the screen
static void wamr_null0_draw_rectangle(wasm_exec_env_t exec_env, int32_t posX, int32_t posY, int32_t width, int32_t height, Null0WasmColor* color) {
  null0_draw_rectangle(posX, posY, width, height, color_from_wasm_to_pntr(*color));
}

// Draw a filled triangle on the screen
static void wamr_null0_draw_triangle(wasm_exec_env_t exec_env, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Null0WasmColor* color) {
  null0_draw_triangle(x1, y1, x2, y2, x3, y3, color_from_wasm_to_pntr(*color));
}

// Draw a filled ellipse on the screen
static void wamr_null0_draw_ellipse(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Null0WasmColor* color) {
  null0_draw_ellipse(centerX, centerY, radiusX, radiusY, color_from_wasm_to_pntr(*color));
}

// Draw a filled circle on the screen
static void wamr_null0_draw_circle(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radius, Null0WasmColor* color) {
  null0_draw_circle(centerX, centerY, radius, color_from_wasm_to_pntr(*color));
}

// Draw a filled polygon on the screen
static void wamr_null0_draw_polygon(wasm_exec_env_t exec_env, pntr_vector* points, int32_t numPoints, Null0WasmColor* color) {
  null0_draw_polygon(points, numPoints, color_from_wasm_to_pntr(*color));
}

// Draw several lines on the screen
static void wamr_null0_draw_polyline(wasm_exec_env_t exec_env, pntr_vector* points, int32_t numPoints, Null0WasmColor* color) {
  null0_draw_polyline(points, numPoints, color_from_wasm_to_pntr(*color));
}

// Draw a filled arc on the screen
static void wamr_null0_draw_arc(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, float32_t radius, float32_t startAngle, float32_t endAngle, int32_t segments, Null0WasmColor* color) {
  null0_draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color_from_wasm_to_pntr(*color));
}

// Draw a filled round-rectangle on the screen
static void wamr_null0_draw_rectangle_rounded(wasm_exec_env_t exec_env, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Null0WasmColor* color) {
  null0_draw_rectangle_rounded(x, y, width, height, cornerRadius, color_from_wasm_to_pntr(*color));
}

// Draw an image on the screen
static void wamr_null0_draw_image(wasm_exec_env_t exec_env, int32_t src, int32_t posX, int32_t posY) {
  null0_draw_image(src, posX, posY);
}

// Draw a tinted image on the screen
static void wamr_null0_draw_image_tint(wasm_exec_env_t exec_env, int32_t src, int32_t posX, int32_t posY, Null0WasmColor* tint) {
  null0_draw_image_tint(src, posX, posY, color_from_wasm_to_pntr(*tint));
}

// Draw an image, rotated, on the screen
static void wamr_null0_draw_image_rotated(wasm_exec_env_t exec_env, int32_t src, int32_t posX, int32_t posY, float32_t degrees, float32_t offsetX, float32_t offsetY, int32_t filter) {
  null0_draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter);
}

// Draw an image, flipped, on the screen
static void wamr_null0_draw_image_flipped(wasm_exec_env_t exec_env, int32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  null0_draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

// Draw an image, scaled, on the screen
static void wamr_null0_draw_image_scaled(wasm_exec_env_t exec_env, int32_t src, int32_t posX, int32_t posY, float32_t scaleX, float32_t scaleY, float32_t offsetX, float32_t offsetY, int32_t filter) {
  null0_draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

// Draw some text on the screen
static void wamr_null0_draw_text(wasm_exec_env_t exec_env, int32_t font, char* text, int32_t posX, int32_t posY, Null0WasmColor* color) {
  null0_draw_text(font, text, posX, posY, color_from_wasm_to_pntr(*color));
}

// Save an image to persistant storage
static void wamr_null0_save_image(wasm_exec_env_t exec_env, int32_t image, char* filename) {
  null0_save_image(image, filename);
}

// Load an image from a file in cart
static uint32_t wamr_null0_load_image(wasm_exec_env_t exec_env, char* filename) {
  return null0_load_image(filename);
}

// Resize an image, in-place
static void wamr_null0_image_resize(wasm_exec_env_t exec_env, int32_t image, int32_t newWidth, int32_t newHeight, int32_t offsetX, int32_t offsetY, Null0WasmColor* fill) {
  null0_image_resize(image, newWidth, newHeight, offsetX, offsetY, color_from_wasm_to_pntr(*fill));
}

// Scale an image, in-place
static void wamr_null0_image_scale(wasm_exec_env_t exec_env, int32_t image, float32_t scaleX, float32_t scaleY, int32_t filter) {
  null0_image_scale(image, scaleX, scaleY, filter);
}

// Replace a color in an image, in-place
static void wamr_null0_image_color_replace(wasm_exec_env_t exec_env, int32_t image, Null0WasmColor* color, Null0WasmColor* replace) {
  null0_image_color_replace(image, color_from_wasm_to_pntr(*color), color_from_wasm_to_pntr(*replace));
}

// Tint a color in an image, in-place
static void wamr_null0_image_color_tint(wasm_exec_env_t exec_env, int32_t image, Null0WasmColor* color) {
  null0_image_color_tint(image, color_from_wasm_to_pntr(*color));
}

// Fade a color in an image, in-place
static void wamr_null0_image_color_fade(wasm_exec_env_t exec_env, int32_t image, float32_t alpha) {
  null0_image_color_fade(image, alpha);
}

// Copy a font to a new font
static uint32_t wamr_null0_font_copy(wasm_exec_env_t exec_env, int32_t font) {
  return null0_font_copy(font);
}

// Scale a font, return a new font
static uint32_t wamr_null0_font_scale(wasm_exec_env_t exec_env, int32_t font, float32_t scaleX, float32_t scaleY, int32_t filter) {
  return null0_font_scale(font, scaleX, scaleY, filter);
}

// Load a BMF font from a file in cart
static uint32_t wamr_null0_load_font_bmf(wasm_exec_env_t exec_env, char* filename, char* characters) {
  return null0_load_font_bmf(filename, characters);
}

// Load a BMF font from an image
static uint32_t wamr_null0_load_font_bmf_from_image(wasm_exec_env_t exec_env, int32_t image, char* characters) {
  return null0_load_font_bmf_from_image(image, characters);
}

// Measure the size of some text
static void wamr_null0_measure_text(wasm_exec_env_t exec_env, pntr_vector* outVectorValue, int32_t font, char* text) {
  vector_from_pntr_to_wasm(null0_measure_text(font, text), outVectorValue);
}

// Meaure an image (use 0 for screen)
static void wamr_null0_measure_image(wasm_exec_env_t exec_env, pntr_vector* outVectorValue, int32_t image) {
  vector_from_pntr_to_wasm(null0_measure_image(image), outVectorValue);
}

// Load a TTY font from a file in cart
static uint32_t wamr_null0_load_font_tty(wasm_exec_env_t exec_env, char* filename, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return null0_load_font_tty(filename, glyphWidth, glyphHeight, characters);
}

// Load a TTY font from an image
static uint32_t wamr_null0_load_font_tty_from_image(wasm_exec_env_t exec_env, int32_t image, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return null0_load_font_tty_from_image(image, glyphWidth, glyphHeight, characters);
}

// Load a TTF font from a file in cart
static uint32_t wamr_null0_load_font_ttf(wasm_exec_env_t exec_env, char* filename, int32_t fontSize) {
  return null0_load_font_ttf(filename, fontSize);
}

// Invert the colors in an image, in-place
static void wamr_null0_image_color_invert(wasm_exec_env_t exec_env, int32_t image) {
  null0_image_color_invert(image);
}

// Calculate a rectangle representing the available alpha border in an image
static void wamr_null0_image_alpha_border(wasm_exec_env_t exec_env, pntr_rectangle* outRectangleValue, int32_t image, float32_t threshold) {
  rect_from_pntr_to_wasm(null0_image_alpha_border(image, threshold), outRectangleValue);
}

// Crop an image, in-place
static void wamr_null0_image_crop(wasm_exec_env_t exec_env, int32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  null0_image_crop(image, x, y, width, height);
}

// Crop an image based on the alpha border, in-place
static void wamr_null0_image_alpha_crop(wasm_exec_env_t exec_env, int32_t image, float32_t threshold) {
  null0_image_alpha_crop(image, threshold);
}

// Adjust the brightness of an image, in-place
static void wamr_null0_image_color_brightness(wasm_exec_env_t exec_env, int32_t image, float32_t factor) {
  null0_image_color_brightness(image, factor);
}

// Flip an image, in-place
static void wamr_null0_image_flip(wasm_exec_env_t exec_env, int32_t image, bool horizontal, bool vertical) {
  null0_image_flip(image, horizontal, vertical);
}

// Change the contrast of an image, in-place
static void wamr_null0_image_color_contrast(wasm_exec_env_t exec_env, int32_t image, float32_t contrast) {
  null0_image_color_contrast(image, contrast);
}

// Use an image as an alpha-mask on another image
static void wamr_null0_image_alpha_mask(wasm_exec_env_t exec_env, int32_t image, int32_t alphaMask, int32_t posX, int32_t posY) {
  null0_image_alpha_mask(image, alphaMask, posX, posY);
}

// Create a new image, rotating another image
static uint32_t wamr_null0_image_rotate(wasm_exec_env_t exec_env, int32_t image, float32_t degrees, int32_t filter) {
  return null0_image_rotate(image, degrees, filter);
}

// Create a new image of a gradient
static uint32_t wamr_null0_image_gradient(wasm_exec_env_t exec_env, int32_t width, int32_t height, Null0WasmColor* topLeft, Null0WasmColor* topRight, Null0WasmColor* bottomLeft, Null0WasmColor* bottomRight) {
  return null0_image_gradient(width, height, color_from_wasm_to_pntr(*topLeft), color_from_wasm_to_pntr(*topRight), color_from_wasm_to_pntr(*bottomLeft), color_from_wasm_to_pntr(*bottomRight));
}

// Unload an image
static void wamr_null0_unload_image(wasm_exec_env_t exec_env, int32_t image) {
  null0_unload_image(image);
}

// Unload a font
static void wamr_null0_unload_font(wasm_exec_env_t exec_env, int32_t font) {
  null0_unload_font(font);
}

// Clear an image
static void wamr_null0_clear_on_image(wasm_exec_env_t exec_env, int32_t destination, Null0WasmColor* color) {
  null0_clear_on_image(destination, color_from_wasm_to_pntr(*color));
}

// Draw a single pixel on an image
static void wamr_null0_draw_point_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t x, int32_t y, Null0WasmColor* color) {
  null0_draw_point_on_image(destination, x, y, color_from_wasm_to_pntr(*color));
}

// Draw a line on an image
static void wamr_null0_draw_line_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, Null0WasmColor* color) {
  null0_draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color_from_wasm_to_pntr(*color));
}

// Draw a filled rectangle on an image
static void wamr_null0_draw_rectangle_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, Null0WasmColor* color) {
  null0_draw_rectangle_on_image(destination, posX, posY, width, height, color_from_wasm_to_pntr(*color));
}

// Draw a filled triangle on an image
static void wamr_null0_draw_triangle_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Null0WasmColor* color) {
  null0_draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color_from_wasm_to_pntr(*color));
}

// Draw a filled ellipse on an image
static void wamr_null0_draw_ellipse_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Null0WasmColor* color) {
  null0_draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color_from_wasm_to_pntr(*color));
}

// Draw a circle on an image
static void wamr_null0_draw_circle_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t centerX, int32_t centerY, int32_t radius, Null0WasmColor* color) {
  null0_draw_circle_on_image(destination, centerX, centerY, radius, color_from_wasm_to_pntr(*color));
}

// Draw a filled polygon on an image
static void wamr_null0_draw_polygon_on_image(wasm_exec_env_t exec_env, int32_t destination, pntr_vector* points, int32_t numPoints, Null0WasmColor* color) {
  null0_draw_polygon_on_image(destination, points, numPoints, color_from_wasm_to_pntr(*color));
}

// Draw several lines on an image
static void wamr_null0_draw_polyline_on_image(wasm_exec_env_t exec_env, int32_t destination, pntr_vector* points, int32_t numPoints, Null0WasmColor* color) {
  null0_draw_polyline_on_image(destination, points, numPoints, color_from_wasm_to_pntr(*color));
}

// Draw a filled round-rectangle on an image
static void wamr_null0_draw_rectangle_rounded_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Null0WasmColor* color) {
  null0_draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color_from_wasm_to_pntr(*color));
}

// Draw an image on an image
static void wamr_null0_draw_image_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t src, int32_t posX, int32_t posY) {
  null0_draw_image_on_image(destination, src, posX, posY);
}

// Draw a tinted image on an image
static void wamr_null0_draw_image_tint_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t src, int32_t posX, int32_t posY, Null0WasmColor* tint) {
  null0_draw_image_tint_on_image(destination, src, posX, posY, color_from_wasm_to_pntr(*tint));
}

// Draw an image, rotated, on an image
static void wamr_null0_draw_image_rotated_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t src, int32_t posX, int32_t posY, float32_t degrees, float32_t offsetX, float32_t offsetY, int32_t filter) {
  null0_draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter);
}

// Draw an image, flipped, on an image
static void wamr_null0_draw_image_flipped_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  null0_draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

// Draw an image, scaled, on an image
static void wamr_null0_draw_image_scaled_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t src, int32_t posX, int32_t posY, float32_t scaleX, float32_t scaleY, float32_t offsetX, float32_t offsetY, int32_t filter) {
  null0_draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

// Draw some text on an image
static void wamr_null0_draw_text_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t font, char* text, int32_t posX, int32_t posY, Null0WasmColor* color) {
  null0_draw_text_on_image(destination, font, text, posX, posY, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined rectangle on the screen
static void wamr_null0_draw_rectangle_outline(wasm_exec_env_t exec_env, int32_t posX, int32_t posY, int32_t width, int32_t height, Null0WasmColor* color) {
  null0_draw_rectangle_outline(posX, posY, width, height, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined triangle on the screen
static void wamr_null0_draw_triangle_outline(wasm_exec_env_t exec_env, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Null0WasmColor* color) {
  null0_draw_triangle_outline(x1, y1, x2, y2, x3, y3, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined ellipse on the screen
static void wamr_null0_draw_ellipse_outline(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Null0WasmColor* color) {
  null0_draw_ellipse_outline(centerX, centerY, radiusX, radiusY, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined circle on the screen
static void wamr_null0_draw_circle_outline(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, int32_t radius, Null0WasmColor* color) {
  null0_draw_circle_outline(centerX, centerY, radius, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined polygon on the screen
static void wamr_null0_draw_polygon_outline(wasm_exec_env_t exec_env, pntr_vector* points, int32_t numPoints, Null0WasmColor* color) {
  null0_draw_polygon_outline(points, numPoints, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined arc on the screen
static void wamr_null0_draw_arc_outline(wasm_exec_env_t exec_env, int32_t centerX, int32_t centerY, float32_t radius, float32_t startAngle, float32_t endAngle, int32_t segments, Null0WasmColor* color) {
  null0_draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined round-rectangle on the screen
static void wamr_null0_draw_rectangle_rounded_outline(wasm_exec_env_t exec_env, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Null0WasmColor* color) {
  null0_draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined rectangle on an image
static void wamr_null0_draw_rectangle_outline_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, Null0WasmColor* color) {
  null0_draw_rectangle_outline_on_image(destination, posX, posY, width, height, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined triangle on an image
static void wamr_null0_draw_triangle_outline_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Null0WasmColor* color) {
  null0_draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined ellipse on an image
static void wamr_null0_draw_ellipse_outline_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Null0WasmColor* color) {
  null0_draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined circle on an image
static void wamr_null0_draw_circle_outline_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t centerX, int32_t centerY, int32_t radius, Null0WasmColor* color) {
  null0_draw_circle_outline_on_image(destination, centerX, centerY, radius, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined polygon on an image
static void wamr_null0_draw_polygon_outline_on_image(wasm_exec_env_t exec_env, int32_t destination, pntr_vector* points, int32_t numPoints, Null0WasmColor* color) {
  null0_draw_polygon_outline_on_image(destination, points, numPoints, color_from_wasm_to_pntr(*color));
}

// Draw a 1px outlined round-rectangle on an image
static void wamr_null0_draw_rectangle_rounded_outline_on_image(wasm_exec_env_t exec_env, int32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Null0WasmColor* color) {
  null0_draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, color_from_wasm_to_pntr(*color));
}

// FILESYSTEM

// Write a file to persistant storage
static bool wamr_null0_file_write(wasm_exec_env_t exec_env, char* filename, unsigned char* data, uint32_t byteSize) {
  return null0_file_write(filename, data, byteSize);
}

// Write a file to persistant storage, appending to the end
static bool wamr_null0_file_append(wasm_exec_env_t exec_env, char* filename, unsigned char* data, uint32_t byteSize) {
  return null0_file_append(filename, data, byteSize);
}

// Get info about a single file
static void wamr_null0_file_info(wasm_exec_env_t exec_env, PHYSFS_Stat* outFileInfoValue, char* filename) {
  fileinfo_from_physfs_to_wasm(null0_file_info(filename), outFileInfoValue);
}

// Get list of files in a directory
static char** wamr_null0_file_list(wasm_exec_env_t exec_env, char* dir) {
  return null0_file_list(dir);
}

// COLORS

// Tint a color with another color
static void wamr_null0_color_tint(wasm_exec_env_t exec_env, Null0WasmColor* outColorValue, Null0WasmColor* color, Null0WasmColor* tint) {
  color_from_pntr_to_wasm(null0_color_tint(color_from_wasm_to_pntr(*color), color_from_wasm_to_pntr(*tint)), outColorValue);
}

// Fade a color
static void wamr_null0_color_fade(wasm_exec_env_t exec_env, Null0WasmColor* outColorValue, Null0WasmColor* color, float32_t alpha) {
  color_from_pntr_to_wasm(null0_color_fade(color_from_wasm_to_pntr(*color), alpha), outColorValue);
}

// Change the brightness of a color
static void wamr_null0_color_brightness(wasm_exec_env_t exec_env, Null0WasmColor* outColorValue, Null0WasmColor* color, float32_t factor) {
  color_from_pntr_to_wasm(null0_color_brightness(color_from_wasm_to_pntr(*color), factor), outColorValue);
}

// Invert a color
static void wamr_null0_color_invert(wasm_exec_env_t exec_env, Null0WasmColor* outColorValue, Null0WasmColor* color) {
  color_from_pntr_to_wasm(null0_color_invert(color_from_wasm_to_pntr(*color)), outColorValue);
}

// Blend 2 colors together
static void wamr_null0_color_alpha_blend(wasm_exec_env_t exec_env, Null0WasmColor* outColorValue, Null0WasmColor* dst, Null0WasmColor* src) {
  color_from_pntr_to_wasm(null0_color_alpha_blend(color_from_wasm_to_pntr(*dst), color_from_wasm_to_pntr(*src)), outColorValue);
}

// color_contrast
static void wamr_null0_color_contrast(wasm_exec_env_t exec_env, Null0WasmColor* outColorValue, Null0WasmColor* color, float32_t contrast) {
  color_from_pntr_to_wasm(null0_color_contrast(color_from_wasm_to_pntr(*color), contrast), outColorValue);
}

// Interpolate colors
static void wamr_null0_color_bilinear_interpolate(wasm_exec_env_t exec_env, Null0WasmColor* outColorValue, Null0WasmColor* color00, Null0WasmColor* color01, Null0WasmColor* color10, Null0WasmColor* color11, float32_t coordinateX, float32_t coordinateY) {
  color_from_pntr_to_wasm(null0_color_bilinear_interpolate(color_from_wasm_to_pntr(*color00), color_from_wasm_to_pntr(*color01), color_from_wasm_to_pntr(*color10), color_from_wasm_to_pntr(*color11), coordinateX, coordinateY), outColorValue);
}

static NativeSymbol null0_wamr_callbacks[] = {
    {"file_read", wamr_null0_file_read, "($*)i"},
    {"get_write_dir", wamr_null0_get_write_dir, "()i"},
    {"trace", wamr_null0_trace, "($)"},
    {"current_time", wamr_null0_current_time, "()I"},
    {"delta_time", wamr_null0_delta_time, "()f"},
    {"random_int", wamr_null0_random_int, "(ii)i"},
    {"load_sound", wamr_null0_load_sound, "($)i"},
    {"play_sound", wamr_null0_play_sound, "(ii)"},
    {"stop_sound", wamr_null0_stop_sound, "(i)"},
    {"new_sfx", wamr_null0_new_sfx, "(*)i"},
    {"preset_sfx", wamr_null0_preset_sfx, "(*i)"},
    {"randomize_sfx", wamr_null0_randomize_sfx, "(*i)"},
    {"mutate_sfx", wamr_null0_mutate_sfx, "(*fi)"},
    {"load_sfx", wamr_null0_load_sfx, "(*$)"},
    {"unload_sound", wamr_null0_unload_sound, "(i)"},
    {"key_pressed", wamr_null0_key_pressed, "(i)i"},
    {"key_down", wamr_null0_key_down, "(i)i"},
    {"key_released", wamr_null0_key_released, "(i)i"},
    {"key_up", wamr_null0_key_up, "(i)i"},
    {"gamepad_button_pressed", wamr_null0_gamepad_button_pressed, "(ii)i"},
    {"gamepad_button_down", wamr_null0_gamepad_button_down, "(ii)i"},
    {"gamepad_button_released", wamr_null0_gamepad_button_released, "(ii)i"},
    {"mouse_position", wamr_null0_mouse_position, "(*)"},
    {"mouse_button_pressed", wamr_null0_mouse_button_pressed, "(i)i"},
    {"mouse_button_down", wamr_null0_mouse_button_down, "(i)i"},
    {"mouse_button_released", wamr_null0_mouse_button_released, "(i)i"},
    {"mouse_button_up", wamr_null0_mouse_button_up, "(i)i"},
    {"new_image", wamr_null0_new_image, "(ii*)i"},
    {"image_copy", wamr_null0_image_copy, "(i)i"},
    {"image_subimage", wamr_null0_image_subimage, "(iiiii)i"},
    {"clear", wamr_null0_clear, "(*)"},
    {"draw_point", wamr_null0_draw_point, "(ii*)"},
    {"draw_line", wamr_null0_draw_line, "(iiii*)"},
    {"draw_rectangle", wamr_null0_draw_rectangle, "(iiii*)"},
    {"draw_triangle", wamr_null0_draw_triangle, "(iiiiii*)"},
    {"draw_ellipse", wamr_null0_draw_ellipse, "(iiii*)"},
    {"draw_circle", wamr_null0_draw_circle, "(iii*)"},
    {"draw_polygon", wamr_null0_draw_polygon, "(*i*)"},
    {"draw_polyline", wamr_null0_draw_polyline, "(*i*)"},
    {"draw_arc", wamr_null0_draw_arc, "(iifffi*)"},
    {"draw_rectangle_rounded", wamr_null0_draw_rectangle_rounded, "(iiiii*)"},
    {"draw_image", wamr_null0_draw_image, "(iii)"},
    {"draw_image_tint", wamr_null0_draw_image_tint, "(iii*)"},
    {"draw_image_rotated", wamr_null0_draw_image_rotated, "(iiifffi)"},
    {"draw_image_flipped", wamr_null0_draw_image_flipped, "(iiiiii)"},
    {"draw_image_scaled", wamr_null0_draw_image_scaled, "(iiiffffi)"},
    {"draw_text", wamr_null0_draw_text, "(i$ii*)"},
    {"save_image", wamr_null0_save_image, "(i$)"},
    {"load_image", wamr_null0_load_image, "($)i"},
    {"image_resize", wamr_null0_image_resize, "(iiiii*)"},
    {"image_scale", wamr_null0_image_scale, "(iffi)"},
    {"image_color_replace", wamr_null0_image_color_replace, "(i**)"},
    {"image_color_tint", wamr_null0_image_color_tint, "(i*)"},
    {"image_color_fade", wamr_null0_image_color_fade, "(if)"},
    {"font_copy", wamr_null0_font_copy, "(i)i"},
    {"font_scale", wamr_null0_font_scale, "(iffi)i"},
    {"load_font_bmf", wamr_null0_load_font_bmf, "($)i"},
    {"load_font_bmf_from_image", wamr_null0_load_font_bmf_from_image, "(i$)i"},
    {"measure_text", wamr_null0_measure_text, "(*i$)"},
    {"measure_image", wamr_null0_measure_image, "(*i)"},
    {"load_font_tty", wamr_null0_load_font_tty, "($ii$)i"},
    {"load_font_tty_from_image", wamr_null0_load_font_tty_from_image, "(iii$)i"},
    {"load_font_ttf", wamr_null0_load_font_ttf, "($i)i"},
    {"image_color_invert", wamr_null0_image_color_invert, "(i)"},
    {"image_alpha_border", wamr_null0_image_alpha_border, "(*if)"},
    {"image_crop", wamr_null0_image_crop, "(iiiii)"},
    {"image_alpha_crop", wamr_null0_image_alpha_crop, "(if)"},
    {"image_color_brightness", wamr_null0_image_color_brightness, "(if)"},
    {"image_flip", wamr_null0_image_flip, "(iii)"},
    {"image_color_contrast", wamr_null0_image_color_contrast, "(if)"},
    {"image_alpha_mask", wamr_null0_image_alpha_mask, "(iiii)"},
    {"image_rotate", wamr_null0_image_rotate, "(ifi)i"},
    {"image_gradient", wamr_null0_image_gradient, "(ii****)i"},
    {"unload_image", wamr_null0_unload_image, "(i)"},
    {"unload_font", wamr_null0_unload_font, "(i)"},
    {"clear_on_image", wamr_null0_clear_on_image, "(i*)"},
    {"draw_point_on_image", wamr_null0_draw_point_on_image, "(iii*)"},
    {"draw_line_on_image", wamr_null0_draw_line_on_image, "(iiiii*)"},
    {"draw_rectangle_on_image", wamr_null0_draw_rectangle_on_image, "(iiiii*)"},
    {"draw_triangle_on_image", wamr_null0_draw_triangle_on_image, "(iiiiiii*)"},
    {"draw_ellipse_on_image", wamr_null0_draw_ellipse_on_image, "(iiiii*)"},
    {"draw_circle_on_image", wamr_null0_draw_circle_on_image, "(iiii*)"},
    {"draw_polygon_on_image", wamr_null0_draw_polygon_on_image, "(i*i*)"},
    {"draw_polyline_on_image", wamr_null0_draw_polyline_on_image, "(i*i*)"},
    {"draw_rectangle_rounded_on_image", wamr_null0_draw_rectangle_rounded_on_image, "(iiiiii*)"},
    {"draw_image_on_image", wamr_null0_draw_image_on_image, "(iiii)"},
    {"draw_image_tint_on_image", wamr_null0_draw_image_tint_on_image, "(iiii*)"},
    {"draw_image_rotated_on_image", wamr_null0_draw_image_rotated_on_image, "(iiiifffi)"},
    {"draw_image_flipped_on_image", wamr_null0_draw_image_flipped_on_image, "(iiiiiii)"},
    {"draw_image_scaled_on_image", wamr_null0_draw_image_scaled_on_image, "(iiiiffffi)"},
    {"draw_text_on_image", wamr_null0_draw_text_on_image, "(ii$ii*)"},
    {"draw_rectangle_outline", wamr_null0_draw_rectangle_outline, "(iiii*)"},
    {"draw_triangle_outline", wamr_null0_draw_triangle_outline, "(iiiiii*)"},
    {"draw_ellipse_outline", wamr_null0_draw_ellipse_outline, "(iiii*)"},
    {"draw_circle_outline", wamr_null0_draw_circle_outline, "(iii*)"},
    {"draw_polygon_outline", wamr_null0_draw_polygon_outline, "(*i*)"},
    {"draw_arc_outline", wamr_null0_draw_arc_outline, "(iifffi*)"},
    {"draw_rectangle_rounded_outline", wamr_null0_draw_rectangle_rounded_outline, "(iiiii*)"},
    {"draw_rectangle_outline_on_image", wamr_null0_draw_rectangle_outline_on_image, "(iiiii*)"},
    {"draw_triangle_outline_on_image", wamr_null0_draw_triangle_outline_on_image, "(iiiiiii*)"},
    {"draw_ellipse_outline_on_image", wamr_null0_draw_ellipse_outline_on_image, "(iiiii*)"},
    {"draw_circle_outline_on_image", wamr_null0_draw_circle_outline_on_image, "(iiii*)"},
    {"draw_polygon_outline_on_image", wamr_null0_draw_polygon_outline_on_image, "(i*i*)"},
    {"draw_rectangle_rounded_outline_on_image", wamr_null0_draw_rectangle_rounded_outline_on_image, "(iiiiii*)"},
    {"file_write", wamr_null0_file_write, "($*~)i"},
    {"file_append", wamr_null0_file_append, "($*~)i"},
    {"file_info", wamr_null0_file_info, "(*$)"},
    {"file_list", wamr_null0_file_list, "($)*"},
    {"color_tint", wamr_null0_color_tint, "(***)"},
    {"color_fade", wamr_null0_color_fade, "(**f)"},
    {"color_brightness", wamr_null0_color_brightness, "(**f)"},
    {"color_invert", wamr_null0_color_invert, "(**)"},
    {"color_alpha_blend", wamr_null0_color_alpha_blend, "(***)"},
    {"color_contrast", wamr_null0_color_contrast, "(**f)"},
    {"color_bilinear_interpolate", wamr_null0_color_bilinear_interpolate, "(*****ff)"}};

// | END GENERATED |

RuntimeInitArgs null0_init_args() {
  RuntimeInitArgs init_args;
  memset(&init_args, 0, sizeof(RuntimeInitArgs));

  static char global_heap_buf[512 * 1024];
  uint32_t stack_size = 8092, heap_size = 8092;

  init_args.mem_alloc_type = Alloc_With_Pool;
  init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
  init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

  init_args.n_native_symbols = sizeof(null0_wamr_callbacks) / sizeof(NativeSymbol);
  init_args.native_module_name = "null0";
  init_args.native_symbols = null0_wamr_callbacks;
  return init_args;
}

// setup WAMR host
bool null0_init() {
  unsigned int bytesRead = 0;
  unsigned char* wasmBytes;

  wasmBytes = null0_file_read("/main.wasm", &bytesRead);

  if (wasmBytes == NULL) {
    fprintf(stderr, "ERROR: Could not read main.wasm\n");
    return false;
  }

  RuntimeInitArgs init_args = null0_init_args();

  if (!wasm_runtime_full_init(&init_args)) {
    fprintf(stderr, "ERROR: Init runtime environment failed.\n");
    return false;
  }

  uint32_t stack_size = 8092, heap_size = 8092;
  unsigned long wasmSize = (unsigned long)bytesRead;
  char error_buf[128];

  error_buf[0] = 0;
  wasm_module_t module = wasm_runtime_load(wasmBytes, wasmSize, error_buf, 128);
  if (error_buf[0] != 0) {
    fprintf(stderr, "ERROR: load - %s\n", error_buf);
    return false;
  }

  error_buf[0] = 0;
  module_inst = wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, 128);
  if (error_buf[0] != 0) {
    fprintf(stderr, "ERROR: instantiate - %s\n", error_buf);
    return false;
  }

  exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);

  cart_update = wasm_runtime_lookup_function(module_inst, "update");
  cart_buttonUp = wasm_runtime_lookup_function(module_inst, "buttonUp");
  cart_buttonDown = wasm_runtime_lookup_function(module_inst, "buttonDown");
  cart_keyUp = wasm_runtime_lookup_function(module_inst, "keyUp");
  cart_keyDown = wasm_runtime_lookup_function(module_inst, "keyDown");

  // this is for hosts that seperate init
  wasm_function_inst_t cart_init = NULL;
  cart_init = wasm_runtime_lookup_function(module_inst, "load");
  if (cart_init != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_init, 0, NULL)) {
      // not fatal, but this will help with troubleshooting
      printf("load: %s\n", wasm_runtime_get_exception(module_inst));
    }
  }

  wasm_application_execute_main(module_inst, 0, NULL);

  return true;
}

// call cart's update
bool null0_update() {
  if (cart_update != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_update, 0, NULL)) {
      // not fatal, but this will help with troubleshooting
      printf("update: %s\n", wasm_runtime_get_exception(module_inst));
    }
  }
  return true;
}

// call cart's unload
void null0_unload() {
  if (cart_unload != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_unload, 0, NULL)) {
      // not fatal, but this will help with troubleshooting
      printf("unload: %s\n", wasm_runtime_get_exception(module_inst));
    }
  }
}

// call cart's event callbacks
void null0_event(pntr_app_event* event) {
  uint32_t argv[1];
  if (cart_keyDown) {
    if (event->type == PNTR_APP_EVENTTYPE_KEY_DOWN) {
      argv[0] = event->key;
      wasm_runtime_call_wasm(exec_env, cart_keyDown, 1, argv);
    }
  }
  if (cart_keyUp) {
    if (event->type == PNTR_APP_EVENTTYPE_KEY_UP) {
      argv[0] = event->key;
      wasm_runtime_call_wasm(exec_env, cart_keyUp, 1, argv);
    }
  }
  if (cart_buttonDown) {
    if (event->type == PNTR_APP_EVENTTYPE_KEY_DOWN) {
      int b = null0_button_map_key(event->key);
      if (b != -1) {
        argv[0] = b;
        wasm_runtime_call_wasm(exec_env, cart_buttonDown, 1, argv);
      }
    }
    if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN) {
      argv[0] = event->gamepadButton;
      wasm_runtime_call_wasm(exec_env, cart_buttonDown, 1, argv);
    }
  }
  if (cart_buttonUp) {
    if (event->type == PNTR_APP_EVENTTYPE_KEY_UP) {
      int b = null0_button_map_key(event->key);
      if (b != -1) {
        argv[0] = b;
        wasm_runtime_call_wasm(exec_env, cart_buttonUp, 1, argv);
      }
    }
    if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP) {
      argv[0] = event->gamepadButton;
      wasm_runtime_call_wasm(exec_env, cart_buttonUp, 1, argv);
    }
  }
}
