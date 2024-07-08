#include <null0.h>

u32 bird[3];
u32 land;
u32 logo;
u32 pipeBottom;
u32 pipeTop;
u32 sky;
u32 font_pixel_18x16;
u32 font_bignumbers;

u32 die;
u32 hit;
u32 point;
u32 swooshing;
u32 wing;
u32 music[3];

u64 t = 0;
i32 y = 100;
bool flying = false;

i32 flap = 0;

int main() {
  bird[0] = load_image("assets/bird0.png");
  bird[1] = load_image("assets/bird1.png");
  bird[2] = load_image("assets/bird2.png");

  land = load_image("assets/land.png");
  logo = load_image("assets/logo.png");
  pipeBottom = load_image("assets/pipe-bottom.png");
  pipeTop = load_image("assets/pipe-top.png");
  sky = load_image("assets/sky.png");

  font_pixel_18x16 = load_font_tty("assets/font_pixel-18x16.png", 18, 16, " !*+,-./0123\"456789:;<=#>?@ABCDEFG$HIJKLMNOPQ%RSTUVWXYZ[&\\]^_`'(){|}~");
  font_bignumbers = load_font_tty("assets/font_bignumbers.png", 24, 36, "0123456789 ");

  die = load_sound("assets/sounds/die.ogg");
  hit = load_sound("assets/sounds/hit.ogg");
  point = load_sound("assets/sounds/point.ogg");
  swooshing = load_sound("assets/sounds/swooshing.ogg");
  wing = load_sound("assets/sounds/wing.ogg");

  music[0] = load_sound("assets/sounds/music1.ogg");
  music[1] = load_sound("assets/sounds/music2.ogg");
  music[2] = load_sound("assets/sounds/music3.ogg");

  play_sound(music[0], true);

  return 0;
}

NULL0_EXPORT("buttonDown")
void buttonDown(GamepadButton button) {
  if (button == GAMEPAD_BUTTON_A) {
    flying = true;
    // TODO: proper flap & rotate
    y -= 30;
  }
}

NULL0_EXPORT("update")
void update() {
  t = current_time() / 10;

  if (y > 155) {
    flying = false;
  }

  if (flying) {
    y += 2;
  }

  draw_image(sky, 0, 0);
  if (flying) {
    draw_image(land, 320 - (t % 320), 180);
    draw_image(land, 320 - (t % 320) - 320, 180);
    draw_image(bird[(t / 10) % 3], 143, y);
  } else {
    draw_image(land, 0, 180);
    draw_image(bird[0], 143, y);
  }
}