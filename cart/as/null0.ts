// this code will be injected at the top of your cart-code

export function malloc(size: usize, id: u32 = 0): usize {
   const pout = __new(size, id)
  __pin(pout)
  return pout
}

export function free(pointer:usize): void {
  __unpin(pointer)
}

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

class UsizePointer {
  constructor(){
    this.value = 0
  }
  value:usize
}

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
  constructor(filesize:i64 = 0, modtime:i64 = 0, createtime:i64 = 0, accesstime:i64 = 0, filetype:FileType = FileType.FILETYPE_REGULAR, readonly:boolean=false) {
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

// utilities

// Get system-time (ms) since unix epoch
@external("null0", "current_time")
declare function current_time(): u64

// Get the change in time (seconds) since the last update run
@external("null0", "delta_time")
declare function delta_time(): f32

// Get a random integer between 2 numbers
@external("null0", "random_int")
declare function random_int(min: i32, max: i32): i32

// sound

// Load a sound from a file in cart
@external("null0", "load_sound")
declare function _null0_load_sound(filename: ArrayBuffer): u32
function load_sound(filename: String):u32 {
  return _null0_load_sound(String.UTF8.encode(filename, true))
}

// Play a sound
@external("null0", "play_sound")
declare function play_sound(sound: u32, loop: boolean): void

// Stop a sound
@external("null0", "stop_sound")
declare function stop_sound(sound: u32): void

// Create a new sound-effect from some sfxr params
@external("null0", "new_sfx")
declare function new_sfx(params: SfxParams): u32

// Generate randomized preset sfxr params
@external("null0", "preset_sfx")
declare function preset_sfx(params: SfxParams, type: SfxPresetType): void

// Randomize sfxr params
@external("null0", "randomize_sfx")
declare function randomize_sfx(params: SfxParams, waveType: SfxWaveType): void

// Randomly mutate sfxr params
@external("null0", "mutate_sfx")
declare function mutate_sfx(params: SfxParams, range: f32, mask: u32): void

// Create a new sfxr from a .rfx file
@external("null0", "load_sfx")
declare function _null0_load_sfx(params: SfxParams, filename: ArrayBuffer): void
function load_sfx(params: SfxParams, filename: String):void {
  _null0_load_sfx(params, String.UTF8.encode(filename, true))
}

// Unload a sound
@external("null0", "unload_sound")
declare function unload_sound(sound: u32): void

// input

// Has the key been pressed? (tracks unpress/read correctly)
@external("null0", "key_pressed")
declare function key_pressed(key: Key): boolean

// Is the key currently down?
@external("null0", "key_down")
declare function key_down(key: Key): boolean

// Has the key been released? (tracks press/read correctly)
@external("null0", "key_released")
declare function key_released(key: Key): boolean

// Is the key currently up?
@external("null0", "key_up")
declare function key_up(key: Key): boolean

// Has the button been pressed? (tracks unpress/read correctly)
@external("null0", "gamepad_button_pressed")
declare function gamepad_button_pressed(gamepad: i32, button: GamepadButton): boolean

// Is the button currently down?
@external("null0", "gamepad_button_down")
declare function gamepad_button_down(gamepad: i32, button: GamepadButton): boolean

// Has the button been released? (tracks press/read correctly)
@external("null0", "gamepad_button_released")
declare function gamepad_button_released(gamepad: i32, button: GamepadButton): boolean

// Get current position of mouse
@external("null0", "mouse_position")
declare function _null0_mouse_position(ret:Vector): void
function mouse_position():Vector {
  const r = new Vector()
  _null0_mouse_position(r)
  return r
}

// Has the button been pressed? (tracks unpress/read correctly)
@external("null0", "mouse_button_pressed")
declare function mouse_button_pressed(button: MouseButton): boolean

// Is the button currently down?
@external("null0", "mouse_button_down")
declare function mouse_button_down(button: MouseButton): boolean

// Has the button been released? (tracks press/read correctly)
@external("null0", "mouse_button_released")
declare function mouse_button_released(button: MouseButton): boolean

// Is the button currently up?
@external("null0", "mouse_button_up")
declare function mouse_button_up(button: MouseButton): boolean

// graphics

// Create a new blank image
@external("null0", "new_image")
declare function new_image(width: i32, height: i32, color: Color): u32

// Copy an image to a new image
@external("null0", "image_copy")
declare function image_copy(image: u32): u32

// Create an image from a region of another image
@external("null0", "image_subimage")
declare function image_subimage(image: u32, x: i32, y: i32, width: i32, height: i32): u32

// Clear the screen
@external("null0", "clear")
declare function clear(color: Color): void

// Draw a single pixel on the screen
@external("null0", "draw_point")
declare function draw_point(x: i32, y: i32, color: Color): void

// Draw a line on the screen
@external("null0", "draw_line")
declare function draw_line(startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color): void

// Draw a filled rectangle on the screen
@external("null0", "draw_rectangle")
declare function draw_rectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color): void

