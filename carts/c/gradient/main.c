#include "null0.h"

u32 bg;

int main() {
  // no update needed, since this does not change
  bg = image_gradient(SCREEN_WIDTH, SCREEN_HEIGHT, BLUE, BLUE, GREEN, GREEN);
  draw_image(bg, 0, 0);
}
