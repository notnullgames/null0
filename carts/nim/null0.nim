import macros

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
      newLit("__attribute__((export_name(\"" & procName & "\"))) $# $#$#")
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
      newLit("__attribute__((import_module(\"null0\"), import_name(\"" &
          procName & "\"))) $# $#$#")
    )

  # Add pragmas to the procedure
  if newProc[4].kind == nnkEmpty:
    newProc[4] = nnkPragma.newTree(importcPragma, cdeclPragma, codeGenPragma)
  else:
    newProc[4].add importcPragma
    newProc[4].add cdeclPragma
    newProc[4].add codeGenPragma

  result = newProc

type
  SfxParams* {.byref, packed.} = object
    randSeed*: uint32
    waveType*: cint
    attackTime*: cfloat
    sustainTime*: cfloat
    sustainPunch*: cfloat
    decayTime*: cfloat
    startFrequency*: cfloat
    minFrequency*: cfloat
    slide*: cfloat
    deltaSlide*: cfloat
    vibratoDepth*: cfloat
    vibratoSpeed*: cfloat
    changeAmount*: cfloat
    changeSpeed*: cfloat
    squareDuty*: cfloat
    dutySweep*: cfloat
    repeatSpeed*: cfloat
    phaserOffset*: cfloat
    phaserSweep*: cfloat
    lpfCutoff*: cfloat
    lpfCutoffSweep*: cfloat
    lpfResonance*: cfloat
    hpfCutoff*: cfloat
    hpfCutoffSweep*: cfloat

  Dimensions* {.byref, packed.} = object
    width*: cint
    height*: cint

  Vector* {.byref, packed.} = object
    x*: cint
    y*: cint

  Rectangle* {.byref, packed.} = object
    x*: cint
    y*: cint
    width*: cint
    height*: cint

  Color* {.byref, packed.} = object
    r*: uint8
    g*: uint8
    b*: uint8
    a*: uint8

  ImageFilter* = enum
    FILTER_NEARESTNEIGHBOR = 0,
    FILTER_BILINEAR = 1,
    FILTER_SMOOTH = 2

  SfxPresetType* = enum
    SFX_COIN = 0,
    SFX_LASER = 1,
    SFX_EXPLOSION = 2,
    SFX_POWERUP = 3,
    SFX_HURT = 4,
    SFX_JUMP = 5,
    SFX_SELECT = 6,
    SFX_SYNTH = 7

  Key* = enum
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

  GamepadButton* = enum
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

  MouseButton* = enum
    MOUSE_BUTTON_UNKNOWN = 0,
    MOUSE_BUTTON_LEFT = 1,
    MOUSE_BUTTON_RIGHT = 2,
    MOUSE_BUTTON_MIDDLE = 3

# Import functions from null0 module with proper C attributes

# Colors functions
proc color_tint*(color: Color, tint: Color): Color {.null0_import.}
proc color_fade*(color: Color, alpha: cfloat): Color {.null0_import.}
proc color_brightness*(color: Color, factor: cfloat): Color {.null0_import.}
proc color_invert*(color: Color): Color {.null0_import.}
proc color_alpha_blend*(dst: Color, src: Color): Color {.null0_import.}
proc color_contrast*(color: Color, contrast: cfloat): Color {.null0_import.}
proc color_bilinear_interpolate*(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: cfloat, coordinateY: cfloat): Color {.null0_import.}

