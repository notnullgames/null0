// GENERATED FILE - do not edit by hand. See tools/gen_cart_cyber.js
//
// The cyber cart-runtime: a Cyber VM with the null0 API bound to it. It
// evals main.cy from the cart once (with persist_main, so its top-level
// fns/vars stay in scope), then re-evals tiny snippets like "update()" to
// invoke callbacks - see the comment in gen_cart_cyber.js for why.

#include "null0.h"
#include "cyber.h"
#include <string.h>

static CLVM* vm = NULL;
static CLEvalConfig persist_cfg;

// two generic slots for passing callback args into a snippet eval,
// without string-formatting numbers into source text
static f32 g_a0 = 0;
static f32 g_a1 = 0;

// the null0 module, baked in so carts do not have to ship it
static const char* NULL0_CY =
  "-- null0 - Cyber bindings for the null0 fantasy console\n"
  "--\n"
  "-- GENERATED FILE - do not edit by hand. See tools/gen_cart_cyber.js\n"
  "--\n"
  "-- This module is baked into the cyber cart-runtime, so carts can just do:\n"
  "--\n"
  "-- ```cyber\n"
  "-- use null0\n"
  "--\n"
  "-- fn load():\n"
  "--   null0.clear(null0.BLUE)\n"
  "--   null0.draw_circle(100, 100, 50, null0.RED)\n"
  "-- ```\n"
  "--\n"
  "-- Callbacks (load/update/unload/buttonUp/buttonDown/keyUp/keyDown/mouseUp/\n"
  "-- mouseDown/mouseMoved) are top-level fns in main.cy - implement the ones\n"
  "-- you need.\n"
  "\n"
  "-- Sfx parameters.\n"
  "type SfxParams struct:\n"
  "  randSeed r32\n"
  "  waveType i32\n"
  "  attackTime f32\n"
  "  sustainTime f32\n"
  "  sustainPunch f32\n"
  "  decayTime f32\n"
  "  startFrequency f32\n"
  "  minFrequency f32\n"
  "  slide f32\n"
  "  deltaSlide f32\n"
  "  vibratoDepth f32\n"
  "  vibratoSpeed f32\n"
  "  changeAmount f32\n"
  "  changeSpeed f32\n"
  "  squareDuty f32\n"
  "  dutySweep f32\n"
  "  repeatSpeed f32\n"
  "  phaserOffset f32\n"
  "  phaserSweep f32\n"
  "  lpfCutoff f32\n"
  "  lpfCutoffSweep f32\n"
  "  lpfResonance f32\n"
  "  hpfCutoff f32\n"
  "  hpfCutoffSweep f32\n"
  "\n"
  "-- The 2D size of something (width/height.)\n"
  "type Dimensions struct:\n"
  "  width i32\n"
  "  height i32\n"
  "\n"
  "-- The 2D position of something (x/y.)\n"
  "type Vector struct:\n"
  "  x i32\n"
  "  y i32\n"
  "\n"
  "-- The 2D position + size of something (x/y/w/h.)\n"
  "type Rectangle struct:\n"
  "  x i32\n"
  "  y i32\n"
  "  width i32\n"
  "  height i32\n"
  "\n"
  "-- An RGBA color.\n"
  "type Color struct:\n"
  "  r byte\n"
  "  g byte\n"
  "  b byte\n"
  "  a byte\n"
  "\n"
  "-- A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`.\n"
  "type TilemapProp struct:\n"
  "  name str\n"
  "  type i32\n"
  "  integer i32\n"
  "  number f32\n"
  "  text str\n"
  "\n"
  "-- An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it.\n"
  "type TilemapObject struct:\n"
  "  id i32\n"
  "  name str\n"
  "  type str\n"
  "  gid i32\n"
  "  x f32\n"
  "  y f32\n"
  "  width f32\n"
  "  height f32\n"
  "  rotation f32\n"
  "  visible i32\n"
  "\n"
  "-- COLORS\n"
  "-- Tint a color with another color.\n"
  "#[bind] fn color_tint(color Color, tint Color) -> Color\n"
  "-- Fade a color.\n"
  "#[bind] fn color_fade(color Color, alpha f32) -> Color\n"
  "-- Change the brightness of a color.\n"
  "#[bind] fn color_brightness(color Color, factor f32) -> Color\n"
  "-- Invert a color.\n"
  "#[bind] fn color_invert(color Color) -> Color\n"
  "-- Blend 2 colors together.\n"
  "#[bind] fn color_alpha_blend(dst Color, src Color) -> Color\n"
  "-- Change contrast of a color.\n"
  "#[bind] fn color_contrast(color Color, contrast f32) -> Color\n"
  "-- Interpolate colors.\n"
  "#[bind] fn color_bilinear_interpolate(color00 Color, color01 Color, color10 Color, color11 Color, coordinateX f32, coordinateY f32) -> Color\n"
  "\n"
  "-- GRAPHICS\n"
  "-- Create a new blank image.\n"
  "#[bind] fn new_image(width i32, height i32, color Color) -> r32\n"
  "-- Copy an image to a new image.\n"
  "#[bind] fn image_copy(image r32) -> r32\n"
  "-- Create an image from a region of another image.\n"
  "#[bind] fn image_subimage(image r32, x i32, y i32, width i32, height i32) -> r32\n"
  "-- Clear the screen.\n"
  "#[bind] fn clear(color Color)\n"
  "-- Draw a single pixel on the screen.\n"
  "#[bind] fn draw_point(x i32, y i32, color Color)\n"
  "-- Draw a line on the screen.\n"
  "#[bind] fn draw_line(startPosX i32, startPosY i32, endPosX i32, endPosY i32, color Color)\n"
  "-- Draw a filled rectangle on the screen.\n"
  "#[bind] fn draw_rectangle(posX i32, posY i32, width i32, height i32, color Color)\n"
  "-- Draw a filled triangle on the screen.\n"
  "#[bind] fn draw_triangle(x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, color Color)\n"
  "-- Draw a filled ellipse on the screen.\n"
  "#[bind] fn draw_ellipse(centerX i32, centerY i32, radiusX i32, radiusY i32, color Color)\n"
  "-- Draw a filled circle on the screen.\n"
  "#[bind] fn draw_circle(centerX i32, centerY i32, radius i32, color Color)\n"
  "-- Draw a filled polygon on the screen.\n"
  "#[bind] fn draw_polygon(points []Vector, color Color)\n"
  "-- Draw a filled arc on the screen.\n"
  "#[bind] fn draw_arc(centerX i32, centerY i32, radius f32, startAngle f32, endAngle f32, segments i32, color Color)\n"
  "-- Draw a filled round-rectangle on the screen.\n"
  "#[bind] fn draw_rectangle_rounded(x i32, y i32, width i32, height i32, cornerRadius i32, color Color)\n"
  "-- Draw an image on the screen.\n"
  "#[bind] fn draw_image(src r32, posX i32, posY i32)\n"
  "-- Draw a tinted image on the screen.\n"
  "#[bind] fn draw_image_tint(src r32, posX i32, posY i32, tint Color)\n"
  "-- Draw an image, rotated, on the screen.\n"
  "#[bind] fn draw_image_rotated(src r32, posX i32, posY i32, degrees f32, offsetX f32, offsetY f32, filter i32)\n"
  "-- Draw an image, flipped, on the screen.\n"
  "#[bind] fn draw_image_flipped(src r32, posX i32, posY i32, flipHorizontal bool, flipVertical bool, flipDiagonal bool)\n"
  "-- Draw an image, scaled, on the screen.\n"
  "#[bind] fn draw_image_scaled(src r32, posX i32, posY i32, scaleX f32, scaleY f32, offsetX f32, offsetY f32, filter i32)\n"
  "-- Draw some text on the screen.\n"
  "#[bind] fn draw_text(font r32, text str, posX i32, posY i32, color Color)\n"
  "-- Save an image to persistant storage.\n"
  "#[bind] fn save_image(image r32, filename str)\n"
  "-- Load an image from a file in cart.\n"
  "#[bind] fn load_image(filename str) -> r32\n"
  "-- Resize an image, return copy.\n"
  "#[bind] fn image_resize(image r32, newWidth i32, newHeight i32, filter i32) -> r32\n"
  "-- Scale an image, return copy.\n"
  "#[bind] fn image_scale(image r32, scaleX f32, scaleY f32, filter i32) -> r32\n"
  "-- Replace a color in an image, in-place.\n"
  "#[bind] fn image_color_replace(image r32, color Color, replace Color)\n"
  "-- Tint a color in an image, in-place.\n"
  "#[bind] fn image_color_tint(image r32, color Color)\n"
  "-- Fade a color in an image, in-place.\n"
  "#[bind] fn image_color_fade(image r32, alpha f32)\n"
  "-- Copy a font to a new font.\n"
  "#[bind] fn font_copy(font r32) -> r32\n"
  "-- Scale a font, return a new font.\n"
  "#[bind] fn font_scale(font r32, scaleX f32, scaleY f32, filter i32) -> r32\n"
  "-- Load a BMF font from a file in cart.\n"
  "#[bind] fn load_font_bmf(filename str, characters str) -> r32\n"
  "-- Load a BMF font from an image.\n"
  "#[bind] fn load_font_bmf_from_image(image r32, characters str) -> r32\n"
  "-- Measure the size of some text.\n"
  "#[bind] fn measure_text(font r32, text str, textLength i32) -> Dimensions\n"
  "-- Meaure an image (use 0 for screen).\n"
  "#[bind] fn measure_image(image r32) -> Dimensions\n"
  "-- Load a TTY font from a file in cart.\n"
  "#[bind] fn load_font_tty(filename str, glyphWidth i32, glyphHeight i32, characters str) -> r32\n"
  "-- Load a TTY font from an image.\n"
  "#[bind] fn load_font_tty_from_image(image r32, glyphWidth i32, glyphHeight i32, characters str) -> r32\n"
  "-- Load a TTF font from a file in cart.\n"
  "#[bind] fn load_font_ttf(filename str, fontSize i32) -> r32\n"
  "-- Invert the colors in an image, in-place.\n"
  "#[bind] fn image_color_invert(image r32)\n"
  "-- Calculate a rectangle representing the available alpha border in an image.\n"
  "#[bind] fn image_alpha_border(image r32, threshold f32) -> Rectangle\n"
  "-- Crop an image, in-place.\n"
  "#[bind] fn image_crop(image r32, x i32, y i32, width i32, height i32)\n"
  "-- Crop an image based on the alpha border, in-place.\n"
  "#[bind] fn image_alpha_crop(image r32, threshold f32)\n"
  "-- Adjust the brightness of an image, in-place.\n"
  "#[bind] fn image_color_brightness(image r32, factor f32)\n"
  "-- Flip an image, in-place.\n"
  "#[bind] fn image_flip(image r32, horizontal bool, vertical bool)\n"
  "-- Change the contrast of an image, in-place.\n"
  "#[bind] fn image_color_contrast(image r32, contrast f32)\n"
  "-- Use an image as an alpha-mask on another image.\n"
  "#[bind] fn image_alpha_mask(image r32, alphaMask r32, posX i32, posY i32)\n"
  "-- Create a new image, rotating another image.\n"
  "#[bind] fn image_rotate(image r32, degrees f32, filter i32) -> r32\n"
  "-- Create a new image of a gradient.\n"
  "#[bind] fn image_gradient(width i32, height i32, topLeft Color, topRight Color, bottomLeft Color, bottomRight Color) -> r32\n"
  "-- Unload an image.\n"
  "#[bind] fn unload_image(image r32)\n"
  "-- Unload a font.\n"
  "#[bind] fn unload_font(font r32)\n"
  "-- Clear an image.\n"
  "#[bind] fn clear_image(destination r32, color Color)\n"
  "-- Draw a single pixel on an image.\n"
  "#[bind] fn draw_point_on_image(destination r32, x i32, y i32, color Color)\n"
  "-- Draw a line on an image.\n"
  "#[bind] fn draw_line_on_image(destination r32, startPosX i32, startPosY i32, endPosX i32, endPosY i32, color Color)\n"
  "-- Draw a filled rectangle on an image.\n"
  "#[bind] fn draw_rectangle_on_image(destination r32, posX i32, posY i32, width i32, height i32, color Color)\n"
  "-- Draw a filled triangle on an image.\n"
  "#[bind] fn draw_triangle_on_image(destination r32, x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, color Color)\n"
  "-- Draw a filled ellipse on an image.\n"
  "#[bind] fn draw_ellipse_on_image(destination r32, centerX i32, centerY i32, radiusX i32, radiusY i32, color Color)\n"
  "-- Draw a circle on an image.\n"
  "#[bind] fn draw_circle_on_image(destination r32, centerX i32, centerY i32, radius i32, color Color)\n"
  "-- Draw a filled polygon on an image.\n"
  "#[bind] fn draw_polygon_on_image(destination r32, points []Vector, color Color)\n"
  "-- Draw a filled round-rectangle on an image.\n"
  "#[bind] fn draw_rectangle_rounded_on_image(destination r32, x i32, y i32, width i32, height i32, cornerRadius i32, color Color)\n"
  "-- Draw an image on an image.\n"
  "#[bind] fn draw_image_on_image(destination r32, src r32, posX i32, posY i32)\n"
  "-- Draw a tinted image on an image.\n"
  "#[bind] fn draw_image_tint_on_image(destination r32, src r32, posX i32, posY i32, tint Color)\n"
  "-- Draw an image, rotated, on an image.\n"
  "#[bind] fn draw_image_rotated_on_image(destination r32, src r32, posX i32, posY i32, degrees f32, offsetX f32, offsetY f32, filter i32)\n"
  "-- Draw an image, flipped, on an image.\n"
  "#[bind] fn draw_image_flipped_on_image(destination r32, src r32, posX i32, posY i32, flipHorizontal bool, flipVertical bool, flipDiagonal bool)\n"
  "-- Draw an image, scaled, on an image.\n"
  "#[bind] fn draw_image_scaled_on_image(destination r32, src r32, posX i32, posY i32, scaleX f32, scaleY f32, offsetX f32, offsetY f32, filter i32)\n"
  "-- Draw some text on an image.\n"
  "#[bind] fn draw_text_on_image(destination r32, font r32, text str, posX i32, posY i32, color Color)\n"
  "-- Draw a outlined (with thickness) rectangle on the screen.\n"
  "#[bind] fn draw_rectangle_outline(posX i32, posY i32, width i32, height i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) triangle on the screen.\n"
  "#[bind] fn draw_triangle_outline(x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) ellipse on the screen.\n"
  "#[bind] fn draw_ellipse_outline(centerX i32, centerY i32, radiusX i32, radiusY i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) circle on the screen.\n"
  "#[bind] fn draw_circle_outline(centerX i32, centerY i32, radius i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) polygon on the screen.\n"
  "#[bind] fn draw_polygon_outline(points []Vector, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) arc on the screen.\n"
  "#[bind] fn draw_arc_outline(centerX i32, centerY i32, radius f32, startAngle f32, endAngle f32, segments i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) round-rectangle on the screen.\n"
  "#[bind] fn draw_rectangle_rounded_outline(x i32, y i32, width i32, height i32, cornerRadius i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) rectangle on an image.\n"
  "#[bind] fn draw_rectangle_outline_on_image(destination r32, posX i32, posY i32, width i32, height i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) triangle on an image.\n"
  "#[bind] fn draw_triangle_outline_on_image(destination r32, x1 i32, y1 i32, x2 i32, y2 i32, x3 i32, y3 i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) ellipse on an image.\n"
  "#[bind] fn draw_ellipse_outline_on_image(destination r32, centerX i32, centerY i32, radiusX i32, radiusY i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) circle on an image.\n"
  "#[bind] fn draw_circle_outline_on_image(destination r32, centerX i32, centerY i32, radius i32, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) polygon on an image.\n"
  "#[bind] fn draw_polygon_outline_on_image(destination r32, points []Vector, thickness i32, color Color)\n"
  "-- Draw a outlined (with thickness) round-rectangle on an image.\n"
  "#[bind] fn draw_rectangle_rounded_outline_on_image(destination r32, x i32, y i32, width i32, height i32, cornerRadius i32, thickness i32, color Color)\n"
  "\n"
  "-- GUI\n"
  "-- Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.\n"
  "#[bind] fn gui_begin_window(title str, rect Rectangle) -> bool\n"
  "-- End the current GUI window.\n"
  "#[bind] fn gui_end_window()\n"
  "-- A button. Returns true when it is clicked.\n"
  "#[bind] fn gui_button(label str) -> bool\n"
  "-- A static text label.\n"
  "#[bind] fn gui_label(text str)\n"
  "-- A block of wrapping text.\n"
  "#[bind] fn gui_text(text str)\n"
  "-- A checkbox. Returns the (possibly changed) state.\n"
  "#[bind] fn gui_checkbox(label str, state bool) -> bool\n"
  "-- A slider. Returns the (possibly changed) value.\n"
  "#[bind] fn gui_slider(value f32, low f32, high f32) -> f32\n"
  "-- Set the current layout row - the column widths (negative for flexible), and the row height.\n"
  "#[bind] fn gui_layout_row(widths []i32, height i32)\n"
  "-- Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.\n"
  "#[bind] fn gui_end()\n"
  "-- Draw the GUI to an image (0 is the screen).\n"
  "#[bind] fn gui_draw(dst r32)\n"
  "\n"
  "-- INPUT\n"
  "-- Has the key been pressed? (tracks unpress/read correctly.)\n"
  "#[bind] fn key_pressed(key i32) -> bool\n"
  "-- Is the key currently down?\n"
  "#[bind] fn key_down(key i32) -> bool\n"
  "-- Has the key been released? (tracks press/read correctly.)\n"
  "#[bind] fn key_released(key i32) -> bool\n"
  "-- Is the key currently up?\n"
  "#[bind] fn key_up(key i32) -> bool\n"
  "-- Has the button been pressed? (tracks unpress/read correctly.)\n"
  "#[bind] fn gamepad_button_pressed(gamepad i32, button i32) -> bool\n"
  "-- Is the button currently down?\n"
  "#[bind] fn gamepad_button_down(gamepad i32, button i32) -> bool\n"
  "-- Has the button been released? (tracks press/read correctly.)\n"
  "#[bind] fn gamepad_button_released(gamepad i32, button i32) -> bool\n"
  "-- Get current position of mouse.\n"
  "#[bind] fn mouse_position() -> Vector\n"
  "-- Has the button been pressed? (tracks unpress/read correctly.)\n"
  "#[bind] fn mouse_button_pressed(button i32) -> bool\n"
  "-- Is the button currently down?\n"
  "#[bind] fn mouse_button_down(button i32) -> bool\n"
  "-- Has the button been released? (tracks press/read correctly.)\n"
  "#[bind] fn mouse_button_released(button i32) -> bool\n"
  "-- Is the button currently up?\n"
  "#[bind] fn mouse_button_up(button i32) -> bool\n"
  "\n"
  "-- SOUND\n"
  "-- Load a sound from a file in cart.\n"
  "#[bind] fn load_sound(filename str) -> r32\n"
  "-- Play a sound.\n"
  "#[bind] fn play_sound(sound r32, loop bool)\n"
  "-- Stop a sound.\n"
  "#[bind] fn stop_sound(sound r32)\n"
  "-- Unload a sound.\n"
  "#[bind] fn unload_sound(sound r32)\n"
  "-- Speak some text and return a sound. Set things to 0 for defaults.\n"
  "#[bind] fn tts_sound(text str, phonetic bool, pitch i32, speed i32, throat i32, mouth i32, sing bool) -> r32\n"
  "-- Create Sfx sound.\n"
  "#[bind] fn sfx_sound(params SfxParams) -> r32\n"
  "-- Create Sfx parameters.\n"
  "#[bind] fn sfx_generate(type_ i32) -> SfxParams\n"
  "\n"
  "-- TILE\n"
  "-- Load a tilemap (a Tiled map, exported as JSON) from a file in cart.\n"
  "#[bind] fn load_tilemap(filename str) -> r32\n"
  "-- Unload a tilemap.\n"
  "#[bind] fn unload_tilemap(tilemap r32)\n"
  "-- Update a tilemap's animation timers (deltaTime is in seconds).\n"
  "#[bind] fn tile_update(tilemap r32, deltaTime f32)\n"
  "-- Get the size of a tilemap, in tiles.\n"
  "#[bind] fn tile_map_size(tilemap r32) -> Dimensions\n"
  "-- Get the size of a single tile of a tilemap, in pixels.\n"
  "#[bind] fn tile_tile_size(tilemap r32) -> Dimensions\n"
  "-- Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)\n"
  "#[bind] fn tile_map_prop(tilemap r32, name str) -> TilemapProp\n"
  "-- Get the number of custom properties on a tilemap.\n"
  "#[bind] fn tile_map_prop_count(tilemap r32) -> i32\n"
  "-- Get a custom property of a tilemap, by index (PROP_NONE when out of range.)\n"
  "#[bind] fn tile_map_prop_at(tilemap r32, index i32) -> TilemapProp\n"
  "-- Draw a tilemap on the screen.\n"
  "#[bind] fn tile_draw(tilemap r32, posX i32, posY i32)\n"
  "-- Draw a tilemap on the screen, tinted by a color.\n"
  "#[bind] fn tile_draw_tint(tilemap r32, posX i32, posY i32, tint Color)\n"
  "-- Draw a tilemap on an image.\n"
  "#[bind] fn tile_draw_on_image(dst r32, tilemap r32, posX i32, posY i32)\n"
  "-- Render a whole tilemap to a new image.\n"
  "#[bind] fn tilemap_image(tilemap r32) -> r32\n"
  "-- Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.\n"
  "#[bind] fn tile_layer_count(tilemap r32) -> i32\n"
  "-- Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)\n"
  "#[bind] fn tile_layer_index(tilemap r32, name str) -> i32\n"
  "-- Get the name of a layer of a tilemap.\n"
  "#[bind] fn tile_layer_name(tilemap r32, layer i32) -> str\n"
  "-- Get the kind of a layer of a tilemap.\n"
  "#[bind] fn tile_layer_type(tilemap r32, layer i32) -> i32\n"
  "-- Get the size of a layer of a tilemap, in tiles.\n"
  "#[bind] fn tile_layer_size(tilemap r32, layer i32) -> Dimensions\n"
  "-- Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.\n"
  "#[bind] fn tile_layer_visible(tilemap r32, layer i32) -> bool\n"
  "-- Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)\n"
  "#[bind] fn tile_layer_prop(tilemap r32, layer i32, name str) -> TilemapProp\n"
  "-- Get the number of custom properties on a layer of a tilemap.\n"
  "#[bind] fn tile_layer_prop_count(tilemap r32, layer i32) -> i32\n"
  "-- Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)\n"
  "#[bind] fn tile_layer_prop_at(tilemap r32, layer i32, index i32) -> TilemapProp\n"
  "-- Draw a single layer of a tilemap on the screen.\n"
  "#[bind] fn tile_draw_layer(tilemap r32, layer i32, posX i32, posY i32)\n"
  "-- Draw a single layer of a tilemap on the screen, tinted by a color.\n"
  "#[bind] fn tile_draw_layer_tint(tilemap r32, layer i32, posX i32, posY i32, tint Color)\n"
  "-- Draw a single layer of a tilemap on an image.\n"
  "#[bind] fn tile_draw_layer_on_image(dst r32, tilemap r32, layer i32, posX i32, posY i32)\n"
  "-- Render a single layer of a tilemap to a new image.\n"
  "#[bind] fn tile_layer_image(tilemap r32, layer i32) -> r32\n"
  "-- Get the gid of the tile at a column/row in a tilemap layer.\n"
  "#[bind] fn tile_get_tile(tilemap r32, layer i32, column i32, row i32) -> i32\n"
  "-- Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.\n"
  "#[bind] fn tile_set_tile(tilemap r32, layer i32, column i32, row i32, gid i32)\n"
  "-- Draw a single tile from a tilemap on the screen.\n"
  "#[bind] fn tile_draw_tile(tilemap r32, gid i32, posX i32, posY i32)\n"
  "-- Get a copy of the image of a single tile in a tilemap.\n"
  "#[bind] fn tile_image(tilemap r32, gid i32) -> r32\n"
  "-- Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.\n"
  "#[bind] fn tile_gid_prop(tilemap r32, gid i32, name str) -> TilemapProp\n"
  "-- Get the number of custom properties on a tile of a tilemap.\n"
  "#[bind] fn tile_gid_prop_count(tilemap r32, gid i32) -> i32\n"
  "-- Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)\n"
  "#[bind] fn tile_gid_prop_at(tilemap r32, gid i32, index i32) -> TilemapProp\n"
  "-- Get the number of objects on an object-layer of a tilemap.\n"
  "#[bind] fn tile_object_count(tilemap r32, layer i32) -> i32\n"
  "-- Get an object from an object-layer of a tilemap.\n"
  "#[bind] fn tile_object(tilemap r32, layer i32, index i32) -> TilemapObject\n"
  "-- Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)\n"
  "#[bind] fn tile_object_index(tilemap r32, layer i32, name str) -> i32\n"
  "-- Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)\n"
  "#[bind] fn tile_object_prop(tilemap r32, layer i32, index i32, name str) -> TilemapProp\n"
  "-- Get the number of custom properties on an object of a tilemap.\n"
  "#[bind] fn tile_object_prop_count(tilemap r32, layer i32, index i32) -> i32\n"
  "-- Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)\n"
  "#[bind] fn tile_object_prop_at(tilemap r32, layer i32, index i32, propIndex i32) -> TilemapProp\n"
  "\n"
  "-- TYPES\n"
  "\n"
  "-- UTILITIES\n"
  "-- Get system-time (ms) since unix epoch.\n"
  "#[bind] fn current_time() -> r64\n"
  "-- Get the change in time (seconds) since the last update run.\n"
  "#[bind] fn delta_time() -> f32\n"
  "-- Get a random integer between 2 numbers.\n"
  "#[bind] fn random_int(min i32, max i32) -> i32\n"
  "-- Get the random-seed.\n"
  "#[bind] fn random_seed_get() -> r64\n"
  "-- Set the random-seed.\n"
  "#[bind] fn random_seed_set(seed r64)\n"
  "\n"
  "-- The screen is image 0\n"
  "global SCREEN i32 = 0\n"
  "global SCREEN_WIDTH i32 = 640\n"
  "global SCREEN_HEIGHT i32 = 480\n"
  "-- The built-in font\n"
  "global FONT_DEFAULT i32 = 0\n"
  "\n"
  "global LIGHTGRAY Color = Color{r=200, g=200, b=200, a=255}\n"
  "global GRAY Color = Color{r=130, g=130, b=130, a=255}\n"
  "global DARKGRAY Color = Color{r=80, g=80, b=80, a=255}\n"
  "global YELLOW Color = Color{r=253, g=249, b=0, a=255}\n"
  "global GOLD Color = Color{r=255, g=203, b=0, a=255}\n"
  "global ORANGE Color = Color{r=255, g=161, b=0, a=255}\n"
  "global PINK Color = Color{r=255, g=109, b=194, a=255}\n"
  "global RED Color = Color{r=230, g=41, b=55, a=255}\n"
  "global MAROON Color = Color{r=190, g=33, b=55, a=255}\n"
  "global GREEN Color = Color{r=0, g=228, b=48, a=255}\n"
  "global LIME Color = Color{r=0, g=158, b=47, a=255}\n"
  "global DARKGREEN Color = Color{r=0, g=117, b=44, a=255}\n"
  "global SKYBLUE Color = Color{r=102, g=191, b=255, a=255}\n"
  "global BLUE Color = Color{r=0, g=121, b=241, a=255}\n"
  "global DARKBLUE Color = Color{r=0, g=82, b=172, a=255}\n"
  "global PURPLE Color = Color{r=200, g=122, b=255, a=255}\n"
  "global VIOLET Color = Color{r=135, g=60, b=190, a=255}\n"
  "global DARKPURPLE Color = Color{r=112, g=31, b=126, a=255}\n"
  "global BEIGE Color = Color{r=211, g=176, b=131, a=255}\n"
  "global BROWN Color = Color{r=127, g=106, b=79, a=255}\n"
  "global DARKBROWN Color = Color{r=76, g=63, b=47, a=255}\n"
  "global WHITE Color = Color{r=255, g=255, b=255, a=255}\n"
  "global BLACK Color = Color{r=0, g=0, b=0, a=255}\n"
  "global BLANK Color = Color{r=0, g=0, b=0, a=0}\n"
  "global MAGENTA Color = Color{r=255, g=0, b=255, a=255}\n"
  "global RAYWHITE Color = Color{r=245, g=245, b=245, a=255}\n"
  "-- The current tagged version of null0 engine\n"
  "global NULL0_VERSION str = '0.0.20'\n"
  "\n"
  "-- Potential image-filtering techniques for scale/etc.\n"
  "global FILTER_NEARESTNEIGHBOR i32 = 0\n"
  "global FILTER_BILINEAR i32 = 1\n"
  "global FILTER_SMOOTH i32 = 2\n"
  "-- Represents a Sfx preset type.\n"
  "global SFX_COIN i32 = 0\n"
  "global SFX_LASER i32 = 1\n"
  "global SFX_EXPLOSION i32 = 2\n"
  "global SFX_POWERUP i32 = 3\n"
  "global SFX_HURT i32 = 4\n"
  "global SFX_JUMP i32 = 5\n"
  "global SFX_SELECT i32 = 6\n"
  "global SFX_SYNTH i32 = 7\n"
  "-- Represents a keyboard key.\n"
  "global KEY_INVALID i32 = 0\n"
  "global KEY_SPACE i32 = 32\n"
  "global KEY_APOSTROPHE i32 = 39\n"
  "global KEY_COMMA i32 = 44\n"
  "global KEY_MINUS i32 = 45\n"
  "global KEY_PERIOD i32 = 46\n"
  "global KEY_SLASH i32 = 47\n"
  "global KEY_0 i32 = 48\n"
  "global KEY_1 i32 = 49\n"
  "global KEY_2 i32 = 50\n"
  "global KEY_3 i32 = 51\n"
  "global KEY_4 i32 = 52\n"
  "global KEY_5 i32 = 53\n"
  "global KEY_6 i32 = 54\n"
  "global KEY_7 i32 = 55\n"
  "global KEY_8 i32 = 56\n"
  "global KEY_9 i32 = 57\n"
  "global KEY_SEMICOLON i32 = 59\n"
  "global KEY_EQUAL i32 = 61\n"
  "global KEY_A i32 = 65\n"
  "global KEY_B i32 = 66\n"
  "global KEY_C i32 = 67\n"
  "global KEY_D i32 = 68\n"
  "global KEY_E i32 = 69\n"
  "global KEY_F i32 = 70\n"
  "global KEY_G i32 = 71\n"
  "global KEY_H i32 = 72\n"
  "global KEY_I i32 = 73\n"
  "global KEY_J i32 = 74\n"
  "global KEY_K i32 = 75\n"
  "global KEY_L i32 = 76\n"
  "global KEY_M i32 = 77\n"
  "global KEY_N i32 = 78\n"
  "global KEY_O i32 = 79\n"
  "global KEY_P i32 = 80\n"
  "global KEY_Q i32 = 81\n"
  "global KEY_R i32 = 82\n"
  "global KEY_S i32 = 83\n"
  "global KEY_T i32 = 84\n"
  "global KEY_U i32 = 85\n"
  "global KEY_V i32 = 86\n"
  "global KEY_W i32 = 87\n"
  "global KEY_X i32 = 88\n"
  "global KEY_Y i32 = 89\n"
  "global KEY_Z i32 = 90\n"
  "global KEY_LEFT_BRACKET i32 = 91\n"
  "global KEY_BACKSLASH i32 = 92\n"
  "global KEY_RIGHT_BRACKET i32 = 93\n"
  "global KEY_GRAVE_ACCENT i32 = 96\n"
  "global KEY_WORLD_1 i32 = 161\n"
  "global KEY_WORLD_2 i32 = 162\n"
  "global KEY_ESCAPE i32 = 256\n"
  "global KEY_ENTER i32 = 257\n"
  "global KEY_TAB i32 = 258\n"
  "global KEY_BACKSPACE i32 = 259\n"
  "global KEY_INSERT i32 = 260\n"
  "global KEY_DELETE i32 = 261\n"
  "global KEY_RIGHT i32 = 262\n"
  "global KEY_LEFT i32 = 263\n"
  "global KEY_DOWN i32 = 264\n"
  "global KEY_UP i32 = 265\n"
  "global KEY_PAGE_UP i32 = 266\n"
  "global KEY_PAGE_DOWN i32 = 267\n"
  "global KEY_HOME i32 = 268\n"
  "global KEY_END i32 = 269\n"
  "global KEY_CAPS_LOCK i32 = 280\n"
  "global KEY_SCROLL_LOCK i32 = 281\n"
  "global KEY_NUM_LOCK i32 = 282\n"
  "global KEY_PRINT_SCREEN i32 = 283\n"
  "global KEY_PAUSE i32 = 284\n"
  "global KEY_F1 i32 = 290\n"
  "global KEY_F2 i32 = 291\n"
  "global KEY_F3 i32 = 292\n"
  "global KEY_F4 i32 = 293\n"
  "global KEY_F5 i32 = 294\n"
  "global KEY_F6 i32 = 295\n"
  "global KEY_F7 i32 = 296\n"
  "global KEY_F8 i32 = 297\n"
  "global KEY_F9 i32 = 298\n"
  "global KEY_F10 i32 = 299\n"
  "global KEY_F11 i32 = 300\n"
  "global KEY_F12 i32 = 301\n"
  "global KEY_F13 i32 = 302\n"
  "global KEY_F14 i32 = 303\n"
  "global KEY_F15 i32 = 304\n"
  "global KEY_F16 i32 = 305\n"
  "global KEY_F17 i32 = 306\n"
  "global KEY_F18 i32 = 307\n"
  "global KEY_F19 i32 = 308\n"
  "global KEY_F20 i32 = 309\n"
  "global KEY_F21 i32 = 310\n"
  "global KEY_F22 i32 = 311\n"
  "global KEY_F23 i32 = 312\n"
  "global KEY_F24 i32 = 313\n"
  "global KEY_F25 i32 = 314\n"
  "global KEY_KP_0 i32 = 320\n"
  "global KEY_KP_1 i32 = 321\n"
  "global KEY_KP_2 i32 = 322\n"
  "global KEY_KP_3 i32 = 323\n"
  "global KEY_KP_4 i32 = 324\n"
  "global KEY_KP_5 i32 = 325\n"
  "global KEY_KP_6 i32 = 326\n"
  "global KEY_KP_7 i32 = 327\n"
  "global KEY_KP_8 i32 = 328\n"
  "global KEY_KP_9 i32 = 329\n"
  "global KEY_KP_DECIMAL i32 = 330\n"
  "global KEY_KP_DIVIDE i32 = 331\n"
  "global KEY_KP_MULTIPLY i32 = 332\n"
  "global KEY_KP_SUBTRACT i32 = 333\n"
  "global KEY_KP_ADD i32 = 334\n"
  "global KEY_KP_ENTER i32 = 335\n"
  "global KEY_KP_EQUAL i32 = 336\n"
  "global KEY_LEFT_SHIFT i32 = 340\n"
  "global KEY_LEFT_CONTROL i32 = 341\n"
  "global KEY_LEFT_ALT i32 = 342\n"
  "global KEY_LEFT_SUPER i32 = 343\n"
  "global KEY_RIGHT_SHIFT i32 = 344\n"
  "global KEY_RIGHT_CONTROL i32 = 345\n"
  "global KEY_RIGHT_ALT i32 = 346\n"
  "global KEY_RIGHT_SUPER i32 = 347\n"
  "global KEY_MENU i32 = 348\n"
  "-- Represents a gamepad button.\n"
  "global GAMEPAD_BUTTON_UNKNOWN i32 = 0\n"
  "global GAMEPAD_BUTTON_UP i32 = 1\n"
  "global GAMEPAD_BUTTON_RIGHT i32 = 2\n"
  "global GAMEPAD_BUTTON_DOWN i32 = 3\n"
  "global GAMEPAD_BUTTON_LEFT i32 = 4\n"
  "global GAMEPAD_BUTTON_Y i32 = 5\n"
  "global GAMEPAD_BUTTON_B i32 = 6\n"
  "global GAMEPAD_BUTTON_A i32 = 7\n"
  "global GAMEPAD_BUTTON_X i32 = 8\n"
  "global GAMEPAD_BUTTON_LEFT_SHOULDER i32 = 9\n"
  "global GAMEPAD_BUTTON_LEFT_TRIGGER i32 = 10\n"
  "global GAMEPAD_BUTTON_RIGHT_SHOULDER i32 = 11\n"
  "global GAMEPAD_BUTTON_RIGHT_TRIGGER i32 = 12\n"
  "global GAMEPAD_BUTTON_SELECT i32 = 13\n"
  "global GAMEPAD_BUTTON_MENU i32 = 14\n"
  "global GAMEPAD_BUTTON_START i32 = 15\n"
  "global GAMEPAD_BUTTON_LEFT_THUMB i32 = 16\n"
  "global GAMEPAD_BUTTON_RIGHT_THUMB i32 = 17\n"
  "-- Represents a mouse button.\n"
  "global MOUSE_BUTTON_UNKNOWN i32 = 0\n"
  "global MOUSE_BUTTON_LEFT i32 = 1\n"
  "global MOUSE_BUTTON_RIGHT i32 = 2\n"
  "global MOUSE_BUTTON_MIDDLE i32 = 3\n"
  "-- The kind of a layer in a tilemap.\n"
  "global LAYER_NONE i32 = 0\n"
  "global LAYER_TILE i32 = 1\n"
  "global LAYER_OBJECT i32 = 2\n"
  "global LAYER_IMAGE i32 = 3\n"
  "global LAYER_GROUP i32 = 4\n"
  "-- The type of a tilemap property's value. Tiled's \"file\" properties arrive as PROP_STRING.\n"
  "global PROP_NONE i32 = 0\n"
  "global PROP_INT i32 = 1\n"
  "global PROP_BOOL i32 = 2\n"
  "global PROP_FLOAT i32 = 3\n"
  "global PROP_STRING i32 = 4\n"
  "global PROP_COLOR i32 = 5\n"
  "\n"
