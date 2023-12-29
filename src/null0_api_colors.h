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
uint32_t null0_color_fade(uint32_t color, float alpha) {
  pntr_color c = pntr_color_fade(pntr_get_color(color), alpha);
  return c.value;
}

// Change the brightness of a color
uint32_t null0_color_brightness(uint32_t color, float factor) {
  pntr_color c = pntr_color_brightness(pntr_get_color(color), factor);
  return c.value;
}

// Invert a color
uint32_t null0_color_invert(uint32_t color) {
  pntr_color c = pntr_color_invert(pntr_get_color(color));
  return c.value;
}

// Blend 2 colors together
uint32_t null0_color_alpha_blend(uint32_t dst, uint32_t src) {
  pntr_color c = pntr_color_alpha_blend(pntr_get_color(dst), pntr_get_color(src));
  return c.value;
}

// color_contrast
uint32_t null0_color_contrast(uint32_t color, float contrast) {
  pntr_color c = pntr_color_contrast(pntr_get_color(color), contrast);
  return c.value;
}

// Interpolate colors
uint32_t null0_color_bilinear_interpolate(uint32_t color00, uint32_t color01, uint32_t color10, uint32_t color11, float coordinateX, float coordinateY) {
  pntr_color c = pntr_color_bilinear_interpolate(pntr_get_color(color00), pntr_get_color(color01), pntr_get_color(color10), pntr_get_color(color11), coordinateX, coordinateY);
  return c.value;
}