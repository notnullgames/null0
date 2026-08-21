// demo wren cart for null0 (interpreted)
//
// exercises more of the API than simple/: shapes, a Vector[] polygon, text,
// and per-frame animation state. the null0 API lives on the Null0 class,
// and structs (Color/Vector/Rectangle/Dimensions/SfxParams) are classes -
// see null0.wren for the whole list. callbacks are module-level Fn variables.

import "null0" for Null0, Vector, FONT_DEFAULT, DARKGRAY, WHITE, RED, GREEN, BLUE, LIGHTGRAY, PURPLE, YELLOW, ORANGE

var frame = 0

var update = Fn.new {
  frame = frame + 1

  Null0.clear(DARKGRAY)
  Null0.draw_text(FONT_DEFAULT, "null0 demo", 20, 20, WHITE)
  Null0.draw_rectangle(40, 80, 100, 70, RED)
  Null0.draw_circle(220, 115, 45, GREEN)
  Null0.draw_triangle(320, 150, 400, 150, 360, 60, BLUE)
  Null0.draw_line(40, 250, 600, 250, LIGHTGRAY)

  // hexagon - the Vector[] array-arg call
  var hexagon = [
    Vector.new(460, 80),
    Vector.new(520, 80),
    Vector.new(550, 140),
    Vector.new(520, 200),
    Vector.new(460, 200),
    Vector.new(430, 140)
  ]
  Null0.draw_polygon(hexagon, PURPLE)

  // a circle sweeping left-to-right across the bottom, proving update()
  // is called repeatedly and state persists
  var x = frame % 600
  Null0.draw_circle(x + 20, 350, 20, YELLOW)

  Null0.draw_text(FONT_DEFAULT, "shapes + animation + text", 20, 440, ORANGE)
}
