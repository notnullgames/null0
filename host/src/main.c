// this is the entrypoint for hosts

#ifndef EMSCRIPTEN
#include "null0_api_wamr.h"
#endif

#ifdef EMSCRIPTEN
#include "null0_api_web.h"
#endif

// global that tracks the cart-name
char* filename = NULL;

bool Init(pntr_app* app) {
  if (!filename) {
    return false;
  }

  // setup main null0 runtime
  if (!null0_engine_init(filename)) {
    return false;
  }
  return null0_init();
}

bool Update(pntr_app* app, pntr_image* screen) {
  return null0_engine_update(app, screen) && null0_update();
}

void Close(pntr_app* app) {
  null0_unload();
  null0_engine_unload();
}

void Event(pntr_app* app, pntr_app_event* event) {
  null0_event(event);
}

pntr_app Main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: null0 <CART>\n");
  } else {
    filename = argv[1];
  }

  printf("Pixel format: %d\n", PNTR_PIXELFORMAT);

#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif

  return (pntr_app){
      .width = 320,
      .height = 240,
      .title = "null0",
      .init = Init,
      .update = Update,
      .close = Close,
      .event = Event,
      .fps = 60};
}