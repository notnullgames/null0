// This is the API for null0 carts

#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL0_EXPORT(n) __attribute__((export_name(n)))
#define NULL0_IMPORT(n) __attribute__((import_module("null0"), import_name(n)))

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;

NULL0_EXPORT("malloc")
void* _null0_malloc(size_t size) {
  return malloc(size);
}

NULL0_EXPORT("free")
void _null0_free(void* ptr) {
  free(ptr);
}

typedef struct {
  u32 width;
  u32 height;
} Dimensions;

typedef struct {
  i32 x;
  i32 y;
} Vector;

typedef struct {
  i32 x;
  i32 y;
  i32 width;
  i32 height;
} Rectangle;

// Sound parameters (96 bytes matching rFXGen WaveParams)
typedef struct SfxParams {
  // Random seed used to generate the wave
  uint32_t randSeed;

  // Wave type (square, sawtooth, sine, noise)
  int waveType;

  // Wave envelope parameters
  float attackTime;
  float sustainTime;
  float sustainPunch;
  float decayTime;

  // Frequency parameters
  float startFrequency;
  float minFrequency;
  float slide;
  float deltaSlide;
  float vibratoDepth;
  float vibratoSpeed;
  // float vibratoPhaseDelay;      // Unused in sfxr code.

  // Tone change parameters
  float changeAmount;
  float changeSpeed;

  // Square wave parameters
  float squareDuty;
  float dutySweep;

  // Repeat parameters
  float repeatSpeed;

  // Phaser parameters
  float phaserOffset;
  float phaserSweep;

  // Filter parameters
  float lpfCutoff;
  float lpfCutoffSweep;
  float lpfResonance;
  float hpfCutoff;
  float hpfCutoffSweep;
} SfxParams;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

typedef enum ImageFilter {
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR,
  FILTER_SMOOTH
} ImageFilter;

