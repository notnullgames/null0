# null0 - type stubs for the null0 fantasy console
#
# GENERATED FILE - do not edit by hand. See tools/gen_cart_python.js
#
# The null0 API is available as plain globals in your cart - nothing to
# import at runtime, same as the lua/js carts. This file is only here so
# editors (anything pyright/Pylance-based) can complete & check your cart.
#
# Unlike lua and JS, python has no notion of ambient globals, so a checker
# needs to be told the names exist. Put null0.pyi next to main.py and open
# your cart with a type-checking-only import. The block never runs, so the
# cart still just uses the globals at runtime:
#
#     TYPE_CHECKING = False
#
#     if TYPE_CHECKING:
#         from null0 import *
#
#     # (this cart runtime is RustPython built without the stdlib, so do NOT
#     # write `from typing import TYPE_CHECKING` - there is no typing module
#     # to import. A plain module-level flag is what pyright looks for.)
#
#     def load():
#         clear(BLUE)
#         draw_circle(100, 100, 50, RED)

from typing import TypedDict

# TYPES

# An image. 0 is "the screen".
Image = int

# A font. 0 is "the default font".
Font = int

# A sound.
Sound = int

# A tilemap (a Tiled map, exported as JSON). 0 is an invalid tilemap.
Tilemap = int

# Potential image-filtering techniques for scale/etc.
ImageFilter = int

# Represents a Sfx preset type.
SfxPresetType = int

# Represents a keyboard key.
Key = int

# Represents a gamepad button.
GamepadButton = int

# Represents a mouse button.
MouseButton = int

# The kind of a layer in a tilemap.
TileLayerKind = int

# The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING.
TilePropType = int

class SfxParams(TypedDict):
    """Sfx parameters."""
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

class Dimensions(TypedDict):
    """The 2D size of something (width/height.)"""
    width: int
    height: int

class Vector(TypedDict):
    """The 2D position of something (x/y.)"""
    x: int
    y: int

class Rectangle(TypedDict):
    """The 2D position + size of something (x/y/w/h.)"""
    x: int
    y: int
    width: int
    height: int

class Color(TypedDict):
    """An RGBA color."""
    r: int
    g: int
    b: int
    a: int

class TilemapProp(TypedDict):
    """A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`."""
    name: str
    type: TilePropType
    integer: int
    number: float
    text: str

class TilemapObject(TypedDict):
    """An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it."""
    id: int
    name: str
    type: str
    gid: int
    x: float
    y: float
    width: float
    height: float
    rotation: float
    visible: int

# COLORS

def color_tint(color: Color, tint: Color) -> Color:
    """Tint a color with another color."""
    ...

def color_fade(color: Color, alpha: float) -> Color:
    """Fade a color."""
    ...

def color_brightness(color: Color, factor: float) -> Color:
    """Change the brightness of a color."""
    ...

def color_invert(color: Color) -> Color:
    """Invert a color."""
    ...

def color_alpha_blend(dst: Color, src: Color) -> Color:
    """Blend 2 colors together."""
    ...

def color_contrast(color: Color, contrast: float) -> Color:
    """Change contrast of a color."""
    ...

def color_bilinear_interpolate(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: float, coordinateY: float) -> Color:
    """Interpolate colors."""
    ...

# GRAPHICS

def new_image(width: int, height: int, color: Color) -> Image:
    """Create a new blank image."""
    ...

def image_copy(image: Image) -> Image:
    """Copy an image to a new image."""
    ...

def image_subimage(image: Image, x: int, y: int, width: int, height: int) -> Image:
    """Create an image from a region of another image."""
    ...

def clear(color: Color) -> None:
    """Clear the screen."""
    ...

def draw_point(x: int, y: int, color: Color) -> None:
    """Draw a single pixel on the screen."""
    ...

def draw_line(startPosX: int, startPosY: int, endPosX: int, endPosY: int, color: Color) -> None:
    """Draw a line on the screen."""
    ...

