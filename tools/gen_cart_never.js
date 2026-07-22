#!/usr/bin/env node

// Generator for Never null0 API bindings
// Generates Never code from the API definitions
//
// NOTE: experimental. Never runs on its own VM, so these bindings document
// the API surface for a future null0-aware Never runtime.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `(* null0 - Never bindings for the null0 fantasy console

   NOTE: experimental. Never programs run on the Never VM, which cannot
   currently import null0 host functions. These bindings document the
   API surface for a future null0-aware Never runtime.

   Usage:

   func load() -> int
   {
       clear(BLUE);
       draw_circle(100, 100, 50, RED);
       0
   }

   ABI notes:
   - handles (Image/Font/Sound), enums and bools are int
   - Color is 4 bytes packed into a single int: r | g<<8 | b<<16 | a<<24
*)
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// constants
out.push('', '(* constants *)')
out.push('let SCREEN = 0;')
out.push('let SCREEN_WIDTH = 640;')
out.push('let SCREEN_HEIGHT = 480;')
out.push('let FONT_DEFAULT = 0;')

// color constants
out.push('', '(* colors, packed r | g<<8 | b<<16 | a<<24 *)')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`let ${colorName} = ${packed}; (* rgba(${r}, ${g}, ${b}, ${a}) *)`)
  }
}
out.push('')

// enum constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `(* ${enumName}: ${enumDef.description} *)`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`let ${enumValue} = ${enumNumber};`)
  }
}
out.push('')

// function signatures as comments
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `(* -- ${apiName.toUpperCase()} -- *)`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const argList = Object.entries(args)
      .map(([name, type]) => `${name}: ${type === 'f32' ? 'float' : 'int'}`)
      .join(', ')
    out.push(`(* ${description} *)`)
    out.push(`(* func ${funcName}(${argList}) -> ${returns === 'void' ? 'int' : returns === 'f32' ? 'float' : 'int'} *)`)
  }
}

out.push('')

await mkdir('carts/never', { recursive: true })
await writeFile('carts/never/null0.nev', out.join('\n'))
