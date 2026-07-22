#!/usr/bin/env node

// Generator for C3 null0 API bindings
// Generates C3 code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - C3 bindings for the null0 fantasy console
//
// Usage:
//
// \`\`\`c3
// import null0;
//
// fn void load() @export("load") {
//     null0::clear(null0::BLUE);
//     null0::draw_circle(100, 100, 50, null0::RED);
// }
// \`\`\`
module null0;

// handle types
alias Image = uint;
alias Font = uint;
alias Sound = uint;

// An RGBA color, packed into a single uint (ABI-compatible with host)
alias Color = uint;

// Create a Color from r, g, b, a components
fn Color rgba(char r, char g, char b, char a) {
    return (Color)r | ((Color)g << 8) | ((Color)b << 16) | ((Color)a << 24);
}

// Create an opaque Color from r, g, b components
fn Color rgb(char r, char g, char b) {
    return rgba(r, g, b, 255);
}
`
]

// map of def-types into across-wasm types
const argTypes = {
  string: 'char*',
  bool: 'bool',
  i32: 'int',
  f32: 'float',
  u32: 'uint',
  u64: 'ulong',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  ImageFilter: 'int',
  Key: 'int',
  GamepadButton: 'int',
  MouseButton: 'int',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': 'Vector*',
  SfxParams: 'SfxParams*',
  SfxPresetType: 'int'
}

// host returns structs/strings as pointers into cart-memory
const retTypes = {
  void: 'void',
  string: 'char*',
  bool: 'bool',
  i32: 'int',
  f32: 'float',
  u32: 'uint',
  u64: 'ulong',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Vector: 'Vector*',
  Dimensions: 'Dimensions*',
  Color: 'Color*',
  Rectangle: 'Rectangle*',
  SfxParams: 'SfxParams*',
  SfxPresetType: 'int'
}

const memberTypes = {
  i32: 'int',
  f32: 'float',
  u32: 'uint',
  u8: 'char'
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs (Color handled above)
for (const [structName, structDef] of Object.entries(structs)) {
  if (structName === 'Color') continue
  out.push('', `// ${structDef.description}`)
  out.push(`struct ${structName} {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberTypes[memberType] || memberType} ${memberName};`)
  }
  out.push('}')
}

// Generate enums as constdef blocks (params use plain int)
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumDef.description}`)
  out.push(`constdef ${enumName} : int {`)
  const entries = Object.entries(enumDef.enums)
  for (let i = 0; i < entries.length; i++) {
    const [enumValue, enumNumber] = entries[i]
    out.push(`    ${enumValue} = ${enumNumber}${i === entries.length - 1 ? ',' : ','}`)
  }
  out.push('}')
}

// Generate constants
out.push('', '// Constants')
out.push('const Image SCREEN = 0;')
out.push('const int SCREEN_WIDTH = 640;')
out.push('const int SCREEN_HEIGHT = 480;')
out.push('const Font FONT_DEFAULT = 0;')
out.push('', '// Colors')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`const Color ${colorName} = 0x${packed.toString(16).padStart(8, '0')}; // rgba(${r}, ${g}, ${b}, ${a})`)
  }
}

// Generate function declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${argTypes[type] || type} ${name}`)
      .join(', ')
    out.push(`// ${description}`)
    out.push(`extern fn ${retTypes[returns] || returns} ${funcName}(${params}) @wasm("null0", "${funcName}");`)
  }
}

out.push('')

await mkdir('carts/c3', { recursive: true })
await writeFile('carts/c3/null0.c3', out.join('\n'))
