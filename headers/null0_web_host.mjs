// this will expose null0 API to js

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

  /////////// UTILITIES ///////////


  // Get system-time (ms) since unix epoch
  api.current_time = () => mod._null0_current_time()
  // Get the change in time (seconds) since the last update run
  api.delta_time = () => mod._null0_delta_time()
  // Get a random integer between 2 numbers
  api.random_int = (min, max) => mod._null0_random_int(min, max)

  /////////// SOUND ///////////


  // Load a sound from a file in cart
  api.load_sound = (filename) => mod._null0_load_sound(mod.stringToNewUTF8(filename))
  // Play a sound
  api.play_sound = (sound, loop) => mod._null0_play_sound(sound, loop)
  // Stop a sound
  api.stop_sound = (sound) => mod._null0_stop_sound(sound)
  // Create a new sound-effect from some sfxr params
  api.new_sfx = (params) => mod._null0_new_sfx(params._address)
  // Generate randomized preset sfxr params
  api.preset_sfx = (params, type) => mod._null0_preset_sfx(params._address, type)
  // Randomize sfxr params
  api.randomize_sfx = (params, waveType) => mod._null0_randomize_sfx(params._address, waveType)
  // Randomly mutate sfxr params
  api.mutate_sfx = (params, range, mask) => mod._null0_mutate_sfx(params._address, range, mask)
  // Create a new sfxr from a .rfx file
  api.load_sfx = (filename) => {
    const ret = new SfxParams()
    mod._null0_load_sfx(ret._address, mod.stringToNewUTF8(filename))
    return ret
  }
  // Unload a sound
  api.unload_sound = (sound) => mod._null0_unload_sound(sound)

  /////////// INPUT ///////////


  // Has the key been pressed? (tracks unpress/read correctly)
  api.key_pressed = (key) => mod._null0_key_pressed(key)
  // Is the key currently down?
  api.key_down = (key) => mod._null0_key_down(key)
  // Has the key been released? (tracks press/read correctly)
  api.key_released = (key) => mod._null0_key_released(key)
  // Is the key currently up?
  api.key_up = (key) => mod._null0_key_up(key)
  // Has the button been pressed? (tracks unpress/read correctly)
  api.gamepad_button_pressed = (gamepad, button) => mod._null0_gamepad_button_pressed(gamepad, button)
  // Is the button currently down?
  api.gamepad_button_down = (gamepad, button) => mod._null0_gamepad_button_down(gamepad, button)
  // Has the button been released? (tracks press/read correctly)
  api.gamepad_button_released = (gamepad, button) => mod._null0_gamepad_button_released(gamepad, button)
  // Is the button currently up?
  api.gamepad_button_up = (gamepad, button) => mod._null0_gamepad_button_up(gamepad, button)
  // Get current position of mouse
  api.mouse_position = () => {
    const ret = new Vector()
    mod._null0_mouse_position(ret._address, )
    return ret
  }
  // Has the button been pressed? (tracks unpress/read correctly)
  api.mouse_button_pressed = (button) => mod._null0_mouse_button_pressed(button)
  // Is the button currently down?
  api.mouse_button_down = (button) => mod._null0_mouse_button_down(button)
  // Has the button been released? (tracks press/read correctly)
  api.mouse_button_released = (button) => mod._null0_mouse_button_released(button)
  // Is the button currently up?
  api.mouse_button_up = (button) => mod._null0_mouse_button_up(button)

  /////////// GRAPHICS ///////////


  // Create a new blank image
  api.new_image = (width, height, color) => mod._null0_new_image(width, height, color._address)
  // Copy an image to a new image
  api.image_copy = (image) => mod._null0_image_copy(image)
  // Create an image from a region of another image
  api.image_subimage = (image, x, y, width, height) => mod._null0_image_subimage(image, x, y, width, height)
  // Clear the screen
  api.clear = (color) => mod._null0_clear(color._address)
  // Draw a single pixel on the screen
  api.draw_point = (x, y, color) => mod._null0_draw_point(x, y, color._address)
  // Draw a line on the screen
  api.draw_line = (startPosX, startPosY, endPosX, endPosY, color) => mod._null0_draw_line(startPosX, startPosY, endPosX, endPosY, color._address)
  // Draw a filled rectangle on the screen
  api.draw_rectangle = (posX, posY, width, height, color) => mod._null0_draw_rectangle(posX, posY, width, height, color._address)
  // Draw a filled triangle on the screen
  api.draw_triangle = (x1, y1, x2, y2, x3, y3, color) => mod._null0_draw_triangle(x1, y1, x2, y2, x3, y3, color._address)
  // Draw a filled ellipse on the screen
  api.draw_ellipse = (centerX, centerY, radiusX, radiusY, color) => mod._null0_draw_ellipse(centerX, centerY, radiusX, radiusY, color._address)
  // Draw a filled circle on the screen
  api.draw_circle = (centerX, centerY, radius, color) => mod._null0_draw_circle(centerX, centerY, radius, color._address)
  // Draw a filled polygon on the screen
  api.draw_polygon = (points, numPoints, color) => mod._null0_draw_polygon(points, numPoints, color._address)
  // Draw several lines on the screen
  api.draw_polyline = (points, numPoints, color) => mod._null0_draw_polyline(points, numPoints, color._address)
  // Draw a filled arc on the screen
  api.draw_arc = (centerX, centerY, radius, startAngle, endAngle, segments, color) => mod._null0_draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color._address)
  // Draw a filled round-rectangle on the screen
  api.draw_rectangle_rounded = (x, y, width, height, cornerRadius, color) => mod._null0_draw_rectangle_rounded(x, y, width, height, cornerRadius, color._address)
  // Draw an image on the screen
  api.draw_image = (src, posX, posY) => mod._null0_draw_image(src, posX, posY)
  // Draw a tinted image on the screen
  api.draw_image_tint = (src, posX, posY, tint) => mod._null0_draw_image_tint(src, posX, posY, tint._address)
  // Draw an image, rotated, on the screen
  api.draw_image_rotated = (src, posX, posY, degrees, offsetX, offsetY, filter) => mod._null0_draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter)
  // Draw an image, flipped, on the screen
  api.draw_image_flipped = (src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) => mod._null0_draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal)
  // Draw an image, scaled, on the screen
  api.draw_image_scaled = (src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) => mod._null0_draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter)
  // Draw some text on the screen
  api.draw_text = (font, text, posX, posY, color) => mod._null0_draw_text(font, mod.stringToNewUTF8(text), posX, posY, color._address)
  // Save an image to persistant storage
  api.save_image = (image, filename) => mod._null0_save_image(image, mod.stringToNewUTF8(filename))
  // Load an image from a file in cart
  api.load_image = (filename) => mod._null0_load_image(mod.stringToNewUTF8(filename))
  // Resize an image, in-place
  api.image_resize = (image, newWidth, newHeight, offsetX, offsetY, fill) => mod._null0_image_resize(image, newWidth, newHeight, offsetX, offsetY, fill._address)
  // Scale an image, in-place
  api.image_scale = (image, scaleX, scaleY, filter) => mod._null0_image_scale(image, scaleX, scaleY, filter)
  // Replace a color in an image, in-place
  api.image_color_replace = (image, color, replace) => mod._null0_image_color_replace(image, color._address, replace._address)
  // Tint a color in an image, in-place
  api.image_color_tint = (image, color) => mod._null0_image_color_tint(image, color._address)
  // Fade a color in an image, in-place
  api.image_color_fade = (image, alpha) => mod._null0_image_color_fade(image, alpha)
  // Copy a font to a new font
  api.font_copy = (font) => mod._null0_font_copy(font)
  // Scale a font, return a new font
  api.font_scale = (font, scaleX, scaleY, filter) => mod._null0_font_scale(font, scaleX, scaleY, filter)
  // Load a BMF font from a file in cart
  api.load_font_bmf = (filename, characters) => mod._null0_load_font_bmf(mod.stringToNewUTF8(filename), mod.stringToNewUTF8(characters))
  // Load a BMF font from an image
  api.load_font_bmf_from_image = (image, characters) => mod._null0_load_font_bmf_from_image(image, mod.stringToNewUTF8(characters))
  // Measure the size of some text
  api.measure_text = (font, text) => {
    const ret = new Dimensions()
    mod._null0_measure_text(ret._address, font, mod.stringToNewUTF8(text))
    return ret
  }
  // Meaure an image (use 0 for screen)
  api.measure_image = (image) => {
    const ret = new Dimensions()
    mod._null0_measure_image(ret._address, image)
    return ret
  }
  // Load a TTY font from a file in cart
  api.load_font_tty = (filename, glyphWidth, glyphHeight, characters) => mod._null0_load_font_tty(mod.stringToNewUTF8(filename), glyphWidth, glyphHeight, mod.stringToNewUTF8(characters))
  // Load a TTY font from an image
  api.load_font_tty_from_image = (image, glyphWidth, glyphHeight, characters) => mod._null0_load_font_tty_from_image(image, glyphWidth, glyphHeight, mod.stringToNewUTF8(characters))
  // Load a TTF font from a file in cart
  api.load_font_ttf = (filename, fontSize) => mod._null0_load_font_ttf(mod.stringToNewUTF8(filename), fontSize)
  // Invert the colors in an image, in-place
  api.image_color_invert = (image) => mod._null0_image_color_invert(image)
  // Calculate a rectangle representing the available alpha border in an image
  api.image_alpha_border = (image, threshold) => {
    const ret = new Rectangle()
    mod._null0_image_alpha_border(ret._address, image, threshold)
    return ret
  }
  // Crop an image, in-place
  api.image_crop = (image, x, y, width, height) => mod._null0_image_crop(image, x, y, width, height)
  // Crop an image based on the alpha border, in-place
  api.image_alpha_crop = (image, threshold) => mod._null0_image_alpha_crop(image, threshold)
  // Adjust the brightness of an image, in-place
  api.image_color_brightness = (image, factor) => mod._null0_image_color_brightness(image, factor)
  // Flip an image, in-place
  api.image_flip = (image, horizontal, vertical) => mod._null0_image_flip(image, horizontal, vertical)
  // Change the contrast of an image, in-place
  api.image_color_contrast = (image, contrast) => mod._null0_image_color_contrast(image, contrast)
  // Use an image as an alpha-mask on another image
  api.image_alpha_mask = (image, alphaMask, posX, posY) => mod._null0_image_alpha_mask(image, alphaMask, posX, posY)
  // Create a new image, rotating another image
  api.image_rotate = (image, degrees, filter) => mod._null0_image_rotate(image, degrees, filter)
  // Create a new image of a gradient
  api.image_gradient = (width, height, topLeft, topRight, bottomLeft, bottomRight) => mod._null0_image_gradient(width, height, topLeft._address, topRight._address, bottomLeft._address, bottomRight._address)
  // Unload an image
  api.unload_image = (image) => mod._null0_unload_image(image)
  // Unload a font
  api.unload_font = (font) => mod._null0_unload_font(font)
  // Clear an image
  api.clear_on_image = (destination, color) => mod._null0_clear_on_image(destination, color._address)
  // Draw a single pixel on an image
  api.draw_point_on_image = (destination, x, y, color) => mod._null0_draw_point_on_image(destination, x, y, color._address)
  // Draw a line on an image
  api.draw_line_on_image = (destination, startPosX, startPosY, endPosX, endPosY, color) => mod._null0_draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color._address)
  // Draw a filled rectangle on an image
  api.draw_rectangle_on_image = (destination, posX, posY, width, height, color) => mod._null0_draw_rectangle_on_image(destination, posX, posY, width, height, color._address)
  // Draw a filled triangle on an image
  api.draw_triangle_on_image = (destination, x1, y1, x2, y2, x3, y3, color) => mod._null0_draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color._address)
  // Draw a filled ellipse on an image
  api.draw_ellipse_on_image = (destination, centerX, centerY, radiusX, radiusY, color) => mod._null0_draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color._address)
  // Draw a circle on an image
  api.draw_circle_on_image = (destination, centerX, centerY, radius, color) => mod._null0_draw_circle_on_image(destination, centerX, centerY, radius, color._address)
  // Draw a filled polygon on an image
  api.draw_polygon_on_image = (destination, points, numPoints, color) => mod._null0_draw_polygon_on_image(destination, points, numPoints, color._address)
  // Draw several lines on an image
  api.draw_polyline_on_image = (destination, points, numPoints, color) => mod._null0_draw_polyline_on_image(destination, points, numPoints, color._address)
  // Draw a filled round-rectangle on an image
  api.draw_rectangle_rounded_on_image = (destination, x, y, width, height, cornerRadius, color) => mod._null0_draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color._address)
  // Draw an image on an image
  api.draw_image_on_image = (destination, src, posX, posY) => mod._null0_draw_image_on_image(destination, src, posX, posY)
  // Draw a tinted image on an image
  api.draw_image_tint_on_image = (destination, src, posX, posY, tint) => mod._null0_draw_image_tint_on_image(destination, src, posX, posY, tint._address)
  // Draw an image, rotated, on an image
  api.draw_image_rotated_on_image = (destination, src, posX, posY, degrees, offsetX, offsetY, filter) => mod._null0_draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter)
  // Draw an image, flipped, on an image
  api.draw_image_flipped_on_image = (destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) => mod._null0_draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal)
  // Draw an image, scaled, on an image
  api.draw_image_scaled_on_image = (destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) => mod._null0_draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter)
  // Draw some text on an image
  api.draw_text_on_image = (destination, font, text, posX, posY, color) => mod._null0_draw_text_on_image(destination, font, mod.stringToNewUTF8(text), posX, posY, color._address)
  // Draw a 1px outlined rectangle on the screen
  api.draw_rectangle_outline = (posX, posY, width, height, color) => mod._null0_draw_rectangle_outline(posX, posY, width, height, color._address)
  // Draw a 1px outlined triangle on the screen
  api.draw_triangle_outline = (x1, y1, x2, y2, x3, y3, color) => mod._null0_draw_triangle_outline(x1, y1, x2, y2, x3, y3, color._address)
  // Draw a 1px outlined ellipse on the screen
  api.draw_ellipse_outline = (centerX, centerY, radiusX, radiusY, color) => mod._null0_draw_ellipse_outline(centerX, centerY, radiusX, radiusY, color._address)
  // Draw a 1px outlined circle on the screen
  api.draw_circle_outline = (centerX, centerY, radius, color) => mod._null0_draw_circle_outline(centerX, centerY, radius, color._address)
  // Draw a 1px outlined polygon on the screen
  api.draw_polygon_outline = (points, numPoints, color) => mod._null0_draw_polygon_outline(points, numPoints, color._address)
  // Draw a 1px outlined arc on the screen
  api.draw_arc_outline = (centerX, centerY, radius, startAngle, endAngle, segments, color) => mod._null0_draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, color._address)
  // Draw a 1px outlined round-rectangle on the screen
  api.draw_rectangle_rounded_outline = (x, y, width, height, cornerRadius, color) => mod._null0_draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, color._address)
  // Draw a 1px outlined rectangle on an image
  api.draw_rectangle_outline_on_image = (destination, posX, posY, width, height, color) => mod._null0_draw_rectangle_outline_on_image(destination, posX, posY, width, height, color._address)
  // Draw a 1px outlined triangle on an image
  api.draw_triangle_outline_on_image = (destination, x1, y1, x2, y2, x3, y3, color) => mod._null0_draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, color._address)
  // Draw a 1px outlined ellipse on an image
  api.draw_ellipse_outline_on_image = (destination, centerX, centerY, radiusX, radiusY, color) => mod._null0_draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, color._address)
  // Draw a 1px outlined circle on an image
  api.draw_circle_outline_on_image = (destination, centerX, centerY, radius, color) => mod._null0_draw_circle_outline_on_image(destination, centerX, centerY, radius, color._address)
  // Draw a 1px outlined polygon on an image
  api.draw_polygon_outline_on_image = (destination, points, numPoints, color) => mod._null0_draw_polygon_outline_on_image(destination, points, numPoints, color._address)
  // Draw a 1px outlined round-rectangle on an image
  api.draw_rectangle_rounded_outline_on_image = (destination, x, y, width, height, cornerRadius, color) => mod._null0_draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, color._address)

  /////////// FILESYSTEM ///////////


  // Read a file from cart
  api.file_read = (filename, bytesRead) => mod._null0_file_read(mod.stringToNewUTF8(filename), bytesRead)
  // Write a file to persistant storage
  api.file_write = (filename, data, byteSize) => mod._null0_file_write(mod.stringToNewUTF8(filename), data, byteSize)
  // Embed memory as a file
  api.file_embed = (filename, data, byteSize) => mod._null0_file_embed(mod.stringToNewUTF8(filename), data, byteSize)

  /////////// COLORS ///////////


  // Tint a color with another color
  api.color_tint = (color, tint) => {
    const ret = new Color()
    mod._null0_color_tint(ret._address, color._address, tint._address)
    return ret
  }
  // Fade a color
  api.color_fade = (color, alpha) => {
    const ret = new Color()
    mod._null0_color_fade(ret._address, color._address, alpha)
    return ret
  }
  // Change the brightness of a color
  api.color_brightness = (color, factor) => {
    const ret = new Color()
    mod._null0_color_brightness(ret._address, color._address, factor)
    return ret
  }
  // Invert a color
  api.color_invert = (color) => {
    const ret = new Color()
    mod._null0_color_invert(ret._address, color._address)
    return ret
  }
  // Blend 2 colors together
  api.color_alpha_blend = (dst, src) => {
    const ret = new Color()
    mod._null0_color_alpha_blend(ret._address, dst._address, src._address)
    return ret
  }
  // color_contrast
  api.color_contrast = (color, contrast) => {
    const ret = new Color()
    mod._null0_color_contrast(ret._address, color._address, contrast)
    return ret
  }
  // Interpolate colors
  api.color_bilinear_interpolate = (color00, color01, color10, color11, coordinateX, coordinateY) => {
    const ret = new Color()
    mod._null0_color_bilinear_interpolate(ret._address, color00._address, color01._address, color10._address, color11._address, coordinateX, coordinateY)
    return ret
  }

}

