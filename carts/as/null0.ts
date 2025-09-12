// null0 - AssemblyScript bindings for the null0 fantasy console
//
// This module provides AssemblyScript bindings for the null0 fantasy console API.
// It allows you to create games that compile to WebAssembly and run in the null0 runtime.
//
// Usage:
//
// Create your cart by implementing the required callbacks:
//
// ```typescript
// import { clear, draw_circle, BLACK, RED } from "./null0";
//
// export function load(): void {
//     // Initialize your game
// }
//
// export function update(): void {
//     // Update game logic (60 FPS)
//     clear(BLACK);
//     draw_circle(100, 100, 50, RED);
// }
// ```

// Type definitions

/** Sfx parameters. */
@unmanaged
export class SfxParams {
  randSeed: u32;
  waveType: i32;
  attackTime: f32;
  sustainTime: f32;
  sustainPunch: f32;
  decayTime: f32;
  startFrequency: f32;
  minFrequency: f32;
  slide: f32;
  deltaSlide: f32;
  vibratoDepth: f32;
  vibratoSpeed: f32;
  changeAmount: f32;
  changeSpeed: f32;
  squareDuty: f32;
  dutySweep: f32;
  repeatSpeed: f32;
  phaserOffset: f32;
  phaserSweep: f32;
  lpfCutoff: f32;
  lpfCutoffSweep: f32;
  lpfResonance: f32;
  hpfCutoff: f32;
  hpfCutoffSweep: f32;

  constructor(randSeed: u32, waveType: i32, attackTime: f32, sustainTime: f32, sustainPunch: f32, decayTime: f32, startFrequency: f32, minFrequency: f32, slide: f32, deltaSlide: f32, vibratoDepth: f32, vibratoSpeed: f32, changeAmount: f32, changeSpeed: f32, squareDuty: f32, dutySweep: f32, repeatSpeed: f32, phaserOffset: f32, phaserSweep: f32, lpfCutoff: f32, lpfCutoffSweep: f32, lpfResonance: f32, hpfCutoff: f32, hpfCutoffSweep: f32) {
    this.randSeed = randSeed;
    this.waveType = waveType;
    this.attackTime = attackTime;
    this.sustainTime = sustainTime;
    this.sustainPunch = sustainPunch;
    this.decayTime = decayTime;
    this.startFrequency = startFrequency;
    this.minFrequency = minFrequency;
    this.slide = slide;
    this.deltaSlide = deltaSlide;
    this.vibratoDepth = vibratoDepth;
    this.vibratoSpeed = vibratoSpeed;
    this.changeAmount = changeAmount;
    this.changeSpeed = changeSpeed;
    this.squareDuty = squareDuty;
    this.dutySweep = dutySweep;
    this.repeatSpeed = repeatSpeed;
    this.phaserOffset = phaserOffset;
    this.phaserSweep = phaserSweep;
    this.lpfCutoff = lpfCutoff;
    this.lpfCutoffSweep = lpfCutoffSweep;
    this.lpfResonance = lpfResonance;
    this.hpfCutoff = hpfCutoff;
    this.hpfCutoffSweep = hpfCutoffSweep;
  }
}

/** The 2D size of something (width/height.) */
@unmanaged
export class Dimensions {
  width: i32;
  height: i32;

  constructor(width: i32, height: i32) {
    this.width = width;
    this.height = height;
  }
}

/** The 2D position of something (x/y.) */
@unmanaged
export class Vector {
  x: i32;
  y: i32;

  constructor(x: i32, y: i32) {
    this.x = x;
    this.y = y;
  }
}

/** The 2D position + size of something (x/y/w/h.) */
@unmanaged
export class Rectangle {
  x: i32;
  y: i32;
  width: i32;
  height: i32;

  constructor(x: i32, y: i32, width: i32, height: i32) {
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
  }
}

/** An RGBA color. */
@unmanaged
export class Color {
  r: u8;
  g: u8;
  b: u8;
  a: u8;

  constructor(r: u8, g: u8, b: u8, a: u8) {
    this.r = r;
    this.g = g;
    this.b = b;
    this.a = a;
  }
}

/** Potential image-filtering techniques for scale/etc. */
export enum ImageFilter {
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR = 1,
  FILTER_SMOOTH = 2,
}

/** Represents a Sfx preset type. */
export enum SfxPresetType {
  SFX_COIN = 0,
  SFX_LASER = 1,
  SFX_EXPLOSION = 2,
  SFX_POWERUP = 3,
  SFX_HURT = 4,
  SFX_JUMP = 5,
  SFX_SELECT = 6,
  SFX_SYNTH = 7,
}