;

// TilemapProp as cyber lays it out
typedef struct {
  CLstr name;
  int32_t type;
  int32_t integer;
  float number;
  CLstr text;
} CyTilemapProp;

// TilemapObject as cyber lays it out
typedef struct {
  int32_t id;
  CLstr name;
  CLstr type;
  int32_t gid;
  float x;
  float y;
  float width;
  float height;
  float rotation;
  int32_t visible;
} CyTilemapObject;

// BINDINGS


// COLORS

// Tint a color with another color.
static CLRet cyber_color_tint(CLThread* t) {
  Color* out = (Color*)cl_thread_ret(t, sizeof(Color));
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  Color* tint = (Color*)cl_thread_param(t, sizeof(Color));
  Color* ret = color_tint(*color, *tint);
  *out = *ret;
  return CL_RET_OK;
}

// Fade a color.
static CLRet cyber_color_fade(CLThread* t) {
  Color* out = (Color*)cl_thread_ret(t, sizeof(Color));
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  f32 alpha = cl_thread_f32(t);
  Color* ret = color_fade(*color, alpha);
  *out = *ret;
  return CL_RET_OK;
}

// Change the brightness of a color.
static CLRet cyber_color_brightness(CLThread* t) {
  Color* out = (Color*)cl_thread_ret(t, sizeof(Color));
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  f32 factor = cl_thread_f32(t);
  Color* ret = color_brightness(*color, factor);
  *out = *ret;
  return CL_RET_OK;
}

