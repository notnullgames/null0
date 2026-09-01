-- null0 - Cyber bindings for the null0 fantasy console
--
-- GENERATED FILE - do not edit by hand. See tools/gen_cart_cyber.js
--
-- This module is baked into the cyber cart-runtime, so carts can just do:
--
-- ```cyber
-- use null0
--
-- fn load():
--   null0.clear(null0.BLUE)
--   null0.draw_circle(100, 100, 50, null0.RED)
-- ```
--
-- Callbacks (load/update/unload/buttonUp/buttonDown/keyUp/keyDown/mouseUp/
-- mouseDown/mouseMoved) are top-level fns in main.cy - implement the ones
-- you need.

-- Sfx parameters.
type SfxParams struct:
  randSeed r32
  waveType i32
  attackTime f32
  sustainTime f32
  sustainPunch f32
  decayTime f32
  startFrequency f32
  minFrequency f32
  slide f32
  deltaSlide f32
  vibratoDepth f32
  vibratoSpeed f32
  changeAmount f32
  changeSpeed f32
  squareDuty f32
  dutySweep f32
  repeatSpeed f32
  phaserOffset f32
  phaserSweep f32
  lpfCutoff f32
  lpfCutoffSweep f32
  lpfResonance f32
  hpfCutoff f32
  hpfCutoffSweep f32

-- The 2D size of something (width/height.)
type Dimensions struct:
  width i32
  height i32

-- The 2D position of something (x/y.)
type Vector struct:
  x i32
  y i32

-- The 2D position + size of something (x/y/w/h.)
type Rectangle struct:
  x i32
  y i32
  width i32
  height i32

-- An RGBA color.
type Color struct:
  r byte
  g byte
  b byte
  a byte

