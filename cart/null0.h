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
  GAMEPAD_BUTTON_UNKNOWN = 0,    // Unknown button, just for error checking
  GAMEPAD_BUTTON_UP = 1,         // Gamepad left DPAD up button
  GAMEPAD_BUTTON_RIGHT,          // Gamepad left DPAD right button
  GAMEPAD_BUTTON_DOWN,           // Gamepad left DPAD down button
  GAMEPAD_BUTTON_LEFT,           // Gamepad left DPAD left button
  GAMEPAD_BUTTON_Y,              // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  GAMEPAD_BUTTON_B,              // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  GAMEPAD_BUTTON_A,              // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  GAMEPAD_BUTTON_X,              // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  GAMEPAD_BUTTON_LEFT_SHOULDER,  // Gamepad top/back trigger left (first), it could be a trailing button
  GAMEPAD_BUTTON_LEFT_TRIGGER,   // Gamepad top/back trigger left (second), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_SHOULDER, // Gamepad top/back trigger right (one), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER,  // Gamepad top/back trigger right (second), it could be a trailing button
  GAMEPAD_BUTTON_SELECT,         // Gamepad center buttons, left one (i.e. PS3: Select)
  GAMEPAD_BUTTON_MENU,           // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  GAMEPAD_BUTTON_START,          // Gamepad center buttons, right one (i.e. PS3: Start)
  GAMEPAD_BUTTON_LEFT_THUMB,     // Gamepad joystick pressed button left
  GAMEPAD_BUTTON_RIGHT_THUMB,    // Gamepad joystick pressed button right
} GamepadButton;

typedef enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3,
} MouseButton;

#define WIDTH 640
#define HEIGHT 480

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

// basic memory-management from host

NULL0_EXPORT("malloc")
void *_null0_malloc(size_t size) {
  return malloc(size);
}

NULL0_EXPORT("free")
void _null0_free(void *ptr) {
  free(ptr);
}

// callbacks for cart to implement

// called on load, you can also use main()
NULL0_EXPORT("load")
void load();

// called on every frame
NULL0_EXPORT("update")
void update();

// called when the cart is unloaded
NULL0_EXPORT("unload")
void unload();

// mapped controller callback
NULL0_EXPORT("buttonUp")
void buttonUp(GamepadButton button);

// mapped controller callback
NULL0_EXPORT("buttonDown")
void buttonDown(GamepadButton button);

// called when keys are unpressed
NULL0_EXPORT("keyUp")
void keyUp(Key key);

// called when keys are pressed
NULL0_EXPORT("keyDown")
void keyDown(Key key);

// DRAW: IMAGE

// Draw an image on an image
NULL0_IMPORT("draw_image")
void draw_image(u32 destination, u32 src, i32 posX, i32 posY);

// Draw an image, flipped, on an image
NULL0_IMPORT("draw_image_flipped")
void draw_image_flipped(u32 destination, u32 src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);

// Draw an image, rotated, on an image
NULL0_IMPORT("draw_image_rotated")
void draw_image_rotated(u32 destination, u32 src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter);

// Draw an image, scaled, on an image
NULL0_IMPORT("draw_image_scaled")
void draw_image_scaled(u32 destination, u32 src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter);

// Draw a tinted image on an image
NULL0_IMPORT("draw_image_tint")
void draw_image_tint(u32 destination, u32 src, i32 posX, i32 posY, Color tint);

// Use an image as an alpha-mask on another image
NULL0_IMPORT("image_alpha_mask")
void image_alpha_mask(u32 image, u32 alphaMask, i32 posX, i32 posY);

// Adjust the brightness of an image, in-place
NULL0_IMPORT("image_color_brightness")
void image_color_brightness(u32 image, f32 factor);

// Change the contrast of an image, in-place
NULL0_IMPORT("image_color_contrast")
void image_color_contrast(u32 image, f32 contrast);

// Fade a color in an image, in-place
NULL0_IMPORT("image_color_fade")
void image_color_fade(u32 image, f32 alpha);

// Invert the colors in an image, in-place
NULL0_IMPORT("image_color_invert")
void image_color_invert(u32 image);

// Replace a color in an image, in-place
NULL0_IMPORT("image_color_replace")
void image_color_replace(u32 image, Color color, Color replace);

// Tint a color in an image, in-place
NULL0_IMPORT("image_color_tint")
void image_color_tint(u32 image, Color color);

// Copy an image to a new image
NULL0_IMPORT("image_copy")
u32 image_copy(u32 image);

// Crop an image, in-place
NULL0_IMPORT("image_crop")
void image_crop(u32 image, i32 x, i32 y, i32 width, i32 height);

// Flip an image, in-place
NULL0_IMPORT("image_flip")
void image_flip(u32 image, bool horizontal, bool vertical);

// Create a new image of a gradient
NULL0_IMPORT("image_gradient")
u32 image_gradient(i32 width, i32 height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight);

// Load an image from a file in cart
NULL0_IMPORT("image_load")
u32 image_load(char *filename);

