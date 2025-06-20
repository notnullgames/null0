function load() {
  console.log('JS cart says "hi"')
}

function update() {
  clear(BLUE)
  draw_rectangle(10, 10, 100, 50, RED)
  if (key_down(KEY_SPACE)) {
    draw_text(FONT_DEFAULT, 'Space pressed!', 50, 50, WHITE)
  }
}

function unload() {
  console.log('unload')
}
