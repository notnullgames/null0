#!/usr/bin/env node

// Generator for Onyx null0 API bindings
// Generates Onyx code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - Onyx bindings for the null0 fantasy console
//
// Usage:
//
//   #load "null0.onyx"
//
//   load :: () {
//       clear(BLUE);
//       draw_circle(100, 100, 50, RED);
//   }
//   #export "load" load
//
// ABI notes:
// - string is passed as a u32 pointer to a null-terminated UTF8 string
// - Color is 4 bytes packed into a single u32: r | g<<8 | b<<16 | a<<24
// - functions returning structs (Vector/Dimensions/Rectangle/Color/SfxParams)
//   return a u32 pointer into your memory

// handle types
Image :: #distinct u32;
Font :: #distinct u32;
Sound :: #distinct u32;

// An RGBA color, packed into a single u32 (ABI-compatible with host)
Color :: #distinct u32;

// Create a Color from r, g, b, a components
rgba :: (r: u32, g: u32, b: u32, a: u32) =>
    cast(Color, r | (g << 8) | (b << 16) | (a << 24));

// Create an opaque Color from r, g, b components
rgb :: (r: u32, g: u32, b: u32) => rgba(r, g, b, 255);
`
]

// map of def-types into across-wasm types
const argTypes = {
  string: 'u32', // pointer to null-terminated UTF8 string
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  ImageFilter: 'i32',
  Key: 'i32',
  GamepadButton: 'i32',
  MouseButton: 'i32',
  Color: 'Color',
  Vector: 'u32',
  Rectangle: 'u32',
  Dimensions: 'u32',
  'Vector[]': 'u32', // pointer to first Vector
  SfxParams: 'u32', // pointer to SfxParams
  SfxPresetType: 'i32'
}

const retTypes = {
  void: 'void',
  string: 'u32',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Vector: 'u32', // pointer to Vector
  Dimensions: 'u32', // pointer to Dimensions
  Color: 'u32', // pointer to Color
  Rectangle: 'u32', // pointer to Rectangle
  SfxParams: 'u32', // pointer to SfxParams
  SfxPresetType: 'i32'
}

const memberTypes = {
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u8: 'u8'
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs (Color handled above)
for (const [structName, structDef] of Object.entries(structs)) {
  if (structName === 'Color') continue
  out.push('', `// ${structDef.description}`)
  out.push(`${structName} :: struct {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberName}: ${memberTypes[memberType] || memberType};`)
  }
  out.push('}')
}

// Generate enum constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumName}: ${enumDef.description}`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`${enumValue} :: ${enumNumber};`)
  }
}

// Generate constants
out.push('', '// Constants')
out.push('SCREEN :: 0;')
out.push('SCREEN_WIDTH :: 640;')
out.push('SCREEN_HEIGHT :: 480;')
out.push('FONT_DEFAULT :: 0;')
out.push('', '// Colors')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`${colorName} :: cast(Color, 0x${packed.toString(16).padStart(8, '0')}); // rgba(${r}, ${g}, ${b}, ${a})`)
  }
}

// Generate foreign block
out.push('', '#foreign "null0" {')
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
      .join(', ')
    out.push(`// ${description}`)
    out.push(`${funcName} :: (${params}) -> ${retTypes[returns] || returns} ---`)
  }
}
out.push('}', '')

await mkdir('carts/onyx', { recursive: true })
await writeFile('carts/onyx/null0.onyx', out.join('\n'))
