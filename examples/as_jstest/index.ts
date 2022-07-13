import {
  cls,
  setTitle,
  drawImage,
  loadImage,
  palette
} from "../../projects/actionscript/src/null0"

const buttonState = [
  false, // A
  false, // B
  false, // X
  false, // Y
  false, // L1
  false, // R1
  false, // START
  false, // SELECT
  false, // LEFT
  false, // RIGHT
  false, // UP
  false  // DOWN
]

let images = [
  0, // A
  0, // B
  0, // X
  0, // Y
  0, // L1
  0, // R1
  0, // START
  0, // SELECT
  0, // LEFT
  0, // RIGHT
  0, // UP
  0, // DOWN
]

let font:u32

let bg:u32

// called when the cart is loaded
export function init(): void {
  setTitle("null0 - mapped input")

  bg = loadImage('assets/bg.png')
  images[0] = loadImage('assets/a.png')
  images[1] = loadImage('assets/b.png')
  images[2] = loadImage('assets/x.png')
  images[3] = loadImage('assets/y.png')
  images[4] = loadImage('assets/l1.png')
  images[5] = loadImage('assets/r1.png')
  images[6] = loadImage('assets/start.png')
  images[7] = loadImage('assets/select.png')
  images[8] = loadImage('assets/left.png')
  images[9] = loadImage('assets/right.png')
  images[10] = loadImage('assets/up.png')
  images[11] = loadImage('assets/down.png')
}

// called when buttons are pressed
export function buttonDown(button:u8):void {
  buttonState[button] = true
}

// called when buttons are let up
export function buttonUp(button:u8):void {
  buttonState[button] = false
}

// called on every frame
export function update(delta:u16): void  {
  cls(palette[2])

  drawImage(bg, 0, 50)
  for (let i = 0; i < buttonState.length; i++) {
    if (buttonState[i]) {
      drawImage(images[i], 0, 3)
    }
  }
}
