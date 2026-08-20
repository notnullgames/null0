---@meta

-- null0 - lua definitions for the null0 fantasy console
--
-- GENERATED FILE - do not edit by hand. See tools/gen_cart_lua.js
--
-- The null0 API is available as plain globals in your cart - no require()
-- needed, same as the JS/python carts. This file is only here so editors
-- (any LuaLS-based one) can complete & check your cart:
--
-- ```lua
-- function load()
--   clear(BLUE)
--   draw_circle(100, 100, 50, RED)
-- end
-- ```

---Sfx parameters.
---@class SfxParams
---@field randSeed integer
---@field waveType integer
---@field attackTime number
---@field sustainTime number
---@field sustainPunch number
---@field decayTime number
---@field startFrequency number
---@field minFrequency number
---@field slide number
---@field deltaSlide number
---@field vibratoDepth number
---@field vibratoSpeed number
---@field changeAmount number
---@field changeSpeed number
---@field squareDuty number
---@field dutySweep number
---@field repeatSpeed number
---@field phaserOffset number
---@field phaserSweep number
---@field lpfCutoff number
---@field lpfCutoffSweep number
---@field lpfResonance number
---@field hpfCutoff number
---@field hpfCutoffSweep number

---The 2D size of something (width/height.)
---@class Dimensions
---@field width integer
---@field height integer

---The 2D position of something (x/y.)
---@class Vector
---@field x integer
---@field y integer

---The 2D position + size of something (x/y/w/h.)
---@class Rectangle
---@field x integer
---@field y integer
---@field width integer
---@field height integer

---An RGBA color.
---@class Color
---@field r integer
---@field g integer
---@field b integer
---@field a integer

-- COLORS

---Tint a color with another color.
---@param color Color
---@param tint Color
---@return Color
function color_tint(color, tint) end

---Fade a color.
---@param color Color
---@param alpha number
---@return Color
function color_fade(color, alpha) end

---Change the brightness of a color.
---@param color Color
---@param factor number
---@return Color
function color_brightness(color, factor) end

---Invert a color.
---@param color Color
---@return Color
function color_invert(color) end

---Blend 2 colors together.
---@param dst Color
---@param src Color
---@return Color
function color_alpha_blend(dst, src) end

---Change contrast of a color.
---@param color Color
---@param contrast number
---@return Color
function color_contrast(color, contrast) end

---Interpolate colors.
---@param color00 Color
---@param color01 Color
---@param color10 Color
---@param color11 Color
---@param coordinateX number
---@param coordinateY number
---@return Color
function color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY) end

-- GRAPHICS

---Create a new blank image.
---@param width integer
---@param height integer
---@param color Color
---@return integer
function new_image(width, height, color) end

---Copy an image to a new image.
---@param image integer
---@return integer
function image_copy(image) end

---Create an image from a region of another image.
---@param image integer
---@param x integer
---@param y integer
---@param width integer
---@param height integer
---@return integer
function image_subimage(image, x, y, width, height) end

---Clear the screen.
---@param color Color
function clear(color) end

---Draw a single pixel on the screen.
---@param x integer
---@param y integer
---@param color Color
function draw_point(x, y, color) end

---Draw a line on the screen.
---@param startPosX integer
---@param startPosY integer
---@param endPosX integer
---@param endPosY integer
---@param color Color
function draw_line(startPosX, startPosY, endPosX, endPosY, color) end

---Draw a filled rectangle on the screen.
---@param posX integer
---@param posY integer
---@param width integer
---@param height integer
---@param color Color
function draw_rectangle(posX, posY, width, height, color) end

---Draw a filled triangle on the screen.
---@param x1 integer
---@param y1 integer
---@param x2 integer
---@param y2 integer
---@param x3 integer
---@param y3 integer
---@param color Color
function draw_triangle(x1, y1, x2, y2, x3, y3, color) end

