#!/usr/bin/env node

// Generator for Grain null0 API bindings
// Generates Grain code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - Grain bindings for the null0 fantasy console
//
// use it as a module (the null0-cart-grain docker image copies this file
// next to your main.gr automatically if you don't ship your own):
//
//   module Main
//
//   from "./null0.gr" include Null0
//
//   @unsafe
//   provide let load = () => {
//     Null0.initColors()
//     Null0.clear(Null0.blue)
//     Null0.draw_circle(100n, 100n, 50n, Null0.red)
//   }
//
//   provide let update = () => void
//
// ABI notes:
// - everything crosses the wasm boundary as a raw WasmI32/WasmI64/WasmF32
//   value - use the literal suffixes 1n/1N/1.0w, NEVER plain Numbers or
//   fromGrain (those are tagged/boxed grain representations, not raw values)
// - handles (Image/Font/Sound), bools and enum values are WasmI32 - the
//   constants below are already WasmI32, pass them directly
// - string is a pointer to a null-terminated UTF8 string in memory (WasmI32)
// - Color/Vector/Rectangle/Dimensions/SfxParams are ALWAYS passed and
//   returned as a WasmI32 pointer into wasm memory, never packed into a
//   scalar - Color is 4 bytes (r, g, b, a); the color constants below are
//   pointers - call initColors() once (first thing in load()) to write the
//   bytes there before first use
// - functions returning structs return a WasmI32 pointer into your memory -
//   read the fields with WasmI32.load / WasmI32.load8U at the offsets noted
//   below - the pointer is only valid until the current callback returns,
//   so copy out what you need
// - anything touching Wasm types needs an @unsafe attribute

module Null0

from "runtime/unsafe/wasmi32" include WasmI32
from "runtime/unsafe/wasmi64" include WasmI64
from "runtime/unsafe/wasmf32" include WasmF32

// constants

@unsafe
provide let screen = 0n
@unsafe
provide let screenWidth = 640n
@unsafe
provide let screenHeight = 480n
@unsafe
provide let fontDefault = 0n
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// color constants: each is a pointer to 4 bytes (r, g, b, a) at a fixed
// offset starting at 65536 (1 page in); initColors() writes the actual bytes
out.push('// colors (pointers to r, g, b, a bytes - call initColors() before use)')
const colorEntries = Object.entries(constants).filter(([, def]) => def.type === 'Color')
const colorInits = []
let colorOffset = 65536
for (const [colorName, colorDef] of colorEntries) {
  const [r, g, b, a] = colorDef.value
  const lname = colorName.toLowerCase()
  out.push(`@unsafe`)
  out.push(`provide let ${lname} = ${colorOffset}n // ${colorName} = rgba(${r}, ${g}, ${b}, ${a})`)
  const bytes = [r, g, b, a]
  colorInits.push(...bytes.map((v, i) => `  WasmI32.store8(${lname}, ${v}n, ${i}n)`))
  colorOffset += 4
}
out.push('')
out.push('// write every color-constant byte into memory - call once, first thing in load()')
out.push('@unsafe')
out.push('provide let initColors = () => {')
out.push(colorInits.join('\n'))
out.push('}')
out.push('')

// enum constants, camelCased so they don't collide with function names
// (KEY_UP vs key_up()) in this flat module namespace
const camel = (s) => s.toLowerCase().replace(/_([a-z0-9])/g, (_, c) => c.toUpperCase())
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumName}: ${enumDef.description}`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push('@unsafe')
    out.push(`provide let ${camel(enumValue)} = ${enumNumber}n`)
  }
}
out.push('')

// struct layouts as comments
const sizes = { i32: 4, f32: 4, u32: 4, u8: 1 }
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `// struct ${structName}: ${structDef.description}`)
  let offset = 0
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`//   offset ${offset}: ${memberName} (${memberType})`)
    offset += sizes[memberType] || 4
  }
}
out.push('')

// grain wasm type mapping
const grainType = (type) => {
  switch (type) {
    case 'f32':
      return 'WasmF32'
    case 'u64':
      return 'WasmI64'
    case 'void':
      return null
    default:
      return 'WasmI32'
  }
}

// Generate foreign declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// -- ${apiName.toUpperCase()} --`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.values(args).map((type) => grainType(type))
    const result = grainType(returns)
    out.push(`// ${description}`)
    out.push('@unsafe')
    out.push(`provide foreign wasm ${funcName}: (${params.join(', ')}) => ${result || 'Void'} from "null0"`)
  }
}

out.push('')

await mkdir('carts/grain', { recursive: true })
await writeFile('carts/grain/null0.gr', out.join('\n'))
