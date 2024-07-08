import loadCart from '@null0/browser'
import { unzip } from 'unzipit'

// this is GamePadButton enum
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

// this will take an emscripten host, and setup imports for plain-wasm cart
export function getImports(host) {
  const out = {
    wasi_snapshot_preview1: {
      args_get() {},
      args_sizes_get() {},
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
      proc_exit() {}
    },
    
    env: {
      memory: host.wasmMemory
    },

    null0: {}
  }

  for (let n of Object.keys(host)) {
    const m = /^_null0_(.+)/g.exec(n)
    if (m){
      out.null0[m[1]] = host[n]
    }
  }

  // here I can wrap to debug
  out.null0.load_image = s => {
    const o = host._null0_load_image(s)
    console.log('load_image', host.UTF8ToString(s), o)
    return o
  }

  return out
}

// load cart as file, load host
export async function getHost (cartUrl, canvas = document.body.appendChild(document.createElement('canvas'))) {
  const host = await loadCart({
    canvas,
    preRun: async function ({ FS }) {
      await FS.createPreloadedFile('/', 'cart', cartUrl, true, false)
    },
    // for some reason it strips off .null0
    arguments: ['/cart']
  })
  canvas.width = 320
  canvas.height = 240
  return host
}

// entry-point for web-stuff
export async function setupCart(cartUrl, canvas = document.body.appendChild(document.createElement('canvas'))) {
  const host = await getHost(cartUrl, canvas)
  const importObj = getImports(host)
  const { entries } = await unzip(cartUrl)
  if (entries['main.wasm']) {
    const wasmBytes = await entries['main.wasm'].arrayBuffer()
    const cartMod = await WebAssembly.compile(wasmBytes)
    const cart = {...(await WebAssembly.instantiate(cartMod, importObj)).exports, imports: importObj}

    // console.log({cart, host})

    if (cart._start) {
      cart._start()
    }

    if (cart.load) {
      cart.load()
    }

    if (cart.update) {
      const cartUpdate = () => {
        cart.update()
        window.requestAnimationFrame(cartUpdate)
      }
      window.requestAnimationFrame(cartUpdate)
    }

    // TODO: add real joystick handler here, too

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

    return {cart, host}
  }
}

export default setupCart

