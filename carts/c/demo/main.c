#include "null0.h"

// module-level state, persists across update() calls
static int frame = 0;

int main() {
  return 0;
}

void update() {
  frame++;

  clear(DARKGRAY);
  draw_text(FONT_DEFAULT, "null0 demo", 20, 20, WHITE);
  draw_rectangle(40, 80, 100, 70, RED);
  draw_circle(220, 115, 45, GREEN);
  draw_triangle(320, 150, 400, 150, 360, 60, BLUE);
  draw_line(40, 250, 600, 250, LIGHTGRAY);

  // hexagon - the trickiest binding: an array of Vector structs
  Vector hexagon[6] = {
    {460, 80}, {520, 80}, {550, 140}, {520, 200}, {460, 200}, {430, 140}
  };
  draw_polygon(hexagon, 6, PURPLE);

  // sweep a circle left-to-right across the bottom, proving update() runs
  // repeatedly and state persists
  int x = frame % 600;
  draw_circle(x + 20, 350, 20, YELLOW);

  draw_text(FONT_DEFAULT, "shapes + animation + text", 20, 440, ORANGE);
}

// other callbacks (optional - implement as needed)

// void unload() {}
// void buttonUp(GamepadButton button, u32 player) {}
// void buttonDown(GamepadButton button, u32 player) {}
// void keyUp(Key key) {}
// void keyDown(Key key) {}
// void mouseDown(MouseButton button) {}
// void mouseUp(MouseButton button) {}
// void mouseMoved(f32 x, f32 y) {}
