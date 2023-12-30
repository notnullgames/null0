// simple native example of logging

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

void cart_main() {
  null0_trace("Hello from justlog.");
}

bool Init(pntr_app* app) {
  if (!null0_load_cart("examples/cart/c/filesystem")) {
    printf("Could not load examples/cart/c/filesystem as root-filesystem!\n");
    null0_unload();
    return false;
  }
  
  cart_main();
  
  // exit after init
  null0_unload();
  return false;
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
      .fps = 60};
}