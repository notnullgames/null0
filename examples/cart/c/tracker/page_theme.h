#pragma once

#include "./defines.h"

// this tracks if the A buttton is down
// using gamepad_button_down would be nice
// but it's per-device and was not working
bool buttonActive = false;

// this holds all the color stuff, for easier handling (looping)
Color* colorFields[13] = {
    &theme.background,
    &theme.text_empty,
    &theme.text_info,
    &theme.text_default,
    &theme.text_value,
    &theme.text_titles,
    &theme.play_markers,
    &theme.cursor,
    &theme.selection,
    &theme.slider,
    &theme.meter_low,
    &theme.meter_mid,
    &theme.meter_peak};

char* colorLabels[13] = {
    "background",
    "text:empty",
    "text:info",
    "text:default",
    "text:values",
    "text:titles",
    "play markers",
    "cursor",
    "selection",
    "scope/slider",
    "meter low",
    "meter mid",
    "meter peak"};

// check bounds of menu state & update cursor offsets
void page_theme_menu_bounds() {
  menuPosition.y = mod(menuPosition.y, 17);

  // wrap fontOptions around
  theme.fontStyle = mod(theme.fontStyle, 4);

  // backlight/font
  if (menuPosition.y < 2) {
    menuPosition.x = 0;
    menuOffset.y = 2;
  }

  // colors
  if (menuPosition.y > 1 && menuPosition.y != 15) {
    menuOffset.y = 3;
    menuPosition.x = mod(menuPosition.x, 3);
  }

  // all inputs before theme name are 2-wide
  if (menuPosition.y < 15) {
    menuPosition.width = 2;
  }

  // buttons
  if (menuPosition.y == 16) {
    menuPosition.width = menuPosition.x < 2 ? 4 : 5;
    menuOffset.y = 4;
  }

  // theme name
  if (menuPosition.y == 15) {
    menuPosition.width = 1;
    menuOffset.y = 4;
    menuPosition.x = mod(menuPosition.x, 12);
    menuOffset.x = 13;
  } else {
    menuOffset.x = 13 + (menuPosition.x * (menuPosition.width));
    // reset button needs 2 less offset
    if (menuPosition.y == 16 && menuPosition.x == 2) {
      menuOffset.x -= 2;
    }
  }
}

// draws a single color-input (label, values, and indicator)
void page_theme_color_input(int index) {
  int y = 5 + index;
  bool active = index == (menuPosition.y - 2);
  Color* val = colorFields[index];

  draw_textf(0, y, active ? theme.cursor : theme.text_default, colorLabels[index]);
  draw_textf(13, y, active && menuPosition.x == 0 ? theme.background : theme.text_value, "%02X", val->r);
  draw_textf(16, y, active && menuPosition.x == 1 ? theme.background : theme.text_value, "%02X", val->g);
  draw_textf(19, y, active && menuPosition.x == 2 ? theme.background : theme.text_value, "%02X", val->b);
  draw_rectangle(SCREEN_MARGIN + (charSize.width * 22), 2 + WAV_HEIGHT + (y * (charSize.height + LINE_SPACING)), charSize.width * 2, charSize.height, *val);
}

void init_page_theme() {
  buttonActive = false;
  page_theme_menu_bounds();
}

