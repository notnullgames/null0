// Null0 host - graphics - generated 2023-12-29T06:49:42.369Z
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <pntr.h>

// Create a new blank image
uint32_t null0_new_image(int32_t width, int32_t height, int32_t color) {
  return null0_add_image(pntr_gen_image_color(width, height, pntr_get_color(color)));
}

// Copy an image to a new image
uint32_t null0_image_copy(uint32_t image) {
  return null0_add_image(pntr_image_copy(null0_images[image]));
}

// Create an image from a region of another image
uint32_t null0_image_subimage(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  return null0_add_image(pntr_image_subimage(null0_images[image], x, y, width, height));
}

// Clear the screen
void null0_clear(uint32_t color) {
  return pntr_clear_background(null0_screen, pntr_get_color(color));
}

// Draw a single pixel on the screen
void null0_draw_point(int32_t x, int32_t y, int32_t color) {
  return pntr_draw_point(null0_screen, x, y, pntr_get_color(color));
}

// Draw a line on the screen
void null0_draw_line(int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, int32_t color) {
  return pntr_draw_line(null0_screen, startPosX, startPosY, endPosX, endPosY, pntr_get_color(color));
}

// Draw a filled rectangle on the screen
void null0_draw_rectangle(int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t color) {
  return pntr_draw_rectangle_fill(null0_screen, posX, posY, width, height, pntr_get_color(color));
}

// Draw a filled triangle on the screen
void null0_draw_triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t color) {
  return pntr_draw_triangle_fill(null0_screen, x1, y1, x2, y2, x3, y3, pntr_get_color(color));
}

// Draw a filled ellipse on the screen
void null0_draw_ellipse(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t color) {
  // printf("null0_draw_ellipse(%d, %d, %d, %d, (%d, %d, %d, %d))\n", centerX, centerY, radiusX, radiusY, color.r, color.g, color.b, color.a);
  return pntr_draw_ellipse_fill(null0_screen, centerX, centerY, radiusX, radiusY, pntr_get_color(color));
}

// Draw a filled circle on the screen
void null0_draw_circle(int32_t centerX, int32_t centerY, int32_t radius, int32_t color) {
  return pntr_draw_circle_fill(null0_screen, centerX, centerY, radius, pntr_get_color(color));
}

// Draw a filled polygon on the screen
void null0_draw_polygon(pntr_vector* points, int32_t numPoints, int32_t color) {
  return pntr_draw_polygon_fill(null0_screen, points, numPoints, pntr_get_color(color));
}

// Draw several lines on the screen
void null0_draw_polyline(pntr_vector* points, int32_t numPoints, int32_t color) {
  return pntr_draw_polyline(null0_screen, points, numPoints, pntr_get_color(color));
}

// Draw a filled arc on the screen
void null0_draw_arc(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, int32_t color) {
  return pntr_draw_arc_fill(null0_screen, centerX, centerY, radius, startAngle, endAngle, segments, pntr_get_color(color));
}

// Draw a filled round-rectangle on the screen
void null0_draw_rectangle_rounded(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t color) {
  return pntr_draw_rectangle_rounded_fill(null0_screen, x, y, width, height, cornerRadius, pntr_get_color(color));
}

// Draw an image on the screen
void null0_draw_image(uint32_t src, int32_t posX, int32_t posY) {
  return pntr_draw_image(null0_screen, null0_images[src], posX, posY);
}

// Draw a tinted image on the screen
void null0_draw_image_tint(uint32_t src, int32_t posX, int32_t posY, int32_t tint) {
  return pntr_draw_image_tint(null0_screen, null0_images[src], posX, posY, pntr_get_color(tint));
}

