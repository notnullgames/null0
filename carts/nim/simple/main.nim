import ../null0

proc load*() {.wasm.} =
  clear(BLUE)
  draw_circle(100, 100, 50, RED)
  echo "Hello from simple(load)."


# callbacks (optional - implement as needed)

# proc update*() {.wasm.} =
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
