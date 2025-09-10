#define PNTR_APP_IMPLEMENTATION
#define PNTR_APP_SFX_IMPLEMENTATION

#include "host.h"

bool Init(pntr_app *app) {
  return host_init(app);
}

bool Update(pntr_app *app, pntr_image *screen) {
  return host_update(app);
}

void Event(pntr_app *app, pntr_app_event *event) {
  host_event(event);
}

void Close(pntr_app *app) {
  host_close();
}

pntr_app Main(int argc, char *argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif
  return (pntr_app){
    .width = 640,
    .height = 480,
    .title = "null0",
    .init = Init,
    .update = Update,
    .event = Event,
    .close = Close,
    .fps = 60};
}