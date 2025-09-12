import ../null0

proc update*() {.null0.} =
  clear(BLACK)
  draw_circle(100, 100, 50, RED)

proc main*(argc: cint, argv: ptr cstring): cint {.null0.} =
  echo "Hello from simple(main)."
  return 0

# callbacks (optional - implement as needed)

# proc unload*() {.null0Export: "unload".} =
#   discard

# proc buttonUp*(button: GamepadButton, player: cuint) {.null0Export: "buttonUp".} =
#   discard

# proc buttonDown*(button: GamepadButton, player: cuint) {.null0Export: "buttonDown".} =
#   discard

# proc keyUp*(key: Key) {.null0Export: "keyUp".} =
#   discard

# proc keyDown*(key: Key) {.null0Export: "keyDown".} =
#   discard

# proc mouseDown*(button: cuint) {.null0Export: "mouseDown".} =
#   discard

# proc mouseUp*(button: cuint) {.null0Export: "mouseUp".} =
#   discard

# proc mouseMoved*(x: cfloat, y: cfloat) {.null0Export: "mouseMoved".} =
#   discard
