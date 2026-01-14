#include "host_header.h"

// COLORS

// Tint a color with another color.
HOST_FUNCTION(uint32_t, color_tint, (uint32_t color, uint32_t tint), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_color tintHost = copy_color_from_cart(tint);
 uint32_t retHost = copy_color_to_cart(pntr_color_tint(colorHost, tintHost));
 return retHost;
})

// Fade a color.
HOST_FUNCTION(uint32_t, color_fade, (uint32_t color, float alpha), {
 pntr_color colorHost = copy_color_from_cart(color);
 uint32_t retHost = copy_color_to_cart(pntr_color_fade(colorHost, alpha));
 return retHost;
})

// Change the brightness of a color.
HOST_FUNCTION(uint32_t, color_brightness, (uint32_t color, float factor), {
 pntr_color colorHost = copy_color_from_cart(color);
 uint32_t retHost = copy_color_to_cart(pntr_color_brightness(colorHost, factor));
 return retHost;
})

// Invert a color.
HOST_FUNCTION(uint32_t, color_invert, (uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 uint32_t retHost = copy_color_to_cart(pntr_color_invert(colorHost));
 return retHost;
})

// Blend 2 colors together.
HOST_FUNCTION(uint32_t, color_alpha_blend, (uint32_t dst, uint32_t src), {
 pntr_color dstHost = copy_color_from_cart(dst);
 pntr_color srcHost = copy_color_from_cart(src);
 uint32_t retHost = copy_color_to_cart(pntr_color_alpha_blend(dstHost, srcHost));
 return retHost;
})

// Change contrast of a color.
HOST_FUNCTION(uint32_t, color_contrast, (uint32_t color, float contrast), {
 pntr_color colorHost = copy_color_from_cart(color);
 uint32_t retHost = copy_color_to_cart(pntr_color_contrast(colorHost, contrast));
 return retHost;
})

// Interpolate colors.
HOST_FUNCTION(uint32_t, color_bilinear_interpolate, (uint32_t color00, uint32_t color01, uint32_t color10, uint32_t color11, float coordinateX, float coordinateY), {
 pntr_color color00Host = copy_color_from_cart(color00);
 pntr_color color01Host = copy_color_from_cart(color01);
 pntr_color color10Host = copy_color_from_cart(color10);
 pntr_color color11Host = copy_color_from_cart(color11);
 uint32_t retHost = copy_color_to_cart(pntr_color_bilinear_interpolate(color00Host, color01Host, color10Host, color11Host, coordinateX, coordinateY));
 return retHost;
})


// GRAPHICS

// Create a new blank image.
HOST_FUNCTION(uint32_t, new_image, (int32_t width, int32_t height, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 uint32_t retHost = add_image(pntr_gen_image_color(width, height, colorHost));
 return retHost;
})

// Copy an image to a new image.
HOST_FUNCTION(uint32_t, image_copy, (uint32_t image), {
 uint32_t retHost = add_image(pntr_image_copy(images[image]));
 return retHost;
})

// Create an image from a region of another image.
HOST_FUNCTION(uint32_t, image_subimage, (uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height), {
 uint32_t retHost = add_image(pntr_image_subimage(images[image], x, y, width, height));
 return retHost;
})

// Clear the screen.
HOST_FUNCTION(void, clear, (uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_clear_background(images[0], colorHost);
})

// Draw a single pixel on the screen.
HOST_FUNCTION(void, draw_point, (int32_t x, int32_t y, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_point(images[0], x, y, colorHost);
})

// Draw a line on the screen.
HOST_FUNCTION(void, draw_line, (int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_line(images[0], startPosX, startPosY, endPosX, endPosY, colorHost);
})

// Draw a filled rectangle on the screen.
HOST_FUNCTION(void, draw_rectangle, (int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_rectangle_fill(images[0], posX, posY, width, height, colorHost);
})

// Draw a filled triangle on the screen.
HOST_FUNCTION(void, draw_triangle, (int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_triangle_fill(images[0], x1, y1, x2, y2, x3, y3, colorHost);
})

