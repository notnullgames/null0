#include "null0.h"

u32 sound;

void buttonDown(GamepadButton button, unsigned int player) {
    play_sound(sound, false);
}

int main() {
    sound = tts_sound("Hello, world!", false, 0, 0, 0, 0, false);
    draw_text(0, "Press a button to say hello!", 200, 220, WHITE);
    return 0;
}