/** Represents a keyboard key. */
export enum Key {
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
}

/** Represents a gamepad button. */
export enum GamepadButton {
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
  GAMEPAD_BUTTON_RIGHT_THUMB = 17,
}

/** Represents a mouse button. */
export enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3,
}

// Screen and font constants
export const SCREEN: u32 = 0;
export const SCREEN_WIDTH: i32 = 640;
export const SCREEN_HEIGHT: i32 = 480;
export const FONT_DEFAULT: u32 = 0;

// Color constants
export const LIGHTGRAY: Color = new Color(200, 200, 200, 255);
export const GRAY: Color = new Color(130, 130, 130, 255);
export const DARKGRAY: Color = new Color(80, 80, 80, 255);
export const YELLOW: Color = new Color(253, 249, 0, 255);
export const GOLD: Color = new Color(255, 203, 0, 255);
export const ORANGE: Color = new Color(255, 161, 0, 255);
export const PINK: Color = new Color(255, 109, 194, 255);
export const RED: Color = new Color(230, 41, 55, 255);
export const MAROON: Color = new Color(190, 33, 55, 255);
export const GREEN: Color = new Color(0, 228, 48, 255);
export const LIME: Color = new Color(0, 158, 47, 255);
export const DARKGREEN: Color = new Color(0, 117, 44, 255);
export const SKYBLUE: Color = new Color(102, 191, 255, 255);
export const BLUE: Color = new Color(0, 121, 241, 255);
export const DARKBLUE: Color = new Color(0, 82, 172, 255);
export const PURPLE: Color = new Color(200, 122, 255, 255);
export const VIOLET: Color = new Color(135, 60, 190, 255);
export const DARKPURPLE: Color = new Color(112, 31, 126, 255);
export const BEIGE: Color = new Color(211, 176, 131, 255);
export const BROWN: Color = new Color(127, 106, 79, 255);
export const DARKBROWN: Color = new Color(76, 63, 47, 255);
export const WHITE: Color = new Color(255, 255, 255, 255);
export const BLACK: Color = new Color(0, 0, 0, 255);
export const BLANK: Color = new Color(0, 0, 0, 0);
export const MAGENTA: Color = new Color(255, 0, 255, 255);
export const RAYWHITE: Color = new Color(245, 245, 245, 255);


// Import functions from null0 module

// Utilities functions
/** Get system-time (ms) since unix epoch. */
@external("null0", "current_time")
export declare function current_time(): u64;
/** Get the change in time (seconds) since the last update run. */
@external("null0", "delta_time")
export declare function delta_time(): f32;
/** Get a random integer between 2 numbers. */
@external("null0", "random_int")
export declare function random_int(min: i32, max: i32): i32;
/** Get the random-seed. */
@external("null0", "random_seed_get")
export declare function random_seed_get(): u64;
/** Set the random-seed. */
@external("null0", "random_seed_set")
export declare function random_seed_set(seed: u64): void;

// Types functions

// Sound functions
/** Load a sound from a file in cart. */
@external("null0", "load_sound")
export declare function load_sound(filename: usize): u32;
/** Play a sound. */
@external("null0", "play_sound")
export declare function play_sound(sound: u32, loop: bool): void;
/** Stop a sound. */
@external("null0", "stop_sound")
export declare function stop_sound(sound: u32): void;
/** Unload a sound. */
@external("null0", "unload_sound")
export declare function unload_sound(sound: u32): void;
/** Speak some text and return a sound. Set things to 0 for defaults. */
@external("null0", "tts_sound")
export declare function tts_sound(text: usize, phonetic: bool, pitch: i32, speed: i32, throat: i32, mouth: i32, sing: bool): u32;
/** Create Sfx sound. */
@external("null0", "sfx_sound")
export declare function sfx_sound(params: SfxParams): u32;
/** Create Sfx parameters. */
@external("null0", "sfx_generate")
export declare function sfx_generate(type: SfxPresetType): SfxParams;

