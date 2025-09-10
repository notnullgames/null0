#!/usr/bin/env node

// Generator for Nelua null0 API bindings
// Generates Nelua code from the API definitions

import { writeFile } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `-- null0 API for Nelua

##[[
cinclude 'null0.h'
]]

global Dimensions <cimport'Dimensions', nodecl> = @record{
  width: uint32,
  height: uint32
}

global Vector <cimport'Vector', nodecl> = @record{
  x: int32,
  y: int32
}

global Rectangle <cimport'Rectangle', nodecl> = @record{
  x: int32,
  y: int32,
  width: int32,
  height: int32
}

global Color <cimport'Color', nodecl> = @record{
  r: uint8,
  g: uint8,
  b: uint8,
  a: uint8
}

global SfxParams <cimport'SfxParams', nodecl> = @record{
  randSeed: uint32,
  waveType: int32,
  attackTime: float32,
  sustainTime: float32,
  sustainPunch: float32,
  decayTime: float32,
  startFrequency: float32,
  minFrequency: float32,
  slide: float32,
  deltaSlide: float32,
  vibratoDepth: float32,
  vibratoSpeed: float32,
  changeAmount: float32,
  changeSpeed: float32,
  squareDuty: float32,
  dutySweep: float32,
  repeatSpeed: float32,
  phaserOffset: float32,
  phaserSweep: float32,
  lpfCutoff: float32,
  lpfCutoffSweep: float32,
  lpfResonance: float32,
  hpfCutoff: float32,
  hpfCutoffSweep: float32
}

global ImageFilter <cimport'ImageFilter', nodecl> = @enum(int32){
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR = 1,
  FILTER_SMOOTH = 2
}

global Key <cimport'Key', nodecl> = @enum(int32){
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

global GamepadButton <cimport'GamepadButton', nodecl> = @enum(int32){
  GAMEPAD_BUTTON_UNKNOWN = 0,
  GAMEPAD_BUTTON_UP = 1,
  GAMEPAD_BUTTON_RIGHT = 2,
  GAMEPAD_BUTTON_DOWN = 3,
  GAMEPAD_BUTTON_LEFT = 4,
  GAMEPAD_BUTTON_Y = 5,
  GAMEPAD_BUTTON_B = 6,
  GAMEPAD_BUTTON_A = 7,
  GAMEPAD_BUTTON_X = 8,
  GAMEPAD_BUTTON_LEFT_SHOULDER = 9,
  GAMEPAD_BUTTON_LEFT_TRIGGER = 10,
  GAMEPAD_BUTTON_RIGHT_SHOULDER = 11,
  GAMEPAD_BUTTON_RIGHT_TRIGGER = 12,
  GAMEPAD_BUTTON_SELECT = 13,
  GAMEPAD_BUTTON_MENU = 14,
  GAMEPAD_BUTTON_START = 15,
  GAMEPAD_BUTTON_LEFT_THUMB = 16,
  GAMEPAD_BUTTON_RIGHT_THUMB = 17
}

global MouseButton <cimport'MouseButton', nodecl> = @enum(int32){
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3
}

global SfxPresetType <cimport'SfxPresetType', nodecl> = @enum(int32){
  SFX_COIN = 0,
  SFX_LASER = 1,
  SFX_EXPLOSION = 2,
  SFX_POWERUP = 3,
  SFX_HURT = 4,
  SFX_JUMP = 5,
  SFX_SELECT = 6,
  SFX_SYNTH = 7
}

global SCREEN: int32 = 0
global SCREEN_WIDTH: int32 = 640
global SCREEN_HEIGHT: int32 = 480
global FONT_DEFAULT: int32 = 0

global LIGHTGRAY: Color <cimport, nodecl>
global GRAY: Color <cimport, nodecl>
global DARKGRAY: Color <cimport, nodecl>
global YELLOW: Color <cimport, nodecl>
global GOLD: Color <cimport, nodecl>
global ORANGE: Color <cimport, nodecl>
global PINK: Color <cimport, nodecl>
global RED: Color <cimport, nodecl>
global MAROON: Color <cimport, nodecl>
global GREEN: Color <cimport, nodecl>
global LIME: Color <cimport, nodecl>
global DARKGREEN: Color <cimport, nodecl>
global SKYBLUE: Color <cimport, nodecl>
global BLUE: Color <cimport, nodecl>
global DARKBLUE: Color <cimport, nodecl>
global PURPLE: Color <cimport, nodecl>
global VIOLET: Color <cimport, nodecl>
global DARKPURPLE: Color <cimport, nodecl>
global BEIGE: Color <cimport, nodecl>
global BROWN: Color <cimport, nodecl>
global DARKBROWN: Color <cimport, nodecl>
global WHITE: Color <cimport, nodecl>
global BLACK: Color <cimport, nodecl>
global BLANK: Color <cimport, nodecl>
global MAGENTA: Color <cimport, nodecl>
global RAYWHITE: Color <cimport, nodecl>
`
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
  'Vector[]': '*Vector',
  SfxParams: 'SfxParams'
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
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}

// Generate parameter list for function signature
const argsMap = (args) => {
  const params = Object.entries(args).map(([name, type]) => {
    return `${name}: ${argTypes[type] || type}`
  })
  // Don't add extra numPoints - it's already in the API definition
  return params.join(', ')
}

// TODO: I could build all of the above code with constants/enums/structs/scalars/callbacks

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `-- ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const neluaReturn = retTypes[returns] || returns
    const paramList = argsMap(args)

    // Generate external function declaration
    out.push(`-- ${description}`)
    out.push(`global function ${funcName}(${paramList}): ${neluaReturn} <cimport,nodecl> end`, '')
  }
}

await writeFile('carts/nelua/null0.nelua', out.join('\n'))
