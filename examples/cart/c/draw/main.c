#include <null0.h>

int main() {
  trace("Hello from draw.");
  return 0;
}

NULL0_EXPORT("update")
void update() {
  clear(BLACK);
  draw_ellipse(100, 100, 100, 50, WHITE);

  draw_triangle(200, 200, 100, 100, 150, 0, GREEN);

  draw_circle(100, 100, 30, RED);
  draw_rectangle(150, 150, 30, 30, RED);
  draw_rectangle_outline(145, 145, 40, 40, RED);

  draw_circle_outline(100, 100, 35, BLUE);
  draw_circle_outline(100, 100, 40, PURPLE);
  draw_circle_outline(100, 100, 45, GREEN);

  draw_point(100, 100, WHITE);
  draw_line(0, 0, 320, 240, YELLOW);
}