// Draw an image, rotated, on the screen
void null0_draw_image_rotated(uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {
  return pntr_draw_image_rotated(null0_screen, null0_images[src], posX, posY, degrees, offsetX, offsetY, filter);
}

// Draw an image, flipped, on the screen
void null0_draw_image_flipped(uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  return pntr_draw_image_flipped(null0_screen, null0_images[src], posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

// Draw an image, scaled, on the screen
void null0_draw_image_scaled(uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {
  return pntr_draw_image_scaled(null0_screen, null0_images[src], posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

// Draw some text on the screen
void null0_draw_text(uint32_t font, char* text, int32_t posX, int32_t posY, int32_t color) {
  return pntr_draw_text(null0_screen, null0_fonts[font], text, posX, posY, pntr_get_color(color));
}

// Save an image to persistant storage
void null0_save_image(uint32_t image, char* fileName) {
  pntr_save_image(null0_images[image], fileName);
}

// Load an image from a file in cart
uint32_t null0_load_image(char* fileName) {
  return null0_add_image(pntr_load_image(fileName));
}

// Resize an image, in-place
void null0_image_resize(uint32_t image, int32_t newWidth, int32_t newHeight, int32_t offsetX, int32_t offsetY, int32_t fill) {
  pntr_image_resize_canvas(null0_images[image], newWidth, newHeight, offsetX, offsetY, pntr_get_color(fill));
}

// Scale an image, in-place
void null0_image_scale(uint32_t image, float scaleX, float scaleY, pntr_filter filter) {
  pntr_image_scale(null0_images[image], scaleX, scaleY, filter);
}

// Replace a color in an image, in-place
void null0_image_color_replace(uint32_t image, int32_t color, int32_t replace) {
  pntr_image_color_replace(null0_images[image], pntr_get_color(color), pntr_get_color(replace));
}

// Tint a color in an image, in-place
void null0_image_color_tint(uint32_t image, int32_t color) {
  pntr_image_color_tint(null0_images[image], pntr_get_color(color));
}

// Fade a color in an image, in-place
void null0_image_color_fade(uint32_t image, float alpha) {
  pntr_image_color_fade(null0_images[image], alpha);
}

// Copy a font to a new font
uint32_t null0_font_copy(uint32_t font) {
  return null0_add_font(pntr_font_copy(null0_fonts[font]));
}

// Scale a font, return a new font
uint32_t null0_font_scale(uint32_t font, float scaleX, float scaleY, pntr_filter filter) {
  return null0_add_font(pntr_font_scale(null0_fonts[font], scaleX, scaleY, filter));
}

// Load a BMF font from a file in cart
uint32_t null0_load_font_bmf(char* fileName, char* characters) {
  return null0_add_font(pntr_load_font_bmf(fileName, characters));
}

// Load a BMF font from an image
uint32_t null0_load_font_bmf_from_image(uint32_t image, char* characters) {
  return null0_add_font(pntr_load_font_bmf_from_image(null0_images[image], characters));
}

// Measure the size of some text
pntr_vector null0_measure_text(uint32_t font, char* text) {
  pntr_vector r = pntr_measure_text_ex(null0_fonts[font], text, 0);
  return r;
}

// Meaure an image (use 0 for screen)
pntr_vector null0_measure_image(uint32_t image) {
  pntr_vector r = (pntr_vector){.x = null0_images[image]->width, .y = null0_images[image]->height};
  return r;
}

// Load a TTY font from a file in cart
uint32_t null0_load_font_tty(char* fileName, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return null0_add_font(pntr_load_font_tty(fileName, glyphWidth, glyphHeight, characters));
}

// Load a TTY font from an image
uint32_t null0_load_font_tty_from_image(uint32_t image, int32_t glyphWidth, int32_t glyphHeight, char* characters) {
  return null0_add_font(pntr_load_font_tty_from_image(null0_images[image], glyphWidth, glyphHeight, characters));
}

// Load a TTF font from a file in cart
uint32_t null0_load_font_ttf(char* fileName, int32_t fontSize) {
  printf("null0_load_font_ttf(%s, %d)\n", fileName, fontSize);
  return null0_add_font(pntr_load_font_ttf(fileName, fontSize));
}

// Invert the colors in an image, in-place
void null0_image_color_invert(uint32_t image) {
  pntr_image_color_invert(null0_images[image]);
}

// Calculate a rectangle representing the available alpha border in an image
pntr_rectangle null0_image_alpha_border(uint32_t image, float threshold) {
  return pntr_image_alpha_border(null0_images[image], threshold);
}

// Crop an image, in-place
void null0_image_crop(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {
  pntr_image_crop(null0_images[image], x, y, width, height);
}

// Crop an image based on the alpha border, in-place
void null0_image_alpha_crop(uint32_t image, float threshold) {
  pntr_image_alpha_crop(null0_images[image], threshold);
}

// Adjust the brightness of an image, in-place
void null0_image_color_brightness(uint32_t image, float factor) {
  pntr_image_color_brightness(null0_images[image], factor);
}

// Flip an image, in-place
void null0_image_flip(uint32_t image, bool horizontal, bool vertical) {
  pntr_image_flip(null0_images[image], horizontal, vertical);
}

// Change the contrast of an image, in-place
void null0_image_color_contrast(uint32_t image, float contrast) {
  pntr_image_color_contrast(null0_images[image], contrast);
}

// Use an image as an alpha-mask on another image
void null0_image_alpha_mask(uint32_t image, uint32_t alphaMask, int32_t posX, int32_t posY) {
  pntr_image_alpha_mask(null0_images[image], null0_images[alphaMask], posX, posY);
}

// Create a new image, rotating another image
uint32_t null0_image_rotate(uint32_t image, float degrees, pntr_filter filter) {
  return null0_add_image(pntr_image_rotate(null0_images[image], degrees, filter));
}

// Create a new image of a gradient
uint32_t null0_image_gradient(int32_t width, int32_t height, int32_t topLeft, int32_t topRight, int32_t bottomLeft, int32_t bottomRight) {
  return null0_add_image(pntr_gen_image_gradient(width, height, pntr_get_color(topLeft), pntr_get_color(topRight), pntr_get_color(bottomLeft), pntr_get_color(bottomRight)));
}

// Unload an image
void null0_unload_image(uint32_t image) {
  pntr_unload_image(null0_images[image]);
}

// Unload a font
void null0_unload_font(uint32_t font) {
  pntr_unload_font(null0_fonts[font]);
}

// Clear an image
void null0_clear_on_image(uint32_t destination, int32_t color) {
  pntr_clear_background(null0_images[destination], pntr_get_color(color));
}

// Draw a single pixel on an image
void null0_draw_point_on_image(uint32_t destination, int32_t x, int32_t y, int32_t color) {
  pntr_draw_point(null0_images[destination], x, y, pntr_get_color(color));
}

// Draw a line on an image
void null0_draw_line_on_image(uint32_t destination, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, int32_t color) {
  pntr_draw_line(null0_images[destination], startPosX, startPosY, endPosX, endPosY, pntr_get_color(color));
}

// Draw a filled rectangle on an image
void null0_draw_rectangle_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t color) {
  pntr_draw_rectangle_fill(null0_images[destination], posX, posY, width, height, pntr_get_color(color));
}

// Draw a filled triangle on an image
void null0_draw_triangle_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t color) {
  pntr_draw_triangle_fill(null0_images[destination], x1, y1, x2, y2, x3, y3, pntr_get_color(color));
}

// Draw a filled ellipse on an image
void null0_draw_ellipse_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t color) {
  pntr_draw_ellipse_fill(null0_images[destination], centerX, centerY, radiusX, radiusY, pntr_get_color(color));
}

// Draw a circle on an image
void null0_draw_circle_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, int32_t color) {
  pntr_draw_circle_fill(null0_images[destination], centerX, centerY, radius, pntr_get_color(color));
}

// Draw a filled polygon on an image
void null0_draw_polygon_on_image(uint32_t destination, pntr_vector* points, int32_t numPoints, int32_t color) {
  pntr_draw_polygon_fill(null0_images[destination], points, numPoints, pntr_get_color(color));
}

// Draw several lines on an image
void null0_draw_polyline_on_image(uint32_t destination, pntr_vector* points, int32_t numPoints, int32_t color) {
  pntr_draw_polyline(null0_images[destination], points, numPoints, pntr_get_color(color));
}

// Draw a filled round-rectangle on an image
void null0_draw_rectangle_rounded_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t color) {
  pntr_draw_rectangle_rounded_fill(null0_images[destination], x, y, width, height, cornerRadius, pntr_get_color(color));
}

// Draw an image on an image
void null0_draw_image_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY) {
  pntr_draw_image(null0_images[destination], null0_images[src], posX, posY);
}

// Draw a tinted image on an image
void null0_draw_image_tint_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, int32_t tint) {
  pntr_draw_image_tint(null0_images[destination], null0_images[src], posX, posY, pntr_get_color(tint));
}