// Input functions
/** Has the key been pressed? (tracks unpress/read correctly.) */
@external("null0", "key_pressed")
export declare function key_pressed(key: Key): bool;
/** Is the key currently down? */
@external("null0", "key_down")
export declare function key_down(key: Key): bool;
/** Has the key been released? (tracks press/read correctly.) */
@external("null0", "key_released")
export declare function key_released(key: Key): bool;
/** Is the key currently up? */
@external("null0", "key_up")
export declare function key_up(key: Key): bool;
/** Has the button been pressed? (tracks unpress/read correctly.) */
@external("null0", "gamepad_button_pressed")
export declare function gamepad_button_pressed(gamepad: i32, button: GamepadButton): bool;
/** Is the button currently down? */
@external("null0", "gamepad_button_down")
export declare function gamepad_button_down(gamepad: i32, button: GamepadButton): bool;
/** Has the button been released? (tracks press/read correctly.) */
@external("null0", "gamepad_button_released")
export declare function gamepad_button_released(gamepad: i32, button: GamepadButton): bool;
/** Get current position of mouse. */
@external("null0", "mouse_position")
export declare function mouse_position(): Vector;
/** Has the button been pressed? (tracks unpress/read correctly.) */
@external("null0", "mouse_button_pressed")
export declare function mouse_button_pressed(button: MouseButton): bool;
/** Is the button currently down? */
@external("null0", "mouse_button_down")
export declare function mouse_button_down(button: MouseButton): bool;
/** Has the button been released? (tracks press/read correctly.) */
@external("null0", "mouse_button_released")
export declare function mouse_button_released(button: MouseButton): bool;
/** Is the button currently up? */
@external("null0", "mouse_button_up")
export declare function mouse_button_up(button: MouseButton): bool;

