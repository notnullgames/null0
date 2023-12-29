// Null0 host - sound - generated 2023-12-29T06:49:42.333Z
#pragma once

#include <stdint.h>
#include "sfx_gen.h"

typedef enum SfxWaveType SfxWaveType;

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
} SfxPresetType;

typedef struct {
  char riff_header[4];  // Contains "RIFF"
  int32_t wav_size;         // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
  char wave_header[4];  // Contains "WAVE"

  // Format Header
  char fmt_header[4];  // Contains "fmt " (includes trailing space)
  int32_t fmt_chunk_size;  // Should be 16 for PCM
  int16_t audio_format;    // Should be 1 for PCM. 3 for IEEE Float
  int16_t num_channels;
  int32_t sample_rate;
  int32_t byte_rate;         // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
  int16_t sample_alignment;  // num_channels * Bytes Per Sample
  int16_t bit_depth;         // Number of bits per sample

  // Data
  char data_header[4];  // Contains "data"
  int32_t data_bytes;       // Number of bytes in data. Number of samples * num_channels * sample byte size
                        // uint8_t bytes[]; // Remainder of wave file is bytes
} RIFF_header;

RIFF_header wav_header = {
    .riff_header = "RIFF",
    .wave_header = "WAVE",
    .fmt_header = "fmt ",
    .data_header = "data",
    .fmt_chunk_size = 16,
    .audio_format = 1,
    .num_channels = 1,
    .sample_rate = 44100,
    .byte_rate = 44100,
    .sample_alignment = 1,
    .bit_depth = 8,

    .wav_size = 0,
    .data_bytes = 0};

// this sets up sfx_gen (required define)
int sfx_random(int range) {
  return null0_random_int(0, range);
}

// Load a sound from a file in cart
uint32_t null0_load_sound(char* fileName) {
  return null0_add_sound(pntr_load_sound(fileName));
}

// Play a sound
void null0_play_sound(uint32_t sound, bool loop) {
  pntr_play_sound(null0_sounds[sound], loop);
}

// Stop a sound
void null0_stop_sound(uint32_t sound) {
  pntr_stop_sound(null0_sounds[sound]);
}

// Create a new sound-effect from some sfxr params
uint32_t null0_new_sfx(SfxParams* params) {
  SfxSynth* synth = sfx_allocSynth(SFX_U8, 44100, 10);
  int sampleCount = sfx_generateWave(synth, params);

  wav_header.wav_size = sampleCount;
  wav_header.data_bytes = sampleCount;

  char* w = malloc(sampleCount + sizeof(wav_header));
  memcpy(w, &wav_header, sizeof(wav_header));
  memcpy((void*)((int64_t)w + sizeof(wav_header)), synth->samples.u8, sampleCount);

  pntr_sound* s = pntr_load_sound_from_memory(PNTR_APP_SOUND_TYPE_WAV, w, sampleCount + sizeof(wav_header));
  if (synth != NULL) {
    free(synth);
  }
  // free(w);
  return null0_add_sound(s);
}

void null0_preset_sfx(SfxParams* params, SfxPresetType type) {
  switch (type) {
    case SFX_COIN:
      return sfx_genPickupCoin(params);
    case SFX_LASER:
      return sfx_genLaserShoot(params);
    case SFX_EXPLOSION:
      return sfx_genExplosion(params);
    case SFX_POWERUP:
      return sfx_genPowerup(params);
    case SFX_HURT:
      return sfx_genHitHurt(params);
    case SFX_JUMP:
      sfx_genJump(params);
    case SFX_SELECT:
      sfx_genBlipSelect(params);
  }
}

void null0_randomize_sfx(SfxParams* params, SfxWaveType waveType) {
  sfx_genRandomize(params, waveType);
}

void null0_mutate_sfx(SfxParams* params, float range, uint32_t mask) {
  sfx_mutate(params, range, mask);
}

// Create a new sound-effect from a .rfx file
uint32_t null0_load_sfx(char* filename) {
  size_t s = sizeof(SfxParams);
  SfxParams* params = malloc(s);
  uint32_t bytesRead = 0;
  unsigned char* bytes = null0_file_read(filename, &bytesRead);
  if (s != bytesRead) {
    return 0;
  }
  memcpy(params, bytes, s);
  return null0_new_sfx(params);
}

// Unload a sound
void null0_unload_sound(uint32_t sound) {
  return pntr_unload_sound(null0_sounds[sound]);
}