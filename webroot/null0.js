import WasiPreview1 from '@easywasm/wasi'
import fflatefs from './fflatefs.js'

// this is output from emscripten
import loadHost from './wbuild/host/null0.mjs'

const debug = false

export default async function loadCart(cartUrl, canvas) {
  const cartName = cartUrl.split('/').pop()
  const fs = await fflatefs(cartUrl)

  return await loadHost({
    canvas,
    arguments: [cartName],
    preRun(h) {
      h.FS.createPreloadedFile('', cartName, cartUrl, true, false)

      // this is called at startup by emscripten-code
      h.cart_callback_init = (wasmBytesPtr, wasmSize) => {
        const wasmBytes = h.HEAPU8.subarray(wasmBytesPtr, wasmBytesPtr + wasmSize)

        const wasi_snapshot_preview1 = new WasiPreview1({ fs })
        const imports = { wasi_snapshot_preview1, null0: {} }

        // expose host-functions that are named _host_whatever as null0.whatever
        for (const f of Object.keys(h)) {
          if (f.startsWith('_host_')) {
            const func = f.replace(/^_host_/, '')
            imports.null0[func] = (...args) => {
              if (debug) {
                console.log(func, args)
              }
              return h[f](...args)
            }
          }
        }

        WebAssembly.instantiate(wasmBytes, imports).then(({ instance }) => {
          h.cart = instance.exports
          fs.wasm = h
          wasi_snapshot_preview1.start(h.cart)
          if (h.cart.load) {
            h.cart.load()
          }
        })
        return true
      }
    }
  })
}