// Draw a filled ellipse on the screen.
HOST_FUNCTION(void, draw_ellipse, (int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_ellipse_fill(images[0], centerX, centerY, radiusX, radiusY, colorHost);
})

// Draw a filled circle on the screen.
HOST_FUNCTION(void, draw_circle, (int32_t centerX, int32_t centerY, int32_t radius, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_circle_fill(images[0], centerX, centerY, radius, colorHost);
})

// Draw a filled polygon on the screen.
HOST_FUNCTION(void, draw_polygon, (uint32_t points, int32_t numPoints, uint32_t color), {
 pntr_vector* pointsHost = copy_memory_from_cart(points, numPoints * sizeof(pntr_vector));
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_polygon_fill(images[0], pointsHost, numPoints, colorHost);
 free(pointsHost);
})

// Draw a filled arc on the screen.
HOST_FUNCTION(void, draw_arc, (int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_arc_fill(images[0], centerX, centerY, radius, startAngle, endAngle, segments, colorHost);
})

// Draw a filled round-rectangle on the screen.
HOST_FUNCTION(void, draw_rectangle_rounded, (int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_rectangle_rounded_fill(images[0], x, y, width, height, cornerRadius, colorHost);
})

// Draw an image on the screen.
HOST_FUNCTION(void, draw_image, (uint32_t src, int32_t posX, int32_t posY), {
 pntr_draw_image(images[0], images[src], posX, posY);
})

// Draw a tinted image on the screen.
HOST_FUNCTION(void, draw_image_tint, (uint32_t src, int32_t posX, int32_t posY, uint32_t tint), {
 pntr_color tintHost = copy_color_from_cart(tint);
 pntr_draw_image_tint(images[0], images[src], posX, posY, tintHost);
})

// Draw an image, rotated, on the screen.
HOST_FUNCTION(void, draw_image_rotated, (uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter), {
 pntr_draw_image_rotated(images[0], images[src], posX, posY, degrees, offsetX, offsetY, filter);
})

// Draw an image, flipped, on the screen.
HOST_FUNCTION(void, draw_image_flipped, (uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal), {
 pntr_draw_image_flipped(images[0], images[src], posX, posY, flipHorizontal, flipVertical, flipDiagonal);
})

// Draw an image, scaled, on the screen.
HOST_FUNCTION(void, draw_image_scaled, (uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter), {
 pntr_draw_image_scaled(images[0], images[src], posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
})

// Draw some text on the screen.
HOST_FUNCTION(void, draw_text, (uint32_t font, uint32_t text, int32_t posX, int32_t posY, uint32_t color), {
 char* textHost = copy_string_from_cart(text);
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_text(images[0], fonts[font], textHost, posX, posY, colorHost);
 free(textHost);
})

// Save an image to persistant storage.
HOST_FUNCTION(void, save_image, (uint32_t image, uint32_t filename), {
 char* filenameHost = copy_string_from_cart(filename);
 pntr_save_image(images[image], filenameHost);
 free(filenameHost);
})

// Load an image from a file in cart.
HOST_FUNCTION(uint32_t, load_image, (uint32_t filename), {
 char* filenameHost = copy_string_from_cart(filename);
 uint32_t retHost = add_image(pntr_load_image(filenameHost));
 free(filenameHost);
 return retHost;
})

// Resize an image, return copy.
HOST_FUNCTION(uint32_t, image_resize, (uint32_t image, int32_t newWidth, int32_t newHeight, pntr_filter filter), {
 uint32_t retHost = add_image(pntr_image_resize(images[image], newWidth, newHeight, filter));
 return retHost;
})

// Scale an image, return copy.
HOST_FUNCTION(uint32_t, image_scale, (uint32_t image, float scaleX, float scaleY, pntr_filter filter), {
 uint32_t retHost = add_image(pntr_image_scale(images[image], scaleX, scaleY, filter));
 return retHost;
})

// Replace a color in an image, in-place.
HOST_FUNCTION(void, image_color_replace, (uint32_t image, uint32_t color, uint32_t replace), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_color replaceHost = copy_color_from_cart(replace);
 pntr_image_color_replace(images[image], colorHost, replaceHost);
})

