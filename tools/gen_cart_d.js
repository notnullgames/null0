#!/usr/bin/env node

// Generator for D null0 API bindings
// Generates D code from the API definitions (for ldc2 -betterC wasm32)

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `//! null0 - D bindings for the null0 fantasy console
//!
//! Usage:
//!
//! \`\`\`d
//! import null0;
//!
//! export extern(C) void load() {
//!     clear(BLUE);
//!     draw_circle(100, 100, 50, RED);
//! }
//! \`\`\`
module null0;

import ldc.attributes;

alias Image = uint;
alias Font = uint;
alias Sound = uint;

/// An RGBA color, packed into a single uint (ABI-compatible with host)
alias Color = uint;

/// Create a Color from r, g, b, a components
Color rgba(ubyte r, ubyte g, ubyte b, ubyte a) {
    return cast(uint)r | (cast(uint)g << 8) | (cast(uint)b << 16) | (cast(uint)a << 24);
}

/// Create an opaque Color from r, g, b components
Color rgb(ubyte r, ubyte g, ubyte b) {
    return rgba(r, g, b, 255);
}

// basic memory-management from host (used when host returns strings/structs)

extern(C) extern __gshared ubyte __heap_base;
private __gshared ubyte* heapPtr;

export extern(C) void* malloc(size_t size) {
    if (heapPtr is null) heapPtr = &__heap_base;
    void* p = heapPtr;
    heapPtr += (size + 15) & ~cast(size_t)15;
    return p;
}

export extern(C) void free(void* ptr) {
    // carts are short-lived, let the wasm linear-memory absorb it
}`
]

// map of def-types into across-wasm types
const argTypes = {
  string: 'const(char)*',
  bool: 'bool',
  i32: 'int',
  f32: 'float',
  u32: 'uint',
  u64: 'ulong',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': 'const(Vector)*',
  SfxParams: 'const(SfxParams)*',
  SfxPresetType: 'SfxPresetType'
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
  SfxPresetType: 'SfxPresetType'
}

const memberTypes = {
  i32: 'int',
  f32: 'float',
  u32: 'uint',
  u8: 'ubyte'
}

const argsMap = (args) =>
  Object.entries(args)
    .map(([name, type]) => `${argTypes[type] || type} ${name}`)
    .join(', ')

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs (Color handled above)
for (const [structName, structDef] of Object.entries(structs)) {
  if (structName === 'Color') continue
  out.push('', `/// ${structDef.description}`)
  out.push(`struct ${structName} {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberTypes[memberType] || memberType} ${memberName};`)
  }
  out.push('}')
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `/// ${enumDef.description}`)
  out.push(`enum ${enumName} : int {`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`    ${enumValue} = ${enumNumber},`)
  }
  out.push('}')
}

// Generate constants
out.push('', '// Constants')
out.push('enum Image SCREEN = 0;')
out.push('enum int SCREEN_WIDTH = 640;')
out.push('enum int SCREEN_HEIGHT = 480;')
out.push('enum Font FONT_DEFAULT = 0;')
out.push('', '// Colors')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`enum Color ${colorName} = 0x${packed.toString(16).padStart(8, '0')}; // rgba(${r}, ${g}, ${b}, ${a})`)
  }
}

// Generate function declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    out.push(`/// ${description}`)
    out.push(`@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "${funcName}"))`)
    out.push(`extern(C) ${retTypes[returns] || returns} ${funcName}(${argsMap(args)});`)
  }
}

out.push('')

await mkdir('carts/d', { recursive: true })
await writeFile('carts/d/null0.d', out.join('\n'))
