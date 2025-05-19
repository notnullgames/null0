// TODO: this could be simplified with new input stuff
// TODO: use drawing instead of images

#include "../null0.h"

bool buttons[] = {
  false,
  false, // GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
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

  images[0] = image_load("assets/bg.png");
  images[1] = image_load("assets/up.png");
  images[2] = image_load("assets/right.png");
  images[3] = image_load("assets/down.png");
  images[4] = image_load("assets/left.png");
  images[5] = image_load("assets/y.png");
  images[6] = image_load("assets/b.png");
  images[7] = image_load("assets/a.png");
  images[8] = image_load("assets/x.png");
  images[9] = image_load("assets/l1.png");
  images[11] = image_load("assets/r1.png");
  images[13] = image_load("assets/select.png");
  images[15] = image_load("assets/start.png");

  bg = image_gradient(SCREEN_WIDTH, SCREEN_HEIGHT, BLUE, BLUE, GREEN, GREEN);

  return 0;
}

void buttonDown(GamepadButton button, unsigned int player) {
  buttons[button] = true;
}

void buttonUp(GamepadButton button, unsigned int player) {
  buttons[button] = false;
}

// all the images are in 320x240 scale, so I scale by 2

void update() {
  draw_image(SCREEN, bg, 0, 0);
  draw_image_scaled(SCREEN, images[0], 0, 94, 2, 2, 0, 0, FILTER_NEARESTNEIGHBOR);
  for (int i = 1; i < 16; i++) {
    if (buttons[i]) {
      draw_image_scaled(SCREEN, images[i], 0, 0, 2, 2, 0, 0, FILTER_NEARESTNEIGHBOR);
    }
  }
}
