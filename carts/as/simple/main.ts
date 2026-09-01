import { clear, draw_circle, draw_text, BLUE, RED, WHITE, FONT_DEFAULT } from 'null0.ts'

export function load(): void {
  clear(BLUE)
  draw_circle(100, 100, 50, RED)
  draw_text(FONT_DEFAULT, 'hello from AssemblyScript', 170, 92, WHITE)
}

// other callbacks you can export:
//
//   export function update(): void {}
