package main

import null0 "null0"

@(export)
load :: proc "c" () {
    null0.clear(null0.BLUE)
    null0.draw_circle(100, 100, 50, null0.RED)
}

// callbacks (optional - implement as needed)

// @(export)
// update :: proc "c" () {}

// @(export)
// unload :: proc "c" () {}

// @(export)
// buttonUp :: proc "c" (button: null0.GamepadButton, player: u32) {}

// @(export)
// buttonDown :: proc "c" (button: null0.GamepadButton, player: u32) {}

// @(export)
// keyUp :: proc "c" (key: null0.Key) {}

// @(export)
// keyDown :: proc "c" (key: null0.Key) {}

// @(export)
// mouseDown :: proc "c" (button: null0.MouseButton) {}

// @(export)
// mouseUp :: proc "c" (button: null0.MouseButton) {}

// @(export)
// mouseMoved :: proc "c" (x, y: f32) {}
