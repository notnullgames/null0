// This is the null0 API input functions

#pragma once

// Has the key been pressed? (tracks unpress/read correctly)
bool null0_key_pressed(pntr_app_key key) {
  return pntr_app_key_pressed(null0_app, key);
}

// Is the key currently down?
bool null0_key_down(pntr_app_key key) {
  return pntr_app_key_down(null0_app, key);
}

// Has the key been released? (tracks press/read correctly)
bool null0_key_released(pntr_app_key key) {
  return pntr_app_key_released(null0_app, key);
}

// Is the key currently up?
bool null0_key_up(pntr_app_key key) {
  return pntr_app_key_up(null0_app, key);
}

// Has the button been pressed? (tracks unpress/read correctly)
bool null0_gamepad_button_pressed(int32_t gamepad, pntr_app_gamepad_button button) {
  return pntr_app_gamepad_button_pressed(null0_app, gamepad, button);
}

// Is the button currently down?
bool null0_gamepad_button_down(int32_t gamepad, pntr_app_gamepad_button button) {
  return pntr_app_gamepad_button_down(null0_app, gamepad, button);
}

// Has the button been released? (tracks press/read correctly)
bool null0_gamepad_button_released(int32_t gamepad, pntr_app_gamepad_button button) {
  return pntr_app_gamepad_button_released(null0_app, gamepad, button);
}

// Get current position of mouse
pntr_vector null0_mouse_position() {
  pntr_vector r = {
      .x = pntr_app_mouse_x(null0_app),
      .y = pntr_app_mouse_y(null0_app)};
  return r;
}

// Has the button been pressed? (tracks unpress/read correctly)
bool null0_mouse_button_pressed(pntr_app_mouse_button button) {
  return pntr_app_mouse_button_pressed(null0_app, button);
}

// Is the button currently down?
bool null0_mouse_button_down(pntr_app_mouse_button button) {
  return pntr_app_mouse_button_down(null0_app, button);
}

// Has the button been released? (tracks press/read correctly)
bool null0_mouse_button_released(pntr_app_mouse_button button) {
  return pntr_app_mouse_button_released(null0_app, button);
}

// Is the button currently up?
bool null0_mouse_button_up(pntr_app_mouse_button button) {
  return pntr_app_mouse_button_up(null0_app, button);
}