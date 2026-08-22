// GENERATED FILE - do not edit by hand. See tools/gen_cart_haskell.js
//
// Custom-wasm-import trampoline: GHC's FFI cannot marshal a C struct by
// value, so every null0 function is re-exposed here with structs as
// pointers. The private `_name` extern carries the real import (module
// "null0", the exact by-value ABI null0.h itself uses); the public `name`
// wraps it with a pointer-only signature Haskell can import directly.

#include <stdint.h>
#include <stdbool.h>

#define NULL0_IMPORT(n) __attribute__((import_module("null0"), import_name(n)))

typedef struct {
  uint32_t randSeed;
  int32_t waveType;
  float attackTime;
  float sustainTime;
  float sustainPunch;
  float decayTime;
  float startFrequency;
  float minFrequency;
  float slide;
  float deltaSlide;
  float vibratoDepth;
  float vibratoSpeed;
  float changeAmount;
  float changeSpeed;
  float squareDuty;
  float dutySweep;
  float repeatSpeed;
  float phaserOffset;
  float phaserSweep;
  float lpfCutoff;
  float lpfCutoffSweep;
  float lpfResonance;
  float hpfCutoff;
  float hpfCutoffSweep;
} SfxParams;

typedef struct {
  int32_t width;
  int32_t height;
} Dimensions;

typedef struct {
  int32_t x;
  int32_t y;
} Vector;

typedef struct {
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
} Rectangle;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

typedef struct {
  char* name;
  int32_t type;
  int32_t integer;
  float number;
  char* text;
} TilemapProp;

typedef struct {
  int32_t id;
  char* name;
  char* type;
  int32_t gid;
  float x;
  float y;
  float width;
  float height;
  float rotation;
  int32_t visible;
} TilemapObject;


// COLORS

NULL0_IMPORT("color_tint")
extern Color* _color_tint(Color color, Color tint);
Color* color_tint(Color* color, Color* tint) {
  return _color_tint(*color, *tint);
}

NULL0_IMPORT("color_fade")
extern Color* _color_fade(Color color, float alpha);
Color* color_fade(Color* color, float alpha) {
  return _color_fade(*color, alpha);
}

NULL0_IMPORT("color_brightness")
extern Color* _color_brightness(Color color, float factor);
Color* color_brightness(Color* color, float factor) {
  return _color_brightness(*color, factor);
}

NULL0_IMPORT("color_invert")
extern Color* _color_invert(Color color);
Color* color_invert(Color* color) {
  return _color_invert(*color);
}

NULL0_IMPORT("color_alpha_blend")
extern Color* _color_alpha_blend(Color dst, Color src);
Color* color_alpha_blend(Color* dst, Color* src) {
  return _color_alpha_blend(*dst, *src);
}

NULL0_IMPORT("color_contrast")
extern Color* _color_contrast(Color color, float contrast);
Color* color_contrast(Color* color, float contrast) {
  return _color_contrast(*color, contrast);
}

NULL0_IMPORT("color_bilinear_interpolate")
extern Color* _color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, float coordinateX, float coordinateY);
Color* color_bilinear_interpolate(Color* color00, Color* color01, Color* color10, Color* color11, float coordinateX, float coordinateY) {
  return _color_bilinear_interpolate(*color00, *color01, *color10, *color11, coordinateX, coordinateY);
}


// GRAPHICS

NULL0_IMPORT("new_image")
extern uint32_t _new_image(int32_t width, int32_t height, Color color);
uint32_t new_image(int32_t width, int32_t height, Color* color) {
  return _new_image(width, height, *color);
}

NULL0_IMPORT("image_copy")
extern uint32_t _image_copy(uint32_t image);
uint32_t image_copy(uint32_t image) {
  return _image_copy(image);
}

NULL0_IMPORT("image_subimage")
extern uint32_t _image_subimage(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height);
uint32_t image_subimage(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  return _image_subimage(image, x, y, width, height);
}

NULL0_IMPORT("clear")
extern void _clear(Color color);
void clear(Color* color) {
  _clear(*color);
}

NULL0_IMPORT("draw_point")
extern void _draw_point(int32_t x, int32_t y, Color color);
void draw_point(int32_t x, int32_t y, Color* color) {
  _draw_point(x, y, *color);
}

NULL0_IMPORT("draw_line")
extern void _draw_line(int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, Color color);
void draw_line(int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, Color* color) {
  _draw_line(startPosX, startPosY, endPosX, endPosY, *color);
}

NULL0_IMPORT("draw_rectangle")
extern void _draw_rectangle(int32_t posX, int32_t posY, int32_t width, int32_t height, Color color);
void draw_rectangle(int32_t posX, int32_t posY, int32_t width, int32_t height, Color* color) {
  _draw_rectangle(posX, posY, width, height, *color);
}

