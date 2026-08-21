#!/usr/bin/env node

// Generator for Haskell null0 API bindings.
//
// This writes 2 files:
//
// - carts/haskell/Null0.hs           the library module carts `import Null0`
// - tools/docker/haskell-cart/imports.c   custom-wasm-import C trampoline
//
// GHC's FFI cannot marshal a C struct passed/returned *by value*, so every
// null0 function that touches a struct gets a tiny C wrapper (imports.c)
// that turns the by-value null0 ABI into a pointer-only ABI Haskell can
// import directly. Everything else (scalars, strings, arrays) is already
// pointer/scalar at the wasm boundary and gets a 1:1 passthrough wrapper,
// generated the same way for consistency.
//
// A wasm import's host module name ("null0") can only be set from C
// (`__attribute__((import_module(...), import_name(...)))`), so every
// function is imported into Haskell through this C layer - see the
// "Custom imports" section of https://github.com/haskell-wasm/ghc-wasm-meta.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

const toFuncName = (funcName) => funcName.replace(/_([a-z0-9])/g, (_, c) => c.toUpperCase())

// constants/enums (KEY_DOWN, GAMEPAD_BUTTON_DOWN, ...) camelCase into the
// same names as some query functions (key_down, gamepad_button_down, ...) -
// track every function name up front so those can be disambiguated
const usedNames = new Set()
for (const apiObj of Object.values(api)) {
  for (const funcName of Object.keys(apiObj)) {
    usedNames.add(toFuncName(funcName))
  }
}

const structNames = Object.keys(structs)

// ---- C side: type of a null0 arg, as null0.h itself declares it (structs by value) ----
const cRawArgType = {
  string: 'char*',
  bool: 'bool',
  i32: 'int32_t',
  f32: 'float',
  u32: 'uint32_t',
  u64: 'uint64_t',
  Image: 'uint32_t',
  Font: 'uint32_t',
  Sound: 'uint32_t',
  Tilemap: 'uint32_t',
  ImageFilter: 'int32_t',
  Key: 'int32_t',
  GamepadButton: 'int32_t',
  MouseButton: 'int32_t',
  SfxPresetType: 'int32_t',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}

// C type of the value the host hands back (structs come back as pointers into cart-memory)
const cRetType = {
  void: 'void',
  string: 'char*',
  bool: 'bool',
  i32: 'int32_t',
  f32: 'float',
  u32: 'uint32_t',
  u64: 'uint64_t',
  Image: 'uint32_t',
  Font: 'uint32_t',
  Sound: 'uint32_t',
  Tilemap: 'uint32_t',
  Color: 'Color*',
  Vector: 'Vector*',
  Dimensions: 'Dimensions*',
  Rectangle: 'Rectangle*',
  SfxParams: 'SfxParams*'
}

// C type of a wrapper-exposed (Haskell-facing) arg: structs become pointers
const cWrapArgType = { ...cRawArgType, Color: 'Color*', Rectangle: 'Rectangle*', SfxParams: 'SfxParams*' }

// ---- Haskell side ----

// raw FFI-safe type for an arg, at the Haskell <-> C-wrapper boundary
const hsFfiArgType = {
  string: 'CString',
  bool: 'CBool',
  i32: 'Int32',
  f32: 'CFloat',
  u32: 'Word32',
  u64: 'Word64',
  Image: 'Word32',
  Font: 'Word32',
  Sound: 'Word32',
  Tilemap: 'Word32',
  ImageFilter: 'Int32',
  Key: 'Int32',
  GamepadButton: 'Int32',
  MouseButton: 'Int32',
  SfxPresetType: 'Int32',
  Color: 'Ptr Color',
  Rectangle: 'Ptr Rectangle',
  SfxParams: 'Ptr SfxParams'
}

// raw FFI-safe return type
const hsFfiRetType = {
  void: 'IO ()',
  string: 'IO CString',
  bool: 'IO CBool',
  i32: 'IO Int32',
  f32: 'IO CFloat',
  u32: 'IO Word32',
  u64: 'IO Word64',
  Image: 'IO Word32',
  Font: 'IO Word32',
  Sound: 'IO Word32',
  Tilemap: 'IO Word32',
  Color: 'IO (Ptr Color)',
  Vector: 'IO (Ptr Vector)',
  Dimensions: 'IO (Ptr Dimensions)',
  Rectangle: 'IO (Ptr Rectangle)',
  SfxParams: 'IO (Ptr SfxParams)'
}

