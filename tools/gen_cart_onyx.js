#!/usr/bin/env node

// Generator for Onyx null0 API bindings
// Generates Onyx code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'

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

// handle types - plain u32 aliases, not #distinct: they're opaque
// ref-counted indexes (same as every other language's binding), not a type
// safety boundary worth the friction of a distinct type (constants like
// FONT_DEFAULT/SCREEN are untyped integer literals and don't auto-coerce
// to a #distinct wrapper, forcing casts at every call site)
Image :: u32;
Font :: u32;
Sound :: u32;
Tilemap :: u32;

// Create a Color from r, g, b, a components
rgba :: (r: u8, g: u8, b: u8, a: u8) -> Color {
    return Color.{ r, g, b, a };
}

// Create an opaque Color from r, g, b components
rgb :: (r: u8, g: u8, b: u8) -> Color { return rgba(r, g, b, 255); }
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
  Tilemap: 'Tilemap',
  ImageFilter: 'i32',
  Key: 'i32',
  GamepadButton: 'i32',
  MouseButton: 'i32',
  Color: 'Color',
  Vector: 'u32',
  Rectangle: 'u32',
  Dimensions: 'u32',
  'Vector[]': 'u32', // pointer to first Vector
  'i32[]': 'u32', // pointer to first i32
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
  Tilemap: 'Tilemap',
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
  u8: 'u8',
  string: 'u32' // pointer to the host's utf8 bytes
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// a new struct fills itself in, following this language's convention
// onyx has no enum types of its own - the values are plain i32 constants
seedTypes(argTypes, { enums, structs }, { enumType: 'i32', structType: 'u32' })
seedTypes(retTypes, { enums, structs }, { enumType: 'i32', structType: 'u32' })
seedTypes(memberTypes, { enums }, { enumType: 'i32' })

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
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
    out.push(`${colorName} :: Color.{ ${r}, ${g}, ${b}, ${a} };`)
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
