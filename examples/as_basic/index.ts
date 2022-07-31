import {
  log,
  cls,
  drawText,
  getFPS,
  loadFont,
  loadImage,
  loadMusic,
  palette,
  playMusic,
  setTitle,
  imageWidth,
  imageHeight,
  drawImage,
  drawSprite,
  playSound,
  loadSound,
  soundPlaying,
  exit
} from "../../projects/actionscript/src/null0"

let logo:u32
let music:u32
let cat:u32
let bounce:u32

const catFrames = [36, 37, 38, 39, 40, 41]
let catFrame = 0

let x:i16 = 0
let y:i16 = 0

let xSpeed:i16 = 1
let ySpeed:i16 = 1

let counter:u16 = 0


// called when the cart is loaded
export function init(): void {
  setTitle("null0 - basic demo")
  logo = loadImage('assets/logo.png')
  cat = loadImage('assets/cat.png')
  music = loadMusic('assets/powermetal.xm')
  bounce = loadSound("assets/bounce.wav")

  // I call it here, which will start it silently on web (until user clicks)
  log('playing music now')
  playMusic(music)
}

// called when resources are loaded (after init)
export function loaded(id: u32): void {
  if (id === logo) {
    const w:u32 = imageWidth(logo)
    const  h:u32 = imageHeight(logo)
    log('loaded logo: ' + w.toString() + 'x' +  h.toString())
  }

  if (id === bounce) {
    log('loaded sound: bounce')
  }

  if (id === music) {
    log('loaded music')
  }

  if (id === cat) {
    const w:u32 = imageWidth(cat)
    const  h:u32 = imageHeight(cat)
    log('loaded cat: ' + w.toString() + 'x' +  h.toString())
  }
}

// called on every frame
export function update(delta:u16): void  {
  counter += 1

  const touching = (x <= 0 || y <= 0 || x >= 276 || y >= 198)

  if (touching && !soundPlaying(bounce)) {
    playSound(bounce)
  }
  
  // DVD-style thing
  cls(touching ? palette[15] : palette[0])

  x = x + xSpeed
  y = y + ySpeed
  if (x > 280) xSpeed = -1
  if (x < 0) xSpeed = 1
  if (y > 200) ySpeed = -1
  if (y < 0) ySpeed = 1
  
  drawImage(logo, x, y);

  if (counter % 20 === 0) {
    catFrame += 1
  }

  drawSprite(cat, <u16>catFrames[catFrame % catFrames.length] , 32, 32, 152, 200)
  drawText('null0', 120, 80,  palette[3], 50, 0)
}
