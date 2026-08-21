package main

import null0 "null0"

// persistent frame counter, incremented once per update()
frame: i32 = 0

// hexagon for draw_polygon: an array of Vector structs
hex_points := [6]null0.Vector{
    {460, 80},
    {520, 80},
    {550, 140},
    {520, 200},
    {460, 200},
    {430, 140},
}

@(export)
update :: proc "c" () {
    null0.clear(null0.DARKGRAY)
    null0.draw_text(null0.FONT_DEFAULT, "null0 demo", 20, 20, null0.WHITE)
    null0.draw_rectangle(40, 80, 100, 70, null0.RED)
    null0.draw_circle(220, 115, 45, null0.GREEN)
    null0.draw_triangle(320, 150, 400, 150, 360, 60, null0.BLUE)
    null0.draw_line(40, 250, 600, 250, null0.LIGHTGRAY)
    null0.draw_polygon(raw_data(hex_points[:]), 6, null0.PURPLE)

    // animate a circle sweeping left-to-right across the bottom of the screen
    frame += 1
    x := frame % 600
    null0.draw_circle(x + 20, 350, 20, null0.YELLOW)

    null0.draw_text(null0.FONT_DEFAULT, "shapes + animation + text", 20, 440, null0.ORANGE)
}

// callbacks (optional - implement as needed)

// @(export)
// load :: proc "c" () {}

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