def draw_rectangle(posX: int, posY: int, width: int, height: int, color: Color) -> None:
    """Draw a filled rectangle on the screen."""
    ...

def draw_triangle(x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, color: Color) -> None:
    """Draw a filled triangle on the screen."""
    ...

def draw_ellipse(centerX: int, centerY: int, radiusX: int, radiusY: int, color: Color) -> None:
    """Draw a filled ellipse on the screen."""
    ...

def draw_circle(centerX: int, centerY: int, radius: int, color: Color) -> None:
    """Draw a filled circle on the screen."""
    ...

def draw_polygon(points: list[Vector], color: Color) -> None:
    """Draw a filled polygon on the screen."""
    ...

def draw_arc(centerX: int, centerY: int, radius: float, startAngle: float, endAngle: float, segments: int, color: Color) -> None:
    """Draw a filled arc on the screen."""
    ...

def draw_rectangle_rounded(x: int, y: int, width: int, height: int, cornerRadius: int, color: Color) -> None:
    """Draw a filled round-rectangle on the screen."""
    ...

def draw_image(src: Image, posX: int, posY: int) -> None:
    """Draw an image on the screen."""
    ...

def draw_image_tint(src: Image, posX: int, posY: int, tint: Color) -> None:
    """Draw a tinted image on the screen."""
    ...

def draw_image_rotated(src: Image, posX: int, posY: int, degrees: float, offsetX: float, offsetY: float, filter: ImageFilter) -> None:
    """Draw an image, rotated, on the screen."""
    ...

def draw_image_flipped(src: Image, posX: int, posY: int, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) -> None:
    """Draw an image, flipped, on the screen."""
    ...

def draw_image_scaled(src: Image, posX: int, posY: int, scaleX: float, scaleY: float, offsetX: float, offsetY: float, filter: ImageFilter) -> None:
    """Draw an image, scaled, on the screen."""
    ...

def draw_text(font: Font, text: str, posX: int, posY: int, color: Color) -> None:
    """Draw some text on the screen."""
    ...

def save_image(image: Image, filename: str) -> None:
    """Save an image to persistant storage."""
    ...

def load_image(filename: str) -> Image:
    """Load an image from a file in cart."""
    ...

def image_resize(image: Image, newWidth: int, newHeight: int, filter: ImageFilter) -> Image:
    """Resize an image, return copy."""
    ...

def image_scale(image: Image, scaleX: float, scaleY: float, filter: ImageFilter) -> Image:
    """Scale an image, return copy."""
    ...

def image_color_replace(image: Image, color: Color, replace: Color) -> None:
    """Replace a color in an image, in-place."""
    ...

def image_color_tint(image: Image, color: Color) -> None:
    """Tint a color in an image, in-place."""
    ...

def image_color_fade(image: Image, alpha: float) -> None:
    """Fade a color in an image, in-place."""
    ...

def font_copy(font: Font) -> Font:
    """Copy a font to a new font."""
    ...

def font_scale(font: Font, scaleX: float, scaleY: float, filter: ImageFilter) -> Font:
    """Scale a font, return a new font."""
    ...

def load_font_bmf(filename: str, characters: str) -> Font:
    """Load a BMF font from a file in cart."""
    ...

def load_font_bmf_from_image(image: Image, characters: str) -> Font:
    """Load a BMF font from an image."""
    ...

def measure_text(font: Font, text: str, textLength: int) -> Dimensions:
    """Measure the size of some text."""
    ...

def measure_image(image: Image) -> Dimensions:
    """Meaure an image (use 0 for screen)."""
    ...

def load_font_tty(filename: str, glyphWidth: int, glyphHeight: int, characters: str) -> Font:
    """Load a TTY font from a file in cart."""
    ...

