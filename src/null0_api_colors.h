// Null0 host - colors - generated 2023-12-29T06:49:42.373Z
#pragma once

#include <pntr.h>
#include <stdint.h>

// Tint a color with another color
uint32_t null0_color_tint(uint32_t color, uint32_t tint) {
  pntr_color c = pntr_color_tint(pntr_get_color(color), pntr_get_color(tint));
  return c.value;
}

// Fade a color
uint32_t null0_color_fade(uint32_t color, float alpha) {}

// Change the brightness of a color
uint32_t null0_color_brightness(uint32_t color, float factor) {}

// Invert a color
uint32_t null0_color_invert(uint32_t color) {}

// Blend 2 colors together
uint32_t null0_color_alpha_blend(uint32_t dst, uint32_t src) {}

// color_contrast
uint32_t null0_color_contrast(uint32_t color, float contrast) {}

// Interpolate colors
uint32_t null0_color_bilinear_interpolate(uint32_t color00, uint32_t color01, uint32_t color10, uint32_t color11, float coordinateX, float coordinateY) {}