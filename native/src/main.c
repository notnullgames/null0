// this is the entrypoint for native WAMR host

#include "null0_api_wamr.h"

// global that tracks the cart-name
char* filename = NULL;

bool Init(pntr_app* app) {
  if (!filename) {
    return false;
  }

  // setup main null0 runtime
  if (!null0_init(filename)) {
    return false;
  }

  // setup WAMR specific host using /main.wasm
  return null0_init_wamr();
}

bool Update(pntr_app* app, pntr_image* screen) {
  if (!null0_update(app, screen)) {
    return false;
  }
  return null0_update_wamr();
}

void Close(pntr_app* app) {}

void Event(pntr_app* app, pntr_app_event* event) {
  null0_event_wamr(event);
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