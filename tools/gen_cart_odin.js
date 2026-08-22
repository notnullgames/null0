#!/usr/bin/env node

// Generator for Odin null0 API bindings
// Generates Odin code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'

const out = [
  `// null0 - Odin bindings for the null0 fantasy console
//
// Usage:
//
// \`\`\`odin
// package main
//
// import null0 "null0"
//
// @(export)
// load :: proc "c" () {
//     null0.clear(null0.BLUE)
//     null0.draw_circle(100, 100, 50, null0.RED)
// }
// \`\`\`
package null0

// handle types
Image :: distinct u32
Font :: distinct u32
Sound :: distinct u32
Tilemap :: distinct u32

// Create a Color from r, g, b, a components
rgba :: proc(r, g, b, a: u8) -> Color {
    return Color{r, g, b, a}
}

// Create an opaque Color from r, g, b components
rgb :: proc(r, g, b: u8) -> Color {
    return rgba(r, g, b, 255)
}
`
]

// map of def-types into across-wasm types
const argTypes = {
  string: 'cstring',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': '[^]Vector',
  'i32[]': '[^]i32',
  SfxParams: '^SfxParams',
  SfxPresetType: 'SfxPresetType'
}

// host returns structs/strings as pointers into cart-memory
const retTypes = {
  void: null,
  string: 'cstring',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  Vector: '^Vector',
  Dimensions: '^Dimensions',
  Color: '^Color',
  Rectangle: '^Rectangle',
  SfxParams: '^SfxParams',
  SfxPresetType: 'SfxPresetType'
}

const memberTypes = {
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u8: 'u8',
  string: 'cstring'
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// a new struct fills itself in, following this language's convention
seedTypes(argTypes, { structs }, { structType: (name) => name })
seedTypes(retTypes, { structs }, { structType: (name) => `^${name}` })

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `// ${structDef.description}`)
  out.push(`${structName} :: struct {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberName}: ${memberTypes[memberType] || memberType},`)
  }
  out.push('}')
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumDef.description}`)
  out.push(`${enumName} :: enum i32 {`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`    ${enumValue} = ${enumNumber},`)
  }
  out.push('}')
}

// Generate constants
out.push('', '// Constants')
out.push('SCREEN :: Image(0)')
out.push('SCREEN_WIDTH :: 640')
out.push('SCREEN_HEIGHT :: 480')
out.push('FONT_DEFAULT :: Font(0)')
out.push('', '// Colors')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`${colorName} :: Color{${r}, ${g}, ${b}, ${a}}`)
  }
}

// Generate foreign block
out.push('', 'foreign import null0_api "null0"', '')
out.push('@(default_calling_convention="c")')
out.push('foreign null0_api {')
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `    // ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
      .join(', ')
    const ret = retTypes[returns] ? ` -> ${retTypes[returns]}` : ''
    out.push(`    // ${description}`)
    out.push(`    ${funcName} :: proc(${params})${ret} ---`)
  }
}
out.push('}', '')

await mkdir('carts/odin/null0', { recursive: true })
await writeFile('carts/odin/null0/null0.odin', out.join('\n'))
