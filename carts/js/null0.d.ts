// null0 - typescript definitions for the null0 fantasy console
//
// GENERATED FILE - do not edit by hand. See tools/gen_cart_js.js
//
// The null0 API is available as plain globals in your cart - nothing to
// import, same as the lua/python carts. This file is only here so editors
// can complete & check your cart:
//
// ```js
// export function load () {
//   clear(BLUE)
//   draw_circle(100, 100, 50, RED)
// }
// ```
//
// Put null0.d.ts next to main.js and your editor will pick it up. If it
// doesn't, add this line to the top of main.js:
//
//     /// <reference path="./null0.d.ts" />

export {}

declare global {
  // TYPES

  /** An image. 0 is "the screen". */
  type Image = number

  /** A font. 0 is "the default font". */
  type Font = number

  /** A sound. */
  type Sound = number

  /** A tilemap (a Tiled map, exported as JSON). 0 is an invalid tilemap. */
  type Tilemap = number

  /** Sfx parameters. */
  interface SfxParams {
    randSeed: number
    waveType: number
    attackTime: number
    sustainTime: number
    sustainPunch: number
    decayTime: number
    startFrequency: number
    minFrequency: number
    slide: number
    deltaSlide: number
    vibratoDepth: number
    vibratoSpeed: number
    changeAmount: number
    changeSpeed: number
    squareDuty: number
    dutySweep: number
    repeatSpeed: number
    phaserOffset: number
    phaserSweep: number
    lpfCutoff: number
    lpfCutoffSweep: number
    lpfResonance: number
    hpfCutoff: number
    hpfCutoffSweep: number
  }

  /** The 2D size of something (width/height.) */
  interface Dimensions {
    width: number
    height: number
  }

  /** The 2D position of something (x/y.) */
  interface Vector {
    x: number
    y: number
  }

  /** The 2D position + size of something (x/y/w/h.) */
  interface Rectangle {
    x: number
    y: number
    width: number
    height: number
  }

  /** An RGBA color. */
  interface Color {
    r: number
    g: number
    b: number
    a: number
  }

  /** A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`. */
  interface TilemapProp {
    name: string
    type: TilePropType
    integer: number
    number: number
    text: string
  }

  /** An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it. */
  interface TilemapObject {
    id: number
    name: string
    type: string
    gid: number
    x: number
    y: number
    width: number
    height: number
    rotation: number
    visible: number
  }

  /** Potential image-filtering techniques for scale/etc. */
  type ImageFilter = 0 | 1 | 2

  /** Represents a Sfx preset type. */
  type SfxPresetType = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7

  /** Represents a keyboard key. */
  type Key = 0 | 32 | 39 | 44 | 45 | 46 | 47 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 59 | 61 | 65 | 66 | 67 | 68 | 69 | 70 | 71 | 72 | 73 | 74 | 75 | 76 | 77 | 78 | 79 | 80 | 81 | 82 | 83 | 84 | 85 | 86 | 87 | 88 | 89 | 90 | 91 | 92 | 93 | 96 | 161 | 162 | 256 | 257 | 258 | 259 | 260 | 261 | 262 | 263 | 264 | 265 | 266 | 267 | 268 | 269 | 280 | 281 | 282 | 283 | 284 | 290 | 291 | 292 | 293 | 294 | 295 | 296 | 297 | 298 | 299 | 300 | 301 | 302 | 303 | 304 | 305 | 306 | 307 | 308 | 309 | 310 | 311 | 312 | 313 | 314 | 320 | 321 | 322 | 323 | 324 | 325 | 326 | 327 | 328 | 329 | 330 | 331 | 332 | 333 | 334 | 335 | 336 | 340 | 341 | 342 | 343 | 344 | 345 | 346 | 347 | 348

  /** Represents a gamepad button. */
  type GamepadButton = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17

  /** Represents a mouse button. */
  type MouseButton = 0 | 1 | 2 | 3

  /** The kind of a layer in a tilemap. */
  type TileLayerKind = 0 | 1 | 2 | 3 | 4

  /** The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING. */
  type TilePropType = 0 | 1 | 2 | 3 | 4 | 5

  // COLORS

  /** Tint a color with another color. */
  function color_tint(color: Color, tint: Color): Color

  /** Fade a color. */
  function color_fade(color: Color, alpha: number): Color

  /** Change the brightness of a color. */
  function color_brightness(color: Color, factor: number): Color

  /** Invert a color. */
  function color_invert(color: Color): Color

  /** Blend 2 colors together. */
  function color_alpha_blend(dst: Color, src: Color): Color

  /** Change contrast of a color. */
  function color_contrast(color: Color, contrast: number): Color

  /** Interpolate colors. */
  function color_bilinear_interpolate(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: number, coordinateY: number): Color

  // GRAPHICS

  /** Create a new blank image. */
  function new_image(width: number, height: number, color: Color): Image

  /** Copy an image to a new image. */
  function image_copy(image: Image): Image

  /** Create an image from a region of another image. */
  function image_subimage(image: Image, x: number, y: number, width: number, height: number): Image

  /** Clear the screen. */
  function clear(color: Color): void

  /** Draw a single pixel on the screen. */
  function draw_point(x: number, y: number, color: Color): void

  /** Draw a line on the screen. */
  function draw_line(startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void

  /** Draw a filled rectangle on the screen. */
  function draw_rectangle(posX: number, posY: number, width: number, height: number, color: Color): void

  /** Draw a filled triangle on the screen. */
  function draw_triangle(x1: number, y1: number, x2: number, y2: number, x3: number, y3: number, color: Color): void

  /** Draw a filled ellipse on the screen. */
  function draw_ellipse(centerX: number, centerY: number, radiusX: number, radiusY: number, color: Color): void

  /** Draw a filled circle on the screen. */
  function draw_circle(centerX: number, centerY: number, radius: number, color: Color): void

  /** Draw a filled polygon on the screen. */
  function draw_polygon(points: Vector[], color: Color): void

  /** Draw a filled arc on the screen. */
  function draw_arc(centerX: number, centerY: number, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void

  /** Draw a filled round-rectangle on the screen. */
  function draw_rectangle_rounded(x: number, y: number, width: number, height: number, cornerRadius: number, color: Color): void

  /** Draw an image on the screen. */
  function draw_image(src: Image, posX: number, posY: number): void

  /** Draw a tinted image on the screen. */
  function draw_image_tint(src: Image, posX: number, posY: number, tint: Color): void

  /** Draw an image, rotated, on the screen. */
  function draw_image_rotated(src: Image, posX: number, posY: number, degrees: number, offsetX: number, offsetY: number, filter: ImageFilter): void

  /** Draw an image, flipped, on the screen. */
  function draw_image_flipped(src: Image, posX: number, posY: number, flipHorizontal: boolean, flipVertical: boolean, flipDiagonal: boolean): void

  /** Draw an image, scaled, on the screen. */
  function draw_image_scaled(src: Image, posX: number, posY: number, scaleX: number, scaleY: number, offsetX: number, offsetY: number, filter: ImageFilter): void

  /** Draw some text on the screen. */
  function draw_text(font: Font, text: string, posX: number, posY: number, color: Color): void

  /** Save an image to persistant storage. */
  function save_image(image: Image, filename: string): void

  /** Load an image from a file in cart. */
  function load_image(filename: string): Image

  /** Resize an image, return copy. */
  function image_resize(image: Image, newWidth: number, newHeight: number, filter: ImageFilter): Image

  /** Scale an image, return copy. */
  function image_scale(image: Image, scaleX: number, scaleY: number, filter: ImageFilter): Image

  /** Replace a color in an image, in-place. */
  function image_color_replace(image: Image, color: Color, replace: Color): void

  /** Tint a color in an image, in-place. */
  function image_color_tint(image: Image, color: Color): void

  /** Fade a color in an image, in-place. */
  function image_color_fade(image: Image, alpha: number): void

  /** Copy a font to a new font. */
  function font_copy(font: Font): Font

  /** Scale a font, return a new font. */
  function font_scale(font: Font, scaleX: number, scaleY: number, filter: ImageFilter): Font

  /** Load a BMF font from a file in cart. */
  function load_font_bmf(filename: string, characters: string): Font

  /** Load a BMF font from an image. */
  function load_font_bmf_from_image(image: Image, characters: string): Font

  /** Measure the size of some text. */
  function measure_text(font: Font, text: string, textLength: number): Dimensions

  /** Meaure an image (use 0 for screen). */
  function measure_image(image: Image): Dimensions

  /** Load a TTY font from a file in cart. */
  function load_font_tty(filename: string, glyphWidth: number, glyphHeight: number, characters: string): Font

  /** Load a TTY font from an image. */
  function load_font_tty_from_image(image: Image, glyphWidth: number, glyphHeight: number, characters: string): Font

  /** Load a TTF font from a file in cart. */
  function load_font_ttf(filename: string, fontSize: number): Font

  /** Invert the colors in an image, in-place. */
  function image_color_invert(image: Image): void

  /** Calculate a rectangle representing the available alpha border in an image. */
  function image_alpha_border(image: Image, threshold: number): Rectangle

  /** Crop an image, in-place. */
  function image_crop(image: Image, x: number, y: number, width: number, height: number): void

  /** Crop an image based on the alpha border, in-place. */
  function image_alpha_crop(image: Image, threshold: number): void

  /** Adjust the brightness of an image, in-place. */
  function image_color_brightness(image: Image, factor: number): void

  /** Flip an image, in-place. */
  function image_flip(image: Image, horizontal: boolean, vertical: boolean): void

  /** Change the contrast of an image, in-place. */
  function image_color_contrast(image: Image, contrast: number): void

  /** Use an image as an alpha-mask on another image. */
  function image_alpha_mask(image: Image, alphaMask: Image, posX: number, posY: number): void

  /** Create a new image, rotating another image. */
  function image_rotate(image: Image, degrees: number, filter: ImageFilter): Image

  /** Create a new image of a gradient. */
  function image_gradient(width: number, height: number, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color): Image

  /** Unload an image. */
  function unload_image(image: Image): void

  /** Unload a font. */
  function unload_font(font: Font): void

  /** Clear an image. */
  function clear_image(destination: Image, color: Color): void

  /** Draw a single pixel on an image. */
  function draw_point_on_image(destination: Image, x: number, y: number, color: Color): void

  /** Draw a line on an image. */
  function draw_line_on_image(destination: Image, startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void

  /** Draw a filled rectangle on an image. */
  function draw_rectangle_on_image(destination: Image, posX: number, posY: number, width: number, height: number, color: Color): void

  /** Draw a filled triangle on an image. */
  function draw_triangle_on_image(destination: Image, x1: number, y1: number, x2: number, y2: number, x3: number, y3: number, color: Color): void

  /** Draw a filled ellipse on an image. */
  function draw_ellipse_on_image(destination: Image, centerX: number, centerY: number, radiusX: number, radiusY: number, color: Color): void

  /** Draw a circle on an image. */
  function draw_circle_on_image(destination: Image, centerX: number, centerY: number, radius: number, color: Color): void

  /** Draw a filled polygon on an image. */
  function draw_polygon_on_image(destination: Image, points: Vector[], color: Color): void

  /** Draw a filled round-rectangle on an image. */
  function draw_rectangle_rounded_on_image(destination: Image, x: number, y: number, width: number, height: number, cornerRadius: number, color: Color): void

  /** Draw an image on an image. */
  function draw_image_on_image(destination: Image, src: Image, posX: number, posY: number): void

  /** Draw a tinted image on an image. */
  function draw_image_tint_on_image(destination: Image, src: Image, posX: number, posY: number, tint: Color): void

  /** Draw an image, rotated, on an image. */
  function draw_image_rotated_on_image(destination: Image, src: Image, posX: number, posY: number, degrees: number, offsetX: number, offsetY: number, filter: ImageFilter): void

  /** Draw an image, flipped, on an image. */
  function draw_image_flipped_on_image(destination: Image, src: Image, posX: number, posY: number, flipHorizontal: boolean, flipVertical: boolean, flipDiagonal: boolean): void

  /** Draw an image, scaled, on an image. */
  function draw_image_scaled_on_image(destination: Image, src: Image, posX: number, posY: number, scaleX: number, scaleY: number, offsetX: number, offsetY: number, filter: ImageFilter): void

  /** Draw some text on an image. */
  function draw_text_on_image(destination: Image, font: Font, text: string, posX: number, posY: number, color: Color): void

  /** Draw a outlined (with thickness) rectangle on the screen. */
  function draw_rectangle_outline(posX: number, posY: number, width: number, height: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) triangle on the screen. */
  function draw_triangle_outline(x1: number, y1: number, x2: number, y2: number, x3: number, y3: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) ellipse on the screen. */
  function draw_ellipse_outline(centerX: number, centerY: number, radiusX: number, radiusY: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) circle on the screen. */
  function draw_circle_outline(centerX: number, centerY: number, radius: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) polygon on the screen. */
  function draw_polygon_outline(points: Vector[], thickness: number, color: Color): void

  /** Draw a outlined (with thickness) arc on the screen. */
  function draw_arc_outline(centerX: number, centerY: number, radius: number, startAngle: number, endAngle: number, segments: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) round-rectangle on the screen. */
  function draw_rectangle_rounded_outline(x: number, y: number, width: number, height: number, cornerRadius: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) rectangle on an image. */
  function draw_rectangle_outline_on_image(destination: Image, posX: number, posY: number, width: number, height: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) triangle on an image. */
  function draw_triangle_outline_on_image(destination: Image, x1: number, y1: number, x2: number, y2: number, x3: number, y3: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) ellipse on an image. */
  function draw_ellipse_outline_on_image(destination: Image, centerX: number, centerY: number, radiusX: number, radiusY: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) circle on an image. */
  function draw_circle_outline_on_image(destination: Image, centerX: number, centerY: number, radius: number, thickness: number, color: Color): void

  /** Draw a outlined (with thickness) polygon on an image. */
  function draw_polygon_outline_on_image(destination: Image, points: Vector[], thickness: number, color: Color): void

  /** Draw a outlined (with thickness) round-rectangle on an image. */
  function draw_rectangle_rounded_outline_on_image(destination: Image, x: number, y: number, width: number, height: number, cornerRadius: number, thickness: number, color: Color): void

  // GUI

  /** Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window. */
  function gui_begin_window(title: string, rect: Rectangle): boolean

  /** End the current GUI window. */
  function gui_end_window(): void

  /** A button. Returns true when it is clicked. */
  function gui_button(label: string): boolean

  /** A static text label. */
  function gui_label(text: string): void

  /** A block of wrapping text. */
  function gui_text(text: string): void

  /** A checkbox. Returns the (possibly changed) state. */
  function gui_checkbox(label: string, state: boolean): boolean

  /** A slider. Returns the (possibly changed) value. */
  function gui_slider(value: number, low: number, high: number): number

  /** Set the current layout row - the column widths (negative for flexible), and the row height. */
  function gui_layout_row(widths: number[], height: number): void

  /** Finish building the GUI for this frame. Called automatically at the end of update if you do not call it. */
  function gui_end(): void

  /** Draw the GUI to an image (0 is the screen). */
  function gui_draw(dst: Image): void

  // INPUT

  /** Has the key been pressed? (tracks unpress/read correctly.) */
  function key_pressed(key: Key): boolean

  /** Is the key currently down? */
  function key_down(key: Key): boolean

  /** Has the key been released? (tracks press/read correctly.) */
  function key_released(key: Key): boolean

  /** Is the key currently up? */
  function key_up(key: Key): boolean

  /** Has the button been pressed? (tracks unpress/read correctly.) */
  function gamepad_button_pressed(gamepad: number, button: GamepadButton): boolean

  /** Is the button currently down? */
  function gamepad_button_down(gamepad: number, button: GamepadButton): boolean

  /** Has the button been released? (tracks press/read correctly.) */
  function gamepad_button_released(gamepad: number, button: GamepadButton): boolean

  /** Get current position of mouse. */
  function mouse_position(): Vector

  /** Has the button been pressed? (tracks unpress/read correctly.) */
  function mouse_button_pressed(button: MouseButton): boolean

  /** Is the button currently down? */
  function mouse_button_down(button: MouseButton): boolean

  /** Has the button been released? (tracks press/read correctly.) */
  function mouse_button_released(button: MouseButton): boolean

  /** Is the button currently up? */
  function mouse_button_up(button: MouseButton): boolean

  // SOUND

  /** Load a sound from a file in cart. */
  function load_sound(filename: string): Sound

  /** Play a sound. */
  function play_sound(sound: Sound, loop: boolean): void

  /** Stop a sound. */
  function stop_sound(sound: Sound): void

  /** Unload a sound. */
  function unload_sound(sound: Sound): void

  /** Speak some text and return a sound. Set things to 0 for defaults. */
  function tts_sound(text: string, phonetic: boolean, pitch: number, speed: number, throat: number, mouth: number, sing: boolean): Sound

  /** Create Sfx sound. */
  function sfx_sound(params: SfxParams): Sound

  /** Create Sfx parameters. */
  function sfx_generate(type: SfxPresetType): SfxParams

  // TILE

  /** Load a tilemap (a Tiled map, exported as JSON) from a file in cart. */
  function load_tilemap(filename: string): Tilemap

  /** Unload a tilemap. */
  function unload_tilemap(tilemap: Tilemap): void

  /** Update a tilemap's animation timers (deltaTime is in seconds). */
  function tile_update(tilemap: Tilemap, deltaTime: number): void

  /** Get the size of a tilemap, in tiles. */
  function tile_map_size(tilemap: Tilemap): Dimensions

  /** Get the size of a single tile of a tilemap, in pixels. */
  function tile_tile_size(tilemap: Tilemap): Dimensions

  /** Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.) */
  function tile_map_prop(tilemap: Tilemap, name: string): TilemapProp

  /** Get the number of custom properties on a tilemap. */
  function tile_map_prop_count(tilemap: Tilemap): number

  /** Get a custom property of a tilemap, by index (PROP_NONE when out of range.) */
  function tile_map_prop_at(tilemap: Tilemap, index: number): TilemapProp

  /** Draw a tilemap on the screen. */
  function tile_draw(tilemap: Tilemap, posX: number, posY: number): void

  /** Draw a tilemap on the screen, tinted by a color. */
  function tile_draw_tint(tilemap: Tilemap, posX: number, posY: number, tint: Color): void

  /** Draw a tilemap on an image. */
  function tile_draw_on_image(dst: Image, tilemap: Tilemap, posX: number, posY: number): void

  /** Render a whole tilemap to a new image. */
  function tilemap_image(tilemap: Tilemap): Image

  /** Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too. */
  function tile_layer_count(tilemap: Tilemap): number

  /** Get the index of a layer of a tilemap, by name (-1 when there is no such layer.) */
  function tile_layer_index(tilemap: Tilemap, name: string): number

  /** Get the name of a layer of a tilemap. */
  function tile_layer_name(tilemap: Tilemap, layer: number): string

  /** Get the kind of a layer of a tilemap. */
  function tile_layer_type(tilemap: Tilemap, layer: number): TileLayerKind

  /** Get the size of a layer of a tilemap, in tiles. */
  function tile_layer_size(tilemap: Tilemap, layer: number): Dimensions

  /** Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing. */
  function tile_layer_visible(tilemap: Tilemap, layer: number): boolean

  /** Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.) */
  function tile_layer_prop(tilemap: Tilemap, layer: number, name: string): TilemapProp

  /** Get the number of custom properties on a layer of a tilemap. */
  function tile_layer_prop_count(tilemap: Tilemap, layer: number): number

  /** Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.) */
  function tile_layer_prop_at(tilemap: Tilemap, layer: number, index: number): TilemapProp

  /** Draw a single layer of a tilemap on the screen. */
  function tile_draw_layer(tilemap: Tilemap, layer: number, posX: number, posY: number): void

  /** Draw a single layer of a tilemap on the screen, tinted by a color. */
  function tile_draw_layer_tint(tilemap: Tilemap, layer: number, posX: number, posY: number, tint: Color): void

  /** Draw a single layer of a tilemap on an image. */
  function tile_draw_layer_on_image(dst: Image, tilemap: Tilemap, layer: number, posX: number, posY: number): void

  /** Render a single layer of a tilemap to a new image. */
  function tile_layer_image(tilemap: Tilemap, layer: number): Image

  /** Get the gid of the tile at a column/row in a tilemap layer. */
  function tile_get_tile(tilemap: Tilemap, layer: number, column: number, row: number): number

  /** Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself. */
  function tile_set_tile(tilemap: Tilemap, layer: number, column: number, row: number, gid: number): void

  /** Draw a single tile from a tilemap on the screen. */
  function tile_draw_tile(tilemap: Tilemap, gid: number, posX: number, posY: number): void

  /** Get a copy of the image of a single tile in a tilemap. */
  function tile_image(tilemap: Tilemap, gid: number): Image

  /** Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them. */
  function tile_gid_prop(tilemap: Tilemap, gid: number, name: string): TilemapProp

  /** Get the number of custom properties on a tile of a tilemap. */
  function tile_gid_prop_count(tilemap: Tilemap, gid: number): number

  /** Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.) */
  function tile_gid_prop_at(tilemap: Tilemap, gid: number, index: number): TilemapProp

  /** Get the number of objects on an object-layer of a tilemap. */
  function tile_object_count(tilemap: Tilemap, layer: number): number

  /** Get an object from an object-layer of a tilemap. */
  function tile_object(tilemap: Tilemap, layer: number, index: number): TilemapObject

  /** Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.) */
  function tile_object_index(tilemap: Tilemap, layer: number, name: string): number

  /** Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.) */
  function tile_object_prop(tilemap: Tilemap, layer: number, index: number, name: string): TilemapProp

  /** Get the number of custom properties on an object of a tilemap. */
  function tile_object_prop_count(tilemap: Tilemap, layer: number, index: number): number

  /** Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.) */
  function tile_object_prop_at(tilemap: Tilemap, layer: number, index: number, propIndex: number): TilemapProp

  // UTILITIES

  /** Get system-time (ms) since unix epoch. */
  function current_time(): bigint

  /** Get the change in time (seconds) since the last update run. */
  function delta_time(): number

  /** Get a random integer between 2 numbers. */
  function random_int(min: number, max: number): number

  /** Get the random-seed. */
  function random_seed_get(): bigint

  /** Set the random-seed. */
  function random_seed_set(seed: bigint): void

  // CONSTANTS

  const LIGHTGRAY: Color

  const GRAY: Color

  const DARKGRAY: Color

  const YELLOW: Color

  const GOLD: Color

  const ORANGE: Color

  const PINK: Color

  const RED: Color

  const MAROON: Color

  const GREEN: Color

  const LIME: Color

  const DARKGREEN: Color

  const SKYBLUE: Color

  const BLUE: Color

  const DARKBLUE: Color

  const PURPLE: Color

  const VIOLET: Color

  const DARKPURPLE: Color

  const BEIGE: Color

  const BROWN: Color

  const DARKBROWN: Color

  const WHITE: Color

  const BLACK: Color

  /** Completely transparent. */
  const BLANK: Color

  const MAGENTA: Color

  /** A nice off-white, from Raylib. */
  const RAYWHITE: Color

  /** The default fonts's number is 0 */
  const FONT_DEFAULT: number

  /** The screen's image number is 0 */
  const SCREEN: number

  /** the width of the screen (in pixels) */
  const SCREEN_WIDTH: number

  /** the height of the screen (in pixels) */
  const SCREEN_HEIGHT: number

  /** The current tagged version of null0 engine */
  const NULL0_VERSION: string

  // Potential image-filtering techniques for scale/etc.
  const FILTER_NEARESTNEIGHBOR: 0
  const FILTER_BILINEAR: 1
  const FILTER_SMOOTH: 2

  // Represents a Sfx preset type.
  const SFX_COIN: 0
  const SFX_LASER: 1
  const SFX_EXPLOSION: 2
  const SFX_POWERUP: 3
  const SFX_HURT: 4
  const SFX_JUMP: 5
  const SFX_SELECT: 6
  const SFX_SYNTH: 7

  // Represents a keyboard key.
  const KEY_INVALID: 0
  const KEY_SPACE: 32
  const KEY_APOSTROPHE: 39
  const KEY_COMMA: 44
  const KEY_MINUS: 45
  const KEY_PERIOD: 46
  const KEY_SLASH: 47
  const KEY_0: 48
  const KEY_1: 49
  const KEY_2: 50
  const KEY_3: 51
  const KEY_4: 52
  const KEY_5: 53
  const KEY_6: 54
  const KEY_7: 55
  const KEY_8: 56
  const KEY_9: 57
  const KEY_SEMICOLON: 59
  const KEY_EQUAL: 61
  const KEY_A: 65
  const KEY_B: 66
  const KEY_C: 67
  const KEY_D: 68
  const KEY_E: 69
  const KEY_F: 70
  const KEY_G: 71
  const KEY_H: 72
  const KEY_I: 73
  const KEY_J: 74
  const KEY_K: 75
  const KEY_L: 76
  const KEY_M: 77
  const KEY_N: 78
  const KEY_O: 79
  const KEY_P: 80
  const KEY_Q: 81
  const KEY_R: 82
  const KEY_S: 83
  const KEY_T: 84
  const KEY_U: 85
  const KEY_V: 86
  const KEY_W: 87
  const KEY_X: 88
  const KEY_Y: 89
  const KEY_Z: 90
  const KEY_LEFT_BRACKET: 91
  const KEY_BACKSLASH: 92
  const KEY_RIGHT_BRACKET: 93
  const KEY_GRAVE_ACCENT: 96
  const KEY_WORLD_1: 161
  const KEY_WORLD_2: 162
  const KEY_ESCAPE: 256
  const KEY_ENTER: 257
  const KEY_TAB: 258
  const KEY_BACKSPACE: 259
  const KEY_INSERT: 260
  const KEY_DELETE: 261
  const KEY_RIGHT: 262
  const KEY_LEFT: 263
  const KEY_DOWN: 264
  const KEY_UP: 265
  const KEY_PAGE_UP: 266
  const KEY_PAGE_DOWN: 267
  const KEY_HOME: 268
  const KEY_END: 269
  const KEY_CAPS_LOCK: 280
  const KEY_SCROLL_LOCK: 281
  const KEY_NUM_LOCK: 282
  const KEY_PRINT_SCREEN: 283
  const KEY_PAUSE: 284
  const KEY_F1: 290
  const KEY_F2: 291
  const KEY_F3: 292
  const KEY_F4: 293
  const KEY_F5: 294
  const KEY_F6: 295
  const KEY_F7: 296
  const KEY_F8: 297
  const KEY_F9: 298
  const KEY_F10: 299
  const KEY_F11: 300
  const KEY_F12: 301
  const KEY_F13: 302
  const KEY_F14: 303
  const KEY_F15: 304
  const KEY_F16: 305
  const KEY_F17: 306
  const KEY_F18: 307
  const KEY_F19: 308
  const KEY_F20: 309
  const KEY_F21: 310
  const KEY_F22: 311
  const KEY_F23: 312
  const KEY_F24: 313
  const KEY_F25: 314
  const KEY_KP_0: 320
  const KEY_KP_1: 321
  const KEY_KP_2: 322
  const KEY_KP_3: 323
  const KEY_KP_4: 324
  const KEY_KP_5: 325
  const KEY_KP_6: 326
  const KEY_KP_7: 327
  const KEY_KP_8: 328
  const KEY_KP_9: 329
  const KEY_KP_DECIMAL: 330
  const KEY_KP_DIVIDE: 331
  const KEY_KP_MULTIPLY: 332
  const KEY_KP_SUBTRACT: 333
  const KEY_KP_ADD: 334
  const KEY_KP_ENTER: 335
  const KEY_KP_EQUAL: 336
  const KEY_LEFT_SHIFT: 340
  const KEY_LEFT_CONTROL: 341
  const KEY_LEFT_ALT: 342
  const KEY_LEFT_SUPER: 343
  const KEY_RIGHT_SHIFT: 344
  const KEY_RIGHT_CONTROL: 345
  const KEY_RIGHT_ALT: 346
  const KEY_RIGHT_SUPER: 347
  const KEY_MENU: 348

  // Represents a gamepad button.
  const GAMEPAD_BUTTON_UNKNOWN: 0
  const GAMEPAD_BUTTON_UP: 1
  const GAMEPAD_BUTTON_RIGHT: 2
  const GAMEPAD_BUTTON_DOWN: 3
  const GAMEPAD_BUTTON_LEFT: 4
  const GAMEPAD_BUTTON_Y: 5
  const GAMEPAD_BUTTON_B: 6
  const GAMEPAD_BUTTON_A: 7
  const GAMEPAD_BUTTON_X: 8
  const GAMEPAD_BUTTON_LEFT_SHOULDER: 9
  const GAMEPAD_BUTTON_LEFT_TRIGGER: 10
  const GAMEPAD_BUTTON_RIGHT_SHOULDER: 11
  const GAMEPAD_BUTTON_RIGHT_TRIGGER: 12
  const GAMEPAD_BUTTON_SELECT: 13
  const GAMEPAD_BUTTON_MENU: 14
  const GAMEPAD_BUTTON_START: 15
  const GAMEPAD_BUTTON_LEFT_THUMB: 16
  const GAMEPAD_BUTTON_RIGHT_THUMB: 17

  // Represents a mouse button.
  const MOUSE_BUTTON_UNKNOWN: 0
  const MOUSE_BUTTON_LEFT: 1
  const MOUSE_BUTTON_RIGHT: 2
  const MOUSE_BUTTON_MIDDLE: 3

  // The kind of a layer in a tilemap.
  const LAYER_NONE: 0
  const LAYER_TILE: 1
  const LAYER_OBJECT: 2
  const LAYER_IMAGE: 3
  const LAYER_GROUP: 4

  // The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING.
  const PROP_NONE: 0
  const PROP_INT: 1
  const PROP_BOOL: 2
  const PROP_FLOAT: 3
  const PROP_STRING: 4
  const PROP_COLOR: 5

}

/**
 * The callbacks a cart can export from main.js. Implement the ones you need -
 * the host skips any you leave out.
 *
 * This interface is documentation: your main.js just exports the functions.
 */
export interface Null0Cart {
  /** Called once when the cart is loaded. */
  load?(): void

  /** Called on every frame. */
  update?(): void

  /** Called when the cart is unloaded. */
  unload?(): void

  /** Mapped controller (keys and gamepad will trigger) callback for when a "button" is unpressed. */
  buttonUp?(button: GamepadButton, player: number): void

  /** Mapped controller (keys and gamepad will trigger) callback for when a "button" is pressed. */
  buttonDown?(button: GamepadButton, player: number): void

  /** Called when keys are unpressed. */
  keyUp?(key: Key): void

  /** Called when keys are pressed. */
  keyDown?(key: Key): void

  /** Called when mouse-button is pressed. */
  mouseDown?(button: MouseButton): void

  /** Called when mouse-button is released. */
  mouseUp?(button: MouseButton): void

  /** Called when mouse is moved. */
  mouseMoved?(x: number, y: number): void
}