typedef enum Key {
  KEY_INVALID = 0,
  KEY_SPACE = 32,
  KEY_APOSTROPHE = 39,
  KEY_COMMA = 44,
  KEY_MINUS = 45,
  KEY_PERIOD = 46,
  KEY_SLASH = 47,
  KEY_0 = 48,
  KEY_1 = 49,
  KEY_2 = 50,
  KEY_3 = 51,
  KEY_4 = 52,
  KEY_5 = 53,
  KEY_6 = 54,
  KEY_7 = 55,
  KEY_8 = 56,
  KEY_9 = 57,
  KEY_SEMICOLON = 59,
  KEY_EQUAL = 61,
  KEY_A = 65,
  KEY_B = 66,
  KEY_C = 67,
  KEY_D = 68,
  KEY_E = 69,
  KEY_F = 70,
  KEY_G = 71,
  KEY_H = 72,
  KEY_I = 73,
  KEY_J = 74,
  KEY_K = 75,
  KEY_L = 76,
  KEY_M = 77,
  KEY_N = 78,
  KEY_O = 79,
  KEY_P = 80,
  KEY_Q = 81,
  KEY_R = 82,
  KEY_S = 83,
  KEY_T = 84,
  KEY_U = 85,
  KEY_V = 86,
  KEY_W = 87,
  KEY_X = 88,
  KEY_Y = 89,
  KEY_Z = 90,
  KEY_LEFT_BRACKET = 91,
  KEY_BACKSLASH = 92,
  KEY_RIGHT_BRACKET = 93,
  KEY_GRAVE_ACCENT = 96,
  KEY_WORLD_1 = 161,
  KEY_WORLD_2 = 162,
  KEY_ESCAPE = 256,
  KEY_ENTER = 257,
  KEY_TAB = 258,
  KEY_BACKSPACE = 259,
  KEY_INSERT = 260,
  KEY_DELETE = 261,
  KEY_RIGHT = 262,
  KEY_LEFT = 263,
  KEY_DOWN = 264,
  KEY_UP = 265,
  KEY_PAGE_UP = 266,
  KEY_PAGE_DOWN = 267,
  KEY_HOME = 268,
  KEY_END = 269,
  KEY_CAPS_LOCK = 280,
  KEY_SCROLL_LOCK = 281,
  KEY_NUM_LOCK = 282,
  KEY_PRINT_SCREEN = 283,
  KEY_PAUSE = 284,
  KEY_F1 = 290,
  KEY_F2 = 291,
  KEY_F3 = 292,
  KEY_F4 = 293,
  KEY_F5 = 294,
  KEY_F6 = 295,
  KEY_F7 = 296,
  KEY_F8 = 297,
  KEY_F9 = 298,
  KEY_F10 = 299,
  KEY_F11 = 300,
  KEY_F12 = 301,
  KEY_F13 = 302,
  KEY_F14 = 303,
  KEY_F15 = 304,
  KEY_F16 = 305,
  KEY_F17 = 306,
  KEY_F18 = 307,
  KEY_F19 = 308,
  KEY_F20 = 309,
  KEY_F21 = 310,
  KEY_F22 = 311,
  KEY_F23 = 312,
  KEY_F24 = 313,
  KEY_F25 = 314,
  KEY_KP_0 = 320,
  KEY_KP_1 = 321,
  KEY_KP_2 = 322,
  KEY_KP_3 = 323,
  KEY_KP_4 = 324,
  KEY_KP_5 = 325,
  KEY_KP_6 = 326,
  KEY_KP_7 = 327,
  KEY_KP_8 = 328,
  KEY_KP_9 = 329,
  KEY_KP_DECIMAL = 330,
  KEY_KP_DIVIDE = 331,
  KEY_KP_MULTIPLY = 332,
  KEY_KP_SUBTRACT = 333,
  KEY_KP_ADD = 334,
  KEY_KP_ENTER = 335,
  KEY_KP_EQUAL = 336,
  KEY_LEFT_SHIFT = 340,
  KEY_LEFT_CONTROL = 341,
  KEY_LEFT_ALT = 342,
  KEY_LEFT_SUPER = 343,
  KEY_RIGHT_SHIFT = 344,
  KEY_RIGHT_CONTROL = 345,
  KEY_RIGHT_ALT = 346,
  KEY_RIGHT_SUPER = 347,
  KEY_MENU = 348,
} Key;

typedef enum GamepadButton {
  GAMEPAD_BUTTON_UNKNOWN = 0,     // Unknown button, just for error checking
  GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
  GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
  GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
  GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
  GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
  GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
  GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
  GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
  GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
  GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
} GamepadButton;

typedef enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3,
} MouseButton;

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
  SFX_SYNTH
} SfxPresetType;

typedef enum SfxWaveType {
  SFX_SQUARE,
  SFX_SAWTOOTH,
  SFX_SINE,
  SFX_NOISE,
  SFX_TRIANGLE,
  SFX_PINK_NOISE
} SfxWaveType;

typedef enum FileType {
  FILETYPE_REGULAR,   /**< a normal file */
  FILETYPE_DIRECTORY, /**< a directory */
  FILETYPE_SYMLINK,   /**< a symlink */
  FILETYPE_OTHER      /**< something completely different like a device */
} FileType;

typedef struct FileInfo {
  i64 filesize;      /**< size in bytes, -1 for non-files and unknown */
  i64 modtime;       /**< last modification time */
  i64 createtime;    /**< like modtime, but for file creation time */
  i64 accesstime;    /**< like modtime, but for file access time */
  FileType filetype; /**< File? Directory? Symlink? */
  bool readonly;     /**< non-zero if read only, zero if writable. */
} FileInfo;

#define WIDTH 320
#define HEIGHT 240