NULL0_IMPORT("draw_triangle")
extern void _draw_triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color color);
void draw_triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color* color) {
  _draw_triangle(x1, y1, x2, y2, x3, y3, *color);
}

NULL0_IMPORT("draw_ellipse")
extern void _draw_ellipse(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Color color);
void draw_ellipse(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Color* color) {
  _draw_ellipse(centerX, centerY, radiusX, radiusY, *color);
}

NULL0_IMPORT("draw_circle")
extern void _draw_circle(int32_t centerX, int32_t centerY, int32_t radius, Color color);
void draw_circle(int32_t centerX, int32_t centerY, int32_t radius, Color* color) {
  _draw_circle(centerX, centerY, radius, *color);
}

NULL0_IMPORT("draw_polygon")
extern void _draw_polygon(Vector* points, uint32_t points_count, Color color);
void draw_polygon(Vector* points, uint32_t points_count, Color* color) {
  _draw_polygon(points, points_count, *color);
}

NULL0_IMPORT("draw_arc")
extern void _draw_arc(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, Color color);
void draw_arc(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, Color* color) {
  _draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, *color);
}

NULL0_IMPORT("draw_rectangle_rounded")
extern void _draw_rectangle_rounded(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Color color);
void draw_rectangle_rounded(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Color* color) {
  _draw_rectangle_rounded(x, y, width, height, cornerRadius, *color);
}

NULL0_IMPORT("draw_image")
extern void _draw_image(uint32_t src, int32_t posX, int32_t posY);
void draw_image(uint32_t src, int32_t posX, int32_t posY) {
  _draw_image(src, posX, posY);
}

NULL0_IMPORT("draw_image_tint")
extern void _draw_image_tint(uint32_t src, int32_t posX, int32_t posY, Color tint);
void draw_image_tint(uint32_t src, int32_t posX, int32_t posY, Color* tint) {
  _draw_image_tint(src, posX, posY, *tint);
}

NULL0_IMPORT("draw_image_rotated")
extern void _draw_image_rotated(uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, int32_t filter);
void draw_image_rotated(uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, int32_t filter) {
  _draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter);
}

