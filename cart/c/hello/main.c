#include "null0.h"
#include "stdio.h"

f32 w = 0;

int main() {
  // width for centered text
  Dimensions dim = measure_text(0, "Hello from null0");
  w = (WIDTH / 2) - (dim.width / 2);
  trace("Hello from hello. %dx%d", dim.width, dim.height);
  return 0;
}

NULL0_EXPORT("update")
void update() {
  clear(BLACK);
  draw_text(0, "Hello from null0", w + 1, (HEIGHT / 2) + 1, BLUE);
  draw_text(0, "Hello from null0", w, HEIGHT / 2, RED);
}
