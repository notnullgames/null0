#!/usr/bin/env node

// Generator for WebAssembly text format (WAT) null0 API bindings
// Generates a .wat file with all host imports, to paste into your module

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `;; null0 - WAT bindings for the null0 fantasy console
;;
;; WAT has no include-system, so copy the imports you need from this file
;; into your own (module ...) and call them like:
;;
;;   (module
;;     (import "null0" "clear" (func $clear (param i32)))
;;     (func (export "load")
;;       (call $clear (i32.const 0xfff17900)))) ;; BLUE
;;
;; ABI notes:
;; - all handles (Image/Font/Sound), enums, bools and pointers are i32
;; - string is a pointer to a null-terminated UTF8 string in memory (i32)
;; - Color is 4 bytes packed into a single i32: r | g<<8 | b<<16 | a<<24
;; - functions returning structs (Vector/Dimensions/Rectangle/Color/SfxParams)
;;   return a pointer (i32) into your memory, read the fields with i32.load

;; -- constants --

(global $SCREEN i32 (i32.const 0))
(global $SCREEN_WIDTH i32 (i32.const 640))
(global $SCREEN_HEIGHT i32 (i32.const 480))
(global $FONT_DEFAULT i32 (i32.const 0))
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// color constants (packed hex)
out.push(';; colors (i32 constants)')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`(global $${colorName.toLowerCase()} i32 (i32.const 0x${packed.toString(16).padStart(8, '0')})) ;; ${colorName} = rgba(${r}, ${g}, ${b}, ${a})`)
  }
}
out.push('')

// enum constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `;; ${enumName}: ${enumDef.description}`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`(global $${enumValue.toLowerCase()} i32 (i32.const ${enumNumber}))`)
  }
}
out.push('')

// struct layouts as comments
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `;; struct ${structName}: ${structDef.description}`)
  let offset = 0
  const sizes = { i32: 4, f32: 4, u32: 4, u8: 1 }
  const loads = { i32: 'i32.load', f32: 'f32.load', u32: 'i32.load', u8: 'i32.load8_u' }
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`;;   offset ${offset}: ${memberName} (${memberType}, read with ${loads[memberType]})`)
    offset += sizes[memberType] || 4
  }
}
out.push('')

// wasm type mapping
const watType = (type) => {
  switch (type) {
    case 'f32':
      return 'f32'
    case 'u64':
      return 'i64'
    case 'void':
      return null
    default:
      return 'i32'
  }
}

// Generate import declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `;; -- ${apiName.toUpperCase()} --`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.values(args).map((t) => watType(t))
    const result = watType(returns)
    let sig = `(import "null0" "${funcName}" (func $${funcName}`
    if (params.length) sig += ` (param ${params.join(' ')})`
    if (result) sig += ` (result ${result})`
    sig += '))'
    out.push(`;; ${description}`)
    out.push(sig)
  }
}

out.push('')

await mkdir('carts/wat', { recursive: true })
await writeFile('carts/wat/null0.wat', out.join('\n'))
