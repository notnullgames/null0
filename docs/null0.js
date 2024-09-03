import loadCart from './wasm/null0.mjs'
import wireCartToHost from './null0_wasm.js'

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

// get just the null0 wasm-host (emscripten)
export async function getHost (cartUrl, canvas = document.body.appendChild(document.createElement('canvas'))) {
  const cartname = cartUrl.split('/').pop().split('.')[0]

  const host = await loadCart({
    canvas,
    preRun: async function ({ FS }) {
      await FS.createPreloadedFile('/', cartname, cartUrl, true, false)
    },
    // for some reason it strips off .null0
    arguments: [`/${cartname}`]
  })

  // read a file from inside the cart
  host.readCartFile = (filename) => {
    const filenamePtr = host._malloc(filename.length + 1)
    host.stringToUTF8(filename, filenamePtr, filename.length + 1)
    const bytesHostPtr = host._malloc(4)
    const retPtr = host._null0_file_read(filenamePtr, bytesHostPtr)
    const r = host.HEAPU8.slice(retPtr, retPtr + host.HEAPU32[bytesHostPtr / 4])
    host._free(bytesHostPtr)
    host._free(filenamePtr)
    host._free(retPtr)
    return r
  }

  return host
}

// setup a cart with engine
export async function setupCart (url, canvas = document.body.appendChild(document.createElement('canvas'))) {
  const host = await getHost(url, canvas)
  const out = { host }
  const cart = {}

  canvas.width = 320
  canvas.height = 240
  canvas.setAttribute('tabindex', 0)
  canvas.addEventListener('click', () => canvas.focus())

  // TODO: focus/unfocus handlers for sound

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

  const wasmBytes = host.readCartFile('main.wasm')
  const cartMod = await WebAssembly.compile(wasmBytes)
  const { exports } = await WebAssembly.instantiate(cartMod, imports)

  for (const k of Object.keys(exports)) {
    cart[k] = exports[k]
  }

  const d = new TextDecoder()
  cart.getString = (offset, length) => d.decode(exports.memory.buffer.slice(offset, offset + length))
  cart.view = new DataView(exports.memory.buffer)

  out.cart = cart

  if (cart._start) {
    cart._start()
  }

  if (cart.load) {
    cart.load()
  }

  if (cart.buttonDown) {
    canvas.addEventListener('keydown', ({ key }) => {
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
    canvas.addEventListener('keyup', ({ key }) => {
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

  const cartUpdate = () => {
    if (cart.update) {
      cart.update()
    }
    window.requestAnimationFrame(cartUpdate)
    if (cart.frameCallback) {
      cart.frameCallback()
    }
  }
  window.requestAnimationFrame(cartUpdate)

  return out
}

export default setupCart