// idiomatic (exported wrapper) type of an arg
const hsIdiomaticArgType = {
  string: 'String',
  bool: 'Bool',
  i32: 'Int32',
  f32: 'CFloat',
  u32: 'Word32',
  u64: 'Word64',
  Image: 'Word32',
  Font: 'Word32',
  Sound: 'Word32',
  Tilemap: 'Word32',
  ImageFilter: 'Int32',
  Key: 'Int32',
  GamepadButton: 'Int32',
  MouseButton: 'Int32',
  SfxPresetType: 'Int32',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}

// idiomatic return type (unwrapped, without IO)
const hsIdiomaticRetType = { ...hsIdiomaticArgType, void: '()', Vector: 'Vector', Dimensions: 'Dimensions' }

// C type for a struct member
const memberCType = { i32: 'int32_t', f32: 'float', u32: 'uint32_t', u8: 'uint8_t' }

// Haskell Storable type + peek/poke accessor for a struct member
const memberHsType = { i32: 'Int32', f32: 'CFloat', u32: 'Word32', u8: 'Word8' }

// work out how a function's args look on both sides of the boundary
// Haskell reserved words that show up as null0 arg names
const hsKeywords = new Set(['type', 'class', 'data', 'let', 'in', 'where', 'do', 'case', 'of', 'if', 'then', 'else', 'import', 'module', 'instance', 'deriving', 'newtype'])
const escapeArg = (name) => (hsKeywords.has(name) ? `${name}_` : name)

function plan(rawArgs) {
  const entries = Object.entries(rawArgs).map(([name, type]) => [escapeArg(name), type])
  const idiomaticParams = [] // [name, hsType]
  const marshal = [] // lines that open a `with`/`withCString`/`withArrayLen` scope (CPS)
  const rawArgVars = [] // variable names passed to the raw ffi call, in order
  const rawFfiTypes = [] // types for the raw ffi import signature
  const cRawParams = [] // C: inner extern's param decls
  const cWrapParams = [] // C: public wrapper's param decls
  const cCallArgs = [] // C: args passed from wrapper to inner extern

  for (let i = 0; i < entries.length; i++) {
    const [name, type] = entries[i]

    if (type === 'Vector[]' || type === 'i32[]') {
      const elemHs = type === 'Vector[]' ? 'Vector' : 'Int32'
      const elemC = type === 'Vector[]' ? 'Vector' : 'int32_t'
      idiomaticParams.push([name, `[${elemHs}]`])
      marshal.push(`withArrayLen ${name} $ \\${name}_count ${name}_ptr ->`)
      rawArgVars.push(`${name}_ptr`, `(fromIntegral ${name}_count)`)
      rawFfiTypes.push(`Ptr ${elemHs}`, 'Word32')
      cRawParams.push(`${elemC}* ${name}`, `uint32_t ${name}_count`)
      cWrapParams.push(`${elemC}* ${name}`, `uint32_t ${name}_count`)
      cCallArgs.push(name, `${name}_count`)
      // the yml lists the array's count as its own following arg (eg.
      // `numPoints: i32`) - it is implicit from withArrayLen, so skip it
      i++
      continue
    }

    idiomaticParams.push([name, hsIdiomaticArgType[type]])
    rawFfiTypes.push(hsFfiArgType[type])

    if (type === 'string') {
      marshal.push(`withCString ${name} $ \\${name}_c ->`)
      rawArgVars.push(`${name}_c`)
      cRawParams.push(`char* ${name}`)
      cWrapParams.push(`char* ${name}`)
      cCallArgs.push(name)
    } else if (type === 'bool') {
      rawArgVars.push(`(fromBool ${name})`)
      cRawParams.push(`bool ${name}`)
      cWrapParams.push(`bool ${name}`)
      cCallArgs.push(name)
    } else if (structNames.includes(type)) {
      marshal.push(`with ${name} $ \\${name}_p ->`)
      rawArgVars.push(`${name}_p`)
      cRawParams.push(`${type} ${name}`)
      cWrapParams.push(`${type}* ${name}`)
      cCallArgs.push(`*${name}`)
    } else {
      rawArgVars.push(name)
      cRawParams.push(`${cRawArgType[type]} ${name}`)
      cWrapParams.push(`${cRawArgType[type]} ${name}`)
      cCallArgs.push(name)
    }
  }

  return { idiomaticParams, marshal, rawArgVars, rawFfiTypes, cRawParams, cWrapParams, cCallArgs }
}

