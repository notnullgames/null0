// TODO: this could be simplified with new input stuff
// TODO: use drawing instead of images

#include "null0.h"

bool buttons[] = {
  false,
  false, // GAMEPAD_BUTTON_UP,              // Gamepad left DPAD up button
  false, // GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
  false, // GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
  false, // GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
  false, // GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  false, // GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  false, // GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  false, // GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  false, // GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
  false, // GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
  false, // GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
  false, // GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
  false, // GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
  false, // GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  false, // GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
  false, // GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
  false, // GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
};

u32 images[16];
u32 bg;

int main() {
  printf("Hello from input.\n");

  images[0] = load_image("assets/bg.png");
  images[GAMEPAD_BUTTON_UP] = load_image("assets/up.png");
  images[GAMEPAD_BUTTON_RIGHT] = load_image("assets/right.png");
  images[GAMEPAD_BUTTON_DOWN] = load_image("assets/down.png");
  images[GAMEPAD_BUTTON_LEFT] = load_image("assets/left.png");
  images[GAMEPAD_BUTTON_Y] = load_image("assets/y.png");
  images[GAMEPAD_BUTTON_B] = load_image("assets/b.png");
  images[GAMEPAD_BUTTON_A] = load_image("assets/a.png");
  images[GAMEPAD_BUTTON_X] = load_image("assets/x.png");
  images[GAMEPAD_BUTTON_LEFT_SHOULDER] = load_image("assets/l1.png");
  images[GAMEPAD_BUTTON_RIGHT_SHOULDER] = load_image("assets/r1.png");
  images[GAMEPAD_BUTTON_SELECT] = load_image("assets/select.png");
  images[GAMEPAD_BUTTON_START] = load_image("assets/start.png");

  bg = image_gradient(SCREEN_WIDTH, SCREEN_HEIGHT, BLUE, BLUE, GREEN, GREEN);

  return 0;
}

void buttonDown(GamepadButton button, unsigned int player) {
  buttons[button] = true;
}

void buttonUp(GamepadButton button, unsigned int player) {
  buttons[button] = false;
}

void update() {
  draw_image(bg, 0, 0);
  if (images[0]) {
    draw_image(images[0], 0, 96);
  }
  for (int i = 1; i < 16; i++) {
    if (buttons[i]) {
      if (images[i]) {
        draw_image(images[i], 0, 0);
      }
    }
  }
}
