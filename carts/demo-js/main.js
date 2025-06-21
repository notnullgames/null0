import mod from './mod.js'

export function load() {
  console.log('JS cart says "hi"')
  console.log(`${mod.name} loaded`)
  console.log('Press buttons to see reaction.')
  console.log('Press SDPACE to see text on screen.')
}

export function buttonDown(button, player) {
  if (player === 9999) {
    player = '(keyboard)'
  }
  console.log(`buttonDown: ${button} ${player}`)
}

export function buttonUp(button, player) {
  if (player === 9999) {
    player = '(keyboard)'
  }
  console.log(`buttonUp: ${button} ${player}`)
}

export function update() {
  clear(BLUE)
  draw_rectangle(10, 10, 100, 50, RED)
  if (key_down(KEY_SPACE)) {
    draw_text(FONT_DEFAULT, 'Space pressed!', 50, 50, WHITE)
  }
}
