#!/usr/bin/env node

// Generator for Jik null0 API bindings
//
// Jik has a limited type system (int, double, char, bool, void) that does not
// directly map to null0's ABI types (u8, f32, u32, u64). The generated file
// provides extern struct/function declarations that match Jik's type system,
// plus C wrappers in @embed blocks for the functions that need type bridging.
//
// For a full cart, include this file or copy the @embed wrappers you need.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'

const out = [
  `// null0 - Jik bindings for the null0 fantasy console
//
// Jik types (int, double, char, bool) don't directly map to null0's
// ABI (u8, f32, u32, u64). This file provides C wrappers in @embed
// blocks to bridge the gap. Include what you need.
//
// Usage:
//
// \`\`\`jik
// // Copy the wrappers you need from null0.jik into your cart's @embed block,
// // or include this file and use the provided functions.
//
// @embed{C_END}
// #include "null0.h"
// C_END
//
// extern func clear as clear(r: int, g: int, b: int, a: int) -> void
// // ... etc
// \`\`\`

// Embed the C header for the underlying C implementations.
@embed{C_END}
#include "null0.h"

// C wrappers to bridge Jik's type system (int/double/char/bool)
// to null0's ABI (u8, f32, u32, u64).
// Each wrapper takes Jik-compatible types and calls the real null0 function.

C_END

// Handle types (u32 indices into host vectors)
alias Image = int
alias Font = int
alias Sound = int
alias Tilemap = int
`
]

// Jik types available: int, double, char, bool
// For null0 types that don't map directly, we use C wrappers
const argTypes = {
  string: '*char',       // char* - Jik uses *byte but extern func can use *char
  bool: 'bool',
  i32: 'int',
  f32: 'double',         // Jik has no f32 — C wrappers convert
  u32: 'int',            // Jik has no u32 — C wrappers handle
  u64: 'int',            // Jik has no u64 — C wrappers approximate
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  ImageFilter: 'int',
  Key: 'int',
  GamepadButton: 'int',
  MouseButton: 'int',
  Color: 'int',          // Color passed as packed int or individual r,g,b,a
  Vector: 'int',         // Vector passed as x,y ints
  Rectangle: 'int',      // Rectangle passed as x,y,w,h ints
  Dimensions: 'int',     // Dimensions passed as w,h ints
  'Vector[]': '*int',    // pointer to array of ints (x,y pairs)
  'i32[]': '*int',
  SfxParams: '*int',     // opaque pointer
  SfxPresetType: 'int'
}

const retTypes = {
  void: 'void',
  string: '*char',
  bool: 'bool',
  i32: 'int',
  f32: 'double',
  u32: 'int',
  u64: 'int',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  Vector: 'int',
  Dimensions: 'int',
  Color: 'int',
  Rectangle: 'int',
  SfxParams: '*int',
  SfxPresetType: 'int'
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// struct returns are an address in cart memory, like the other struct types here
seedTypes(argTypes, { enums, structs }, { enumType: 'int', structType: 'int' })
seedTypes(retTypes, { enums, structs }, { enumType: 'int', structType: 'int' })

out.push('', '// NOTE: Jik does not have u8, f32, u32, or u64 types.')
out.push('// Struct returns use C wrappers. See the generated @embed blocks.')
out.push('// For a working example, see carts/jik/simple/main.jik')
out.push('')

// Generate enums as simple int constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumDef.description}`)
  const entries = Object.entries(enumDef.enums)
  for (const [enumValue, enumNumber] of entries) {
    out.push(`// ${enumValue} = ${enumNumber}  (use as int)`)
  }
}

// Generate constants as comments (Jik doesn't support typed constants well)
out.push('', '// Constants (use these values as int literals)')
out.push('// SCREEN = 0')
out.push('// SCREEN_WIDTH = 640')
out.push('// SCREEN_HEIGHT = 480')
out.push('// FONT_DEFAULT = 0')
out.push('', '// Color values (pass r,g,b,a as individual int arguments)')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`// ${colorName}: r=${r}, g=${g}, b=${b}, a=${a}`)
  }
}

// Generate extern function declarations with notes about wrapper needs
out.push('', '// === EXTERN FUNCTIONS ===')
out.push('// Functions that take/return structs need C wrappers to bridge types.')
out.push('// Copy the @embed wrappers you need into your cart.')
out.push('')

for (const [apiName, funcDef] of Object.entries(api)) {
  out.push(`// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
      .join(', ')
    const retType = retTypes[returns]
    const retDecl = retType ? ` -> ${retType}` : ''
    out.push(`// ${description}`)
    out.push(`// extern func ${funcName} as ${funcName}(${params})${retDecl}`)
  }
}

out.push('')

await mkdir('carts/jik', { recursive: true })
await writeFile('carts/jik/null0.jik', out.join('\n'))
