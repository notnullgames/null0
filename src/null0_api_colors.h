// Null0 host - colors - generated 2023-12-29T06:49:42.373Z
#pragma once

#include <pntr.h>
#include <stdint.h>

// Tint a color with another color
uint32_t null0_color_tint(uint32_t color, uint32_t tint) {
  pntr_color c = pntr_color_tint((pntr_color)color, pntr_get_color(tint));
  return c.value;
}

// Fade a color
uint32_t null0_color_fade(uint32_t color, float alpha) {
  pntr_color c = pntr_color_fade((pntr_color)color, alpha);
  return c.value;
}

// Change the brightness of a color
uint32_t null0_color_brightness(uint32_t color, float factor) {
  pntr_color c = pntr_color_brightness((pntr_color)color, factor);
  return c.value;
}

// Invert a color
uint32_t null0_color_invert(uint32_t color) {
  pntr_color c = pntr_color_invert((pntr_color)color);
  return c.value;
}

// Blend 2 colors together
uint32_t null0_color_alpha_blend(uint32_t dst, uint32_t src) {
  pntr_color c = pntr_color_alpha_blend((pntr_color)dst, (pntr_color)src);
  return c.value;
}

// color_contrast
uint32_t null0_color_contrast(uint32_t color, float contrast) {
  pntr_color c = pntr_color_contrast(pntr_get_color(color), contrast);
  return c.value;
}

// Interpolate colors
uint32_t null0_color_bilinear_interpolate(uint32_t color00, uint32_t color01, uint32_t color10, uint32_t color11, float coordinateX, float coordinateY) {
  pntr_color c = pntr_color_bilinear_interpolate((pntr_color)color00, (pntr_color)color01, (pntr_color)color10, (pntr_color)color11, coordinateX, coordinateY);
  return c.value;
}

// these are for standalone native use, since null0 uses plain uint32s
#define NULL0_LIGHTGRAY PNTR_LIGHTGRAY.value
#define NULL0_GRAY PNTR_GRAY.value
#define NULL0_DARKGRAY PNTR_DARKGRAY.value
#define NULL0_YELLOW PNTR_YELLOW.value
#define NULL0_GOLD PNTR_GOLD.value
#define NULL0_ORANGE PNTR_ORANGE.value
#define NULL0_PINK PNTR_PINK.value
#define NULL0_RED PNTR_RED.value
#define NULL0_MAROON PNTR_MAROON.value
#define NULL0_GREEN PNTR_GREEN.value
#define NULL0_LIME PNTR_LIME.value
#define NULL0_DARKGREEN PNTR_DARKGREEN.value
#define NULL0_SKYBLUE PNTR_SKYBLUE.value
#define NULL0_BLUE PNTR_BLUE.value
#define NULL0_DARKBLUE PNTR_DARKBLUE.value
#define NULL0_PURPLE PNTR_PURPLE.value
#define NULL0_VIOLET PNTR_VIOLET.value
#define NULL0_DARKPURPLE PNTR_DARKPURPLE.value
#define NULL0_BEIGE PNTR_BEIGE.value
#define NULL0_BROWN PNTR_BROWN.value
#define NULL0_DARKBROWN PNTR_DARKBROWN.value
#define NULL0_WHITE PNTR_WHITE.value
#define NULL0_BLACK PNTR_BLACK.value
#define NULL0_BLANK PNTR_BLANK.value
#define NULL0_MAGENTA PNTR_MAGENTA.value
#define NULL0_RAYWHITE PNTR_RAYWHITE.value
