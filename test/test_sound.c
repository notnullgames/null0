#define PNTR_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_APP_IMPLEMENTATION

#include "pntr_app.h"

pntr_font* font;
pntr_sound* sound;

bool Init(pntr_app* app) {
  font = pntr_load_font_default();
  sound = pntr_load_sound("cart/c/sound/assets/apache.ogg");
  pntr_play_sound(sound, true);
  return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
  pntr_clear_background(screen, PNTR_BLACK);
  pntr_draw_text(screen, font, "You should hear sound.", 80, 110, PNTR_WHITE);
  return true;
}

void Close(pntr_app* app) {
}

void Event(pntr_app* app, pntr_app_event* event) {
}

pntr_app Main(int argc, char* argv[]) {
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