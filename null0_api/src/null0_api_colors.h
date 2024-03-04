// This is the null0 API color functions/defines

#pragma once

// Tint a color with another color
pntr_color null0_color_tint(pntr_color color, pntr_color tint) {
  return pntr_color_tint(color, tint);
}

// Fade a color
pntr_color null0_color_fade(pntr_color color, float alpha) {
  return pntr_color_fade(color, alpha);
}

// Change the brightness of a color
pntr_color null0_color_brightness(pntr_color color, float factor) {
  return pntr_color_brightness(color, factor);
}

// Invert a color
pntr_color null0_color_invert(pntr_color color) {
  return pntr_color_invert(color);
}

// Blend 2 colors together
pntr_color null0_color_alpha_blend(pntr_color dst, pntr_color src) {
  return pntr_color_alpha_blend(dst, src);
}

// color_contrast
pntr_color null0_color_contrast(pntr_color color, float contrast) {
  return pntr_color_contrast(color, contrast);
}

// Interpolate colors
pntr_color null0_color_bilinear_interpolate(pntr_color color00, pntr_color color01, pntr_color color10, pntr_color color11, float coordinateX, float coordinateY) {
  return pntr_color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY);
}