// Draw a filled triangle on the screen
@external("null0", "draw_triangle")
declare function draw_triangle(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color): void

// Draw a filled ellipse on the screen
@external("null0", "draw_ellipse")
declare function draw_ellipse(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color): void

// Draw a filled circle on the screen
@external("null0", "draw_circle")
declare function draw_circle(centerX: i32, centerY: i32, radius: i32, color: Color): void

// Draw a filled polygon on the screen
@external("null0", "draw_polygon")
declare function draw_polygon(points: Array<Vector>, numPoints: i32, color: Color): void

// Draw several lines on the screen
@external("null0", "draw_polyline")
declare function draw_polyline(points: Array<Vector>, numPoints: i32, color: Color): void

// Draw a filled arc on the screen
@external("null0", "draw_arc")
declare function draw_arc(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, color: Color): void

// Draw a filled round-rectangle on the screen
@external("null0", "draw_rectangle_rounded")
declare function draw_rectangle_rounded(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color): void

// Draw an image on the screen
@external("null0", "draw_image")
declare function draw_image(src: u32, posX: i32, posY: i32): void

// Draw a tinted image on the screen
@external("null0", "draw_image_tint")
declare function draw_image_tint(src: u32, posX: i32, posY: i32, tint: Color): void

// Draw an image, rotated, on the screen
@external("null0", "draw_image_rotated")
declare function draw_image_rotated(src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void

// Draw an image, flipped, on the screen
@external("null0", "draw_image_flipped")
declare function draw_image_flipped(src: u32, posX: i32, posY: i32, flipHorizontal: boolean, flipVertical: boolean, flipDiagonal: boolean): void

// Draw an image, scaled, on the screen
@external("null0", "draw_image_scaled")
declare function draw_image_scaled(src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void

// Draw some text on the screen
@external("null0", "draw_text")
declare function _null0_draw_text(font: u32, text: ArrayBuffer, posX: i32, posY: i32, color: Color): void
function draw_text(font: u32, text: String, posX: i32, posY: i32, color: Color): void {
  _null0_draw_text(font, String.UTF8.encode(text, true), posX, posY, color)
}

// Save an image to persistant storage
@external("null0", "save_image")
declare function _null0_save_image(image: u32, filename: ArrayBuffer): void

// Load an image from a file in cart
@external("null0", "load_image")
declare function _null0_load_image(filename: ArrayBuffer): u32
function load_image(filename: string): u32 {
  return _null0_load_image(String.UTF8.encode(filename, true))
}

// Resize an image, in-place
@external("null0", "image_resize")
declare function image_resize(image: u32, newWidth: i32, newHeight: i32, offsetX: i32, offsetY: i32, fill: Color): void

// Scale an image, in-place
@external("null0", "image_scale")
declare function image_scale(image: u32, scaleX: f32, scaleY: f32, filter: ImageFilter): void

// Replace a color in an image, in-place
@external("null0", "image_color_replace")
declare function image_color_replace(image: u32, color: Color, replace: Color): void

// Tint a color in an image, in-place
@external("null0", "image_color_tint")
declare function image_color_tint(image: u32, color: Color): void

// Fade a color in an image, in-place
@external("null0", "image_color_fade")
declare function image_color_fade(image: u32, alpha: f32): void

// Copy a font to a new font
@external("null0", "font_copy")
declare function font_copy(font: u32): u32

// Scale a font, return a new font
@external("null0", "font_scale")
declare function font_scale(font: u32, scaleX: f32, scaleY: f32, filter: ImageFilter): u32

// Load a BMF font from a file in cart
@external("null0", "load_font_bmf")
declare function _null0_load_font_bmf(filename: ArrayBuffer, characters: ArrayBuffer): u32
function load_font_bmf(filename: string, characters: string): u32 {
  return _null0_load_font_bmf(String.UTF8.encode(filename, true), String.UTF8.encode(characters, true))
}

// Load a BMF font from an image
@external("null0", "load_font_bmf_from_image")
declare function _null0_load_font_bmf_from_image(image: u32, characters: ArrayBuffer): u32
function load_font_bmf_from_image(image: u32, characters: string): u32 {
  return _null0_load_font_bmf_from_image(image, String.UTF8.encode(characters, true))
}

// Measure the size of some text
@external("null0", "measure_text")
declare function _null0_measure_text(ret:Dimensions, font: u32, text: ArrayBuffer): void
function measure_text(font: u32, text: String): Dimensions {
  const r = new Dimensions()
  _null0_measure_text(r, font, String.UTF8.encode(text, true))
  return r
}

// Meaure an image (use 0 for screen)
@external("null0", "measure_image")
declare function measure_image(image: u32): Dimensions

// Load a TTY font from a file in cart
@external("null0", "load_font_tty")
declare function _null0_load_font_tty(filename: ArrayBuffer, glyphWidth: i32, glyphHeight: i32, characters: ArrayBuffer): u32
function load_font_tty(filename: string, glyphWidth: i32, glyphHeight: i32, characters: string): u32 {
  return _null0_load_font_tty(String.UTF8.encode(filename, true), glyphWidth, glyphHeight, String.UTF8.encode(characters, true))
}

// Load a TTY font from an image
@external("null0", "load_font_tty_from_image")
declare function _null0_load_font_tty_from_image(image: u32, glyphWidth: i32, glyphHeight: i32, characters: ArrayBuffer): u32
function load_font_tty_from_image(image: u32, glyphWidth: i32, glyphHeight: i32, characters: string): u32 {
  return _null0_load_font_tty_from_image(image, glyphWidth, glyphHeight, String.UTF8.encode(characters, true))
}

// Load a TTF font from a file in cart
@external("null0", "load_font_ttf")
declare function _null0_load_font_ttf(filename: ArrayBuffer, fontSize: i32): u32
function load_font_ttf(filename: string, fontSize: i32): u32 {
  return _null0_load_font_ttf(String.UTF8.encode(filename, true), fontSize)
}

// Invert the colors in an image, in-place
@external("null0", "image_color_invert")
declare function image_color_invert(image: u32): void

// Calculate a rectangle representing the available alpha border in an image
@external("null0", "image_alpha_border")
declare function _null0_image_alpha_border(ret:Rectangle, image: u32, threshold: f32): void
function image_alpha_border(ret:usize, image: u32, threshold: f32): Rectangle {
  const r = new Rectangle()
  _null0_image_alpha_border(r, image, threshold)
  return r
}

// Crop an image, in-place
@external("null0", "image_crop")
declare function image_crop(image: u32, x: i32, y: i32, width: i32, height: i32): void

// Crop an image based on the alpha border, in-place
@external("null0", "image_alpha_crop")
declare function image_alpha_crop(image: u32, threshold: f32): void

// Adjust the brightness of an image, in-place
@external("null0", "image_color_brightness")
declare function image_color_brightness(image: u32, factor: f32): void

// Flip an image, in-place
@external("null0", "image_flip")
declare function image_flip(image: u32, horizontal: boolean, vertical: boolean): void

// Change the contrast of an image, in-place
@external("null0", "image_color_contrast")
declare function image_color_contrast(image: u32, contrast: f32): void

// Use an image as an alpha-mask on another image
@external("null0", "image_alpha_mask")
declare function image_alpha_mask(image: u32, alphaMask: u32, posX: i32, posY: i32): void

// Create a new image, rotating another image
@external("null0", "image_rotate")
declare function image_rotate(image: u32, degrees: f32, filter: ImageFilter): u32

// Create a new image of a gradient
@external("null0", "image_gradient")
declare function image_gradient(width: i32, height: i32, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color): u32

// Unload an image
@external("null0", "unload_image")
declare function unload_image(image: u32): void

// Unload a font
@external("null0", "unload_font")
declare function unload_font(font: u32): void

// Clear an image
@external("null0", "clear_on_image")
declare function clear_on_image(destination: u32, color: Color): void

// Draw a single pixel on an image
@external("null0", "draw_point_on_image")
declare function draw_point_on_image(destination: u32, x: i32, y: i32, color: Color): void

// Draw a line on an image
@external("null0", "draw_line_on_image")
declare function draw_line_on_image(destination: u32, startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color): void

// Draw a filled rectangle on an image
@external("null0", "draw_rectangle_on_image")
declare function draw_rectangle_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, color: Color): void

// Draw a filled triangle on an image
@external("null0", "draw_triangle_on_image")
declare function draw_triangle_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color): void

