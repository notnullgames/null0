// simple native example of drawing text

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_PIXELFORMAT_RGBA
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

float  w = 0;

void cart_main() {
  pntr_vector dim = null0_measure_text(0, "Hello from null0");
  w = (320 / 2) - (dim.x / 2);
  null0_trace("Hello from hello. %dx%d", dim.x, dim.y);
}

bool cart_update() {
  null0_clear(NULL0_BLACK);
  null0_draw_text(0, "Hello from null0", w + 1, (240 / 2) + 1, NULL0_BLUE);
  null0_draw_text(0, "Hello from null0", w, 240 / 2, NULL0_RED);
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