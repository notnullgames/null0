#pragma once

#include <ctype.h>

#include "./defines.h"

#define sign(x) ((x / abs(x)))
// euclidean modulo
#define mod(a, b) (a % b + b * sign(b)) % b

// modify text, in place, to be the theme-style
void displayText(char* word) {
  int i = 0;
  if (theme.fontStyle == FONT_UPPER || theme.fontStyle == FONT_UPPER_ALT_ZERO) {
    while (word[i]) {
      word[i] = toupper(word[i]);
      if (theme.fontStyle == FONT_UPPER_ALT_ZERO && word[i] == '0') {
        word[i] = '}';
      }
      i++;
    }
  } else if (theme.fontStyle == FONT_LOWER || theme.fontStyle == FONT_LOWER_ALT_ZERO) {
    while (word[i]) {
      word[i] = tolower(word[i]);
      if (theme.fontStyle == FONT_LOWER_ALT_ZERO && word[i] == '0') {
        word[i] = '}';
      }
      i++;
    }
  }
}

// Draw some text on the screen (using printf-style)
// layout uses character coordinates (not pixels) to make it easier
void draw_textf(i32 posX, i32 posY, Color color, const char* format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(null0_traceBuffer, NULL0_TRACE_SIZE, format, args);
  va_end(args);
  displayText(null0_traceBuffer);
  draw_text(
      UI_FONT,
      null0_traceBuffer,
      SCREEN_MARGIN + (posX * charSize.width),
      SCREEN_MARGIN + WAV_HEIGHT + (posY * (charSize.height + LINE_SPACING)),
      color);
}

// draw current cursor-position
void draw_cursor() {
  draw_rectangle(
      SCREEN_MARGIN - 1 + ((menuPosition.x + menuOffset.x) * charSize.width),
      SCREEN_MARGIN - 4 + WAV_HEIGHT + ((menuPosition.y + menuOffset.y) * (charSize.height + LINE_SPACING)),
      (menuPosition.width * charSize.width) + 1,
      (menuPosition.height * charSize.height) + 2,
      theme.cursor);
}