// Null0 host - graphics - generated 2023-12-29T06:49:42.369Z
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <pntr.h>

// Create a new blank image
uint32_t null0_new_image(int32_t width, int32_t height, uint32_t color) {}

// Copy an image to a new image
uint32_t null0_image_copy(uint32_t image) {}

// Create an image from a region of another image
uint32_t null0_image_subimage(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {}

// Clear the screen
void null0_clear(uint32_t color) {}

// Draw a single pixel on the screen
void null0_draw_point(int32_t x, int32_t y, uint32_t color) {}

// Draw a line on the screen
void null0_draw_line(int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, uint32_t color) {}

// Draw a filled rectangle on the screen
void null0_draw_rectangle(int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {}

// Draw a filled triangle on the screen
void null0_draw_triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {}

// Draw a filled ellipse on the screen
void null0_draw_ellipse(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {}

// Draw a filled circle on the screen
void null0_draw_circle(int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {}

// Draw a filled polygon on the screen
void null0_draw_polygon(pntr_vector* points, int32_t numPoints, uint32_t color) {}

// Draw several lines on the screen
void null0_draw_polyline(pntr_vector* points, int32_t numPoints, uint32_t color) {}

// Draw a filled arc on the screen
void null0_draw_arc(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, uint32_t color) {}

// Draw a filled round-rectangle on the screen
void null0_draw_rectangle_rounded(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {}

// Draw an image on the screen
void null0_draw_image(uint32_t src, int32_t posX, int32_t posY) {}

// Draw a tinted image on the screen
void null0_draw_image_tint(uint32_t src, int32_t posX, int32_t posY, uint32_t tint) {}

// Draw an image, rotated, on the screen
void null0_draw_image_rotated(uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {}

// Draw an image, flipped, on the screen
void null0_draw_image_flipped(uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical) {}

// Draw an image, scaled, on the screen
void null0_draw_image_scaled(uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {}

// Draw some text on the screen
void null0_draw_text(uint32_t font, char* text, int32_t posX, int32_t posY, uint32_t color) {}

// Save an image to persistant storage
void null0_save_image(uint32_t image, char* filename) {}

// Load an image from a file in cart
uint32_t null0_load_image(char* filename) {}

// Resize an image, in-place
void null0_image_resize(uint32_t image, int32_t newWidth, int32_t newHeight, int32_t offsetX, int32_t offsetY, uint32_t fill) {}

// Scale an image, in-place
void null0_image_scale(uint32_t image, float scaleX, float scaleY, pntr_filter filter) {}

// Replace a color in an image, in-place
void null0_image_color_replace(uint32_t image, uint32_t color, uint32_t replace) {}

// Tint a color in an image, in-place
void null0_image_color_tint(uint32_t image, uint32_t color) {}

// Fade a color in an image, in-place
void null0_image_color_fade(uint32_t image, float alpha) {}

// Copy a font to a new font
uint32_t null0_font_copy(uint32_t font) {}

// Scale a font, return a new font
uint32_t null0_font_scale(uint32_t font, float scaleX, float scaleY, pntr_filter filter) {}

// Load a BMF font from a file in cart
uint32_t null0_load_font_bmf(char* filename, char* characters) {}

// Load a BMF font from an image
uint32_t null0_load_font_bmf_from_image(uint32_t image, char* characters) {}

// Measure the size of some text
pntr_vector null0_measure_text(uint32_t font, char* text) {}

// Meaure an image (use 0 for screen)
pntr_vector null0_measure_image(uint32_t image) {}

// Load a TTY font from a file in cart
uint32_t null0_load_font_tty(char* filename, int32_t glyphWidth, int32_t glyphHeight, char* characters) {}

// Load a TTY font from an image
uint32_t null0_load_font_tty_from_image(uint32_t image, int32_t glyphWidth, int32_t glyphHeight, char* characters) {}

// Load a TTF font from a file in cart
uint32_t null0_load_font_ttf(char* filename, int32_t fontSize) {}

// Invert the colors in an image, in-place
void null0_image_color_invert(uint32_t image) {}

// Calculate a rectangle representing the available alpha border in an image
pntr_rectangle null0_image_alpha_border(uint32_t image, float threshold) {}

// Crop an image, in-place
void null0_image_crop(uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height) {}

// Crop an image based on the alpha border, in-place
void null0_image_alpha_crop(uint32_t image, float threshold) {}

// Adjust the brightness of an image, in-place
void null0_image_color_brightness(uint32_t image, float factor) {}

// Flip an image, in-place
void null0_image_flip(uint32_t image, bool horizontal, bool vertical) {}

// Change the contrast of an image, in-place
void null0_image_color_contrast(uint32_t image, float contrast) {}

// Use an image as an alpha-mask on another image
void null0_image_alpha_mask(uint32_t image, uint32_t alphaMask, int32_t posX, int32_t posY) {}

// Create a new image, rotating another image
uint32_t null0_image_rotate(uint32_t image, float degrees, pntr_filter filter) {}

// Create a new image of a gradient
uint32_t null0_image_gradient(int32_t width, int32_t height, uint32_t topLeft, uint32_t topRight, uint32_t bottomLeft, uint32_t bottomRight) {}

// Unload an image
void null0_unload_image(uint32_t image) {}

// Unload a font
void null0_unload_font(uint32_t font) {}

// Clear an image
void null0_clear_on_image(uint32_t destination, uint32_t color) {}

// Draw a single pixel on an image
void null0_draw_point_on_image(uint32_t destination, int32_t x, int32_t y, uint32_t color) {}

// Draw a line on an image
void null0_draw_line_on_image(uint32_t destination, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, uint32_t color) {}

// Draw a filled rectangle on an image
void null0_draw_rectangle_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {}

// Draw a filled triangle on an image
void null0_draw_triangle_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {}

// Draw a filled ellipse on an image
void null0_draw_ellipse_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {}

// Draw a circle on an image
void null0_draw_circle_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {}

// Draw a filled polygon on an image
void null0_draw_polygon_on_image(uint32_t destination, pntr_vector* points, int32_t numPoints, uint32_t color) {}

// Draw several lines on an image
void null0_draw_polyline_on_image(uint32_t destination, pntr_vector* points, int32_t numPoints, uint32_t color) {}

// Draw a filled round-rectangle on an image
void null0_draw_rectangle_rounded_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {}

// Draw an image on an image
void null0_draw_image_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY) {}

// Draw a tinted image on an image
void null0_draw_image_tint_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, uint32_t tint) {}

// Draw an image, rotated, on an image
void null0_draw_image_rotated_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {}

// Draw an image, flipped, on an image
void null0_draw_image_flipped_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical) {}

// Draw an image, scaled, on an image
void null0_draw_image_scaled_on_image(uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {}

// Draw some text on an image
void null0_draw_text_on_image(uint32_t destination, uint32_t font, char* text, int32_t posX, int32_t posY, uint32_t color) {}

// Draw a 1px outlined rectangle on the screen
void null0_draw_rectangle_outline(int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {}

// Draw a 1px outlined triangle on the screen
void null0_draw_triangle_outline(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {}

// Draw a 1px outlined ellipse on the screen
void null0_draw_ellipse_outline(int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {}

// Draw a 1px outlined circle on the screen
void null0_draw_circle_outline(int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {}

// Draw a 1px outlined polygon on the screen
void null0_draw_polygon_outline(pntr_vector* points, int32_t numPoints, uint32_t color) {}

// Draw a 1px outlined arc on the screen
void null0_draw_arc_outline(int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, uint32_t color) {}

// Draw a 1px outlined round-rectangle on the screen
void null0_draw_rectangle_rounded_outline(int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {}

// Draw a 1px outlined rectangle on an image
void null0_draw_rectangle_outline_on_image(uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color) {}

// Draw a 1px outlined triangle on an image
void null0_draw_triangle_outline_on_image(uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color) {}

// Draw a 1px outlined ellipse on an image
void null0_draw_ellipse_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color) {}

// Draw a 1px outlined circle on an image
void null0_draw_circle_outline_on_image(uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color) {}

// Draw a 1px outlined polygon on an image
void null0_draw_polygon_outline_on_image(uint32_t destination, pntr_vector* points, int32_t numPoints, uint32_t color) {}

// Draw a 1px outlined round-rectangle on an image
void null0_draw_rectangle_rounded_outline_on_image(uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color) {}