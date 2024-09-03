#include <null0.h>

u32 audioLogo;
u32 sfx;
u32 apache;
SfxParams* params;

u32 preloaded_sfx;
u32 fileloaded_sfx;

// debug function to print a SfxParams
void print_sfx(SfxParams sfx_params) {
  trace("(SfxParams) {\n\
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
}",
      (unsigned long)sfx_params.randSeed, sfx_params.waveType, sfx_params.attackTime, sfx_params.sustainTime, sfx_params.sustainPunch, sfx_params.decayTime, sfx_params.startFrequency, sfx_params.minFrequency, sfx_params.slide, sfx_params.deltaSlide, sfx_params.vibratoDepth, sfx_params.vibratoSpeed, sfx_params.changeAmount, sfx_params.changeSpeed, sfx_params.squareDuty, sfx_params.dutySweep, sfx_params.repeatSpeed, sfx_params.phaserOffset, sfx_params.phaserSweep, sfx_params.lpfCutoff, sfx_params.lpfCutoffSweep, sfx_params.lpfResonance, sfx_params.hpfCutoff, sfx_params.hpfCutoffSweep);
}

int main() {
  trace("Hello from sound.");

  apache = load_sound("assets/apache.ogg");
  // play_sound(apache, true);

  audioLogo = load_sound("assets/notnullgames.ogg");

  params = malloc(sizeof(SfxParams));
  sfx = new_sfx(params);
  preset_sfx(params, SFX_POWERUP);

  // example of a preloaded sound
  SfxParams preloaded = (SfxParams) {
    .randSeed=0,
    .waveType=1,
    .attackTime=0.000000f,
    .sustainTime=0.357139f,
    .sustainPunch=0.000000f,
    .decayTime=0.425881f,
    .startFrequency=0.331024f,
    .minFrequency=0.000000f,
    .slide=0.159528f,
    .deltaSlide=0.000000f,
    .vibratoDepth=0.000000f,
    .vibratoSpeed=0.000000f,
    .changeAmount=0.000000f,
    .changeSpeed=0.000000f,
    .squareDuty=1.000000f,
    .dutySweep=0.000000f,
    .repeatSpeed=0.000000f,
    .phaserOffset=0.000000f,
    .phaserSweep=0.000000f,
    .lpfCutoff=1.000000f,
    .lpfCutoffSweep=0.000000f,
    .lpfResonance=0.000000f,
    .hpfCutoff=0.000000f,
    .hpfCutoffSweep=0.000000f 
  };
  preloaded_sfx = new_sfx(&preloaded);

  // load a SFX from a file
  // currently this is broke
  // SfxParams* fileloaded = malloc(96);
  // load_sfx(fileloaded, "assets/sound.rfx");
  // fileloaded_sfx = new_sfx(fileloaded);
  // print_sfx(*fileloaded);

  return 0;
}

NULL0_EXPORT("update")
void update() {
  clear(BLACK);
  draw_text(0, "Press A for our name. (ogg file)", 40, HEIGHT / 2 - 60, RAYWHITE);
  draw_text(0, "Press B for powerup sound.", 60, HEIGHT / 2 - 40, RAYWHITE);
  draw_text(0, "Press X for coin sound.", 65, HEIGHT / 2 - 20, RAYWHITE);
  draw_text(0, "Press Y for hurt sound.", 65, HEIGHT / 2, RAYWHITE);
  draw_text(0, "Press START for hardcoded sfx struct", 18, HEIGHT / 2 + 20, RAYWHITE);
  // draw_text(0, "Press SELECT for file sfx", 45, HEIGHT / 2 + 40, RAYWHITE);
}

NULL0_EXPORT("buttonDown")
void buttonDown(GamepadButton button) {
  if (button == GAMEPAD_BUTTON_A) {
    play_sound(audioLogo, false);
  }

  if (button == GAMEPAD_BUTTON_B) {
    unload_sound(sfx);
    preset_sfx(params, SFX_POWERUP);
    sfx = new_sfx(params);
    play_sound(sfx, false);
    // print_sfx(*params);
  }
  if (button == GAMEPAD_BUTTON_X) {
    unload_sound(sfx);
    preset_sfx(params, SFX_COIN);
    sfx = new_sfx(params);
    play_sound(sfx, false);
    // print_sfx(*params);
  }
  if (button == GAMEPAD_BUTTON_Y) {
    unload_sound(sfx);
    preset_sfx(params, SFX_HURT);
    sfx = new_sfx(params);
    play_sound(sfx, false);
    // print_sfx(*params);
  }

  if (button == GAMEPAD_BUTTON_START) {
    play_sound(preloaded_sfx, false);
  }

  // if (button == GAMEPAD_BUTTON_SELECT) {
  //   play_sound(fileloaded_sfx, false);
  // }
}