"""null0 - Python bindings for the null0 fantasy console.

Usage:

```python
import null0

def load():
    null0.clear(null0.BLUE)
    null0.draw_circle(100, 100, 50, null0.RED)
```

NOTE: py2wasm (CPython -> WebAssembly) cannot yet declare custom host
imports. These bindings document the full API surface; functions call
_host(), which a null0-aware Python runtime can provide.

ABI notes:
- handles (Image/Font/Sound), enums and bools are ints
- Color is 4 bytes packed into a single int: r | g<<8 | b<<16 | a<<24
- functions returning structs (Vector/Dimensions/Rectangle/Color/SfxParams)
  return a pointer (int) into cart memory
"""

from enum import IntEnum
from dataclasses import dataclass


def _host(name: str, *args):
    """Call a host function. Provided by a null0-aware Python runtime."""
    raise NotImplementedError(f"null0 host function '{name}' is not available in this runtime")


def rgba(r: int, g: int, b: int, a: int) -> int:
    """Create a Color from r, g, b, a components."""
    return (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | ((a & 0xFF) << 24)


def rgb(r: int, g: int, b: int) -> int:
    """Create an opaque Color from r, g, b components."""
    return rgba(r, g, b, 255)


# handle types
Image = int
Font = int
Sound = int
Color = int


# Sfx parameters.
@dataclass
class SfxParams:
    randSeed: int
    waveType: int
    attackTime: float
    sustainTime: float
    sustainPunch: float
    decayTime: float
    startFrequency: float
    minFrequency: float
    slide: float
    deltaSlide: float
    vibratoDepth: float
    vibratoSpeed: float
    changeAmount: float
    changeSpeed: float
    squareDuty: float
    dutySweep: float
    repeatSpeed: float
    phaserOffset: float
    phaserSweep: float
    lpfCutoff: float
    lpfCutoffSweep: float
    lpfResonance: float
    hpfCutoff: float
    hpfCutoffSweep: float

# The 2D size of something (width/height.)
@dataclass
class Dimensions:
    width: int
    height: int

# The 2D position of something (x/y.)
@dataclass
class Vector:
    x: int
    y: int

# The 2D position + size of something (x/y/w/h.)
@dataclass
class Rectangle:
    x: int
    y: int
    width: int
    height: int

# Potential image-filtering techniques for scale/etc.
class ImageFilter(IntEnum):
    FILTER_NEARESTNEIGHBOR = 0
    FILTER_BILINEAR = 1
    FILTER_SMOOTH = 2

# Represents a Sfx preset type.
class SfxPresetType(IntEnum):
    SFX_COIN = 0
    SFX_LASER = 1
    SFX_EXPLOSION = 2
    SFX_POWERUP = 3
    SFX_HURT = 4
    SFX_JUMP = 5
    SFX_SELECT = 6
    SFX_SYNTH = 7

# Represents a keyboard key.
class Key(IntEnum):
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

# Represents a gamepad button.
class GamepadButton(IntEnum):
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

# Represents a mouse button.
class MouseButton(IntEnum):
    MOUSE_BUTTON_UNKNOWN = 0
    MOUSE_BUTTON_LEFT = 1
    MOUSE_BUTTON_RIGHT = 2
    MOUSE_BUTTON_MIDDLE = 3

# Constants
SCREEN: Image = 0
SCREEN_WIDTH: int = 640
SCREEN_HEIGHT: int = 480
FONT_DEFAULT: Font = 0

# Colors
LIGHTGRAY: Color = 0xffc8c8c8  # rgba(200, 200, 200, 255)
GRAY: Color = 0xff828282  # rgba(130, 130, 130, 255)
DARKGRAY: Color = 0xff505050  # rgba(80, 80, 80, 255)
YELLOW: Color = 0xff00f9fd  # rgba(253, 249, 0, 255)
GOLD: Color = 0xff00cbff  # rgba(255, 203, 0, 255)
ORANGE: Color = 0xff00a1ff  # rgba(255, 161, 0, 255)
PINK: Color = 0xffc26dff  # rgba(255, 109, 194, 255)
RED: Color = 0xff3729e6  # rgba(230, 41, 55, 255)
MAROON: Color = 0xff3721be  # rgba(190, 33, 55, 255)
GREEN: Color = 0xff30e400  # rgba(0, 228, 48, 255)
LIME: Color = 0xff2f9e00  # rgba(0, 158, 47, 255)
DARKGREEN: Color = 0xff2c7500  # rgba(0, 117, 44, 255)
SKYBLUE: Color = 0xffffbf66  # rgba(102, 191, 255, 255)
BLUE: Color = 0xfff17900  # rgba(0, 121, 241, 255)
DARKBLUE: Color = 0xffac5200  # rgba(0, 82, 172, 255)
PURPLE: Color = 0xffff7ac8  # rgba(200, 122, 255, 255)
VIOLET: Color = 0xffbe3c87  # rgba(135, 60, 190, 255)
DARKPURPLE: Color = 0xff7e1f70  # rgba(112, 31, 126, 255)
BEIGE: Color = 0xff83b0d3  # rgba(211, 176, 131, 255)
BROWN: Color = 0xff4f6a7f  # rgba(127, 106, 79, 255)
DARKBROWN: Color = 0xff2f3f4c  # rgba(76, 63, 47, 255)
WHITE: Color = 0xffffffff  # rgba(255, 255, 255, 255)
BLACK: Color = 0xff000000  # rgba(0, 0, 0, 255)
BLANK: Color = 0x00000000  # rgba(0, 0, 0, 0)
MAGENTA: Color = 0xffff00ff  # rgba(255, 0, 255, 255)
RAYWHITE: Color = 0xfff5f5f5  # rgba(245, 245, 245, 255)

# COLORS

def color_tint(color: int, tint: int) -> int:
    """Tint a color with another color."""
    return _host("color_tint", color, tint)

def color_fade(color: int, alpha: float) -> int:
    """Fade a color."""
    return _host("color_fade", color, alpha)

def color_brightness(color: int, factor: float) -> int:
    """Change the brightness of a color."""
    return _host("color_brightness", color, factor)

def color_invert(color: int) -> int:
    """Invert a color."""
    return _host("color_invert", color)

def color_alpha_blend(dst: int, src: int) -> int:
    """Blend 2 colors together."""
    return _host("color_alpha_blend", dst, src)

def color_contrast(color: int, contrast: float) -> int:
    """Change contrast of a color."""
    return _host("color_contrast", color, contrast)

def color_bilinear_interpolate(color00: int, color01: int, color10: int, color11: int, coordinateX: float, coordinateY: float) -> int:
    """Interpolate colors."""
    return _host("color_bilinear_interpolate", color00, color01, color10, color11, coordinateX, coordinateY)

# GRAPHICS

def new_image(width: int, height: int, color: int) -> int:
    """Create a new blank image."""
    return _host("new_image", width, height, color)

def image_copy(image: int) -> int:
    """Copy an image to a new image."""
    return _host("image_copy", image)

def image_subimage(image: int, x: int, y: int, width: int, height: int) -> int:
    """Create an image from a region of another image."""
    return _host("image_subimage", image, x, y, width, height)

def clear(color: int) -> None:
    """Clear the screen."""
    return _host("clear", color)

def draw_point(x: int, y: int, color: int) -> None:
    """Draw a single pixel on the screen."""
    return _host("draw_point", x, y, color)

def draw_line(startPosX: int, startPosY: int, endPosX: int, endPosY: int, color: int) -> None:
    """Draw a line on the screen."""
    return _host("draw_line", startPosX, startPosY, endPosX, endPosY, color)

def draw_rectangle(posX: int, posY: int, width: int, height: int, color: int) -> None:
    """Draw a filled rectangle on the screen."""
    return _host("draw_rectangle", posX, posY, width, height, color)

def draw_triangle(x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, color: int) -> None:
    """Draw a filled triangle on the screen."""
    return _host("draw_triangle", x1, y1, x2, y2, x3, y3, color)

def draw_ellipse(centerX: int, centerY: int, radiusX: int, radiusY: int, color: int) -> None:
    """Draw a filled ellipse on the screen."""
    return _host("draw_ellipse", centerX, centerY, radiusX, radiusY, color)

def draw_circle(centerX: int, centerY: int, radius: int, color: int) -> None:
    """Draw a filled circle on the screen."""
    return _host("draw_circle", centerX, centerY, radius, color)

def draw_polygon(points: int, numPoints: int, color: int) -> None:
    """Draw a filled polygon on the screen."""
    return _host("draw_polygon", points, numPoints, color)

def draw_arc(centerX: int, centerY: int, radius: float, startAngle: float, endAngle: float, segments: int, color: int) -> None:
    """Draw a filled arc on the screen."""
    return _host("draw_arc", centerX, centerY, radius, startAngle, endAngle, segments, color)

def draw_rectangle_rounded(x: int, y: int, width: int, height: int, cornerRadius: int, color: int) -> None:
    """Draw a filled round-rectangle on the screen."""
    return _host("draw_rectangle_rounded", x, y, width, height, cornerRadius, color)

def draw_image(src: int, posX: int, posY: int) -> None:
    """Draw an image on the screen."""
    return _host("draw_image", src, posX, posY)

def draw_image_tint(src: int, posX: int, posY: int, tint: int) -> None:
    """Draw a tinted image on the screen."""
    return _host("draw_image_tint", src, posX, posY, tint)

def draw_image_rotated(src: int, posX: int, posY: int, degrees: float, offsetX: float, offsetY: float, filter: int) -> None:
    """Draw an image, rotated, on the screen."""
    return _host("draw_image_rotated", src, posX, posY, degrees, offsetX, offsetY, filter)

def draw_image_flipped(src: int, posX: int, posY: int, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) -> None:
    """Draw an image, flipped, on the screen."""
    return _host("draw_image_flipped", src, posX, posY, flipHorizontal, flipVertical, flipDiagonal)

def draw_image_scaled(src: int, posX: int, posY: int, scaleX: float, scaleY: float, offsetX: float, offsetY: float, filter: int) -> None:
    """Draw an image, scaled, on the screen."""
    return _host("draw_image_scaled", src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter)

def draw_text(font: int, text: str, posX: int, posY: int, color: int) -> None:
    """Draw some text on the screen."""
    return _host("draw_text", font, text, posX, posY, color)

def save_image(image: int, filename: str) -> None:
    """Save an image to persistant storage."""
    return _host("save_image", image, filename)

def load_image(filename: str) -> int:
    """Load an image from a file in cart."""
    return _host("load_image", filename)

def image_resize(image: int, newWidth: int, newHeight: int, filter: int) -> int:
    """Resize an image, return copy."""
    return _host("image_resize", image, newWidth, newHeight, filter)

def image_scale(image: int, scaleX: float, scaleY: float, filter: int) -> int:
    """Scale an image, return copy."""
    return _host("image_scale", image, scaleX, scaleY, filter)

def image_color_replace(image: int, color: int, replace: int) -> None:
    """Replace a color in an image, in-place."""
    return _host("image_color_replace", image, color, replace)

def image_color_tint(image: int, color: int) -> None:
    """Tint a color in an image, in-place."""
    return _host("image_color_tint", image, color)

def image_color_fade(image: int, alpha: float) -> None:
    """Fade a color in an image, in-place."""
    return _host("image_color_fade", image, alpha)

def font_copy(font: int) -> int:
    """Copy a font to a new font."""
    return _host("font_copy", font)

def font_scale(font: int, scaleX: float, scaleY: float, filter: int) -> int:
    """Scale a font, return a new font."""
    return _host("font_scale", font, scaleX, scaleY, filter)

def load_font_bmf(filename: str, characters: str) -> int:
    """Load a BMF font from a file in cart."""
    return _host("load_font_bmf", filename, characters)

def load_font_bmf_from_image(image: int, characters: str) -> int:
    """Load a BMF font from an image."""
    return _host("load_font_bmf_from_image", image, characters)

def measure_text(font: int, text: str, textLength: int) -> int:
    """Measure the size of some text."""
    return _host("measure_text", font, text, textLength)

def measure_image(image: int) -> int:
    """Meaure an image (use 0 for screen)."""
    return _host("measure_image", image)

def load_font_tty(filename: str, glyphWidth: int, glyphHeight: int, characters: str) -> int:
    """Load a TTY font from a file in cart."""
    return _host("load_font_tty", filename, glyphWidth, glyphHeight, characters)

def load_font_tty_from_image(image: int, glyphWidth: int, glyphHeight: int, characters: str) -> int:
    """Load a TTY font from an image."""
    return _host("load_font_tty_from_image", image, glyphWidth, glyphHeight, characters)

def load_font_ttf(filename: str, fontSize: int) -> int:
    """Load a TTF font from a file in cart."""
    return _host("load_font_ttf", filename, fontSize)

def image_color_invert(image: int) -> None:
    """Invert the colors in an image, in-place."""
    return _host("image_color_invert", image)

def image_alpha_border(image: int, threshold: float) -> int:
    """Calculate a rectangle representing the available alpha border in an image."""
    return _host("image_alpha_border", image, threshold)

def image_crop(image: int, x: int, y: int, width: int, height: int) -> None:
    """Crop an image, in-place."""
    return _host("image_crop", image, x, y, width, height)

def image_alpha_crop(image: int, threshold: float) -> None:
    """Crop an image based on the alpha border, in-place."""
    return _host("image_alpha_crop", image, threshold)

def image_color_brightness(image: int, factor: float) -> None:
    """Adjust the brightness of an image, in-place."""
    return _host("image_color_brightness", image, factor)

def image_flip(image: int, horizontal: bool, vertical: bool) -> None:
    """Flip an image, in-place."""
    return _host("image_flip", image, horizontal, vertical)

def image_color_contrast(image: int, contrast: float) -> None:
    """Change the contrast of an image, in-place."""
    return _host("image_color_contrast", image, contrast)

def image_alpha_mask(image: int, alphaMask: int, posX: int, posY: int) -> None:
    """Use an image as an alpha-mask on another image."""
    return _host("image_alpha_mask", image, alphaMask, posX, posY)

def image_rotate(image: int, degrees: float, filter: int) -> int:
    """Create a new image, rotating another image."""
    return _host("image_rotate", image, degrees, filter)

def image_gradient(width: int, height: int, topLeft: int, topRight: int, bottomLeft: int, bottomRight: int) -> int:
    """Create a new image of a gradient."""
    return _host("image_gradient", width, height, topLeft, topRight, bottomLeft, bottomRight)

def unload_image(image: int) -> None:
    """Unload an image."""
    return _host("unload_image", image)

def unload_font(font: int) -> None:
    """Unload a font."""
    return _host("unload_font", font)

def clear_image(destination: int, color: int) -> None:
    """Clear an image."""
    return _host("clear_image", destination, color)

def draw_point_on_image(destination: int, x: int, y: int, color: int) -> None:
    """Draw a single pixel on an image."""
    return _host("draw_point_on_image", destination, x, y, color)

def draw_line_on_image(destination: int, startPosX: int, startPosY: int, endPosX: int, endPosY: int, color: int) -> None:
    """Draw a line on an image."""
    return _host("draw_line_on_image", destination, startPosX, startPosY, endPosX, endPosY, color)

def draw_rectangle_on_image(destination: int, posX: int, posY: int, width: int, height: int, color: int) -> None:
    """Draw a filled rectangle on an image."""
    return _host("draw_rectangle_on_image", destination, posX, posY, width, height, color)

def draw_triangle_on_image(destination: int, x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, color: int) -> None:
    """Draw a filled triangle on an image."""
    return _host("draw_triangle_on_image", destination, x1, y1, x2, y2, x3, y3, color)

def draw_ellipse_on_image(destination: int, centerX: int, centerY: int, radiusX: int, radiusY: int, color: int) -> None:
    """Draw a filled ellipse on an image."""
    return _host("draw_ellipse_on_image", destination, centerX, centerY, radiusX, radiusY, color)

def draw_circle_on_image(destination: int, centerX: int, centerY: int, radius: int, color: int) -> None:
    """Draw a circle on an image."""
    return _host("draw_circle_on_image", destination, centerX, centerY, radius, color)

def draw_polygon_on_image(destination: int, points: int, numPoints: int, color: int) -> None:
    """Draw a filled polygon on an image."""
    return _host("draw_polygon_on_image", destination, points, numPoints, color)

def draw_rectangle_rounded_on_image(destination: int, x: int, y: int, width: int, height: int, cornerRadius: int, color: int) -> None:
    """Draw a filled round-rectangle on an image."""
    return _host("draw_rectangle_rounded_on_image", destination, x, y, width, height, cornerRadius, color)

def draw_image_on_image(destination: int, src: int, posX: int, posY: int) -> None:
    """Draw an image on an image."""
    return _host("draw_image_on_image", destination, src, posX, posY)

def draw_image_tint_on_image(destination: int, src: int, posX: int, posY: int, tint: int) -> None:
    """Draw a tinted image on an image."""
    return _host("draw_image_tint_on_image", destination, src, posX, posY, tint)

def draw_image_rotated_on_image(destination: int, src: int, posX: int, posY: int, degrees: float, offsetX: float, offsetY: float, filter: int) -> None:
    """Draw an image, rotated, on an image."""
    return _host("draw_image_rotated_on_image", destination, src, posX, posY, degrees, offsetX, offsetY, filter)

def draw_image_flipped_on_image(destination: int, src: int, posX: int, posY: int, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) -> None:
    """Draw an image, flipped, on an image."""
    return _host("draw_image_flipped_on_image", destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal)

def draw_image_scaled_on_image(destination: int, src: int, posX: int, posY: int, scaleX: float, scaleY: float, offsetX: float, offsetY: float, filter: int) -> None:
    """Draw an image, scaled, on an image."""
    return _host("draw_image_scaled_on_image", destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter)

def draw_text_on_image(destination: int, font: int, text: str, posX: int, posY: int, color: int) -> None:
    """Draw some text on an image."""
    return _host("draw_text_on_image", destination, font, text, posX, posY, color)

def draw_rectangle_outline(posX: int, posY: int, width: int, height: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) rectangle on the screen."""
    return _host("draw_rectangle_outline", posX, posY, width, height, thickness, color)

def draw_triangle_outline(x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) triangle on the screen."""
    return _host("draw_triangle_outline", x1, y1, x2, y2, x3, y3, thickness, color)

def draw_ellipse_outline(centerX: int, centerY: int, radiusX: int, radiusY: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) ellipse on the screen."""
    return _host("draw_ellipse_outline", centerX, centerY, radiusX, radiusY, thickness, color)

def draw_circle_outline(centerX: int, centerY: int, radius: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) circle on the screen."""
    return _host("draw_circle_outline", centerX, centerY, radius, thickness, color)

def draw_polygon_outline(points: int, numPoints: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) polygon on the screen."""
    return _host("draw_polygon_outline", points, numPoints, thickness, color)

def draw_arc_outline(centerX: int, centerY: int, radius: float, startAngle: float, endAngle: float, segments: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) arc on the screen."""
    return _host("draw_arc_outline", centerX, centerY, radius, startAngle, endAngle, segments, thickness, color)

def draw_rectangle_rounded_outline(x: int, y: int, width: int, height: int, cornerRadius: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) round-rectangle on the screen."""
    return _host("draw_rectangle_rounded_outline", x, y, width, height, cornerRadius, thickness, color)

def draw_rectangle_outline_on_image(destination: int, posX: int, posY: int, width: int, height: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) rectangle on an image."""
    return _host("draw_rectangle_outline_on_image", destination, posX, posY, width, height, thickness, color)

def draw_triangle_outline_on_image(destination: int, x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) triangle on an image."""
    return _host("draw_triangle_outline_on_image", destination, x1, y1, x2, y2, x3, y3, thickness, color)

def draw_ellipse_outline_on_image(destination: int, centerX: int, centerY: int, radiusX: int, radiusY: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) ellipse on an image."""
    return _host("draw_ellipse_outline_on_image", destination, centerX, centerY, radiusX, radiusY, thickness, color)

def draw_circle_outline_on_image(destination: int, centerX: int, centerY: int, radius: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) circle on an image."""
    return _host("draw_circle_outline_on_image", destination, centerX, centerY, radius, thickness, color)

def draw_polygon_outline_on_image(destination: int, points: int, numPoints: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) polygon on an image."""
    return _host("draw_polygon_outline_on_image", destination, points, numPoints, thickness, color)

def draw_rectangle_rounded_outline_on_image(destination: int, x: int, y: int, width: int, height: int, cornerRadius: int, thickness: int, color: int) -> None:
    """Draw a outlined (with thickness) round-rectangle on an image."""
    return _host("draw_rectangle_rounded_outline_on_image", destination, x, y, width, height, cornerRadius, thickness, color)

# INPUT

def key_pressed(key: int) -> bool:
    """Has the key been pressed? (tracks unpress/read correctly.)"""
    return _host("key_pressed", key)

def key_down(key: int) -> bool:
    """Is the key currently down?"""
    return _host("key_down", key)

def key_released(key: int) -> bool:
    """Has the key been released? (tracks press/read correctly.)"""
    return _host("key_released", key)

def key_up(key: int) -> bool:
    """Is the key currently up?"""
    return _host("key_up", key)

def gamepad_button_pressed(gamepad: int, button: int) -> bool:
    """Has the button been pressed? (tracks unpress/read correctly.)"""
    return _host("gamepad_button_pressed", gamepad, button)

def gamepad_button_down(gamepad: int, button: int) -> bool:
    """Is the button currently down?"""
    return _host("gamepad_button_down", gamepad, button)

def gamepad_button_released(gamepad: int, button: int) -> bool:
    """Has the button been released? (tracks press/read correctly.)"""
    return _host("gamepad_button_released", gamepad, button)

def mouse_position() -> int:
    """Get current position of mouse."""
    return _host("mouse_position")

def mouse_button_pressed(button: int) -> bool:
    """Has the button been pressed? (tracks unpress/read correctly.)"""
    return _host("mouse_button_pressed", button)

def mouse_button_down(button: int) -> bool:
    """Is the button currently down?"""
    return _host("mouse_button_down", button)

def mouse_button_released(button: int) -> bool:
    """Has the button been released? (tracks press/read correctly.)"""
    return _host("mouse_button_released", button)

def mouse_button_up(button: int) -> bool:
    """Is the button currently up?"""
    return _host("mouse_button_up", button)

# SOUND

def load_sound(filename: str) -> int:
    """Load a sound from a file in cart."""
    return _host("load_sound", filename)

def play_sound(sound: int, loop: bool) -> None:
    """Play a sound."""
    return _host("play_sound", sound, loop)

def stop_sound(sound: int) -> None:
    """Stop a sound."""
    return _host("stop_sound", sound)

def unload_sound(sound: int) -> None:
    """Unload a sound."""
    return _host("unload_sound", sound)

def tts_sound(text: str, phonetic: bool, pitch: int, speed: int, throat: int, mouth: int, sing: bool) -> int:
    """Speak some text and return a sound. Set things to 0 for defaults."""
    return _host("tts_sound", text, phonetic, pitch, speed, throat, mouth, sing)

def sfx_sound(params: int) -> int:
    """Create Sfx sound."""
    return _host("sfx_sound", params)

def sfx_generate(type: int) -> int:
    """Create Sfx parameters."""
    return _host("sfx_generate", type)

# TYPES

# UTILITIES

def current_time() -> int:
    """Get system-time (ms) since unix epoch."""
    return _host("current_time")

def delta_time() -> float:
    """Get the change in time (seconds) since the last update run."""
    return _host("delta_time")

def random_int(min: int, max: int) -> int:
    """Get a random integer between 2 numbers."""
    return _host("random_int", min, max)

def random_seed_get() -> int:
    """Get the random-seed."""
    return _host("random_seed_get")

def random_seed_set(seed: int) -> None:
    """Set the random-seed."""
    return _host("random_seed_set", seed)