Color LIGHTGRAY = (Color){.r = 200, .g = 200, .b = 200, .a = 255};
Color GRAY = (Color){.r = 130, .g = 130, .b = 130, .a = 255};
Color DARKGRAY = (Color){.r = 80, .g = 80, .b = 80, .a = 255};
Color YELLOW = (Color){.r = 253, .g = 249, .b = 0, .a = 255};
Color GOLD = (Color){.r = 255, .g = 203, .b = 0, .a = 255};
Color ORANGE = (Color){.r = 255, .g = 161, .b = 0, .a = 255};
Color PINK = (Color){.r = 255, .g = 109, .b = 194, .a = 255};
Color RED = (Color){.r = 230, .g = 41, .b = 55, .a = 255};
Color MAROON = (Color){.r = 190, .g = 33, .b = 55, .a = 255};
Color GREEN = (Color){.r = 0, .g = 228, .b = 48, .a = 255};
Color LIME = (Color){.r = 0, .g = 158, .b = 47, .a = 255};
Color DARKGREEN = (Color){.r = 0, .g = 117, .b = 44, .a = 255};
Color SKYBLUE = (Color){.r = 102, .g = 191, .b = 255, .a = 255};
Color BLUE = (Color){.r = 0, .g = 121, .b = 241, .a = 255};
Color DARKBLUE = (Color){.r = 0, .g = 82, .b = 172, .a = 255};
Color PURPLE = (Color){.r = 200, .g = 122, .b = 255, .a = 255};
Color VIOLET = (Color){.r = 135, .g = 60, .b = 190, .a = 255};
Color DARKPURPLE = (Color){.r = 112, .g = 31, .b = 126, .a = 255};
Color BEIGE = (Color){.r = 211, .g = 176, .b = 131, .a = 255};
Color BROWN = (Color){.r = 127, .g = 106, .b = 79, .a = 255};
Color DARKBROWN = (Color){.r = 76, .g = 63, .b = 47, .a = 255};
Color WHITE = (Color){.r = 255, .g = 255, .b = 255, .a = 255};
Color BLACK = (Color){.r = 0, .g = 0, .b = 0, .a = 255};
Color BLANK = (Color){.r = 0, .g = 0, .b = 0, .a = 0};
Color MAGENTA = (Color){.r = 255, .g = 0, .b = 255, .a = 255};
Color RAYWHITE = (Color){.r = 245, .g = 245, .b = 245, .a = 255};

// max-size for trace messages
#ifndef NULL0_TRACE_SIZE
#define NULL0_TRACE_SIZE 1024 * 1024 * 1024
#endif

NULL0_IMPORT("trace")
void _null0_trace_real(char* str);

char null0_traceBuffer[NULL0_TRACE_SIZE];

// Log a string (using printf-style)
void trace(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(null0_traceBuffer, NULL0_TRACE_SIZE, format, args);
  va_end(args);
  _null0_trace_real(null0_traceBuffer);
}

// | GENERATED |

/////////// UTILITIES ///////////

// Get system-time (ms) since unix epoch
NULL0_IMPORT("current_time")
u64 current_time();

// Get the change in time (seconds) since the last update run
NULL0_IMPORT("delta_time")
f32 delta_time();

// Get a random integer between 2 numbers
NULL0_IMPORT("random_int")
i32 random_int(i32 min, i32 max);

/////////// SOUND ///////////

// Load a sound from a file in cart
NULL0_IMPORT("load_sound")
u32 load_sound(char* filename);

// Play a sound
NULL0_IMPORT("play_sound")
void play_sound(u32 sound, bool loop);

// Stop a sound
NULL0_IMPORT("stop_sound")
void stop_sound(u32 sound);

// Create a new sound-effect from some sfxr params
NULL0_IMPORT("new_sfx")
u32 new_sfx(SfxParams* params);

// Generate randomized preset sfxr params
NULL0_IMPORT("preset_sfx")
void preset_sfx(SfxParams* params, SfxPresetType type);

// Randomize sfxr params
NULL0_IMPORT("randomize_sfx")
void randomize_sfx(SfxParams* params, SfxWaveType waveType);

// Randomly mutate sfxr params
NULL0_IMPORT("mutate_sfx")
void mutate_sfx(SfxParams* params, f32 range, u32 mask);