# Graphics functions
proc new_image*(width: cint, height: cint, color: Color): uint32 {.null0_import.}
proc image_copy*(image: uint32): uint32 {.null0_import.}
proc image_subimage*(image: uint32, x: cint, y: cint, width: cint, height: cint): uint32 {.null0_import.}
proc clear*(color: Color) {.null0_import.}
proc draw_point*(x: cint, y: cint, color: Color) {.null0_import.}
proc draw_line*(startPosX: cint, startPosY: cint, endPosX: cint, endPosY: cint, color: Color) {.null0_import.}
proc draw_rectangle*(posX: cint, posY: cint, width: cint, height: cint, color: Color) {.null0_import.}
proc draw_triangle*(x1: cint, y1: cint, x2: cint, y2: cint, x3: cint, y3: cint, color: Color) {.null0_import.}
proc draw_ellipse*(centerX: cint, centerY: cint, radiusX: cint, radiusY: cint, color: Color) {.null0_import.}
proc draw_circle*(centerX: cint, centerY: cint, radius: cint, color: Color) {.null0_import.}
proc draw_polygon*(points: ptr Vector, numPoints: cint, color: Color) {.null0_import.}
proc draw_arc*(centerX: cint, centerY: cint, radius: cfloat, startAngle: cfloat, endAngle: cfloat, segments: cint, color: Color) {.null0_import.}
proc draw_rectangle_rounded*(x: cint, y: cint, width: cint, height: cint, cornerRadius: cint, color: Color) {.null0_import.}
proc draw_image*(src: uint32, posX: cint, posY: cint) {.null0_import.}
proc draw_image_tint*(src: uint32, posX: cint, posY: cint, tint: Color) {.null0_import.}
proc draw_image_rotated*(src: uint32, posX: cint, posY: cint, degrees: cfloat, offsetX: cfloat, offsetY: cfloat, filter: ImageFilter) {.null0_import.}
proc draw_image_flipped*(src: uint32, posX: cint, posY: cint, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) {.null0_import.}
proc draw_image_scaled*(src: uint32, posX: cint, posY: cint, scaleX: cfloat, scaleY: cfloat, offsetX: cfloat, offsetY: cfloat, filter: ImageFilter) {.null0_import.}
proc draw_text*(font: uint32, text: cstring, posX: cint, posY: cint, color: Color) {.null0_import.}
proc save_image*(image: uint32, filename: cstring) {.null0_import.}
proc load_image*(filename: cstring): uint32 {.null0_import.}
proc image_resize*(image: uint32, newWidth: cint, newHeight: cint, filter: ImageFilter): uint32 {.null0_import.}
proc image_scale*(image: uint32, scaleX: cfloat, scaleY: cfloat, filter: ImageFilter): uint32 {.null0_import.}
proc image_color_replace*(image: uint32, color: Color, replace: Color) {.null0_import.}
proc image_color_tint*(image: uint32, color: Color) {.null0_import.}
proc image_color_fade*(image: uint32, alpha: cfloat) {.null0_import.}
proc font_copy*(font: uint32): uint32 {.null0_import.}
proc font_scale*(font: uint32, scaleX: cfloat, scaleY: cfloat, filter: ImageFilter): uint32 {.null0_import.}
proc load_font_bmf*(filename: cstring, characters: cstring): uint32 {.null0_import.}
proc load_font_bmf_from_image*(image: uint32, characters: cstring): uint32 {.null0_import.}
proc measure_text*(font: uint32, text: cstring, textLength: cint): Dimensions {.null0_import.}
proc measure_image*(image: uint32): Dimensions {.null0_import.}
proc load_font_tty*(filename: cstring, glyphWidth: cint, glyphHeight: cint, characters: cstring): uint32 {.null0_import.}
proc load_font_tty_from_image*(image: uint32, glyphWidth: cint, glyphHeight: cint, characters: cstring): uint32 {.null0_import.}
proc load_font_ttf*(filename: cstring, fontSize: cint): uint32 {.null0_import.}
proc image_color_invert*(image: uint32) {.null0_import.}
proc image_alpha_border*(image: uint32, threshold: cfloat): Rectangle {.null0_import.}
proc image_crop*(image: uint32, x: cint, y: cint, width: cint, height: cint) {.null0_import.}
proc image_alpha_crop*(image: uint32, threshold: cfloat) {.null0_import.}
proc image_color_brightness*(image: uint32, factor: cfloat) {.null0_import.}
proc image_flip*(image: uint32, horizontal: bool, vertical: bool) {.null0_import.}
proc image_color_contrast*(image: uint32, contrast: cfloat) {.null0_import.}
proc image_alpha_mask*(image: uint32, alphaMask: uint32, posX: cint, posY: cint) {.null0_import.}
proc image_rotate*(image: uint32, degrees: cfloat, filter: ImageFilter): uint32 {.null0_import.}
proc image_gradient*(width: cint, height: cint, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color): uint32 {.null0_import.}
proc unload_image*(image: uint32) {.null0_import.}
proc unload_font*(font: uint32) {.null0_import.}
proc clear_image*(destination: uint32, color: Color) {.null0_import.}
proc draw_point_on_image*(destination: uint32, x: cint, y: cint, color: Color) {.null0_import.}
proc draw_line_on_image*(destination: uint32, startPosX: cint, startPosY: cint, endPosX: cint, endPosY: cint, color: Color) {.null0_import.}
proc draw_rectangle_on_image*(destination: uint32, posX: cint, posY: cint, width: cint, height: cint, color: Color) {.null0_import.}
proc draw_triangle_on_image*(destination: uint32, x1: cint, y1: cint, x2: cint, y2: cint, x3: cint, y3: cint, color: Color) {.null0_import.}
proc draw_ellipse_on_image*(destination: uint32, centerX: cint, centerY: cint, radiusX: cint, radiusY: cint, color: Color) {.null0_import.}
proc draw_circle_on_image*(destination: uint32, centerX: cint, centerY: cint, radius: cint, color: Color) {.null0_import.}
proc draw_polygon_on_image*(destination: uint32, points: ptr Vector, numPoints: cint, color: Color) {.null0_import.}
proc draw_rectangle_rounded_on_image*(destination: uint32, x: cint, y: cint, width: cint, height: cint, cornerRadius: cint, color: Color) {.null0_import.}
proc draw_image_on_image*(destination: uint32, src: uint32, posX: cint, posY: cint) {.null0_import.}
proc draw_image_tint_on_image*(destination: uint32, src: uint32, posX: cint, posY: cint, tint: Color) {.null0_import.}
proc draw_image_rotated_on_image*(destination: uint32, src: uint32, posX: cint, posY: cint, degrees: cfloat, offsetX: cfloat, offsetY: cfloat, filter: ImageFilter) {.null0_import.}
proc draw_image_flipped_on_image*(destination: uint32, src: uint32, posX: cint, posY: cint, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) {.null0_import.}
proc draw_image_scaled_on_image*(destination: uint32, src: uint32, posX: cint, posY: cint, scaleX: cfloat, scaleY: cfloat, offsetX: cfloat, offsetY: cfloat, filter: ImageFilter) {.null0_import.}
proc draw_text_on_image*(destination: uint32, font: uint32, text: cstring, posX: cint, posY: cint, color: Color) {.null0_import.}
proc draw_rectangle_outline*(posX: cint, posY: cint, width: cint, height: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_triangle_outline*(x1: cint, y1: cint, x2: cint, y2: cint, x3: cint, y3: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_ellipse_outline*(centerX: cint, centerY: cint, radiusX: cint, radiusY: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_circle_outline*(centerX: cint, centerY: cint, radius: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_polygon_outline*(points: ptr Vector, numPoints: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_arc_outline*(centerX: cint, centerY: cint, radius: cfloat, startAngle: cfloat, endAngle: cfloat, segments: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_rectangle_rounded_outline*(x: cint, y: cint, width: cint, height: cint, cornerRadius: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_rectangle_outline_on_image*(destination: uint32, posX: cint, posY: cint, width: cint, height: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_triangle_outline_on_image*(destination: uint32, x1: cint, y1: cint, x2: cint, y2: cint, x3: cint, y3: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_ellipse_outline_on_image*(destination: uint32, centerX: cint, centerY: cint, radiusX: cint, radiusY: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_circle_outline_on_image*(destination: uint32, centerX: cint, centerY: cint, radius: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_polygon_outline_on_image*(destination: uint32, points: ptr Vector, numPoints: cint, thickness: cint, color: Color) {.null0_import.}
proc draw_rectangle_rounded_outline_on_image*(destination: uint32, x: cint, y: cint, width: cint, height: cint, cornerRadius: cint, thickness: cint, color: Color) {.null0_import.}

# Input functions
proc key_pressed*(key: Key): bool {.null0_import.}
proc key_down*(key: Key): bool {.null0_import.}
proc key_released*(key: Key): bool {.null0_import.}
proc key_up*(key: Key): bool {.null0_import.}
proc gamepad_button_pressed*(gamepad: cint, button: GamepadButton): bool {.null0_import.}
proc gamepad_button_down*(gamepad: cint, button: GamepadButton): bool {.null0_import.}
proc gamepad_button_released*(gamepad: cint, button: GamepadButton): bool {.null0_import.}
proc mouse_position*(): Vector {.null0_import.}
proc mouse_button_pressed*(button: MouseButton): bool {.null0_import.}
proc mouse_button_down*(button: MouseButton): bool {.null0_import.}
proc mouse_button_released*(button: MouseButton): bool {.null0_import.}
proc mouse_button_up*(button: MouseButton): bool {.null0_import.}

# Sound functions
proc load_sound*(filename: cstring): uint32 {.null0_import.}
proc play_sound*(sound: uint32, loop: bool) {.null0_import.}
proc stop_sound*(sound: uint32) {.null0_import.}
proc unload_sound*(sound: uint32) {.null0_import.}
proc tts_sound*(text: cstring, phonetic: bool, pitch: cint, speed: cint, throat: cint, mouth: cint, sing: bool): uint32 {.null0_import.}
proc sfx_sound*(params: SfxParams): uint32 {.null0_import.}
proc sfx_generate*(`type`: SfxPresetType): SfxParams {.null0_import.}

# Types functions

# Utilities functions
proc current_time*(): uint64 {.null0_import.}
proc delta_time*(): cfloat {.null0_import.}
proc random_int*(min: cint, max: cint): cint {.null0_import.}
proc random_seed_get*(): uint64 {.null0_import.}
proc random_seed_set*(seed: uint64) {.null0_import.}

# this removes errors about nop main
proc main*(argc: cint, argv: ptr cstring): cint {.wasm.} =
  return 0

const
  SCREEN* = 0
  SCREEN_WIDTH* = 640
  SCREEN_HEIGHT* = 480
  FONT_DEFAULT* = 0

  LIGHTGRAY* = Color(r: 200, g: 200, b: 200, a: 255)
  GRAY* = Color(r: 130, g: 130, b: 130, a: 255)
  DARKGRAY* = Color(r: 80, g: 80, b: 80, a: 255)
  YELLOW* = Color(r: 253, g: 249, b: 0, a: 255)
  GOLD* = Color(r: 255, g: 203, b: 0, a: 255)
  ORANGE* = Color(r: 255, g: 161, b: 0, a: 255)
  PINK* = Color(r: 255, g: 109, b: 194, a: 255)
  RED* = Color(r: 230, g: 41, b: 55, a: 255)
  MAROON* = Color(r: 190, g: 33, b: 55, a: 255)
  GREEN* = Color(r: 0, g: 228, b: 48, a: 255)
  LIME* = Color(r: 0, g: 158, b: 47, a: 255)
  DARKGREEN* = Color(r: 0, g: 117, b: 44, a: 255)
  SKYBLUE* = Color(r: 102, g: 191, b: 255, a: 255)
  BLUE* = Color(r: 0, g: 121, b: 241, a: 255)
  DARKBLUE* = Color(r: 0, g: 82, b: 172, a: 255)
  PURPLE* = Color(r: 200, g: 122, b: 255, a: 255)
  VIOLET* = Color(r: 135, g: 60, b: 190, a: 255)
  DARKPURPLE* = Color(r: 112, g: 31, b: 126, a: 255)
  BEIGE* = Color(r: 211, g: 176, b: 131, a: 255)
  BROWN* = Color(r: 127, g: 106, b: 79, a: 255)
  DARKBROWN* = Color(r: 76, g: 63, b: 47, a: 255)
  WHITE* = Color(r: 255, g: 255, b: 255, a: 255)
  BLACK* = Color(r: 0, g: 0, b: 0, a: 255)
  BLANK* = Color(r: 0, g: 0, b: 0, a: 0)
  MAGENTA* = Color(r: 255, g: 0, b: 255, a: 255)
  RAYWHITE* = Color(r: 245, g: 245, b: 245, a: 255)