// Tint a color in an image, in-place.
HOST_FUNCTION(void, image_color_tint, (uint32_t image, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_image_color_tint(images[image], colorHost);
})

// Fade a color in an image, in-place.
HOST_FUNCTION(void, image_color_fade, (uint32_t image, float alpha), {
 pntr_image_color_fade(images[image], alpha);
})

// Copy a font to a new font.
HOST_FUNCTION(uint32_t, font_copy, (uint32_t font), {
 uint32_t retHost = add_font(pntr_font_copy(fonts[font]));
 return retHost;
})

// Scale a font, return a new font.
HOST_FUNCTION(uint32_t, font_scale, (uint32_t font, float scaleX, float scaleY, pntr_filter filter), {
 uint32_t retHost = add_font(pntr_font_scale(fonts[font], scaleX, scaleY, filter));
 return retHost;
})

// Load a BMF font from a file in cart.
HOST_FUNCTION(uint32_t, load_font_bmf, (uint32_t filename, uint32_t characters), {
 char* filenameHost = copy_string_from_cart(filename);
 char* charactersHost = copy_string_from_cart(characters);
 uint32_t retHost = add_font(pntr_load_font_bmf(filenameHost, charactersHost));
 free(filenameHost);
 free(charactersHost);
 return retHost;
})

// Load a BMF font from an image.
HOST_FUNCTION(uint32_t, load_font_bmf_from_image, (uint32_t image, uint32_t characters), {
 char* charactersHost = copy_string_from_cart(characters);
 uint32_t retHost = add_font(pntr_load_font_bmf_from_image(images[image], charactersHost));
 free(charactersHost);
 return retHost;
})

// Measure the size of some text.
HOST_FUNCTION(uint32_t, measure_text, (uint32_t font, uint32_t text, int32_t textLength), {
 char* textHost = copy_string_from_cart(text);
 pntr_vector retHostVal = pntr_measure_text_ex(fonts[font], textHost, textLength);
 uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(pntr_vector));
 free(textHost);
 return retHost;
})

// Meaure an image (use 0 for screen).
HOST_FUNCTION(uint32_t, measure_image, (uint32_t image), {
 pntr_vector retHostVal = null0_measure_image(images[image]);
 uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(pntr_vector));
 return retHost;
})

// Load a TTY font from a file in cart.
HOST_FUNCTION(uint32_t, load_font_tty, (uint32_t filename, int32_t glyphWidth, int32_t glyphHeight, uint32_t characters), {
 char* filenameHost = copy_string_from_cart(filename);
 char* charactersHost = copy_string_from_cart(characters);
 uint32_t retHost = add_font(pntr_load_font_tty(filenameHost, glyphWidth, glyphHeight, charactersHost));
 free(filenameHost);
 free(charactersHost);
 return retHost;
})

// Load a TTY font from an image.
HOST_FUNCTION(uint32_t, load_font_tty_from_image, (uint32_t image, int32_t glyphWidth, int32_t glyphHeight, uint32_t characters), {
 char* charactersHost = copy_string_from_cart(characters);
 uint32_t retHost = add_font(pntr_load_font_tty_from_image(images[image], glyphWidth, glyphHeight, charactersHost));
 free(charactersHost);
 return retHost;
})

// Load a TTF font from a file in cart.
HOST_FUNCTION(uint32_t, load_font_ttf, (uint32_t filename, int32_t fontSize), {
 char* filenameHost = copy_string_from_cart(filename);
 uint32_t retHost = add_font(pntr_load_font_ttf(filenameHost, fontSize));
 free(filenameHost);
 return retHost;
})

// Invert the colors in an image, in-place.
HOST_FUNCTION(void, image_color_invert, (uint32_t image), {
 pntr_image_color_invert(images[image]);
})

// Calculate a rectangle representing the available alpha border in an image.
HOST_FUNCTION(uint32_t, image_alpha_border, (uint32_t image, float threshold), {
 pntr_rectangle retHostVal = pntr_image_alpha_border(images[image], threshold);
 uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(pntr_rectangle));
 return retHost;
})