def load_font_tty_from_image(image: Image, glyphWidth: int, glyphHeight: int, characters: str) -> Font:
    """Load a TTY font from an image."""
    ...

def load_font_ttf(filename: str, fontSize: int) -> Font:
    """Load a TTF font from a file in cart."""
    ...

def image_color_invert(image: Image) -> None:
    """Invert the colors in an image, in-place."""
    ...

def image_alpha_border(image: Image, threshold: float) -> Rectangle:
    """Calculate a rectangle representing the available alpha border in an image."""
    ...

def image_crop(image: Image, x: int, y: int, width: int, height: int) -> None:
    """Crop an image, in-place."""
    ...

def image_alpha_crop(image: Image, threshold: float) -> None:
    """Crop an image based on the alpha border, in-place."""
    ...

def image_color_brightness(image: Image, factor: float) -> None:
    """Adjust the brightness of an image, in-place."""
    ...

def image_flip(image: Image, horizontal: bool, vertical: bool) -> None:
    """Flip an image, in-place."""
    ...

def image_color_contrast(image: Image, contrast: float) -> None:
    """Change the contrast of an image, in-place."""
    ...

def image_alpha_mask(image: Image, alphaMask: Image, posX: int, posY: int) -> None:
    """Use an image as an alpha-mask on another image."""
    ...

def image_rotate(image: Image, degrees: float, filter: ImageFilter) -> Image:
    """Create a new image, rotating another image."""
    ...

def image_gradient(width: int, height: int, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color) -> Image:
    """Create a new image of a gradient."""
    ...

def unload_image(image: Image) -> None:
    """Unload an image."""
    ...

def unload_font(font: Font) -> None:
    """Unload a font."""
    ...

def clear_image(destination: Image, color: Color) -> None:
    """Clear an image."""
    ...

def draw_point_on_image(destination: Image, x: int, y: int, color: Color) -> None:
    """Draw a single pixel on an image."""
    ...

def draw_line_on_image(destination: Image, startPosX: int, startPosY: int, endPosX: int, endPosY: int, color: Color) -> None:
    """Draw a line on an image."""
    ...

def draw_rectangle_on_image(destination: Image, posX: int, posY: int, width: int, height: int, color: Color) -> None:
    """Draw a filled rectangle on an image."""
    ...

def draw_triangle_on_image(destination: Image, x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, color: Color) -> None:
    """Draw a filled triangle on an image."""
    ...

def draw_ellipse_on_image(destination: Image, centerX: int, centerY: int, radiusX: int, radiusY: int, color: Color) -> None:
    """Draw a filled ellipse on an image."""
    ...

def draw_circle_on_image(destination: Image, centerX: int, centerY: int, radius: int, color: Color) -> None:
    """Draw a circle on an image."""
    ...

def draw_polygon_on_image(destination: Image, points: list[Vector], color: Color) -> None:
    """Draw a filled polygon on an image."""
    ...

def draw_rectangle_rounded_on_image(destination: Image, x: int, y: int, width: int, height: int, cornerRadius: int, color: Color) -> None:
    """Draw a filled round-rectangle on an image."""
    ...

def draw_image_on_image(destination: Image, src: Image, posX: int, posY: int) -> None:
    """Draw an image on an image."""
    ...

def draw_image_tint_on_image(destination: Image, src: Image, posX: int, posY: int, tint: Color) -> None:
    """Draw a tinted image on an image."""
    ...

def draw_image_rotated_on_image(destination: Image, src: Image, posX: int, posY: int, degrees: float, offsetX: float, offsetY: float, filter: ImageFilter) -> None:
    """Draw an image, rotated, on an image."""
    ...

def draw_image_flipped_on_image(destination: Image, src: Image, posX: int, posY: int, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) -> None:
    """Draw an image, flipped, on an image."""
    ...

def draw_image_scaled_on_image(destination: Image, src: Image, posX: int, posY: int, scaleX: float, scaleY: float, offsetX: float, offsetY: float, filter: ImageFilter) -> None:
    """Draw an image, scaled, on an image."""
    ...

