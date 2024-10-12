// this will generate the assemblyscript header for carts
// TODO: only partially implemented (hand-edited output)

import { getAPI } from './shared.js'
import { writeFile } from 'fs/promises'

const api = await getAPI()

let out = `// this code will be injected at the top of your cart-code

// ENUMS

enum ImageFilter {
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR,
  FILTER_SMOOTH
};

enum Key {
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
  KEY_MENU = 348,
};

enum GamepadButton {
  GAMEPAD_BUTTON_UNKNOWN = 0,     // Unknown button, just for error checking
  GAMEPAD_BUTTON_UP = 1,          // Gamepad left DPAD up button
  GAMEPAD_BUTTON_RIGHT,           // Gamepad left DPAD right button
  GAMEPAD_BUTTON_DOWN,            // Gamepad left DPAD down button
  GAMEPAD_BUTTON_LEFT,            // Gamepad left DPAD left button
  GAMEPAD_BUTTON_Y,               // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  GAMEPAD_BUTTON_B,               // Gamepad right button right (i.e. PS3: Square, Xbox: X)
  GAMEPAD_BUTTON_A,               // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  GAMEPAD_BUTTON_X,               // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
  GAMEPAD_BUTTON_LEFT_SHOULDER,   // Gamepad top/back trigger left (first), it could be a trailing button
  GAMEPAD_BUTTON_LEFT_TRIGGER,    // Gamepad top/back trigger left (second), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_SHOULDER,  // Gamepad top/back trigger right (one), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER,   // Gamepad top/back trigger right (second), it could be a trailing button
  GAMEPAD_BUTTON_SELECT,          // Gamepad center buttons, left one (i.e. PS3: Select)
  GAMEPAD_BUTTON_MENU,            // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  GAMEPAD_BUTTON_START,           // Gamepad center buttons, right one (i.e. PS3: Start)
  GAMEPAD_BUTTON_LEFT_THUMB,      // Gamepad joystick pressed button left
  GAMEPAD_BUTTON_RIGHT_THUMB      // Gamepad joystick pressed button right
}

enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3,
}

enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
  SFX_SYNTH
}

enum SfxWaveType {
  SFX_SQUARE,
  SFX_SAWTOOTH,
  SFX_SINE,
  SFX_NOISE,
  SFX_TRIANGLE,
  SFX_PINK_NOISE
}

enum FileType {
  FILETYPE_REGULAR,   /**< a normal file */
  FILETYPE_DIRECTORY, /**< a directory */
  FILETYPE_SYMLINK,   /**< a symlink */
  FILETYPE_OTHER      /**< something completely different like a device */
}


// STRUCTS

class Color {
  constructor(r:u8 = 0, g:u8 = 0, b:u8 = 0, a:u8 = 0) {
    this.r = r
    this.g = g
    this.b = b
    this.a = a
  }
  
  r: u8
  g: u8
  b: u8
  a: u8
}

class Dimensions {
  constructor(width:u32 = 0, height:u32 = 0) {
    this.width = width
    this.height = height
  }

  width: u32
  height: u32
}

class Vector {
  constructor(x:u32 = 0, y:u32 = 0) {
    this.x = x
    this.y = y
  }

  x: i32
  y: i32
}

class Rectangle {
  constructor(x:i32 = 0, y:i32 = 0, width:i32 = 0, height:i32 = 0) {
    this.x = x
    this.y = y
    this.width = width
    this.height = height
  }

  x: i32
  y: i32
  width: i32
  height: i32
}

class FileInfo {
  constructor(filesize:i64 = 0, modtime:i64 = 0, createtime:i64 = 0, accesstime:i64 = 0, filetype:FileType, readonly:boolean=false) {
    this.filesize = filesize
    this.modtime = modtime
    this.createtime = createtime
    this.accesstime = accesstime
    this.filetype = filetype
    this.readonly = readonly
  }

  filesize:i64
  modtime:i64
  createtime:i64
  accesstime:i64
  filetype:FileType
  readonly:boolean
}

class SfxParams {
  constructor(randSeed: u32 = 0, waveType: i32 = 0, attackTime: f32 = 0, sustainTime: f32 = 0, sustainPunch: f32 = 0, decayTime: f32 = 0, startFrequency: f32 = 0, minFrequency: f32 = 0, slide: f32 = 0, deltaSlide: f32 = 0, vibratoDepth: f32 = 0, vibratoSpeed: f32 = 0, changeAmount: f32 = 0, changeSpeed: f32 = 0, squareDuty: f32 = 0, dutySweep: f32 = 0, repeatSpeed: f32 = 0, phaserOffset: f32 = 0, phaserSweep: f32 = 0, lpfCutoff: f32 = 0, lpfCutoffSweep: f32 = 0, lpfResonance: f32 = 0, hpfCutoff: f32 = 0, hpfCutoffSweep: f32 = 0) {
    this.randSeed = randSeed
    this.waveType = waveType
    this.attackTime = attackTime
    this.sustainTime = sustainTime
    this.sustainPunch = sustainPunch
    this.decayTime = decayTime
    this.startFrequency = startFrequency
    this.minFrequency = minFrequency
    this.slide = slide
    this.deltaSlide = deltaSlide
    this.vibratoDepth = vibratoDepth
    this.vibratoSpeed = vibratoSpeed
    this.changeAmount = changeAmount
    this.changeSpeed = changeSpeed
    this.squareDuty = squareDuty
    this.dutySweep = dutySweep
    this.repeatSpeed = repeatSpeed
    this.phaserOffset = phaserOffset
    this.phaserSweep = phaserSweep
    this.lpfCutoff = lpfCutoff
    this.lpfCutoffSweep = lpfCutoffSweep
    this.lpfResonance = lpfResonance
    this.hpfCutoff = hpfCutoff
    this.hpfCutoffSweep = hpfCutoffSweep
  }

  randSeed: u32
  waveType: i32
  attackTime: f32
  sustainTime: f32
  sustainPunch: f32
  decayTime: f32
  startFrequency: f32
  minFrequency: f32
  slide: f32
  deltaSlide: f32
  vibratoDepth: f32
  vibratoSpeed: f32
  changeAmount: f32
  changeSpeed: f32
  squareDuty: f32
  dutySweep: f32
  repeatSpeed: f32
  phaserOffset: f32
  phaserSweep: f32
  lpfCutoff: f32
  lpfCutoffSweep: f32
  lpfResonance: f32
  hpfCutoff: f32
  hpfCutoffSweep: f32
}


// DEFINITIONS

const HEIGHT: f32 = 240.0
const WIDTH: f32 = 320.0

const LIGHTGRAY: Color = new Color(200, 200, 200, 255)
const GRAY: Color = new Color(130, 130, 130, 255)
const DARKGRAY: Color = new Color(80, 80, 80, 255)
const YELLOW: Color = new Color(253, 249, 0, 255)
const GOLD: Color = new Color(255, 203, 0, 255)
const ORANGE: Color = new Color(255, 161, 0, 255)
const PINK: Color = new Color(255, 109, 194, 255)
const RED: Color = new Color(230, 41, 55, 255)
const MAROON: Color = new Color(190, 33, 55, 255)
const GREEN: Color = new Color(0, 228, 48, 255)
const LIME: Color = new Color(0, 158, 47, 255)
const DARKGREEN: Color = new Color(0, 117, 44, 255)
const SKYBLUE: Color = new Color(102, 191, 255, 255)
const BLUE: Color = new Color(0, 121, 241, 255)
const DARKBLUE: Color = new Color(0, 82, 172, 255)
const PURPLE: Color = new Color(200, 122, 255, 255)
const VIOLET: Color = new Color(135, 60, 190, 255)
const DARKPURPLE: Color = new Color(112, 31, 126, 255)
const BEIGE: Color = new Color(211, 176, 131, 255)
const BROWN: Color = new Color(127, 106, 79, 255)
const DARKBROWN: Color = new Color(76, 63, 47, 255)
const WHITE: Color = new Color(255, 255, 255, 255)
const BLACK: Color = new Color(0, 0, 0, 255)
const BLANK: Color = new Color(0, 0, 0, 0)
const MAGENTA: Color = new Color(255, 0, 255, 255)
const RAYWHITE: Color = new Color(245, 245, 245, 255)


// FUNCTIONS

`

for (const cat of Object.keys(api)) {
  if (cat === 'testing') {
    continue
  }

  out += `// ${cat}\n\n`

  for (const fname of Object.keys(api[cat])) {
    if (fname === 'trace') {
      continue
    }
    const func = api[cat][fname]
    out += `// ${func.description}\n`
    out += `@external("null0", "${fname}")\n`
    out += `declare function ${fname}(${Object.keys(func.args).map(a => `${a}: ${func.args[a]}`).join(', ')}): ${func.returns}\n\n`
  }
}

console.log(out)