// Crop an image, in-place.
HOST_FUNCTION(void, image_crop, (uint32_t image, int32_t x, int32_t y, int32_t width, int32_t height), {
 pntr_image_crop(images[image], x, y, width, height);
})

// Crop an image based on the alpha border, in-place.
HOST_FUNCTION(void, image_alpha_crop, (uint32_t image, float threshold), {
 pntr_image_alpha_crop(images[image], threshold);
})

// Adjust the brightness of an image, in-place.
HOST_FUNCTION(void, image_color_brightness, (uint32_t image, float factor), {
 pntr_image_color_brightness(images[image], factor);
})

// Flip an image, in-place.
HOST_FUNCTION(void, image_flip, (uint32_t image, bool horizontal, bool vertical), {
 pntr_image_flip(images[image], horizontal, vertical);
})

// Change the contrast of an image, in-place.
HOST_FUNCTION(void, image_color_contrast, (uint32_t image, float contrast), {
 pntr_image_color_contrast(images[image], contrast);
})

// Use an image as an alpha-mask on another image.
HOST_FUNCTION(void, image_alpha_mask, (uint32_t image, uint32_t alphaMask, int32_t posX, int32_t posY), {
 pntr_image_alpha_mask(images[image], images[alphaMask], posX, posY);
})

// Create a new image, rotating another image.
HOST_FUNCTION(uint32_t, image_rotate, (uint32_t image, float degrees, pntr_filter filter), {
 uint32_t retHost = add_image(pntr_image_rotate(images[image], degrees, filter));
 return retHost;
})

// Create a new image of a gradient.
HOST_FUNCTION(uint32_t, image_gradient, (int32_t width, int32_t height, uint32_t topLeft, uint32_t topRight, uint32_t bottomLeft, uint32_t bottomRight), {
 pntr_color topLeftHost = copy_color_from_cart(topLeft);
 pntr_color topRightHost = copy_color_from_cart(topRight);
 pntr_color bottomLeftHost = copy_color_from_cart(bottomLeft);
 pntr_color bottomRightHost = copy_color_from_cart(bottomRight);
 uint32_t retHost = add_image(pntr_gen_image_gradient(width, height, topLeftHost, topRightHost, bottomLeftHost, bottomRightHost));
 return retHost;
})

// Unload an image.
HOST_FUNCTION(void, unload_image, (uint32_t image), {
 pntr_unload_image(images[image]);
})

// Unload a font.
HOST_FUNCTION(void, unload_font, (uint32_t font), {
 pntr_unload_font(fonts[font]);
})

// Clear an image.
HOST_FUNCTION(void, clear_image, (uint32_t destination, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_clear_background(images[destination], colorHost);
})

// Draw a single pixel on an image.
HOST_FUNCTION(void, draw_point_on_image, (uint32_t destination, int32_t x, int32_t y, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_point(images[destination], x, y, colorHost);
})

// Draw a line on an image.
HOST_FUNCTION(void, draw_line_on_image, (uint32_t destination, int32_t startPosX, int32_t startPosY, int32_t endPosX, int32_t endPosY, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_line(images[destination], startPosX, startPosY, endPosX, endPosY, colorHost);
})

// Draw a filled rectangle on an image.
HOST_FUNCTION(void, draw_rectangle_on_image, (uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_rectangle_fill(images[destination], posX, posY, width, height, colorHost);
})

// Draw a filled triangle on an image.
HOST_FUNCTION(void, draw_triangle_on_image, (uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_triangle_fill(images[destination], x1, y1, x2, y2, x3, y3, colorHost);
})

// Draw a filled ellipse on an image.
HOST_FUNCTION(void, draw_ellipse_on_image, (uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_ellipse_fill(images[destination], centerX, centerY, radiusX, radiusY, colorHost);
})

// Draw a circle on an image.
HOST_FUNCTION(void, draw_circle_on_image, (uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_circle_fill(images[destination], centerX, centerY, radius, colorHost);
})

