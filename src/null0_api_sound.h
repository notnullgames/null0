// Null0 host - sound - generated 2023-12-29T06:49:42.333Z
#pragma once

#include <stdint.h>
#include "sfx_gen.h"

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
} SfxPresetType;

typedef enum SfxWaveType SfxWaveType;
int sfx_random(int range) {
  return null0_random_int(0, range);
}

// Load a sound from a file in cart
uint32_t null0_load_sound(char* filename) {}

// Play a sound
void null0_play_sound(uint32_t sound, bool loop) {}

// Stop a sound
void null0_stop_sound(uint32_t sound) {}

// Seek to a position in a sound
void null0_seek_sound(uint32_t sound, float position) {}

// Create a new sound from some text (text-to-speech)
uint32_t null0_speak(char* text) {}

// Create a new sound-effect from some sfxr params
uint32_t null0_new_sfx(SfxParams* params) {}

// Generate randomized preset sfxr params
void null0_preset_sfx(SfxParams* params, SfxPresetType type) {}

// Randomize sfxr params
void null0_randomize_sfx(SfxParams* params, SfxWaveType waveType) {}

// Randomly mutate sfxr params
void null0_mutate_sfx(SfxParams* params, float range, uint32_t mask) {}

// Create a new sfxr from a .rfx file
SfxParams null0_load_sfx(char* filename) {}

// Unload a sound
void null0_unload_sound(uint32_t sound) {}