NULL0_IMPORT("draw_image_flipped")
extern void _draw_image_flipped(uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);
void draw_image_flipped(uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  _draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

NULL0_IMPORT("draw_image_scaled")
extern void _draw_image_scaled(uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, int32_t filter);
void draw_image_scaled(uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, int32_t filter) {
  _draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

NULL0_IMPORT("draw_text")
extern void _draw_text(uint32_t font, char* text, int32_t posX, int32_t posY, Color color);
void draw_text(uint32_t font, char* text, int32_t posX, int32_t posY, Color* color) {
  _draw_text(font, text, posX, posY, *color);
}

NULL0_IMPORT("save_image")
extern void _save_image(uint32_t image, char* filename);
void save_image(uint32_t image, char* filename) {
  _save_image(image, filename);
}

NULL0_IMPORT("load_image")
extern uint32_t _load_image(char* filename);
uint32_t load_image(char* filename) {
  return _load_image(filename);
}

NULL0_IMPORT("image_resize")
extern uint32_t _image_resize(uint32_t image, int32_t newWidth, int32_t newHeight, int32_t filter);
uint32_t image_resize(uint32_t image, int32_t newWidth, int32_t newHeight, int32_t filter) {
  return _image_resize(image, newWidth, newHeight, filter);
}

NULL0_IMPORT("image_scale")
extern uint32_t _image_scale(uint32_t image, float scaleX, float scaleY, int32_t filter);
uint32_t image_scale(uint32_t image, float scaleX, float scaleY, int32_t filter) {
  return _image_scale(image, scaleX, scaleY, filter);
}

NULL0_IMPORT("image_color_replace")
extern void _image_color_replace(uint32_t image, Color color, Color replace);
void image_color_replace(uint32_t image, Color* color, Color* replace) {
  _image_color_replace(image, *color, *replace);
}

NULL0_IMPORT("image_color_tint")
extern void _image_color_tint(uint32_t image, Color color);
void image_color_tint(uint32_t image, Color* color) {
  _image_color_tint(image, *color);
}

NULL0_IMPORT("image_color_fade")
extern void _image_color_fade(uint32_t image, float alpha);
void image_color_fade(uint32_t image, float alpha) {
  _image_color_fade(image, alpha);
}

NULL0_IMPORT("font_copy")
extern uint32_t _font_copy(uint32_t font);
uint32_t font_copy(uint32_t font) {
  return _font_copy(font);
}

NULL0_IMPORT("font_scale")
extern uint32_t _font_scale(uint32_t font, float scaleX, float scaleY, int32_t filter);
uint32_t font_scale(uint32_t font, float scaleX, float scaleY, int32_t filter) {
  return _font_scale(font, scaleX, scaleY, filter);
}

NULL0_IMPORT("load_font_bmf")
extern uint32_t _load_font_bmf(char* filename, char* characters);
uint32_t load_font_bmf(char* filename, char* characters) {
  return _load_font_bmf(filename, characters);
}

NULL0_IMPORT("load_font_bmf_from_image")
extern uint32_t _load_font_bmf_from_image(uint32_t image, char* characters);
uint32_t load_font_bmf_from_image(uint32_t image, char* characters) {
  return _load_font_bmf_from_image(image, characters);
}

NULL0_IMPORT("measure_text")
extern Dimensions* _measure_text(uint32_t font, char* text, int32_t textLength);
Dimensions* measure_text(uint32_t font, char* text, int32_t textLength) {
  return _measure_text(font, text, textLength);
}

NULL0_IMPORT("measure_image")
extern Dimensions* _measure_image(uint32_t image);
Dimensions* measure_image(uint32_t image) {
  return _measure_image(image);
}

NULL0_IMPORT("load_font_tty")
extern uint32_t _load_font_tty(char* filename, int32_t glyphWidth, int32_t glyphHeight, char* characters);
uint32_t load_font_tty(char* filename, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return _load_font_tty(filename, glyphWidth, glyphHeight, characters);
}

NULL0_IMPORT("load_font_tty_from_image")
extern uint32_t _load_font_tty_from_image(uint32_t image, int32_t glyphWidth, int32_t glyphHeight, char* characters);
uint32_t load_font_tty_from_image(uint32_t image, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return _load_font_tty_from_image(image, glyphWidth, glyphHeight, characters);
}

NULL0_IMPORT("load_font_ttf")
extern uint32_t _load_font_ttf(char* filename, int32_t fontSize);
uint32_t load_font_ttf(char* filename, int32_t fontSize) {
  return _load_font_ttf(filename, fontSize);
}

NULL0_IMPORT("image_color_invert")
extern void _image_color_invert(uint32_t image);
void image_color_invert(uint32_t image) {
  _image_color_invert(image);
}

NULL0_IMPORT("image_alpha_border")
extern Rectangle* _image_alpha_border(uint32_t image, float threshold);
Rectangle* image_alpha_border(uint32_t image, float threshold) {
  return _image_alpha_border(image, threshold);
}

NULL0_IMPORT("image_crop")
extern void _image_crop(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height);
void image_crop(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  _image_crop(image, x, y, width, height);
}

NULL0_IMPORT("image_alpha_crop")
extern void _image_alpha_crop(uint32_t image, float threshold);
void image_alpha_crop(uint32_t image, float threshold) {
  _image_alpha_crop(image, threshold);
}

NULL0_IMPORT("image_color_brightness")
extern void _image_color_brightness(uint32_t image, float factor);
void image_color_brightness(uint32_t image, float factor) {
  _image_color_brightness(image, factor);
}

NULL0_IMPORT("image_flip")
extern void _image_flip(uint32_t image, bool horizontal, bool vertical);
void image_flip(uint32_t image, bool horizontal, bool vertical) {
  _image_flip(image, horizontal, vertical);
}

NULL0_IMPORT("image_color_contrast")
extern void _image_color_contrast(uint32_t image, float contrast);
void image_color_contrast(uint32_t image, float contrast) {
  _image_color_contrast(image, contrast);
}

NULL0_IMPORT("image_alpha_mask")
extern void _image_alpha_mask(uint32_t image, uint32_t alphaMask, int32_t posX, int32_t posY);
void image_alpha_mask(uint32_t image, uint32_t alphaMask, int32_t posX, int32_t posY) {
  _image_alpha_mask(image, alphaMask, posX, posY);
}

NULL0_IMPORT("image_rotate")
extern uint32_t _image_rotate(uint32_t image, float degrees, int32_t filter);
uint32_t image_rotate(uint32_t image, float degrees, int32_t filter) {
  return _image_rotate(image, degrees, filter);
}

NULL0_IMPORT("image_gradient")
extern uint32_t _image_gradient(int32_t width, int32_t height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight);
uint32_t image_gradient(int32_t width, int32_t height, Color* topLeft, Color* topRight, Color* bottomLeft, Color* bottomRight) {
  return _image_gradient(width, height, *topLeft, *topRight, *bottomLeft, *bottomRight);
}

NULL0_IMPORT("unload_image")
extern void _unload_image(uint32_t image);
void unload_image(uint32_t image) {
  _unload_image(image);
}

NULL0_IMPORT("unload_font")
extern void _unload_font(uint32_t font);
void unload_font(uint32_t font) {
  _unload_font(font);
}

NULL0_IMPORT("clear_image")
extern void _clear_image(uint32_t destination, Color color);
void clear_image(uint32_t destination, Color* color) {
  _clear_image(destination, *color);
}

NULL0_IMPORT("draw_point_on_image")
extern void _draw_point_on_image(uint32_t destination, int32_t x, int32_t y, Color color);
void draw_point_on_image(uint32_t destination, int32_t x, int32_t y, Color* color) {
  _draw_point_on_image(destination, x, y, *color);
}

NULL0_IMPORT("draw_line_on_image")
extern void _draw_line_on_image(uint32_t destination, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, Color color);
void draw_line_on_image(uint32_t destination, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, Color* color) {
  _draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, *color);
}

NULL0_IMPORT("draw_rectangle_on_image")
extern void _draw_rectangle_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, Color color);
void draw_rectangle_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, Color* color) {
  _draw_rectangle_on_image(destination, posX, posY, width, height, *color);
}

