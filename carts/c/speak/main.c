#include "null0.h"

u32 sound;

void buttonDown(GamepadButton button, unsigned int player) {
    play_sound(sound, false);
}

/*
SAM:               72,  64, 128, 128
Elf:               72,  64, 110, 160
Little Robot:      92,  60, 190, 190
Stuffy Guy:        82,  72, 110, 105
Little Old Lady:   82,  32, 145, 145
Extra-Terrestrial: 100, 64, 150, 200
*/


int main() {
    sound = tts_sound("Hello, world!", false, 82,  72, 110, 105, false);
    draw_text(0, "Press a button to say hello!", 200, 220, WHITE);
    return 0;
}