// Create a new sfxr from a .rfx file
NULL0_IMPORT("load_sfx")
void load_sfx(SfxParams* ret, char* filename);

// Unload a sound
NULL0_IMPORT("unload_sound")
void unload_sound(u32 sound);

/////////// INPUT ///////////

// Has the key been pressed? (tracks unpress/read correctly)
NULL0_IMPORT("key_pressed")
bool key_pressed(Key key);

// Is the key currently down?
NULL0_IMPORT("key_down")
bool key_down(Key key);

// Has the key been released? (tracks press/read correctly)
NULL0_IMPORT("key_released")
bool key_released(Key key);

// Is the key currently up?
NULL0_IMPORT("key_up")
bool key_up(Key key);

// Has the button been pressed? (tracks unpress/read correctly)
NULL0_IMPORT("gamepad_button_pressed")
bool gamepad_button_pressed(i32 gamepad, GamepadButton button);

// Is the button currently down?
NULL0_IMPORT("gamepad_button_down")
bool gamepad_button_down(i32 gamepad, GamepadButton button);

// Has the button been released? (tracks press/read correctly)
NULL0_IMPORT("gamepad_button_released")
bool gamepad_button_released(i32 gamepad, GamepadButton button);

// Is the button currently up?
NULL0_IMPORT("gamepad_button_up")
bool gamepad_button_up(i32 gamepad, GamepadButton button);

// Get current position of mouse
NULL0_IMPORT("mouse_position")
Vector mouse_position();

// Has the button been pressed? (tracks unpress/read correctly)
NULL0_IMPORT("mouse_button_pressed")
bool mouse_button_pressed(MouseButton button);

// Is the button currently down?
NULL0_IMPORT("mouse_button_down")
bool mouse_button_down(MouseButton button);

// Has the button been released? (tracks press/read correctly)
NULL0_IMPORT("mouse_button_released")
bool mouse_button_released(MouseButton button);

// Is the button currently up?
NULL0_IMPORT("mouse_button_up")
bool mouse_button_up(MouseButton button);

/////////// GRAPHICS ///////////

// Create a new blank image
NULL0_IMPORT("new_image")
u32 new_image(i32 width, i32 height, Color color);

// Copy an image to a new image
NULL0_IMPORT("image_copy")
u32 image_copy(u32 image);

// Create an image from a region of another image
NULL0_IMPORT("image_subimage")
u32 image_subimage(u32 image, i32 x, i32 y, i32 width, i32 height);

// Clear the screen
NULL0_IMPORT("clear")
void clear(Color color);

// Draw a single pixel on the screen
NULL0_IMPORT("draw_point")
void draw_point(i32 x, i32 y, Color color);

// Draw a line on the screen
NULL0_IMPORT("draw_line")
void draw_line(i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color);

// Draw a filled rectangle on the screen
NULL0_IMPORT("draw_rectangle")
void draw_rectangle(i32 posX, i32 posY, i32 width, i32 height, Color color);

// Draw a filled triangle on the screen
NULL0_IMPORT("draw_triangle")
void draw_triangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color);

// Draw a filled ellipse on the screen
NULL0_IMPORT("draw_ellipse")
void draw_ellipse(i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color);

// Draw a filled circle on the screen
NULL0_IMPORT("draw_circle")
void draw_circle(i32 centerX, i32 centerY, i32 radius, Color color);

// Draw a filled polygon on the screen
NULL0_IMPORT("draw_polygon")
void draw_polygon(Vector* points, i32 numPoints, Color color);

// Draw several lines on the screen
NULL0_IMPORT("draw_polyline")
void draw_polyline(Vector* points, i32 numPoints, Color color);

// Draw a filled arc on the screen
NULL0_IMPORT("draw_arc")
void draw_arc(i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, Color color);

// Draw a filled round-rectangle on the screen
NULL0_IMPORT("draw_rectangle_rounded")
void draw_rectangle_rounded(i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color);

