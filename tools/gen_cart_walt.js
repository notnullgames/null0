#!/usr/bin/env node

// Generator for walt null0 API bindings
// Generates a .walt file with all host imports, to copy from into your cart

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - walt bindings for the null0 fantasy console
//
// walt imports are per-module, so copy the imports you need from this file
// into your own cart, like:
//
//   type Clear = (i32) => void;
//   import { clear: Clear } from 'null0';
//
//   export function load(): void {
//     clear(BLUE);
//   }
//
// ABI notes:
// - all handles (Image/Font/Sound), enums, bools and pointers are i32
// - string is a pointer to a null-terminated UTF8 string in memory (i32)
// - Color is 4 bytes packed into a single i32: r | g<<8 | b<<16 | a<<24
// - functions returning structs (Vector/Dimensions/Rectangle/Color/SfxParams)
//   return a pointer (i32) into your memory

// constants

const SCREEN: i32 = 0;
const SCREEN_WIDTH: i32 = 640;
const SCREEN_HEIGHT: i32 = 480;
const FONT_DEFAULT: i32 = 0;
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// color constants (packed hex)
out.push('// colors')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`const ${colorName}: i32 = 0x${packed.toString(16).padStart(8, '0')}; // rgba(${r}, ${g}, ${b}, ${a})`)
  }
}
out.push('')

// enum constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumName}: ${enumDef.description}`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`const ${enumValue}: i32 = ${enumNumber};`)
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

// walt type mapping
const waltType = (type) => {
  switch (type) {
    case 'f32':
      return 'f32'
    case 'u64':
      return 'i64'
    case 'void':
      return null
    default:
      return 'i32'
  }
}

// pascal-case for type names
const pascal = (name) => name.split('_').map((p) => p.charAt(0).toUpperCase() + p.slice(1)).join('')

// Generate import declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// -- ${apiName.toUpperCase()} --`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.values(args).map((t) => waltType(t))
    const result = waltType(returns)
    const typeName = pascal(funcName)
    out.push(`// ${description}`)
    out.push(`type ${typeName} = (${params.join(', ')}) => ${result || 'void'};`)
    out.push(`// import { ${funcName}: ${typeName} } from 'null0';`)
  }
}

out.push('')

await mkdir('carts/walt', { recursive: true })
await writeFile('carts/walt/null0.walt', out.join('\n'))
