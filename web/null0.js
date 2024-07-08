import loadCart from '@null0/browser'
import { unzip } from 'unzipit'
import memhelpers from 'cmem_helpers'
import wireCartToHost from './null0_wasm.js'

/*
typedef enum GamepadButton {
  GAMEPAD_BUTTON_UNKNOWN = 0,     // Unknown button, just for error checking
  GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
  GAMEPAD_BUTTON_RIGHT = 2,           // Gamepad left DPAD right button
  GAMEPAD_BUTTON_DOWN = 3,            // Gamepad left DPAD down button
  GAMEPAD_BUTTON_LEFT = 4,            // Gamepad left DPAD left button
  GAMEPAD_BUTTON_Y = 5,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  GAMEPAD_BUTTON_B = 6,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  GAMEPAD_BUTTON_A = 7,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  GAMEPAD_BUTTON_X = 8,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  GAMEPAD_BUTTON_LEFT_SHOULDER = 9,   // Gamepad top/back trigger left (first), it could be a trailing button
  GAMEPAD_BUTTON_LEFT_TRIGGER = 10,    // Gamepad top/back trigger left (second), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_SHOULDER = 11,  // Gamepad top/back trigger right (one), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER = 12,   // Gamepad top/back trigger right (second), it could be a trailing button
  GAMEPAD_BUTTON_SELECT = 13,          // Gamepad center buttons, left one (i.e. PS3: Select)
  GAMEPAD_BUTTON_MENU = 14,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  GAMEPAD_BUTTON_START = 15,           // Gamepad center buttons, right one (i.e. PS3: Start)
  GAMEPAD_BUTTON_LEFT_THUMB = 16,      // Gamepad joystick pressed button left
  GAMEPAD_BUTTON_RIGHT_THUMB = 17,     // Gamepad joystick pressed button right
} GamepadButton;
*/

export const Buttons = {
  A: 7,
  B: 6,
  X: 8,
  Y: 5,
  START: 15,
  SELECT: 13,
  L: 9,
  R: 11,
  UP: 1,
  DOWN: 3,
  LEFT: 4,
  RIGHT: 2
}

export async function getHost (cartUrl, canvas = document.body.appendChild(document.createElement('canvas'))) {
  const host = await loadCart({
    canvas,
    preRun: async function ({ FS }) {
      await FS.createPreloadedFile('/', 'cart', cartUrl, true, false)
    },
    // for some reason it strips off .null0
    arguments: ['/cart']
  })

  const helpers = memhelpers(host.HEAPU8, host._malloc)
  return { helpers, ...host }
}

export async function setupCart (url, canvas = document.body.appendChild(document.createElement('canvas'))) {
  const host = await getHost(url, canvas)
  const out = { host }
  const cart = {}

  canvas.width = 320
  canvas.height = 240

  const imports = {
    null0: wireCartToHost(host, cart),

    // minimal WASI that only allows console logging
    wasi_snapshot_preview1: {
      fd_write (fd, iovsPtr, iovsLength, bytesWrittenPtr) {
        const iovs = new Uint32Array(cart.memory.buffer, iovsPtr, iovsLength * 2)
        if (fd === 1 || fd === 2) { // stdout/stderr
          let text = ''
          let totalBytesWritten = 0
          for (let i = 0; i < iovsLength * 2; i += 2) {
            const offset = iovs[i]
            const length = iovs[i + 1]
            text += cart.getString(offset, length)
            totalBytesWritten += length
          }
          cart.view.setInt32(bytesWrittenPtr, totalBytesWritten, true)

          // not exactly right, since it will add newlines, but this covers printf and stuff
          if (fd === 1) {
            console.log(text)
          } else {
            console.error(text)
          }
        }
        return 0
      },

      fd_close () {
        return 0
      },

      fd_fdstat_get () {
        return 0
      },

      fd_seek () {
        return 0
      },

      proc_exit (status) {
        console.error('exit', status)
        return 0
      }
    }
  }

  const { entries } = await unzip(url)

  // cart could be a plain zip file for js filesystem
  if (entries['main.wasm']) {
    const wasmBytes = await entries['main.wasm'].arrayBuffer()
    const cartMod = await WebAssembly.compile(wasmBytes)
    const { exports } = await WebAssembly.instantiate(cartMod, imports)

    for (const k of Object.keys(exports)) {
      cart[k] = exports[k]
    }

    const helpers = memhelpers(cart.memory.buffer, cart.malloc)
    cart.getString = helpers.getString
    cart.setString = helpers.setString
    cart.struct = helpers.struct
    cart.view = new DataView(cart.memory.buffer)
  }

  out.cart = cart

  if (cart._start) {
    cart._start()
  }

  if (cart.load) {
    cart.load()
  }

  if (cart.buttonDown) {
    window.addEventListener('keydown', ({key}) => {
      if (key === 'z') {
        cart.buttonDown(Buttons.B)
      }
      if (key === 'x') {
        cart.buttonDown(Buttons.A)
      }
      if (key === 'a') {
        cart.buttonDown(Buttons.Y)
      }
      if (key === 's') {
        cart.buttonDown(Buttons.X)
      }
      if (key === 'Shift') {
        cart.buttonDown(Buttons.SELECT)
      }
      if (key === 'Enter') {
        cart.buttonDown(Buttons.START)
      }
      if (key === 'q') {
        cart.buttonDown(Buttons.L)
      }
      if (key === 'w') {
        cart.buttonDown(Buttons.R)
      }
      if (key === 'ArrowUp') {
        cart.buttonDown(Buttons.UP)
      }
      if (key === 'ArrowDown') {
        cart.buttonDown(Buttons.DOWN)
      }
      if (key === 'ArrowLeft') {
        cart.buttonDown(Buttons.LEFT)
      }
      if (key === 'ArrowRight') {
        cart.buttonDown(Buttons.RIGHT)
      }
    })
  }

  if (cart.buttonUp) {
    window.addEventListener('keyup', ({key}) => {
      if (key === 'z') {
        cart.buttonUp(Buttons.B)
      }
      if (key === 'x') {
        cart.buttonUp(Buttons.A)
      }
      if (key === 'a') {
        cart.buttonUp(Buttons.Y)
      }
      if (key === 's') {
        cart.buttonUp(Buttons.X)
      }
      if (key === 'Shift') {
        cart.buttonUp(Buttons.SELECT)
      }
      if (key === 'Enter') {
        cart.buttonUp(Buttons.START)
      }
      if (key === 'q') {
        cart.buttonUp(Buttons.L)
      }
      if (key === 'w') {
        cart.buttonUp(Buttons.R)
      }
      if (key === 'ArrowUp') {
        cart.buttonUp(Buttons.UP)
      }
      if (key === 'ArrowDown') {
        cart.buttonUp(Buttons.DOWN)
      }
      if (key === 'ArrowLeft') {
        cart.buttonUp(Buttons.LEFT)
      }
      if (key === 'ArrowRight') {
        cart.buttonUp(Buttons.RIGHT)
      }
    })
  }

  if (cart.update) {
    const cartUpdate = () => {
      cart.update()
      window.requestAnimationFrame(cartUpdate)
    }
    window.requestAnimationFrame(cartUpdate)
  }

  return out
}

export default setupCart
