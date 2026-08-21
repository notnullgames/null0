#!/usr/bin/env node

// Generator for Zen-C null0 API bindings
// Zen-C compiles to C, so the C header does the heavy lifting.
// This generates an idiomatic Zen-C wrapper with explicit externs.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - Zen-C bindings for the null0 fantasy console
//
// Usage:
//
// \`\`\`zc
// include "null0.h"
//
// export fn load() {
//     clear(BLUE);
//     draw_circle(100, 100, 50, RED);
// }
// \`\`\`

// handle types (u32 indices into host vectors)
alias Image = uint;
alias Font = uint;
alias Sound = uint;
alias Tilemap = uint;
`
]

// map of def-types into Zen-C types for extern declarations
const argTypes = {
  string: '*char',       // char*
  bool: 'bool',
  i32: 'int',
  f32: 'float',
  u32: 'uint',
  u64: 'ulong',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  ImageFilter: 'int',
  Key: 'int',
  GamepadButton: 'int',
  MouseButton: 'int',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': '*Vector',
  'i32[]': '*int',
  SfxParams: '*SfxParams',
  SfxPresetType: 'int'
}

// host returns structs/strings as pointers into cart-memory
const retTypes = {
  void: 'void',
  string: '*char',
  bool: 'bool',
  i32: 'int',
  f32: 'float',
  u32: 'uint',
  u64: 'ulong',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  Vector: 'Vector',
  Dimensions: 'Dimensions',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: '*SfxParams',
  SfxPresetType: 'int'
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `// ${structDef.description}`)
  out.push(`struct ${structName} {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    const zcType = { i32: 'int', f32: 'float', u32: 'uint', u8: 'byte' }[memberType] || memberType
    out.push(`    ${memberName}: ${zcType},`)
  }
  out.push('}')
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumDef.description}`)
  const entries = Object.entries(enumDef.enums)
  for (const [enumValue, enumNumber] of entries) {
    out.push(`const ${enumValue} = ${enumNumber};`)
  }
}

// Generate constants
out.push('', '// Constants')
out.push('const SCREEN: Image = 0;')
out.push('const SCREEN_WIDTH: int = 640;')
out.push('const SCREEN_HEIGHT: int = 480;')
out.push('const FONT_DEFAULT: Font = 0;')
out.push('', '// Colors')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`const ${colorName} = Color { r = ${r}, g = ${g}, b = ${b}, a = ${a} };`)
  }
}

// Generate extern function declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
      .join(', ')
    const retType = retTypes[returns] || returns
    const retDecl = retType === 'void' ? '' : ` -> ${retType}`
    out.push(`// ${description}`)
    out.push(`extern fn ${funcName}(${params})${retDecl};`)
  }
}

// Generate callback stubs (for cart to export)
out.push('', '// Callbacks (cart exports)')
out.push('export fn load();')
out.push('export fn update();')
out.push('export fn unload();')

for (const [cbName, cbDef] of Object.entries(callbacks)) {
  const params = Object.entries(cbDef.args)
    .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
    .join(', ')
  const cbParams = Object.entries(cbDef.args)
    .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
    .join(', ')
  out.push(`// ${cbDef.description}`)
  out.push(`export fn ${cbName}(${cbParams});`)
}

out.push('')

await mkdir('carts/zenc', { recursive: true })
await writeFile('carts/zenc/null0.zc', out.join('\n'))
