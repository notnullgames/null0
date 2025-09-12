#!/usr/bin/env node

// Generator for Nim null0 API bindings
// Generates Nim code from the API definitions

import { writeFile } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `import macros

# pragma macros for exporting/importing functions

macro wasm*(t: typed): untyped =
  ## Macro equivalent to NULL0_EXPORT - exports procedure with clang attributes
  if t.kind notin {nnkProcDef, nnkFuncDef}:
    error("Can only export procedures", t)

  let
    newProc = copyNimTree(t)
    procName = $t.name
    exportcPragma = nnkExprColonExpr.newTree(ident"exportc", newLit(procName))
    cdeclPragma = ident"cdecl"
    codeGenPragma = nnkExprColonExpr.newTree(
      ident"codegenDecl",
      newLit("__attribute__((export_name(\\"" & procName & "\\"))) $# $#$#")
    )

  # Add pragmas to the procedure
  if newProc[4].kind == nnkEmpty:
    newProc[4] = nnkPragma.newTree(exportcPragma, cdeclPragma, codeGenPragma)
  else:
    newProc[4].add exportcPragma
    newProc[4].add cdeclPragma
    newProc[4].add codeGenPragma

  result = newProc

macro null0_import*(t: typed): untyped =
  ## Macro equivalent to NULL0_IMPORT - imports procedure with clang attributes
  if t.kind notin {nnkProcDef, nnkFuncDef}:
    error("Can only import procedures", t)

  let
    newProc = copyNimTree(t)
    procName = $t.name
    importcPragma = nnkExprColonExpr.newTree(ident"importc", newLit(procName))
    cdeclPragma = ident"cdecl"
    codeGenPragma = nnkExprColonExpr.newTree(
      ident"codegenDecl",
      newLit("__attribute__((import_module(\\"null0\\"), import_name(\\"" &
          procName & "\\"))) $# $#$#")
    )

  # Add pragmas to the procedure
  if newProc[4].kind == nnkEmpty:
    newProc[4] = nnkPragma.newTree(importcPragma, cdeclPragma, codeGenPragma)
  else:
    newProc[4].add importcPragma
    newProc[4].add cdeclPragma
    newProc[4].add codeGenPragma

  result = newProc

type`
]

// Type mapping from API types to Nim types
const argTypes = {
  string: 'cstring',
  bool: 'bool',
  i32: 'cint',
  f32: 'cfloat',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'uint32',
  Font: 'uint32',
  Sound: 'uint32',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': 'ptr Vector',
  SfxParams: 'SfxParams',
  SfxPresetType: 'SfxPresetType'
}

const retTypes = {
  void: null, // void functions have no return type
  string: 'cstring',
  bool: 'bool',
  i32: 'cint',
  f32: 'cfloat',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'uint32',
  Font: 'uint32',
  Sound: 'uint32',
  Vector: 'Vector',
  Dimensions: 'Dimensions',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}

// Type mapping for struct member types
const memberTypes = {
  i32: 'cint',
  f32: 'cfloat',
  u32: 'uint32',
  u8: 'uint8'
}

// Reserved keywords in Nim that need to be escaped
const nimReservedKeywords = new Set(['type', 'var', 'let', 'const', 'proc', 'func', 'method', 'template', 'macro', 'if', 'elif', 'else', 'when', 'case', 'of', 'for', 'while', 'break', 'continue', 'return', 'yield', 'try', 'except', 'finally', 'raise', 'defer', 'import', 'include', 'from', 'export', 'as', 'object', 'tuple', 'enum', 'concept', 'distinct', 'array', 'seq', 'set', 'string', 'cstring', 'char', 'bool', 'int', 'int8', 'int16', 'int32', 'int64', 'uint', 'uint8', 'uint16', 'uint32', 'uint64', 'float', 'float32', 'float64', 'range', 'ptr', 'ref', 'nil', 'true', 'false'])

// Generate parameter list for function signature
const argsMap = (args) => {
  const params = Object.entries(args).map(([name, type]) => {
    // Escape reserved keywords by adding backticks
    const paramName = nimReservedKeywords.has(name) ? `\`${name}\`` : name
    return `${paramName}: ${argTypes[type] || type}`
  })
  return params.join(', ')
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  out.push(`  ${structName}* {.byref, packed.} = object`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberName}*: ${memberTypes[memberType] || memberType}`)
  }
  out.push('')
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push(`  ${enumName}* = enum`)
  const enumEntries = Object.entries(enumDef.enums)
  for (let i = 0; i < enumEntries.length; i++) {
    const [enumValue, enumNumber] = enumEntries[i]
    const isLast = i === enumEntries.length - 1
    out.push(`    ${enumValue} = ${enumNumber}${isLast ? '' : ','}`)
  }
  out.push('')
}

out.push(`# Import functions from null0 module with proper C attributes
`)

// Generate function declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push(`# ${apiName.charAt(0).toUpperCase() + apiName.slice(1)} functions`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const nimReturn = retTypes[returns]
    const paramList = argsMap(args)
    const returnType = nimReturn && nimReturn !== null ? `: ${nimReturn}` : ''

    // Generate function declaration
    out.push(`proc ${funcName}*(${paramList})${returnType} {.null0_import.}`)
  }
  out.push('')
}

// Add the main function and constants
out.push(`# this removes errors about nop main
proc main*(argc: cint, argv: ptr cstring): cint {.wasm.} =
  return 0

const
  SCREEN* = 0
  SCREEN_WIDTH* = 640
  SCREEN_HEIGHT* = 480
  FONT_DEFAULT* = 0
`)

// Generate color constants
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`  ${colorName}* = Color(r: ${r}, g: ${g}, b: ${b}, a: ${a})`)
  }
}

out.push('')

await writeFile('carts/nim/null0.nim', out.join('\n'))