// Invert a color.
static CLRet cyber_color_invert(CLThread* t) {
  Color* out = (Color*)cl_thread_ret(t, sizeof(Color));
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  Color* ret = color_invert(*color);
  *out = *ret;
  return CL_RET_OK;
}

// Blend 2 colors together.
static CLRet cyber_color_alpha_blend(CLThread* t) {
  Color* out = (Color*)cl_thread_ret(t, sizeof(Color));
  Color* dst = (Color*)cl_thread_param(t, sizeof(Color));
  Color* src = (Color*)cl_thread_param(t, sizeof(Color));
  Color* ret = color_alpha_blend(*dst, *src);
  *out = *ret;
  return CL_RET_OK;
}

// Change contrast of a color.
static CLRet cyber_color_contrast(CLThread* t) {
  Color* out = (Color*)cl_thread_ret(t, sizeof(Color));
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  f32 contrast = cl_thread_f32(t);
  Color* ret = color_contrast(*color, contrast);
  *out = *ret;
  return CL_RET_OK;
}

// Interpolate colors.
static CLRet cyber_color_bilinear_interpolate(CLThread* t) {
  Color* out = (Color*)cl_thread_ret(t, sizeof(Color));
  Color* color00 = (Color*)cl_thread_param(t, sizeof(Color));
  Color* color01 = (Color*)cl_thread_param(t, sizeof(Color));
  Color* color10 = (Color*)cl_thread_param(t, sizeof(Color));
  Color* color11 = (Color*)cl_thread_param(t, sizeof(Color));
  f32 coordinateX = cl_thread_f32(t);
  f32 coordinateY = cl_thread_f32(t);
  Color* ret = color_bilinear_interpolate(*color00, *color01, *color10, *color11, coordinateX, coordinateY);
  *out = *ret;
  return CL_RET_OK;
}


