import "null0" for Null0, BLUE, RED, WHITE, FONT_DEFAULT

var load = Fn.new {
  Null0.clear(BLUE)
  Null0.draw_circle(100, 100, 50, RED)
  Null0.draw_text(FONT_DEFAULT, "hello from Wren", 170, 92, WHITE)
}

// other callbacks you can define:
//
//   var update = Fn.new {}
//   var buttonDown = Fn.new { |button, player| }