def draw_text_on_image(destination: Image, font: Font, text: str, posX: int, posY: int, color: Color) -> None:
    """Draw some text on an image."""
    ...

def draw_rectangle_outline(posX: int, posY: int, width: int, height: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) rectangle on the screen."""
    ...

def draw_triangle_outline(x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) triangle on the screen."""
    ...

def draw_ellipse_outline(centerX: int, centerY: int, radiusX: int, radiusY: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) ellipse on the screen."""
    ...

def draw_circle_outline(centerX: int, centerY: int, radius: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) circle on the screen."""
    ...

def draw_polygon_outline(points: list[Vector], thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) polygon on the screen."""
    ...

def draw_arc_outline(centerX: int, centerY: int, radius: float, startAngle: float, endAngle: float, segments: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) arc on the screen."""
    ...

def draw_rectangle_rounded_outline(x: int, y: int, width: int, height: int, cornerRadius: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) round-rectangle on the screen."""
    ...

def draw_rectangle_outline_on_image(destination: Image, posX: int, posY: int, width: int, height: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) rectangle on an image."""
    ...

def draw_triangle_outline_on_image(destination: Image, x1: int, y1: int, x2: int, y2: int, x3: int, y3: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) triangle on an image."""
    ...

def draw_ellipse_outline_on_image(destination: Image, centerX: int, centerY: int, radiusX: int, radiusY: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) ellipse on an image."""
    ...

def draw_circle_outline_on_image(destination: Image, centerX: int, centerY: int, radius: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) circle on an image."""
    ...

def draw_polygon_outline_on_image(destination: Image, points: list[Vector], thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) polygon on an image."""
    ...

def draw_rectangle_rounded_outline_on_image(destination: Image, x: int, y: int, width: int, height: int, cornerRadius: int, thickness: int, color: Color) -> None:
    """Draw a outlined (with thickness) round-rectangle on an image."""
    ...

# GUI

def gui_begin_window(title: str, rect: Rectangle) -> bool:
    """Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window."""
    ...

def gui_end_window() -> None:
    """End the current GUI window."""
    ...

def gui_button(label: str) -> bool:
    """A button. Returns true when it is clicked."""
    ...

def gui_label(text: str) -> None:
    """A static text label."""
    ...

def gui_text(text: str) -> None:
    """A block of wrapping text."""
    ...

def gui_checkbox(label: str, state: bool) -> bool:
    """A checkbox. Returns the (possibly changed) state."""
    ...

def gui_slider(value: float, low: float, high: float) -> float:
    """A slider. Returns the (possibly changed) value."""
    ...

def gui_layout_row(widths: list[int], height: int) -> None:
    """Set the current layout row - the column widths (negative for flexible), and the row height."""
    ...

def gui_end() -> None:
    """Finish building the GUI for this frame. Called automatically at the end of update if you do not call it."""
    ...

def gui_draw(dst: Image) -> None:
    """Draw the GUI to an image (0 is the screen)."""
    ...

# INPUT

def key_pressed(key: Key) -> bool:
    """Has the key been pressed? (tracks unpress/read correctly.)"""
    ...

def key_down(key: Key) -> bool:
    """Is the key currently down?"""
    ...

def key_released(key: Key) -> bool:
    """Has the key been released? (tracks press/read correctly.)"""
    ...

def key_up(key: Key) -> bool:
    """Is the key currently up?"""
    ...

def gamepad_button_pressed(gamepad: int, button: GamepadButton) -> bool:
    """Has the button been pressed? (tracks unpress/read correctly.)"""
    ...

def gamepad_button_down(gamepad: int, button: GamepadButton) -> bool:
    """Is the button currently down?"""
    ...

def gamepad_button_released(gamepad: int, button: GamepadButton) -> bool:
    """Has the button been released? (tracks press/read correctly.)"""
    ...