// ==================================================================
// carts/haskell/Null0.hs
// ==================================================================

const hs = [
  '-- null0 - Haskell bindings for the null0 fantasy console',
  '--',
  '-- GENERATED FILE - do not edit by hand. See tools/gen_cart_haskell.js',
  '--',
  '-- Usage:',
  '--',
  '-- > import Null0',
  '-- >',
  '-- > update :: IO ()',
  '-- > update = clear blue',
  '',
  '{-# LANGUAGE ForeignFunctionInterface #-}',
  'module Null0 where',
  '',
  'import Foreign',
  'import Foreign.C.String',
  'import Foreign.C.Types',
  'import Data.Int',
  'import Data.Word',
  ''
]

// ---- structs ----

for (const structName of structNames) {
  const members = Object.entries(structs[structName].members)
  hs.push(`-- | ${structs[structName].description}`)
  hs.push(`data ${structName} = ${structName}`)
  members.forEach(([name, type], i) => {
    hs.push(`  ${i === 0 ? '{ ' : ', '}${structName.toLowerCase()}_${name} :: ${memberHsType[type]}`)
  })
  hs.push('  } deriving (Show, Eq)')
  hs.push('')

  let offset = 0
  const offsets = members.map(([name, type]) => {
    const o = offset
    offset += type === 'u8' ? 1 : 4
    return o
  })

  hs.push(`instance Storable ${structName} where`)
  hs.push(`  sizeOf _ = ${offset}`)
  hs.push('  alignment _ = 4')
  hs.push(
    `  peek p = ${structName} <$> ${members.map(([name, type], i) => `(peekByteOff p ${offsets[i]} :: IO ${memberHsType[type]})`).join(' <*> ')}`
  )
  hs.push(
    `  poke p (${structName} ${members.map(([name]) => `f_${name}`).join(' ')}) = ${members
      .map(([name, type], i) => `pokeByteOff p ${offsets[i]} f_${name}`)
      .join(' >> ')}`
  )
  hs.push('')
}

// ---- constants ----

hs.push('-- | The screen is image 0', 'screen :: Word32', 'screen = 0', '')
hs.push('screenWidth :: Int32', 'screenWidth = 640', '')
hs.push('screenHeight :: Int32', 'screenHeight = 480', '')
hs.push('-- | The built-in font', 'fontDefault :: Word32', 'fontDefault = 0', '')

// ALL_CAPS or ALL_CAPS_WITH_UNDERSCORES -> camelCase
const toCamel = (name) =>
  name
    .toLowerCase()
    .split('_')
    .map((word, i) => (i === 0 ? word : word.charAt(0).toUpperCase() + word.slice(1)))
    .join('')

// a constant/enum name that collides with a function name (eg. KEY_DOWN vs.
// key_down) gets a trailing ' - a normal Haskell disambiguation idiom
const uniqueName = (name) => {
  let hsName = toCamel(name)
  while (usedNames.has(hsName)) hsName += "'"
  usedNames.add(hsName)
  return hsName
}

for (const [name, def] of Object.entries(constants)) {
  const hsName = uniqueName(name)
  if (def.type === 'Color') {
    const [r, g, b, a] = def.value
    hs.push(`${hsName} :: Color`)
    hs.push(`${hsName} = Color ${r} ${g} ${b} ${a}`)
    hs.push('')
  } else if (def.type === 'string') {
    hs.push(`-- | ${def.description}`)
    hs.push(`${hsName} :: String`)
    hs.push(`${hsName} = ${JSON.stringify(def.value)}`)
    hs.push('')
  }
}

for (const [enumName, enumDef] of Object.entries(enums)) {
  hs.push(`-- ${enumDef.description}`)
  for (const [entryName, entryValue] of Object.entries(enumDef.enums)) {
    const hsName = uniqueName(entryName)
    hs.push(`${hsName} :: Int32`)
    hs.push(`${hsName} = ${entryValue}`)
    hs.push('')
  }
}

// ---- C trampoline (imports.c) ----

