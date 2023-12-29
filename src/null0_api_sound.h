// Null0 host - sound - generated 2023-12-29T02:43:33.858Z
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "sfx_gen.h"
#include "null0_api_filesystem.h"

// Load a sound from a file in cart
uint32_t null0_load_sound(char* filename) {
  return 0;
}

// Play a sound
void null0_play_sound(uint32_t sound, bool loop) {}

// Stop a sound
void null0_stop_sound(uint32_t sound) {}

// Seek to a position in a sound
void null0_seek_sound(uint32_t sound, float position) {}

// Create a new sound from some text (text-to-speech)
uint32_t null0_speak(char* text) {
   return 0;
}

// Create a new sound-effect from some sfxr params
uint32_t null0_new_sfx(SfxParams* params) {
   return 0;
}

// Generate randomized preset sfxr params
void null0_preset_sfx(SfxParams* params, SfxPresetType type) {}

// Randomize sfxr params
void null0_randomize_sfx(SfxParams* params, SfxWaveType waveType) {}

// Randomly mutate sfxr params
void null0_mutate_sfx(SfxParams* params, float range, uint32_t mask) {}

// Create a new sfxr from a .rfx file
SfxParams null0_load_sfx(char* filename) {
  uint32_t bytesRead = 0;
  unsigned char* bytes = null0_file_read(filename, &bytesRead);
  if (bytesRead != 0) {
    SfxParams* ret = malloc(sizeof(SfxParams));
    memcpy(ret, bytes, bytesRead);
    return *ret;
  }
  return NULL;
}

// Unload a sound
void null0_unload_sound(uint32_t sound) {}