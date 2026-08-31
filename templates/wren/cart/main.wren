// simple wren cart for null0 (interpreted)
//
// the null0 API lives on the Null0 class, and structs (Color/Vector/
// Rectangle/Dimensions/SfxParams) are classes - see null0.wren for the
// whole list. callbacks are module-level Fn variables.

import "null0" for Null0, BLUE, RED, WHITE, KEY_SPACE, FONT_DEFAULT

var counter = 0

var load = Fn.new {
  System.print("wren cart says \"hi\"")
  System.print("Press buttons to see reaction.")
  System.print("Press SPACE to see text on screen.")
}

var buttonDown = Fn.new { |button, player|
  System.print("buttonDown: %(button) %(player)")
}

var update = Fn.new {
  counter = counter + 1
  Null0.clear(BLUE)
  Null0.draw_rectangle(10, 10, 100, 50, RED)
  if (Null0.key_down(KEY_SPACE)) {
    Null0.draw_text(FONT_DEFAULT, "Space pressed!", 50, 50, WHITE)
  }
}

// other callbacks you can implement:
// var unload = Fn.new {}
// var buttonUp = Fn.new { |button, player| }
// var keyUp = Fn.new { |key| }
// var keyDown = Fn.new { |key| }
// var mouseDown = Fn.new { |button| }
// var mouseUp = Fn.new { |button| }
// var mouseMoved = Fn.new { |x, y| }
