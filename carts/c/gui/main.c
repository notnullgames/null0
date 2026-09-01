#include "null0.h"

// Several of each on purpose: a window with one checkbox and one slider looks
// fine even when microui's widget identity is broken, because there is nothing
// for it to be confused with. See "Rule 4" in AGENTS.md.

Rectangle pos = {.x = 20, .y = 20, .width = 260, .height = 220};

bool sound = true;
bool music = false;
bool fullscreen = false;
float volume = 0.5f;
float brightness = 0.8f;

int main() {
  return 0;
}

void update() {
  if (gui_begin_window("Settings", pos)) {
    gui_layout_row((i32[]){-1}, 1, 0);

    if (gui_button("Click me")) {
      printf("Clicked!\n");
      fflush(stdout);
    }

    sound = gui_checkbox("Sound", sound);
    music = gui_checkbox("Music", music);
    fullscreen = gui_checkbox("Fullscreen", fullscreen);

    gui_label("Volume:");
    volume = gui_slider(volume, 0.0f, 1.0f);
    gui_label("Brightness:");
    brightness = gui_slider(brightness, 0.0f, 1.0f);

    gui_end_window();
  }
  gui_end();

  clear(DARKGRAY);
  gui_draw(SCREEN);
}