// Draw a filled ellipse on an image
@external("null0", "draw_ellipse_on_image")
declare function draw_ellipse_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color): void

// Draw a circle on an image
@external("null0", "draw_circle_on_image")
declare function draw_circle_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, color: Color): void

// Draw a filled polygon on an image
@external("null0", "draw_polygon_on_image")
declare function draw_polygon_on_image(destination: u32, points: Array<Vector>, numPoints: i32, color: Color): void

// Draw several lines on an image
@external("null0", "draw_polyline_on_image")
declare function draw_polyline_on_image(destination: u32, points: Array<Vector>, numPoints: i32, color: Color): void

// Draw a filled round-rectangle on an image
@external("null0", "draw_rectangle_rounded_on_image")
declare function draw_rectangle_rounded_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color): void

// Draw an image on an image
@external("null0", "draw_image_on_image")
declare function draw_image_on_image(destination: u32, src: u32, posX: i32, posY: i32): void

// Draw a tinted image on an image
@external("null0", "draw_image_tint_on_image")
declare function draw_image_tint_on_image(destination: u32, src: u32, posX: i32, posY: i32, tint: Color): void

// Draw an image, rotated, on an image
@external("null0", "draw_image_rotated_on_image")
declare function draw_image_rotated_on_image(destination: u32, src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void

// Draw an image, flipped, on an image
@external("null0", "draw_image_flipped_on_image")
declare function draw_image_flipped_on_image(destination: u32, src: u32, posX: i32, posY: i32, flipHorizontal: boolean, flipVertical: boolean, flipDiagonal: boolean): void

// Draw an image, scaled, on an image
@external("null0", "draw_image_scaled_on_image")
declare function draw_image_scaled_on_image(destination: u32, src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void

// Draw some text on an image
@external("null0", "draw_text_on_image")
declare function draw_text_on_image(destination: u32, font: u32, text: string, posX: i32, posY: i32, color: Color): void

// Draw a 1px outlined rectangle on the screen
@external("null0", "draw_rectangle_outline")
declare function draw_rectangle_outline(posX: i32, posY: i32, width: i32, height: i32, color: Color): void

// Draw a 1px outlined triangle on the screen
@external("null0", "draw_triangle_outline")
declare function draw_triangle_outline(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color): void

// Draw a 1px outlined ellipse on the screen
@external("null0", "draw_ellipse_outline")
declare function draw_ellipse_outline(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color): void

// Draw a 1px outlined circle on the screen
@external("null0", "draw_circle_outline")
declare function draw_circle_outline(centerX: i32, centerY: i32, radius: i32, color: Color): void

// Draw a 1px outlined polygon on the screen
@external("null0", "draw_polygon_outline")
declare function draw_polygon_outline(points: Array<Vector>, numPoints: i32, color: Color): void

// Draw a 1px outlined arc on the screen
@external("null0", "draw_arc_outline")
declare function draw_arc_outline(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, color: Color): void

// Draw a 1px outlined round-rectangle on the screen
@external("null0", "draw_rectangle_rounded_outline")
declare function draw_rectangle_rounded_outline(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color): void

// Draw a 1px outlined rectangle on an image
@external("null0", "draw_rectangle_outline_on_image")
declare function draw_rectangle_outline_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, color: Color): void

// Draw a 1px outlined triangle on an image
@external("null0", "draw_triangle_outline_on_image")
declare function draw_triangle_outline_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color): void

