const buttons = {}

let bg

export function load() {
  console.log('hello from input-js')
  bg = image_gradient(SCREEN_WIDTH, SCREEN_HEIGHT, BLUE, BLUE, GREEN, GREEN)
}

export function update() {
  draw_image(bg, 0, 0)

  // L/R
  draw_circle_outline(140, 214, 130, 10, buttons[GAMEPAD_BUTTON_LEFT_SHOULDER] ? DARKGRAY : BLACK)
  draw_circle_outline(500, 214, 130, 10, buttons[GAMEPAD_BUTTON_RIGHT_SHOULDER] ? DARKGRAY : BLACK)

  // Center connecting bar
  draw_rectangle(200, 110, 240, 220, LIGHTGRAY)
  draw_rectangle_outline(200, 110, 240, 220, 2, BLACK)

  // Left controller outer ring
  draw_circle(140, 220, 130, LIGHTGRAY)
  draw_circle_outline(140, 220, 130, 5, BLACK)

  // Right controller outer ring
  draw_circle(500, 220, 130, LIGHTGRAY)
  draw_circle_outline(500, 220, 130, 5, BLACK)

  // Right controller inner pad
  draw_circle(500, 220, 105, DARKGRAY)
  draw_circle_outline(500, 220, 105, 5, BLACK)

  // circle for D-pad
  draw_circle_outline(140, 220, 75, 5, BLACK)

  // D-pad buttons
  draw_rectangle(120, 200, 40, 40, BLACK) // middle
  draw_rectangle(120, 160, 40, 40, buttons[GAMEPAD_BUTTON_UP] ? DARKGRAY : BLACK) // N
  draw_rectangle(160, 200, 40, 40, buttons[GAMEPAD_BUTTON_RIGHT] ? DARKGRAY : BLACK) // E
  draw_rectangle(120, 240, 40, 40, buttons[GAMEPAD_BUTTON_DOWN] ? DARKGRAY : BLACK) // S
  draw_rectangle(80, 200, 40, 40, buttons[GAMEPAD_BUTTON_LEFT] ? DARKGRAY : BLACK) // W

  // BG for action buttons
  draw_circle(500, 220, 70, RAYWHITE)
  draw_circle_outline(500, 220, 70, 4, BLACK)

  // Action buttons (4 red circles on right)
  draw_circle(460, 220, 23, GREEN)
  draw_circle(500, 185, 23, BLUE)
  draw_circle(500, 255, 23, YELLOW)
  draw_circle(540, 220, 23, RED)
  draw_circle_outline(460, 220, 23, 5, buttons[GAMEPAD_BUTTON_Y] ? LIME : BLACK)
  draw_circle_outline(500, 185, 23, 5, buttons[GAMEPAD_BUTTON_X] ? DARKBLUE : BLACK)
  draw_circle_outline(500, 255, 23, 5, buttons[GAMEPAD_BUTTON_B] ? ORANGE : BLACK)
  draw_circle_outline(540, 220, 23, 5, buttons[GAMEPAD_BUTTON_A] ? MAROON : BLACK)

  // select/start
  draw_rectangle(260, 290, 45, 17, BLACK) // select
  draw_rectangle(330, 290, 45, 17, BLACK) // start
  draw_rectangle_outline(260, 290, 45, 17, 4, buttons[GAMEPAD_BUTTON_SELECT] ? DARKGRAY : BLACK)
  draw_rectangle_outline(330, 290, 45, 17, 4, buttons[GAMEPAD_BUTTON_START] ? DARKGRAY : BLACK)
}

export function buttonDown(button, player) {
  buttons[button] = true
}

export function buttonUp(button, player) {
  buttons[button] = false
}