-- A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`.
type TilemapProp struct:
  name str
  type i32
  integer i32
  number f32
  text str

-- An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it.
type TilemapObject struct:
  id i32
  name str
  type str
  gid i32
  x f32
  y f32
  width f32
  height f32
  rotation f32
  visible i32

-- COLORS
-- Tint a color with another color.
#[bind] fn color_tint(color Color, tint Color) -> Color
-- Fade a color.
#[bind] fn color_fade(color Color, alpha f32) -> Color
-- Change the brightness of a color.
#[bind] fn color_brightness(color Color, factor f32) -> Color
-- Invert a color.
#[bind] fn color_invert(color Color) -> Color
-- Blend 2 colors together.
#[bind] fn color_alpha_blend(dst Color, src Color) -> Color
-- Change contrast of a color.
#[bind] fn color_contrast(color Color, contrast f32) -> Color
-- Interpolate colors.
#[bind] fn color_bilinear_interpolate(color00 Color, color01 Color, color10 Color, color11 Color, coordinateX f32, coordinateY f32) -> Color

-- GRAPHICS
-- Create a new blank image.
#[bind] fn new_image(width i32, height i32, color Color) -> r32
-- Copy an image to a new image.
#[bind] fn image_copy(image r32) -> r32
-- Create an image from a region of another image.
#[bind] fn image_subimage(image r32, x i32, y i32, width i32, height i32) -> r32
-- Clear the screen.
#[bind] fn clear(color Color)
-- Draw a single pixel on the screen.
#[bind] fn draw_point(x i32, y i32, color Color)
-- Draw a line on the screen.
#[bind] fn draw_line(startPosX i32, startPosY i32, endPosX i32, endPosY i32, color Color)
-- Draw a filled rectangle on the screen.
#[bind] fn draw_rectangle(posX i32, posY i32, width i32, height i32, color Color)
-- Draw a filled triangle on the screen.
#[bind] fn draw_triangle(x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, color Color)
-- Draw a filled ellipse on the screen.
#[bind] fn draw_ellipse(centerX i32, centerY i32, radiusX i32, radiusY i32, color Color)
-- Draw a filled circle on the screen.
#[bind] fn draw_circle(centerX i32, centerY i32, radius i32, color Color)
-- Draw a filled polygon on the screen.
#[bind] fn draw_polygon(points []Vector, color Color)
-- Draw a filled arc on the screen.
#[bind] fn draw_arc(centerX i32, centerY i32, radius f32, startAngle f32, endAngle f32, segments i32, color Color)
-- Draw a filled round-rectangle on the screen.
#[bind] fn draw_rectangle_rounded(x i32, y i32, width i32, height i32, cornerRadius i32, color Color)
-- Draw an image on the screen.
#[bind] fn draw_image(src r32, posX i32, posY i32)
-- Draw a tinted image on the screen.
#[bind] fn draw_image_tint(src r32, posX i32, posY i32, tint Color)
-- Draw an image, rotated, on the screen.
#[bind] fn draw_image_rotated(src r32, posX i32, posY i32, degrees f32, offsetX f32, offsetY f32, filter i32)
-- Draw an image, flipped, on the screen.
#[bind] fn draw_image_flipped(src r32, posX i32, posY i32, flipHorizontal bool, flipVertical bool, flipDiagonal bool)
-- Draw an image, scaled, on the screen.
#[bind] fn draw_image_scaled(src r32, posX i32, posY i32, scaleX f32, scaleY f32, offsetX f32, offsetY f32, filter i32)
-- Draw some text on the screen.
#[bind] fn draw_text(font r32, text str, posX i32, posY i32, color Color)
-- Save an image to persistant storage.
#[bind] fn save_image(image r32, filename str)
-- Load an image from a file in cart.
#[bind] fn load_image(filename str) -> r32
-- Resize an image, return copy.
#[bind] fn image_resize(image r32, newWidth i32, newHeight i32, filter i32) -> r32
-- Scale an image, return copy.
#[bind] fn image_scale(image r32, scaleX f32, scaleY f32, filter i32) -> r32
-- Replace a color in an image, in-place.
#[bind] fn image_color_replace(image r32, color Color, replace Color)
-- Tint a color in an image, in-place.
#[bind] fn image_color_tint(image r32, color Color)
-- Fade a color in an image, in-place.
#[bind] fn image_color_fade(image r32, alpha f32)
-- Copy a font to a new font.
#[bind] fn font_copy(font r32) -> r32
-- Scale a font, return a new font.
#[bind] fn font_scale(font r32, scaleX f32, scaleY f32, filter i32) -> r32
-- Load a BMF font from a file in cart.
#[bind] fn load_font_bmf(filename str, characters str) -> r32
-- Load a BMF font from an image.
#[bind] fn load_font_bmf_from_image(image r32, characters str) -> r32
-- Measure the size of some text.
#[bind] fn measure_text(font r32, text str, textLength i32) -> Dimensions
-- Meaure an image (use 0 for screen).
#[bind] fn measure_image(image r32) -> Dimensions
-- Load a TTY font from a file in cart.
#[bind] fn load_font_tty(filename str, glyphWidth i32, glyphHeight i32, characters str) -> r32
-- Load a TTY font from an image.
#[bind] fn load_font_tty_from_image(image r32, glyphWidth i32, glyphHeight i32, characters str) -> r32
-- Load a TTF font from a file in cart.
#[bind] fn load_font_ttf(filename str, fontSize i32) -> r32
-- Invert the colors in an image, in-place.
#[bind] fn image_color_invert(image r32)
-- Calculate a rectangle representing the available alpha border in an image.
#[bind] fn image_alpha_border(image r32, threshold f32) -> Rectangle
-- Crop an image, in-place.
#[bind] fn image_crop(image r32, x i32, y i32, width i32, height i32)
-- Crop an image based on the alpha border, in-place.
#[bind] fn image_alpha_crop(image r32, threshold f32)
-- Adjust the brightness of an image, in-place.
#[bind] fn image_color_brightness(image r32, factor f32)
-- Flip an image, in-place.
#[bind] fn image_flip(image r32, horizontal bool, vertical bool)
-- Change the contrast of an image, in-place.
#[bind] fn image_color_contrast(image r32, contrast f32)
-- Use an image as an alpha-mask on another image.
#[bind] fn image_alpha_mask(image r32, alphaMask r32, posX i32, posY i32)
-- Create a new image, rotating another image.
#[bind] fn image_rotate(image r32, degrees f32, filter i32) -> r32
-- Create a new image of a gradient.
#[bind] fn image_gradient(width i32, height i32, topLeft Color, topRight Color, bottomLeft Color, bottomRight Color) -> r32
-- Unload an image.
#[bind] fn unload_image(image r32)
-- Unload a font.
#[bind] fn unload_font(font r32)
-- Clear an image.
#[bind] fn clear_image(destination r32, color Color)
-- Draw a single pixel on an image.
#[bind] fn draw_point_on_image(destination r32, x i32, y i32, color Color)
-- Draw a line on an image.
#[bind] fn draw_line_on_image(destination r32, startPosX i32, startPosY i32, endPosX i32, endPosY i32, color Color)
-- Draw a filled rectangle on an image.
#[bind] fn draw_rectangle_on_image(destination r32, posX i32, posY i32, width i32, height i32, color Color)
-- Draw a filled triangle on an image.
#[bind] fn draw_triangle_on_image(destination r32, x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, color Color)
-- Draw a filled ellipse on an image.
#[bind] fn draw_ellipse_on_image(destination r32, centerX i32, centerY i32, radiusX i32, radiusY i32, color Color)
-- Draw a circle on an image.
#[bind] fn draw_circle_on_image(destination r32, centerX i32, centerY i32, radius i32, color Color)
-- Draw a filled polygon on an image.
#[bind] fn draw_polygon_on_image(destination r32, points []Vector, color Color)
-- Draw a filled round-rectangle on an image.
#[bind] fn draw_rectangle_rounded_on_image(destination r32, x i32, y i32, width i32, height i32, cornerRadius i32, color Color)
-- Draw an image on an image.
#[bind] fn draw_image_on_image(destination r32, src r32, posX i32, posY i32)
-- Draw a tinted image on an image.
#[bind] fn draw_image_tint_on_image(destination r32, src r32, posX i32, posY i32, tint Color)
-- Draw an image, rotated, on an image.
#[bind] fn draw_image_rotated_on_image(destination r32, src r32, posX i32, posY i32, degrees f32, offsetX f32, offsetY f32, filter i32)
-- Draw an image, flipped, on an image.
#[bind] fn draw_image_flipped_on_image(destination r32, src r32, posX i32, posY i32, flipHorizontal bool, flipVertical bool, flipDiagonal bool)
-- Draw an image, scaled, on an image.
#[bind] fn draw_image_scaled_on_image(destination r32, src r32, posX i32, posY i32, scaleX f32, scaleY f32, offsetX f32, offsetY f32, filter i32)
-- Draw some text on an image.
#[bind] fn draw_text_on_image(destination r32, font r32, text str, posX i32, posY i32, color Color)
-- Draw a outlined (with thickness) rectangle on the screen.
#[bind] fn draw_rectangle_outline(posX i32, posY i32, width i32, height i32, thickness i32, color Color)
-- Draw a outlined (with thickness) triangle on the screen.
#[bind] fn draw_triangle_outline(x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, thickness i32, color Color)
-- Draw a outlined (with thickness) ellipse on the screen.
#[bind] fn draw_ellipse_outline(centerX i32, centerY i32, radiusX i32, radiusY i32, thickness i32, color Color)
-- Draw a outlined (with thickness) circle on the screen.
#[bind] fn draw_circle_outline(centerX i32, centerY i32, radius i32, thickness i32, color Color)
-- Draw a outlined (with thickness) polygon on the screen.
#[bind] fn draw_polygon_outline(points []Vector, thickness i32, color Color)
-- Draw a outlined (with thickness) arc on the screen.
#[bind] fn draw_arc_outline(centerX i32, centerY i32, radius f32, startAngle f32, endAngle f32, segments i32, thickness i32, color Color)
-- Draw a outlined (with thickness) round-rectangle on the screen.
#[bind] fn draw_rectangle_rounded_outline(x i32, y i32, width i32, height i32, cornerRadius i32, thickness i32, color Color)
-- Draw a outlined (with thickness) rectangle on an image.
#[bind] fn draw_rectangle_outline_on_image(destination r32, posX i32, posY i32, width i32, height i32, thickness i32, color Color)
-- Draw a outlined (with thickness) triangle on an image.
#[bind] fn draw_triangle_outline_on_image(destination r32, x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, thickness i32, color Color)
-- Draw a outlined (with thickness) ellipse on an image.
#[bind] fn draw_ellipse_outline_on_image(destination r32, centerX i32, centerY i32, radiusX i32, radiusY i32, thickness i32, color Color)
-- Draw a outlined (with thickness) circle on an image.
#[bind] fn draw_circle_outline_on_image(destination r32, centerX i32, centerY i32, radius i32, thickness i32, color Color)
-- Draw a outlined (with thickness) polygon on an image.
#[bind] fn draw_polygon_outline_on_image(destination r32, points []Vector, thickness i32, color Color)
-- Draw a outlined (with thickness) round-rectangle on an image.
#[bind] fn draw_rectangle_rounded_outline_on_image(destination r32, x i32, y i32, width i32, height i32, cornerRadius i32, thickness i32, color Color)

-- GUI
-- Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.
#[bind] fn gui_begin_window(title str, rect Rectangle) -> bool
-- End the current GUI window.
#[bind] fn gui_end_window()
-- A button. Returns true when it is clicked.
#[bind] fn gui_button(label str) -> bool
-- A static text label.
#[bind] fn gui_label(text str)
-- A block of wrapping text.
#[bind] fn gui_text(text str)
-- A checkbox. Returns the (possibly changed) state.
#[bind] fn gui_checkbox(label str, state bool) -> bool
-- A slider. Returns the (possibly changed) value.
#[bind] fn gui_slider(value f32, low f32, high f32) -> f32
-- Set the current layout row - the column widths (negative for flexible), and the row height.
#[bind] fn gui_layout_row(widths []i32, height i32)
-- Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.
#[bind] fn gui_end()
-- Draw the GUI to an image (0 is the screen).
#[bind] fn gui_draw(dst r32)

-- INPUT
-- Has the key been pressed? (tracks unpress/read correctly.)
#[bind] fn key_pressed(key i32) -> bool
-- Is the key currently down?
#[bind] fn key_down(key i32) -> bool
-- Has the key been released? (tracks press/read correctly.)
#[bind] fn key_released(key i32) -> bool
-- Is the key currently up?
#[bind] fn key_up(key i32) -> bool
-- Has the button been pressed? (tracks unpress/read correctly.)
#[bind] fn gamepad_button_pressed(gamepad i32, button i32) -> bool
-- Is the button currently down?
#[bind] fn gamepad_button_down(gamepad i32, button i32) -> bool
-- Has the button been released? (tracks press/read correctly.)
#[bind] fn gamepad_button_released(gamepad i32, button i32) -> bool
-- Get current position of mouse.
#[bind] fn mouse_position() -> Vector
-- Has the button been pressed? (tracks unpress/read correctly.)
#[bind] fn mouse_button_pressed(button i32) -> bool
-- Is the button currently down?
#[bind] fn mouse_button_down(button i32) -> bool
-- Has the button been released? (tracks press/read correctly.)
#[bind] fn mouse_button_released(button i32) -> bool
-- Is the button currently up?
#[bind] fn mouse_button_up(button i32) -> bool

-- SOUND
-- Load a sound from a file in cart.
#[bind] fn load_sound(filename str) -> r32
-- Play a sound.
#[bind] fn play_sound(sound r32, loop bool)
-- Stop a sound.
#[bind] fn stop_sound(sound r32)
-- Unload a sound.
#[bind] fn unload_sound(sound r32)
-- Speak some text and return a sound. Set things to 0 for defaults.
#[bind] fn tts_sound(text str, phonetic bool, pitch i32, speed i32, throat i32, mouth i32, sing bool) -> r32
-- Create Sfx sound.
#[bind] fn sfx_sound(params SfxParams) -> r32
-- Create Sfx parameters.
#[bind] fn sfx_generate(type_ i32) -> SfxParams

-- TILE
-- Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
#[bind] fn load_tilemap(filename str) -> r32
-- Unload a tilemap.
#[bind] fn unload_tilemap(tilemap r32)
-- Update a tilemap's animation timers (deltaTime is in seconds).
#[bind] fn tile_update(tilemap r32, deltaTime f32)
-- Get the size of a tilemap, in tiles.
#[bind] fn tile_map_size(tilemap r32) -> Dimensions
-- Get the size of a single tile of a tilemap, in pixels.
#[bind] fn tile_tile_size(tilemap r32) -> Dimensions
-- Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)
#[bind] fn tile_map_prop(tilemap r32, name str) -> TilemapProp
-- Get the number of custom properties on a tilemap.
#[bind] fn tile_map_prop_count(tilemap r32) -> i32
-- Get a custom property of a tilemap, by index (PROP_NONE when out of range.)
#[bind] fn tile_map_prop_at(tilemap r32, index i32) -> TilemapProp
-- Draw a tilemap on the screen.
#[bind] fn tile_draw(tilemap r32, posX i32, posY i32)
-- Draw a tilemap on the screen, tinted by a color.
#[bind] fn tile_draw_tint(tilemap r32, posX i32, posY i32, tint Color)
-- Draw a tilemap on an image.
#[bind] fn tile_draw_on_image(dst r32, tilemap r32, posX i32, posY i32)
-- Render a whole tilemap to a new image.
#[bind] fn tilemap_image(tilemap r32) -> r32
-- Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.
#[bind] fn tile_layer_count(tilemap r32) -> i32
-- Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)
#[bind] fn tile_layer_index(tilemap r32, name str) -> i32
-- Get the name of a layer of a tilemap.
#[bind] fn tile_layer_name(tilemap r32, layer i32) -> str
-- Get the kind of a layer of a tilemap.
#[bind] fn tile_layer_type(tilemap r32, layer i32) -> i32
-- Get the size of a layer of a tilemap, in tiles.
#[bind] fn tile_layer_size(tilemap r32, layer i32) -> Dimensions
-- Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.
#[bind] fn tile_layer_visible(tilemap r32, layer i32) -> bool
-- Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)
#[bind] fn tile_layer_prop(tilemap r32, layer i32, name str) -> TilemapProp
-- Get the number of custom properties on a layer of a tilemap.
#[bind] fn tile_layer_prop_count(tilemap r32, layer i32) -> i32
-- Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)
#[bind] fn tile_layer_prop_at(tilemap r32, layer i32, index i32) -> TilemapProp
-- Draw a single layer of a tilemap on the screen.
#[bind] fn tile_draw_layer(tilemap r32, layer i32, posX i32, posY i32)
-- Draw a single layer of a tilemap on the screen, tinted by a color.
#[bind] fn tile_draw_layer_tint(tilemap r32, layer i32, posX i32, posY i32, tint Color)
-- Draw a single layer of a tilemap on an image.
#[bind] fn tile_draw_layer_on_image(dst r32, tilemap r32, layer i32, posX i32, posY i32)
-- Render a single layer of a tilemap to a new image.
#[bind] fn tile_layer_image(tilemap r32, layer i32) -> r32
-- Get the gid of the tile at a column/row in a tilemap layer.
#[bind] fn tile_get_tile(tilemap r32, layer i32, column i32, row i32) -> i32
-- Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.
#[bind] fn tile_set_tile(tilemap r32, layer i32, column i32, row i32, gid i32)
-- Draw a single tile from a tilemap on the screen.
#[bind] fn tile_draw_tile(tilemap r32, gid i32, posX i32, posY i32)
-- Get a copy of the image of a single tile in a tilemap.
#[bind] fn tile_image(tilemap r32, gid i32) -> r32
-- Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.
#[bind] fn tile_gid_prop(tilemap r32, gid i32, name str) -> TilemapProp
-- Get the number of custom properties on a tile of a tilemap.
#[bind] fn tile_gid_prop_count(tilemap r32, gid i32) -> i32
-- Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)
#[bind] fn tile_gid_prop_at(tilemap r32, gid i32, index i32) -> TilemapProp
-- Get the number of objects on an object-layer of a tilemap.
#[bind] fn tile_object_count(tilemap r32, layer i32) -> i32
-- Get an object from an object-layer of a tilemap.
#[bind] fn tile_object(tilemap r32, layer i32, index i32) -> TilemapObject
-- Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)
#[bind] fn tile_object_index(tilemap r32, layer i32, name str) -> i32
-- Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)
#[bind] fn tile_object_prop(tilemap r32, layer i32, index i32, name str) -> TilemapProp
-- Get the number of custom properties on an object of a tilemap.
#[bind] fn tile_object_prop_count(tilemap r32, layer i32, index i32) -> i32
-- Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)
#[bind] fn tile_object_prop_at(tilemap r32, layer i32, index i32, propIndex i32) -> TilemapProp

-- TYPES

-- UTILITIES
-- Get system-time (ms) since unix epoch.
#[bind] fn current_time() -> r64
-- Get the change in time (seconds) since the last update run.
#[bind] fn delta_time() -> f32
-- Get a random integer between 2 numbers.
#[bind] fn random_int(min i32, max i32) -> i32
-- Get the random-seed.
#[bind] fn random_seed_get() -> r64
-- Set the random-seed.
#[bind] fn random_seed_set(seed r64)

-- The screen is image 0
global SCREEN i32 = 0
global SCREEN_WIDTH i32 = 640
global SCREEN_HEIGHT i32 = 480
-- The built-in font
global FONT_DEFAULT i32 = 0

global LIGHTGRAY Color = Color{r=200, g=200, b=200, a=255}
global GRAY Color = Color{r=130, g=130, b=130, a=255}
global DARKGRAY Color = Color{r=80, g=80, b=80, a=255}
global YELLOW Color = Color{r=253, g=249, b=0, a=255}
global GOLD Color = Color{r=255, g=203, b=0, a=255}
global ORANGE Color = Color{r=255, g=161, b=0, a=255}
global PINK Color = Color{r=255, g=109, b=194, a=255}
global RED Color = Color{r=230, g=41, b=55, a=255}
global MAROON Color = Color{r=190, g=33, b=55, a=255}
global GREEN Color = Color{r=0, g=228, b=48, a=255}
global LIME Color = Color{r=0, g=158, b=47, a=255}
global DARKGREEN Color = Color{r=0, g=117, b=44, a=255}
global SKYBLUE Color = Color{r=102, g=191, b=255, a=255}
global BLUE Color = Color{r=0, g=121, b=241, a=255}
global DARKBLUE Color = Color{r=0, g=82, b=172, a=255}
global PURPLE Color = Color{r=200, g=122, b=255, a=255}
global VIOLET Color = Color{r=135, g=60, b=190, a=255}
global DARKPURPLE Color = Color{r=112, g=31, b=126, a=255}
global BEIGE Color = Color{r=211, g=176, b=131, a=255}
global BROWN Color = Color{r=127, g=106, b=79, a=255}
global DARKBROWN Color = Color{r=76, g=63, b=47, a=255}
global WHITE Color = Color{r=255, g=255, b=255, a=255}
global BLACK Color = Color{r=0, g=0, b=0, a=255}
global BLANK Color = Color{r=0, g=0, b=0, a=0}
global MAGENTA Color = Color{r=255, g=0, b=255, a=255}
global RAYWHITE Color = Color{r=245, g=245, b=245, a=255}
-- The current tagged version of null0 engine
global NULL0_VERSION str = '0.0.16'

-- Potential image-filtering techniques for scale/etc.
global FILTER_NEARESTNEIGHBOR i32 = 0
global FILTER_BILINEAR i32 = 1
global FILTER_SMOOTH i32 = 2
-- Represents a Sfx preset type.
global SFX_COIN i32 = 0
global SFX_LASER i32 = 1
global SFX_EXPLOSION i32 = 2
global SFX_POWERUP i32 = 3
global SFX_HURT i32 = 4
global SFX_JUMP i32 = 5
global SFX_SELECT i32 = 6
global SFX_SYNTH i32 = 7
-- Represents a keyboard key.
global KEY_INVALID i32 = 0
global KEY_SPACE i32 = 32
global KEY_APOSTROPHE i32 = 39
global KEY_COMMA i32 = 44
global KEY_MINUS i32 = 45
global KEY_PERIOD i32 = 46
global KEY_SLASH i32 = 47
global KEY_0 i32 = 48
global KEY_1 i32 = 49
global KEY_2 i32 = 50
global KEY_3 i32 = 51
global KEY_4 i32 = 52
global KEY_5 i32 = 53
global KEY_6 i32 = 54
global KEY_7 i32 = 55
global KEY_8 i32 = 56
global KEY_9 i32 = 57
global KEY_SEMICOLON i32 = 59
global KEY_EQUAL i32 = 61
global KEY_A i32 = 65
global KEY_B i32 = 66
global KEY_C i32 = 67
global KEY_D i32 = 68
global KEY_E i32 = 69
global KEY_F i32 = 70
global KEY_G i32 = 71
global KEY_H i32 = 72
global KEY_I i32 = 73
global KEY_J i32 = 74
global KEY_K i32 = 75
global KEY_L i32 = 76
global KEY_M i32 = 77
global KEY_N i32 = 78
global KEY_O i32 = 79
global KEY_P i32 = 80
global KEY_Q i32 = 81
global KEY_R i32 = 82
global KEY_S i32 = 83
global KEY_T i32 = 84
global KEY_U i32 = 85
global KEY_V i32 = 86
global KEY_W i32 = 87
global KEY_X i32 = 88
global KEY_Y i32 = 89
global KEY_Z i32 = 90
global KEY_LEFT_BRACKET i32 = 91
global KEY_BACKSLASH i32 = 92
global KEY_RIGHT_BRACKET i32 = 93
global KEY_GRAVE_ACCENT i32 = 96
global KEY_WORLD_1 i32 = 161
global KEY_WORLD_2 i32 = 162
global KEY_ESCAPE i32 = 256
global KEY_ENTER i32 = 257
global KEY_TAB i32 = 258
global KEY_BACKSPACE i32 = 259
global KEY_INSERT i32 = 260
global KEY_DELETE i32 = 261
global KEY_RIGHT i32 = 262
global KEY_LEFT i32 = 263
global KEY_DOWN i32 = 264
global KEY_UP i32 = 265
global KEY_PAGE_UP i32 = 266
global KEY_PAGE_DOWN i32 = 267
global KEY_HOME i32 = 268
global KEY_END i32 = 269
global KEY_CAPS_LOCK i32 = 280
global KEY_SCROLL_LOCK i32 = 281
global KEY_NUM_LOCK i32 = 282
global KEY_PRINT_SCREEN i32 = 283
global KEY_PAUSE i32 = 284
global KEY_F1 i32 = 290
global KEY_F2 i32 = 291
global KEY_F3 i32 = 292
global KEY_F4 i32 = 293
global KEY_F5 i32 = 294
global KEY_F6 i32 = 295
global KEY_F7 i32 = 296
global KEY_F8 i32 = 297
global KEY_F9 i32 = 298
global KEY_F10 i32 = 299
global KEY_F11 i32 = 300
global KEY_F12 i32 = 301
global KEY_F13 i32 = 302
global KEY_F14 i32 = 303
global KEY_F15 i32 = 304
global KEY_F16 i32 = 305
global KEY_F17 i32 = 306
global KEY_F18 i32 = 307
global KEY_F19 i32 = 308
global KEY_F20 i32 = 309
global KEY_F21 i32 = 310
global KEY_F22 i32 = 311
global KEY_F23 i32 = 312
global KEY_F24 i32 = 313
global KEY_F25 i32 = 314
global KEY_KP_0 i32 = 320
global KEY_KP_1 i32 = 321
global KEY_KP_2 i32 = 322
global KEY_KP_3 i32 = 323
global KEY_KP_4 i32 = 324
global KEY_KP_5 i32 = 325
global KEY_KP_6 i32 = 326
global KEY_KP_7 i32 = 327
global KEY_KP_8 i32 = 328
global KEY_KP_9 i32 = 329
global KEY_KP_DECIMAL i32 = 330
global KEY_KP_DIVIDE i32 = 331
global KEY_KP_MULTIPLY i32 = 332
global KEY_KP_SUBTRACT i32 = 333
global KEY_KP_ADD i32 = 334
global KEY_KP_ENTER i32 = 335
global KEY_KP_EQUAL i32 = 336
global KEY_LEFT_SHIFT i32 = 340
global KEY_LEFT_CONTROL i32 = 341
global KEY_LEFT_ALT i32 = 342
global KEY_LEFT_SUPER i32 = 343
global KEY_RIGHT_SHIFT i32 = 344
global KEY_RIGHT_CONTROL i32 = 345
global KEY_RIGHT_ALT i32 = 346
global KEY_RIGHT_SUPER i32 = 347
global KEY_MENU i32 = 348
-- Represents a gamepad button.
global GAMEPAD_BUTTON_UNKNOWN i32 = 0
global GAMEPAD_BUTTON_UP i32 = 1
global GAMEPAD_BUTTON_RIGHT i32 = 2
global GAMEPAD_BUTTON_DOWN i32 = 3
global GAMEPAD_BUTTON_LEFT i32 = 4
global GAMEPAD_BUTTON_Y i32 = 5
global GAMEPAD_BUTTON_B i32 = 6
global GAMEPAD_BUTTON_A i32 = 7
global GAMEPAD_BUTTON_X i32 = 8
global GAMEPAD_BUTTON_LEFT_SHOULDER i32 = 9
global GAMEPAD_BUTTON_LEFT_TRIGGER i32 = 10
global GAMEPAD_BUTTON_RIGHT_SHOULDER i32 = 11
global GAMEPAD_BUTTON_RIGHT_TRIGGER i32 = 12
global GAMEPAD_BUTTON_SELECT i32 = 13
global GAMEPAD_BUTTON_MENU i32 = 14
global GAMEPAD_BUTTON_START i32 = 15
global GAMEPAD_BUTTON_LEFT_THUMB i32 = 16
global GAMEPAD_BUTTON_RIGHT_THUMB i32 = 17
-- Represents a mouse button.
global MOUSE_BUTTON_UNKNOWN i32 = 0
global MOUSE_BUTTON_LEFT i32 = 1
global MOUSE_BUTTON_RIGHT i32 = 2
global MOUSE_BUTTON_MIDDLE i32 = 3
-- The kind of a layer in a tilemap.
global LAYER_NONE i32 = 0
global LAYER_TILE i32 = 1
global LAYER_OBJECT i32 = 2
global LAYER_IMAGE i32 = 3
global LAYER_GROUP i32 = 4
-- The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING.
global PROP_NONE i32 = 0
global PROP_INT i32 = 1
global PROP_BOOL i32 = 2
global PROP_FLOAT i32 = 3
global PROP_STRING i32 = 4
global PROP_COLOR i32 = 5
