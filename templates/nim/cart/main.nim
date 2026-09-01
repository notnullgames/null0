import null0

proc load*() {.wasm.} =
  clear(BLUE)
  draw_circle(100, 100, 50, RED)
  draw_text(FONT_DEFAULT, "hello from Nim", 170, 92, WHITE)

# callbacks (optional - implement as needed)
#
#   proc update*() {.wasm.} =
#     discard