NULL0_IMPORT("draw_triangle_on_image")
extern void _draw_triangle_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color color);
void draw_triangle_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color* color) {
  _draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, *color);
}

NULL0_IMPORT("draw_ellipse_on_image")
extern void _draw_ellipse_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Color color);
void draw_ellipse_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, Color* color) {
  _draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, *color);
}

NULL0_IMPORT("draw_circle_on_image")
extern void _draw_circle_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, Color color);
void draw_circle_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, Color* color) {
  _draw_circle_on_image(destination, centerX, centerY, radius, *color);
}

NULL0_IMPORT("draw_polygon_on_image")
extern void _draw_polygon_on_image(uint32_t destination, Vector* points, uint32_t points_count, Color color);
void draw_polygon_on_image(uint32_t destination, Vector* points, uint32_t points_count, Color* color) {
  _draw_polygon_on_image(destination, points, points_count, *color);
}

NULL0_IMPORT("draw_rectangle_rounded_on_image")
extern void _draw_rectangle_rounded_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Color color);
void draw_rectangle_rounded_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, Color* color) {
  _draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, *color);
}

NULL0_IMPORT("draw_image_on_image")
extern void _draw_image_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY);
void draw_image_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY) {
  _draw_image_on_image(destination, src, posX, posY);
}

NULL0_IMPORT("draw_image_tint_on_image")
extern void _draw_image_tint_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, Color tint);
void draw_image_tint_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, Color* tint) {
  _draw_image_tint_on_image(destination, src, posX, posY, *tint);
}

NULL0_IMPORT("draw_image_rotated_on_image")
extern void _draw_image_rotated_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, int32_t filter);
void draw_image_rotated_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, int32_t filter) {
  _draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter);
}

NULL0_IMPORT("draw_image_flipped_on_image")
extern void _draw_image_flipped_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);
void draw_image_flipped_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  _draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

NULL0_IMPORT("draw_image_scaled_on_image")
extern void _draw_image_scaled_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, int32_t filter);
void draw_image_scaled_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, int32_t filter) {
  _draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

NULL0_IMPORT("draw_text_on_image")
extern void _draw_text_on_image(uint32_t destination, uint32_t font, char* text, int32_t posX, int32_t posY, Color color);
void draw_text_on_image(uint32_t destination, uint32_t font, char* text, int32_t posX, int32_t posY, Color* color) {
  _draw_text_on_image(destination, font, text, posX, posY, *color);
}

NULL0_IMPORT("draw_rectangle_outline")
extern void _draw_rectangle_outline(int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t thickness, Color color);
void draw_rectangle_outline(int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t thickness, Color* color) {
  _draw_rectangle_outline(posX, posY, width, height, thickness, *color);
}

NULL0_IMPORT("draw_triangle_outline")
extern void _draw_triangle_outline(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t thickness, Color color);
void draw_triangle_outline(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t thickness, Color* color) {
  _draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, *color);
}

NULL0_IMPORT("draw_ellipse_outline")
extern void _draw_ellipse_outline(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t thickness, Color color);
void draw_ellipse_outline(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t thickness, Color* color) {
  _draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, *color);
}

NULL0_IMPORT("draw_circle_outline")
extern void _draw_circle_outline(int32_t centerX, int32_t centerY, int32_t radius, int32_t thickness, Color color);
void draw_circle_outline(int32_t centerX, int32_t centerY, int32_t radius, int32_t thickness, Color* color) {
  _draw_circle_outline(centerX, centerY, radius, thickness, *color);
}

NULL0_IMPORT("draw_polygon_outline")
extern void _draw_polygon_outline(Vector* points, uint32_t points_count, int32_t thickness, Color color);
void draw_polygon_outline(Vector* points, uint32_t points_count, int32_t thickness, Color* color) {
  _draw_polygon_outline(points, points_count, thickness, *color);
}

NULL0_IMPORT("draw_arc_outline")
extern void _draw_arc_outline(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, int32_t thickness, Color color);
void draw_arc_outline(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, int32_t thickness, Color* color) {
  _draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, *color);
}

NULL0_IMPORT("draw_rectangle_rounded_outline")
extern void _draw_rectangle_rounded_outline(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, Color color);
void draw_rectangle_rounded_outline(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, Color* color) {
  _draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, *color);
}

