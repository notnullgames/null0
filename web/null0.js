import loadCart from '@null0/browser'
import { unzip } from 'unzipit'
import memhelpers from 'cmem_helpers'
import wireCartToHost from './null0_wasm.js'

export async function getHost (cartUrl, canvas = document.body.appendChild(document.createElement('canvas'))) {
  const host = await loadCart({
    canvas,
    // noInitialRun: true,
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

  if (cart.update) {
    const cartUpdate = () => {
      cart.update()
      window.requestAnimationFrame(cartUpdate)
    }
    window.requestAnimationFrame(cartUpdate)
  }

  return out
}
