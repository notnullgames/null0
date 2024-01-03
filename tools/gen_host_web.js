// Generate JS host-bindings

import { glob } from 'glob'
import YAML from 'yaml'
import { readFile, writeFile } from 'fs/promises'

// functions that have a hand-made interface
const customFunctions = ['trace']

const api = {}
for (const f of await glob('api/*.yml')) {
  const api_name = f.replace(/^api\/(.+)\.yml$/g, '$1')
  api[api_name] = YAML.parse(await readFile(f, 'utf8'))
}

let code = `// this will expose null0 API to js

export default function null0_bind (api, mod) {
  class Color {
    constructor (init = {}, address) {
      this._size = 4
      this._address = address || mod._malloc(this._size)
      for (const k of Object.keys(init)) {
        this[k] = init[k]
      }
    }

    get r () {
      return mod.HEAPU8[this._address]
    }

    get g () {
      return mod.HEAPU8[this._address + 1]
    }

    get b () {
      return mod.HEAPU8[this._address + 2]
    }

    get a () {
      return mod.HEAPU8[this._address + 3]
    }

    get data () {
      return mod.HEAPU32[this._address / 4]
    }

    set r (v) {
      mod.HEAPU8[this._address] = v
    }

    set g (v) {
      mod.HEAPU8[this._address + 1] = v
    }

    set b (v) {
      mod.HEAPU8[this._address + 2] = v
    }

    set a (v) {
      mod.HEAPU8[this._address + 3] = v
    }

    set data (v) {
      mod.HEAPU32[this._address / 4] = v
    }
  }

  class Dimensions {
    constructor (init = {}, address) {
      this._size = 8
      this._address = address || mod._malloc(this._size)
      for (const k of Object.keys(init)) {
        this[k] = init[k]
      }
    }

    get width () {
      return mod.HEAPU32[this._address / 4]
    }

    get height () {
      return mod.HEAPU32[(this._address / 4) + 1]
    }

    set width (v) {
      mod.HEAPU32[this._address / 4] = v
    }

    set height (v) {
      mod.HEAPU32[(this._address / 4) + 1] = v
    }
  }

  class Vector {
    constructor (init = {}, address) {
      this._size = 8
      this._address = address || mod._malloc(this._size)
      for (const k of Object.keys(init)) {
        this[k] = init[k]
      }
    }

    get x () {
      return mod.HEAP32[this._address / 4]
    }

    get y () {
      return mod.HEAP32[(this._address / 4) + 1]
    }

    set x (v) {
      mod.HEAP32[this._address / 4] = v
    }

    set y (v) {
      mod.HEAP32[(this._address / 4) + 1] = v
    }
  }

  class Rectangle {
    constructor (init = {}, address) {
      this._size = 16
      this._address = address || mod._malloc(this._size)
      for (const k of Object.keys(init)) {
        this[k] = init[k]
      }
    }

    get x () {
      return mod.HEAP32[this._address / 4]
    }

    get y () {
      return mod.HEAP32[(this._address / 4) + 1]
    }

    get width () {
      return mod.HEAP32[(this._address / 4) + 2]
    }

    get height () {
      return mod.HEAP32[(this._address / 4) + 3]
    }

    set x (v) {
      mod.HEAP32[this._address / 4] = v
    }

    set y (v) {
      mod.HEAP32[(this._address / 4) + 1] = v
    }

    set width (v) {
      mod.HEAP32[(this._address / 4) + 2] = v
    }

    set height (v) {
      mod.HEAP32[(this._address / 4) + 3] = v
    }
  }

  class SfxParams {
    constructor (init = {}, address) {
      this._size = 96
      this._address = address || mod._malloc(this._size)
      for (const k of Object.keys(init)) {
        this[k] = init[k]
      }
    }

    // Random seed used to generate the wave
    get randSeed() {
      return mod.HEAPU32[(this._address / 4)]
    }

    set randSeed(v) {
      mod.HEAPU32[(this._address / 4)] = v
    }

    // Wave type (square, sawtooth, sine, noise)
    get waveType() {
      return mod.HEAP32[(this._address / 4) + 1]
    }

    set waveType(v) {
      mod.HEAP32[(this._address / 4) + 1] = v
    }

    // Wave envelope parameters

    get attackTime() {
      return mod.HEAPF32[(this._address / 4) + 2]
    }

    set attackTime(v) {
      mod.HEAPF32[(this._address / 4) + 2] = v
    }

    get sustainTime() {
      return mod.HEAPF32[(this._address / 4) + 3]
    }

    set sustainTime(v) {
      mod.HEAPF32[(this._address / 4) + 3] = v
    }

    get sustainPunch() {
      return mod.HEAPF32[(this._address / 4) + 4]
    }

    set sustainPunch(v) {
      mod.HEAPF32[(this._address / 4) + 4] = v
    }

    get decayTime() {
      return mod.HEAPF32[(this._address / 4) + 5]
    }

    set decayTime(v) {
      mod.HEAPF32[(this._address / 4) + 5] = v
    }

    // Frequency parameters

    get startFrequency() {
      return mod.HEAPF32[(this._address / 4) + 6]
    }

    set startFrequency(v) {
      mod.HEAPF32[(this._address / 4) + 6] = v
    }

    get minFrequency() {
      return mod.HEAPF32[(this._address / 4) + 7]
    }

    set minFrequency(v) {
      mod.HEAPF32[(this._address / 4) + 7] = v
    }

    get slide() {
      return mod.HEAPF32[(this._address / 4) + 8]
    }

    set slide(v) {
      mod.HEAPF32[(this._address / 4) + 8] = v
    }

    get deltaSlide() {
      return mod.HEAPF32[(this._address / 4) + 9]
    }

    set deltaSlide(v) {
      mod.HEAPF32[(this._address / 4) + 9] = v
    }

    get vibratoDepth() {
      return mod.HEAPF32[(this._address / 4) + 10]
    }

    set vibratoDepth(v) {
      mod.HEAPF32[(this._address / 4) + 10] = v
    }

    get vibratoSpeed() {
      return mod.HEAPF32[(this._address / 4) + 11]
    }

    set vibratoSpeed(v) {
      mod.HEAPF32[(this._address / 4) + 11] = v
    }

    // Tone change parameters

    get changeAmount() {
      return mod.HEAPF32[(this._address / 4) + 12]
    }

    set changeAmount(v) {
      mod.HEAPF32[(this._address / 4) + 12] = v
    }

    get changeSpeed() {
      return mod.HEAPF32[(this._address / 4) + 13]
    }

    set changeSpeed(v) {
      mod.HEAPF32[(this._address / 4) + 13] = v
    }

    // Square wave parameters

    get squareDuty() {
      return mod.HEAPF32[(this._address / 4) + 14]
    }

    set squareDuty(v) {
      mod.HEAPF32[(this._address / 4) + 14] = v
    }

    get dutySweep() {
      return mod.HEAPF32[(this._address / 4) + 15]
    }

    set dutySweep(v) {
      mod.HEAPF32[(this._address / 4) + 15] = v
    }

    // Repeat parameters

    get repeatSpeed() {
      return mod.HEAPF32[(this._address / 4) + 16]
    }

    set repeatSpeed(v) {
      mod.HEAPF32[(this._address / 4) + 16] = v
    }

    // Phaser parameters

    get phaserOffset() {
      return mod.HEAPF32[(this._address / 4) + 17]
    }

    set phaserOffset(v) {
      mod.HEAPF32[(this._address / 4) + 17] = v
    }

    get phaserSweep() {
      return mod.HEAPF32[(this._address / 4) + 18]
    }

    set phaserSweep(v) {
      mod.HEAPF32[(this._address / 4) + 18] = v
    }


    // Filter parameters

    get lpfCutoff() {
      return mod.HEAPF32[(this._address / 4) + 19]
    }

    set lpfCutoff(v) {
      mod.HEAPF32[(this._address / 4) + 19] = v
    }

    get lpfCutoffSweep() {
      return mod.HEAPF32[(this._address / 4) + 20]
    }

    set lpfCutoffSweep(v) {
      mod.HEAPF32[(this._address / 4) + 20] = v
    }

    get lpfResonance() {
      return mod.HEAPF32[(this._address / 4) + 21]
    }

    set lpfResonance(v) {
      mod.HEAPF32[(this._address / 4) + 21] = v
    }

    get hpfCutoff() {
      return mod.HEAPF32[(this._address / 4) + 22]
    }

    set hpfCutoff(v) {
      mod.HEAPF32[(this._address / 4) + 22] = v
    }

    get hpfCutoffSweep() {
      return mod.HEAPF32[(this._address / 4) + 23]
    }

    set hpfCutoffSweep(v) {
      mod.HEAPF32[(this._address / 4) + 23] = v
    }
  }

  api.WIDTH = 320
  api.HEIGHT = 240

  api.Color = Color
  api.Dimensions = Dimensions
  api.Vector = Vector
  api.Rectangle = Rectangle
  api.SfxParams = SfxParams

  api.ImageFilter = {
    FILTER_NEARESTNEIGHBOR: 0,
    FILTER_BILINEAR: 1,
    FILTER_SMOOTH: 2
  }

  api.Key = {
    KEY_INVALID: 0,
    KEY_SPACE: 32,
    KEY_APOSTROPHE: 39,
    KEY_COMMA: 44,
    KEY_MINUS: 45,
    KEY_PERIOD: 46,
    KEY_SLASH: 47,
    KEY_0: 48,
    KEY_1: 49,
    KEY_2: 50,
    KEY_3: 51,
    KEY_4: 52,
    KEY_5: 53,
    KEY_6: 54,
    KEY_7: 55,
    KEY_8: 56,
    KEY_9: 57,
    KEY_SEMICOLON: 59,
    KEY_EQUAL: 61,
    KEY_A: 65,
    KEY_B: 66,
    KEY_C: 67,
    KEY_D: 68,
    KEY_E: 69,
    KEY_F: 70,
    KEY_G: 71,
    KEY_H: 72,
    KEY_I: 73,
    KEY_J: 74,
    KEY_K: 75,
    KEY_L: 76,
    KEY_M: 77,
    KEY_N: 78,
    KEY_O: 79,
    KEY_P: 80,
    KEY_Q: 81,
    KEY_R: 82,
    KEY_S: 83,
    KEY_T: 84,
    KEY_U: 85,
    KEY_V: 86,
    KEY_W: 87,
    KEY_X: 88,
    KEY_Y: 89,
    KEY_Z: 90,
    KEY_LEFT_BRACKET: 91,
    KEY_BACKSLASH: 92,
    KEY_RIGHT_BRACKET: 93,
    KEY_GRAVE_ACCENT: 96,
    KEY_WORLD_1: 161,
    KEY_WORLD_2: 162,
    KEY_ESCAPE: 256,
    KEY_ENTER: 257,
    KEY_TAB: 258,
    KEY_BACKSPACE: 259,
    KEY_INSERT: 260,
    KEY_DELETE: 261,
    KEY_RIGHT: 262,
    KEY_LEFT: 263,
    KEY_DOWN: 264,
    KEY_UP: 265,
    KEY_PAGE_UP: 266,
    KEY_PAGE_DOWN: 267,
    KEY_HOME: 268,
    KEY_END: 269,
    KEY_CAPS_LOCK: 280,
    KEY_SCROLL_LOCK: 281,
    KEY_NUM_LOCK: 282,
    KEY_PRINT_SCREEN: 283,
    KEY_PAUSE: 284,
    KEY_F1: 290,
    KEY_F2: 291,
    KEY_F3: 292,
    KEY_F4: 293,
    KEY_F5: 294,
    KEY_F6: 295,
    KEY_F7: 296,
    KEY_F8: 297,
    KEY_F9: 298,
    KEY_F10: 299,
    KEY_F11: 300,
    KEY_F12: 301,
    KEY_F13: 302,
    KEY_F14: 303,
    KEY_F15: 304,
    KEY_F16: 305,
    KEY_F17: 306,
    KEY_F18: 307,
    KEY_F19: 308,
    KEY_F20: 309,
    KEY_F21: 310,
    KEY_F22: 311,
    KEY_F23: 312,
    KEY_F24: 313,
    KEY_F25: 314,
    KEY_KP_0: 320,
    KEY_KP_1: 321,
    KEY_KP_2: 322,
    KEY_KP_3: 323,
    KEY_KP_4: 324,
    KEY_KP_5: 325,
    KEY_KP_6: 326,
    KEY_KP_7: 327,
    KEY_KP_8: 328,
    KEY_KP_9: 329,
    KEY_KP_DECIMAL: 330,
    KEY_KP_DIVIDE: 331,
    KEY_KP_MULTIPLY: 332,
    KEY_KP_SUBTRACT: 333,
    KEY_KP_ADD: 334,
    KEY_KP_ENTER: 335,
    KEY_KP_EQUAL: 336,
    KEY_LEFT_SHIFT: 340,
    KEY_LEFT_CONTROL: 341,
    KEY_LEFT_ALT: 342,
    KEY_LEFT_SUPER: 343,
    KEY_RIGHT_SHIFT: 344,
    KEY_RIGHT_CONTROL: 345,
    KEY_RIGHT_ALT: 346,
    KEY_RIGHT_SUPER: 347,
    KEY_MENU: 348
  }

  api.GamepadButton = {
    GAMEPAD_BUTTON_UNKNOWN: 0, // Unknown button, just for error checking
    GAMEPAD_BUTTON_UP: 1, // Gamepad left DPAD up button
    GAMEPAD_BUTTON_RIGHT: 2, // Gamepad left DPAD right button
    GAMEPAD_BUTTON_DOWN: 3, // Gamepad left DPAD down button
    GAMEPAD_BUTTON_LEFT: 4, // Gamepad left DPAD left button
    GAMEPAD_BUTTON_Y: 5, // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    GAMEPAD_BUTTON_B: 6, // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    GAMEPAD_BUTTON_A: 7, // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    GAMEPAD_BUTTON_X: 8, // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    GAMEPAD_BUTTON_LEFT_SHOULDER: 9, // Gamepad top/back trigger left (first), it could be a trailing button
    GAMEPAD_BUTTON_LEFT_TRIGGER: 10, // Gamepad top/back trigger left (second), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_SHOULDER: 11, // Gamepad top/back trigger right (one), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER: 12, // Gamepad top/back trigger right (second), it could be a trailing button
    GAMEPAD_BUTTON_SELECT: 13, // Gamepad center buttons, left one (i.e. PS3: Select)
    GAMEPAD_BUTTON_MENU: 14, // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    GAMEPAD_BUTTON_START: 15, // Gamepad center buttons, right one (i.e. PS3: Start)
    GAMEPAD_BUTTON_LEFT_THUMB: 16, // Gamepad joystick pressed button left
    GAMEPAD_BUTTON_RIGHT_THUMB: 17 // Gamepad joystick pressed button right
  }

  api.MouseButton = {
    MOUSE_BUTTON_UNKNOWN: 0,
    MOUSE_BUTTON_LEFT: 1,
    MOUSE_BUTTON_RIGHT: 2,
    MOUSE_BUTTON_MIDDLE: 3
  }

  api.SfxPresetType = {
    SFX_COIN: 0,
    SFX_LASER: 1,
    SFX_EXPLOSION: 2,
    SFX_POWERUP: 3,
    SFX_HURT: 4,
    SFX_JUMP: 5,
    SFX_SELECT: 6
  }

  api.SfxWaveType = {
    SFX_SQUARE: 0,
    SFX_SAWTOOTH: 1,
    SFX_SINE: 2,
    SFX_NOISE: 3,
    SFX_TRIANGLE: 4,
    SFX_PINK_NOISE: 5
  }

  // make enums act kidna like C enums
  for (const t of ['ImageFilter', 'Key', 'GamepadButton', 'MouseButton', 'SfxPresetType', 'SfxWaveType']) {
    for (const k of Object.keys(api[t])) {
      api[k] = api[t][k]
    }
  }

  api.LIGHTGRAY = new Color({ r: 200, g: 200, b: 200, a: 255 })
  api.GRAY = new Color({ r: 130, g: 130, b: 130, a: 255 })
  api.DARKGRAY = new Color({ r: 80, g: 80, b: 80, a: 255 })
  api.YELLOW = new Color({ r: 253, g: 249, b: 0, a: 255 })
  api.GOLD = new Color({ r: 255, g: 203, b: 0, a: 255 })
  api.ORANGE = new Color({ r: 255, g: 161, b: 0, a: 255 })
  api.PINK = new Color({ r: 255, g: 109, b: 194, a: 255 })
  api.RED = new Color({ r: 230, g: 41, b: 55, a: 255 })
  api.MAROON = new Color({ r: 190, g: 33, b: 55, a: 255 })
  api.GREEN = new Color({ r: 0, g: 228, b: 48, a: 255 })
  api.LIME = new Color({ r: 0, g: 158, b: 47, a: 255 })
  api.DARKGREEN = new Color({ r: 0, g: 117, b: 44, a: 255 })
  api.SKYBLUE = new Color({ r: 102, g: 191, b: 255, a: 255 })
  api.BLUE = new Color({ r: 0, g: 121, b: 241, a: 255 })
  api.DARKBLUE = new Color({ r: 0, g: 82, b: 172, a: 255 })
  api.PURPLE = new Color({ r: 200, g: 122, b: 255, a: 255 })
  api.VIOLET = new Color({ r: 135, g: 60, b: 190, a: 255 })
  api.DARKPURPLE = new Color({ r: 112, g: 31, b: 126, a: 255 })
  api.BEIGE = new Color({ r: 211, g: 176, b: 131, a: 255 })
  api.BROWN = new Color({ r: 127, g: 106, b: 79, a: 255 })
  api.DARKBROWN = new Color({ r: 76, g: 63, b: 47, a: 255 })
  api.WHITE = new Color({ r: 255, g: 255, b: 255, a: 255 })
  api.BLACK = new Color({ r: 0, g: 0, b: 0, a: 255 })
  api.BLANK = new Color({ r: 0, g: 0, b: 0, a: 0 })
  api.MAGENTA = new Color({ r: 255, g: 0, b: 255, a: 255 })
  api.RAYWHITE = new Color({ r: 245, g: 245, b: 245, a: 255 })
`

