#define PNTR_IMPLEMENTATION
#define PNTR_APP_IMPLEMENTATION
#define PNTR_PIXELFORMAT_ARGB

#include "pntr_app.h"

pntr_color colors[27];

bool Init(pntr_app* app) {
  colors[0] = PNTR_LIGHTGRAY;
  colors[1] = PNTR_GRAY;
  colors[2] = PNTR_DARKGRAY;
  colors[3] = PNTR_YELLOW;
  colors[4] = PNTR_GOLD;
  colors[5] = PNTR_ORANGE;
  colors[6] = PNTR_PINK;
  colors[7] = PNTR_RED;
  colors[8] = PNTR_MAROON;
  colors[9] = PNTR_GREEN;
  colors[10] = PNTR_LIME;
  colors[11] = PNTR_DARKGREEN;
  colors[12] = PNTR_SKYBLUE;
  colors[13] = PNTR_BLUE;
  colors[14] = PNTR_DARKBLUE;
  colors[15] = PNTR_PURPLE;
  colors[16] = PNTR_VIOLET;
  colors[17] = PNTR_DARKPURPLE;
  colors[18] = PNTR_BEIGE;
  colors[19] = PNTR_BROWN;
  colors[20] = PNTR_DARKBROWN;
  colors[21] = PNTR_WHITE;
  colors[22] = PNTR_BLACK;
  colors[24] = PNTR_BLANK;
  colors[25] = PNTR_MAGENTA;
  colors[26] = PNTR_RAYWHITE;

  return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
  pntr_clear_background(screen, PNTR_BLACK);

  int x;
  int c = 0;
  for (x = 10; x < (28 * 10); x += 10) {
    pntr_draw_rectangle_fill(screen, x + 13, 5, 8, 5, PNTR_WHITE);
    pntr_draw_rectangle_fill(screen, x + 15, 15, 5, 210, colors[c++]);
    pntr_draw_rectangle_fill(screen, x + 13, 230, 8, 5, PNTR_WHITE);
  }

  return true;
}

void Close(pntr_app* app) {
}

void Event(pntr_app* app, pntr_app_event* event) {
}

pntr_app Main(int argc, char* argv[]) {
  return (pntr_app){
      .width = 320,
      .height = 240,
      .title = "null0",
      .init = Init,
      .update = Update,
      .close = Close,
      .event = Event,
      .fps = 60};
}