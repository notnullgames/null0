// this is the entrypoint for native WAMR host

#include "null0_native.h"

// global that tracks the cart-name
char* filename = NULL;

bool Init(pntr_app* app) {
  if (!filename) {
    return false;
  }
  return null0_native_init(filename);
}

bool Update(pntr_app* app, pntr_image* screen) {
  return null0_native_update(app, screen);
}

void Close(pntr_app* app) {
  null0_native_unload();
}

void Event(pntr_app* app, pntr_app_event* event) {
  null0_native_event(event);
}

pntr_app Main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: null0 <CART>\n");
  } else {
    filename = argv[1];
  }

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