// Draw an image on the screen
NULL0_IMPORT("draw_image")
void draw_image(u32 src, i32 posX, i32 posY);

// Draw a tinted image on the screen
NULL0_IMPORT("draw_image_tint")
void draw_image_tint(u32 src, i32 posX, i32 posY, Color tint);

// Draw an image, rotated, on the screen
NULL0_IMPORT("draw_image_rotated")
void draw_image_rotated(u32 src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter);

// Draw an image, flipped, on the screen
NULL0_IMPORT("draw_image_flipped")
void draw_image_flipped(u32 src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);

// Draw an image, scaled, on the screen
NULL0_IMPORT("draw_image_scaled")
void draw_image_scaled(u32 src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter);

// Draw some text on the screen
NULL0_IMPORT("draw_text")
void draw_text(u32 font, char* text, i32 posX, i32 posY, Color color);

// Save an image to persistant storage
NULL0_IMPORT("save_image")
void save_image(u32 image, char* filename);

// Load an image from a file in cart
NULL0_IMPORT("load_image")
u32 load_image(char* filename);

// Resize an image, in-place
NULL0_IMPORT("image_resize")
void image_resize(u32 image, i32 newWidth, i32 newHeight, i32 offsetX, i32 offsetY, Color fill);

// Scale an image, in-place
NULL0_IMPORT("image_scale")
void image_scale(u32 image, f32 scaleX, f32 scaleY, ImageFilter filter);

// Replace a color in an image, in-place
NULL0_IMPORT("image_color_replace")
void image_color_replace(u32 image, Color color, Color replace);

// Tint a color in an image, in-place
NULL0_IMPORT("image_color_tint")
void image_color_tint(u32 image, Color color);

// Fade a color in an image, in-place
NULL0_IMPORT("image_color_fade")
void image_color_fade(u32 image, f32 alpha);

// Copy a font to a new font
NULL0_IMPORT("font_copy")
u32 font_copy(u32 font);

// Scale a font, return a new font
NULL0_IMPORT("font_scale")
u32 font_scale(u32 font, f32 scaleX, f32 scaleY, ImageFilter filter);

// Load a BMF font from a file in cart
NULL0_IMPORT("load_font_bmf")
u32 load_font_bmf(char* filename, char* characters);

// Load a BMF font from an image
NULL0_IMPORT("load_font_bmf_from_image")
u32 load_font_bmf_from_image(u32 image, char* characters);

// Measure the size of some text
NULL0_IMPORT("measure_text")
Dimensions measure_text(u32 font, char* text);

// Meaure an image (use 0 for screen)
NULL0_IMPORT("measure_image")
Dimensions measure_image(u32 image);

// Load a TTY font from a file in cart
NULL0_IMPORT("load_font_tty")
u32 load_font_tty(char* filename, i32 glyphWidth, i32 glyphHeight, char* characters);

// Load a TTY font from an image
NULL0_IMPORT("load_font_tty_from_image")
u32 load_font_tty_from_image(u32 image, i32 glyphWidth, i32 glyphHeight, char* characters);

// Load a TTF font from a file in cart
NULL0_IMPORT("load_font_ttf")
u32 load_font_ttf(char* filename, i32 fontSize);

// Invert the colors in an image, in-place
NULL0_IMPORT("image_color_invert")
void image_color_invert(u32 image);

// Calculate a rectangle representing the available alpha border in an image
NULL0_IMPORT("image_alpha_border")
Rectangle image_alpha_border(u32 image, f32 threshold);

// Crop an image, in-place
NULL0_IMPORT("image_crop")
void image_crop(u32 image, i32 x, i32 y, i32 width, i32 height);

// Crop an image based on the alpha border, in-place
NULL0_IMPORT("image_alpha_crop")
void image_alpha_crop(u32 image, f32 threshold);

// Adjust the brightness of an image, in-place
NULL0_IMPORT("image_color_brightness")
void image_color_brightness(u32 image, f32 factor);

