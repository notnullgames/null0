import { clear, draw_circle, draw_text, stringToPtr, BLUE, RED, WHITE, FONT_DEFAULT } from 'null0.ts'

// a string crosses to the host as a pointer to null-terminated utf8, so it
// goes through stringToPtr() from the bindings rather than straight in
export function load(): void {
  clear(BLUE)
  draw_circle(100, 100, 50, RED)
  draw_text(FONT_DEFAULT, stringToPtr('hello from AssemblyScript'), 170, 92, WHITE)
}

// other callbacks you can export:
//
//   export function update(): void {}