// Draw a filled polygon on an image.
HOST_FUNCTION(void, draw_polygon_on_image, (uint32_t destination, uint32_t points, int32_t numPoints, uint32_t color), {
 pntr_vector* pointsHost = copy_memory_from_cart(points, numPoints * sizeof(pntr_vector));
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_polygon_fill(images[destination], pointsHost, numPoints, colorHost);
 free(pointsHost);
})

// Draw a filled round-rectangle on an image.
HOST_FUNCTION(void, draw_rectangle_rounded_on_image, (uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_rectangle_rounded_fill(images[destination], x, y, width, height, cornerRadius, colorHost);
})

// Draw an image on an image.
HOST_FUNCTION(void, draw_image_on_image, (uint32_t destination, uint32_t src, int32_t posX, int32_t posY), {
 pntr_draw_image(images[destination], images[src], posX, posY);
})

// Draw a tinted image on an image.
HOST_FUNCTION(void, draw_image_tint_on_image, (uint32_t destination, uint32_t src, int32_t posX, int32_t posY, uint32_t tint), {
 pntr_color tintHost = copy_color_from_cart(tint);
 pntr_draw_image_tint(images[destination], images[src], posX, posY, tintHost);
})

// Draw an image, rotated, on an image.
HOST_FUNCTION(void, draw_image_rotated_on_image, (uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float degrees, float offsetX, float offsetY, pntr_filter filter), {
 pntr_draw_image_rotated(images[destination], images[src], posX, posY, degrees, offsetX, offsetY, filter);
})

// Draw an image, flipped, on an image.
HOST_FUNCTION(void, draw_image_flipped_on_image, (uint32_t destination, uint32_t src, int32_t posX, int32_t posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal), {
 pntr_draw_image_flipped(images[destination], images[src], posX, posY, flipHorizontal, flipVertical, flipDiagonal);
})

