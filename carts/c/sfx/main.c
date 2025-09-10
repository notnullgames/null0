#include "null0.h"

u32 sound;

void buttonDown(GamepadButton button, unsigned int player) {
    play_sound(sound, false);
}

int main() {
    SfxParams *p = sfx_generate(SFX_COIN);
    sound = sfx_sound(*p);
    free(p);
    draw_text(0, "Press a button to play a SFX!", 200, 220, WHITE);
    return 0;
}