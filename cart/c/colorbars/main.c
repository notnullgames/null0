#include <null0.h>

Color colors[26];

int main() {
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
  colors[12] = SKYBLUE;
  colors[13] = BLUE;
  colors[14] = DARKBLUE;
  colors[15] = PURPLE;
  colors[16] = VIOLET;
  colors[17] = DARKPURPLE;
  colors[18] = BEIGE;
  colors[19] = BROWN;
  colors[20] = DARKBROWN;
  colors[21] = WHITE;
  colors[22] = BLACK;
  colors[23] = BLANK;
  colors[24] = MAGENTA;
  colors[25] = RAYWHITE;

  Color c = color_tint(RED, GREEN);
  trace("Null0 Tint RED with GREEN: (%u, %u, %u, %u)\n", c.r, c.g, c.b, c.a);

  return 0;
}

NULL0_EXPORT("update")
void update() {
  clear(BLACK);

  int x;
  int c = 0;
  for (x = 10; x < (28 * 10); x += 10) {
    draw_rectangle(x + 13, 5, 8, 5, WHITE);
    draw_rectangle(x + 15, 15, 5, 210, colors[c++]);
    draw_rectangle(x + 13, 230, 8, 5, WHITE);
  }
}