// Flip an image, in-place
NULL0_IMPORT("image_flip")
void image_flip(u32 image, bool horizontal, bool vertical);

// Change the contrast of an image, in-place
NULL0_IMPORT("image_color_contrast")
void image_color_contrast(u32 image, f32 contrast);

// Use an image as an alpha-mask on another image
NULL0_IMPORT("image_alpha_mask")
void image_alpha_mask(u32 image, u32 alphaMask, i32 posX, i32 posY);

// Create a new image, rotating another image
NULL0_IMPORT("image_rotate")
u32 image_rotate(u32 image, f32 degrees, ImageFilter filter);

// Create a new image of a gradient
NULL0_IMPORT("image_gradient")
u32 image_gradient(i32 width, i32 height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight);

// Unload an image
NULL0_IMPORT("unload_image")
void unload_image(u32 image);

// Unload a font
NULL0_IMPORT("unload_font")
void unload_font(u32 font);

// Clear an image
NULL0_IMPORT("clear_on_image")
void clear_on_image(u32 destination, Color color);

// Draw a single pixel on an image
NULL0_IMPORT("draw_point_on_image")
void draw_point_on_image(u32 destination, i32 x, i32 y, Color color);

// Draw a line on an image
NULL0_IMPORT("draw_line_on_image")
void draw_line_on_image(u32 destination, i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color);

// Draw a filled rectangle on an image
NULL0_IMPORT("draw_rectangle_on_image")
void draw_rectangle_on_image(u32 destination, i32 posX, i32 posY, i32 width, i32 height, Color color);

// Draw a filled triangle on an image
NULL0_IMPORT("draw_triangle_on_image")
void draw_triangle_on_image(u32 destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color);

// Draw a filled ellipse on an image
NULL0_IMPORT("draw_ellipse_on_image")
void draw_ellipse_on_image(u32 destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color);

// Draw a circle on an image
NULL0_IMPORT("draw_circle_on_image")
void draw_circle_on_image(u32 destination, i32 centerX, i32 centerY, i32 radius, Color color);

// Draw a filled polygon on an image
NULL0_IMPORT("draw_polygon_on_image")
void draw_polygon_on_image(u32 destination, Vector* points, i32 numPoints, Color color);

// Draw several lines on an image
NULL0_IMPORT("draw_polyline_on_image")
void draw_polyline_on_image(u32 destination, Vector* points, i32 numPoints, Color color);

// Draw a filled round-rectangle on an image
NULL0_IMPORT("draw_rectangle_rounded_on_image")
void draw_rectangle_rounded_on_image(u32 destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color);

// Draw an image on an image
NULL0_IMPORT("draw_image_on_image")
void draw_image_on_image(u32 destination, u32 src, i32 posX, i32 posY);

// Draw a tinted image on an image
NULL0_IMPORT("draw_image_tint_on_image")
void draw_image_tint_on_image(u32 destination, u32 src, i32 posX, i32 posY, Color tint);

// Draw an image, rotated, on an image
NULL0_IMPORT("draw_image_rotated_on_image")
void draw_image_rotated_on_image(u32 destination, u32 src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter);

// Draw an image, flipped, on an image
NULL0_IMPORT("draw_image_flipped_on_image")
void draw_image_flipped_on_image(u32 destination, u32 src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);

// Draw an image, scaled, on an image
NULL0_IMPORT("draw_image_scaled_on_image")
void draw_image_scaled_on_image(u32 destination, u32 src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter);

// Draw some text on an image
NULL0_IMPORT("draw_text_on_image")
void draw_text_on_image(u32 destination, u32 font, char* text, i32 posX, i32 posY, Color color);

// Draw a 1px outlined rectangle on the screen
NULL0_IMPORT("draw_rectangle_outline")
void draw_rectangle_outline(i32 posX, i32 posY, i32 width, i32 height, Color color);

// Draw a 1px outlined triangle on the screen
NULL0_IMPORT("draw_triangle_outline")
void draw_triangle_outline(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color);

