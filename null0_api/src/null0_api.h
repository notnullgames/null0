// this header implements the null0 API

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// use null0 file-functions (defined in null0_api_filesystem) for pntr
unsigned char* null0_file_read(char* filename, uint32_t* bytesRead);
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize);

#define PNTR_LOAD_FILE null0_file_read
#define PNTR_SAVE_FILE null0_file_write

#define PNTR_PIXELFORMAT_ARGB
#define PNTR_ENABLE_MATH
#define PNTR_ENABLE_JPEG
// #define PNTR_NO_STB_IMAGE_IMPLEMENTATION
// #define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
// #define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION
#define PNTR_IMPLEMENTATION
#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#include <pntr.h>
#include <pntr_app.h>

#include "physfs.h"

#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"

pntr_app* null0_app;

#include "null0_api_colors.h"
#include "null0_api_filesystem.h"
#include "null0_api_utils.h"

#include "null0_api_graphics.h"
#include "null0_api_input.h"
#include "null0_api_sound.h"

// map keys to buttons
int null0_button_map_key(int key) {
  if (key == PNTR_APP_KEY_UP) {
    return PNTR_APP_GAMEPAD_BUTTON_UP;
  }
  if (key == PNTR_APP_KEY_DOWN) {
    return PNTR_APP_GAMEPAD_BUTTON_DOWN;
  }
  if (key == PNTR_APP_KEY_LEFT) {
    return PNTR_APP_GAMEPAD_BUTTON_LEFT;
  }
  if (key == PNTR_APP_KEY_RIGHT) {
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
  }
  if (key == PNTR_APP_KEY_Q) {
    return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
  }
  if (key == PNTR_APP_KEY_W) {
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
  }
  if (key == PNTR_APP_KEY_Z) {
    return PNTR_APP_GAMEPAD_BUTTON_B;
  }
  if (key == PNTR_APP_KEY_X) {
    return PNTR_APP_GAMEPAD_BUTTON_A;
  }
  if (key == PNTR_APP_KEY_A) {
    return PNTR_APP_GAMEPAD_BUTTON_Y;
  }
  if (key == PNTR_APP_KEY_S) {
    return PNTR_APP_GAMEPAD_BUTTON_X;
  }
  if (key == PNTR_APP_KEY_LEFT_SHIFT || key == PNTR_APP_KEY_RIGHT_SHIFT) {
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  }
  if (key == PNTR_APP_KEY_ENTER) {
    return PNTR_APP_GAMEPAD_BUTTON_START;
  }
  return -1;
}

// call this in your own host's init function to setup basic frame of things
bool null0_init(char* filename) {
  if (filename != NULL) {
    if (!null0_init_filesystem(filename)) {
      return false;
    }
  }

  // default font is 0
  null0_add_font(pntr_load_font_default());

  // image 0 is screen
  null0_add_image(null0_screen);

  return true;
}

// call this in your own host's update function to update things
bool null0_update(pntr_app* app, pntr_image* screen) {
  null0_app = app;
  null0_screen = screen;
  return true;
}

// call this in your own host's unload funciton on exit
void null0_unload() {
  null0_unload_filesystem();
  // TODO: unload all resources
}