// Meaure an image (use 0 for screen)
NULL0_IMPORT("image_measure")
Dimensions image_measure(u32 image);

// Create a new blank image
NULL0_IMPORT("image_new")
u32 image_new(i32 width, i32 height, Color color);

// Resize an image, in-place
NULL0_IMPORT("image_resize")
void image_resize(u32 image, i32 newWidth, i32 newHeight, i32 offsetX, i32 offsetY, Color fill);

// Create a new image, rotating another image
NULL0_IMPORT("image_rotate")
u32 image_rotate(u32 image, f32 degrees, ImageFilter filter);

// Save an image to persistant storage
NULL0_IMPORT("image_save")
void image_save(u32 image, char *filename);

// Unload an image
NULL0_IMPORT("image_unload")
void image_unload(u32 image);

// Create an image from a region of another image
NULL0_IMPORT("subimage")
u32 subimage(u32 image, i32 x, i32 y, i32 width, i32 height);

// DRAW: SHAPES

// Clear an image
NULL0_IMPORT("clear")
void clear(u32 destination, Color color);

// Draw an arc on an image. Set thickness to 0 for "fill".
NULL0_IMPORT("draw_arc")
void draw_arc(u32 destination, i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, u32 thickness, Color color);

// Draw a circle on an image. Set thickness to 0 for "fill".
NULL0_IMPORT("draw_circle")
void draw_circle(u32 destination, i32 centerX, i32 centerY, i32 radius, u32 thickness, Color color);

// Draw a filled ellipse on an image. Set thickness to 0 for "fill".
NULL0_IMPORT("draw_ellipse")
void draw_ellipse(u32 destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, u32 thickness, Color color);

// Draw a line on an image
NULL0_IMPORT("draw_line")
void draw_line(u32 destination, i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, u32 thickness, Color color);

// Draw a single pixel on an image
NULL0_IMPORT("draw_point")
void draw_point(u32 destination, i32 x, i32 y, Color color);

// Draw a filled rectangle on an image. Set thickness to 0 for "fill".
NULL0_IMPORT("draw_rectangle")
void draw_rectangle(u32 destination, i32 posX, i32 posY, i32 width, i32 height, u32 thickness, Color color);

// Draw a filled round-rectangle on an image. Set thickness to 0 for "fill".
NULL0_IMPORT("draw_rectangle_rounded")
void draw_rectangle_rounded(u32 destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, u32 thickness, Color color);

// Draw some text on an image
NULL0_IMPORT("draw_text")
void draw_text(u32 destination, u32 font, char *text, i32 posX, i32 posY, Color color);

// Draw a filled triangle on an image. Set thickness to 0 for "fill".
NULL0_IMPORT("draw_triangle")
void draw_triangle(u32 destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, u32 thickness, Color color);

// FONTS

// Copy a font to a new font
NULL0_IMPORT("font_copy")
u32 font_copy(u32 font);

// Load a BMF font from a file in cart
NULL0_IMPORT("font_load_bmf")
u32 font_load_bmf(char *filename, char *characters);

// Load a BMF font from an image
NULL0_IMPORT("font_load_bmf_from_image")
u32 font_load_bmf_from_image(u32 image, char *characters);

// Load a TTF font from a file in cart
NULL0_IMPORT("font_load_ttf")
u32 font_load_ttf(char *filename, i32 fontSize);

// Load a TTY font from a file in cart
NULL0_IMPORT("font_load_tty")
u32 font_load_tty(char *filename, i32 glyphWidth, i32 glyphHeight, char *characters);

// Load a TTY font from an image
NULL0_IMPORT("font_load_tty_from_image")
u32 font_load_tty_from_image(u32 image, i32 glyphWidth, i32 glyphHeight, char *characters);

// Scale a font, return a new font
NULL0_IMPORT("font_scale")
u32 font_scale(u32 font, f32 scaleX, f32 scaleY, ImageFilter filter);

// Unload a font
NULL0_IMPORT("font_unload")
void font_unload(u32 font);

// Measure the size of some text
NULL0_IMPORT("text_measure")
Dimensions text_measure(u32 font, char *text);

// UTILS: COLORS

// Blend 2 colors together
NULL0_IMPORT("color_alpha_blend")
Color *color_alpha_blend(Color dst, Color src);

// Interpolate colors
NULL0_IMPORT("color_bilinear_interpolate")
Color *color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, f32 coordinateX, f32 coordinateY);

// Change the brightness of a color
NULL0_IMPORT("color_brightness")
Color *color_brightness(Color color, f32 factor);

// Change contrast of a color
NULL0_IMPORT("color_contrast")
Color *color_contrast(Color color, f32 contrast);

// Fade a color
NULL0_IMPORT("color_fade")
Color *color_fade(Color color, f32 alpha);

// Invert a color
NULL0_IMPORT("color_invert")
Color *color_invert(Color color);

// Tint a color with another color
NULL0_IMPORT("color_tint")
Color *color_tint(Color color, Color tint);

// SOUND
NULL0_IMPORT("soundfont_load")
u32 soundfont_load(char *filename);