// Draw a 1px outlined ellipse on the screen
NULL0_IMPORT("draw_ellipse_outline")
void draw_ellipse_outline(i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color);

// Draw a 1px outlined circle on the screen
NULL0_IMPORT("draw_circle_outline")
void draw_circle_outline(i32 centerX, i32 centerY, i32 radius, Color color);

// Draw a 1px outlined polygon on the screen
NULL0_IMPORT("draw_polygon_outline")
void draw_polygon_outline(Vector* points, i32 numPoints, Color color);

// Draw a 1px outlined arc on the screen
NULL0_IMPORT("draw_arc_outline")
void draw_arc_outline(i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, Color color);

// Draw a 1px outlined round-rectangle on the screen
NULL0_IMPORT("draw_rectangle_rounded_outline")
void draw_rectangle_rounded_outline(i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color);

// Draw a 1px outlined rectangle on an image
NULL0_IMPORT("draw_rectangle_outline_on_image")
void draw_rectangle_outline_on_image(u32 destination, i32 posX, i32 posY, i32 width, i32 height, Color color);

// Draw a 1px outlined triangle on an image
NULL0_IMPORT("draw_triangle_outline_on_image")
void draw_triangle_outline_on_image(u32 destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color);

// Draw a 1px outlined ellipse on an image
NULL0_IMPORT("draw_ellipse_outline_on_image")
void draw_ellipse_outline_on_image(u32 destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color);

// Draw a 1px outlined circle on an image
NULL0_IMPORT("draw_circle_outline_on_image")
void draw_circle_outline_on_image(u32 destination, i32 centerX, i32 centerY, i32 radius, Color color);

// Draw a 1px outlined polygon on an image
NULL0_IMPORT("draw_polygon_outline_on_image")
void draw_polygon_outline_on_image(u32 destination, Vector* points, i32 numPoints, Color color);

// Draw a 1px outlined round-rectangle on an image
NULL0_IMPORT("draw_rectangle_rounded_outline_on_image")
void draw_rectangle_rounded_outline_on_image(u32 destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color);

/////////// FILESYSTEM ///////////

// Get info about a single file
NULL0_IMPORT("file_info")
FileInfo file_info(char* filename);

// Read a file from cart
NULL0_IMPORT("file_read")
void _null0_file_read(char* filename, u32* bytesRead, u8* ret);
u8* file_read(char* filename, u32* bytesRead) {
  FileInfo i = file_info(filename);
  u8* ret = malloc(i.filesize);
  _null0_file_read(filename, bytesRead, ret);
  return ret;
}

// Write a file to persistant storage
NULL0_IMPORT("file_write")
bool file_write(char* filename, u8* data, u32 byteSize);

// Write a file to persistant storage, appending to the end
NULL0_IMPORT("file_append")
bool file_append(char* filename, u8* data, u32 byteSize);

// Get list of files in a directory
NULL0_IMPORT("file_list")
char** file_list(char* dir);

// Get the user's writable dir (where file writes or appends go)
NULL0_IMPORT("get_write_dir")
char* get_write_dir();

/////////// COLORS ///////////

// Tint a color with another color
NULL0_IMPORT("color_tint")
Color color_tint(Color color, Color tint);

// Fade a color
NULL0_IMPORT("color_fade")
Color color_fade(Color color, f32 alpha);

// Change the brightness of a color
NULL0_IMPORT("color_brightness")
Color color_brightness(Color color, f32 factor);

// Invert a color
NULL0_IMPORT("color_invert")
Color color_invert(Color color);

// Blend 2 colors together
NULL0_IMPORT("color_alpha_blend")
Color color_alpha_blend(Color dst, Color src);

// color_contrast
NULL0_IMPORT("color_contrast")
Color color_contrast(Color color, f32 contrast);

// Interpolate colors
NULL0_IMPORT("color_bilinear_interpolate")
Color color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, f32 coordinateX, f32 coordinateY);

// | END GENERATED |
