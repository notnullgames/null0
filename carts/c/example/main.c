#include "null0.h"

u32 logo;
Dimensions *logodim;
int i = 0;

int main() {
  printf("hello\n");
  logo = load_image("assets/logo.png");

  if (logo == 0) {
    printf("failed to load logo: %u\n", logo);
  } else {
    logodim = measure_image(logo);
    printf("logo loaded: %u %ux%u\n", logo, logodim->width, logodim->height);
  }
  return 0;
}

void update() {
  clear(BLACK);

  draw_rectangle(10, 10, 620, 460, BLUE);
  draw_rectangle(20, 20, 600, 440, GREEN);
  draw_rectangle(30, 30, 580, 420, YELLOW);
  draw_rectangle(40, 40, 560, 400, RED);
  draw_rectangle(50, 50, 540, 380, ORANGE);

  draw_circle_outline(320, 240, 100, 4, RAYWHITE);
  draw_circle_outline(320, 240, 95, 4, MAROON);
  draw_circle_outline(320, 240, 90, 4, SKYBLUE);
  draw_circle_outline(320, 240, 85, 4, VIOLET);
  draw_circle_outline(320, 240, 80, 0, BLUE);

  draw_image_rotated(logo, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), i++, (float)logodim->width / 2, (float)logodim->height / 2, FILTER_NEARESTNEIGHBOR);
}
