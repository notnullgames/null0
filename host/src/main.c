#define PNTR_APP_IMPLEMENTATION
#define PNTR_APP_SFX_IMPLEMENTATION
#define PNTR_TILED_IMPLEMENTATION
#define PNTR_MICROUI_IMPLEMENTATION

#ifdef __ANDROID__
#include "raylib.h"
// pntr_app opens a 2x window, which raylib letterboxes on android - leaving
// nowhere to draw the on-screen controller. use the whole display instead
#define InitWindow(width, height, title) InitWindow(0, 0, title)
// draw the on-screen controller over each frame, just before it's shown
void null0_android_draw_controller();
static inline void null0_android_end_drawing() {
  null0_android_draw_controller();
  EndDrawing();
}
#define EndDrawing null0_android_end_drawing
#endif

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