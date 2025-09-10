#include "null0.h"

u32 sound = 0;

void buttonUp(GamepadButton button, unsigned int player) {
    SfxParams* params = sfx_generate(SFX_LASER);
    if (sound != 0) {
        unload_sound(sound);
    }
    sound = sfx_sound(*params);
    play_sound(sound, false);
    free(params);
}

int main() {
    draw_text(0, "Press a button to play a SFX!", 200, 220, WHITE);
    return 0;
}