def mouse_position() -> Vector:
    """Get current position of mouse."""
    ...

def mouse_button_pressed(button: MouseButton) -> bool:
    """Has the button been pressed? (tracks unpress/read correctly.)"""
    ...

def mouse_button_down(button: MouseButton) -> bool:
    """Is the button currently down?"""
    ...

def mouse_button_released(button: MouseButton) -> bool:
    """Has the button been released? (tracks press/read correctly.)"""
    ...

def mouse_button_up(button: MouseButton) -> bool:
    """Is the button currently up?"""
    ...

# SOUND

def load_sound(filename: str) -> Sound:
    """Load a sound from a file in cart."""
    ...

def play_sound(sound: Sound, loop: bool) -> None:
    """Play a sound."""
    ...

def stop_sound(sound: Sound) -> None:
    """Stop a sound."""
    ...

def unload_sound(sound: Sound) -> None:
    """Unload a sound."""
    ...

def tts_sound(text: str, phonetic: bool, pitch: int, speed: int, throat: int, mouth: int, sing: bool) -> Sound:
    """Speak some text and return a sound. Set things to 0 for defaults."""
    ...

def sfx_sound(params: SfxParams) -> Sound:
    """Create Sfx sound."""
    ...

def sfx_generate(type: SfxPresetType) -> SfxParams:
    """Create Sfx parameters."""
    ...

# TILE

def load_tilemap(filename: str) -> Tilemap:
    """Load a tilemap (a Tiled map, exported as JSON) from a file in cart."""
    ...

def unload_tilemap(tilemap: Tilemap) -> None:
    """Unload a tilemap."""
    ...

def tile_update(tilemap: Tilemap, deltaTime: float) -> None:
    """Update a tilemap's animation timers (deltaTime is in seconds)."""
    ...

def tile_map_size(tilemap: Tilemap) -> Dimensions:
    """Get the size of a tilemap, in tiles."""
    ...

def tile_tile_size(tilemap: Tilemap) -> Dimensions:
    """Get the size of a single tile of a tilemap, in pixels."""
    ...

def tile_map_prop(tilemap: Tilemap, name: str) -> TilemapProp:
    """Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)"""
    ...

def tile_map_prop_count(tilemap: Tilemap) -> int:
    """Get the number of custom properties on a tilemap."""
    ...

def tile_map_prop_at(tilemap: Tilemap, index: int) -> TilemapProp:
    """Get a custom property of a tilemap, by index (PROP_NONE when out of range.)"""
    ...

def tile_draw(tilemap: Tilemap, posX: int, posY: int) -> None:
    """Draw a tilemap on the screen."""
    ...

def tile_draw_tint(tilemap: Tilemap, posX: int, posY: int, tint: Color) -> None:
    """Draw a tilemap on the screen, tinted by a color."""
    ...

def tile_draw_on_image(dst: Image, tilemap: Tilemap, posX: int, posY: int) -> None:
    """Draw a tilemap on an image."""
    ...

def tilemap_image(tilemap: Tilemap) -> Image:
    """Render a whole tilemap to a new image."""
    ...

def tile_layer_count(tilemap: Tilemap) -> int:
    """Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too."""
    ...

def tile_layer_index(tilemap: Tilemap, name: str) -> int:
    """Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)"""
    ...

def tile_layer_name(tilemap: Tilemap, layer: int) -> str:
    """Get the name of a layer of a tilemap."""
    ...

def tile_layer_type(tilemap: Tilemap, layer: int) -> TileLayerKind:
    """Get the kind of a layer of a tilemap."""
    ...

def tile_layer_size(tilemap: Tilemap, layer: int) -> Dimensions:
    """Get the size of a layer of a tilemap, in tiles."""
    ...

def tile_layer_visible(tilemap: Tilemap, layer: int) -> bool:
    """Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing."""
    ...