---Draw a filled ellipse on the screen.
---@param centerX integer
---@param centerY integer
---@param radiusX integer
---@param radiusY integer
---@param color Color
function draw_ellipse(centerX, centerY, radiusX, radiusY, color) end

---Draw a filled circle on the screen.
---@param centerX integer
---@param centerY integer
---@param radius integer
---@param color Color
function draw_circle(centerX, centerY, radius, color) end

---Draw a filled polygon on the screen.
---@param points Vector[]
---@param color Color
function draw_polygon(points, color) end

---Draw a filled arc on the screen.
---@param centerX integer
---@param centerY integer
---@param radius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param color Color
function draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color) end

---Draw a filled round-rectangle on the screen.
---@param x integer
---@param y integer
---@param width integer
---@param height integer
---@param cornerRadius integer
---@param color Color
function draw_rectangle_rounded(x, y, width, height, cornerRadius, color) end

---Draw an image on the screen.
---@param src integer
---@param posX integer
---@param posY integer
function draw_image(src, posX, posY) end

---Draw a tinted image on the screen.
---@param src integer
---@param posX integer
---@param posY integer
---@param tint Color
function draw_image_tint(src, posX, posY, tint) end

---Draw an image, rotated, on the screen.
---@param src integer
---@param posX integer
---@param posY integer
---@param degrees number
---@param offsetX number
---@param offsetY number
---@param filter integer
function draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter) end

---Draw an image, flipped, on the screen.
---@param src integer
---@param posX integer
---@param posY integer
---@param flipHorizontal boolean
---@param flipVertical boolean
---@param flipDiagonal boolean
function draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) end

---Draw an image, scaled, on the screen.
---@param src integer
---@param posX integer
---@param posY integer
---@param scaleX number
---@param scaleY number
---@param offsetX number
---@param offsetY number
---@param filter integer
function draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) end

---Draw some text on the screen.
---@param font integer
---@param text string
---@param posX integer
---@param posY integer
---@param color Color
function draw_text(font, text, posX, posY, color) end

---Save an image to persistant storage.
---@param image integer
---@param filename string
function save_image(image, filename) end

---Load an image from a file in cart.
---@param filename string
---@return integer
function load_image(filename) end

---Resize an image, return copy.
---@param image integer
---@param newWidth integer
---@param newHeight integer
---@param filter integer
---@return integer
function image_resize(image, newWidth, newHeight, filter) end

---Scale an image, return copy.
---@param image integer
---@param scaleX number
---@param scaleY number
---@param filter integer
---@return integer
function image_scale(image, scaleX, scaleY, filter) end

---Replace a color in an image, in-place.
---@param image integer
---@param color Color
---@param replace Color
function image_color_replace(image, color, replace) end

---Tint a color in an image, in-place.
---@param image integer
---@param color Color
function image_color_tint(image, color) end

---Fade a color in an image, in-place.
---@param image integer
---@param alpha number
function image_color_fade(image, alpha) end

---Copy a font to a new font.
---@param font integer
---@return integer
function font_copy(font) end

---Scale a font, return a new font.
---@param font integer
---@param scaleX number
---@param scaleY number
---@param filter integer
---@return integer
function font_scale(font, scaleX, scaleY, filter) end

---Load a BMF font from a file in cart.
---@param filename string
---@param characters string
---@return integer
function load_font_bmf(filename, characters) end

---Load a BMF font from an image.
---@param image integer
---@param characters string
---@return integer
function load_font_bmf_from_image(image, characters) end

---Measure the size of some text.
---@param font integer
---@param text string
---@param textLength integer
---@return Dimensions
function measure_text(font, text, textLength) end

---Meaure an image (use 0 for screen).
---@param image integer
---@return Dimensions
function measure_image(image) end

---Load a TTY font from a file in cart.
---@param filename string
---@param glyphWidth integer
---@param glyphHeight integer
---@param characters string
---@return integer
function load_font_tty(filename, glyphWidth, glyphHeight, characters) end