// Draw an image, scaled, on an image.
HOST_FUNCTION(void, draw_image_scaled_on_image, (uint32_t destination, uint32_t src, int32_t posX, int32_t posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter), {
 pntr_draw_image_scaled(images[destination], images[src], posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
})

// Draw some text on an image.
HOST_FUNCTION(void, draw_text_on_image, (uint32_t destination, uint32_t font, uint32_t text, int32_t posX, int32_t posY, uint32_t color), {
 char* textHost = copy_string_from_cart(text);
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_text(images[destination], fonts[font], textHost, posX, posY, colorHost);
 free(textHost);
})

// Draw a outlined (with thickness) rectangle on the screen.
HOST_FUNCTION(void, draw_rectangle_outline, (int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_rectangle_thick(images[0], posX, posY, width, height, thickness, colorHost);
})

// Draw a outlined (with thickness) triangle on the screen.
HOST_FUNCTION(void, draw_triangle_outline, (int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_triangle_thick(images[0], x1, y1, x2, y2, x3, y3, thickness, colorHost);
})

// Draw a outlined (with thickness) ellipse on the screen.
HOST_FUNCTION(void, draw_ellipse_outline, (int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_ellipse_thick(images[0], centerX, centerY, radiusX, radiusY, thickness, colorHost);
})

// Draw a outlined (with thickness) circle on the screen.
HOST_FUNCTION(void, draw_circle_outline, (int32_t centerX, int32_t centerY, int32_t radius, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_circle_thick(images[0], centerX, centerY, radius, thickness, colorHost);
})

// Draw a outlined (with thickness) polygon on the screen.
HOST_FUNCTION(void, draw_polygon_outline, (uint32_t points, int32_t numPoints, int32_t thickness, uint32_t color), {
 pntr_vector* pointsHost = copy_memory_from_cart(points, numPoints * sizeof(pntr_vector));
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_polygon_thick(images[0], pointsHost, numPoints, thickness, colorHost);
 free(pointsHost);
})

// Draw a outlined (with thickness) arc on the screen.
HOST_FUNCTION(void, draw_arc_outline, (int32_t centerX, int32_t centerY, float radius, float startAngle, float endAngle, int32_t segments, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_arc_thick(images[0], centerX, centerY, radius, startAngle, endAngle, segments, thickness, colorHost);
})

// Draw a outlined (with thickness) round-rectangle on the screen.
HOST_FUNCTION(void, draw_rectangle_rounded_outline, (int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 null0_draw_rectangle_thick_rounded(images[0], x, y, width, height, cornerRadius, thickness, colorHost);
})

// Draw a outlined (with thickness) rectangle on an image.
HOST_FUNCTION(void, draw_rectangle_outline_on_image, (uint32_t destination, int32_t posX, int32_t posY, int32_t width, int32_t height, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_rectangle_thick(images[destination], posX, posY, width, height, thickness, colorHost);
})

// Draw a outlined (with thickness) triangle on an image.
HOST_FUNCTION(void, draw_triangle_outline_on_image, (uint32_t destination, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_triangle_thick(images[destination], x1, y1, x2, y2, x3, y3, thickness, colorHost);
})

// Draw a outlined (with thickness) ellipse on an image.
HOST_FUNCTION(void, draw_ellipse_outline_on_image, (uint32_t destination, int32_t centerX, int32_t centerY, int32_t radiusX, int32_t radiusY, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_ellipse_thick(images[destination], centerX, centerY, radiusX, radiusY, thickness, colorHost);
})

// Draw a outlined (with thickness) circle on an image.
HOST_FUNCTION(void, draw_circle_outline_on_image, (uint32_t destination, int32_t centerX, int32_t centerY, int32_t radius, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_circle_thick(images[destination], centerX, centerY, radius, thickness, colorHost);
})

// Draw a outlined (with thickness) polygon on an image.
HOST_FUNCTION(void, draw_polygon_outline_on_image, (uint32_t destination, uint32_t points, int32_t numPoints, int32_t thickness, uint32_t color), {
 pntr_vector* pointsHost = copy_memory_from_cart(points, numPoints * sizeof(pntr_vector));
 pntr_color colorHost = copy_color_from_cart(color);
 pntr_draw_polygon_thick(images[destination], pointsHost, numPoints, thickness, colorHost);
 free(pointsHost);
})

// Draw a outlined (with thickness) round-rectangle on an image.
HOST_FUNCTION(void, draw_rectangle_rounded_outline_on_image, (uint32_t destination, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, uint32_t color), {
 pntr_color colorHost = copy_color_from_cart(color);
 null0_draw_rectangle_thick_rounded(images[destination], x, y, width, height, cornerRadius, thickness, colorHost);
})


// INPUT

// Has the key been pressed? (tracks unpress/read correctly.)
HOST_FUNCTION(bool, key_pressed, (pntr_app_key key), {
 bool retHost = pntr_app_key_pressed(null0_app, key);
 return retHost;
})

// Is the key currently down?
HOST_FUNCTION(bool, key_down, (pntr_app_key key), {
 bool retHost = pntr_app_key_down(null0_app, key);
 return retHost;
})

// Has the key been released? (tracks press/read correctly.)
HOST_FUNCTION(bool, key_released, (pntr_app_key key), {
 bool retHost = pntr_app_key_released(null0_app, key);
 return retHost;
})

// Is the key currently up?
HOST_FUNCTION(bool, key_up, (pntr_app_key key), {
 bool retHost = pntr_app_key_up(null0_app, key);
 return retHost;
})

// Has the button been pressed? (tracks unpress/read correctly.)
HOST_FUNCTION(bool, gamepad_button_pressed, (int32_t gamepad, pntr_app_gamepad_button button), {
 bool retHost = pntr_app_gamepad_button_pressed(null0_app, gamepad, button);
 return retHost;
})

// Is the button currently down?
HOST_FUNCTION(bool, gamepad_button_down, (int32_t gamepad, pntr_app_gamepad_button button), {
 bool retHost = pntr_app_gamepad_button_down(null0_app, gamepad, button);
 return retHost;
})

// Has the button been released? (tracks press/read correctly.)
HOST_FUNCTION(bool, gamepad_button_released, (int32_t gamepad, pntr_app_gamepad_button button), {
 bool retHost = pntr_app_gamepad_button_released(null0_app, gamepad, button);
 return retHost;
})

// Get current position of mouse.
HOST_FUNCTION(uint32_t, mouse_position, (), {
 pntr_vector retHostVal = null0_mouse_position();
 uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(pntr_vector));
 return retHost;
})

