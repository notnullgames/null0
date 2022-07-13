// NULL0 Web Runtime

/* global zip, WebAssembly, fetch, Image, Audio, FontFace, Blob */

import { ChiptuneJsConfig, ChiptuneJsPlayer } from './chiptune2.mjs'

// TODO: look into using webgl canvas, instead

export const B_A = 0
export const B_B = 1
export const B_X = 2
export const B_Y = 3
export const B_L1 = 4
export const B_R1 = 5
export const B_START = 6
export const B_SELECT = 7
export const B_LEFT = 8
export const B_RIGHT = 9
export const B_UP = 10
export const B_DOWN = 11

export const keyMap = {
  KeyX: B_A,
  KeyZ: B_B,
  KeyS: B_X,
  KeyA: B_Y,
  KeyQ: B_L1,
  KeyW: B_R1,
  Enter: B_START,
  ShiftLeft: B_SELECT,
  ArrowLeft: B_LEFT,
  ArrowRight: B_RIGHT,
  ArrowUp: B_UP,
  ArrowDown: B_DOWN
}

export const gamepadMap = [1, 0, 3, 2, 4, 5, 9, 8, 14, 15, 12, 13]

const gamePadeState = [false, false, false, false, false, false, false, false, false, false, false, false]
const gamePadeStateOld = [false, false, false, false, false, false, false, false, false, false, false, false]

// Euclidean modulus (wrap around)
const emod = (n, m) => (n % m + m) % m

export default class WebRuntime {
  constructor (wasmBinary, canvas, prefix = '') {
    this.wasmBinary = wasmBinary
    this.canvas = canvas
    this.prefix = prefix
    this.musicPlayer = false
    this.ctx = canvas.getContext('2d')
    this.controllers = []

    const runtime = this

    this.imports = {
      env: {
        abort (message, fileName, lineNumber, columnNumber) {
          message = runtime.getString(message >>> 0)
          fileName = runtime.getString(fileName >>> 0)
          lineNumber = lineNumber >>> 0
          columnNumber = columnNumber >>> 0;
          (() => {
            throw Error(`${message} in ${fileName}:${lineNumber}:${columnNumber}`)
          })()
        },

        seed () {
          return Math.random() * Date.now()
        },

        null0_getFPS () {
          return (1 / (runtime.delta / 1000)) | 0
        },

        null0_exit () {
          runtime.running = false
        },

        null0_setTitle (title) {
          document.title = runtime.getString(title >>> 0)
        },

        null0_log (text) {
          console.log(runtime.getString(text >>> 0))
        },

        null0_cls (color) {
          runtime.ctx.fillStyle = runtime.toColor(color)
          runtime.ctx.fillRect(0, 0, 320, 240)
        },

        null0_loadImage (p) {
          return runtime.getImage(runtime.getString(p >>> 0))
        },

        null0_loadSound (p) {
          return runtime.getSound(runtime.getString(p >>> 0))
        },

        null0_loadMusic (p) {
          return runtime.getMusic(runtime.getString(p >>> 0))
        },

        null0_loadFont (p) {
          return runtime.getFont(runtime.getString(p >>> 0))
        },

        null0_drawImage (image, x, y) {
          if (image && runtime.assets[image] && runtime.assets[image].loaded) {
            runtime.ctx.drawImage(runtime.assets[image].image, x, y)
          }
        },

        null0_drawSprite (image, frame, width, height, x, y) {
          image = image >>> 0
          if (!image || !runtime.assets[image] || !runtime.assets[image].loaded) {
            return
          }

          // this allows negative & wrap-around positioning
          x = emod(x, 320)
          y = emod(y, 240)

          const columns = (runtime.assets[image].image.width / width) | 0
          const frameX = (((frame % columns) | 0) * width)
          const frameY = (((frame / columns) | 0) * height)
          runtime.ctx.drawImage(runtime.assets[image].image, frameX, frameY, width, height, x, y, width, height)
        },

        null0_imageWidth (image) {
          if (image && runtime.assets[image] && runtime.assets[image].loaded) {
            return runtime.assets[image].image.width
          }
          return 0
        },

        null0_imageHeight (image) {
          if (image && runtime.assets[image] && runtime.assets[image].loaded) {
            return runtime.assets[image].image.height
          }
          return 0
        },

        null0_playMusic (a) {
          if (runtime.assets[a]) {
            runtime.assets[a].playing = Date.now()
            if (runtime.assets[a].loaded && runtime.musicPlayer) {
              runtime.musicPlayer.play(runtime.assets[a].buffer)
            }
          }
        },

        null0_stopMusic (a) {
          if (runtime.assets[a]) {
            runtime.assets[a].playing = 0
            if (runtime.assets[a].loaded && runtime.musicPlayer) {
              runtime.musicPlayer.stop()
            }
          }
        },

        null0_playSound (sound) {
          if (!sound || !runtime.assets[sound] || !runtime.assets[sound].loaded || !runtime.musicPlayer) {
            return
          }
          runtime.assets[sound].play()
        },

        null0_soundPlaying (sound) {
          if (!sound || !runtime.assets[sound] || !runtime.assets[sound].loaded) {
            return false
          }
          return !runtime.assets[sound].paused
        },

        null0_drawText (text, x, y, color, size, font) {
          size = size || 10

          // this allows negative & wrap-around positioning
          x = emod(x, 320)
          y = emod(y, 240)

          const { name } = runtime.assets[font]
          runtime.ctx.fillStyle = runtime.toColor(color)
          runtime.ctx.font = `${size / 2}px ${name}`
          runtime.ctx.fillText(runtime.getString(text), x, y + size)
        }
      }
    }
  }

