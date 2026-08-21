// module-level state, persists across update() calls
let frame = 0

// hexagon - the trickiest binding: an array of {x, y} objects
const hexagon = [
  { x: 460, y: 80 },
  { x: 520, y: 80 },
  { x: 550, y: 140 },
  { x: 520, y: 200 },
  { x: 460, y: 200 },
  { x: 430, y: 140 },
]

export function update() {
  frame++

  clear(DARKGRAY)
  draw_text(FONT_DEFAULT, 'null0 demo', 20, 20, WHITE)
  draw_rectangle(40, 80, 100, 70, RED)
  draw_circle(220, 115, 45, GREEN)
  draw_triangle(320, 150, 400, 150, 360, 60, BLUE)
  draw_line(40, 250, 600, 250, LIGHTGRAY)
  draw_polygon(hexagon, PURPLE)

  // sweep a circle left-to-right across the bottom, proving update() runs
  // repeatedly and state persists
  const x = frame % 600
  draw_circle(x + 20, 350, 20, YELLOW)

  draw_text(FONT_DEFAULT, 'shapes + animation + text', 20, 440, ORANGE)
}

// callbacks (optional - implement as needed)

// export function load() {}
// export function unload() {}
// export function buttonUp(button, player) {}
// export function buttonDown(button, player) {}
// export function keyUp(key) {}
// export function keyDown(key) {}
// export function mouseDown(button) {}
// export function mouseUp(button) {}
// export function mouseMoved(x, y) {}