---Load a TTY font from an image.
---@param image integer
---@param glyphWidth integer
---@param glyphHeight integer
---@param characters string
---@return integer
function load_font_tty_from_image(image, glyphWidth, glyphHeight, characters) end

---Load a TTF font from a file in cart.
---@param filename string
---@param fontSize integer
---@return integer
function load_font_ttf(filename, fontSize) end

---Invert the colors in an image, in-place.
---@param image integer
function image_color_invert(image) end

---Calculate a rectangle representing the available alpha border in an image.
---@param image integer
---@param threshold number
---@return Rectangle
function image_alpha_border(image, threshold) end

---Crop an image, in-place.
---@param image integer
---@param x integer
---@param y integer
---@param width integer
---@param height integer
function image_crop(image, x, y, width, height) end

---Crop an image based on the alpha border, in-place.
---@param image integer
---@param threshold number
function image_alpha_crop(image, threshold) end

---Adjust the brightness of an image, in-place.
---@param image integer
---@param factor number
function image_color_brightness(image, factor) end

---Flip an image, in-place.
---@param image integer
---@param horizontal boolean
---@param vertical boolean
function image_flip(image, horizontal, vertical) end

---Change the contrast of an image, in-place.
---@param image integer
---@param contrast number
function image_color_contrast(image, contrast) end

---Use an image as an alpha-mask on another image.
---@param image integer
---@param alphaMask integer
---@param posX integer
---@param posY integer
function image_alpha_mask(image, alphaMask, posX, posY) end

---Create a new image, rotating another image.
---@param image integer
---@param degrees number
---@param filter integer
---@return integer
function image_rotate(image, degrees, filter) end

---Create a new image of a gradient.
---@param width integer
---@param height integer
---@param topLeft Color
---@param topRight Color
---@param bottomLeft Color
---@param bottomRight Color
---@return integer
function image_gradient(width, height, topLeft, topRight, bottomLeft, bottomRight) end

---Unload an image.
---@param image integer
function unload_image(image) end

---Unload a font.
---@param font integer
function unload_font(font) end

---Clear an image.
---@param destination integer
---@param color Color
function clear_image(destination, color) end

---Draw a single pixel on an image.
---@param destination integer
---@param x integer
---@param y integer
---@param color Color
function draw_point_on_image(destination, x, y, color) end

---Draw a line on an image.
---@param destination integer
---@param startPosX integer
---@param startPosY integer
---@param endPosX integer
---@param endPosY integer
---@param color Color
function draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color) end

---Draw a filled rectangle on an image.
---@param destination integer
---@param posX integer
---@param posY integer
---@param width integer
---@param height integer
---@param color Color
function draw_rectangle_on_image(destination, posX, posY, width, height, color) end

---Draw a filled triangle on an image.
---@param destination integer
---@param x1 integer
---@param y1 integer
---@param x2 integer
---@param y2 integer
---@param x3 integer
---@param y3 integer
---@param color Color
function draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color) end

---Draw a filled ellipse on an image.
---@param destination integer
---@param centerX integer
---@param centerY integer
---@param radiusX integer
---@param radiusY integer
---@param color Color
function draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color) end

---Draw a circle on an image.
---@param destination integer
---@param centerX integer
---@param centerY integer
---@param radius integer
---@param color Color
function draw_circle_on_image(destination, centerX, centerY, radius, color) end

---Draw a filled polygon on an image.
---@param destination integer
---@param points Vector[]
---@param color Color
function draw_polygon_on_image(destination, points, color) end

---Draw a filled round-rectangle on an image.
---@param destination integer
---@param x integer
---@param y integer
---@param width integer
---@param height integer
---@param cornerRadius integer
---@param color Color
function draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color) end

---Draw an image on an image.
---@param destination integer
---@param src integer
---@param posX integer
---@param posY integer
function draw_image_on_image(destination, src, posX, posY) end

