#!/usr/bin/env node

// Generator for AssemblyScript null0 API bindings
// Generates TypeScript code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `// null0 - AssemblyScript bindings for the null0 fantasy console
//
// This module provides AssemblyScript bindings for the null0 fantasy console API.
// It allows you to create games that compile to WebAssembly and run in the null0 runtime.
//
// Usage:
//
// Create your cart by implementing the required callbacks:
//
// \`\`\`typescript
// import { clear, draw_circle, BLACK, RED } from "./null0";
//
// export function load(): void {
//     // Initialize your game
// }
//
// export function update(): void {
//     // Update game logic (60 FPS)
//     clear(BLACK);
//     draw_circle(100, 100, 50, RED);
// }
// \`\`\`

// Type definitions`
]

// Type mapping from API types to AssemblyScript types
const argTypes = {
  string: 'usize', // Strings are passed as pointers in WASM FFI
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'u32',
  Font: 'u32',
  Sound: 'u32',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': 'usize', // Vector arrays are passed as pointers
  SfxParams: 'SfxParams',
  SfxPresetType: 'SfxPresetType'
}

const retTypes = {
  void: 'void',
  string: 'usize', // String returns are also pointers
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'u32',
  Font: 'u32',
  Sound: 'u32',
  Vector: 'Vector',
  Dimensions: 'Dimensions',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}

// Type mapping for struct member types
const memberTypes = {
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u8: 'u8'
}

// Generate parameter list for function signature
const argsMap = (args) => {
  const params = Object.entries(args).map(([name, type]) => {
    return `${name}: ${argTypes[type] || type}`
  })
  return params.join(', ')
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `/** ${structDef.description} */`)
  out.push(`@unmanaged`)
  out.push(`export class ${structName} {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`  ${memberName}: ${memberTypes[memberType] || memberType};`)
  }
  out.push('')
  out.push(
    `  constructor(${Object.entries(structDef.members)
      .map(([name, type]) => `${name}: ${memberTypes[type] || type}`)
      .join(', ')}) {`
  )
  for (const [memberName] of Object.entries(structDef.members)) {
    out.push(`    this.${memberName} = ${memberName};`)
  }
  out.push(`  }`)
  out.push(`}`)
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `/** ${enumDef.description} */`)
  out.push(`export enum ${enumName} {`)
  const enumEntries = Object.entries(enumDef.enums)
  for (const [enumValue, enumNumber] of enumEntries) {
    out.push(`  ${enumValue} = ${enumNumber},`)
  }
  out.push(`}`)
}

// Generate constants
out.push('', '// Screen and font constants')
out.push('export const SCREEN: u32 = 0;')
out.push('export const SCREEN_WIDTH: i32 = 640;')
out.push('export const SCREEN_HEIGHT: i32 = 480;')
out.push('export const FONT_DEFAULT: u32 = 0;')

out.push('', '// Color constants')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`export const ${colorName}: Color = new Color(${r}, ${g}, ${b}, ${a});`)
  }
}

// Generate function declarations with @external decorator
out.push('', '// Import functions from null0 module')

// Generate function declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push(``, `// ${apiName.charAt(0).toUpperCase() + apiName.slice(1)} functions`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const asReturn = retTypes[returns] || returns
    const paramList = argsMap(args)

    // Generate function declaration with description and @external decorator
    out.push(`/** ${description} */`)
    out.push(`@external("null0", "${funcName}")`)
    if (args['Vector[]']) {
      // Special handling for Vector arrays - add length parameter
      const modifiedArgs = Object.entries(args)
        .map(([name, type]) => {
          if (type === 'Vector[]') {
            return `${name}: usize, ${name}Length: i32`
          }
          return `${name}: ${argTypes[type] || type}`
        })
        .join(', ')
      out.push(`export declare function ${funcName}(${modifiedArgs}): ${asReturn};`)
    } else {
      out.push(`export declare function ${funcName}(${paramList}): ${asReturn};`)
    }
  }
}

// Add helper functions for Vector arrays
out.push('', '// Helper functions for working with Vector arrays')
out.push(`/** Convert StaticArray<Vector> to pointer for WASM FFI */`)
out.push(`export function vectorArrayToPtr(vectors: StaticArray<Vector>): usize {`)
out.push(`  return changetype<usize>(vectors);`)
out.push(`}`)

// Add string conversion helpers
out.push('', '// String conversion helpers for WASM FFI')
out.push(`/** Convert string to null-terminated C string pointer */`)
out.push(`export function stringToPtr(str: string): usize {`)
out.push(`  return changetype<usize>(String.UTF8.encode(str, true));`)
out.push(`}`)

await mkdir('carts/as', { recursive: true })
await writeFile('carts/as/null0.ts', out.join('\n'))
