// this defines the API of the null0 game-engine

#pragma once

#include <stdbool.h>
#include <stdint.h>

// use null0 file-functions (defined in null0_api_filesystem) for pntr
unsigned char* null0_file_read(char* filename, uint32_t* bytesRead);
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize);

#define PNTR_LOAD_FILE null0_file_read
#define PNTR_SAVE_FILE null0_file_write

// make sure importing pntr will implement it, too
#define PNTR_IMPLEMENTATION
#define PNTR_APP_IMPLEMENTATION
#include <pntr.h>
#include <pntr_app.h>

// use zip as dir
#define STRPOOL_IMPLEMENTATION
#define ASSETSYS_IMPLEMENTATION
#include "assetsys.h"

// growable arrays
#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"

// setup shared arrays of resources
cvector_vector_type(pntr_font*) null0_fonts;
cvector_vector_type(pntr_image*) null0_images;
cvector_vector_type(pntr_sound*) null0_sounds;

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

// initialize null0 API for a single game (using a zip file oir directory for assets)
bool null0_init(char* filename) {
  return false;
}

// load a cart (wasm or zip file)
bool null0_load_cart(char* filename) {
  bool loaded = null0_init(filename);
  return loaded;
}

// call on each frame to update things
void null0_update() {}

// call when you are ready to quit, to unload things
void null0_unload() {}
