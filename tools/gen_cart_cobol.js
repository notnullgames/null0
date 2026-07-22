#!/usr/bin/env node

// Generator for COBOL null0 API bindings (GnuCOBOL/cobweb)
// Generates a COBOL copybook from the API definitions
//
// NOTE: experimental. COBOL carts call host functions with CALL:

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `      *> null0 - COBOL bindings for the null0 fantasy console
      *> (copybook - COPY null0 in WORKING-STORAGE SECTION.)
      *>
      *> Usage:
      *>
      *>     IDENTIFICATION DIVISION.
      *>     PROGRAM-ID. simple.
      *>     DATA DIVISION.
      *>     WORKING-STORAGE SECTION.
      *>     COPY null0.
      *>     PROCEDURE DIVISION.
      *>         CALL "clear" USING BY VALUE BLUE
      *>         CALL "draw_circle" USING BY VALUE 100 100 50 RED
      *>         STOP RUN.
      *>
      *> ABI notes:
      *> - handles (Image/Font/Sound), enums and bools are PIC 9(9) COMP-5
      *> - Color is 4 bytes packed: r | g<<8 | b<<16 | a<<24
      *> - strings are null-terminated (use Z"..." literals)
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// constants
// NOTE: SCREEN and BLANK are reserved words in GnuCOBOL, so they get a NULL0- prefix
out.push('', '      *> constants')
out.push('       78 NULL0-SCREEN     VALUE 0.')
out.push('       78 SCREEN-WIDTH     VALUE 640.')
out.push('       78 SCREEN-HEIGHT    VALUE 480.')
out.push('       78 FONT-DEFAULT     VALUE 0.')

// color constants
// NOTE: colors are 01-level items (not 78) because GnuCOBOL rejects
// literals > 2^31-1 in BY VALUE, and 78s act as literals there
out.push('', '      *> colors (packed r | g<<8 | b<<16 | a<<24)')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    // BLANK is a reserved word in GnuCOBOL
    const safeName = colorName === 'BLANK' ? 'NULL0-BLANK' : colorName
    out.push(`       01  ${safeName.padEnd(14)}PIC 9(10) COMP-5 VALUE ${packed}. *> rgba(${r}, ${g}, ${b}, ${a})`)
  }
}
out.push('')

// enum constants
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `      *> ${enumName}: ${enumDef.description}`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`       78 ${enumValue.replace(/_/g, '-').padEnd(30)}VALUE ${enumNumber}.`)
  }
}
out.push('')

// struct layouts as comments
const sizes = { i32: 4, f32: 4, u32: 4, u8: 1 }
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `      *> struct ${structName}: ${structDef.description}`)
  let offset = 0
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`      *>   offset ${offset}: ${memberName} (${memberType})`)
    offset += sizes[memberType] || 4
  }
}
out.push('')

// function signatures as comments
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `      *> -- ${apiName.toUpperCase()} --`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const argList = Object.keys(args).map((a) => a.toUpperCase().replace(/([A-Z])/g, '-$1').replace(/^-/, '')).join(' ')
    out.push(`      *> ${description}`)
    out.push(`      *>   CALL "${funcName}"${argList ? ` USING BY VALUE ${argList}` : ''}${returns !== 'void' ? ' RETURNING RESULT' : ''}`)
  }
}

out.push('')

await mkdir('carts/cobol', { recursive: true })
await writeFile('carts/cobol/null0.cpy', out.join('\n'))

// C shim: GnuCOBOL -static CALLs link against these int-returning wrappers,
// which forward to the real null0 host-imports with the exact ABI signatures.
//
// import signature types (must match the host registration exactly)
const impTypes = {
  void: 'void',
  i32: 'int32_t',
  u32: 'uint32_t',
  f32: 'float',
  u64: 'uint64_t',
  bool: 'int32_t',
  string: 'uint32_t',
  Color: 'uint32_t',
  Image: 'uint32_t',
  Font: 'uint32_t',
  Sound: 'uint32_t',
  Vector: 'uint32_t',
  Rectangle: 'uint32_t',
  Dimensions: 'uint32_t',
  SfxParams: 'uint32_t',
  'Vector[]': 'uint32_t',
  ImageFilter: 'int32_t',
  Key: 'int32_t',
  GamepadButton: 'int32_t',
  MouseButton: 'int32_t',
  SfxPresetType: 'int32_t'
}

// wrapper types (K&R-compatible with the `extern int name ();` that cobc generates)
const wrapTypes = {
  i32: 'int',
  u32: 'int',
  bool: 'int',
  Color: 'int',
  Image: 'int',
  Font: 'int',
  Sound: 'int',
  ImageFilter: 'int',
  Key: 'int',
  GamepadButton: 'int',
  MouseButton: 'int',
  SfxPresetType: 'int',
  f32: 'float',
  u64: 'uint64_t',
  string: 'char*',
  Vector: 'void*',
  Rectangle: 'void*',
  Dimensions: 'void*',
  SfxParams: 'void*',
  'Vector[]': 'void*'
}

const castArg = (name, type) => {
  const imp = impTypes[type]
  const wrap = wrapTypes[type]
  if (imp === wrap || (imp === 'int32_t' && wrap === 'int') || (imp === 'uint32_t' && wrap === 'int') || imp === 'float') {
    return name
  }
  if (wrap === 'char*' || wrap === 'void*') {
    return `(uint32_t)(uintptr_t)${name}`
  }
  return `(${imp})${name}`
}

const shim = [
  `// null0 - COBOL shim (generated by gen_cart_cobol.js)
// cobc -static generates direct C calls to int-returning functions;
// these wrappers forward them to the real null0 host-imports.
//
// Limitations:
// - f32 returns (delta_time) come back as raw int32 bits
// - u64 returns (current_time, random_seed_get) are truncated to int32
#include <stdint.h>
`
]

for (const [apiName, funcDef] of Object.entries(api)) {
  shim.push('', `// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns }] of Object.entries(funcDef)) {
    const impRet = impTypes[returns] || 'int32_t'
    const impArgs = Object.entries(args).map(([n, t]) => `${impTypes[t] || 'int32_t'} ${n}`).join(', ')
    const wrapArgs = Object.entries(args).map(([n, t]) => `${wrapTypes[t] || 'int'} ${n}`).join(', ')
    const callArgs = Object.entries(args).map(([n, t]) => castArg(n, t)).join(', ')
    shim.push(`__attribute__((import_module("null0"), import_name("${funcName}")))`)
    shim.push(`extern ${impRet} n0_${funcName}(${impArgs});`)
    if (returns === 'void') {
      shim.push(`int ${funcName}(${wrapArgs}) { n0_${funcName}(${callArgs}); return 0; }`, '')
    } else if (returns === 'f32') {
      shim.push(`int ${funcName}(${wrapArgs}) { union { float f; int i; } u; u.f = n0_${funcName}(${callArgs}); return u.i; }`, '')
    } else {
      shim.push(`int ${funcName}(${wrapArgs}) { return (int)n0_${funcName}(${callArgs}); }`, '')
    }
  }
}

await writeFile('carts/cobol/null0_cobol_shim.c', shim.join('\n'))
