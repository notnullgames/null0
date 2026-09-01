#!/usr/bin/env node

// Generator for AssemblyScript null0 API bindings
// Generates TypeScript code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'

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
  Tilemap: 'u32',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': 'usize', // Vector arrays are passed as pointers
  'i32[]': 'usize', // i32 arrays are passed as pointers
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
  Tilemap: 'u32',
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
  u8: 'u8',
  string: 'usize' // a pointer to the host's utf8 bytes, not an AS string
}

// Generate parameter list for function signature
const argsMap = (args) => {
  const params = Object.entries(args).map(([name, type]) => {
    return `${name}: ${argTypes[type] || type}`
  })
  return params.join(', ')
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// a new struct fills itself in (an @unmanaged class is already a pointer)
seedTypes(argTypes, { structs }, { structType: (name) => name })
seedTypes(retTypes, { structs }, { structType: (name) => name })

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
out.push('', '// Constants')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`export const ${colorName}: Color = new Color(${r}, ${g}, ${b}, ${a});`)
  } else {
    out.push(`export const ${colorName}: ${colorDef.type} = ${JSON.stringify(colorDef.value)};`)
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

    // A string crosses as a pointer, but making every cart write
    // stringToPtr(...) at the call site is exactly the kind of 1:1 mapping the
    // other high-level bindings avoid. Declare the raw import under a _ptr
    // name and export an ergonomic wrapper over it.
    const stringArgs = Object.entries(args).filter(([, type]) => type === 'string')
    if (stringArgs.length || returns === 'string') {
      const rawParams = Object.entries(args)
        .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
        .join(', ')
      out.push(`/** ${description} (raw pointer form) */`)
      out.push(`@external("null0", "${funcName}")`)
      out.push(`export declare function ${funcName}_ptr(${rawParams}): ${asReturn};`)

      const niceParams = Object.entries(args)
        .map(([name, type]) => `${name}: ${type === 'string' ? 'string' : argTypes[type] || type}`)
        .join(', ')
      const callArgs = Object.entries(args)
        .map(([name, type]) => (type === 'string' ? `stringToPtr(${name})` : name))
        .join(', ')
      const niceReturn = returns === 'string' ? 'string' : asReturn
      const call = `${funcName}_ptr(${callArgs})`
      out.push(`/** ${description} */`)
      out.push(`export function ${funcName}(${niceParams}): ${niceReturn} {`)
      if (returns === 'void') {
        out.push(`  ${call};`)
      } else if (returns === 'string') {
        out.push(`  return ptrToString(${call});`)
      } else {
        out.push(`  return ${call};`)
      }
      out.push(`}`)
      continue
    }

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
out.push('')
out.push(`/** Read a null-terminated utf8 string the host wrote into cart memory */`)
out.push(`export function ptrToString(ptr: usize): string {`)
out.push(`  return ptr == 0 ? '' : String.UTF8.decodeUnsafeCStr(ptr);`)
out.push(`}`)

await mkdir('carts/as', { recursive: true })
await writeFile('carts/as/null0.ts', out.join('\n'))