NULL0_IMPORT("draw_rectangle_outline_on_image")
extern void _draw_rectangle_outline_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t thickness, Color color);
void draw_rectangle_outline_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t thickness, Color* color) {
  _draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, *color);
}

NULL0_IMPORT("draw_triangle_outline_on_image")
extern void _draw_triangle_outline_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t thickness, Color color);
void draw_triangle_outline_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t thickness, Color* color) {
  _draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, *color);
}

NULL0_IMPORT("draw_ellipse_outline_on_image")
extern void _draw_ellipse_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t thickness, Color color);
void draw_ellipse_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t thickness, Color* color) {
  _draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, *color);
}

NULL0_IMPORT("draw_circle_outline_on_image")
extern void _draw_circle_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, int32_t thickness, Color color);
void draw_circle_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, int32_t thickness, Color* color) {
  _draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, *color);
}

NULL0_IMPORT("draw_polygon_outline_on_image")
extern void _draw_polygon_outline_on_image(uint32_t destination, Vector* points, uint32_t points_count, int32_t thickness, Color color);
void draw_polygon_outline_on_image(uint32_t destination, Vector* points, uint32_t points_count, int32_t thickness, Color* color) {
  _draw_polygon_outline_on_image(destination, points, points_count, thickness, *color);
}

NULL0_IMPORT("draw_rectangle_rounded_outline_on_image")
extern void _draw_rectangle_rounded_outline_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, Color color);
void draw_rectangle_rounded_outline_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, Color* color) {
  _draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, *color);
}


// GUI

NULL0_IMPORT("gui_begin_window")
extern bool _gui_begin_window(char* title, Rectangle rect);
bool gui_begin_window(char* title, Rectangle* rect) {
  return _gui_begin_window(title, *rect);
}

NULL0_IMPORT("gui_end_window")
extern void _gui_end_window(void);
void gui_end_window(void) {
  _gui_end_window();
}

NULL0_IMPORT("gui_button")
extern bool _gui_button(char* label);
bool gui_button(char* label) {
  return _gui_button(label);
}

NULL0_IMPORT("gui_label")
extern void _gui_label(char* text);
void gui_label(char* text) {
  _gui_label(text);
}

NULL0_IMPORT("gui_text")
extern void _gui_text(char* text);
void gui_text(char* text) {
  _gui_text(text);
}

NULL0_IMPORT("gui_checkbox")
extern bool _gui_checkbox(char* label, bool state);
bool gui_checkbox(char* label, bool state) {
  return _gui_checkbox(label, state);
}

NULL0_IMPORT("gui_slider")
extern float _gui_slider(float value, float low, float high);
float gui_slider(float value, float low, float high) {
  return _gui_slider(value, low, high);
}

NULL0_IMPORT("gui_layout_row")
extern void _gui_layout_row(int32_t* widths, uint32_t widths_count, int32_t height);
void gui_layout_row(int32_t* widths, uint32_t widths_count, int32_t height) {
  _gui_layout_row(widths, widths_count, height);
}

NULL0_IMPORT("gui_end")
extern void _gui_end(void);
void gui_end(void) {
  _gui_end();
}

NULL0_IMPORT("gui_draw")
extern void _gui_draw(uint32_t dst);
void gui_draw(uint32_t dst) {
  _gui_draw(dst);
}


// INPUT

NULL0_IMPORT("key_pressed")
extern bool _key_pressed(int32_t key);
bool key_pressed(int32_t key) {
  return _key_pressed(key);
}

NULL0_IMPORT("key_down")
extern bool _key_down(int32_t key);
bool key_down(int32_t key) {
  return _key_down(key);
}

NULL0_IMPORT("key_released")
extern bool _key_released(int32_t key);
bool key_released(int32_t key) {
  return _key_released(key);
}

NULL0_IMPORT("key_up")
extern bool _key_up(int32_t key);
bool key_up(int32_t key) {
  return _key_up(key);
}

NULL0_IMPORT("gamepad_button_pressed")
extern bool _gamepad_button_pressed(int32_t gamepad, int32_t button);
bool gamepad_button_pressed(int32_t gamepad, int32_t button) {
  return _gamepad_button_pressed(gamepad, button);
}

NULL0_IMPORT("gamepad_button_down")
extern bool _gamepad_button_down(int32_t gamepad, int32_t button);
bool gamepad_button_down(int32_t gamepad, int32_t button) {
  return _gamepad_button_down(gamepad, button);
}

NULL0_IMPORT("gamepad_button_released")
extern bool _gamepad_button_released(int32_t gamepad, int32_t button);
bool gamepad_button_released(int32_t gamepad, int32_t button) {
  return _gamepad_button_released(gamepad, button);
}

NULL0_IMPORT("mouse_position")
extern Vector* _mouse_position(void);
Vector* mouse_position(void) {
  return _mouse_position();
}