const c = [
  '// GENERATED FILE - do not edit by hand. See tools/gen_cart_haskell.js',
  '//',
  '// Custom-wasm-import trampoline: GHC\'s FFI cannot marshal a C struct by',
  '// value, so every null0 function is re-exposed here with structs as',
  '// pointers. The private `_name` extern carries the real import (module',
  '// "null0", the exact by-value ABI null0.h itself uses); the public `name`',
  '// wraps it with a pointer-only signature Haskell can import directly.',
  '',
  '#include <stdint.h>',
  '#include <stdbool.h>',
  '',
  '#define NULL0_IMPORT(n) __attribute__((import_module("null0"), import_name(n)))',
  ''
]

for (const structName of structNames) {
  const members = Object.entries(structs[structName].members)
  c.push(`typedef struct {`)
  for (const [name, type] of members) {
    c.push(`  ${memberCType[type]} ${name};`)
  }
  c.push(`} ${structName};`, '')
}

// ---- functions: both sides ----

for (const [apiName, apiObj] of Object.entries(api)) {
  hs.push(`-- ${apiName.toUpperCase()}`, '')
  c.push('', `// ${apiName.toUpperCase()}`, '')

  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const { idiomaticParams, marshal, rawArgVars, rawFfiTypes, cRawParams, cWrapParams, cCallArgs } = plan(args)

    const isStructRet = ['Color', 'Vector', 'Dimensions', 'Rectangle', 'SfxParams'].includes(returns)

    // -- C side --
    const rawRetC = cRetType[returns]
    c.push(`NULL0_IMPORT("${funcName}")`)
    c.push(`extern ${rawRetC} _${funcName}(${cRawParams.length ? cRawParams.join(', ') : 'void'});`)
    const wrapRetC = isStructRet ? rawRetC : cRetType[returns]
    c.push(`${wrapRetC} ${funcName}(${cWrapParams.length ? cWrapParams.join(', ') : 'void'}) {`)
    if (returns === 'void') {
      c.push(`  _${funcName}(${cCallArgs.join(', ')});`)
    } else {
      c.push(`  return _${funcName}(${cCallArgs.join(', ')});`)
    }
    c.push('}', '')

    // -- Haskell raw FFI import --
    const hsFuncName = toFuncName(funcName)
    const rawSig = rawFfiTypes.length ? `${rawFfiTypes.join(' -> ')} -> ${hsFfiRetType[returns]}` : hsFfiRetType[returns]
    hs.push(`foreign import ccall unsafe "${funcName}" c_${hsFuncName} :: ${rawSig}`)

    // -- Haskell idiomatic wrapper --
    const idiomaticSig = idiomaticParams.length
      ? `${idiomaticParams.map(([, t]) => t).join(' -> ')} -> IO ${hsIdiomaticRetType[returns]}`
      : `IO ${hsIdiomaticRetType[returns]}`
    hs.push(`-- | ${description}`)
    hs.push(`${hsFuncName} :: ${idiomaticSig}`)
    const paramNames = idiomaticParams.map(([n]) => n)
    const callExpr = `c_${hsFuncName} ${rawArgVars.join(' ')}`.trim()

    let body
    if (returns === 'void') {
      body = marshal.length ? callExpr : callExpr
    } else if (returns === 'string') {
      body = `${callExpr} >>= peekCString`
    } else if (isStructRet) {
      body = `${callExpr} >>= peek`
    } else if (returns === 'bool') {
      body = `toBool <$> ${callExpr}`
    } else {
      body = callExpr
    }

    if (marshal.length) {
      hs.push(`${hsFuncName} ${paramNames.join(' ')} =`)
      marshal.forEach((line) => hs.push(`  ${line}`))
      hs.push(`    ${body}`)
    } else {
      hs.push(`${hsFuncName}${paramNames.length ? ' ' + paramNames.join(' ') : ''} = ${body}`)
    }
    hs.push('')
  }
}

hs.push('')

c.push(
  '',
  '// RTS startup: null0 calls _initialize (this wasm module is built as a',
  '// WASI reactor) once, before any other export - hook it to bring up the',
  '// Haskell RTS, since -no-hs-main means nothing else will.',
  '#include <HsFFI.h>',
  '',
  '__attribute__((constructor))',
  'static void null0_hs_init(void) {',
  '  int argc = 0;',
  '  hs_init(&argc, 0);',
  '}'
)

await mkdir('carts/haskell', { recursive: true })
await mkdir('tools/docker/haskell-cart', { recursive: true })
await writeFile('carts/haskell/Null0.hs', hs.join('\n'))
await writeFile('tools/docker/haskell-cart/imports.c', c.join('\n'))