// GRAPHICS

// Create a new blank image.
static CLRet cyber_new_image(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  u32 ret = new_image(width, height, *color);
  *out = ret;
  return CL_RET_OK;
}

// Copy an image to a new image.
static CLRet cyber_image_copy(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 image = (u32)cl_thread_r32(t);
  u32 ret = image_copy(image);
  *out = ret;
  return CL_RET_OK;
}

// Create an image from a region of another image.
static CLRet cyber_image_subimage(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 image = (u32)cl_thread_r32(t);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  u32 ret = image_subimage(image, x, y, width, height);
  *out = ret;
  return CL_RET_OK;
}

// Clear the screen.
static CLRet cyber_clear(CLThread* t) {
  cl_thread_ret(t, 0);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  clear(*color);
  return CL_RET_OK;
}

// Draw a single pixel on the screen.
static CLRet cyber_draw_point(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_point(x, y, *color);
  return CL_RET_OK;
}

// Draw a line on the screen.
static CLRet cyber_draw_line(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 startPosX = cl_thread_i32(t);
  i32 startPosY = cl_thread_i32(t);
  i32 endPosX = cl_thread_i32(t);
  i32 endPosY = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_line(startPosX, startPosY, endPosX, endPosY, *color);
  return CL_RET_OK;
}

// Draw a filled rectangle on the screen.
static CLRet cyber_draw_rectangle(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle(posX, posY, width, height, *color);
  return CL_RET_OK;
}

// Draw a filled triangle on the screen.
static CLRet cyber_draw_triangle(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 x1 = cl_thread_i32(t);
  i32 y1 = cl_thread_i32(t);
  i32 x2 = cl_thread_i32(t);
  i32 y2 = cl_thread_i32(t);
  i32 x3 = cl_thread_i32(t);
  i32 y3 = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_triangle(x1, y1, x2, y2, x3, y3, *color);
  return CL_RET_OK;
}

// Draw a filled ellipse on the screen.
static CLRet cyber_draw_ellipse(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radiusX = cl_thread_i32(t);
  i32 radiusY = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_ellipse(centerX, centerY, radiusX, radiusY, *color);
  return CL_RET_OK;
}

// Draw a filled circle on the screen.
static CLRet cyber_draw_circle(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radius = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_circle(centerX, centerY, radius, *color);
  return CL_RET_OK;
}

// Draw a filled polygon on the screen.
static CLRet cyber_draw_polygon(CLThread* t) {
  cl_thread_ret(t, 0);
  CLSlice points_slice = cl_thread_slice(t);
  Vector* points = (Vector*)points_slice.ptr;
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_polygon(points, (u32)points_slice.len, *color);
  return CL_RET_OK;
}

// Draw a filled arc on the screen.
static CLRet cyber_draw_arc(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  f32 radius = cl_thread_f32(t);
  f32 startAngle = cl_thread_f32(t);
  f32 endAngle = cl_thread_f32(t);
  i32 segments = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, *color);
  return CL_RET_OK;
}

// Draw a filled round-rectangle on the screen.
static CLRet cyber_draw_rectangle_rounded(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  i32 cornerRadius = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle_rounded(x, y, width, height, cornerRadius, *color);
  return CL_RET_OK;
}

// Draw an image on the screen.
static CLRet cyber_draw_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  draw_image(src, posX, posY);
  return CL_RET_OK;
}

// Draw a tinted image on the screen.
static CLRet cyber_draw_image_tint(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  Color* tint = (Color*)cl_thread_param(t, sizeof(Color));
  draw_image_tint(src, posX, posY, *tint);
  return CL_RET_OK;
}

// Draw an image, rotated, on the screen.
static CLRet cyber_draw_image_rotated(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  f32 degrees = cl_thread_f32(t);
  f32 offsetX = cl_thread_f32(t);
  f32 offsetY = cl_thread_f32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter);
  return CL_RET_OK;
}

// Draw an image, flipped, on the screen.
static CLRet cyber_draw_image_flipped(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  bool flipHorizontal = cl_thread_i32(t) != 0;
  bool flipVertical = cl_thread_i32(t) != 0;
  bool flipDiagonal = cl_thread_i32(t) != 0;
  draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
  return CL_RET_OK;
}

// Draw an image, scaled, on the screen.
static CLRet cyber_draw_image_scaled(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  f32 scaleX = cl_thread_f32(t);
  f32 scaleY = cl_thread_f32(t);
  f32 offsetX = cl_thread_f32(t);
  f32 offsetY = cl_thread_f32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
  return CL_RET_OK;
}

// Draw some text on the screen.
static CLRet cyber_draw_text(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 font = (u32)cl_thread_r32(t);
  CLstr text_s = cl_thread_str(t);
  CLBytes text_b = cl_str_bytes(text_s);
  char* text = malloc(text_b.len + 1);
  memcpy(text, text_b.ptr, text_b.len);
  text[text_b.len] = '\0';
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_text(font, text, posX, posY, *color);
  free(text);
  return CL_RET_OK;
}

// Save an image to persistant storage.
static CLRet cyber_save_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  CLstr filename_s = cl_thread_str(t);
  CLBytes filename_b = cl_str_bytes(filename_s);
  char* filename = malloc(filename_b.len + 1);
  memcpy(filename, filename_b.ptr, filename_b.len);
  filename[filename_b.len] = '\0';
  save_image(image, filename);
  free(filename);
  return CL_RET_OK;
}

// Load an image from a file in cart.
static CLRet cyber_load_image(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  CLstr filename_s = cl_thread_str(t);
  CLBytes filename_b = cl_str_bytes(filename_s);
  char* filename = malloc(filename_b.len + 1);
  memcpy(filename, filename_b.ptr, filename_b.len);
  filename[filename_b.len] = '\0';
  u32 ret = load_image(filename);
  *out = ret;
  free(filename);
  return CL_RET_OK;
}

// Resize an image, return copy.
static CLRet cyber_image_resize(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 image = (u32)cl_thread_r32(t);
  i32 newWidth = cl_thread_i32(t);
  i32 newHeight = cl_thread_i32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  u32 ret = image_resize(image, newWidth, newHeight, filter);
  *out = ret;
  return CL_RET_OK;
}

// Scale an image, return copy.
static CLRet cyber_image_scale(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 image = (u32)cl_thread_r32(t);
  f32 scaleX = cl_thread_f32(t);
  f32 scaleY = cl_thread_f32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  u32 ret = image_scale(image, scaleX, scaleY, filter);
  *out = ret;
  return CL_RET_OK;
}

// Replace a color in an image, in-place.
static CLRet cyber_image_color_replace(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  Color* replace = (Color*)cl_thread_param(t, sizeof(Color));
  image_color_replace(image, *color, *replace);
  return CL_RET_OK;
}

// Tint a color in an image, in-place.
static CLRet cyber_image_color_tint(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  image_color_tint(image, *color);
  return CL_RET_OK;
}

// Fade a color in an image, in-place.
static CLRet cyber_image_color_fade(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  f32 alpha = cl_thread_f32(t);
  image_color_fade(image, alpha);
  return CL_RET_OK;
}

// Copy a font to a new font.
static CLRet cyber_font_copy(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 font = (u32)cl_thread_r32(t);
  u32 ret = font_copy(font);
  *out = ret;
  return CL_RET_OK;
}

// Scale a font, return a new font.
static CLRet cyber_font_scale(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 font = (u32)cl_thread_r32(t);
  f32 scaleX = cl_thread_f32(t);
  f32 scaleY = cl_thread_f32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  u32 ret = font_scale(font, scaleX, scaleY, filter);
  *out = ret;
  return CL_RET_OK;
}

// Load a BMF font from a file in cart.
static CLRet cyber_load_font_bmf(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  CLstr filename_s = cl_thread_str(t);
  CLBytes filename_b = cl_str_bytes(filename_s);
  char* filename = malloc(filename_b.len + 1);
  memcpy(filename, filename_b.ptr, filename_b.len);
  filename[filename_b.len] = '\0';
  CLstr characters_s = cl_thread_str(t);
  CLBytes characters_b = cl_str_bytes(characters_s);
  char* characters = malloc(characters_b.len + 1);
  memcpy(characters, characters_b.ptr, characters_b.len);
  characters[characters_b.len] = '\0';
  u32 ret = load_font_bmf(filename, characters);
  *out = ret;
  free(filename);
  free(characters);
  return CL_RET_OK;
}

// Load a BMF font from an image.
static CLRet cyber_load_font_bmf_from_image(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 image = (u32)cl_thread_r32(t);
  CLstr characters_s = cl_thread_str(t);
  CLBytes characters_b = cl_str_bytes(characters_s);
  char* characters = malloc(characters_b.len + 1);
  memcpy(characters, characters_b.ptr, characters_b.len);
  characters[characters_b.len] = '\0';
  u32 ret = load_font_bmf_from_image(image, characters);
  *out = ret;
  free(characters);
  return CL_RET_OK;
}

// Measure the size of some text.
static CLRet cyber_measure_text(CLThread* t) {
  Dimensions* out = (Dimensions*)cl_thread_ret(t, sizeof(Dimensions));
  u32 font = (u32)cl_thread_r32(t);
  CLstr text_s = cl_thread_str(t);
  CLBytes text_b = cl_str_bytes(text_s);
  char* text = malloc(text_b.len + 1);
  memcpy(text, text_b.ptr, text_b.len);
  text[text_b.len] = '\0';
  i32 textLength = cl_thread_i32(t);
  Dimensions* ret = measure_text(font, text, textLength);
  *out = *ret;
  free(text);
  return CL_RET_OK;
}

// Meaure an image (use 0 for screen).
static CLRet cyber_measure_image(CLThread* t) {
  Dimensions* out = (Dimensions*)cl_thread_ret(t, sizeof(Dimensions));
  u32 image = (u32)cl_thread_r32(t);
  Dimensions* ret = measure_image(image);
  *out = *ret;
  return CL_RET_OK;
}

// Load a TTY font from a file in cart.
static CLRet cyber_load_font_tty(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  CLstr filename_s = cl_thread_str(t);
  CLBytes filename_b = cl_str_bytes(filename_s);
  char* filename = malloc(filename_b.len + 1);
  memcpy(filename, filename_b.ptr, filename_b.len);
  filename[filename_b.len] = '\0';
  i32 glyphWidth = cl_thread_i32(t);
  i32 glyphHeight = cl_thread_i32(t);
  CLstr characters_s = cl_thread_str(t);
  CLBytes characters_b = cl_str_bytes(characters_s);
  char* characters = malloc(characters_b.len + 1);
  memcpy(characters, characters_b.ptr, characters_b.len);
  characters[characters_b.len] = '\0';
  u32 ret = load_font_tty(filename, glyphWidth, glyphHeight, characters);
  *out = ret;
  free(filename);
  free(characters);
  return CL_RET_OK;
}

// Load a TTY font from an image.
static CLRet cyber_load_font_tty_from_image(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 image = (u32)cl_thread_r32(t);
  i32 glyphWidth = cl_thread_i32(t);
  i32 glyphHeight = cl_thread_i32(t);
  CLstr characters_s = cl_thread_str(t);
  CLBytes characters_b = cl_str_bytes(characters_s);
  char* characters = malloc(characters_b.len + 1);
  memcpy(characters, characters_b.ptr, characters_b.len);
  characters[characters_b.len] = '\0';
  u32 ret = load_font_tty_from_image(image, glyphWidth, glyphHeight, characters);
  *out = ret;
  free(characters);
  return CL_RET_OK;
}

// Load a TTF font from a file in cart.
static CLRet cyber_load_font_ttf(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  CLstr filename_s = cl_thread_str(t);
  CLBytes filename_b = cl_str_bytes(filename_s);
  char* filename = malloc(filename_b.len + 1);
  memcpy(filename, filename_b.ptr, filename_b.len);
  filename[filename_b.len] = '\0';
  i32 fontSize = cl_thread_i32(t);
  u32 ret = load_font_ttf(filename, fontSize);
  *out = ret;
  free(filename);
  return CL_RET_OK;
}

// Invert the colors in an image, in-place.
static CLRet cyber_image_color_invert(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  image_color_invert(image);
  return CL_RET_OK;
}

// Calculate a rectangle representing the available alpha border in an image.
static CLRet cyber_image_alpha_border(CLThread* t) {
  Rectangle* out = (Rectangle*)cl_thread_ret(t, sizeof(Rectangle));
  u32 image = (u32)cl_thread_r32(t);
  f32 threshold = cl_thread_f32(t);
  Rectangle* ret = image_alpha_border(image, threshold);
  *out = *ret;
  return CL_RET_OK;
}

// Crop an image, in-place.
static CLRet cyber_image_crop(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  image_crop(image, x, y, width, height);
  return CL_RET_OK;
}

// Crop an image based on the alpha border, in-place.
static CLRet cyber_image_alpha_crop(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  f32 threshold = cl_thread_f32(t);
  image_alpha_crop(image, threshold);
  return CL_RET_OK;
}

// Adjust the brightness of an image, in-place.
static CLRet cyber_image_color_brightness(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  f32 factor = cl_thread_f32(t);
  image_color_brightness(image, factor);
  return CL_RET_OK;
}

