import null0

# a richer demo: shapes, text, a polygon (array-arg), and per-frame animation state

var frameCount: int = 0

proc update*() {.wasm.} =
  inc frameCount

  clear(DARKGRAY)
  draw_text(FONT_DEFAULT, "null0 demo", 20, 20, WHITE)

  draw_rectangle(40, 80, 100, 70, RED)
  draw_circle(220, 115, 45, GREEN)
  draw_triangle(320, 150, 400, 150, 360, 60, BLUE)
  draw_line(40, 250, 600, 250, LIGHTGRAY)

  var hexagon = [
    Vector(x: 460, y: 80),
    Vector(x: 520, y: 80),
    Vector(x: 550, y: 140),
    Vector(x: 520, y: 200),
    Vector(x: 460, y: 200),
    Vector(x: 430, y: 140)
  ]
  draw_polygon(addr hexagon[0], cint(hexagon.len), PURPLE)

  let x = cint(frameCount mod 600)
  draw_circle(x + 20, 350, 20, YELLOW)

  draw_text(FONT_DEFAULT, "shapes + animation + text", 20, 440, ORANGE)


# callbacks (optional - implement as needed)

# proc load*() {.wasm.} =
#   discard

# proc unload*() {.wasm.} =
#   discard

# proc buttonUp*(button: GamepadButton, player: cuint) {.wasm.} =
#   discard

# proc buttonDown*(button: GamepadButton, player: cuint) {.wasm.} =
#   discard

# proc keyUp*(key: Key) {.wasm.} =
#   discard

# proc keyDown*(key: Key) {.wasm.} =
#   discard

# proc mouseDown*(button: cuint) {.wasm.} =
#   discard

# proc mouseUp*(button: cuint) {.wasm.} =
#   discard

# proc mouseMoved*(x: cfloat, y: cfloat) {.wasm.} =
#   discard
