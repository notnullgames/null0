#!/usr/bin/env node

// Generator for wisp (lisp) null0 API bindings
// Generates wisp code from the API definitions
//
// NOTE: experimental. wisp is a very immature lisp-on-wasm; these bindings
// document the API surface for when wisp supports host imports.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `;;; null0 - wisp bindings for the null0 fantasy console
;;;
;;; NOTE: experimental. wisp cannot currently import null0 host functions;
;;; these bindings document the API surface for when it can.
;;;
;;; Usage:
;;;
;;;   (defn load () (clear BLUE) (draw-circle 100 100 50 RED))
;;;
;;; ABI notes:
;;; - handles (Image/Font/Sound), enums and bools are i32
;;; - Color is 4 bytes packed into a single i32: r | g<<8 | b<<16 | a<<24
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

const kebab = (name) => name.replace(/_/g, '-')

// constants
out.push('', ';;; constants')
out.push('(def SCREEN 0)')
out.push('(def SCREEN-WIDTH 640)')
out.push('(def SCREEN-HEIGHT 480)')
out.push('(def FONT-DEFAULT 0)')

// color constants
out.push('', ';;; colors (packed r | g<<8 | b<<16 | a<<24)')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`(def ${colorName} ${packed}) ; rgba(${r}, ${g}, ${b}, ${a})`)
  }
}
out.push('')

// enum constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `;;; ${enumName}: ${enumDef.description}`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`(def ${kebab(enumValue)} ${enumNumber})`)
  }
}
out.push('')

// function signatures as comments
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `;;; -- ${apiName.toUpperCase()} --`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    out.push(`;;; ${description}`)
    out.push(`;;; (${kebab(funcName)}${Object.keys(args).length ? ' ' + Object.keys(args).join(' ') : ''})${returns !== 'void' ? ` -> ${returns}` : ''}`)
  }
}

out.push('')

await mkdir('carts/wisp', { recursive: true })
await writeFile('carts/wisp/null0.wisp', out.join('\n'))