NULL0_IMPORT("mouse_button_pressed")
extern bool _mouse_button_pressed(int32_t button);
bool mouse_button_pressed(int32_t button) {
  return _mouse_button_pressed(button);
}

NULL0_IMPORT("mouse_button_down")
extern bool _mouse_button_down(int32_t button);
bool mouse_button_down(int32_t button) {
  return _mouse_button_down(button);
}

NULL0_IMPORT("mouse_button_released")
extern bool _mouse_button_released(int32_t button);
bool mouse_button_released(int32_t button) {
  return _mouse_button_released(button);
}

NULL0_IMPORT("mouse_button_up")
extern bool _mouse_button_up(int32_t button);
bool mouse_button_up(int32_t button) {
  return _mouse_button_up(button);
}


// SOUND

NULL0_IMPORT("load_sound")
extern uint32_t _load_sound(char* filename);
uint32_t load_sound(char* filename) {
  return _load_sound(filename);
}

NULL0_IMPORT("play_sound")
extern void _play_sound(uint32_t sound, bool loop);
void play_sound(uint32_t sound, bool loop) {
  _play_sound(sound, loop);
}

NULL0_IMPORT("stop_sound")
extern void _stop_sound(uint32_t sound);
void stop_sound(uint32_t sound) {
  _stop_sound(sound);
}

NULL0_IMPORT("unload_sound")
extern void _unload_sound(uint32_t sound);
void unload_sound(uint32_t sound) {
  _unload_sound(sound);
}

NULL0_IMPORT("tts_sound")
extern uint32_t _tts_sound(char* text, bool phonetic, int32_t pitch, int32_t speed, int32_t throat, int32_t mouth, bool sing);
uint32_t tts_sound(char* text, bool phonetic, int32_t pitch, int32_t speed, int32_t throat, int32_t mouth, bool sing) {
  return _tts_sound(text, phonetic, pitch, speed, throat, mouth, sing);
}

NULL0_IMPORT("sfx_sound")
extern uint32_t _sfx_sound(SfxParams params);
uint32_t sfx_sound(SfxParams* params) {
  return _sfx_sound(*params);
}

NULL0_IMPORT("sfx_generate")
extern SfxParams* _sfx_generate(int32_t type_);
SfxParams* sfx_generate(int32_t type_) {
  return _sfx_generate(type_);
}


// TILE

NULL0_IMPORT("load_tilemap")
extern uint32_t _load_tilemap(char* filename);
uint32_t load_tilemap(char* filename) {
  return _load_tilemap(filename);
}

NULL0_IMPORT("unload_tilemap")
extern void _unload_tilemap(uint32_t tilemap);
void unload_tilemap(uint32_t tilemap) {
  _unload_tilemap(tilemap);
}

NULL0_IMPORT("tile_update")
extern void _tile_update(uint32_t tilemap, float deltaTime);
void tile_update(uint32_t tilemap, float deltaTime) {
  _tile_update(tilemap, deltaTime);
}

NULL0_IMPORT("tile_map_size")
extern Dimensions* _tile_map_size(uint32_t tilemap);
Dimensions* tile_map_size(uint32_t tilemap) {
  return _tile_map_size(tilemap);
}

NULL0_IMPORT("tile_tile_size")
extern Dimensions* _tile_tile_size(uint32_t tilemap);
Dimensions* tile_tile_size(uint32_t tilemap) {
  return _tile_tile_size(tilemap);
}

NULL0_IMPORT("tile_map_prop")
extern TilemapProp* _tile_map_prop(uint32_t tilemap, char* name);
TilemapProp* tile_map_prop(uint32_t tilemap, char* name) {
  return _tile_map_prop(tilemap, name);
}

NULL0_IMPORT("tile_map_prop_count")
extern int32_t _tile_map_prop_count(uint32_t tilemap);
int32_t tile_map_prop_count(uint32_t tilemap) {
  return _tile_map_prop_count(tilemap);
}

NULL0_IMPORT("tile_map_prop_at")
extern TilemapProp* _tile_map_prop_at(uint32_t tilemap, int32_t index);
TilemapProp* tile_map_prop_at(uint32_t tilemap, int32_t index) {
  return _tile_map_prop_at(tilemap, index);
}

NULL0_IMPORT("tile_draw")
extern void _tile_draw(uint32_t tilemap, int32_t posX, int32_t posY);
void tile_draw(uint32_t tilemap, int32_t posX, int32_t posY) {
  _tile_draw(tilemap, posX, posY);
}

NULL0_IMPORT("tile_draw_tint")
extern void _tile_draw_tint(uint32_t tilemap, int32_t posX, int32_t posY, Color tint);
void tile_draw_tint(uint32_t tilemap, int32_t posX, int32_t posY, Color* tint) {
  _tile_draw_tint(tilemap, posX, posY, *tint);
}

