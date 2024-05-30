// this is the entrypoint for native WAMR host

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
  if (!null0_init(filename)) {
    return false;
  }

#ifndef EMSCRIPTEN
  return null0_init_wamr();
#endif
#ifdef EMSCRIPTEN
  return null0_init_web();
#endif
}

bool Update(pntr_app* app, pntr_image* screen) {
  if (!null0_update(app, screen)) {
    return false;
  }
#ifndef EMSCRIPTEN
  return null0_update_wamr();
#endif
#ifdef EMSCRIPTEN
  return null0_update_web();
#endif
}

void Close(pntr_app* app) {}

void Event(pntr_app* app, pntr_app_event* event) {
#ifndef EMSCRIPTEN
  null0_event_wamr(event);
#endif
#ifdef EMSCRIPTEN
  null0_event_web(event);
#endif
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