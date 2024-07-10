// this will generate the web-host wrapper

import { getAPI } from './shared.js'
import { writeFile } from 'fs/promises'

const api = await getAPI()

const out = [
`// Null0 host interface for web

const MAX_STRING_LEN = 1024 * 20

const td = new TextDecoder()

export default function wireCartToHost (host, cart) {
  let cartMem

  const copyBytesFromCart = (cartPtr, size, retPtr) => {
    cartMem ||= new Uint8Array(cart.memory.buffer)
    const hostPtr = retPtr || host._malloc(size)
    for (let b = 0; b < size; b++) {
      host.HEAPU8[hostPtr + b] = cartMem[cartPtr + b]
    }
    return hostPtr
  }

  const copyBytesToCart = (hostPtr, size, retPtr) => {
    cartMem ||= new Uint8Array(cart.memory.buffer)
    const cartPtr = retPtr || cart.malloc(size)
    for (let b = 0; b < size; b++) {
      cartMem[cartPtr + b] = host.HEAPU8[hostPtr + b]
    }
    return cartPtr
  }

  const cartStrlen = (pointer) => {
    cartMem ||= new Uint8Array(cart.memory.buffer)
    let end = pointer
    while (end < (pointer + MAX_STRING_LEN)) {
      if (cartMem[end] === 0) {
        break
      }
      end++
    }
    return end - pointer
  }

  const hostStrlen = (pointer) => {
    let end = pointer
    while (end < (pointer + MAX_STRING_LEN)) {
      if (host.HEAPU8[end] === 0) {
        break
      }
      end++
    }
    return end - pointer
  }

  return {`
]

const funcs = []

const poterRets = [
    'SfxParams',
    'Vector',
    'Dimensions', 'Rectangle',
    'bytes',      'FileInfo',
    'Color'
  ]


for (const cat of Object.values(api)) {
  for (const fname of Object.keys(cat)) {
    const al = Object.keys(cat[fname].args)
    if (poterRets.includes(cat[fname].returns)) {
      al.unshift('retPtr')
    }
    funcs.push(`${fname}(${al.join(', ')}) {}`)
  }
}

out.push(funcs.map(f => `    ${f}`).join(',\n'))
out.push(`  }\n}`)

await writeFile('docs/null0_wasm.js', out.join('\n'))