---Draw a tinted image on an image.
---@param destination integer
---@param src integer
---@param posX integer
---@param posY integer
---@param tint Color
function draw_image_tint_on_image(destination, src, posX, posY, tint) end

---Draw an image, rotated, on an image.
---@param destination integer
---@param src integer
---@param posX integer
---@param posY integer
---@param degrees number
---@param offsetX number
---@param offsetY number
---@param filter integer
function draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter) end

---Draw an image, flipped, on an image.
---@param destination integer
---@param src integer
---@param posX integer
---@param posY integer
---@param flipHorizontal boolean
---@param flipVertical boolean
---@param flipDiagonal boolean
function draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) end

---Draw an image, scaled, on an image.
---@param destination integer
---@param src integer
---@param posX integer
---@param posY integer
---@param scaleX number
---@param scaleY number
---@param offsetX number
---@param offsetY number
---@param filter integer
function draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) end

---Draw some text on an image.
---@param destination integer
---@param font integer
---@param text string
---@param posX integer
---@param posY integer
---@param color Color
function draw_text_on_image(destination, font, text, posX, posY, color) end

---Draw a outlined (with thickness) rectangle on the screen.
---@param posX integer
---@param posY integer
---@param width integer
---@param height integer
---@param thickness integer
---@param color Color
function draw_rectangle_outline(posX, posY, width, height, thickness, color) end

---Draw a outlined (with thickness) triangle on the screen.
---@param x1 integer
---@param y1 integer
---@param x2 integer
---@param y2 integer
---@param x3 integer
---@param y3 integer
---@param thickness integer
---@param color Color
function draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, color) end

---Draw a outlined (with thickness) ellipse on the screen.
---@param centerX integer
---@param centerY integer
---@param radiusX integer
---@param radiusY integer
---@param thickness integer
---@param color Color
function draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, color) end

---Draw a outlined (with thickness) circle on the screen.
---@param centerX integer
---@param centerY integer
---@param radius integer
---@param thickness integer
---@param color Color
function draw_circle_outline(centerX, centerY, radius, thickness, color) end

---Draw a outlined (with thickness) polygon on the screen.
---@param points Vector[]
---@param thickness integer
---@param color Color
function draw_polygon_outline(points, thickness, color) end

---Draw a outlined (with thickness) arc on the screen.
---@param centerX integer
---@param centerY integer
---@param radius number
---@param startAngle number
---@param endAngle number
---@param segments integer
---@param thickness integer
---@param color Color
function draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color) end

---Draw a outlined (with thickness) round-rectangle on the screen.
---@param x integer
---@param y integer
---@param width integer
---@param height integer
---@param cornerRadius integer
---@param thickness integer
---@param color Color
function draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, color) end

---Draw a outlined (with thickness) rectangle on an image.
---@param destination integer
---@param posX integer
---@param posY integer
---@param width integer
---@param height integer
---@param thickness integer
---@param color Color
function draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, color) end

---Draw a outlined (with thickness) triangle on an image.
---@param destination integer
---@param x1 integer
---@param y1 integer
---@param x2 integer
---@param y2 integer
---@param x3 integer
---@param y3 integer
---@param thickness integer
---@param color Color
function draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, color) end

---Draw a outlined (with thickness) ellipse on an image.
---@param destination integer
---@param centerX integer
---@param centerY integer
---@param radiusX integer
---@param radiusY integer
---@param thickness integer
---@param color Color
function draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, color) end

---Draw a outlined (with thickness) circle on an image.
---@param destination integer
---@param centerX integer
---@param centerY integer
---@param radius integer
---@param thickness integer
---@param color Color
function draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, color) end

---Draw a outlined (with thickness) polygon on an image.
---@param destination integer
---@param points Vector[]
---@param thickness integer
---@param color Color
function draw_polygon_outline_on_image(destination, points, thickness, color) end

---Draw a outlined (with thickness) round-rectangle on an image.
---@param destination integer
---@param x integer
---@param y integer
---@param width integer
---@param height integer
---@param cornerRadius integer
---@param thickness integer
---@param color Color
function draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, color) end