  // start the runtime
  async run () {
    const fileHeader = new Uint8Array(this.wasmBinary).subarray(0, 4).toString()
    if (fileHeader === '80,75,3,4') { // zip
      const z = new zip.ZipReader(new zip.Uint8ArrayReader(new Uint8Array(this.wasmBinary)))
      this.zipFile = (await z.getEntries()).filter(f => !f.directory && !f.filename.split('/').pop().startsWith('.') && !f.filename.startsWith('__MACOSX'))
      const c = this.zipFile.find(f => f.filename === 'cart.wasm')
      if (!c) {
        throw new Error('No cart.wasm')
      }
      console.log('ZIP', this.zipFile)
      this.wasmBinary = await c.getData(new zip.Uint8ArrayWriter())
    }

    this.running = true
    this.oldtime = 0
    this.newtime = 0
    this.delta = 0
    const m = await WebAssembly.instantiate(await WebAssembly.compile(this.wasmBinary), this.imports)
    this.cart = m.exports
    this.memory = m.exports.memory
    this.stringType = 0
    this.assets = [{ type: 'font', name: 'null0', loaded: true }]

    if (m.exports.memory && m.exports.__collect && m.exports.__new && m.exports.__pin && m.exports.__rtti_base && m.exports.__unpin) { // assemblyscript runtime
      this.stringType = 1
    }

    this.loaded = id => this.cart.loaded ? this.cart.loaded(id) : null

    if (this.cart.init) {
      this.cart.init()
    }

    if (this.cart.update) {
      const doUpdate = () => {
        this.oldtime = this.newtime
        this.newtime = window.performance.now()
        this.delta = this.newtime - this.oldtime
        if (this.cart.update) {
          this.cart.update(this.delta)
        }
        if (this.cart.buttonUp || this.cart.buttonDown) {
          const [gamepad] = navigator.getGamepads()
          if (gamepad) {
            for (const b in gamepadMap) {
              gamePadeState[b] = gamepad.buttons[gamepadMap[b]].pressed
              if (gamePadeState[b] !== gamePadeStateOld[b]) {
                if (gamePadeState[b]) {
                  if (this.cart.buttonDown) {
                    this.cart.buttonDown(b)
                  }
                } else {
                  if (this.cart.buttonUp) {
                    this.cart.buttonUp(b)
                  }
                }
              }
              gamePadeStateOld[b] = gamePadeState[b]
            }
          }
        }
        if (this.running) {
          window.requestAnimationFrame(doUpdate)
        }
      }
      doUpdate()
    }

    document.addEventListener('click', () => {
      this.musicPlayer = new ChiptuneJsPlayer(new ChiptuneJsConfig(-1))
      for (const a in this.assets) {
        const asset = this.assets[a]
        if (asset && asset.type === 'music') {
          if (asset.playing) {
            this.musicPlayer.play(asset.buffer)
            // TODO: this is currently broken
            this.musicPlayer.setPositionSeconds((Date.now() - asset.playing) / 1000)
          }
          this.loaded(a)
        }
      }
    }, { once: true })

    document.addEventListener('keydown', e => {
      if (this.running) {
        e.preventDefault()
        if (this.cart.buttonDown && typeof keyMap[e.code] !== 'undefined') {
          this.cart.buttonDown(keyMap[e.code])
        }
      }
    })

    document.addEventListener('keyup', e => {
      if (this.running) {
        e.preventDefault()
        if (this.cart.buttonUp && typeof keyMap[e.code] !== 'undefined') {
          this.cart.buttonUp(keyMap[e.code])
        }
      }
    })
  }

