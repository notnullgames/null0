#!/usr/bin/env node

// Generator for Grain null0 API bindings
// Generates Grain code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - Grain bindings for the null0 fantasy console
//
// Grain needs foreign declarations inside your own module, so copy the
// ones you need from this file, like:
//
//   module Main
//
//   from "runtime/unsafe/wasmi32" include WasmI32
//
//   foreign wasm clear: (WasmI32) => Void from "null0"
//
//   // Color is a pointer to 4 bytes (r, g, b, a) in memory, not a packed
//   // scalar - write the bytes once (e.g. first thing in load()) before
//   // using a color constant:
//   @unsafe
//   provide let load = () => {
//     WasmI32.store8(WasmI32.fromGrain(65536), WasmI32.fromGrain(0), 0n)
//     WasmI32.store8(WasmI32.fromGrain(65536), WasmI32.fromGrain(121), 1n)
//     WasmI32.store8(WasmI32.fromGrain(65536), WasmI32.fromGrain(241), 2n)
//     WasmI32.store8(WasmI32.fromGrain(65536), WasmI32.fromGrain(255), 3n)
//     clear(WasmI32.fromGrain(blue))
//   }
//
//   provide let update = () => void
//
// ABI notes:
// - all handles (Image/Font/Sound), enums, bools are WasmI32
// - string is a pointer to a null-terminated UTF8 string in memory (WasmI32)
// - Color/Vector/Rectangle/Dimensions/SfxParams are ALWAYS passed and
//   returned as a WasmI32 pointer into wasm memory, never packed into a
//   scalar - Color is 4 bytes (r, g, b, a); the color constants below are
//   addresses (plain Numbers, wrap with WasmI32.fromGrain() like any other
//   arg) - write the bytes there yourself (see the inline WasmI32.store8
//   calls below each constant) before first use
// - functions returning structs return a pointer (WasmI32) into your
//   memory, read the fields with WasmI32.load / WasmI32.load8U at the
//   offsets noted below
// - anything touching Wasm types needs an @unsafe attribute

// constants

let SCREEN = 0
let SCREEN_WIDTH = 640
let SCREEN_HEIGHT = 480
let FONT_DEFAULT = 0
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// color constants: each is an address (pointer) at a fixed offset starting
// at 65536 (1 page in) - copy the matching store8 calls into your own load()
out.push('// colors (addresses; copy the matching stores into your own load())')
const colorEntries = Object.entries(constants).filter(([, def]) => def.type === 'Color')
let colorOffset = 65536
for (const [colorName, colorDef] of colorEntries) {
  const [r, g, b, a] = colorDef.value
  const lname = colorName.toLowerCase()
  out.push(`let ${lname} = ${colorOffset} // ${colorName} = rgba(${r}, ${g}, ${b}, ${a})`)
  const bytes = [r, g, b, a]
  const stores = bytes.map((v, i) => `WasmI32.store8(WasmI32.fromGrain(${lname}), WasmI32.fromGrain(${v}), ${i}n)`).join('; ')
  out.push(`// ${stores}`)
  colorOffset += 4
}
out.push('')

// enum constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumName}: ${enumDef.description}`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`let ${enumValue.toLowerCase()} = ${enumNumber}`)
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
    out.push(`foreign wasm ${funcName}: (${params.join(', ')}) => ${result || 'Void'} from "null0"`)
  }
}

out.push('')

await mkdir('carts/grain', { recursive: true })
await writeFile('carts/grain/null0.gr', out.join('\n'))