-- INPUT

---Has the key been pressed? (tracks unpress/read correctly.)
---@param key integer
---@return boolean
function key_pressed(key) end

---Is the key currently down?
---@param key integer
---@return boolean
function key_down(key) end

---Has the key been released? (tracks press/read correctly.)
---@param key integer
---@return boolean
function key_released(key) end

---Is the key currently up?
---@param key integer
---@return boolean
function key_up(key) end

---Has the button been pressed? (tracks unpress/read correctly.)
---@param gamepad integer
---@param button integer
---@return boolean
function gamepad_button_pressed(gamepad, button) end

---Is the button currently down?
---@param gamepad integer
---@param button integer
---@return boolean
function gamepad_button_down(gamepad, button) end

---Has the button been released? (tracks press/read correctly.)
---@param gamepad integer
---@param button integer
---@return boolean
function gamepad_button_released(gamepad, button) end

---Get current position of mouse.
---@return Vector
function mouse_position() end

---Has the button been pressed? (tracks unpress/read correctly.)
---@param button integer
---@return boolean
function mouse_button_pressed(button) end

---Is the button currently down?
---@param button integer
---@return boolean
function mouse_button_down(button) end

---Has the button been released? (tracks press/read correctly.)
---@param button integer
---@return boolean
function mouse_button_released(button) end

---Is the button currently up?
---@param button integer
---@return boolean
function mouse_button_up(button) end

-- SOUND

---Load a sound from a file in cart.
---@param filename string
---@return integer
function load_sound(filename) end

---Play a sound.
---@param sound integer
---@param loop boolean
function play_sound(sound, loop) end

---Stop a sound.
---@param sound integer
function stop_sound(sound) end

---Unload a sound.
---@param sound integer
function unload_sound(sound) end

---Speak some text and return a sound. Set things to 0 for defaults.
---@param text string
---@param phonetic boolean
---@param pitch integer
---@param speed integer
---@param throat integer
---@param mouth integer
---@param sing boolean
---@return integer
function tts_sound(text, phonetic, pitch, speed, throat, mouth, sing) end

---Create Sfx sound.
---@param params SfxParams
---@return integer
function sfx_sound(params) end

---Create Sfx parameters.
---@param type integer
---@return SfxParams
function sfx_generate(type) end

-- TYPES

-- UTILITIES

---Get system-time (ms) since unix epoch.
---@return integer
function current_time() end

---Get the change in time (seconds) since the last update run.
---@return number
function delta_time() end

---Get a random integer between 2 numbers.
---@param min integer
---@param max integer
---@return integer
function random_int(min, max) end

---Get the random-seed.
---@return integer
function random_seed_get() end

---Set the random-seed.
---@param seed integer
function random_seed_set(seed) end

-- CONSTANTS

---The screen is image 0
SCREEN = 0
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
---The built-in font
FONT_DEFAULT = 0