for (const type of Object.keys(api)) {
  code += `\n  /////////// ${type.toUpperCase()} ///////////\n\n\n`
  for (const fun of Object.keys(api[type]).filter(f => !customFunctions.includes(f))) {
    const callArgs = Object.keys(api[type][fun].args).map((name) => {
      const t = api[type][fun].args[name]
      if (['Color', 'Dimensions', 'Vector', 'Rectangle', 'SfxParams', 'SfxParams*'].includes(t)) {
        return `${name}._address`
      } else if (t === 'string') {
        return `mod.stringToNewUTF8(${name})`
      } else {
        return name
      }
    })

    code += `  // ${api[type][fun].description}\n`
    const t = api[type][fun].returns
    if (['Color', 'Dimensions', 'Vector', 'Rectangle', 'SfxParams', 'SfxParams*'].includes(t)) {
      code += `  api.${fun} = (${Object.keys(api[type][fun].args).join(', ')}) => {
    const ret = new ${t}()
    mod._null0_${fun}(ret._address, ${callArgs.join(', ')})
    return ret
  }\n`
    } else {
      code += `  api.${fun} = (${Object.keys(api[type][fun].args).join(', ')}) => mod._null0_${fun}(${callArgs.join(', ')})\n`
    }
  }
}

code += `
}

`

await writeFile('headers/null0_web_host.mjs', code)