// Flip an image, in-place.
static CLRet cyber_image_flip(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  bool horizontal = cl_thread_i32(t) != 0;
  bool vertical = cl_thread_i32(t) != 0;
  image_flip(image, horizontal, vertical);
  return CL_RET_OK;
}

// Change the contrast of an image, in-place.
static CLRet cyber_image_color_contrast(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  f32 contrast = cl_thread_f32(t);
  image_color_contrast(image, contrast);
  return CL_RET_OK;
}

// Use an image as an alpha-mask on another image.
static CLRet cyber_image_alpha_mask(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  u32 alphaMask = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  image_alpha_mask(image, alphaMask, posX, posY);
  return CL_RET_OK;
}

// Create a new image, rotating another image.
static CLRet cyber_image_rotate(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 image = (u32)cl_thread_r32(t);
  f32 degrees = cl_thread_f32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  u32 ret = image_rotate(image, degrees, filter);
  *out = ret;
  return CL_RET_OK;
}

// Create a new image of a gradient.
static CLRet cyber_image_gradient(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  Color* topLeft = (Color*)cl_thread_param(t, sizeof(Color));
  Color* topRight = (Color*)cl_thread_param(t, sizeof(Color));
  Color* bottomLeft = (Color*)cl_thread_param(t, sizeof(Color));
  Color* bottomRight = (Color*)cl_thread_param(t, sizeof(Color));
  u32 ret = image_gradient(width, height, *topLeft, *topRight, *bottomLeft, *bottomRight);
  *out = ret;
  return CL_RET_OK;
}

// Unload an image.
static CLRet cyber_unload_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 image = (u32)cl_thread_r32(t);
  unload_image(image);
  return CL_RET_OK;
}

// Unload a font.
static CLRet cyber_unload_font(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 font = (u32)cl_thread_r32(t);
  unload_font(font);
  return CL_RET_OK;
}

// Clear an image.
static CLRet cyber_clear_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  clear_image(destination, *color);
  return CL_RET_OK;
}

// Draw a single pixel on an image.
static CLRet cyber_draw_point_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_point_on_image(destination, x, y, *color);
  return CL_RET_OK;
}

// Draw a line on an image.
static CLRet cyber_draw_line_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 startPosX = cl_thread_i32(t);
  i32 startPosY = cl_thread_i32(t);
  i32 endPosX = cl_thread_i32(t);
  i32 endPosY = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, *color);
  return CL_RET_OK;
}

// Draw a filled rectangle on an image.
static CLRet cyber_draw_rectangle_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle_on_image(destination, posX, posY, width, height, *color);
  return CL_RET_OK;
}

// Draw a filled triangle on an image.
static CLRet cyber_draw_triangle_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 x1 = cl_thread_i32(t);
  i32 y1 = cl_thread_i32(t);
  i32 x2 = cl_thread_i32(t);
  i32 y2 = cl_thread_i32(t);
  i32 x3 = cl_thread_i32(t);
  i32 y3 = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, *color);
  return CL_RET_OK;
}

// Draw a filled ellipse on an image.
static CLRet cyber_draw_ellipse_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radiusX = cl_thread_i32(t);
  i32 radiusY = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, *color);
  return CL_RET_OK;
}

// Draw a circle on an image.
static CLRet cyber_draw_circle_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radius = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_circle_on_image(destination, centerX, centerY, radius, *color);
  return CL_RET_OK;
}

// Draw a filled polygon on an image.
static CLRet cyber_draw_polygon_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  CLSlice points_slice = cl_thread_slice(t);
  Vector* points = (Vector*)points_slice.ptr;
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_polygon_on_image(destination, points, (u32)points_slice.len, *color);
  return CL_RET_OK;
}

// Draw a filled round-rectangle on an image.
static CLRet cyber_draw_rectangle_rounded_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  i32 cornerRadius = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, *color);
  return CL_RET_OK;
}

// Draw an image on an image.
static CLRet cyber_draw_image_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  draw_image_on_image(destination, src, posX, posY);
  return CL_RET_OK;
}

// Draw a tinted image on an image.
static CLRet cyber_draw_image_tint_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  Color* tint = (Color*)cl_thread_param(t, sizeof(Color));
  draw_image_tint_on_image(destination, src, posX, posY, *tint);
  return CL_RET_OK;
}

// Draw an image, rotated, on an image.
static CLRet cyber_draw_image_rotated_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  f32 degrees = cl_thread_f32(t);
  f32 offsetX = cl_thread_f32(t);
  f32 offsetY = cl_thread_f32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter);
  return CL_RET_OK;
}

// Draw an image, flipped, on an image.
static CLRet cyber_draw_image_flipped_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  bool flipHorizontal = cl_thread_i32(t) != 0;
  bool flipVertical = cl_thread_i32(t) != 0;
  bool flipDiagonal = cl_thread_i32(t) != 0;
  draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
  return CL_RET_OK;
}

// Draw an image, scaled, on an image.
static CLRet cyber_draw_image_scaled_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  u32 src = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  f32 scaleX = cl_thread_f32(t);
  f32 scaleY = cl_thread_f32(t);
  f32 offsetX = cl_thread_f32(t);
  f32 offsetY = cl_thread_f32(t);
  i32 filter = (ImageFilter)cl_thread_i32(t);
  draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
  return CL_RET_OK;
}

// Draw some text on an image.
static CLRet cyber_draw_text_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  u32 font = (u32)cl_thread_r32(t);
  CLstr text_s = cl_thread_str(t);
  CLBytes text_b = cl_str_bytes(text_s);
  char* text = malloc(text_b.len + 1);
  memcpy(text, text_b.ptr, text_b.len);
  text[text_b.len] = '\0';
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_text_on_image(destination, font, text, posX, posY, *color);
  free(text);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) rectangle on the screen.
static CLRet cyber_draw_rectangle_outline(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle_outline(posX, posY, width, height, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) triangle on the screen.
static CLRet cyber_draw_triangle_outline(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 x1 = cl_thread_i32(t);
  i32 y1 = cl_thread_i32(t);
  i32 x2 = cl_thread_i32(t);
  i32 y2 = cl_thread_i32(t);
  i32 x3 = cl_thread_i32(t);
  i32 y3 = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) ellipse on the screen.
static CLRet cyber_draw_ellipse_outline(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radiusX = cl_thread_i32(t);
  i32 radiusY = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) circle on the screen.
static CLRet cyber_draw_circle_outline(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radius = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_circle_outline(centerX, centerY, radius, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) polygon on the screen.
static CLRet cyber_draw_polygon_outline(CLThread* t) {
  cl_thread_ret(t, 0);
  CLSlice points_slice = cl_thread_slice(t);
  Vector* points = (Vector*)points_slice.ptr;
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_polygon_outline(points, (u32)points_slice.len, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) arc on the screen.
static CLRet cyber_draw_arc_outline(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  f32 radius = cl_thread_f32(t);
  f32 startAngle = cl_thread_f32(t);
  f32 endAngle = cl_thread_f32(t);
  i32 segments = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) round-rectangle on the screen.
static CLRet cyber_draw_rectangle_rounded_outline(CLThread* t) {
  cl_thread_ret(t, 0);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  i32 cornerRadius = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) rectangle on an image.
static CLRet cyber_draw_rectangle_outline_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) triangle on an image.
static CLRet cyber_draw_triangle_outline_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 x1 = cl_thread_i32(t);
  i32 y1 = cl_thread_i32(t);
  i32 x2 = cl_thread_i32(t);
  i32 y2 = cl_thread_i32(t);
  i32 x3 = cl_thread_i32(t);
  i32 y3 = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) ellipse on an image.
static CLRet cyber_draw_ellipse_outline_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radiusX = cl_thread_i32(t);
  i32 radiusY = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) circle on an image.
static CLRet cyber_draw_circle_outline_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 centerX = cl_thread_i32(t);
  i32 centerY = cl_thread_i32(t);
  i32 radius = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) polygon on an image.
static CLRet cyber_draw_polygon_outline_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  CLSlice points_slice = cl_thread_slice(t);
  Vector* points = (Vector*)points_slice.ptr;
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_polygon_outline_on_image(destination, points, (u32)points_slice.len, thickness, *color);
  return CL_RET_OK;
}

// Draw a outlined (with thickness) round-rectangle on an image.
static CLRet cyber_draw_rectangle_rounded_outline_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 destination = (u32)cl_thread_r32(t);
  i32 x = cl_thread_i32(t);
  i32 y = cl_thread_i32(t);
  i32 width = cl_thread_i32(t);
  i32 height = cl_thread_i32(t);
  i32 cornerRadius = cl_thread_i32(t);
  i32 thickness = cl_thread_i32(t);
  Color* color = (Color*)cl_thread_param(t, sizeof(Color));
  draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, *color);
  return CL_RET_OK;
}


// GUI

// Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.
static CLRet cyber_gui_begin_window(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  CLstr title_s = cl_thread_str(t);
  CLBytes title_b = cl_str_bytes(title_s);
  char* title = malloc(title_b.len + 1);
  memcpy(title, title_b.ptr, title_b.len);
  title[title_b.len] = '\0';
  Rectangle* rect = (Rectangle*)cl_thread_param(t, sizeof(Rectangle));
  bool ret = gui_begin_window(title, *rect);
  *out = ret;
  free(title);
  return CL_RET_OK;
}

// End the current GUI window.
static CLRet cyber_gui_end_window(CLThread* t) {
  cl_thread_ret(t, 0);
  gui_end_window();
  return CL_RET_OK;
}

// A button. Returns true when it is clicked.
static CLRet cyber_gui_button(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  CLstr label_s = cl_thread_str(t);
  CLBytes label_b = cl_str_bytes(label_s);
  char* label = malloc(label_b.len + 1);
  memcpy(label, label_b.ptr, label_b.len);
  label[label_b.len] = '\0';
  bool ret = gui_button(label);
  *out = ret;
  free(label);
  return CL_RET_OK;
}

// A static text label.
static CLRet cyber_gui_label(CLThread* t) {
  cl_thread_ret(t, 0);
  CLstr text_s = cl_thread_str(t);
  CLBytes text_b = cl_str_bytes(text_s);
  char* text = malloc(text_b.len + 1);
  memcpy(text, text_b.ptr, text_b.len);
  text[text_b.len] = '\0';
  gui_label(text);
  free(text);
  return CL_RET_OK;
}

// A block of wrapping text.
static CLRet cyber_gui_text(CLThread* t) {
  cl_thread_ret(t, 0);
  CLstr text_s = cl_thread_str(t);
  CLBytes text_b = cl_str_bytes(text_s);
  char* text = malloc(text_b.len + 1);
  memcpy(text, text_b.ptr, text_b.len);
  text[text_b.len] = '\0';
  gui_text(text);
  free(text);
  return CL_RET_OK;
}

// A checkbox. Returns the (possibly changed) state.
static CLRet cyber_gui_checkbox(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  CLstr label_s = cl_thread_str(t);
  CLBytes label_b = cl_str_bytes(label_s);
  char* label = malloc(label_b.len + 1);
  memcpy(label, label_b.ptr, label_b.len);
  label[label_b.len] = '\0';
  bool state = cl_thread_i32(t) != 0;
  bool ret = gui_checkbox(label, state);
  *out = ret;
  free(label);
  return CL_RET_OK;
}

// A slider. Returns the (possibly changed) value.
static CLRet cyber_gui_slider(CLThread* t) {
  f32* out = (f32*)cl_thread_ret(t, sizeof(f32));
  f32 value = cl_thread_f32(t);
  f32 low = cl_thread_f32(t);
  f32 high = cl_thread_f32(t);
  f32 ret = gui_slider(value, low, high);
  *out = ret;
  return CL_RET_OK;
}

// Set the current layout row - the column widths (negative for flexible), and the row height.
static CLRet cyber_gui_layout_row(CLThread* t) {
  cl_thread_ret(t, 0);
  CLSlice widths_slice = cl_thread_slice(t);
  i32* widths = (i32*)widths_slice.ptr;
  i32 height = cl_thread_i32(t);
  gui_layout_row(widths, (u32)widths_slice.len, height);
  return CL_RET_OK;
}

// Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.
static CLRet cyber_gui_end(CLThread* t) {
  cl_thread_ret(t, 0);
  gui_end();
  return CL_RET_OK;
}

// Draw the GUI to an image (0 is the screen).
static CLRet cyber_gui_draw(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 dst = (u32)cl_thread_r32(t);
  gui_draw(dst);
  return CL_RET_OK;
}


// INPUT

// Has the key been pressed? (tracks unpress/read correctly.)
static CLRet cyber_key_pressed(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 key = (Key)cl_thread_i32(t);
  bool ret = key_pressed(key);
  *out = ret;
  return CL_RET_OK;
}

// Is the key currently down?
static CLRet cyber_key_down(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 key = (Key)cl_thread_i32(t);
  bool ret = key_down(key);
  *out = ret;
  return CL_RET_OK;
}

// Has the key been released? (tracks press/read correctly.)
static CLRet cyber_key_released(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 key = (Key)cl_thread_i32(t);
  bool ret = key_released(key);
  *out = ret;
  return CL_RET_OK;
}

// Is the key currently up?
static CLRet cyber_key_up(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 key = (Key)cl_thread_i32(t);
  bool ret = key_up(key);
  *out = ret;
  return CL_RET_OK;
}

// Has the button been pressed? (tracks unpress/read correctly.)
static CLRet cyber_gamepad_button_pressed(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 gamepad = cl_thread_i32(t);
  i32 button = (GamepadButton)cl_thread_i32(t);
  bool ret = gamepad_button_pressed(gamepad, button);
  *out = ret;
  return CL_RET_OK;
}

