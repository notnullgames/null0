#pragma once

#include "null0.h"

// the height of the rectangle that shows current audio output (at top of screen)
#define WAV_HEIGHT 30

// the number of pixels between lines
#define LINE_SPACING 3

// margin around stuff on screen
#define SCREEN_MARGIN 5

typedef enum {
  FONT_UPPER,
  FONT_UPPER_ALT_ZERO,
  FONT_LOWER,
  FONT_LOWER_ALT_ZERO,
} FontStyle;

typedef enum {
  PAGE_SONG,
  PAGE_PATTERN,
  PAGE_PHRASE,
  PAGE_INSTRUMENT,
  PAGE_MOD,
  PAGE_CHAIN,
  PAGE_TABLE,
  PAGE_THEME
} Page;

// TODO: reverse-engineer M8T format, so this can interop easier (load directly from file)
typedef struct {
  u8 backlight;  // not sure what this is, maybe M8-specific? Default on M8 is 0xC0

  FontStyle fontStyle;
  Color background;
  Color text_empty;
  Color text_info;
  Color text_default;
  Color text_value;
  Color text_titles;
  Color play_markers;
  Color cursor;
  Color selection;
  Color slider;
  Color meter_low;
  Color meter_mid;
  Color meter_peak;

  char* name;
} Theme;

// default theme
Theme themeDefault = {
    .backlight = 0xc0,
    .fontStyle = FONT_UPPER,
    .background = (Color){.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF},
    .text_empty = (Color){.r = 0x1e, .g = 0x1e, .b = 0x28, .a = 0xFF},
    .text_info = (Color){.r = 0x60, .g = 0x60, .b = 0x8e, .a = 0xFF},
    .text_default = (Color){.r = 0x8c, .g = 0x8c, .b = 0xba, .a = 0xFF},
    .text_value = (Color){.r = 0xfa, .g = 0xfa, .b = 0xfa, .a = 0xFF},
    .text_titles = (Color){.r = 0x32, .g = 0xec, .b = 0xff, .a = 0xFF},
    .play_markers = (Color){.r = 0x00, .g = 0xff, .b = 0x70, .a = 0xFF},
    .cursor = (Color){.r = 0x32, .g = 0xec, .b = 0xff, .a = 0xFF},
    .selection = (Color){.r = 0xff, .g = 0x00, .b = 0xd2, .a = 0xFF},
    .slider = (Color){.r = 0x32, .g = 0xec, .b = 0xff, .a = 0xFF},
    .meter_low = (Color){.r = 0x00, .g = 0xff, .b = 0x50, .a = 0xFF},
    .meter_mid = (Color){.r = 0xff, .g = 0xe0, .b = 0x00, .a = 0xFF},
    .meter_peak = (Color){.r = 0xff, .g = 0x30, .b = 0x70, .a = 0xFF}};
