// TODO: this could be simplified with new input stuff
// TODO: use drawing instead of images

#include <null0.h>

bool buttons[] = {
    false,
    false,  // GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
    false,  // GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
    false,  // GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
    false,  // GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
    false,  // GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    false,  // GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    false,  // GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    false,  // GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    false,  // GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
    false,  // GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
    false,  // GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
    false,  // GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
    false,  // GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
    false,  // GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    false,  // GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
    false,  // GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
    false,  // GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
};

u32 images[16];
u32 bg;

int main() {
  trace("Hello from input.");

  images[0] = load_image("assets/bg.png");
  images[1] = load_image("assets/up.png");
  images[2] = load_image("assets/right.png");
  images[3] = load_image("assets/down.png");
  images[4] = load_image("assets/left.png");
  images[5] = load_image("assets/y.png");
  images[6] = load_image("assets/b.png");
  images[7] = load_image("assets/a.png");
  images[8] = load_image("assets/x.png");
  images[9] = load_image("assets/l1.png");
  images[11] = load_image("assets/r1.png");
  images[13] = load_image("assets/select.png");
  images[15] = load_image("assets/start.png");

  bg = image_gradient(320, 240, BLUE, BLUE, GREEN, GREEN);

  return 0;
}

NULL0_EXPORT("buttonDown")
void buttonDown(GamepadButton button) {
  buttons[button] = true;
}

NULL0_EXPORT("buttonUp")
void buttonUp(GamepadButton button) {
  buttons[button] = false;
}

NULL0_EXPORT("update")
void update() {
  draw_image(bg, 0, 0);
  draw_image(images[0], 0, 47);

  for (int i = 1; i < 16; i++) {
    if (buttons[i]) {
      draw_image(images[i], 0, 0);
    }
  }
}