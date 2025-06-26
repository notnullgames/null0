#include "null0.h"

int main() {
  Color colors[26];

  colors[0] = LIGHTGRAY;
  colors[1] = GRAY;
  colors[2] = DARKGRAY;
  colors[3] = YELLOW;
  colors[4] = GOLD;
  colors[5] = ORANGE;
  colors[6] = PINK;
  colors[7] = RED;
  colors[8] = MAROON;
  colors[9] = GREEN;
  colors[10] = LIME;
  colors[11] = DARKGREEN;
  colors[12] = BLANK;
  colors[13] = SKYBLUE;
  colors[14] = DARKBLUE;
  colors[15] = PURPLE;
  colors[16] = VIOLET;
  colors[17] = DARKPURPLE;
  colors[18] = BEIGE;
  colors[19] = BROWN;
  colors[20] = DARKBROWN;
  colors[21] = WHITE;
  colors[22] = BLACK;
  colors[23] = BLUE;
  colors[24] = MAGENTA;
  colors[25] = RAYWHITE;

  int margin = 10;
  float bar_width = (SCREEN_WIDTH / (26.0 * 2)) + (margin / 4);
  float bar_height = SCREEN_HEIGHT - (margin * 2.0);

  // it doesn't change, so just draw it once

  int d = SCREEN_HEIGHT / 4;
  int i = 0;
  while (d) {
    draw_circle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, d -= bar_width, i++ % 2 ? WHITE : RED);
  }

  int x;
  for (x = 0; x < 26; x++) {
    draw_rectangle(margin + (x * (bar_width + margin)), margin, bar_width, bar_height, colors[x]);
    if (x == 0) {
      draw_rectangle_outline(margin + (x * (bar_width + margin)), margin, bar_width, bar_height, 1, WHITE);
    } else {
      draw_rectangle_outline(margin + (x * (bar_width + margin)), margin, bar_width, bar_height, 1, LIGHTGRAY);
    }
  }

  return 0;
}
