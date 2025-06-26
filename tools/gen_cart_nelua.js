#!/usr/bin/env node

// Generator for Nelua null0 API bindings
// Generates Nelua code from the API definitions

import { writeFile } from 'node:fs/promises'
import { indent, createApiStream } from './utils.js'

const out = [
  `-- null0 API for Nelua
-- This file provides Nelua bindings for the null0 game engine API
-- Generated automatically - do not edit manually

-- Type definitions
global Color: type = @record{
  r: uint8,
  g: uint8,
  b: uint8,
  a: uint8
}

global Vector: type = @record{
  x: int32,
  y: int32
}

global Rectangle: type = @record{
  x: int32,
  y: int32,
  width: int32,
  height: int32
}

global Dimensions: type = @record{
  width: uint32,
  height: uint32
}

-- Enum definitions
global ImageFilter: type = @enum{
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR,
  FILTER_SMOOTH
}

global Key: type = @enum{
  KEY_INVALID = 0,
  KEY_SPACE = 32,
  KEY_APOSTROPHE = 39,
  KEY_COMMA = 44,
  KEY_MINUS = 45,
  KEY_PERIOD = 46,
  KEY_SLASH = 47,
  KEY_0 = 48,
  KEY_1 = 49,
  KEY_2 = 50,
  KEY_3 = 51,
  KEY_4 = 52,
  KEY_5 = 53,
  KEY_6 = 54,
  KEY_7 = 55,
  KEY_8 = 56,
  KEY_9 = 57,
  KEY_SEMICOLON = 59,
  KEY_EQUAL = 61,
  KEY_A = 65,
  KEY_B = 66,
  KEY_C = 67,
  KEY_D = 68,
  KEY_E = 69,
  KEY_F = 70,
  KEY_G = 71,
  KEY_H = 72,
  KEY_I = 73,
  KEY_J = 74,
  KEY_K = 75,
  KEY_L = 76,
  KEY_M = 77,
  KEY_N = 78,
  KEY_O = 79,
  KEY_P = 80,
  KEY_Q = 81,
  KEY_R = 82,
  KEY_S = 83,
  KEY_T = 84,
  KEY_U = 85,
  KEY_V = 86,
  KEY_W = 87,
  KEY_X = 88,
  KEY_Y = 89,
  KEY_Z = 90,
  KEY_LEFT_BRACKET = 91,
  KEY_BACKSLASH = 92,
  KEY_RIGHT_BRACKET = 93,
  KEY_GRAVE_ACCENT = 96,
  KEY_WORLD_1 = 161,
  KEY_WORLD_2 = 162,
  KEY_ESCAPE = 256,
  KEY_ENTER = 257,
  KEY_TAB = 258,
  KEY_BACKSPACE = 259,
  KEY_INSERT = 260,
  KEY_DELETE = 261,
  KEY_RIGHT = 262,
  KEY_LEFT = 263,
  KEY_DOWN = 264,
  KEY_UP = 265,
  KEY_PAGE_UP = 266,
  KEY_PAGE_DOWN = 267,
  KEY_HOME = 268,
  KEY_END = 269,
  KEY_CAPS_LOCK = 280,
  KEY_SCROLL_LOCK = 281,
  KEY_NUM_LOCK = 282,
  KEY_PRINT_SCREEN = 283,
  KEY_PAUSE = 284,
  KEY_F1 = 290,
  KEY_F2 = 291,
  KEY_F3 = 292,
  KEY_F4 = 293,
  KEY_F5 = 294,
  KEY_F6 = 295,
  KEY_F7 = 296,
  KEY_F8 = 297,
  KEY_F9 = 298,
  KEY_F10 = 299,
  KEY_F11 = 300,
  KEY_F12 = 301,
  KEY_F13 = 302,
  KEY_F14 = 303,
  KEY_F15 = 304,
  KEY_F16 = 305,
  KEY_F17 = 306,
  KEY_F18 = 307,
  KEY_F19 = 308,
  KEY_F20 = 309,
  KEY_F21 = 310,
  KEY_F22 = 311,
  KEY_F23 = 312,
  KEY_F24 = 313,
  KEY_F25 = 314,
  KEY_KP_0 = 320,
  KEY_KP_1 = 321,
  KEY_KP_2 = 322,
  KEY_KP_3 = 323,
  KEY_KP_4 = 324,
  KEY_KP_5 = 325,
  KEY_KP_6 = 326,
  KEY_KP_7 = 327,
  KEY_KP_8 = 328,
  KEY_KP_9 = 329,
  KEY_KP_DECIMAL = 330,
  KEY_KP_DIVIDE = 331,
  KEY_KP_MULTIPLY = 332,
  KEY_KP_SUBTRACT = 333,
  KEY_KP_ADD = 334,
  KEY_KP_ENTER = 335,
  KEY_KP_EQUAL = 336,
  KEY_LEFT_SHIFT = 340,
  KEY_LEFT_CONTROL = 341,
  KEY_LEFT_ALT = 342,
  KEY_LEFT_SUPER = 343,
  KEY_RIGHT_SHIFT = 344,
  KEY_RIGHT_CONTROL = 345,
  KEY_RIGHT_ALT = 346,
  KEY_RIGHT_SUPER = 347,
  KEY_MENU = 348
}

global GamepadButton: type = @enum{
  GAMEPAD_BUTTON_UNKNOWN = 0,
  GAMEPAD_BUTTON_UP = 1,
  GAMEPAD_BUTTON_RIGHT,
  GAMEPAD_BUTTON_DOWN,
  GAMEPAD_BUTTON_LEFT,
  GAMEPAD_BUTTON_Y,
  GAMEPAD_BUTTON_B,
  GAMEPAD_BUTTON_A,
  GAMEPAD_BUTTON_X,
  GAMEPAD_BUTTON_LEFT_SHOULDER,
  GAMEPAD_BUTTON_LEFT_TRIGGER,
  GAMEPAD_BUTTON_RIGHT_SHOULDER,
  GAMEPAD_BUTTON_RIGHT_TRIGGER,
  GAMEPAD_BUTTON_SELECT,
  GAMEPAD_BUTTON_MENU,
  GAMEPAD_BUTTON_START,
  GAMEPAD_BUTTON_LEFT_THUMB,
  GAMEPAD_BUTTON_RIGHT_THUMB
}

global MouseButton: type = @enum{
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3
}

-- Constants
global SCREEN: integer <comptime> = 0
global SCREEN_WIDTH: integer <comptime> = 640
global SCREEN_HEIGHT: integer <comptime> = 480
global FONT_DEFAULT: integer <comptime> = 0

-- Color constants
global LIGHTGRAY: Color <comptime> = {r = 200, g = 200, b = 200, a = 255}
global GRAY: Color <comptime> = {r = 130, g = 130, b = 130, a = 255}
global DARKGRAY: Color <comptime> = {r = 80, g = 80, b = 80, a = 255}
global YELLOW: Color <comptime> = {r = 253, g = 249, b = 0, a = 255}
global GOLD: Color <comptime> = {r = 255, g = 203, b = 0, a = 255}
global ORANGE: Color <comptime> = {r = 255, g = 161, b = 0, a = 255}
global PINK: Color <comptime> = {r = 255, g = 109, b = 194, a = 255}
global RED: Color <comptime> = {r = 230, g = 41, b = 55, a = 255}
global MAROON: Color <comptime> = {r = 190, g = 33, b = 55, a = 255}
global GREEN: Color <comptime> = {r = 0, g = 228, b = 48, a = 255}
global LIME: Color <comptime> = {r = 0, g = 158, b = 47, a = 255}
global DARKGREEN: Color <comptime> = {r = 0, g = 117, b = 44, a = 255}
global SKYBLUE: Color <comptime> = {r = 102, g = 191, b = 255, a = 255}
global BLUE: Color <comptime> = {r = 0, g = 121, b = 241, a = 255}
global DARKBLUE: Color <comptime> = {r = 0, g = 82, b = 172, a = 255}
global PURPLE: Color <comptime> = {r = 200, g = 122, b = 255, a = 255}
global VIOLET: Color <comptime> = {r = 135, g = 60, b = 190, a = 255}
global DARKPURPLE: Color <comptime> = {r = 112, g = 31, b = 126, a = 255}
global BEIGE: Color <comptime> = {r = 211, g = 176, b = 131, a = 255}
global BROWN: Color <comptime> = {r = 127, g = 106, b = 79, a = 255}
global DARKBROWN: Color <comptime> = {r = 76, g = 63, b = 47, a = 255}
global WHITE: Color <comptime> = {r = 255, g = 255, b = 255, a = 255}
global BLACK: Color <comptime> = {r = 0, g = 0, b = 0, a = 255}
global BLANK: Color <comptime> = {r = 0, g = 0, b = 0, a = 0}
global MAGENTA: Color <comptime> = {r = 255, g = 0, b = 255, a = 255}
global RAYWHITE: Color <comptime> = {r = 245, g = 245, b = 245, a = 255}

-- Math functions
global math: type = @record{}
global function math.sin(x: number): number <cimport 'sin', nodecl, cinclude '<math.h>'> end
global function math.cos(x: number): number <cimport 'cos', nodecl, cinclude '<math.h>'> end
global function math.sqrt(x: number): number <cimport 'sqrt', nodecl, cinclude '<math.h>'> end
global function math.pi(): number <comptime>
  return 3.14159265358979323846
end

-- Type aliases for resources
global Image: type = @uint32
global Font: type = @uint32  
global Sound: type = @uint32`
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
  Vector: '*Vector',
  Dimensions: '*Dimensions',
  Color: '*Color'
}

