// This is the null0 API sound functions

#pragma once

#define PNTR_APP_SFX_IMPLEMENTATION
#include "pntr_app_sfx.h"

cvector_vector_type(pntr_sound*) null0_sounds;

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
  SFX_SYNTH
} SfxPresetType;

void print_sfx(pntr_app* app, SfxParams sfx_params) {
  char code[1024];
  snprintf(code, 1024,
      "(SfxParams) {\n\
  .randSeed=%lu,\n\
  .waveType=%d,\n\
  .attackTime=%ff,\n\
  .sustainTime=%ff,\n\
  .sustainPunch=%ff,\n\
  .decayTime=%ff,\n\
  .startFrequency=%ff,\n\
  .minFrequency=%ff,\n\
  .slide=%ff,\n\
  .deltaSlide=%ff,\n\
  .vibratoDepth=%ff,\n\
  .vibratoSpeed=%ff,\n\
  .changeAmount=%ff,\n\
  .changeSpeed=%ff,\n\
  .squareDuty=%ff,\n\
  .dutySweep=%ff,\n\
  .repeatSpeed=%ff,\n\
  .phaserOffset=%ff,\n\
  .phaserSweep=%ff,\n\
  .lpfCutoff=%ff,\n\
  .lpfCutoffSweep=%ff,\n\
  .lpfResonance=%ff,\n\
  .hpfCutoff=%ff,\n\
  .hpfCutoffSweep=%ff \n\
}\n",
      (unsigned long)sfx_params.randSeed, sfx_params.waveType, sfx_params.attackTime, sfx_params.sustainTime, sfx_params.sustainPunch, sfx_params.decayTime, sfx_params.startFrequency, sfx_params.minFrequency, sfx_params.slide, sfx_params.deltaSlide, sfx_params.vibratoDepth, sfx_params.vibratoSpeed, sfx_params.changeAmount, sfx_params.changeSpeed, sfx_params.squareDuty, sfx_params.dutySweep, sfx_params.repeatSpeed, sfx_params.phaserOffset, sfx_params.phaserSweep, sfx_params.lpfCutoff, sfx_params.lpfCutoffSweep, sfx_params.lpfResonance, sfx_params.hpfCutoff, sfx_params.hpfCutoffSweep);

  // Export it to the clipboard and the logs.
  pntr_app_set_clipboard(app, code, 0);
  printf("%s\n", code);
}

uint32_t null0_add_sound(pntr_sound* sound) {
  uint32_t id = cvector_size(null0_sounds);
  cvector_push_back(null0_sounds, sound);
  return id;
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

// Unload a sound
void null0_unload_sound(uint32_t sound) {
  return pntr_unload_sound(null0_sounds[sound]);
}

// Create a new sound-effect from some sfxr params
uint32_t null0_new_sfx(SfxParams* params) {
  printf("null0_new_sfx\n");
  return null0_add_sound(pntr_app_sfx_sound(null0_app, params));
}

void null0_preset_sfx(SfxParams* params, SfxPresetType type) {
  switch (type) {
    case SFX_COIN:
      pntr_app_sfx_gen_pickup_coin(null0_app, params);
      printf("null0_preset_sfx: coin\n");
      break;
    case SFX_LASER:
      pntr_app_sfx_gen_laser_shoot(null0_app, params);
      printf("null0_preset_sfx: laser\n");
      break;
    case SFX_EXPLOSION:
      pntr_app_sfx_gen_explosion(null0_app, params);
      printf("null0_preset_sfx: explosion\n");
      break;
    case SFX_POWERUP:
      pntr_app_sfx_gen_powerup(null0_app, params);
      printf("null0_preset_sfx: powerup\n");
      break;
    case SFX_HURT:
      pntr_app_sfx_gen_hit_hurt(null0_app, params);
      printf("null0_preset_sfx: hurt\n");
      break;
    case SFX_JUMP:
      pntr_app_sfx_gen_jump(null0_app, params);
      printf("null0_preset_sfx: jump\n");
      break;
    case SFX_SELECT:
      pntr_app_sfx_gen_blip_select(null0_app, params);
      printf("null0_preset_sfx: select\n");
      break;
    case SFX_SYNTH:
      pntr_app_sfx_gen_synth(null0_app, params);
      printf("null0_preset_sfx: synth\n");
      break;
    default:
      printf("null0_preset_sfx: no type!\n");
  }

  print_sfx(null0_app, *params);
  
}

void null0_randomize_sfx(SfxParams* params, enum SfxWaveType waveType) {
  pntr_app_sfx_gen_randomize(null0_app, params, waveType);
}

void null0_mutate_sfx(SfxParams* params, float range, uint32_t mask) {
  pntr_app_sfx_mutate(null0_app, params, range, mask);
}

// Create a new sound-effect from a .rfx file
SfxParams null0_load_sfx(char* filename) {
  SfxParams params = {0};
  pntr_app_sfx_load_params(&params, filename);
  return params;
}
