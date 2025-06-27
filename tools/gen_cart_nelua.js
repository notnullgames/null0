#!/usr/bin/env node

// Generator for Nelua null0 API bindings
// Generates Nelua code from the API definitions

import { writeFile } from 'node:fs/promises'
import { createApiStream } from './utils.js'

const out = [
  `-- null0 API for Nelua
-- This file provides Nelua bindings for the null0 game engine API
-- Generated automatically - do not edit manually

## cinclude 'null0.h'

-- Import C types directly to avoid naming conflicts
global Color: type <cimport,nodecl> = @record{}
global Vector: type <cimport,nodecl> = @record{}
global Rectangle: type <cimport,nodecl> = @record{}
global Dimensions: type <cimport,nodecl> = @record{}
global Image: type <cimport,nodecl> = @uint32
global Font: type <cimport,nodecl> = @uint32
global Sound: type <cimport,nodecl> = @uint32
global ImageFilter: type <cimport,nodecl> = @cint
global Key: type <cimport,nodecl> = @cint
global GamepadButton: type <cimport,nodecl> = @cint
global MouseButton: type <cimport,nodecl> = @cint

-- Import C constants directly
global SCREEN: uint32 <cimport,nodecl>
global SCREEN_WIDTH: int32 <cimport,nodecl>
global SCREEN_HEIGHT: int32 <cimport,nodecl>
global FONT_DEFAULT: uint32 <cimport,nodecl>

-- Import color constants from C
global WHITE: Color <cimport,nodecl>
global BLACK: Color <cimport,nodecl>
global RED: Color <cimport,nodecl>
global GREEN: Color <cimport,nodecl>
global BLUE: Color <cimport,nodecl>
global YELLOW: Color <cimport,nodecl>
global LIGHTGRAY: Color <cimport,nodecl>
global GRAY: Color <cimport,nodecl>
global DARKGRAY: Color <cimport,nodecl>
global BLANK: Color <cimport,nodecl>

-- Import key constants
global KEY_INVALID: Key <cimport,nodecl>
global KEY_SPACE: Key <cimport,nodecl>
global KEY_A: Key <cimport,nodecl>
global KEY_B: Key <cimport,nodecl>
global KEY_C: Key <cimport,nodecl>
global KEY_D: Key <cimport,nodecl>
global KEY_E: Key <cimport,nodecl>
global KEY_F: Key <cimport,nodecl>
global KEY_G: Key <cimport,nodecl>
global KEY_H: Key <cimport,nodecl>
global KEY_I: Key <cimport,nodecl>
global KEY_J: Key <cimport,nodecl>
global KEY_K: Key <cimport,nodecl>
global KEY_L: Key <cimport,nodecl>
global KEY_M: Key <cimport,nodecl>
global KEY_N: Key <cimport,nodecl>
global KEY_O: Key <cimport,nodecl>
global KEY_P: Key <cimport,nodecl>
global KEY_Q: Key <cimport,nodecl>
global KEY_R: Key <cimport,nodecl>
global KEY_S: Key <cimport,nodecl>
global KEY_T: Key <cimport,nodecl>
global KEY_U: Key <cimport,nodecl>
global KEY_V: Key <cimport,nodecl>
global KEY_W: Key <cimport,nodecl>
global KEY_X: Key <cimport,nodecl>
global KEY_Y: Key <cimport,nodecl>
global KEY_Z: Key <cimport,nodecl>
global KEY_ESCAPE: Key <cimport,nodecl>
global KEY_ENTER: Key <cimport,nodecl>
global KEY_LEFT: Key <cimport,nodecl>
global KEY_RIGHT: Key <cimport,nodecl>
global KEY_UP: Key <cimport,nodecl>
global KEY_DOWN: Key <cimport,nodecl>`
]

// Type mapping from API types to Nelua types
const argTypes = {
  string: 'cstring',
  bool: 'boolean',
  i32: 'int32',
  f32: 'float32',
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
  'Vector[]': '*Vector'
}

const retTypes = {
  void: 'void',
  string: 'cstring',
  bool: 'boolean',
  i32: 'int32',
  f32: 'float32',
  u64: 'uint64',
  Image: 'uint32',
  Font: 'uint32',
  Sound: 'uint32',
  Vector: 'Vector',
  Dimensions: 'Dimensions',
  Color: 'Color',
  Rectangle: 'Rectangle'
}

// Generate parameter list for function signature
const argsMap = (args) => {
  const params = Object.entries(args).map(([name, type]) => {
    return `${name}: ${argTypes[type] || type}`
  })
  // Don't add extra numPoints - it's already in the API definition
  return params.join(', ')
}

const api = createApiStream()

api.on('api', (apiName) => {
  out.push('', `-- ${apiName.toUpperCase()}`, '')
})

api.on('function', ({ apiName, funcName, args = {}, returns = 'void', description = '' }) => {
  const neluaReturn = retTypes[returns] || returns
  const paramList = argsMap(args)

  // Generate external function declaration
  out.push(`-- ${description}`)
  out.push(`global function ${funcName}(${paramList}): ${neluaReturn} <cimport,nodecl> end`, '')
})

api.on('end', async () => {
  await writeFile('carts/nelua/null0.nelua', out.join('\n'))
  console.log('Generated Nelua API bindings: carts/nelua/null0.nelua')
})

api.on('error', (e) => {
  console.error('Error generating Nelua bindings:', e)
  process.exit(1)
})