// Types that are returned as pointers and need dereferencing
const returnRef = ['Vector', 'Dimensions', 'Color']

// Generate parameter list for function signature
const argsMap = (args) =>
  Object.entries(args)
    .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
    .join(', ')

// Generate parameter list for function call with type conversions
const callArgsMap = (args) =>
  Object.entries(args)
    .map(([name, type]) => {
      // Convert Nelua integers to C int32 if needed
      if (type === 'i32') {
        return `(@int32)(${name})`
      }
      // Handle special cases like Vector[] -> size_t and pointer
      if (type === 'Vector[]') {
        return `${name}, numPoints`
      }
      return name
    })
    .join(', ')

const api = createApiStream()

api.on('api', (apiName) => {
  out.push('', `-- ${apiName.toUpperCase()}`, '')
})

api.on('function', ({ apiName, funcName, args = {}, returns = 'void', description = '' }) => {
  const neluaReturn = retTypes[returns] || returns
  const paramList = argsMap(args)
  const hasVectorArray = Object.values(args).includes('Vector[]')

  // Generate C import
  out.push(`-- ${description}`)
  out.push(`local function _${funcName}(${paramList}${hasVectorArray ? ', numPoints: int32' : ''}): ${neluaReturn} <cimport '${funcName}', nodecl> end`)

  // Generate Nelua wrapper
  out.push(`global function ${funcName}(${paramList}${hasVectorArray ? ', numPoints: integer' : ''}): ${neluaReturn}`)

  const callArgs = callArgsMap(args) + (hasVectorArray ? ', (@int32)(numPoints)' : '')

  if (returns === 'void') {
    out.push(`  _${funcName}(${callArgs})`)
  } else if (returnRef.includes(returns)) {
    out.push(`  local result = _${funcName}(${callArgs})`)
    out.push(`  return result != nilptr and $result or (@${argTypes[returns]}){0}`)
  } else {
    out.push(`  return _${funcName}(${callArgs})`)
  }

  out.push('end', '')
})

api.on('end', async () => {
  await writeFile('carts/null0.nelua', out.join('\n'))
  console.log('Generated Nelua API bindings: carts/null0.nelua')
})

api.on('error', (e) => {
  console.error('Error generating Nelua bindings:', e)
  process.exit(1)
})