// Draw a 1px outlined ellipse on an image
@external("null0", "draw_ellipse_outline_on_image")
declare function draw_ellipse_outline_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color): void

// Draw a 1px outlined circle on an image
@external("null0", "draw_circle_outline_on_image")
declare function draw_circle_outline_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, color: Color): void

// Draw a 1px outlined polygon on an image
@external("null0", "draw_polygon_outline_on_image")
declare function draw_polygon_outline_on_image(destination: u32, points: Array<Vector>, numPoints: i32, color: Color): void

// Draw a 1px outlined round-rectangle on an image
@external("null0", "draw_rectangle_rounded_outline_on_image")
declare function draw_rectangle_rounded_outline_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color): void

// filesystem

// Read a file from cart (or local persistant)
@external("null0", "file_read")
declare function _null0_file_read(filename: ArrayBuffer, byteSize:UsizePointer, retBytes:ArrayBuffer): void
function file_read(filename: string): ArrayBuffer {
  const i = file_info(filename)
  const ret = new ArrayBuffer(<i32>i.filesize)
  const b = new UsizePointer()
  _null0_file_read(String.UTF8.encode(filename, true), b, ret)
  return ret
}

// Write a file to persistant storage
@external("null0", "file_write")
declare function _null0_file_write(filename: ArrayBuffer, data: ArrayBuffer, byteSize: u32): boolean
function file_write(filename: string, data: ArrayBuffer): boolean {
  return _null0_file_write(String.UTF8.encode(filename, true), data, data.byteLength)
}