---@type Color
LIGHTGRAY = { r = 200, g = 200, b = 200, a = 255 }
---@type Color
GRAY = { r = 130, g = 130, b = 130, a = 255 }
---@type Color
DARKGRAY = { r = 80, g = 80, b = 80, a = 255 }
---@type Color
YELLOW = { r = 253, g = 249, b = 0, a = 255 }
---@type Color
GOLD = { r = 255, g = 203, b = 0, a = 255 }
---@type Color
ORANGE = { r = 255, g = 161, b = 0, a = 255 }
---@type Color
PINK = { r = 255, g = 109, b = 194, a = 255 }
---@type Color
RED = { r = 230, g = 41, b = 55, a = 255 }
---@type Color
MAROON = { r = 190, g = 33, b = 55, a = 255 }
---@type Color
GREEN = { r = 0, g = 228, b = 48, a = 255 }
---@type Color
LIME = { r = 0, g = 158, b = 47, a = 255 }
---@type Color
DARKGREEN = { r = 0, g = 117, b = 44, a = 255 }
---@type Color
SKYBLUE = { r = 102, g = 191, b = 255, a = 255 }
---@type Color
BLUE = { r = 0, g = 121, b = 241, a = 255 }
---@type Color
DARKBLUE = { r = 0, g = 82, b = 172, a = 255 }
---@type Color
PURPLE = { r = 200, g = 122, b = 255, a = 255 }
---@type Color
VIOLET = { r = 135, g = 60, b = 190, a = 255 }
---@type Color
DARKPURPLE = { r = 112, g = 31, b = 126, a = 255 }
---@type Color
BEIGE = { r = 211, g = 176, b = 131, a = 255 }
---@type Color
BROWN = { r = 127, g = 106, b = 79, a = 255 }
---@type Color
DARKBROWN = { r = 76, g = 63, b = 47, a = 255 }
---@type Color
WHITE = { r = 255, g = 255, b = 255, a = 255 }
---@type Color
BLACK = { r = 0, g = 0, b = 0, a = 255 }
---@type Color
BLANK = { r = 0, g = 0, b = 0, a = 0 }
---@type Color
MAGENTA = { r = 255, g = 0, b = 255, a = 255 }
---@type Color
RAYWHITE = { r = 245, g = 245, b = 245, a = 255 }
---The current tagged version of null0 engine
NULL0_VERSION = "0.0.8"

-- Potential image-filtering techniques for scale/etc.
FILTER_NEARESTNEIGHBOR = 0
FILTER_BILINEAR = 1
FILTER_SMOOTH = 2

-- Represents a Sfx preset type.
SFX_COIN = 0
SFX_LASER = 1
SFX_EXPLOSION = 2
SFX_POWERUP = 3
SFX_HURT = 4
SFX_JUMP = 5
SFX_SELECT = 6
SFX_SYNTH = 7

-- Represents a keyboard key.
KEY_INVALID = 0
KEY_SPACE = 32
KEY_APOSTROPHE = 39
KEY_COMMA = 44
KEY_MINUS = 45
KEY_PERIOD = 46
KEY_SLASH = 47
KEY_0 = 48
KEY_1 = 49
KEY_2 = 50
KEY_3 = 51
KEY_4 = 52
KEY_5 = 53
KEY_6 = 54
KEY_7 = 55
KEY_8 = 56
KEY_9 = 57
KEY_SEMICOLON = 59
KEY_EQUAL = 61
KEY_A = 65
KEY_B = 66
KEY_C = 67
KEY_D = 68
KEY_E = 69
KEY_F = 70
KEY_G = 71
KEY_H = 72
KEY_I = 73
KEY_J = 74
KEY_K = 75
KEY_L = 76
KEY_M = 77
KEY_N = 78
KEY_O = 79
KEY_P = 80
KEY_Q = 81
KEY_R = 82
KEY_S = 83
KEY_T = 84
KEY_U = 85
KEY_V = 86
KEY_W = 87
KEY_X = 88
KEY_Y = 89
KEY_Z = 90
KEY_LEFT_BRACKET = 91
KEY_BACKSLASH = 92
KEY_RIGHT_BRACKET = 93
KEY_GRAVE_ACCENT = 96
KEY_WORLD_1 = 161
KEY_WORLD_2 = 162
KEY_ESCAPE = 256
KEY_ENTER = 257
KEY_TAB = 258
KEY_BACKSPACE = 259
KEY_INSERT = 260
KEY_DELETE = 261
KEY_RIGHT = 262
KEY_LEFT = 263
KEY_DOWN = 264
KEY_UP = 265
KEY_PAGE_UP = 266
KEY_PAGE_DOWN = 267
KEY_HOME = 268
KEY_END = 269
KEY_CAPS_LOCK = 280
KEY_SCROLL_LOCK = 281
KEY_NUM_LOCK = 282
KEY_PRINT_SCREEN = 283
KEY_PAUSE = 284
KEY_F1 = 290
KEY_F2 = 291
KEY_F3 = 292
KEY_F4 = 293
KEY_F5 = 294
KEY_F6 = 295
KEY_F7 = 296
KEY_F8 = 297
KEY_F9 = 298
KEY_F10 = 299
KEY_F11 = 300
KEY_F12 = 301
KEY_F13 = 302
KEY_F14 = 303
KEY_F15 = 304
KEY_F16 = 305
KEY_F17 = 306
KEY_F18 = 307
KEY_F19 = 308
KEY_F20 = 309
KEY_F21 = 310
KEY_F22 = 311
KEY_F23 = 312
KEY_F24 = 313
KEY_F25 = 314
KEY_KP_0 = 320
KEY_KP_1 = 321
KEY_KP_2 = 322
KEY_KP_3 = 323
KEY_KP_4 = 324
KEY_KP_5 = 325
KEY_KP_6 = 326
KEY_KP_7 = 327
KEY_KP_8 = 328
KEY_KP_9 = 329
KEY_KP_DECIMAL = 330
KEY_KP_DIVIDE = 331
KEY_KP_MULTIPLY = 332
KEY_KP_SUBTRACT = 333
KEY_KP_ADD = 334
KEY_KP_ENTER = 335
KEY_KP_EQUAL = 336
KEY_LEFT_SHIFT = 340
KEY_LEFT_CONTROL = 341
KEY_LEFT_ALT = 342
KEY_LEFT_SUPER = 343
KEY_RIGHT_SHIFT = 344
KEY_RIGHT_CONTROL = 345
KEY_RIGHT_ALT = 346
KEY_RIGHT_SUPER = 347
KEY_MENU = 348

