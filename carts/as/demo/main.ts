// AssemblyScript null0 cart example

import {
  clear,
  draw_text,
  draw_rectangle,
  draw_circle,
  draw_triangle,
  draw_line,
  draw_polygon,
  stringToPtr,
  DARKGRAY,
  WHITE,
  RED,
  GREEN,
  BLUE,
  LIGHTGRAY,
  PURPLE,
  YELLOW,
  ORANGE,
  FONT_DEFAULT,
} from 'null0.ts'

// module-level state, persists across update() calls
let frame: i32 = 0

// hexagon - the trickiest binding: an array of Vector structs.
// NOTE: StaticArray<Vector> (+ vectorArrayToPtr) does NOT work here - Vector
// is still a class, and AS stores class-typed array elements as pointers to
// separately-allocated instances, not inline {x,y} structs. The host expects
// a flat, packed Vector[] (two contiguous i32s per point), so build that
// directly as a static memory segment instead.
const hexagon: usize = memory.data<i32>([460, 80, 520, 80, 550, 140, 520, 200, 460, 200, 430, 140])

export function update(): void {
  frame++

  clear(DARKGRAY)
  draw_text(FONT_DEFAULT, stringToPtr('null0 demo'), 20, 20, WHITE)
  draw_rectangle(40, 80, 100, 70, RED)
  draw_circle(220, 115, 45, GREEN)
  draw_triangle(320, 150, 400, 150, 360, 60, BLUE)
  draw_line(40, 250, 600, 250, LIGHTGRAY)
  draw_polygon(hexagon, 6, PURPLE)

  // sweep a circle left-to-right across the bottom, proving update() runs
  // repeatedly and state persists
  const x: i32 = frame % 600
  draw_circle(x + 20, 350, 20, YELLOW)

  draw_text(FONT_DEFAULT, stringToPtr('shapes + animation + text'), 20, 440, ORANGE)
}

// callbacks (optional - implement as needed)

// export function load(): void {}
// export function unload(): void {}
// export function buttonUp(button: i32, player: u32): void {}
// export function buttonDown(button: i32, player: u32): void {}
// export function keyUp(key: i32): void {}
// export function keyDown(key: i32): void {}
// export function mouseDown(button: u32): void {}
// export function mouseUp(button: u32): void {}
// export function mouseMoved(x: f32, y: f32): void {}
