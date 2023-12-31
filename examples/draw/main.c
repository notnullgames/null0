// simple native example of drawing

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

void cart_main() {
  null0_trace("Hello from draw.");
}

bool cart_update() {
  null0_clear(NULL0_BLACK);
  null0_draw_ellipse(100, 100, 100, 50, NULL0_WHITE);

  null0_draw_triangle(200, 200, 100, 100, 150, 0, NULL0_GREEN);

  null0_draw_circle(100, 100, 30, NULL0_RED);
  null0_draw_rectangle(150, 150, 30, 30, NULL0_RED);
  null0_draw_rectangle_outline(145, 145, 40, 40, NULL0_RED);

  null0_draw_circle_outline(100, 100, 35, NULL0_BLUE);
  null0_draw_circle_outline(100, 100, 40, NULL0_PURPLE);
  null0_draw_circle_outline(100, 100, 45, NULL0_GREEN);

  null0_draw_point(100, 100, NULL0_WHITE);
  null0_draw_line(0, 0, 320, 240, NULL0_YELLOW);
}

bool Init(pntr_app* app) {
  if (!null0_load_cart(NULL)) {
    printf("Could not initialize\n");
    null0_unload();
    return false;
  }
  cart_main();
  return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
  null0_update(app, screen);
  cart_update();
  return true;
}


pntr_app Main(int argc, char* argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif
  return (pntr_app){
      .width = 320,
      .height = 240,
      .title = "null0",
      .init = Init,
      .update = Update,
      .fps = 60};
}