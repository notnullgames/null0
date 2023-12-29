// this is the entrypoint for the main runtime

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#define PNTR_PIXELFORMAT_RGBA
#define PNTR_ENABLE_MATH
#define PNTR_ENABLE_JPEG
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

bool Init(pntr_app* app) {
  return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
  return true;
}

void Close(pntr_app* app) {}

void Event(pntr_app* app, pntr_app_event* event) {}

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
      .close = Close,
      .event = Event,
      .fps = 60};
}