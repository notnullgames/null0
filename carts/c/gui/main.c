#include "null0.h"

// reused for positioning
Rectangle pos = {.x = 20, .y = 20, .width = 220, .height = 160};

bool checked = false;
float volume = 0.5f;

int main() {
  return 0;
}

void update() {
  if (gui_begin_window("Hello", pos)) {
    gui_layout_row((i32[]){-1}, 1, 0);
    if (gui_button("Click me")) {
      printf("Clicked!\n");
      fflush(stdout);
    }
    checked = gui_checkbox("Check me", checked);
    gui_label("Volume:");
    volume = gui_slider(volume, 0.0f, 1.0f);
    gui_end_window();
  }
  gui_end();

  clear(DARKGRAY);
  gui_draw(SCREEN);
}
