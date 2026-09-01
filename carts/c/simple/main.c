#include "null0.h"

// every language's `simple` cart draws exactly this, so you can put any two
// of them side by side and see only the language differ

int main() {
  clear(BLUE);
  draw_circle(100, 100, 50, RED);
  draw_text(FONT_DEFAULT, "hello from C", 170, 92, WHITE);
  return 0;
}

// callbacks (optional - implement as needed)

// void update() {}
// void unload() {}
// void buttonUp(GamepadButton button, u32 player) {}
// void buttonDown(GamepadButton button, u32 player) {}
// void keyUp(Key key) {}
// void keyDown(Key key) {}
// void mouseDown(MouseButton button) {}
// void mouseUp(MouseButton button) {}
// void mouseMoved(f32 x, f32 y) {}