// Draw an image, rotated, on an image
void null0_draw_image_rotated_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {
  pntr_draw_image_rotated(null0_images[destination], null0_images[src], posX, posY, degrees, offsetX, offsetY, filter);
}

// Draw an image, flipped, on an image
void null0_draw_image_flipped_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
  pntr_draw_image_flipped(null0_images[destination], null0_images[src], posX, posY, flipHorizontal, flipVertical, flipDiagonal);
}

// Draw an image, scaled, on an image
void null0_draw_image_scaled_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {
  pntr_draw_image_scaled(null0_images[destination], null0_images[src], posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
}

// Draw some text on an image
void null0_draw_text_on_image(uint32_t destination, uint32_t font, char* text, int32_t posX, int32_t posY, int32_t color) {
  pntr_draw_text(null0_images[destination], null0_fonts[font], text, posX, posY, pntr_get_color(color));
}

// Draw a 1px outlined rectangle on the screen
void null0_draw_rectangle_outline(int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t color) {
  
  pntr_draw_rectangle(null0_screen, posX, posY, width, height, pntr_get_color(color));
}

// Draw a 1px outlined triangle on the screen
void null0_draw_triangle_outline(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t color) {
  pntr_draw_triangle(null0_screen, x1, y1, x2, y2, x3, y3, pntr_get_color(color));
}

// Draw a 1px outlined ellipse on the screen
void null0_draw_ellipse_outline(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t color) {
  return pntr_draw_ellipse(null0_screen, centerX, centerY, radiusX, radiusY, pntr_get_color(color));
}

// Draw a 1px outlined circle on the screen
void null0_draw_circle_outline(int32_t centerX, int32_t centerY, int32_t radius, int32_t color) {
  return pntr_draw_circle(null0_screen, centerX, centerY, radius, pntr_get_color(color));
}

// Draw a 1px outlined polygon on the screen
void null0_draw_polygon_outline(pntr_vector* points, int32_t numPoints, int32_t color) {
  return pntr_draw_polygon(null0_screen, points, numPoints, pntr_get_color(color));
}

// Draw a 1px outlined arc on the screen
void null0_draw_arc_outline(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, int32_t color) {
  return pntr_draw_arc(null0_screen, centerX, centerY, radius, startAngle, endAngle, segments, pntr_get_color(color));
}

// Draw a 1px outlined round-rectangle on the screen
void null0_draw_rectangle_rounded_outline(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t color) {
  pntr_draw_rectangle_rounded(null0_screen, x, y, width, height, cornerRadius, cornerRadius, cornerRadius, cornerRadius, pntr_get_color(color));
}

// Draw a 1px outlined rectangle on an image
void null0_draw_rectangle_outline_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t color) {
  pntr_draw_rectangle(null0_images[destination], posX, posY, width, height, pntr_get_color(color));
}

// Draw a 1px outlined triangle on an image
void null0_draw_triangle_outline_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t color) {
  pntr_draw_triangle(null0_images[destination], x1, y1, x2, y2, x3, y3, pntr_get_color(color));
}

// Draw a 1px outlined ellipse on an image
void null0_draw_ellipse_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t color) {
  pntr_draw_ellipse(null0_images[destination], centerX, centerY, radiusX, radiusY, pntr_get_color(color));
}

// Draw a 1px outlined circle on an image
void null0_draw_circle_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, int32_t color) {
  pntr_draw_circle(null0_images[destination], centerX, centerY, radius, pntr_get_color(color));
}

// Draw a 1px outlined polygon on an image
void null0_draw_polygon_outline_on_image(uint32_t destination, pntr_vector* points, int32_t numPoints, int32_t color) {
  pntr_draw_polygon(null0_images[destination], points, numPoints, pntr_get_color(color));
}

// Draw a 1px outlined round-rectangle on an image
void null0_draw_rectangle_rounded_outline_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t color) {
  pntr_draw_rectangle_rounded(null0_images[destination], x, y, width, height, cornerRadius, cornerRadius, cornerRadius, cornerRadius, pntr_get_color(color));
}
