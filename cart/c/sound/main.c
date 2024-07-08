#include <null0.h>

u32 audioLogo;
u32 sfx;
u32 apache;
SfxParams* params;

// TODO: sfx seem broke

int main() {
  trace("Hello from sound.");

  apache = load_sound("assets/apache.ogg");
  play_sound(apache, true);

  audioLogo = load_sound("assets/notnullgames.ogg");

  params = malloc(sizeof(SfxParams));
  sfx = new_sfx(params);

  // this segfaults, but all works without it
  // preset_sfx(params, SFX_POWERUP);

  return 0;
}

NULL0_EXPORT("update")
void update() {
  clear(BLACK);
  draw_text(0, "Press A for our name. (ogg file)", 40, HEIGHT / 2 - 40, RAYWHITE);
  draw_text(0, "Press B for powerup sound.", 60, HEIGHT / 2 - 20, RAYWHITE);
  draw_text(0, "Press X for coin sound.", 65, HEIGHT / 2, RAYWHITE);
  draw_text(0, "Press Y for hurt sound.", 65, HEIGHT / 2 + 20, RAYWHITE);
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
  }
  if (button == GAMEPAD_BUTTON_X) {
    unload_sound(sfx);
    preset_sfx(params, SFX_COIN);
    sfx = new_sfx(params);
    play_sound(sfx, false);
  }
  if (button == GAMEPAD_BUTTON_Y) {
    unload_sound(sfx);
    preset_sfx(params, SFX_HURT);
    sfx = new_sfx(params);
    play_sound(sfx, false);
  }
}