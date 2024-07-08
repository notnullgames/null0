#include "null0.h"

#include "./defines.h"

// global vars
Theme theme;

// this will be filled with the size of 1 character
Dimensions charSize;

// the current page the user is on
Page currentPage;

// this is character-space sizing for the cursor
Rectangle menuPosition = (Rectangle){.x = 0, .y = 0, .width = 1, .height = 1};

// use this to offset to wherever the cursor is on screen (in characters)
Vector menuOffset = (Vector){.x = 0, .y = 0};

u32 UI_FONT = 0;

#include "./utils.h"

void switchPage(Page newPage);

#include "./page_theme.h"

void switchPage(Page newPage) {
  if (newPage == PAGE_THEME) {
    init_page_theme();
  }

  currentPage = newPage;
}

int main() {
  UI_FONT = load_font_ttf("assets/m8stealth57.ttf", 7);
  // measure_text was not working, so I hardcode the size
  // charSize = measure_text(UI_FONT, "0");
  charSize.width = 6;
  charSize.height = 7;

  // TODO: load current theme
  theme = themeDefault;

  switchPage(PAGE_THEME);

  return 0;
}

NULL0_EXPORT("buttonDown")
void buttonDown(GamepadButton button) {
  if (currentPage == PAGE_THEME) {
    buttonDown_page_theme(button);
  }
}

NULL0_EXPORT("buttonUp")
void buttonUp(GamepadButton button) {
  if (currentPage == PAGE_THEME) {
    buttonUp_page_theme(button);
  }
}

NULL0_EXPORT("update")
void update() {
  clear(theme.background);
  if (currentPage == PAGE_THEME) {
    draw_page_theme();
  }
}