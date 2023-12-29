// Null0 host - input - generated 2023-12-29T06:49:42.337Z
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <pntr_app.h>

// Has the key been pressed? (tracks unpress/read correctly)
bool null0_key_pressed(pntr_app_key key) {}

// Is the key currently down?
bool null0_key_down(pntr_app_key key) {}

// Has the key been released? (tracks press/read correctly)
bool null0_key_released(pntr_app_key key) {}

// Is the key currently up?
bool null0_key_up(pntr_app_key key) {}

// Has the button been pressed? (tracks unpress/read correctly)
bool null0_gamepad_button_pressed(int32_t gamepad, pntr_app_gamepad_button button) {}

// Is the button currently down?
bool null0_gamepad_button_down(int32_t gamepad, pntr_app_gamepad_button button) {}

// Has the button been released? (tracks press/read correctly)
bool null0_gamepad_button_released(int32_t gamepad, pntr_app_gamepad_button button) {}

// Is the button currently up?
bool null0_gamepad_button_up(int32_t gamepad, pntr_app_gamepad_button button) {}

// Get current position of mouse
pntr_vector null0_mouse_position() {}

// Has the button been pressed? (tracks unpress/read correctly)
bool null0_mouse_button_pressed(pntr_app_mouse_button button) {}

// Is the button currently down?
bool null0_mouse_button_down(pntr_app_mouse_button button) {}

// Has the button been released? (tracks press/read correctly)
bool null0_mouse_button_released(pntr_app_mouse_button button) {}

// Is the button currently up?
bool null0_mouse_button_up(pntr_app_mouse_button button) {}