void buttonDown_page_theme(GamepadButton button) {
  if (!buttonActive) {
    if (button == GAMEPAD_BUTTON_UP) {
      menuPosition.y--;
      page_theme_menu_bounds();
    } else if (button == GAMEPAD_BUTTON_DOWN) {
      menuPosition.y++;
      page_theme_menu_bounds();
    } else if (button == GAMEPAD_BUTTON_LEFT) {
      menuPosition.x--;
      page_theme_menu_bounds();
    } else if (button == GAMEPAD_BUTTON_RIGHT) {
      menuPosition.x++;
      page_theme_menu_bounds();
    }

    // jump to beginning of theme name / buttons whhen they are current row
    if ((button == GAMEPAD_BUTTON_UP || button == GAMEPAD_BUTTON_DOWN) && menuPosition.y > 14) {
      menuPosition.x = 0;
    }
  } else {
    // it's a u8 value you can increment/decrement
    if (menuPosition.y < 15) {
      u8* val = NULL;

      if (menuPosition.y == 0) {
        val = &theme.backlight;
      }

      if (menuPosition.y == 1) {
        if (button == GAMEPAD_BUTTON_UP) {
          theme.fontStyle = FONT_UPPER;
        } else if (button == GAMEPAD_BUTTON_DOWN) {
          theme.fontStyle = FONT_LOWER_ALT_ZERO;
        } else if (button == GAMEPAD_BUTTON_LEFT) {
          theme.fontStyle = mod(theme.fontStyle - 1, 4);
        } else if (button == GAMEPAD_BUTTON_RIGHT) {
          theme.fontStyle = mod(theme.fontStyle + 1, 4);
        }
      }

      // it's a color
      if (menuPosition.y > 1) {
        if (menuPosition.x == 0) {
          val = &colorFields[menuPosition.y - 2]->r;
        }
        if (menuPosition.x == 1) {
          val = &colorFields[menuPosition.y - 2]->g;
        }
        if (menuPosition.x == 2) {
          val = &colorFields[menuPosition.y - 2]->b;
        }
      }

      if (val != NULL) {
        if (button == GAMEPAD_BUTTON_UP) {
          (*val) -= 0x10;
        } else if (button == GAMEPAD_BUTTON_DOWN) {
          (*val) += 0x10;
        } else if (button == GAMEPAD_BUTTON_LEFT) {
          (*val)--;
        } else if (button == GAMEPAD_BUTTON_RIGHT) {
          (*val)++;
        }
      }
    }
  }

  if (button == GAMEPAD_BUTTON_A) {
    buttonActive = true;
    // buttons
    if (menuPosition.y == 16) {
      if (menuPosition.x == 0) {
        trace("load");
      } else if (menuPosition.x == 1) {
        trace("save");
      } else if (menuPosition.x == 2) {
        theme = themeDefault;
      }
    }

    // TODO: text input for theme name
  }
}

void buttonUp_page_theme(GamepadButton button) {
  if (button == GAMEPAD_BUTTON_A) {
    buttonActive = false;
  }
}

void draw_page_theme() {
  // I used this while building to debug offsets
  draw_textf(0, -2, theme.text_value, "pos: %dx%d, size: %dx%d, offset: %dx%d", menuPosition.x, menuPosition.y, menuPosition.width, menuPosition.height, menuOffset.x, menuOffset.y);

  // these are used for rolling layouts
  int y = 0;

  char* fontStyleText = "uppercase";

  if (theme.fontStyle == FONT_UPPER_ALT_ZERO) {
    fontStyleText = "upper alt.zero";
  } else if (theme.fontStyle == FONT_LOWER) {
    fontStyleText = "lowercase";
  } else if (theme.fontStyle == FONT_LOWER_ALT_ZERO) {
    fontStyleText = "lower alt.zero";
  }

  draw_cursor();

  draw_textf(0, y++, theme.text_titles, "theme settings");
  y++;

  draw_textf(13, y, menuPosition.y == 0 ? theme.background : theme.text_value, "%02X", theme.backlight);
  draw_textf(0, y++, menuPosition.y == 0 ? theme.cursor : theme.text_default, "backlight");

  draw_textf(13, y, menuPosition.y == 1 ? theme.background : theme.text_value, "%02X", theme.fontStyle);
  draw_textf(16, y, theme.slider, "%s", fontStyleText);
  draw_textf(0, y++, menuPosition.y == 1 ? theme.cursor : theme.text_default, "font options");

  y++;

  for (y = y; y < 18; y++) {
    page_theme_color_input(y - 5);
  }

  y++;

  draw_textf(13, y, theme.text_empty, "------------");
  draw_textf(0, y++, menuPosition.y == 15 ? theme.cursor : theme.text_default, "theme name");

  draw_textf(13, y, menuPosition.y == 16 && menuPosition.x == 0 ? theme.background : theme.text_value, "load");
  draw_textf(18, y, menuPosition.y == 16 && menuPosition.x == 1 ? theme.background : theme.text_value, "save");
  draw_textf(23, y, menuPosition.y == 16 && menuPosition.x == 2 ? theme.background : theme.text_value, "reset");
}