-- Represents a gamepad button.
GAMEPAD_BUTTON_UNKNOWN = 0
GAMEPAD_BUTTON_UP = 1
GAMEPAD_BUTTON_RIGHT = 2
GAMEPAD_BUTTON_DOWN = 3
GAMEPAD_BUTTON_LEFT = 4
GAMEPAD_BUTTON_Y = 5
GAMEPAD_BUTTON_B = 6
GAMEPAD_BUTTON_A = 7
GAMEPAD_BUTTON_X = 8
GAMEPAD_BUTTON_LEFT_SHOULDER = 9
GAMEPAD_BUTTON_LEFT_TRIGGER = 10
GAMEPAD_BUTTON_RIGHT_SHOULDER = 11
GAMEPAD_BUTTON_RIGHT_TRIGGER = 12
GAMEPAD_BUTTON_SELECT = 13
GAMEPAD_BUTTON_MENU = 14
GAMEPAD_BUTTON_START = 15
GAMEPAD_BUTTON_LEFT_THUMB = 16
GAMEPAD_BUTTON_RIGHT_THUMB = 17

-- Represents a mouse button.
MOUSE_BUTTON_UNKNOWN = 0
MOUSE_BUTTON_LEFT = 1
MOUSE_BUTTON_RIGHT = 2
MOUSE_BUTTON_MIDDLE = 3

-- CALLBACKS (implement the ones you need, in main.lua)

---Called when the cart is loaded.
function load() end

---Called on every frame.
function update() end

---Called when the cart is unloaded.
function unload() end

---Mapped controller (keys and gamepad will trigger) callback for when a "button" is unpressed.
---@param button integer
---@param player integer
function buttonUp(button, player) end

---Mapped controller (keys and gamepad will trigger) callback for when a "button" is pressed.
---@param button integer
---@param player integer
function buttonDown(button, player) end

---Called when keys are unpressed.
---@param key integer
function keyUp(key) end

---Called when keys are pressed.
---@param key integer
function keyDown(key) end

---Called when mouse-button is pressed.
---@param button integer
function mouseDown(button) end

---Called when mouse-button is released.
---@param button integer
function mouseUp(button) end

---Called when mouse is moved.
---@param x number
---@param y number
function mouseMoved(x, y) end