def tile_layer_prop(tilemap: Tilemap, layer: int, name: str) -> TilemapProp:
    """Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)"""
    ...

def tile_layer_prop_count(tilemap: Tilemap, layer: int) -> int:
    """Get the number of custom properties on a layer of a tilemap."""
    ...

def tile_layer_prop_at(tilemap: Tilemap, layer: int, index: int) -> TilemapProp:
    """Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)"""
    ...

def tile_draw_layer(tilemap: Tilemap, layer: int, posX: int, posY: int) -> None:
    """Draw a single layer of a tilemap on the screen."""
    ...

def tile_draw_layer_tint(tilemap: Tilemap, layer: int, posX: int, posY: int, tint: Color) -> None:
    """Draw a single layer of a tilemap on the screen, tinted by a color."""
    ...

def tile_draw_layer_on_image(dst: Image, tilemap: Tilemap, layer: int, posX: int, posY: int) -> None:
    """Draw a single layer of a tilemap on an image."""
    ...

def tile_layer_image(tilemap: Tilemap, layer: int) -> Image:
    """Render a single layer of a tilemap to a new image."""
    ...

def tile_get_tile(tilemap: Tilemap, layer: int, column: int, row: int) -> int:
    """Get the gid of the tile at a column/row in a tilemap layer."""
    ...

def tile_set_tile(tilemap: Tilemap, layer: int, column: int, row: int, gid: int) -> None:
    """Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself."""
    ...

def tile_draw_tile(tilemap: Tilemap, gid: int, posX: int, posY: int) -> None:
    """Draw a single tile from a tilemap on the screen."""
    ...

def tile_image(tilemap: Tilemap, gid: int) -> Image:
    """Get a copy of the image of a single tile in a tilemap."""
    ...

def tile_gid_prop(tilemap: Tilemap, gid: int, name: str) -> TilemapProp:
    """Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them."""
    ...

def tile_gid_prop_count(tilemap: Tilemap, gid: int) -> int:
    """Get the number of custom properties on a tile of a tilemap."""
    ...

def tile_gid_prop_at(tilemap: Tilemap, gid: int, index: int) -> TilemapProp:
    """Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)"""
    ...

def tile_object_count(tilemap: Tilemap, layer: int) -> int:
    """Get the number of objects on an object-layer of a tilemap."""
    ...

def tile_object(tilemap: Tilemap, layer: int, index: int) -> TilemapObject:
    """Get an object from an object-layer of a tilemap."""
    ...

def tile_object_index(tilemap: Tilemap, layer: int, name: str) -> int:
    """Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)"""
    ...

def tile_object_prop(tilemap: Tilemap, layer: int, index: int, name: str) -> TilemapProp:
    """Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)"""
    ...

def tile_object_prop_count(tilemap: Tilemap, layer: int, index: int) -> int:
    """Get the number of custom properties on an object of a tilemap."""
    ...

def tile_object_prop_at(tilemap: Tilemap, layer: int, index: int, propIndex: int) -> TilemapProp:
    """Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)"""
    ...

# UTILITIES

def current_time() -> int:
    """Get system-time (ms) since unix epoch."""
    ...

def delta_time() -> float:
    """Get the change in time (seconds) since the last update run."""
    ...

def random_int(min: int, max: int) -> int:
    """Get a random integer between 2 numbers."""
    ...

def random_seed_get() -> int:
    """Get the random-seed."""
    ...

def random_seed_set(seed: int) -> None:
    """Set the random-seed."""
    ...

# CONSTANTS

LIGHTGRAY: Color

GRAY: Color

DARKGRAY: Color

YELLOW: Color

GOLD: Color

ORANGE: Color

PINK: Color

RED: Color

MAROON: Color

GREEN: Color

LIME: Color

DARKGREEN: Color

SKYBLUE: Color

BLUE: Color

DARKBLUE: Color

PURPLE: Color

VIOLET: Color