  // u16 RGBA to rgba color string
  toColor (num) {
    num >>>= 0
    const r = ((num & 0xFF000000) >>> 24)
    const g = (num & 0xFF0000) >>> 16
    const b = (num & 0xFF00) >>> 8
    const a = (num & 0xFF) / 255
    return 'rgba(' + [r, g, b, a].join(',') + ')'
  }

  // get a string from a pointer in WASM
  getString (pointer) {
    // TODO: handle other types of strings
    if (this.stringType === 1) { // assemblyscript
      if (!pointer) return null
      const
        end = pointer + new Uint32Array(this.memory.buffer)[pointer - 4 >>> 2] >>> 1
      const memoryU16 = new Uint16Array(this.memory.buffer)
      let
        start = pointer >>> 1
      let string = ''
      while (end - start > 1024) string += String.fromCharCode(...memoryU16.subarray(start, start += 1024))
      return string + String.fromCharCode(...memoryU16.subarray(start, end))
    }
  }

  // get an Image to insert into assets
  getImage (filename) {
    const a = this.assets.length
    this.assets.push({ type: 'image', loaded: false, filename })
    const img = new Image()
    img.addEventListener('load', () => {
      this.assets[a].image = img
      this.assets[a].loaded = true
      URL.revokeObjectURL(img.src)
      this.loaded(a)
    })

    if (this.zipFile) {
      const f = this.zipFile.findIndex(f => f.filename === filename)
      if (f === -1) {
        console.error(`File not found: ${filename}`)
      } else {
        this.zipFile[f].getData(new zip.Uint8ArrayWriter())
          .then(fi => {
            img.src = URL.createObjectURL(new Blob([fi]))
          })
      }
    } else {
      img.src = `${this.prefix}${filename}`
    }
    return a
  }

  // get an Audio to insert into assets
  getSound (filename) {
    const a = this.assets.length
    this.assets.push({ type: 'sound', loaded: false, filename })
    const aud = new Audio()
    aud.addEventListener('canplaythrough', () => {
      this.assets[a].audio = aud
      URL.revokeObjectURL(aud.src)
      // loaded(a) not called to prevent audio before click
    })

    if (this.zipFile) {
      const f = this.zipFile.findIndex(f => f.filename === filename)
      if (f === -1) {
        console.error(`File not found: ${filename}`)
      } else {
        const f = this.zipFile.findIndex(f => f.filename === filename)
        this.zipFile[f].getData(new zip.Uint8ArrayWriter())
          .then(fi => {
            aud.src = URL.createObjectURL(new Blob([fi]))
          })
      }
    } else {
      aud.src = `${this.prefix}${filename}`
    }
    return a
  }

  // get a music file to insert into assets
  getMusic (filename) {
    const a = this.assets.length
    this.assets.push({ type: 'music', loaded: false, playing: 0, filename })

    if (this.zipFile) {
      const f = this.zipFile.find(f => f.filename === filename)
      if (f === -1) {
        console.error(`File not found: ${filename}`)
      } else {
        f.getData(new zip.Uint8ArrayWriter())
          .then(buffer => {
            this.assets[a].buffer = buffer
            this.assets[a].loaded = true
            // loaded(a) not called to prevent audio before click
          })
      }
    } else {
      fetch(this.prefix + filename).then(r => r.arrayBuffer()).then(buffer => {
        this.assets[a].buffer = buffer
        this.assets[a].loaded = true
        // loaded(a) not called to prevent audio before click
      })
    }
    return a
  }

  // get a font to insert into assets
  getFont (filename) {
    const a = this.assets.length
    const name = `font${a}`
    this.assets.push({ type: 'font', name, loaded: false, filename })

    if (this.zipFile) {
      const f = this.zipFile.findIndex(f => f.filename === filename)
      if (typeof f === 'undefined') {
        console.error(`File not found: ${filename}`)
      } else {
        this.zipFile[f].getData(new zip.Uint8ArrayWriter())
          .then(fi => {
            const url = URL.createObjectURL(new Blob([fi]))
            const face = new FontFace(name, `url("${url}")`)
            face.load().then(() => {
              document.fonts.add(face)
              this.assets[a].loaded = true
              URL.revokeObjectURL(url)
              this.loaded(a)
            })
          })
      }
    } else {
      const face = new FontFace(name, `url("${this.prefix}${filename}")`)
      face.load().then(() => {
        document.fonts.add(face)
        this.assets[a].loaded = true
        this.loaded(a)
      })
    }
    return a
  }
}