// Graphics functions
/** Create a new blank image. */
@external("null0", "new_image")
export declare function new_image(width: i32, height: i32, color: Color): u32;
/** Copy an image to a new image. */
@external("null0", "image_copy")
export declare function image_copy(image: u32): u32;
/** Create an image from a region of another image. */
@external("null0", "image_subimage")
export declare function image_subimage(image: u32, x: i32, y: i32, width: i32, height: i32): u32;
/** Clear the screen. */
@external("null0", "clear")
export declare function clear(color: Color): void;
/** Draw a single pixel on the screen. */
@external("null0", "draw_point")
export declare function draw_point(x: i32, y: i32, color: Color): void;
/** Draw a line on the screen. */
@external("null0", "draw_line")
export declare function draw_line(startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color): void;
/** Draw a filled rectangle on the screen. */
@external("null0", "draw_rectangle")
export declare function draw_rectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color): void;
/** Draw a filled triangle on the screen. */
@external("null0", "draw_triangle")
export declare function draw_triangle(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color): void;
/** Draw a filled ellipse on the screen. */
@external("null0", "draw_ellipse")
export declare function draw_ellipse(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color): void;
/** Draw a filled circle on the screen. */
@external("null0", "draw_circle")
export declare function draw_circle(centerX: i32, centerY: i32, radius: i32, color: Color): void;
/** Draw a filled polygon on the screen. */
@external("null0", "draw_polygon")
export declare function draw_polygon(points: usize, numPoints: i32, color: Color): void;
/** Draw a filled arc on the screen. */
@external("null0", "draw_arc")
export declare function draw_arc(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, color: Color): void;
/** Draw a filled round-rectangle on the screen. */
@external("null0", "draw_rectangle_rounded")
export declare function draw_rectangle_rounded(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color): void;
/** Draw an image on the screen. */
@external("null0", "draw_image")
export declare function draw_image(src: u32, posX: i32, posY: i32): void;
/** Draw a tinted image on the screen. */
@external("null0", "draw_image_tint")
export declare function draw_image_tint(src: u32, posX: i32, posY: i32, tint: Color): void;
/** Draw an image, rotated, on the screen. */
@external("null0", "draw_image_rotated")
export declare function draw_image_rotated(src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void;
/** Draw an image, flipped, on the screen. */
@external("null0", "draw_image_flipped")
export declare function draw_image_flipped(src: u32, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool): void;
/** Draw an image, scaled, on the screen. */
@external("null0", "draw_image_scaled")
export declare function draw_image_scaled(src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void;
/** Draw some text on the screen. */
@external("null0", "draw_text")
export declare function draw_text(font: u32, text: usize, posX: i32, posY: i32, color: Color): void;
/** Save an image to persistant storage. */
@external("null0", "save_image")
export declare function save_image(image: u32, filename: usize): void;
/** Load an image from a file in cart. */
@external("null0", "load_image")
export declare function load_image(filename: usize): u32;
/** Resize an image, return copy. */
@external("null0", "image_resize")
export declare function image_resize(image: u32, newWidth: i32, newHeight: i32, filter: ImageFilter): u32;
/** Scale an image, return copy. */
@external("null0", "image_scale")
export declare function image_scale(image: u32, scaleX: f32, scaleY: f32, filter: ImageFilter): u32;
/** Replace a color in an image, in-place. */
@external("null0", "image_color_replace")
export declare function image_color_replace(image: u32, color: Color, replace: Color): void;
/** Tint a color in an image, in-place. */
@external("null0", "image_color_tint")
export declare function image_color_tint(image: u32, color: Color): void;
/** Fade a color in an image, in-place. */
@external("null0", "image_color_fade")
export declare function image_color_fade(image: u32, alpha: f32): void;
/** Copy a font to a new font. */
@external("null0", "font_copy")
export declare function font_copy(font: u32): u32;
/** Scale a font, return a new font. */
@external("null0", "font_scale")
export declare function font_scale(font: u32, scaleX: f32, scaleY: f32, filter: ImageFilter): u32;
/** Load a BMF font from a file in cart. */
@external("null0", "load_font_bmf")
export declare function load_font_bmf(filename: usize, characters: usize): u32;
/** Load a BMF font from an image. */
@external("null0", "load_font_bmf_from_image")
export declare function load_font_bmf_from_image(image: u32, characters: usize): u32;
/** Measure the size of some text. */
@external("null0", "measure_text")
export declare function measure_text(font: u32, text: usize, textLength: i32): Dimensions;
/** Meaure an image (use 0 for screen). */
@external("null0", "measure_image")
export declare function measure_image(image: u32): Dimensions;
/** Load a TTY font from a file in cart. */
@external("null0", "load_font_tty")
export declare function load_font_tty(filename: usize, glyphWidth: i32, glyphHeight: i32, characters: usize): u32;
/** Load a TTY font from an image. */
@external("null0", "load_font_tty_from_image")
export declare function load_font_tty_from_image(image: u32, glyphWidth: i32, glyphHeight: i32, characters: usize): u32;
/** Load a TTF font from a file in cart. */
@external("null0", "load_font_ttf")
export declare function load_font_ttf(filename: usize, fontSize: i32): u32;
/** Invert the colors in an image, in-place. */
@external("null0", "image_color_invert")
export declare function image_color_invert(image: u32): void;
/** Calculate a rectangle representing the available alpha border in an image. */
@external("null0", "image_alpha_border")
export declare function image_alpha_border(image: u32, threshold: f32): Rectangle;
/** Crop an image, in-place. */
@external("null0", "image_crop")
export declare function image_crop(image: u32, x: i32, y: i32, width: i32, height: i32): void;
/** Crop an image based on the alpha border, in-place. */
@external("null0", "image_alpha_crop")
export declare function image_alpha_crop(image: u32, threshold: f32): void;
/** Adjust the brightness of an image, in-place. */
@external("null0", "image_color_brightness")
export declare function image_color_brightness(image: u32, factor: f32): void;
/** Flip an image, in-place. */
@external("null0", "image_flip")
export declare function image_flip(image: u32, horizontal: bool, vertical: bool): void;
/** Change the contrast of an image, in-place. */
@external("null0", "image_color_contrast")
export declare function image_color_contrast(image: u32, contrast: f32): void;
/** Use an image as an alpha-mask on another image. */
@external("null0", "image_alpha_mask")
export declare function image_alpha_mask(image: u32, alphaMask: u32, posX: i32, posY: i32): void;
/** Create a new image, rotating another image. */
@external("null0", "image_rotate")
export declare function image_rotate(image: u32, degrees: f32, filter: ImageFilter): u32;
/** Create a new image of a gradient. */
@external("null0", "image_gradient")
export declare function image_gradient(width: i32, height: i32, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color): u32;
/** Unload an image. */
@external("null0", "unload_image")
export declare function unload_image(image: u32): void;
/** Unload a font. */
@external("null0", "unload_font")
export declare function unload_font(font: u32): void;
/** Clear an image. */
@external("null0", "clear_image")
export declare function clear_image(destination: u32, color: Color): void;
/** Draw a single pixel on an image. */
@external("null0", "draw_point_on_image")
export declare function draw_point_on_image(destination: u32, x: i32, y: i32, color: Color): void;
/** Draw a line on an image. */
@external("null0", "draw_line_on_image")
export declare function draw_line_on_image(destination: u32, startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color): void;
/** Draw a filled rectangle on an image. */
@external("null0", "draw_rectangle_on_image")
export declare function draw_rectangle_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, color: Color): void;
/** Draw a filled triangle on an image. */
@external("null0", "draw_triangle_on_image")
export declare function draw_triangle_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color): void;
/** Draw a filled ellipse on an image. */
@external("null0", "draw_ellipse_on_image")
export declare function draw_ellipse_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color): void;
/** Draw a circle on an image. */
@external("null0", "draw_circle_on_image")
export declare function draw_circle_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, color: Color): void;
/** Draw a filled polygon on an image. */
@external("null0", "draw_polygon_on_image")
export declare function draw_polygon_on_image(destination: u32, points: usize, numPoints: i32, color: Color): void;
/** Draw a filled round-rectangle on an image. */
@external("null0", "draw_rectangle_rounded_on_image")
export declare function draw_rectangle_rounded_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color): void;
/** Draw an image on an image. */
@external("null0", "draw_image_on_image")
export declare function draw_image_on_image(destination: u32, src: u32, posX: i32, posY: i32): void;
/** Draw a tinted image on an image. */
@external("null0", "draw_image_tint_on_image")
export declare function draw_image_tint_on_image(destination: u32, src: u32, posX: i32, posY: i32, tint: Color): void;
/** Draw an image, rotated, on an image. */
@external("null0", "draw_image_rotated_on_image")
export declare function draw_image_rotated_on_image(destination: u32, src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void;
/** Draw an image, flipped, on an image. */
@external("null0", "draw_image_flipped_on_image")
export declare function draw_image_flipped_on_image(destination: u32, src: u32, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool): void;
/** Draw an image, scaled, on an image. */
@external("null0", "draw_image_scaled_on_image")
export declare function draw_image_scaled_on_image(destination: u32, src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter): void;
/** Draw some text on an image. */
@external("null0", "draw_text_on_image")
export declare function draw_text_on_image(destination: u32, font: u32, text: usize, posX: i32, posY: i32, color: Color): void;
/** Draw a outlined (with thickness) rectangle on the screen. */
@external("null0", "draw_rectangle_outline")
export declare function draw_rectangle_outline(posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) triangle on the screen. */
@external("null0", "draw_triangle_outline")
export declare function draw_triangle_outline(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) ellipse on the screen. */
@external("null0", "draw_ellipse_outline")
export declare function draw_ellipse_outline(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) circle on the screen. */
@external("null0", "draw_circle_outline")
export declare function draw_circle_outline(centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) polygon on the screen. */
@external("null0", "draw_polygon_outline")
export declare function draw_polygon_outline(points: usize, numPoints: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) arc on the screen. */
@external("null0", "draw_arc_outline")
export declare function draw_arc_outline(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) round-rectangle on the screen. */
@external("null0", "draw_rectangle_rounded_outline")
export declare function draw_rectangle_rounded_outline(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) rectangle on an image. */
@external("null0", "draw_rectangle_outline_on_image")
export declare function draw_rectangle_outline_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) triangle on an image. */
@external("null0", "draw_triangle_outline_on_image")
export declare function draw_triangle_outline_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) ellipse on an image. */
@external("null0", "draw_ellipse_outline_on_image")
export declare function draw_ellipse_outline_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) circle on an image. */
@external("null0", "draw_circle_outline_on_image")
export declare function draw_circle_outline_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) polygon on an image. */
@external("null0", "draw_polygon_outline_on_image")
export declare function draw_polygon_outline_on_image(destination: u32, points: usize, numPoints: i32, thickness: i32, color: Color): void;
/** Draw a outlined (with thickness) round-rectangle on an image. */
@external("null0", "draw_rectangle_rounded_outline_on_image")
export declare function draw_rectangle_rounded_outline_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color): void;

