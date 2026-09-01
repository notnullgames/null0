// the null0 API is available as plain globals - nothing to import. drop
// null0.d.ts next to this file for editor completion.

export function load () {
  clear(BLUE)
  draw_circle(100, 100, 50, RED)
  draw_text(FONT_DEFAULT, 'hello from JavaScript', 170, 92, WHITE)
}

// other callbacks you can export:
//
//   export function update () {}
//   export function unload () {}
//   export function buttonDown (button, player) {}