// Has the button been pressed? (tracks unpress/read correctly.)
HOST_FUNCTION(bool, mouse_button_pressed, (pntr_app_mouse_button button), {
 bool retHost = pntr_app_mouse_button_pressed(null0_app, button);
 return retHost;
})

// Is the button currently down?
HOST_FUNCTION(bool, mouse_button_down, (pntr_app_mouse_button button), {
 bool retHost = pntr_app_mouse_button_down(null0_app, button);
 return retHost;
})

// Has the button been released? (tracks press/read correctly.)
HOST_FUNCTION(bool, mouse_button_released, (pntr_app_mouse_button button), {
 bool retHost = pntr_app_mouse_button_released(null0_app, button);
 return retHost;
})

// Is the button currently up?
HOST_FUNCTION(bool, mouse_button_up, (pntr_app_mouse_button button), {
 bool retHost = pntr_app_mouse_button_up(null0_app, button);
 return retHost;
})


// SOUND

// Load a sound from a file in cart.
HOST_FUNCTION(uint32_t, load_sound, (uint32_t filename), {
 char* filenameHost = copy_string_from_cart(filename);
 uint32_t retHost = add_sound(pntr_load_sound(filenameHost));
 free(filenameHost);
 return retHost;
})

// Play a sound.
HOST_FUNCTION(void, play_sound, (uint32_t sound, bool loop), {
 pntr_play_sound(sounds[sound], loop);
})

// Stop a sound.
HOST_FUNCTION(void, stop_sound, (uint32_t sound), {
 pntr_stop_sound(sounds[sound]);
})

// Unload a sound.
HOST_FUNCTION(void, unload_sound, (uint32_t sound), {
 pntr_unload_sound(sounds[sound]);
})

// Speak some text and return a sound. Set things to 0 for defaults.
HOST_FUNCTION(uint32_t, tts_sound, (uint32_t text, bool phonetic, int32_t pitch, int32_t speed, int32_t throat, int32_t mouth, bool sing), {
 char* textHost = copy_string_from_cart(text);
 uint32_t retHost = add_sound(null0_tts_sound(textHost, phonetic, pitch, speed, throat, mouth, sing));
 free(textHost);
 return retHost;
})

// Create Sfx sound.
HOST_FUNCTION(uint32_t, sfx_sound, (uint32_t params), {
 SfxParams* paramsHost = copy_memory_from_cart(params, sizeof(SfxParams));
 uint32_t retHost = add_sound(null0_sfx_sound(paramsHost));
 free(paramsHost);
 return retHost;
})

// Create Sfx parameters.
HOST_FUNCTION(uint32_t, sfx_generate, (SfxPresetType type), {
 SfxParams retHostVal = null0_sfx_generate(type);
 uint32_t retHost = copy_memory_to_cart(&retHostVal, sizeof(SfxParams));
 return retHost;
})


// TYPES


// UTILITIES

// Get system-time (ms) since unix epoch.
HOST_FUNCTION(uint64_t, current_time, (), {
 uint64_t retHost = null0_current_time();
 return retHost;
})

// Get the change in time (seconds) since the last update run.
HOST_FUNCTION(float, delta_time, (), {
 float retHost = pntr_app_delta_time(null0_app);
 return retHost;
})

// Get a random integer between 2 numbers.
HOST_FUNCTION(int32_t, random_int, (int32_t min, int32_t max), {
 int32_t retHost = pntr_app_random(null0_app, min, max);
 return retHost;
})

// Get the random-seed.
HOST_FUNCTION(uint64_t, random_seed_get, (), {
 uint64_t retHost = pntr_app_random_seed(null0_app);
 return retHost;
})

// Set the random-seed.
HOST_FUNCTION(void, random_seed_set, (uint64_t seed), {
 pntr_app_random_set_seed(null0_app, seed);
})