// Colors functions
/** Tint a color with another color. */
@external("null0", "color_tint")
export declare function color_tint(color: Color, tint: Color): Color;
/** Fade a color. */
@external("null0", "color_fade")
export declare function color_fade(color: Color, alpha: f32): Color;
/** Change the brightness of a color. */
@external("null0", "color_brightness")
export declare function color_brightness(color: Color, factor: f32): Color;
/** Invert a color. */
@external("null0", "color_invert")
export declare function color_invert(color: Color): Color;
/** Blend 2 colors together. */
@external("null0", "color_alpha_blend")
export declare function color_alpha_blend(dst: Color, src: Color): Color;
/** Change contrast of a color. */
@external("null0", "color_contrast")
export declare function color_contrast(color: Color, contrast: f32): Color;
/** Interpolate colors. */
@external("null0", "color_bilinear_interpolate")
export declare function color_bilinear_interpolate(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: f32, coordinateY: f32): Color;

// Helper functions for working with Vector arrays
/** Convert StaticArray<Vector> to pointer for WASM FFI */
export function vectorArrayToPtr(vectors: StaticArray<Vector>): usize {
  return changetype<usize>(vectors);
}

// String conversion helpers for WASM FFI
/** Convert string to null-terminated C string pointer */
export function stringToPtr(str: string): usize {
  return changetype<usize>(String.UTF8.encode(str, true));
}