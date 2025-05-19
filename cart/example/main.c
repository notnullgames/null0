#include "../null0.h"

u32 logo;
int i = 0;

int main() {
  printf("hello\n");
  logo = image_load("assets/logo.png");
  if (logo == 0) {
    printf("failed to load logo: %u\n", logo);
  } else {
    printf("logo loaded: %u\n", logo);
  }
  return 0;
}

void update() {
  clear(0, BLACK);

  draw_rectangle(0, 10, 10, 620, 460, 0, BLUE);
  draw_rectangle(0, 20, 20, 600, 440, 0, GREEN);
  draw_rectangle(0, 30, 30, 580, 420, 0, YELLOW);
  draw_rectangle(0, 40, 40, 560, 400, 0, RED);
  draw_rectangle(0, 50, 50, 540, 380, 0, ORANGE);

  draw_circle(0, 320, 240, 100, 4, RAYWHITE);
  draw_circle(0, 320, 240, 95, 4, MAROON);
  draw_circle(0, 320, 240, 90, 4, SKYBLUE);
  draw_circle(0, 320, 240, 85, 4, VIOLET);
  draw_circle(0, 320, 240, 80, 0, BLUE);

  draw_image_rotated(0, logo, (640 / 2), (480 / 2), i++, 135.0 / 2, 135.0 / 2, FILTER_NEARESTNEIGHBOR);
}
