#!/usr/bin/env node

// Generator for walt null0 API bindings
// Generates a .walt file with all host imports, to copy from into your cart

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - walt bindings for the null0 fantasy console
//
// walt imports are per-module, so copy the imports/constants/statements you
// need from this file into your own cart. You'll also need a local memory
// (walt requires this even for plain i32.store8, and importing memory from
// 'env' doesn't work here since null0 doesn't provide it):
//
//   export const memory: Memory = { initial: 2 };
//
//   two pages because the colors live at 65536, one page in; and exported
//   because the web host reads Color pointers out of cart.memory.buffer
//   (the native host gets the memory instance from WAMR either way, so a
//   missing export only breaks in a browser)
//
//   type Clear = (i32) => void;
//   import { clear: Clear } from 'null0';
//
//   export function load(): void {
//     // populate the color constants below, once - inline these stores
//     // directly in a function body; wrapping them in their own function
//     // triggers a walt-compiler codegen bug (invalid bytecode)
//     i32.store8(65536, 0); i32.store8(65537, 121);
//     i32.store8(65538, 241); i32.store8(65539, 255);
//     clear(BLUE);
//   }
//
// ABI notes:
// - all handles (Image/Font/Sound), enums, bools are i32
// - string is a pointer to a null-terminated UTF8 string in memory (i32)
// - Color/Vector/Rectangle/Dimensions/SfxParams are ALWAYS passed and
//   returned as an i32 pointer into wasm memory, never packed into a
//   scalar - Color is 4 bytes (r, g, b, a); the color constants below are
//   pointers to fixed addresses - write the bytes there yourself (see the
//   inline store statements below each constant) before first use
// - functions returning structs return a pointer (i32) into your memory,
//   read the fields with i32.load / i32.load8_u at the offsets noted below

// constants

const SCREEN: i32 = 0;
const SCREEN_WIDTH: i32 = 640;
const SCREEN_HEIGHT: i32 = 480;
const FONT_DEFAULT: i32 = 0;
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// color constants: each is a pointer to 4 bytes (r,g,b,a) at a fixed address
// starting at 65536 (1 page in) - copy the matching store8 statements into
// your own load(), inline (not in a separate function - see note above)
out.push('// colors (pointers; copy the matching stores into your own load())')
const colorEntries = Object.entries(constants).filter(([, def]) => def.type === 'Color')
let colorOffset = 65536
for (const [colorName, colorDef] of colorEntries) {
  const [r, g, b, a] = colorDef.value
  out.push(`const ${colorName}: i32 = ${colorOffset}; // rgba(${r}, ${g}, ${b}, ${a})`)
  out.push(`// i32.store8(${colorOffset}, ${r}); i32.store8(${colorOffset + 1}, ${g}); i32.store8(${colorOffset + 2}, ${b}); i32.store8(${colorOffset + 3}, ${a});`)
  colorOffset += 4
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