DARKPURPLE: Color

BEIGE: Color

BROWN: Color

DARKBROWN: Color

WHITE: Color

BLACK: Color

# Completely transparent.
BLANK: Color

MAGENTA: Color

# A nice off-white, from Raylib.
RAYWHITE: Color

# The default fonts's number is 0
FONT_DEFAULT: int

# The screen's image number is 0
SCREEN: int

# the width of the screen (in pixels)
SCREEN_WIDTH: int

# the height of the screen (in pixels)
SCREEN_HEIGHT: int

# The current tagged version of null0 engine
NULL0_VERSION: str

# Potential image-filtering techniques for scale/etc.
FILTER_NEARESTNEIGHBOR: ImageFilter
FILTER_BILINEAR: ImageFilter
FILTER_SMOOTH: ImageFilter

# Represents a Sfx preset type.
SFX_COIN: SfxPresetType
SFX_LASER: SfxPresetType
SFX_EXPLOSION: SfxPresetType
SFX_POWERUP: SfxPresetType
SFX_HURT: SfxPresetType
SFX_JUMP: SfxPresetType
SFX_SELECT: SfxPresetType
SFX_SYNTH: SfxPresetType

# Represents a keyboard key.
KEY_INVALID: Key
KEY_SPACE: Key
KEY_APOSTROPHE: Key
KEY_COMMA: Key
KEY_MINUS: Key
KEY_PERIOD: Key
KEY_SLASH: Key
KEY_0: Key
KEY_1: Key
KEY_2: Key
KEY_3: Key
KEY_4: Key
KEY_5: Key
KEY_6: Key
KEY_7: Key
KEY_8: Key
KEY_9: Key
KEY_SEMICOLON: Key
KEY_EQUAL: Key
KEY_A: Key
KEY_B: Key
KEY_C: Key
KEY_D: Key
KEY_E: Key
KEY_F: Key
KEY_G: Key
KEY_H: Key
KEY_I: Key
KEY_J: Key
KEY_K: Key
KEY_L: Key
KEY_M: Key
KEY_N: Key
KEY_O: Key
KEY_P: Key
KEY_Q: Key
KEY_R: Key
KEY_S: Key
KEY_T: Key
KEY_U: Key
KEY_V: Key
KEY_W: Key
KEY_X: Key
KEY_Y: Key
KEY_Z: Key
KEY_LEFT_BRACKET: Key
KEY_BACKSLASH: Key
KEY_RIGHT_BRACKET: Key
KEY_GRAVE_ACCENT: Key
KEY_WORLD_1: Key
KEY_WORLD_2: Key
KEY_ESCAPE: Key
KEY_ENTER: Key
KEY_TAB: Key
KEY_BACKSPACE: Key
KEY_INSERT: Key
KEY_DELETE: Key
KEY_RIGHT: Key
KEY_LEFT: Key
KEY_DOWN: Key
KEY_UP: Key
KEY_PAGE_UP: Key
KEY_PAGE_DOWN: Key
KEY_HOME: Key
KEY_END: Key
KEY_CAPS_LOCK: Key
KEY_SCROLL_LOCK: Key
KEY_NUM_LOCK: Key
KEY_PRINT_SCREEN: Key
KEY_PAUSE: Key
KEY_F1: Key
KEY_F2: Key
KEY_F3: Key
KEY_F4: Key
KEY_F5: Key
KEY_F6: Key
KEY_F7: Key
KEY_F8: Key
KEY_F9: Key
KEY_F10: Key
KEY_F11: Key
KEY_F12: Key
KEY_F13: Key
KEY_F14: Key
KEY_F15: Key
KEY_F16: Key
KEY_F17: Key
KEY_F18: Key
KEY_F19: Key
KEY_F20: Key
KEY_F21: Key
KEY_F22: Key
KEY_F23: Key
KEY_F24: Key
KEY_F25: Key
KEY_KP_0: Key
KEY_KP_1: Key
KEY_KP_2: Key
KEY_KP_3: Key
KEY_KP_4: Key
KEY_KP_5: Key
KEY_KP_6: Key
KEY_KP_7: Key
KEY_KP_8: Key
KEY_KP_9: Key
KEY_KP_DECIMAL: Key
KEY_KP_DIVIDE: Key
KEY_KP_MULTIPLY: Key
KEY_KP_SUBTRACT: Key
KEY_KP_ADD: Key
KEY_KP_ENTER: Key
KEY_KP_EQUAL: Key
KEY_LEFT_SHIFT: Key
KEY_LEFT_CONTROL: Key
KEY_LEFT_ALT: Key
KEY_LEFT_SUPER: Key
KEY_RIGHT_SHIFT: Key
KEY_RIGHT_CONTROL: Key
KEY_RIGHT_ALT: Key
KEY_RIGHT_SUPER: Key
KEY_MENU: Key