// Is the button currently down?
static CLRet cyber_gamepad_button_down(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 gamepad = cl_thread_i32(t);
  i32 button = (GamepadButton)cl_thread_i32(t);
  bool ret = gamepad_button_down(gamepad, button);
  *out = ret;
  return CL_RET_OK;
}

// Has the button been released? (tracks press/read correctly.)
static CLRet cyber_gamepad_button_released(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 gamepad = cl_thread_i32(t);
  i32 button = (GamepadButton)cl_thread_i32(t);
  bool ret = gamepad_button_released(gamepad, button);
  *out = ret;
  return CL_RET_OK;
}

// Get current position of mouse.
static CLRet cyber_mouse_position(CLThread* t) {
  Vector* out = (Vector*)cl_thread_ret(t, sizeof(Vector));
  Vector* ret = mouse_position();
  *out = *ret;
  return CL_RET_OK;
}

// Has the button been pressed? (tracks unpress/read correctly.)
static CLRet cyber_mouse_button_pressed(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 button = (MouseButton)cl_thread_i32(t);
  bool ret = mouse_button_pressed(button);
  *out = ret;
  return CL_RET_OK;
}

// Is the button currently down?
static CLRet cyber_mouse_button_down(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 button = (MouseButton)cl_thread_i32(t);
  bool ret = mouse_button_down(button);
  *out = ret;
  return CL_RET_OK;
}

// Has the button been released? (tracks press/read correctly.)
static CLRet cyber_mouse_button_released(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 button = (MouseButton)cl_thread_i32(t);
  bool ret = mouse_button_released(button);
  *out = ret;
  return CL_RET_OK;
}

// Is the button currently up?
static CLRet cyber_mouse_button_up(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  i32 button = (MouseButton)cl_thread_i32(t);
  bool ret = mouse_button_up(button);
  *out = ret;
  return CL_RET_OK;
}


// SOUND

// Load a sound from a file in cart.
static CLRet cyber_load_sound(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  CLstr filename_s = cl_thread_str(t);
  CLBytes filename_b = cl_str_bytes(filename_s);
  char* filename = malloc(filename_b.len + 1);
  memcpy(filename, filename_b.ptr, filename_b.len);
  filename[filename_b.len] = '\0';
  u32 ret = load_sound(filename);
  *out = ret;
  free(filename);
  return CL_RET_OK;
}

// Play a sound.
static CLRet cyber_play_sound(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 sound = (u32)cl_thread_r32(t);
  bool loop = cl_thread_i32(t) != 0;
  play_sound(sound, loop);
  return CL_RET_OK;
}

// Stop a sound.
static CLRet cyber_stop_sound(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 sound = (u32)cl_thread_r32(t);
  stop_sound(sound);
  return CL_RET_OK;
}

// Unload a sound.
static CLRet cyber_unload_sound(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 sound = (u32)cl_thread_r32(t);
  unload_sound(sound);
  return CL_RET_OK;
}

// Speak some text and return a sound. Set things to 0 for defaults.
static CLRet cyber_tts_sound(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  CLstr text_s = cl_thread_str(t);
  CLBytes text_b = cl_str_bytes(text_s);
  char* text = malloc(text_b.len + 1);
  memcpy(text, text_b.ptr, text_b.len);
  text[text_b.len] = '\0';
  bool phonetic = cl_thread_i32(t) != 0;
  i32 pitch = cl_thread_i32(t);
  i32 speed = cl_thread_i32(t);
  i32 throat = cl_thread_i32(t);
  i32 mouth = cl_thread_i32(t);
  bool sing = cl_thread_i32(t) != 0;
  u32 ret = tts_sound(text, phonetic, pitch, speed, throat, mouth, sing);
  *out = ret;
  free(text);
  return CL_RET_OK;
}

// Create Sfx sound.
static CLRet cyber_sfx_sound(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  SfxParams* params = (SfxParams*)cl_thread_param(t, sizeof(SfxParams));
  u32 ret = sfx_sound(*params);
  *out = ret;
  return CL_RET_OK;
}

// Create Sfx parameters.
static CLRet cyber_sfx_generate(CLThread* t) {
  SfxParams* out = (SfxParams*)cl_thread_ret(t, sizeof(SfxParams));
  i32 type_ = (SfxPresetType)cl_thread_i32(t);
  SfxParams* ret = sfx_generate(type_);
  *out = *ret;
  return CL_RET_OK;
}


// TILE

// Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
static CLRet cyber_load_tilemap(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  CLstr filename_s = cl_thread_str(t);
  CLBytes filename_b = cl_str_bytes(filename_s);
  char* filename = malloc(filename_b.len + 1);
  memcpy(filename, filename_b.ptr, filename_b.len);
  filename[filename_b.len] = '\0';
  u32 ret = load_tilemap(filename);
  *out = ret;
  free(filename);
  return CL_RET_OK;
}

// Unload a tilemap.
static CLRet cyber_unload_tilemap(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  unload_tilemap(tilemap);
  return CL_RET_OK;
}

// Update a tilemap's animation timers (deltaTime is in seconds).
static CLRet cyber_tile_update(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  f32 deltaTime = cl_thread_f32(t);
  tile_update(tilemap, deltaTime);
  return CL_RET_OK;
}

// Get the size of a tilemap, in tiles.
static CLRet cyber_tile_map_size(CLThread* t) {
  Dimensions* out = (Dimensions*)cl_thread_ret(t, sizeof(Dimensions));
  u32 tilemap = (u32)cl_thread_r32(t);
  Dimensions* ret = tile_map_size(tilemap);
  *out = *ret;
  return CL_RET_OK;
}

// Get the size of a single tile of a tilemap, in pixels.
static CLRet cyber_tile_tile_size(CLThread* t) {
  Dimensions* out = (Dimensions*)cl_thread_ret(t, sizeof(Dimensions));
  u32 tilemap = (u32)cl_thread_r32(t);
  Dimensions* ret = tile_tile_size(tilemap);
  *out = *ret;
  return CL_RET_OK;
}

// Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)
static CLRet cyber_tile_map_prop(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  CLstr name_s = cl_thread_str(t);
  CLBytes name_b = cl_str_bytes(name_s);
  char* name = malloc(name_b.len + 1);
  memcpy(name, name_b.ptr, name_b.len);
  name[name_b.len] = '\0';
  TilemapProp* ret = tile_map_prop(tilemap, name);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  free(name);
  return CL_RET_OK;
}

// Get the number of custom properties on a tilemap.
static CLRet cyber_tile_map_prop_count(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 ret = tile_map_prop_count(tilemap);
  *out = ret;
  return CL_RET_OK;
}

// Get a custom property of a tilemap, by index (PROP_NONE when out of range.)
static CLRet cyber_tile_map_prop_at(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 index = cl_thread_i32(t);
  TilemapProp* ret = tile_map_prop_at(tilemap, index);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  return CL_RET_OK;
}

// Draw a tilemap on the screen.
static CLRet cyber_tile_draw(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  tile_draw(tilemap, posX, posY);
  return CL_RET_OK;
}

// Draw a tilemap on the screen, tinted by a color.
static CLRet cyber_tile_draw_tint(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  Color* tint = (Color*)cl_thread_param(t, sizeof(Color));
  tile_draw_tint(tilemap, posX, posY, *tint);
  return CL_RET_OK;
}

// Draw a tilemap on an image.
static CLRet cyber_tile_draw_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 dst = (u32)cl_thread_r32(t);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  tile_draw_on_image(dst, tilemap, posX, posY);
  return CL_RET_OK;
}

// Render a whole tilemap to a new image.
static CLRet cyber_tilemap_image(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 tilemap = (u32)cl_thread_r32(t);
  u32 ret = tilemap_image(tilemap);
  *out = ret;
  return CL_RET_OK;
}

// Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.
static CLRet cyber_tile_layer_count(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 ret = tile_layer_count(tilemap);
  *out = ret;
  return CL_RET_OK;
}

// Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)
static CLRet cyber_tile_layer_index(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  CLstr name_s = cl_thread_str(t);
  CLBytes name_b = cl_str_bytes(name_s);
  char* name = malloc(name_b.len + 1);
  memcpy(name, name_b.ptr, name_b.len);
  name[name_b.len] = '\0';
  i32 ret = tile_layer_index(tilemap, name);
  *out = ret;
  free(name);
  return CL_RET_OK;
}

// Get the name of a layer of a tilemap.
static CLRet cyber_tile_layer_name(CLThread* t) {
  CLstr* out = (CLstr*)cl_thread_ret(t, sizeof(CLstr));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  char* ret = tile_layer_name(tilemap, layer);
  *out = cl_ustr_init(t, CL_BYTES(ret));
  return CL_RET_OK;
}

// Get the kind of a layer of a tilemap.
static CLRet cyber_tile_layer_type(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 ret = tile_layer_type(tilemap, layer);
  *out = ret;
  return CL_RET_OK;
}

// Get the size of a layer of a tilemap, in tiles.
static CLRet cyber_tile_layer_size(CLThread* t) {
  Dimensions* out = (Dimensions*)cl_thread_ret(t, sizeof(Dimensions));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  Dimensions* ret = tile_layer_size(tilemap, layer);
  *out = *ret;
  return CL_RET_OK;
}

// Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.
static CLRet cyber_tile_layer_visible(CLThread* t) {
  bool* out = (bool*)cl_thread_ret(t, sizeof(bool));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  bool ret = tile_layer_visible(tilemap, layer);
  *out = ret;
  return CL_RET_OK;
}

// Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)
static CLRet cyber_tile_layer_prop(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  CLstr name_s = cl_thread_str(t);
  CLBytes name_b = cl_str_bytes(name_s);
  char* name = malloc(name_b.len + 1);
  memcpy(name, name_b.ptr, name_b.len);
  name[name_b.len] = '\0';
  TilemapProp* ret = tile_layer_prop(tilemap, layer, name);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  free(name);
  return CL_RET_OK;
}

// Get the number of custom properties on a layer of a tilemap.
static CLRet cyber_tile_layer_prop_count(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 ret = tile_layer_prop_count(tilemap, layer);
  *out = ret;
  return CL_RET_OK;
}

// Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)
static CLRet cyber_tile_layer_prop_at(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 index = cl_thread_i32(t);
  TilemapProp* ret = tile_layer_prop_at(tilemap, layer, index);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  return CL_RET_OK;
}

// Draw a single layer of a tilemap on the screen.
static CLRet cyber_tile_draw_layer(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  tile_draw_layer(tilemap, layer, posX, posY);
  return CL_RET_OK;
}

// Draw a single layer of a tilemap on the screen, tinted by a color.
static CLRet cyber_tile_draw_layer_tint(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  Color* tint = (Color*)cl_thread_param(t, sizeof(Color));
  tile_draw_layer_tint(tilemap, layer, posX, posY, *tint);
  return CL_RET_OK;
}

// Draw a single layer of a tilemap on an image.
static CLRet cyber_tile_draw_layer_on_image(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 dst = (u32)cl_thread_r32(t);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  tile_draw_layer_on_image(dst, tilemap, layer, posX, posY);
  return CL_RET_OK;
}

// Render a single layer of a tilemap to a new image.
static CLRet cyber_tile_layer_image(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  u32 ret = tile_layer_image(tilemap, layer);
  *out = ret;
  return CL_RET_OK;
}

// Get the gid of the tile at a column/row in a tilemap layer.
static CLRet cyber_tile_get_tile(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 column = cl_thread_i32(t);
  i32 row = cl_thread_i32(t);
  i32 ret = tile_get_tile(tilemap, layer, column, row);
  *out = ret;
  return CL_RET_OK;
}

// Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.
static CLRet cyber_tile_set_tile(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 column = cl_thread_i32(t);
  i32 row = cl_thread_i32(t);
  i32 gid = cl_thread_i32(t);
  tile_set_tile(tilemap, layer, column, row, gid);
  return CL_RET_OK;
}

// Draw a single tile from a tilemap on the screen.
static CLRet cyber_tile_draw_tile(CLThread* t) {
  cl_thread_ret(t, 0);
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 gid = cl_thread_i32(t);
  i32 posX = cl_thread_i32(t);
  i32 posY = cl_thread_i32(t);
  tile_draw_tile(tilemap, gid, posX, posY);
  return CL_RET_OK;
}

