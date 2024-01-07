// this defines the API of the null0 game-engine

#pragma once

#include <dirent.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH_STRING_SIZE 127

// use null0 file-functions (defined in null0_api_filesystem) for pntr
unsigned char* null0_file_read(char* filename, uint32_t* bytesRead);
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize);

#define PNTR_LOAD_FILE null0_file_read
#define PNTR_SAVE_FILE null0_file_write

#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF

// make sure importing pntr will implement it, too
#define PNTR_IMPLEMENTATION
#define PNTR_APP_IMPLEMENTATION
#include <pntr.h>
#include <pntr_app.h>

// growable arrays
#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"

// setup shared globals
cvector_vector_type(pntr_font*) null0_fonts;
cvector_vector_type(pntr_image*) null0_images;
cvector_vector_type(pntr_sound*) null0_sounds;
pntr_app* null0_app;
pntr_image* null0_screen;

// these are to simplify bindings
uint32_t null0_add_image(pntr_image* image) {
  uint32_t id = cvector_size(null0_images);
  cvector_push_back(null0_images, image);
  return id;
}

uint32_t null0_add_sound(pntr_sound* sound) {
  uint32_t id = cvector_size(null0_sounds);
  cvector_push_back(null0_sounds, sound);
  return id;
}

uint32_t null0_add_font(pntr_font* font) {
  uint32_t id = cvector_size(null0_fonts);
  cvector_push_back(null0_fonts, font);
  return id;
}

#include "null0_api_utilities.h"

#include "null0_api_colors.h"
#include "null0_api_filesystem.h"
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

// initialize structures & load a cart (wasm or zip file)
bool null0_load_cart(char* filename) {
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

// call on each frame to update things
void null0_update(pntr_app* app, pntr_image* screen) {
  null0_app = app;
  null0_screen = screen;
}

// call when you are ready to quit, to unload things
void null0_unload() {
  // null0_unload_fonts
  // null0_unload_images
  // null0_unload_sounds
  // null0_unload_filesystem
}
