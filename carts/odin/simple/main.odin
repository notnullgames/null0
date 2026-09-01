package main

import null0 "null0"

@(export)
load :: proc "c" () {
    null0.clear(null0.BLUE)
    null0.draw_circle(100, 100, 50, null0.RED)
    null0.draw_text(null0.FONT_DEFAULT, "hello from Odin", 170, 92, null0.WHITE)
}

// callbacks (optional - implement as needed)
//
//   @(export)
//   update :: proc "c" () {}