NULL0_IMPORT("tile_draw_on_image")
extern void _tile_draw_on_image(uint32_t dst, uint32_t tilemap, int32_t posX, int32_t posY);
void tile_draw_on_image(uint32_t dst, uint32_t tilemap, int32_t posX, int32_t posY) {
  _tile_draw_on_image(dst, tilemap, posX, posY);
}

NULL0_IMPORT("tilemap_image")
extern uint32_t _tilemap_image(uint32_t tilemap);
uint32_t tilemap_image(uint32_t tilemap) {
  return _tilemap_image(tilemap);
}

NULL0_IMPORT("tile_layer_count")
extern int32_t _tile_layer_count(uint32_t tilemap);
int32_t tile_layer_count(uint32_t tilemap) {
  return _tile_layer_count(tilemap);
}

NULL0_IMPORT("tile_layer_index")
extern int32_t _tile_layer_index(uint32_t tilemap, char* name);
int32_t tile_layer_index(uint32_t tilemap, char* name) {
  return _tile_layer_index(tilemap, name);
}

NULL0_IMPORT("tile_layer_name")
extern char* _tile_layer_name(uint32_t tilemap, int32_t layer);
char* tile_layer_name(uint32_t tilemap, int32_t layer) {
  return _tile_layer_name(tilemap, layer);
}

NULL0_IMPORT("tile_layer_type")
extern int32_t _tile_layer_type(uint32_t tilemap, int32_t layer);
int32_t tile_layer_type(uint32_t tilemap, int32_t layer) {
  return _tile_layer_type(tilemap, layer);
}

NULL0_IMPORT("tile_layer_size")
extern Dimensions* _tile_layer_size(uint32_t tilemap, int32_t layer);
Dimensions* tile_layer_size(uint32_t tilemap, int32_t layer) {
  return _tile_layer_size(tilemap, layer);
}

NULL0_IMPORT("tile_layer_visible")
extern bool _tile_layer_visible(uint32_t tilemap, int32_t layer);
bool tile_layer_visible(uint32_t tilemap, int32_t layer) {
  return _tile_layer_visible(tilemap, layer);
}

NULL0_IMPORT("tile_layer_prop")
extern TilemapProp* _tile_layer_prop(uint32_t tilemap, int32_t layer, char* name);
TilemapProp* tile_layer_prop(uint32_t tilemap, int32_t layer, char* name) {
  return _tile_layer_prop(tilemap, layer, name);
}

NULL0_IMPORT("tile_layer_prop_count")
extern int32_t _tile_layer_prop_count(uint32_t tilemap, int32_t layer);
int32_t tile_layer_prop_count(uint32_t tilemap, int32_t layer) {
  return _tile_layer_prop_count(tilemap, layer);
}

NULL0_IMPORT("tile_layer_prop_at")
extern TilemapProp* _tile_layer_prop_at(uint32_t tilemap, int32_t layer, int32_t index);
TilemapProp* tile_layer_prop_at(uint32_t tilemap, int32_t layer, int32_t index) {
  return _tile_layer_prop_at(tilemap, layer, index);
}

NULL0_IMPORT("tile_draw_layer")
extern void _tile_draw_layer(uint32_t tilemap, int32_t layer, int32_t posX, int32_t posY);
void tile_draw_layer(uint32_t tilemap, int32_t layer, int32_t posX, int32_t posY) {
  _tile_draw_layer(tilemap, layer, posX, posY);
}

NULL0_IMPORT("tile_draw_layer_tint")
extern void _tile_draw_layer_tint(uint32_t tilemap, int32_t layer, int32_t posX, int32_t posY, Color tint);
void tile_draw_layer_tint(uint32_t tilemap, int32_t layer, int32_t posX, int32_t posY, Color* tint) {
  _tile_draw_layer_tint(tilemap, layer, posX, posY, *tint);
}

NULL0_IMPORT("tile_draw_layer_on_image")
extern void _tile_draw_layer_on_image(uint32_t dst, uint32_t tilemap, int32_t layer, int32_t posX, int32_t posY);
void tile_draw_layer_on_image(uint32_t dst, uint32_t tilemap, int32_t layer, int32_t posX, int32_t posY) {
  _tile_draw_layer_on_image(dst, tilemap, layer, posX, posY);
}

NULL0_IMPORT("tile_layer_image")
extern uint32_t _tile_layer_image(uint32_t tilemap, int32_t layer);
uint32_t tile_layer_image(uint32_t tilemap, int32_t layer) {
  return _tile_layer_image(tilemap, layer);
}

NULL0_IMPORT("tile_get_tile")
extern int32_t _tile_get_tile(uint32_t tilemap, int32_t layer, int32_t column, int32_t row);
int32_t tile_get_tile(uint32_t tilemap, int32_t layer, int32_t column, int32_t row) {
  return _tile_get_tile(tilemap, layer, column, row);
}

