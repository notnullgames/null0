// This will generate the C host-interface

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

let code = ''
const exports = []

// map types in api to C types
function mapType (type) {
  if (['Font', 'Sound', 'Image'].includes(type)) {
    return 'u32'
  }
  if (type === 'string') {
    return 'char*'
  }
  if (type === 'string*') {
    return 'char**'
  }
  if (type === 'bytes') {
    return 'u8*'
  }
  return type
}

for (const type of Object.keys(api)) {
  code += `\n/////////// ${type.toUpperCase()} ///////////\n\n\n`
  for (const fun of Object.keys(api[type]).filter(f => !customFunctions.includes(f))) {
    exports.push(`_${fun}`)
    code += `// ${api[type][fun].description}
NULL0_IMPORT("${fun}")
${mapType(api[type][fun].returns)} ${fun}(${Object.keys(api[type][fun].args).map(a => `${mapType(api[type][fun].args[a])} ${a}`).join(', ')});

`
  }
}

const out = `// generated null0 cart-header for C

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define NULL0_EXPORT(n) __attribute__((export_name(n)))
#define NULL0_IMPORT(n) __attribute__((import_module("null0"), import_name(n)))

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;

NULL0_EXPORT("malloc")
void* _null0_malloc(size_t size) {
  return malloc(size);
}

NULL0_EXPORT("alloca")
void* _null0_alloca(size_t size) {
  return __builtin_alloca(size);
}

NULL0_EXPORT("free")
void _null0_free(void* ptr) {
  free(ptr);
}

typedef struct {
  u32 width;
  u32 height;
} Dimensions;

typedef struct {
  i32 x;
  i32 y;
} Vector;

typedef struct {
  i32 x;
  i32 y;
  i32 width;
  i32 height;
} Rectangle;

typedef struct {
  // Random seed used to generate the wave
  u32 randSeed;

  // Wave type (square, sawtooth, sine, noise)
  i32 waveType;

  // Wave envelope parameters
  f32 attackTime;
  f32 sustainTime;
  f32 sustainPunch;
  f32 decayTime;

  // Frequency parameters
  f32 startFrequency;
  f32 minFrequency;
  f32 slide;
  f32 deltaSlide;
  f32 vibratoDepth;
  f32 vibratoSpeed;

  // Tone change parameters
  f32 changeAmount;
  f32 changeSpeed;

  // Square wave parameters
  f32 squareDuty;
  f32 dutySweep;

  // Repeat parameters
  f32 repeatSpeed;

  // Phaser parameters
  f32 phaserOffset;
  f32 phaserSweep;

  // Filter parameters
  f32 lpfCutoff;
  f32 lpfCutoffSweep;
  f32 lpfResonance;
  f32 hpfCutoff;
  f32 hpfCutoffSweep;
} SfxParams;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

typedef enum ImageFilter {
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR,
  FILTER_SMOOTH
} ImageFilter;

typedef enum Key {
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
} Key;

typedef enum GamepadButton {
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
  GAMEPAD_BUTTON_RIGHT_THUMB,     // Gamepad joystick pressed button right
} GamepadButton;

typedef enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3,
} MouseButton;

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT
} SfxPresetType;

typedef enum SfxWaveType {
    SFX_SQUARE,
    SFX_SAWTOOTH,
    SFX_SINE,
    SFX_NOISE,
    SFX_TRIANGLE,
    SFX_PINK_NOISE
} SfxWaveType;

#define WIDTH 320
#define HEIGHT 240

Color LIGHTGRAY = (Color) {.r=200, .g=200, .b=200, .a=255};
Color GRAY = (Color) {.r=130, .g=130, .b=130, .a=255};
Color DARKGRAY = (Color) {.r=80, .g=80, .b=80, .a=255};
Color YELLOW = (Color) {.r=253, .g=249, .b=0, .a=255};
Color GOLD = (Color) {.r=255, .g=203, .b=0, .a=255};
Color ORANGE = (Color) {.r=255, .g=161, .b=0, .a=255};
Color PINK = (Color) {.r=255, .g=109, .b=194, .a=255};
Color RED = (Color) {.r=230, .g=41, .b=55, .a=255};
Color MAROON = (Color) {.r=190, .g=33, .b=55, .a=255};
Color GREEN = (Color) {.r=0, .g=228, .b=48, .a=255};
Color LIME = (Color) {.r=0, .g=158, .b=47, .a=255};
Color DARKGREEN = (Color) {.r=0, .g=117, .b=44, .a=255};
Color SKYBLUE = (Color) {.r=102, .g=191, .b=255, .a=255};
Color BLUE = (Color) {.r=0, .g=121, .b=241, .a=255};
Color DARKBLUE = (Color) {.r=0, .g=82, .b=172, .a=255};
Color PURPLE = (Color) {.r=200, .g=122, .b=255, .a=255};
Color VIOLET = (Color) {.r=135, .g=60, .b=190, .a=255};
Color DARKPURPLE = (Color) {.r=112, .g=31, .b=126, .a=255};
Color BEIGE = (Color) {.r=211, .g=176, .b=131, .a=255};
Color BROWN = (Color) {.r=127, .g=106, .b=79, .a=255};
Color DARKBROWN = (Color) {.r=76, .g=63, .b=47, .a=255};
Color WHITE = (Color) {.r=255, .g=255, .b=255, .a=255};
Color BLACK = (Color) {.r=0, .g=0, .b=0, .a=255};
Color BLANK = (Color) {.r=0, .g=0, .b=0, .a=0};
Color MAGENTA = (Color) {.r=255, .g=0, .b=255, .a=255};
Color RAYWHITE = (Color) {.r=245, .g=245, .b=245, .a=255};

// max-size for trace messages
#ifndef NULL0_TRACE_SIZE
#define NULL0_TRACE_SIZE 1024
#endif

NULL0_IMPORT("trace")
void _null0_trace_real(char* str);

char null0_traceBuffer[NULL0_TRACE_SIZE];

// Log a string (using printf-style)
void trace(const char *format, ...) {
  va_list args;
  va_start (args, format);
  vsnprintf (null0_traceBuffer, NULL0_TRACE_SIZE, format, args);
  va_end (args);
  _null0_trace_real(null0_traceBuffer);
}

${code}
`

await writeFile('headers/null0.h', out)
