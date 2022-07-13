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
} from "./null0"

// assets
let cat:u32
let music:u32

// track if the music has been loaded
let musicPlaying = false

// main counter, increments every frame
let counter = 0

// do animations like this:
const catFrames = [36, 37, 38, 39, 40, 41]
let catFrame = 0
const defaultFont = 0

// called when the cart is loaded
export function init(): void {
  setTitle('Demo Game')

  log('Hi, from inside the cart. Edit src/index.ts to make your game!')
  
  // load any resources 
  cat = loadImage('assets/cat.png')
  music = loadMusic('assets/brainless_introtune.mod')
}

// called when resources are loaded (after init)
export function loaded(id: u32): void {
  log('loaded asset #' + id.toString())

  if (id === cat) {
    log('cat image loaded.')
  }

  if (id === music) {
    musicPlaying = true
    playMusic(music)
  }
}

// called on every frame
export function update(delta:u16): void  {
  counter += 1
  if (counter % 20 === 0) {
    catFrame += 1
  }

  cls(palette[0])
  drawText('Demo Game', 90, 50, palette[3], 40, defaultFont)
  
  if (!musicPlaying) {
    drawText('Click to hear sounds (on web.)', 90, 90, palette[6], 15, defaultFont)
  }
  drawSprite(cat, <u16>catFrames[catFrame % catFrames.length] , 32, 32, 152, 200,)
}