// Get a copy of the image of a single tile in a tilemap.
static CLRet cyber_tile_image(CLThread* t) {
  u32* out = (u32*)cl_thread_ret(t, sizeof(u32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 gid = cl_thread_i32(t);
  u32 ret = tile_image(tilemap, gid);
  *out = ret;
  return CL_RET_OK;
}

// Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.
static CLRet cyber_tile_gid_prop(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 gid = cl_thread_i32(t);
  CLstr name_s = cl_thread_str(t);
  CLBytes name_b = cl_str_bytes(name_s);
  char* name = malloc(name_b.len + 1);
  memcpy(name, name_b.ptr, name_b.len);
  name[name_b.len] = '\0';
  TilemapProp* ret = tile_gid_prop(tilemap, gid, name);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  free(name);
  return CL_RET_OK;
}

// Get the number of custom properties on a tile of a tilemap.
static CLRet cyber_tile_gid_prop_count(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 gid = cl_thread_i32(t);
  i32 ret = tile_gid_prop_count(tilemap, gid);
  *out = ret;
  return CL_RET_OK;
}

// Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)
static CLRet cyber_tile_gid_prop_at(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 gid = cl_thread_i32(t);
  i32 index = cl_thread_i32(t);
  TilemapProp* ret = tile_gid_prop_at(tilemap, gid, index);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  return CL_RET_OK;
}

// Get the number of objects on an object-layer of a tilemap.
static CLRet cyber_tile_object_count(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 ret = tile_object_count(tilemap, layer);
  *out = ret;
  return CL_RET_OK;
}

// Get an object from an object-layer of a tilemap.
static CLRet cyber_tile_object(CLThread* t) {
  CyTilemapObject* out = (CyTilemapObject*)cl_thread_ret(t, sizeof(CyTilemapObject));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 index = cl_thread_i32(t);
  TilemapObject* ret = tile_object(tilemap, layer, index);
  out->id = ret->id;
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = cl_ustr_init(t, CL_BYTES(ret->type == NULL ? "" : ret->type));
  out->gid = ret->gid;
  out->x = ret->x;
  out->y = ret->y;
  out->width = ret->width;
  out->height = ret->height;
  out->rotation = ret->rotation;
  out->visible = ret->visible;
  return CL_RET_OK;
}

// Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)
static CLRet cyber_tile_object_index(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  CLstr name_s = cl_thread_str(t);
  CLBytes name_b = cl_str_bytes(name_s);
  char* name = malloc(name_b.len + 1);
  memcpy(name, name_b.ptr, name_b.len);
  name[name_b.len] = '\0';
  i32 ret = tile_object_index(tilemap, layer, name);
  *out = ret;
  free(name);
  return CL_RET_OK;
}

// Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)
static CLRet cyber_tile_object_prop(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 index = cl_thread_i32(t);
  CLstr name_s = cl_thread_str(t);
  CLBytes name_b = cl_str_bytes(name_s);
  char* name = malloc(name_b.len + 1);
  memcpy(name, name_b.ptr, name_b.len);
  name[name_b.len] = '\0';
  TilemapProp* ret = tile_object_prop(tilemap, layer, index, name);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  free(name);
  return CL_RET_OK;
}

// Get the number of custom properties on an object of a tilemap.
static CLRet cyber_tile_object_prop_count(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 index = cl_thread_i32(t);
  i32 ret = tile_object_prop_count(tilemap, layer, index);
  *out = ret;
  return CL_RET_OK;
}

// Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)
static CLRet cyber_tile_object_prop_at(CLThread* t) {
  CyTilemapProp* out = (CyTilemapProp*)cl_thread_ret(t, sizeof(CyTilemapProp));
  u32 tilemap = (u32)cl_thread_r32(t);
  i32 layer = cl_thread_i32(t);
  i32 index = cl_thread_i32(t);
  i32 propIndex = cl_thread_i32(t);
  TilemapProp* ret = tile_object_prop_at(tilemap, layer, index, propIndex);
  out->name = cl_ustr_init(t, CL_BYTES(ret->name == NULL ? "" : ret->name));
  out->type = ret->type;
  out->integer = ret->integer;
  out->number = ret->number;
  out->text = cl_ustr_init(t, CL_BYTES(ret->text == NULL ? "" : ret->text));
  return CL_RET_OK;
}


// TYPES


// UTILITIES

// Get system-time (ms) since unix epoch.
static CLRet cyber_current_time(CLThread* t) {
  u64* out = (u64*)cl_thread_ret(t, sizeof(u64));
  u64 ret = current_time();
  *out = ret;
  return CL_RET_OK;
}

// Get the change in time (seconds) since the last update run.
static CLRet cyber_delta_time(CLThread* t) {
  f32* out = (f32*)cl_thread_ret(t, sizeof(f32));
  f32 ret = delta_time();
  *out = ret;
  return CL_RET_OK;
}

// Get a random integer between 2 numbers.
static CLRet cyber_random_int(CLThread* t) {
  i32* out = (i32*)cl_thread_ret(t, sizeof(i32));
  i32 min = cl_thread_i32(t);
  i32 max = cl_thread_i32(t);
  i32 ret = random_int(min, max);
  *out = ret;
  return CL_RET_OK;
}

// Get the random-seed.
static CLRet cyber_random_seed_get(CLThread* t) {
  u64* out = (u64*)cl_thread_ret(t, sizeof(u64));
  u64 ret = random_seed_get();
  *out = ret;
  return CL_RET_OK;
}

// Set the random-seed.
static CLRet cyber_random_seed_set(CLThread* t) {
  cl_thread_ret(t, 0);
  u64 seed = (u64)cl_thread_r64(t);
  random_seed_set(seed);
  return CL_RET_OK;
}

// module loader: `use null0` resolves to the baked-in module above.
// Screen/font handles, colors and enum values are all plain `global
// NAME TYPE = value` declarations inside NULL0_CY, not `#[bind] global`
// - see gen_cart_cyber.js for why. Only the two frame-arg slots below
// are real host-bound globals (they need to be host-writable).
static bool module_loader(CLVM* vmp, CLSym* mod, CLBytes uri, CLLoaderResult* res) {
  if (uri.len == 5 && strncmp(uri.ptr, "null0", 5) == 0) {
  cl_mod_add_func(mod, CL_BYTES("color_tint"), CL_BIND_FUNC(cyber_color_tint));
  cl_mod_add_func(mod, CL_BYTES("color_fade"), CL_BIND_FUNC(cyber_color_fade));
  cl_mod_add_func(mod, CL_BYTES("color_brightness"), CL_BIND_FUNC(cyber_color_brightness));
  cl_mod_add_func(mod, CL_BYTES("color_invert"), CL_BIND_FUNC(cyber_color_invert));
  cl_mod_add_func(mod, CL_BYTES("color_alpha_blend"), CL_BIND_FUNC(cyber_color_alpha_blend));
  cl_mod_add_func(mod, CL_BYTES("color_contrast"), CL_BIND_FUNC(cyber_color_contrast));
  cl_mod_add_func(mod, CL_BYTES("color_bilinear_interpolate"), CL_BIND_FUNC(cyber_color_bilinear_interpolate));
  cl_mod_add_func(mod, CL_BYTES("new_image"), CL_BIND_FUNC(cyber_new_image));
  cl_mod_add_func(mod, CL_BYTES("image_copy"), CL_BIND_FUNC(cyber_image_copy));
  cl_mod_add_func(mod, CL_BYTES("image_subimage"), CL_BIND_FUNC(cyber_image_subimage));
  cl_mod_add_func(mod, CL_BYTES("clear"), CL_BIND_FUNC(cyber_clear));
  cl_mod_add_func(mod, CL_BYTES("draw_point"), CL_BIND_FUNC(cyber_draw_point));
  cl_mod_add_func(mod, CL_BYTES("draw_line"), CL_BIND_FUNC(cyber_draw_line));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle"), CL_BIND_FUNC(cyber_draw_rectangle));
  cl_mod_add_func(mod, CL_BYTES("draw_triangle"), CL_BIND_FUNC(cyber_draw_triangle));
  cl_mod_add_func(mod, CL_BYTES("draw_ellipse"), CL_BIND_FUNC(cyber_draw_ellipse));
  cl_mod_add_func(mod, CL_BYTES("draw_circle"), CL_BIND_FUNC(cyber_draw_circle));
  cl_mod_add_func(mod, CL_BYTES("draw_polygon"), CL_BIND_FUNC(cyber_draw_polygon));
  cl_mod_add_func(mod, CL_BYTES("draw_arc"), CL_BIND_FUNC(cyber_draw_arc));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle_rounded"), CL_BIND_FUNC(cyber_draw_rectangle_rounded));
  cl_mod_add_func(mod, CL_BYTES("draw_image"), CL_BIND_FUNC(cyber_draw_image));
  cl_mod_add_func(mod, CL_BYTES("draw_image_tint"), CL_BIND_FUNC(cyber_draw_image_tint));
  cl_mod_add_func(mod, CL_BYTES("draw_image_rotated"), CL_BIND_FUNC(cyber_draw_image_rotated));
  cl_mod_add_func(mod, CL_BYTES("draw_image_flipped"), CL_BIND_FUNC(cyber_draw_image_flipped));
  cl_mod_add_func(mod, CL_BYTES("draw_image_scaled"), CL_BIND_FUNC(cyber_draw_image_scaled));
  cl_mod_add_func(mod, CL_BYTES("draw_text"), CL_BIND_FUNC(cyber_draw_text));
  cl_mod_add_func(mod, CL_BYTES("save_image"), CL_BIND_FUNC(cyber_save_image));
  cl_mod_add_func(mod, CL_BYTES("load_image"), CL_BIND_FUNC(cyber_load_image));
  cl_mod_add_func(mod, CL_BYTES("image_resize"), CL_BIND_FUNC(cyber_image_resize));
  cl_mod_add_func(mod, CL_BYTES("image_scale"), CL_BIND_FUNC(cyber_image_scale));
  cl_mod_add_func(mod, CL_BYTES("image_color_replace"), CL_BIND_FUNC(cyber_image_color_replace));
  cl_mod_add_func(mod, CL_BYTES("image_color_tint"), CL_BIND_FUNC(cyber_image_color_tint));
  cl_mod_add_func(mod, CL_BYTES("image_color_fade"), CL_BIND_FUNC(cyber_image_color_fade));
  cl_mod_add_func(mod, CL_BYTES("font_copy"), CL_BIND_FUNC(cyber_font_copy));
  cl_mod_add_func(mod, CL_BYTES("font_scale"), CL_BIND_FUNC(cyber_font_scale));
  cl_mod_add_func(mod, CL_BYTES("load_font_bmf"), CL_BIND_FUNC(cyber_load_font_bmf));
  cl_mod_add_func(mod, CL_BYTES("load_font_bmf_from_image"), CL_BIND_FUNC(cyber_load_font_bmf_from_image));
  cl_mod_add_func(mod, CL_BYTES("measure_text"), CL_BIND_FUNC(cyber_measure_text));
  cl_mod_add_func(mod, CL_BYTES("measure_image"), CL_BIND_FUNC(cyber_measure_image));
  cl_mod_add_func(mod, CL_BYTES("load_font_tty"), CL_BIND_FUNC(cyber_load_font_tty));
  cl_mod_add_func(mod, CL_BYTES("load_font_tty_from_image"), CL_BIND_FUNC(cyber_load_font_tty_from_image));
  cl_mod_add_func(mod, CL_BYTES("load_font_ttf"), CL_BIND_FUNC(cyber_load_font_ttf));
  cl_mod_add_func(mod, CL_BYTES("image_color_invert"), CL_BIND_FUNC(cyber_image_color_invert));
  cl_mod_add_func(mod, CL_BYTES("image_alpha_border"), CL_BIND_FUNC(cyber_image_alpha_border));
  cl_mod_add_func(mod, CL_BYTES("image_crop"), CL_BIND_FUNC(cyber_image_crop));
  cl_mod_add_func(mod, CL_BYTES("image_alpha_crop"), CL_BIND_FUNC(cyber_image_alpha_crop));
  cl_mod_add_func(mod, CL_BYTES("image_color_brightness"), CL_BIND_FUNC(cyber_image_color_brightness));
  cl_mod_add_func(mod, CL_BYTES("image_flip"), CL_BIND_FUNC(cyber_image_flip));
  cl_mod_add_func(mod, CL_BYTES("image_color_contrast"), CL_BIND_FUNC(cyber_image_color_contrast));
  cl_mod_add_func(mod, CL_BYTES("image_alpha_mask"), CL_BIND_FUNC(cyber_image_alpha_mask));
  cl_mod_add_func(mod, CL_BYTES("image_rotate"), CL_BIND_FUNC(cyber_image_rotate));
  cl_mod_add_func(mod, CL_BYTES("image_gradient"), CL_BIND_FUNC(cyber_image_gradient));
  cl_mod_add_func(mod, CL_BYTES("unload_image"), CL_BIND_FUNC(cyber_unload_image));
  cl_mod_add_func(mod, CL_BYTES("unload_font"), CL_BIND_FUNC(cyber_unload_font));
  cl_mod_add_func(mod, CL_BYTES("clear_image"), CL_BIND_FUNC(cyber_clear_image));
  cl_mod_add_func(mod, CL_BYTES("draw_point_on_image"), CL_BIND_FUNC(cyber_draw_point_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_line_on_image"), CL_BIND_FUNC(cyber_draw_line_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle_on_image"), CL_BIND_FUNC(cyber_draw_rectangle_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_triangle_on_image"), CL_BIND_FUNC(cyber_draw_triangle_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_ellipse_on_image"), CL_BIND_FUNC(cyber_draw_ellipse_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_circle_on_image"), CL_BIND_FUNC(cyber_draw_circle_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_polygon_on_image"), CL_BIND_FUNC(cyber_draw_polygon_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle_rounded_on_image"), CL_BIND_FUNC(cyber_draw_rectangle_rounded_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_image_on_image"), CL_BIND_FUNC(cyber_draw_image_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_image_tint_on_image"), CL_BIND_FUNC(cyber_draw_image_tint_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_image_rotated_on_image"), CL_BIND_FUNC(cyber_draw_image_rotated_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_image_flipped_on_image"), CL_BIND_FUNC(cyber_draw_image_flipped_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_image_scaled_on_image"), CL_BIND_FUNC(cyber_draw_image_scaled_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_text_on_image"), CL_BIND_FUNC(cyber_draw_text_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle_outline"), CL_BIND_FUNC(cyber_draw_rectangle_outline));
  cl_mod_add_func(mod, CL_BYTES("draw_triangle_outline"), CL_BIND_FUNC(cyber_draw_triangle_outline));
  cl_mod_add_func(mod, CL_BYTES("draw_ellipse_outline"), CL_BIND_FUNC(cyber_draw_ellipse_outline));
  cl_mod_add_func(mod, CL_BYTES("draw_circle_outline"), CL_BIND_FUNC(cyber_draw_circle_outline));
  cl_mod_add_func(mod, CL_BYTES("draw_polygon_outline"), CL_BIND_FUNC(cyber_draw_polygon_outline));
  cl_mod_add_func(mod, CL_BYTES("draw_arc_outline"), CL_BIND_FUNC(cyber_draw_arc_outline));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle_rounded_outline"), CL_BIND_FUNC(cyber_draw_rectangle_rounded_outline));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle_outline_on_image"), CL_BIND_FUNC(cyber_draw_rectangle_outline_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_triangle_outline_on_image"), CL_BIND_FUNC(cyber_draw_triangle_outline_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_ellipse_outline_on_image"), CL_BIND_FUNC(cyber_draw_ellipse_outline_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_circle_outline_on_image"), CL_BIND_FUNC(cyber_draw_circle_outline_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_polygon_outline_on_image"), CL_BIND_FUNC(cyber_draw_polygon_outline_on_image));
  cl_mod_add_func(mod, CL_BYTES("draw_rectangle_rounded_outline_on_image"), CL_BIND_FUNC(cyber_draw_rectangle_rounded_outline_on_image));
  cl_mod_add_func(mod, CL_BYTES("gui_begin_window"), CL_BIND_FUNC(cyber_gui_begin_window));
  cl_mod_add_func(mod, CL_BYTES("gui_end_window"), CL_BIND_FUNC(cyber_gui_end_window));
  cl_mod_add_func(mod, CL_BYTES("gui_button"), CL_BIND_FUNC(cyber_gui_button));
  cl_mod_add_func(mod, CL_BYTES("gui_label"), CL_BIND_FUNC(cyber_gui_label));
  cl_mod_add_func(mod, CL_BYTES("gui_text"), CL_BIND_FUNC(cyber_gui_text));
  cl_mod_add_func(mod, CL_BYTES("gui_checkbox"), CL_BIND_FUNC(cyber_gui_checkbox));
  cl_mod_add_func(mod, CL_BYTES("gui_slider"), CL_BIND_FUNC(cyber_gui_slider));
  cl_mod_add_func(mod, CL_BYTES("gui_layout_row"), CL_BIND_FUNC(cyber_gui_layout_row));
  cl_mod_add_func(mod, CL_BYTES("gui_end"), CL_BIND_FUNC(cyber_gui_end));
  cl_mod_add_func(mod, CL_BYTES("gui_draw"), CL_BIND_FUNC(cyber_gui_draw));
  cl_mod_add_func(mod, CL_BYTES("key_pressed"), CL_BIND_FUNC(cyber_key_pressed));
  cl_mod_add_func(mod, CL_BYTES("key_down"), CL_BIND_FUNC(cyber_key_down));
  cl_mod_add_func(mod, CL_BYTES("key_released"), CL_BIND_FUNC(cyber_key_released));
  cl_mod_add_func(mod, CL_BYTES("key_up"), CL_BIND_FUNC(cyber_key_up));
  cl_mod_add_func(mod, CL_BYTES("gamepad_button_pressed"), CL_BIND_FUNC(cyber_gamepad_button_pressed));
  cl_mod_add_func(mod, CL_BYTES("gamepad_button_down"), CL_BIND_FUNC(cyber_gamepad_button_down));
  cl_mod_add_func(mod, CL_BYTES("gamepad_button_released"), CL_BIND_FUNC(cyber_gamepad_button_released));
  cl_mod_add_func(mod, CL_BYTES("mouse_position"), CL_BIND_FUNC(cyber_mouse_position));
  cl_mod_add_func(mod, CL_BYTES("mouse_button_pressed"), CL_BIND_FUNC(cyber_mouse_button_pressed));
  cl_mod_add_func(mod, CL_BYTES("mouse_button_down"), CL_BIND_FUNC(cyber_mouse_button_down));
  cl_mod_add_func(mod, CL_BYTES("mouse_button_released"), CL_BIND_FUNC(cyber_mouse_button_released));
  cl_mod_add_func(mod, CL_BYTES("mouse_button_up"), CL_BIND_FUNC(cyber_mouse_button_up));
  cl_mod_add_func(mod, CL_BYTES("load_sound"), CL_BIND_FUNC(cyber_load_sound));
  cl_mod_add_func(mod, CL_BYTES("play_sound"), CL_BIND_FUNC(cyber_play_sound));
  cl_mod_add_func(mod, CL_BYTES("stop_sound"), CL_BIND_FUNC(cyber_stop_sound));
  cl_mod_add_func(mod, CL_BYTES("unload_sound"), CL_BIND_FUNC(cyber_unload_sound));
  cl_mod_add_func(mod, CL_BYTES("tts_sound"), CL_BIND_FUNC(cyber_tts_sound));
  cl_mod_add_func(mod, CL_BYTES("sfx_sound"), CL_BIND_FUNC(cyber_sfx_sound));
  cl_mod_add_func(mod, CL_BYTES("sfx_generate"), CL_BIND_FUNC(cyber_sfx_generate));
  cl_mod_add_func(mod, CL_BYTES("load_tilemap"), CL_BIND_FUNC(cyber_load_tilemap));
  cl_mod_add_func(mod, CL_BYTES("unload_tilemap"), CL_BIND_FUNC(cyber_unload_tilemap));
  cl_mod_add_func(mod, CL_BYTES("tile_update"), CL_BIND_FUNC(cyber_tile_update));
  cl_mod_add_func(mod, CL_BYTES("tile_map_size"), CL_BIND_FUNC(cyber_tile_map_size));
  cl_mod_add_func(mod, CL_BYTES("tile_tile_size"), CL_BIND_FUNC(cyber_tile_tile_size));
  cl_mod_add_func(mod, CL_BYTES("tile_map_prop"), CL_BIND_FUNC(cyber_tile_map_prop));
  cl_mod_add_func(mod, CL_BYTES("tile_map_prop_count"), CL_BIND_FUNC(cyber_tile_map_prop_count));
  cl_mod_add_func(mod, CL_BYTES("tile_map_prop_at"), CL_BIND_FUNC(cyber_tile_map_prop_at));
  cl_mod_add_func(mod, CL_BYTES("tile_draw"), CL_BIND_FUNC(cyber_tile_draw));
  cl_mod_add_func(mod, CL_BYTES("tile_draw_tint"), CL_BIND_FUNC(cyber_tile_draw_tint));
  cl_mod_add_func(mod, CL_BYTES("tile_draw_on_image"), CL_BIND_FUNC(cyber_tile_draw_on_image));
  cl_mod_add_func(mod, CL_BYTES("tilemap_image"), CL_BIND_FUNC(cyber_tilemap_image));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_count"), CL_BIND_FUNC(cyber_tile_layer_count));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_index"), CL_BIND_FUNC(cyber_tile_layer_index));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_name"), CL_BIND_FUNC(cyber_tile_layer_name));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_type"), CL_BIND_FUNC(cyber_tile_layer_type));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_size"), CL_BIND_FUNC(cyber_tile_layer_size));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_visible"), CL_BIND_FUNC(cyber_tile_layer_visible));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_prop"), CL_BIND_FUNC(cyber_tile_layer_prop));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_prop_count"), CL_BIND_FUNC(cyber_tile_layer_prop_count));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_prop_at"), CL_BIND_FUNC(cyber_tile_layer_prop_at));
  cl_mod_add_func(mod, CL_BYTES("tile_draw_layer"), CL_BIND_FUNC(cyber_tile_draw_layer));
  cl_mod_add_func(mod, CL_BYTES("tile_draw_layer_tint"), CL_BIND_FUNC(cyber_tile_draw_layer_tint));
  cl_mod_add_func(mod, CL_BYTES("tile_draw_layer_on_image"), CL_BIND_FUNC(cyber_tile_draw_layer_on_image));
  cl_mod_add_func(mod, CL_BYTES("tile_layer_image"), CL_BIND_FUNC(cyber_tile_layer_image));
  cl_mod_add_func(mod, CL_BYTES("tile_get_tile"), CL_BIND_FUNC(cyber_tile_get_tile));
  cl_mod_add_func(mod, CL_BYTES("tile_set_tile"), CL_BIND_FUNC(cyber_tile_set_tile));
  cl_mod_add_func(mod, CL_BYTES("tile_draw_tile"), CL_BIND_FUNC(cyber_tile_draw_tile));
  cl_mod_add_func(mod, CL_BYTES("tile_image"), CL_BIND_FUNC(cyber_tile_image));
  cl_mod_add_func(mod, CL_BYTES("tile_gid_prop"), CL_BIND_FUNC(cyber_tile_gid_prop));
  cl_mod_add_func(mod, CL_BYTES("tile_gid_prop_count"), CL_BIND_FUNC(cyber_tile_gid_prop_count));
  cl_mod_add_func(mod, CL_BYTES("tile_gid_prop_at"), CL_BIND_FUNC(cyber_tile_gid_prop_at));
  cl_mod_add_func(mod, CL_BYTES("tile_object_count"), CL_BIND_FUNC(cyber_tile_object_count));
  cl_mod_add_func(mod, CL_BYTES("tile_object"), CL_BIND_FUNC(cyber_tile_object));
  cl_mod_add_func(mod, CL_BYTES("tile_object_index"), CL_BIND_FUNC(cyber_tile_object_index));
  cl_mod_add_func(mod, CL_BYTES("tile_object_prop"), CL_BIND_FUNC(cyber_tile_object_prop));
  cl_mod_add_func(mod, CL_BYTES("tile_object_prop_count"), CL_BIND_FUNC(cyber_tile_object_prop_count));
  cl_mod_add_func(mod, CL_BYTES("tile_object_prop_at"), CL_BIND_FUNC(cyber_tile_object_prop_at));
  cl_mod_add_func(mod, CL_BYTES("current_time"), CL_BIND_FUNC(cyber_current_time));
  cl_mod_add_func(mod, CL_BYTES("delta_time"), CL_BIND_FUNC(cyber_delta_time));
  cl_mod_add_func(mod, CL_BYTES("random_int"), CL_BIND_FUNC(cyber_random_int));
  cl_mod_add_func(mod, CL_BYTES("random_seed_get"), CL_BIND_FUNC(cyber_random_seed_get));
  cl_mod_add_func(mod, CL_BYTES("random_seed_set"), CL_BIND_FUNC(cyber_random_seed_set));
    cl_mod_add_global(mod, CL_BYTES("__a0"), CL_BIND_GLOBAL(&g_a0));
    cl_mod_add_global(mod, CL_BYTES("__a1"), CL_BIND_GLOBAL(&g_a1));
    res->src = CL_BYTES(NULL0_CY);
    res->manage_src = false;
    return true;
  }
  return cl_default_loader(vmp, mod, uri, res);
}

