#!/usr/bin/env node

// Generator for WebAssembly text format (WAT) null0 API bindings
// Generates a .wat file with all host imports, to paste into your module

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `;; null0 - WAT bindings for the null0 fantasy console
;;
;; WAT has no include-system, so copy the imports/data/globals you need from
;; this file into your own (module ...). Every module needs its own copy of
;; any (data ...) segments and (global ...) pointers you use, since data
;; segments can't be shared across modules. Call it like:
;;
;;   (module
;;     (import "null0" "clear" (func $clear (param i32)))
;;     (memory (export "memory") 1)
;;     (data (i32.const 65536) "\\00\\79\\f1\\ff") ;; BLUE bytes (r g b a)
;;     (global $blue i32 (i32.const 65536))
;;     (func (export "load")
;;       (call $clear (global.get $blue))))
;;
;; ABI notes:
;; - all handles (Image/Font/Sound), enums, bools are i32
;; - string is a pointer to a null-terminated UTF8 string in memory (i32)
;; - Color/Vector/Rectangle/Dimensions/SfxParams are ALWAYS passed and
;;   returned as an i32 pointer into wasm memory, never packed into a
;;   scalar - Color is 4 bytes (r, g, b, a); write them into your own
;;   memory (e.g. via a data segment, like the color constants below) and
;;   pass the address
;; - functions returning structs return a pointer (i32) into your memory,
;;   read the fields with i32.load / i32.load8_u at the offsets noted below

;; -- constants --

(global $SCREEN i32 (i32.const 0))
(global $SCREEN_WIDTH i32 (i32.const 640))
(global $SCREEN_HEIGHT i32 (i32.const 480))
(global $FONT_DEFAULT i32 (i32.const 0))
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// color constants: 4 bytes (r,g,b,a) each, placed in a data segment starting
// at offset 65536 (1 page in, out of the way of typical stack/data use), with
// a pointer global for each - a Color is ALWAYS a pointer, never packed
out.push(';; colors (each is a data segment of 4 bytes + a pointer global)')
const colorEntries = Object.entries(constants).filter(([, def]) => def.type === 'Color')
let colorOffset = 65536
for (const [colorName, colorDef] of colorEntries) {
  const [r, g, b, a] = colorDef.value
  const bytes = [r, g, b, a].map((n) => '\\' + n.toString(16).padStart(2, '0')).join('')
  out.push(`(data (i32.const ${colorOffset}) "${bytes}") ;; ${colorName} = rgba(${r}, ${g}, ${b}, ${a})`)
  out.push(`(global $${colorName.toLowerCase()} i32 (i32.const ${colorOffset}))`)
  colorOffset += 4
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
