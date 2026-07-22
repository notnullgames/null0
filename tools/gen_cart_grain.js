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
//   @unsafe
//   provide let load = () => {
//     clear(WasmI32.fromGrain(blue))
//   }
//
//   provide let update = () => void
//
// ABI notes:
// - all handles (Image/Font/Sound), enums, bools and pointers are WasmI32
// - string is a pointer to a null-terminated UTF8 string in memory (WasmI32)
// - Color is 4 bytes packed into a single i32: r | g<<8 | b<<16 | a<<24
//   (the color constants below are plain Numbers, wrap them with
//   WasmI32.fromGrain() when calling)
// - functions returning structs (Vector/Dimensions/Rectangle/Color/SfxParams)
//   return a pointer (WasmI32) into your memory
// - anything touching Wasm types needs an @unsafe attribute

// constants

let SCREEN = 0
let SCREEN_WIDTH = 640
let SCREEN_HEIGHT = 480
let FONT_DEFAULT = 0
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// color constants
out.push('// colors (packed r | g<<8 | b<<16 | a<<24)')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`let ${colorName.toLowerCase()} = 0x${packed.toString(16).padStart(8, '0')} // ${colorName} = rgba(${r}, ${g}, ${b}, ${a})`)
  }
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
