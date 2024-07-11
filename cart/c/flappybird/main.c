#include <math.h>
#include <null0.h>

#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

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

float d = 0;
u64 t = 0;
i32 m = 0;

float fps = 0;
char* fpsText;

// the location of land
const u16 landTop = 180;

i32 score = 0;
char scoreText[6] = "0";

typedef enum {
  GAME_INTRO,
  GAME_PLAY,
  GAME_DEAD
} GameMode;

GameMode currentMode = GAME_INTRO;

typedef struct {
  u32 images[3];
  float collisionPadding;
  float x;
  float y;
  float speed;
  float ySpeed;
  float yGravity;
  float animationSlide;
  float animTimer;
  float angle;
  i32 width;
  i32 height;
  i32 ox;
  i32 oy;
} Bird;

Bird bird = {
    .collisionPadding = 5.0f,
    .speed = 1000.0f,
    .ySpeed = 0.0f,
    .yGravity = 1500.0f,
    .animationSlide = 2.0f,
    .animTimer = 0.0f,
    .angle = 0.0f};

int main() {
  bird.images[0] = load_image("assets/bird0.png");
  bird.images[1] = load_image("assets/bird1.png");
  bird.images[2] = load_image("assets/bird2.png");
  Dimensions birdDim = measure_image(bird.images[0]);
  bird.width = birdDim.width;
  bird.height = birdDim.height;
  bird.ox = bird.width / 2.0f;
  bird.oy = bird.height / 2.0f;
  bird.x = 320 / 2;
  bird.y = 240 / 2;

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

  return 0;
}

NULL0_EXPORT("buttonDown")
void buttonDown(GamepadButton button) {
  if (currentMode == GAME_INTRO) {
    currentMode = GAME_PLAY;
    play_sound(music[0], true);
  }

  // flap
  if (currentMode == GAME_PLAY) {
    bird.ySpeed = -280.0f;
    bird.animationSlide = 0;
    play_sound(wing, false);
  }
}

// double an image and loop around screen
void parallax(u32 image, u32 x, u32 y, u32 w) {
  draw_image(image, w - (x % w), y);
  draw_image(image, w - (x % w) - w, y);
}

// update current state of bird and draw it
void draw_bird(Bird bird, float delta) {
  bird.animTimer += delta;

  if (bird.animTimer > 0.12f) {
    bird.animTimer = 0;
    bird.animationSlide += 1;
    if (bird.animationSlide > 3) {
      bird.animationSlide = 3;
    }
  }

  bird.ySpeed += bird.yGravity * delta;
  bird.y += bird.ySpeed * (delta * 10);

  if ((bird.y + bird.height / 2.0f) - bird.collisionPadding > landTop) {
    currentMode = GAME_DEAD;
    play_sound(die, false);
  }

  // bird.angle = atan2(bird.ySpeed, bird.speed) * -20;
  bird.angle = radToDeg(atan2(bird.ySpeed, bird.speed) * -20);

  // trace("time: %f, angle: %f, speed: %f, ySpeed: %f", bird.animTimer, bird.angle, bird.speed, bird.ySpeed);

  draw_image_rotated(bird.images[(t / 100) % 3], bird.x, bird.y, bird.angle, bird.ox, bird.oy, FILTER_NEARESTNEIGHBOR);
}

NULL0_EXPORT("update")
void update() {
  t = current_time();
  d = delta_time() / 1000;

  if (currentMode != GAME_DEAD) {
    m = t / 10;
  }

  parallax(sky, m / 10, 0, 457);
  parallax(land, m, landTop, 320);

  if (currentMode == GAME_INTRO) {
    draw_bird(bird, 0);
    draw_image(logo, 60, 30);
  }

  if (currentMode == GAME_PLAY) {
    draw_bird(bird, d);
    sprintf(scoreText, "%d", score);
    draw_text(font_bignumbers, scoreText, 145 - ((strlen(scoreText) - 1) * 12), 30, WHITE);
  }
}