# Represents a gamepad button.
GAMEPAD_BUTTON_UNKNOWN: GamepadButton
GAMEPAD_BUTTON_UP: GamepadButton
GAMEPAD_BUTTON_RIGHT: GamepadButton
GAMEPAD_BUTTON_DOWN: GamepadButton
GAMEPAD_BUTTON_LEFT: GamepadButton
GAMEPAD_BUTTON_Y: GamepadButton
GAMEPAD_BUTTON_B: GamepadButton
GAMEPAD_BUTTON_A: GamepadButton
GAMEPAD_BUTTON_X: GamepadButton
GAMEPAD_BUTTON_LEFT_SHOULDER: GamepadButton
GAMEPAD_BUTTON_LEFT_TRIGGER: GamepadButton
GAMEPAD_BUTTON_RIGHT_SHOULDER: GamepadButton
GAMEPAD_BUTTON_RIGHT_TRIGGER: GamepadButton
GAMEPAD_BUTTON_SELECT: GamepadButton
GAMEPAD_BUTTON_MENU: GamepadButton
GAMEPAD_BUTTON_START: GamepadButton
GAMEPAD_BUTTON_LEFT_THUMB: GamepadButton
GAMEPAD_BUTTON_RIGHT_THUMB: GamepadButton

# Represents a mouse button.
MOUSE_BUTTON_UNKNOWN: MouseButton
MOUSE_BUTTON_LEFT: MouseButton
MOUSE_BUTTON_RIGHT: MouseButton
MOUSE_BUTTON_MIDDLE: MouseButton

# The kind of a layer in a tilemap.
LAYER_NONE: TileLayerKind
LAYER_TILE: TileLayerKind
LAYER_OBJECT: TileLayerKind
LAYER_IMAGE: TileLayerKind
LAYER_GROUP: TileLayerKind

# The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING.
PROP_NONE: TilePropType
PROP_INT: TilePropType
PROP_BOOL: TilePropType
PROP_FLOAT: TilePropType
PROP_STRING: TilePropType
PROP_COLOR: TilePropType

# CALLBACKS
#
# Define the ones you need in main.py - the host skips any you leave out.
#
# Called once when the cart is loaded.
#     def load(): ...
# Called on every frame.
#     def update(): ...
# Called when the cart is unloaded.
#     def unload(): ...
# Mapped controller (keys and gamepad will trigger) callback for when a "button" is unpressed.
#     def buttonUp(button, player): ...
# Mapped controller (keys and gamepad will trigger) callback for when a "button" is pressed.
#     def buttonDown(button, player): ...
# Called when keys are unpressed.
#     def keyUp(key): ...
# Called when keys are pressed.
#     def keyDown(key): ...
# Called when mouse-button is pressed.
#     def mouseDown(button): ...
# Called when mouse-button is released.
#     def mouseUp(button): ...
# Called when mouse is moved.
#     def mouseMoved(x, y): ...