NULL0_IMPORT("tile_set_tile")
extern void _tile_set_tile(uint32_t tilemap, int32_t layer, int32_t column, int32_t row, int32_t gid);
void tile_set_tile(uint32_t tilemap, int32_t layer, int32_t column, int32_t row, int32_t gid) {
  _tile_set_tile(tilemap, layer, column, row, gid);
}

NULL0_IMPORT("tile_draw_tile")
extern void _tile_draw_tile(uint32_t tilemap, int32_t gid, int32_t posX, int32_t posY);
void tile_draw_tile(uint32_t tilemap, int32_t gid, int32_t posX, int32_t posY) {
  _tile_draw_tile(tilemap, gid, posX, posY);
}

NULL0_IMPORT("tile_image")
extern uint32_t _tile_image(uint32_t tilemap, int32_t gid);
uint32_t tile_image(uint32_t tilemap, int32_t gid) {
  return _tile_image(tilemap, gid);
}

NULL0_IMPORT("tile_gid_prop")
extern TilemapProp* _tile_gid_prop(uint32_t tilemap, int32_t gid, char* name);
TilemapProp* tile_gid_prop(uint32_t tilemap, int32_t gid, char* name) {
  return _tile_gid_prop(tilemap, gid, name);
}

NULL0_IMPORT("tile_gid_prop_count")
extern int32_t _tile_gid_prop_count(uint32_t tilemap, int32_t gid);
int32_t tile_gid_prop_count(uint32_t tilemap, int32_t gid) {
  return _tile_gid_prop_count(tilemap, gid);
}

NULL0_IMPORT("tile_gid_prop_at")
extern TilemapProp* _tile_gid_prop_at(uint32_t tilemap, int32_t gid, int32_t index);
TilemapProp* tile_gid_prop_at(uint32_t tilemap, int32_t gid, int32_t index) {
  return _tile_gid_prop_at(tilemap, gid, index);
}

NULL0_IMPORT("tile_object_count")
extern int32_t _tile_object_count(uint32_t tilemap, int32_t layer);
int32_t tile_object_count(uint32_t tilemap, int32_t layer) {
  return _tile_object_count(tilemap, layer);
}

NULL0_IMPORT("tile_object")
extern TilemapObject* _tile_object(uint32_t tilemap, int32_t layer, int32_t index);
TilemapObject* tile_object(uint32_t tilemap, int32_t layer, int32_t index) {
  return _tile_object(tilemap, layer, index);
}

NULL0_IMPORT("tile_object_index")
extern int32_t _tile_object_index(uint32_t tilemap, int32_t layer, char* name);
int32_t tile_object_index(uint32_t tilemap, int32_t layer, char* name) {
  return _tile_object_index(tilemap, layer, name);
}

NULL0_IMPORT("tile_object_prop")
extern TilemapProp* _tile_object_prop(uint32_t tilemap, int32_t layer, int32_t index, char* name);
TilemapProp* tile_object_prop(uint32_t tilemap, int32_t layer, int32_t index, char* name) {
  return _tile_object_prop(tilemap, layer, index, name);
}

NULL0_IMPORT("tile_object_prop_count")
extern int32_t _tile_object_prop_count(uint32_t tilemap, int32_t layer, int32_t index);
int32_t tile_object_prop_count(uint32_t tilemap, int32_t layer, int32_t index) {
  return _tile_object_prop_count(tilemap, layer, index);
}

NULL0_IMPORT("tile_object_prop_at")
extern TilemapProp* _tile_object_prop_at(uint32_t tilemap, int32_t layer, int32_t index, int32_t propIndex);
TilemapProp* tile_object_prop_at(uint32_t tilemap, int32_t layer, int32_t index, int32_t propIndex) {
  return _tile_object_prop_at(tilemap, layer, index, propIndex);
}


// TYPES


// UTILITIES

NULL0_IMPORT("current_time")
extern uint64_t _current_time(void);
uint64_t current_time(void) {
  return _current_time();
}

NULL0_IMPORT("delta_time")
extern float _delta_time(void);
float delta_time(void) {
  return _delta_time();
}

NULL0_IMPORT("random_int")
extern int32_t _random_int(int32_t min, int32_t max);
int32_t random_int(int32_t min, int32_t max) {
  return _random_int(min, max);
}

NULL0_IMPORT("random_seed_get")
extern uint64_t _random_seed_get(void);
uint64_t random_seed_get(void) {
  return _random_seed_get();
}

NULL0_IMPORT("random_seed_set")
extern void _random_seed_set(uint64_t seed);
void random_seed_set(uint64_t seed) {
  _random_seed_set(seed);
}


// RTS startup: null0 calls _initialize (this wasm module is built as a
// WASI reactor) once, before any other export - hook it to bring up the
// Haskell RTS, since -no-hs-main means nothing else will.
#include <HsFFI.h>

__attribute__((constructor))
static void null0_hs_init(void) {
  int argc = 0;
  hs_init(&argc, 0);
}