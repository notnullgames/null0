#include "null0.h"

u32 sound = 0;
u32 sound_from_file = 0;

void buttonUp(GamepadButton button, unsigned int player) {
    if (button == GAMEPAD_BUTTON_START) {
        play_sound(sound_from_file, false);
    } else {
        if (sound > 0) {
            unload_sound(sound);
            sound = 0;
        }

        SfxParams* params = NULL;

        if (button == GAMEPAD_BUTTON_A) {
            params = sfx_generate(SFX_COIN);
        } else if (button == GAMEPAD_BUTTON_B) {
            params = sfx_generate(SFX_LASER);
        } else if (button == GAMEPAD_BUTTON_X) {
            params = sfx_generate(SFX_EXPLOSION);
        } else if (button == GAMEPAD_BUTTON_Y) {
            params = sfx_generate(SFX_POWERUP);
        } else if (button == GAMEPAD_BUTTON_SELECT) {
            params = sfx_generate(SFX_HURT);
        } else if (button == GAMEPAD_BUTTON_LEFT_SHOULDER) {
            params = sfx_generate(SFX_JUMP);
        } else if (button == GAMEPAD_BUTTON_RIGHT_SHOULDER) {
            params = sfx_generate(SFX_SELECT);
        }

        if (params != NULL) {
            sound = sfx_sound(*params);
            play_sound(sound, false);
            free(params);
        }
    }
}

// example function to see params
void print_sfx(SfxParams* params) {
    printf("SfxParams: {\n");
    printf("  randSeed: %u\n", params->randSeed);
    printf("  waveType: %d\n", params->waveType);
    printf("  attackTime: %f\n", params->attackTime);
    printf("  sustainTime: %f\n", params->sustainTime);
    printf("  sustainPunch: %f\n", params->sustainPunch);
    printf("  decayTime: %f\n", params->decayTime);
    printf("  startFrequency: %f\n", params->startFrequency);
    printf("  minFrequency: %f\n", params->minFrequency);
    printf("  slide: %f\n", params->slide);
    printf("  deltaSlide: %f\n", params->deltaSlide);
    printf("  vibratoDepth: %f\n", params->vibratoDepth);
    printf("  vibratoSpeed: %f\n", params->vibratoSpeed);
    printf("  changeAmount: %f\n", params->changeAmount);
    printf("  changeSpeed: %f\n", params->changeSpeed);
    printf("  squareDuty: %f\n", params->squareDuty);
    printf("  dutySweep: %f\n", params->dutySweep);
    printf("  repeatSpeed: %f\n", params->repeatSpeed);
    printf("  phaserOffset: %f\n", params->phaserOffset);
    printf("  phaserSweep: %f\n", params->phaserSweep);
    printf("  lpfCutoff: %f\n", params->lpfCutoff);
    printf("  lpfCutoffSweep: %f\n", params->lpfCutoffSweep);
    printf("  lpfResonance: %f\n", params->lpfResonance);
    printf("  hpfCutoff: %f\n", params->hpfCutoff);
    printf("  hpfCutoffSweep: %f\n", params->hpfCutoffSweep);
    printf("}\n");
}

int main() {
    draw_text(0, "Press a button to play a SFX!", 200, 220, WHITE);

    // here is how to load from a file
    // use https://raylibtech.itch.io/rfxgen
    SfxParams* params = malloc(sizeof(SfxParams));
    FILE *file = fopen("assets/sound.rfx", "r");
    fseek(file, 8, SEEK_SET); // header is "rFX " then version/len (int16)
    fread(params, 1, sizeof(SfxParams), file);
    fclose(file);
    sound_from_file = sfx_sound(*params);

    // I load the first one to increment the sound-number (so I can check against 0)
    sound = sfx_sound(*params);

    printf("loaded %d from sound.rfx: ", sound_from_file);
    print_sfx(params);
    free(params);

    return 0;
}