// Write a file to persistant storage, appending to the end
@external("null0", "file_append")
declare function _null0_file_append(filename: ArrayBuffer, data: ArrayBuffer, byteSize: u32): boolean
function file_append(filename: string, data: ArrayBuffer): boolean {
  return _null0_file_append(String.UTF8.encode(filename, true), data, data.byteLength)
}

// Get info about a single file
@external("null0", "file_info")
declare function _null0_file_info(ret:FileInfo, filename: ArrayBuffer): void
function file_info(filename:string): FileInfo {
  const r = new FileInfo()
  _null0_file_info(r, String.UTF8.encode(filename, true))
  return r
}

// Get the user's writable dir (where file writes or appends go)
@external("null0", "get_write_dir")
declare function _null0_get_write_dir(): ArrayBuffer
function get_write_dir(): string {
  return String.UTF8.decode(_null0_get_write_dir())
}

// colors

// Tint a color with another color
@external("null0", "color_tint")
declare function _null0_color_tint(ret:Color, color: Color, tint: Color): void
function color_tint(color: Color, tint: Color): Color {
  const r = new Color()
  _null0_color_tint(r, color, tint)
  return r
}

// Fade a color
@external("null0", "color_fade")
declare function _null0_color_fade(ret:Color, color: Color, alpha: f32): void
function color_fade(color: Color, alpha: f32):Color {
  const r = new Color()
  _null0_color_fade(r, color, alpha)
  return r
}

// Change the brightness of a color
@external("null0", "color_brightness")
declare function _null0_color_brightness(ret:Color, color: Color, factor: f32): void
function color_brightness(color: Color, factor: f32):Color {
  const r = new Color()
  _null0_color_brightness(r, color, factor)
  return r
}

// Invert a color
@external("null0", "color_invert")
declare function _null0_color_invert(ret:Color, color: Color): void
function color_invert(color: Color):Color {
  const r = new Color()
  _null0_color_invert(r, color)
  return r
}

// Blend 2 colors together
@external("null0", "color_alpha_blend")
declare function _null0_color_alpha_blend(ret:Color, dst: Color, src: Color): void
function color_alpha_blend(dst: Color, src: Color): Color {
  const r = new Color()
  _null0_color_alpha_blend(r, dst, src)
  return r
}

// Change contrast of a color
@external("null0", "color_contrast")
declare function _null0_color_contrast(ret:Color, color: Color, contrast: f32): void
function color_contrast(color: Color, contrast: f32):Color {
  const r = new Color()
  _null0_color_contrast(r, color, contrast)
  return r
}

// Interpolate colors
@external("null0", "color_bilinear_interpolate")
declare function _null0_color_bilinear_interpolate(ret:Color, color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: f32, coordinateY: f32): void
function color_bilinear_interpolate(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: f32, coordinateY: f32): Color {
  const r = new Color()
  _null0_color_bilinear_interpolate(r, color00, color01, color10, color11, coordinateX, coordinateY)
  return r
}