// eval a small persisted snippet (a callback call). Errors are logged but
// not fatal - a cart is not required to define every callback, and an
// undeclared-function error is how a missing one shows up.
static void eval_snippet(const char* src) {
  CLBytes s = { .ptr = (char*)src, .len = strlen(src) };
  CLBytes uri = CL_BYTES("frame");
  CLEvalResult res;
  cl_vm_evalx(vm, uri, s, persist_cfg, &res);
}

// read a whole file from the cart
static char* read_file(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* text = malloc(size + 1);
  if (text == NULL) {
    fclose(file);
    return NULL;
  }
  size_t read = fread(text, 1, size, file);
  text[read] = '\0';
  fclose(file);
  return text;
}

int main() {
  vm = cl_vm_init();
  cl_vm_set_loader(vm, module_loader);
  persist_cfg = clDefaultEvalConfig();
  persist_cfg.persist_main = true;

  char* source = read_file("main.cy");
  if (source == NULL) {
    printf("cyber: no main.cy in cart\n");
    fflush(stdout);
    return 1;
  }

  CLBytes src = { .ptr = source, .len = strlen(source) };
  CLBytes uri = CL_BYTES("main");
  CLEvalResult eval;
  CLResultCode code = cl_vm_evalx(vm, uri, src, persist_cfg, &eval);
  free(source);
  if (code != CL_SUCCESS) {
    CLBytes summary = cl_vm_error_summary(vm);
    printf("cyber: %.*s\n", (int)summary.len, summary.ptr);
    fflush(stdout);
    return 1;
  }

  // load() is called here, since the host only calls _start on a wasi cart
  eval_snippet("load()");
  fflush(stdout);
  return 0;
}

void update() {
  eval_snippet("update()");
  fflush(stdout);
}

void unload() {
  eval_snippet("unload()");
  fflush(stdout);
}

// Mapped controller (keys and gamepad will trigger) callback for when a "button" is unpressed.
void buttonUp(GamepadButton button, unsigned int player) {
  g_a0 = (f32)button;
  g_a1 = (f32)player;
  eval_snippet("buttonUp(int(null0.__a0), int(null0.__a1))");
  fflush(stdout);
}

// Mapped controller (keys and gamepad will trigger) callback for when a "button" is pressed.
void buttonDown(GamepadButton button, unsigned int player) {
  g_a0 = (f32)button;
  g_a1 = (f32)player;
  eval_snippet("buttonDown(int(null0.__a0), int(null0.__a1))");
  fflush(stdout);
}

// Called when keys are unpressed.
void keyUp(Key key) {
  g_a0 = (f32)key;
  eval_snippet("keyUp(int(null0.__a0))");
  fflush(stdout);
}

// Called when keys are pressed.
void keyDown(Key key) {
  g_a0 = (f32)key;
  eval_snippet("keyDown(int(null0.__a0))");
  fflush(stdout);
}

// Called when mouse-button is pressed.
void mouseDown(unsigned int button) {
  g_a0 = (f32)button;
  eval_snippet("mouseDown(int(null0.__a0))");
  fflush(stdout);
}

// Called when mouse-button is released.
void mouseUp(unsigned int button) {
  g_a0 = (f32)button;
  eval_snippet("mouseUp(int(null0.__a0))");
  fflush(stdout);
}

// Called when mouse is moved.
void mouseMoved(float x, float y) {
  g_a0 = (f32)x;
  g_a1 = (f32)y;
  eval_snippet("mouseMoved(null0.__a0, null0.__a1)");
  fflush(stdout);
}
