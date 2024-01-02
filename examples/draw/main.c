// simple native example of drawing

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_PIXELFORMAT_RGBA
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

void cart_main() {
  null0_trace("Hello from draw.");
}

bool cart_update() {
  null0_clear(NULL0_GREEN);
  return true;
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