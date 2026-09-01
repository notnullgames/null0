// GENERATED FILE - do not edit by hand. See tools/gen_cart_wren.js
//
// The wren cart-runtime: a wren VM with the null0 API bound to it. It runs
// main.wren from the cart, then calls the callbacks the cart defined.

#include "null0.h"
#include "wren.h"

static WrenVM* vm = NULL;

// the null0 module, baked in so carts do not have to ship it
static const char* NULL0_WREN =
  "// null0 - Wren bindings for the null0 fantasy console\n"
  "//\n"
  "// GENERATED FILE - do not edit by hand. See tools/gen_cart_wren.js\n"
  "//\n"
  "// This module is baked into the wren cart-runtime, so carts can just do:\n"
  "//\n"
  "// ```wren\n"
  "// import \"null0\" for Null0, BLUE, RED\n"
  "//\n"
  "// var load = Fn.new {\n"
  "//   Null0.clear(BLUE)\n"
  "//   Null0.draw_circle(100, 100, 50, RED)\n"
  "// }\n"
  "// ```\n"
  "//\n"
  "// Callbacks (load/update/unload/buttonUp/buttonDown/keyUp/keyDown/mouseUp/\n"
  "// mouseDown/mouseMoved) are module-level Fn variables, in main.wren.\n"
  "\n"
  "// An RGBA color.\n"
  "class Color {\n"
  "  construct new(r, g, b) {\n"
  "    _r = r\n"
  "    _g = g\n"
  "    _b = b\n"
  "    _a = 255\n"
  "  }\n"
  "\n"
  "  construct new(r, g, b, a) {\n"
  "    _r = r\n"
  "    _g = g\n"
  "    _b = b\n"
  "    _a = a\n"
  "  }\n"
  "\n"
  "  // Create a Color from a packed rgba number\n"
  "  static fromValue(v) { Color.new((v >> 24) & 0xff, (v >> 16) & 0xff, (v >> 8) & 0xff, v & 0xff) }\n"
  "\n"
  "  r { _r }\n"
  "  r=(v) { _r = v }\n"
  "  g { _g }\n"
  "  g=(v) { _g = v }\n"
  "  b { _b }\n"
  "  b=(v) { _b = v }\n"
  "  a { _a }\n"
  "  a=(v) { _a = v }\n"
  "\n"
  "  // The color as a single packed rgba number\n"
  "  value { ((_r & 0xff) << 24) | ((_g & 0xff) << 16) | ((_b & 0xff) << 8) | (_a & 0xff) }\n"
  "\n"
  "  ==(other) { other is Color && value == other.value }\n"
  "  !=(other) { !(this == other) }\n"
  "  toString { \"Color(%(_r), %(_g), %(_b), %(_a))\" }\n"
  "}\n"
  "\n"
  "// Sfx parameters.\n"
  "class SfxParams {\n"
  "  // Every member starts at 0 - fill them in with the setters, or\n"
  "  // start from Null0.sfx_generate(SFX_COIN) and tweak it\n"
  "  construct new() {\n"
  "    _randSeed = 0\n"
  "    _waveType = 0\n"
  "    _attackTime = 0\n"
  "    _sustainTime = 0\n"
  "    _sustainPunch = 0\n"
  "    _decayTime = 0\n"
  "    _startFrequency = 0\n"
  "    _minFrequency = 0\n"
  "    _slide = 0\n"
  "    _deltaSlide = 0\n"
  "    _vibratoDepth = 0\n"
  "    _vibratoSpeed = 0\n"
  "    _changeAmount = 0\n"
  "    _changeSpeed = 0\n"
  "    _squareDuty = 0\n"
  "    _dutySweep = 0\n"
  "    _repeatSpeed = 0\n"
  "    _phaserOffset = 0\n"
  "    _phaserSweep = 0\n"
  "    _lpfCutoff = 0\n"
  "    _lpfCutoffSweep = 0\n"
  "    _lpfResonance = 0\n"
  "    _hpfCutoff = 0\n"
  "    _hpfCutoffSweep = 0\n"
  "  }\n"
  "\n"
  "  // Create a SfxParams from a list of its members\n"
  "  static fromList(l) {\n"
  "    var value = SfxParams.new()\n"
  "    value.randSeed = l[0]\n"
  "    value.waveType = l[1]\n"
  "    value.attackTime = l[2]\n"
  "    value.sustainTime = l[3]\n"
  "    value.sustainPunch = l[4]\n"
  "    value.decayTime = l[5]\n"
  "    value.startFrequency = l[6]\n"
  "    value.minFrequency = l[7]\n"
  "    value.slide = l[8]\n"
  "    value.deltaSlide = l[9]\n"
  "    value.vibratoDepth = l[10]\n"
  "    value.vibratoSpeed = l[11]\n"
  "    value.changeAmount = l[12]\n"
  "    value.changeSpeed = l[13]\n"
  "    value.squareDuty = l[14]\n"
  "    value.dutySweep = l[15]\n"
  "    value.repeatSpeed = l[16]\n"
  "    value.phaserOffset = l[17]\n"
  "    value.phaserSweep = l[18]\n"
  "    value.lpfCutoff = l[19]\n"
  "    value.lpfCutoffSweep = l[20]\n"
  "    value.lpfResonance = l[21]\n"
  "    value.hpfCutoff = l[22]\n"
  "    value.hpfCutoffSweep = l[23]\n"
  "    return value\n"
  "  }\n"
  "\n"
  "  randSeed { _randSeed }\n"
  "  randSeed=(v) { _randSeed = v }\n"
  "  waveType { _waveType }\n"
  "  waveType=(v) { _waveType = v }\n"
  "  attackTime { _attackTime }\n"
  "  attackTime=(v) { _attackTime = v }\n"
  "  sustainTime { _sustainTime }\n"
  "  sustainTime=(v) { _sustainTime = v }\n"
  "  sustainPunch { _sustainPunch }\n"
  "  sustainPunch=(v) { _sustainPunch = v }\n"
  "  decayTime { _decayTime }\n"
  "  decayTime=(v) { _decayTime = v }\n"
  "  startFrequency { _startFrequency }\n"
  "  startFrequency=(v) { _startFrequency = v }\n"
  "  minFrequency { _minFrequency }\n"
  "  minFrequency=(v) { _minFrequency = v }\n"
  "  slide { _slide }\n"
  "  slide=(v) { _slide = v }\n"
  "  deltaSlide { _deltaSlide }\n"
  "  deltaSlide=(v) { _deltaSlide = v }\n"
  "  vibratoDepth { _vibratoDepth }\n"
  "  vibratoDepth=(v) { _vibratoDepth = v }\n"
  "  vibratoSpeed { _vibratoSpeed }\n"
  "  vibratoSpeed=(v) { _vibratoSpeed = v }\n"
  "  changeAmount { _changeAmount }\n"
  "  changeAmount=(v) { _changeAmount = v }\n"
  "  changeSpeed { _changeSpeed }\n"
  "  changeSpeed=(v) { _changeSpeed = v }\n"
  "  squareDuty { _squareDuty }\n"
  "  squareDuty=(v) { _squareDuty = v }\n"
  "  dutySweep { _dutySweep }\n"
  "  dutySweep=(v) { _dutySweep = v }\n"
  "  repeatSpeed { _repeatSpeed }\n"
  "  repeatSpeed=(v) { _repeatSpeed = v }\n"
  "  phaserOffset { _phaserOffset }\n"
  "  phaserOffset=(v) { _phaserOffset = v }\n"
  "  phaserSweep { _phaserSweep }\n"
  "  phaserSweep=(v) { _phaserSweep = v }\n"
  "  lpfCutoff { _lpfCutoff }\n"
  "  lpfCutoff=(v) { _lpfCutoff = v }\n"
  "  lpfCutoffSweep { _lpfCutoffSweep }\n"
  "  lpfCutoffSweep=(v) { _lpfCutoffSweep = v }\n"
  "  lpfResonance { _lpfResonance }\n"
  "  lpfResonance=(v) { _lpfResonance = v }\n"
  "  hpfCutoff { _hpfCutoff }\n"
  "  hpfCutoff=(v) { _hpfCutoff = v }\n"
  "  hpfCutoffSweep { _hpfCutoffSweep }\n"
  "  hpfCutoffSweep=(v) { _hpfCutoffSweep = v }\n"
  "\n"
  "  // The members, in the order the null0 API wants them\n"
  "  toList { [_randSeed, _waveType, _attackTime, _sustainTime, _sustainPunch, _decayTime, _startFrequency, _minFrequency, _slide, _deltaSlide, _vibratoDepth, _vibratoSpeed, _changeAmount, _changeSpeed, _squareDuty, _dutySweep, _repeatSpeed, _phaserOffset, _phaserSweep, _lpfCutoff, _lpfCutoffSweep, _lpfResonance, _hpfCutoff, _hpfCutoffSweep] }\n"
  "\n"
  "  toString { \"SfxParams(%(_randSeed), %(_waveType), %(_attackTime), %(_sustainTime), %(_sustainPunch), %(_decayTime), %(_startFrequency), %(_minFrequency), %(_slide), %(_deltaSlide), %(_vibratoDepth), %(_vibratoSpeed), %(_changeAmount), %(_changeSpeed), %(_squareDuty), %(_dutySweep), %(_repeatSpeed), %(_phaserOffset), %(_phaserSweep), %(_lpfCutoff), %(_lpfCutoffSweep), %(_lpfResonance), %(_hpfCutoff), %(_hpfCutoffSweep))\" }\n"
  "}\n"
  "\n"
  "// The 2D size of something (width/height.)\n"
  "class Dimensions {\n"
  "  construct new(width, height) {\n"
  "    _width = width\n"
  "    _height = height\n"
  "  }\n"
  "\n"
  "  // Create a Dimensions from a list of its members\n"
  "  static fromList(l) { Dimensions.new(l[0], l[1]) }\n"
  "\n"
  "  width { _width }\n"
  "  width=(v) { _width = v }\n"
  "  height { _height }\n"
  "  height=(v) { _height = v }\n"
  "\n"
  "  // The members, in the order the null0 API wants them\n"
  "  toList { [_width, _height] }\n"
  "\n"
  "  toString { \"Dimensions(%(_width), %(_height))\" }\n"
  "}\n"
  "\n"
  "// The 2D position of something (x/y.)\n"
  "class Vector {\n"
  "  construct new(x, y) {\n"
  "    _x = x\n"
  "    _y = y\n"
  "  }\n"
  "\n"
  "  // Create a Vector from a list of its members\n"
  "  static fromList(l) { Vector.new(l[0], l[1]) }\n"
  "\n"
  "  x { _x }\n"
  "  x=(v) { _x = v }\n"
  "  y { _y }\n"
  "  y=(v) { _y = v }\n"
  "\n"
  "  // The members, in the order the null0 API wants them\n"
  "  toList { [_x, _y] }\n"
  "\n"
  "  toString { \"Vector(%(_x), %(_y))\" }\n"
  "}\n"
  "\n"
  "// The 2D position + size of something (x/y/w/h.)\n"
  "class Rectangle {\n"
  "  construct new(x, y, width, height) {\n"
  "    _x = x\n"
  "    _y = y\n"
  "    _width = width\n"
  "    _height = height\n"
  "  }\n"
  "\n"
  "  // Create a Rectangle from a list of its members\n"
  "  static fromList(l) { Rectangle.new(l[0], l[1], l[2], l[3]) }\n"
  "\n"
  "  x { _x }\n"
  "  x=(v) { _x = v }\n"
  "  y { _y }\n"
  "  y=(v) { _y = v }\n"
  "  width { _width }\n"
  "  width=(v) { _width = v }\n"
  "  height { _height }\n"
  "  height=(v) { _height = v }\n"
  "\n"
  "  // The members, in the order the null0 API wants them\n"
  "  toList { [_x, _y, _width, _height] }\n"
  "\n"
  "  toString { \"Rectangle(%(_x), %(_y), %(_width), %(_height))\" }\n"
  "}\n"
  "\n"
  "// A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`.\n"
  "class TilemapProp {\n"
  "  construct new(name, type, integer, number, text) {\n"
  "    _name = name\n"
  "    _type = type\n"
  "    _integer = integer\n"
  "    _number = number\n"
  "    _text = text\n"
  "  }\n"
  "\n"
  "  // Create a TilemapProp from a list of its members\n"
  "  static fromList(l) { TilemapProp.new(l[0], l[1], l[2], l[3], l[4]) }\n"
  "\n"
  "  name { _name }\n"
  "  name=(v) { _name = v }\n"
  "  type { _type }\n"
  "  type=(v) { _type = v }\n"
  "  integer { _integer }\n"
  "  integer=(v) { _integer = v }\n"
  "  number { _number }\n"
  "  number=(v) { _number = v }\n"
  "  text { _text }\n"
  "  text=(v) { _text = v }\n"
  "\n"
  "  // The members, in the order the null0 API wants them\n"
  "  toList { [_name, _type, _integer, _number, _text] }\n"
  "\n"
  "  toString { \"TilemapProp(%(_name), %(_type), %(_integer), %(_number), %(_text))\" }\n"
  "}\n"
  "\n"
  "// An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it.\n"
  "class TilemapObject {\n"
  "  construct new(id, name, type, gid, x, y, width, height, rotation, visible) {\n"
  "    _id = id\n"
  "    _name = name\n"
  "    _type = type\n"
  "    _gid = gid\n"
  "    _x = x\n"
  "    _y = y\n"
  "    _width = width\n"
  "    _height = height\n"
  "    _rotation = rotation\n"
  "    _visible = visible\n"
  "  }\n"
  "\n"
  "  // Create a TilemapObject from a list of its members\n"
  "  static fromList(l) { TilemapObject.new(l[0], l[1], l[2], l[3], l[4], l[5], l[6], l[7], l[8], l[9]) }\n"
  "\n"
  "  id { _id }\n"
  "  id=(v) { _id = v }\n"
  "  name { _name }\n"
  "  name=(v) { _name = v }\n"
  "  type { _type }\n"
  "  type=(v) { _type = v }\n"
  "  gid { _gid }\n"
  "  gid=(v) { _gid = v }\n"
  "  x { _x }\n"
  "  x=(v) { _x = v }\n"
  "  y { _y }\n"
  "  y=(v) { _y = v }\n"
  "  width { _width }\n"
  "  width=(v) { _width = v }\n"
  "  height { _height }\n"
  "  height=(v) { _height = v }\n"
  "  rotation { _rotation }\n"
  "  rotation=(v) { _rotation = v }\n"
  "  visible { _visible }\n"
  "  visible=(v) { _visible = v }\n"
  "\n"
  "  // The members, in the order the null0 API wants them\n"
  "  toList { [_id, _name, _type, _gid, _x, _y, _width, _height, _rotation, _visible] }\n"
  "\n"
  "  toString { \"TilemapObject(%(_id), %(_name), %(_type), %(_gid), %(_x), %(_y), %(_width), %(_height), %(_rotation), %(_visible))\" }\n"
  "}\n"
  "\n"
  "// The null0 API\n"
  "class Null0 {\n"
  "\n"
  "  // COLORS\n"
  "\n"
  "  // Tint a color with another color.\n"
  "  foreign static color_tint_(a0, a1)\n"
  "  static color_tint(color, tint) { Color.fromValue(color_tint_(color.value, tint.value)) }\n"
  "\n"
  "  // Fade a color.\n"
  "  foreign static color_fade_(a0, a1)\n"
  "  static color_fade(color, alpha) { Color.fromValue(color_fade_(color.value, alpha)) }\n"
  "\n"
  "  // Change the brightness of a color.\n"
  "  foreign static color_brightness_(a0, a1)\n"
  "  static color_brightness(color, factor) { Color.fromValue(color_brightness_(color.value, factor)) }\n"
  "\n"
  "  // Invert a color.\n"
  "  foreign static color_invert_(a0)\n"
  "  static color_invert(color) { Color.fromValue(color_invert_(color.value)) }\n"
  "\n"
  "  // Blend 2 colors together.\n"
  "  foreign static color_alpha_blend_(a0, a1)\n"
  "  static color_alpha_blend(dst, src) { Color.fromValue(color_alpha_blend_(dst.value, src.value)) }\n"
  "\n"
  "  // Change contrast of a color.\n"
  "  foreign static color_contrast_(a0, a1)\n"
  "  static color_contrast(color, contrast) { Color.fromValue(color_contrast_(color.value, contrast)) }\n"
  "\n"
  "  // Interpolate colors.\n"
  "  foreign static color_bilinear_interpolate_(a0, a1, a2, a3, a4, a5)\n"
  "  static color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY) { Color.fromValue(color_bilinear_interpolate_(color00.value, color01.value, color10.value, color11.value, coordinateX, coordinateY)) }\n"
  "\n"
  "  // GRAPHICS\n"
  "\n"
  "  // Create a new blank image.\n"
  "  foreign static new_image_(a0, a1, a2)\n"
  "  static new_image(width, height, color) { new_image_(width, height, color.value) }\n"
  "\n"
  "  // Copy an image to a new image.\n"
  "  foreign static image_copy_(a0)\n"
  "  static image_copy(image) { image_copy_(image) }\n"
  "\n"
  "  // Create an image from a region of another image.\n"
  "  foreign static image_subimage_(a0, a1, a2, a3, a4)\n"
  "  static image_subimage(image, x, y, width, height) { image_subimage_(image, x, y, width, height) }\n"
  "\n"
  "  // Clear the screen.\n"
  "  foreign static clear_(a0)\n"
  "  static clear(color) { clear_(color.value) }\n"
  "\n"
  "  // Draw a single pixel on the screen.\n"
  "  foreign static draw_point_(a0, a1, a2)\n"
  "  static draw_point(x, y, color) { draw_point_(x, y, color.value) }\n"
  "\n"
  "  // Draw a line on the screen.\n"
  "  foreign static draw_line_(a0, a1, a2, a3, a4)\n"
  "  static draw_line(startPosX, startPosY, endPosX, endPosY, color) { draw_line_(startPosX, startPosY, endPosX, endPosY, color.value) }\n"
  "\n"
  "  // Draw a filled rectangle on the screen.\n"
  "  foreign static draw_rectangle_(a0, a1, a2, a3, a4)\n"
  "  static draw_rectangle(posX, posY, width, height, color) { draw_rectangle_(posX, posY, width, height, color.value) }\n"
  "\n"
  "  // Draw a filled triangle on the screen.\n"
  "  foreign static draw_triangle_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_triangle(x1, y1, x2, y2, x3, y3, color) { draw_triangle_(x1, y1, x2, y2, x3, y3, color.value) }\n"
  "\n"
  "  // Draw a filled ellipse on the screen.\n"
  "  foreign static draw_ellipse_(a0, a1, a2, a3, a4)\n"
  "  static draw_ellipse(centerX, centerY, radiusX, radiusY, color) { draw_ellipse_(centerX, centerY, radiusX, radiusY, color.value) }\n"
  "\n"
  "  // Draw a filled circle on the screen.\n"
  "  foreign static draw_circle_(a0, a1, a2, a3)\n"
  "  static draw_circle(centerX, centerY, radius, color) { draw_circle_(centerX, centerY, radius, color.value) }\n"
  "\n"
  "  // Draw a filled polygon on the screen.\n"
  "  foreign static draw_polygon_(a0, a1)\n"
  "  static draw_polygon(points, color) {\n"
  "    var flat_points = []\n"
  "    for (v in points) {\n"
  "      flat_points.add(v.x)\n"
  "      flat_points.add(v.y)\n"
  "    }\n"
  "    return draw_polygon_(flat_points, color.value)\n"
  "  }\n"
  "\n"
  "  // Draw a filled arc on the screen.\n"
  "  foreign static draw_arc_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color) { draw_arc_(centerX, centerY, radius, startAngle, endAngle, segments, color.value) }\n"
  "\n"
  "  // Draw a filled round-rectangle on the screen.\n"
  "  foreign static draw_rectangle_rounded_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_rectangle_rounded(x, y, width, height, cornerRadius, color) { draw_rectangle_rounded_(x, y, width, height, cornerRadius, color.value) }\n"
  "\n"
  "  // Draw an image on the screen.\n"
  "  foreign static draw_image_(a0, a1, a2)\n"
  "  static draw_image(src, posX, posY) { draw_image_(src, posX, posY) }\n"
  "\n"
  "  // Draw a tinted image on the screen.\n"
  "  foreign static draw_image_tint_(a0, a1, a2, a3)\n"
  "  static draw_image_tint(src, posX, posY, tint) { draw_image_tint_(src, posX, posY, tint.value) }\n"
  "\n"
  "  // Draw an image, rotated, on the screen.\n"
  "  foreign static draw_image_rotated_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter) { draw_image_rotated_(src, posX, posY, degrees, offsetX, offsetY, filter) }\n"
  "\n"
  "  // Draw an image, flipped, on the screen.\n"
  "  foreign static draw_image_flipped_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) { draw_image_flipped_(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) }\n"
  "\n"
  "  // Draw an image, scaled, on the screen.\n"
  "  foreign static draw_image_scaled_(a0, a1, a2, a3, a4, a5, a6, a7)\n"
  "  static draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) { draw_image_scaled_(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) }\n"
  "\n"
  "  // Draw some text on the screen.\n"
  "  foreign static draw_text_(a0, a1, a2, a3, a4)\n"
  "  static draw_text(font, text, posX, posY, color) { draw_text_(font, text, posX, posY, color.value) }\n"
  "\n"
  "  // Save an image to persistant storage.\n"
  "  foreign static save_image_(a0, a1)\n"
  "  static save_image(image, filename) { save_image_(image, filename) }\n"
  "\n"
  "  // Load an image from a file in cart.\n"
  "  foreign static load_image_(a0)\n"
  "  static load_image(filename) { load_image_(filename) }\n"
  "\n"
  "  // Resize an image, return copy.\n"
  "  foreign static image_resize_(a0, a1, a2, a3)\n"
  "  static image_resize(image, newWidth, newHeight, filter) { image_resize_(image, newWidth, newHeight, filter) }\n"
  "\n"
  "  // Scale an image, return copy.\n"
  "  foreign static image_scale_(a0, a1, a2, a3)\n"
  "  static image_scale(image, scaleX, scaleY, filter) { image_scale_(image, scaleX, scaleY, filter) }\n"
  "\n"
  "  // Replace a color in an image, in-place.\n"
  "  foreign static image_color_replace_(a0, a1, a2)\n"
  "  static image_color_replace(image, color, replace) { image_color_replace_(image, color.value, replace.value) }\n"
  "\n"
  "  // Tint a color in an image, in-place.\n"
  "  foreign static image_color_tint_(a0, a1)\n"
  "  static image_color_tint(image, color) { image_color_tint_(image, color.value) }\n"
  "\n"
  "  // Fade a color in an image, in-place.\n"
  "  foreign static image_color_fade_(a0, a1)\n"
  "  static image_color_fade(image, alpha) { image_color_fade_(image, alpha) }\n"
  "\n"
  "  // Copy a font to a new font.\n"
  "  foreign static font_copy_(a0)\n"
  "  static font_copy(font) { font_copy_(font) }\n"
  "\n"
  "  // Scale a font, return a new font.\n"
  "  foreign static font_scale_(a0, a1, a2, a3)\n"
  "  static font_scale(font, scaleX, scaleY, filter) { font_scale_(font, scaleX, scaleY, filter) }\n"
  "\n"
  "  // Load a BMF font from a file in cart.\n"
  "  foreign static load_font_bmf_(a0, a1)\n"
  "  static load_font_bmf(filename, characters) { load_font_bmf_(filename, characters) }\n"
  "\n"
  "  // Load a BMF font from an image.\n"
  "  foreign static load_font_bmf_from_image_(a0, a1)\n"
  "  static load_font_bmf_from_image(image, characters) { load_font_bmf_from_image_(image, characters) }\n"
  "\n"
  "  // Measure the size of some text.\n"
  "  foreign static measure_text_(a0, a1, a2)\n"
  "  static measure_text(font, text, textLength) { Dimensions.fromList(measure_text_(font, text, textLength)) }\n"
  "\n"
  "  // Meaure an image (use 0 for screen).\n"
  "  foreign static measure_image_(a0)\n"
  "  static measure_image(image) { Dimensions.fromList(measure_image_(image)) }\n"
  "\n"
  "  // Load a TTY font from a file in cart.\n"
  "  foreign static load_font_tty_(a0, a1, a2, a3)\n"
  "  static load_font_tty(filename, glyphWidth, glyphHeight, characters) { load_font_tty_(filename, glyphWidth, glyphHeight, characters) }\n"
  "\n"
  "  // Load a TTY font from an image.\n"
  "  foreign static load_font_tty_from_image_(a0, a1, a2, a3)\n"
  "  static load_font_tty_from_image(image, glyphWidth, glyphHeight, characters) { load_font_tty_from_image_(image, glyphWidth, glyphHeight, characters) }\n"
  "\n"
  "  // Load a TTF font from a file in cart.\n"
  "  foreign static load_font_ttf_(a0, a1)\n"
  "  static load_font_ttf(filename, fontSize) { load_font_ttf_(filename, fontSize) }\n"
  "\n"
  "  // Invert the colors in an image, in-place.\n"
  "  foreign static image_color_invert_(a0)\n"
  "  static image_color_invert(image) { image_color_invert_(image) }\n"
  "\n"
  "  // Calculate a rectangle representing the available alpha border in an image.\n"
  "  foreign static image_alpha_border_(a0, a1)\n"
  "  static image_alpha_border(image, threshold) { Rectangle.fromList(image_alpha_border_(image, threshold)) }\n"
  "\n"
  "  // Crop an image, in-place.\n"
  "  foreign static image_crop_(a0, a1, a2, a3, a4)\n"
  "  static image_crop(image, x, y, width, height) { image_crop_(image, x, y, width, height) }\n"
  "\n"
  "  // Crop an image based on the alpha border, in-place.\n"
  "  foreign static image_alpha_crop_(a0, a1)\n"
  "  static image_alpha_crop(image, threshold) { image_alpha_crop_(image, threshold) }\n"
  "\n"
  "  // Adjust the brightness of an image, in-place.\n"
  "  foreign static image_color_brightness_(a0, a1)\n"
  "  static image_color_brightness(image, factor) { image_color_brightness_(image, factor) }\n"
  "\n"
  "  // Flip an image, in-place.\n"
  "  foreign static image_flip_(a0, a1, a2)\n"
  "  static image_flip(image, horizontal, vertical) { image_flip_(image, horizontal, vertical) }\n"
  "\n"
  "  // Change the contrast of an image, in-place.\n"
  "  foreign static image_color_contrast_(a0, a1)\n"
  "  static image_color_contrast(image, contrast) { image_color_contrast_(image, contrast) }\n"
  "\n"
  "  // Use an image as an alpha-mask on another image.\n"
  "  foreign static image_alpha_mask_(a0, a1, a2, a3)\n"
  "  static image_alpha_mask(image, alphaMask, posX, posY) { image_alpha_mask_(image, alphaMask, posX, posY) }\n"
  "\n"
  "  // Create a new image, rotating another image.\n"
  "  foreign static image_rotate_(a0, a1, a2)\n"
  "  static image_rotate(image, degrees, filter) { image_rotate_(image, degrees, filter) }\n"
  "\n"
  "  // Create a new image of a gradient.\n"
  "  foreign static image_gradient_(a0, a1, a2, a3, a4, a5)\n"
  "  static image_gradient(width, height, topLeft, topRight, bottomLeft, bottomRight) { image_gradient_(width, height, topLeft.value, topRight.value, bottomLeft.value, bottomRight.value) }\n"
  "\n"
  "  // Unload an image.\n"
  "  foreign static unload_image_(a0)\n"
  "  static unload_image(image) { unload_image_(image) }\n"
  "\n"
  "  // Unload a font.\n"
  "  foreign static unload_font_(a0)\n"
  "  static unload_font(font) { unload_font_(font) }\n"
  "\n"
  "  // Clear an image.\n"
  "  foreign static clear_image_(a0, a1)\n"
  "  static clear_image(destination, color) { clear_image_(destination, color.value) }\n"
  "\n"
  "  // Draw a single pixel on an image.\n"
  "  foreign static draw_point_on_image_(a0, a1, a2, a3)\n"
  "  static draw_point_on_image(destination, x, y, color) { draw_point_on_image_(destination, x, y, color.value) }\n"
  "\n"
  "  // Draw a line on an image.\n"
  "  foreign static draw_line_on_image_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color) { draw_line_on_image_(destination, startPosX, startPosY, endPosX, endPosY, color.value) }\n"
  "\n"
  "  // Draw a filled rectangle on an image.\n"
  "  foreign static draw_rectangle_on_image_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_rectangle_on_image(destination, posX, posY, width, height, color) { draw_rectangle_on_image_(destination, posX, posY, width, height, color.value) }\n"
  "\n"
  "  // Draw a filled triangle on an image.\n"
  "  foreign static draw_triangle_on_image_(a0, a1, a2, a3, a4, a5, a6, a7)\n"
  "  static draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color) { draw_triangle_on_image_(destination, x1, y1, x2, y2, x3, y3, color.value) }\n"
  "\n"
  "  // Draw a filled ellipse on an image.\n"
  "  foreign static draw_ellipse_on_image_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color) { draw_ellipse_on_image_(destination, centerX, centerY, radiusX, radiusY, color.value) }\n"
  "\n"
  "  // Draw a circle on an image.\n"
  "  foreign static draw_circle_on_image_(a0, a1, a2, a3, a4)\n"
  "  static draw_circle_on_image(destination, centerX, centerY, radius, color) { draw_circle_on_image_(destination, centerX, centerY, radius, color.value) }\n"
  "\n"
  "  // Draw a filled polygon on an image.\n"
  "  foreign static draw_polygon_on_image_(a0, a1, a2)\n"
  "  static draw_polygon_on_image(destination, points, color) {\n"
  "    var flat_points = []\n"
  "    for (v in points) {\n"
  "      flat_points.add(v.x)\n"
  "      flat_points.add(v.y)\n"
  "    }\n"
  "    return draw_polygon_on_image_(destination, flat_points, color.value)\n"
  "  }\n"
  "\n"
  "  // Draw a filled round-rectangle on an image.\n"
  "  foreign static draw_rectangle_rounded_on_image_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color) { draw_rectangle_rounded_on_image_(destination, x, y, width, height, cornerRadius, color.value) }\n"
  "\n"
  "  // Draw an image on an image.\n"
  "  foreign static draw_image_on_image_(a0, a1, a2, a3)\n"
  "  static draw_image_on_image(destination, src, posX, posY) { draw_image_on_image_(destination, src, posX, posY) }\n"
  "\n"
  "  // Draw a tinted image on an image.\n"
  "  foreign static draw_image_tint_on_image_(a0, a1, a2, a3, a4)\n"
  "  static draw_image_tint_on_image(destination, src, posX, posY, tint) { draw_image_tint_on_image_(destination, src, posX, posY, tint.value) }\n"
  "\n"
  "  // Draw an image, rotated, on an image.\n"
  "  foreign static draw_image_rotated_on_image_(a0, a1, a2, a3, a4, a5, a6, a7)\n"
  "  static draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter) { draw_image_rotated_on_image_(destination, src, posX, posY, degrees, offsetX, offsetY, filter) }\n"
  "\n"
  "  // Draw an image, flipped, on an image.\n"
  "  foreign static draw_image_flipped_on_image_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) { draw_image_flipped_on_image_(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) }\n"
  "\n"
  "  // Draw an image, scaled, on an image.\n"
  "  foreign static draw_image_scaled_on_image_(a0, a1, a2, a3, a4, a5, a6, a7, a8)\n"
  "  static draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) { draw_image_scaled_on_image_(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) }\n"
  "\n"
  "  // Draw some text on an image.\n"
  "  foreign static draw_text_on_image_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_text_on_image(destination, font, text, posX, posY, color) { draw_text_on_image_(destination, font, text, posX, posY, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) rectangle on the screen.\n"
  "  foreign static draw_rectangle_outline_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_rectangle_outline(posX, posY, width, height, thickness, color) { draw_rectangle_outline_(posX, posY, width, height, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) triangle on the screen.\n"
  "  foreign static draw_triangle_outline_(a0, a1, a2, a3, a4, a5, a6, a7)\n"
  "  static draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, color) { draw_triangle_outline_(x1, y1, x2, y2, x3, y3, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) ellipse on the screen.\n"
  "  foreign static draw_ellipse_outline_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, color) { draw_ellipse_outline_(centerX, centerY, radiusX, radiusY, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) circle on the screen.\n"
  "  foreign static draw_circle_outline_(a0, a1, a2, a3, a4)\n"
  "  static draw_circle_outline(centerX, centerY, radius, thickness, color) { draw_circle_outline_(centerX, centerY, radius, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) polygon on the screen.\n"
  "  foreign static draw_polygon_outline_(a0, a1, a2)\n"
  "  static draw_polygon_outline(points, thickness, color) {\n"
  "    var flat_points = []\n"
  "    for (v in points) {\n"
  "      flat_points.add(v.x)\n"
  "      flat_points.add(v.y)\n"
  "    }\n"
  "    return draw_polygon_outline_(flat_points, thickness, color.value)\n"
  "  }\n"
  "\n"
  "  // Draw a outlined (with thickness) arc on the screen.\n"
  "  foreign static draw_arc_outline_(a0, a1, a2, a3, a4, a5, a6, a7)\n"
  "  static draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color) { draw_arc_outline_(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) round-rectangle on the screen.\n"
  "  foreign static draw_rectangle_rounded_outline_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, color) { draw_rectangle_rounded_outline_(x, y, width, height, cornerRadius, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) rectangle on an image.\n"
  "  foreign static draw_rectangle_outline_on_image_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, color) { draw_rectangle_outline_on_image_(destination, posX, posY, width, height, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) triangle on an image.\n"
  "  foreign static draw_triangle_outline_on_image_(a0, a1, a2, a3, a4, a5, a6, a7, a8)\n"
  "  static draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, color) { draw_triangle_outline_on_image_(destination, x1, y1, x2, y2, x3, y3, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) ellipse on an image.\n"
  "  foreign static draw_ellipse_outline_on_image_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, color) { draw_ellipse_outline_on_image_(destination, centerX, centerY, radiusX, radiusY, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) circle on an image.\n"
  "  foreign static draw_circle_outline_on_image_(a0, a1, a2, a3, a4, a5)\n"
  "  static draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, color) { draw_circle_outline_on_image_(destination, centerX, centerY, radius, thickness, color.value) }\n"
  "\n"
  "  // Draw a outlined (with thickness) polygon on an image.\n"
  "  foreign static draw_polygon_outline_on_image_(a0, a1, a2, a3)\n"
  "  static draw_polygon_outline_on_image(destination, points, thickness, color) {\n"
  "    var flat_points = []\n"
  "    for (v in points) {\n"
  "      flat_points.add(v.x)\n"
  "      flat_points.add(v.y)\n"
  "    }\n"
  "    return draw_polygon_outline_on_image_(destination, flat_points, thickness, color.value)\n"
  "  }\n"
  "\n"
  "  // Draw a outlined (with thickness) round-rectangle on an image.\n"
  "  foreign static draw_rectangle_rounded_outline_on_image_(a0, a1, a2, a3, a4, a5, a6, a7)\n"
  "  static draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, color) { draw_rectangle_rounded_outline_on_image_(destination, x, y, width, height, cornerRadius, thickness, color.value) }\n"
  "\n"
  "  // GUI\n"
  "\n"
  "  // Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.\n"
  "  foreign static gui_begin_window_(a0, a1)\n"
  "  static gui_begin_window(title, rect) { gui_begin_window_(title, rect.toList) }\n"
  "\n"
  "  // End the current GUI window.\n"
  "  foreign static gui_end_window_\n"
  "  static gui_end_window { gui_end_window_ }\n"
  "\n"
  "  // A button. Returns true when it is clicked.\n"
  "  foreign static gui_button_(a0)\n"
  "  static gui_button(label) { gui_button_(label) }\n"
  "\n"
  "  // A static text label.\n"
  "  foreign static gui_label_(a0)\n"
  "  static gui_label(text) { gui_label_(text) }\n"
  "\n"
  "  // A block of wrapping text.\n"
  "  foreign static gui_text_(a0)\n"
  "  static gui_text(text) { gui_text_(text) }\n"
  "\n"
  "  // A checkbox. Returns the (possibly changed) state.\n"
  "  foreign static gui_checkbox_(a0, a1)\n"
  "  static gui_checkbox(label, state) { gui_checkbox_(label, state) }\n"
  "\n"
  "  // A slider. Returns the (possibly changed) value.\n"
  "  foreign static gui_slider_(a0, a1, a2)\n"
  "  static gui_slider(value, low, high) { gui_slider_(value, low, high) }\n"
  "\n"
  "  // Set the current layout row - the column widths (negative for flexible), and the row height.\n"
  "  foreign static gui_layout_row_(a0, a1)\n"
  "  static gui_layout_row(widths, height) { gui_layout_row_(widths, height) }\n"
  "\n"
  "  // Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.\n"
  "  foreign static gui_end_\n"
  "  static gui_end { gui_end_ }\n"
  "\n"
  "  // Draw the GUI to an image (0 is the screen).\n"
  "  foreign static gui_draw_(a0)\n"
  "  static gui_draw(dst) { gui_draw_(dst) }\n"
  "\n"
  "  // INPUT\n"
  "\n"
  "  // Has the key been pressed? (tracks unpress/read correctly.)\n"
  "  foreign static key_pressed_(a0)\n"
  "  static key_pressed(key) { key_pressed_(key) }\n"
  "\n"
  "  // Is the key currently down?\n"
  "  foreign static key_down_(a0)\n"
  "  static key_down(key) { key_down_(key) }\n"
  "\n"
  "  // Has the key been released? (tracks press/read correctly.)\n"
  "  foreign static key_released_(a0)\n"
  "  static key_released(key) { key_released_(key) }\n"
  "\n"
  "  // Is the key currently up?\n"
  "  foreign static key_up_(a0)\n"
  "  static key_up(key) { key_up_(key) }\n"
  "\n"
  "  // Has the button been pressed? (tracks unpress/read correctly.)\n"
  "  foreign static gamepad_button_pressed_(a0, a1)\n"
  "  static gamepad_button_pressed(gamepad, button) { gamepad_button_pressed_(gamepad, button) }\n"
  "\n"
  "  // Is the button currently down?\n"
  "  foreign static gamepad_button_down_(a0, a1)\n"
  "  static gamepad_button_down(gamepad, button) { gamepad_button_down_(gamepad, button) }\n"
  "\n"
  "  // Has the button been released? (tracks press/read correctly.)\n"
  "  foreign static gamepad_button_released_(a0, a1)\n"
  "  static gamepad_button_released(gamepad, button) { gamepad_button_released_(gamepad, button) }\n"
  "\n"
  "  // Get current position of mouse.\n"
  "  foreign static mouse_position_\n"
  "  static mouse_position { Vector.fromList(mouse_position_) }\n"
  "\n"
  "  // Has the button been pressed? (tracks unpress/read correctly.)\n"
  "  foreign static mouse_button_pressed_(a0)\n"
  "  static mouse_button_pressed(button) { mouse_button_pressed_(button) }\n"
  "\n"
  "  // Is the button currently down?\n"
  "  foreign static mouse_button_down_(a0)\n"
  "  static mouse_button_down(button) { mouse_button_down_(button) }\n"
  "\n"
  "  // Has the button been released? (tracks press/read correctly.)\n"
  "  foreign static mouse_button_released_(a0)\n"
  "  static mouse_button_released(button) { mouse_button_released_(button) }\n"
  "\n"
  "  // Is the button currently up?\n"
  "  foreign static mouse_button_up_(a0)\n"
  "  static mouse_button_up(button) { mouse_button_up_(button) }\n"
  "\n"
  "  // SOUND\n"
  "\n"
  "  // Load a sound from a file in cart.\n"
  "  foreign static load_sound_(a0)\n"
  "  static load_sound(filename) { load_sound_(filename) }\n"
  "\n"
  "  // Play a sound.\n"
  "  foreign static play_sound_(a0, a1)\n"
  "  static play_sound(sound, loop) { play_sound_(sound, loop) }\n"
  "\n"
  "  // Stop a sound.\n"
  "  foreign static stop_sound_(a0)\n"
  "  static stop_sound(sound) { stop_sound_(sound) }\n"
  "\n"
  "  // Unload a sound.\n"
  "  foreign static unload_sound_(a0)\n"
  "  static unload_sound(sound) { unload_sound_(sound) }\n"
  "\n"
  "  // Speak some text and return a sound. Set things to 0 for defaults.\n"
  "  foreign static tts_sound_(a0, a1, a2, a3, a4, a5, a6)\n"
  "  static tts_sound(text, phonetic, pitch, speed, throat, mouth, sing) { tts_sound_(text, phonetic, pitch, speed, throat, mouth, sing) }\n"
  "\n"
  "  // Create Sfx sound.\n"
  "  foreign static sfx_sound_(a0)\n"
  "  static sfx_sound(params) { sfx_sound_(params.toList) }\n"
  "\n"
  "  // Create Sfx parameters.\n"
  "  foreign static sfx_generate_(a0)\n"
  "  static sfx_generate(type) { SfxParams.fromList(sfx_generate_(type)) }\n"
  "\n"
  "  // TILE\n"
  "\n"
  "  // Load a tilemap (a Tiled map, exported as JSON) from a file in cart.\n"
  "  foreign static load_tilemap_(a0)\n"
  "  static load_tilemap(filename) { load_tilemap_(filename) }\n"
  "\n"
  "  // Unload a tilemap.\n"
  "  foreign static unload_tilemap_(a0)\n"
  "  static unload_tilemap(tilemap) { unload_tilemap_(tilemap) }\n"
  "\n"
  "  // Update a tilemap's animation timers (deltaTime is in seconds).\n"
  "  foreign static tile_update_(a0, a1)\n"
  "  static tile_update(tilemap, deltaTime) { tile_update_(tilemap, deltaTime) }\n"
  "\n"
  "  // Get the size of a tilemap, in tiles.\n"
  "  foreign static tile_map_size_(a0)\n"
  "  static tile_map_size(tilemap) { Dimensions.fromList(tile_map_size_(tilemap)) }\n"
  "\n"
  "  // Get the size of a single tile of a tilemap, in pixels.\n"
  "  foreign static tile_tile_size_(a0)\n"
  "  static tile_tile_size(tilemap) { Dimensions.fromList(tile_tile_size_(tilemap)) }\n"
  "\n"
  "  // Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)\n"
  "  foreign static tile_map_prop_(a0, a1)\n"
  "  static tile_map_prop(tilemap, name) { TilemapProp.fromList(tile_map_prop_(tilemap, name)) }\n"
  "\n"
  "  // Get the number of custom properties on a tilemap.\n"
  "  foreign static tile_map_prop_count_(a0)\n"
  "  static tile_map_prop_count(tilemap) { tile_map_prop_count_(tilemap) }\n"
  "\n"
  "  // Get a custom property of a tilemap, by index (PROP_NONE when out of range.)\n"
  "  foreign static tile_map_prop_at_(a0, a1)\n"
  "  static tile_map_prop_at(tilemap, index) { TilemapProp.fromList(tile_map_prop_at_(tilemap, index)) }\n"
  "\n"
  "  // Draw a tilemap on the screen.\n"
  "  foreign static tile_draw_(a0, a1, a2)\n"
  "  static tile_draw(tilemap, posX, posY) { tile_draw_(tilemap, posX, posY) }\n"
  "\n"
  "  // Draw a tilemap on the screen, tinted by a color.\n"
  "  foreign static tile_draw_tint_(a0, a1, a2, a3)\n"
  "  static tile_draw_tint(tilemap, posX, posY, tint) { tile_draw_tint_(tilemap, posX, posY, tint.value) }\n"
  "\n"
  "  // Draw a tilemap on an image.\n"
  "  foreign static tile_draw_on_image_(a0, a1, a2, a3)\n"
  "  static tile_draw_on_image(dst, tilemap, posX, posY) { tile_draw_on_image_(dst, tilemap, posX, posY) }\n"
  "\n"
  "  // Render a whole tilemap to a new image.\n"
  "  foreign static tilemap_image_(a0)\n"
  "  static tilemap_image(tilemap) { tilemap_image_(tilemap) }\n"
  "\n"
  "  // Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.\n"
  "  foreign static tile_layer_count_(a0)\n"
  "  static tile_layer_count(tilemap) { tile_layer_count_(tilemap) }\n"
  "\n"
  "  // Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)\n"
  "  foreign static tile_layer_index_(a0, a1)\n"
  "  static tile_layer_index(tilemap, name) { tile_layer_index_(tilemap, name) }\n"
  "\n"
  "  // Get the name of a layer of a tilemap.\n"
  "  foreign static tile_layer_name_(a0, a1)\n"
  "  static tile_layer_name(tilemap, layer) { tile_layer_name_(tilemap, layer) }\n"
  "\n"
  "  // Get the kind of a layer of a tilemap.\n"
  "  foreign static tile_layer_type_(a0, a1)\n"
  "  static tile_layer_type(tilemap, layer) { tile_layer_type_(tilemap, layer) }\n"
  "\n"
  "  // Get the size of a layer of a tilemap, in tiles.\n"
  "  foreign static tile_layer_size_(a0, a1)\n"
  "  static tile_layer_size(tilemap, layer) { Dimensions.fromList(tile_layer_size_(tilemap, layer)) }\n"
  "\n"
  "  // Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.\n"
  "  foreign static tile_layer_visible_(a0, a1)\n"
  "  static tile_layer_visible(tilemap, layer) { tile_layer_visible_(tilemap, layer) }\n"
  "\n"
  "  // Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)\n"
  "  foreign static tile_layer_prop_(a0, a1, a2)\n"
  "  static tile_layer_prop(tilemap, layer, name) { TilemapProp.fromList(tile_layer_prop_(tilemap, layer, name)) }\n"
  "\n"
  "  // Get the number of custom properties on a layer of a tilemap.\n"
  "  foreign static tile_layer_prop_count_(a0, a1)\n"
  "  static tile_layer_prop_count(tilemap, layer) { tile_layer_prop_count_(tilemap, layer) }\n"
  "\n"
  "  // Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)\n"
  "  foreign static tile_layer_prop_at_(a0, a1, a2)\n"
  "  static tile_layer_prop_at(tilemap, layer, index) { TilemapProp.fromList(tile_layer_prop_at_(tilemap, layer, index)) }\n"
  "\n"
  "  // Draw a single layer of a tilemap on the screen.\n"
  "  foreign static tile_draw_layer_(a0, a1, a2, a3)\n"
  "  static tile_draw_layer(tilemap, layer, posX, posY) { tile_draw_layer_(tilemap, layer, posX, posY) }\n"
  "\n"
  "  // Draw a single layer of a tilemap on the screen, tinted by a color.\n"
  "  foreign static tile_draw_layer_tint_(a0, a1, a2, a3, a4)\n"
  "  static tile_draw_layer_tint(tilemap, layer, posX, posY, tint) { tile_draw_layer_tint_(tilemap, layer, posX, posY, tint.value) }\n"
  "\n"
  "  // Draw a single layer of a tilemap on an image.\n"
  "  foreign static tile_draw_layer_on_image_(a0, a1, a2, a3, a4)\n"
  "  static tile_draw_layer_on_image(dst, tilemap, layer, posX, posY) { tile_draw_layer_on_image_(dst, tilemap, layer, posX, posY) }\n"
  "\n"
  "  // Render a single layer of a tilemap to a new image.\n"
  "  foreign static tile_layer_image_(a0, a1)\n"
  "  static tile_layer_image(tilemap, layer) { tile_layer_image_(tilemap, layer) }\n"
  "\n"
  "  // Get the gid of the tile at a column/row in a tilemap layer.\n"
  "  foreign static tile_get_tile_(a0, a1, a2, a3)\n"
  "  static tile_get_tile(tilemap, layer, column, row) { tile_get_tile_(tilemap, layer, column, row) }\n"
  "\n"
  "  // Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.\n"
  "  foreign static tile_set_tile_(a0, a1, a2, a3, a4)\n"
  "  static tile_set_tile(tilemap, layer, column, row, gid) { tile_set_tile_(tilemap, layer, column, row, gid) }\n"
  "\n"
  "  // Draw a single tile from a tilemap on the screen.\n"
  "  foreign static tile_draw_tile_(a0, a1, a2, a3)\n"
  "  static tile_draw_tile(tilemap, gid, posX, posY) { tile_draw_tile_(tilemap, gid, posX, posY) }\n"
  "\n"
  "  // Get a copy of the image of a single tile in a tilemap.\n"
  "  foreign static tile_image_(a0, a1)\n"
  "  static tile_image(tilemap, gid) { tile_image_(tilemap, gid) }\n"
  "\n"
  "  // Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.\n"
  "  foreign static tile_gid_prop_(a0, a1, a2)\n"
  "  static tile_gid_prop(tilemap, gid, name) { TilemapProp.fromList(tile_gid_prop_(tilemap, gid, name)) }\n"
  "\n"
  "  // Get the number of custom properties on a tile of a tilemap.\n"
  "  foreign static tile_gid_prop_count_(a0, a1)\n"
  "  static tile_gid_prop_count(tilemap, gid) { tile_gid_prop_count_(tilemap, gid) }\n"
  "\n"
  "  // Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)\n"
  "  foreign static tile_gid_prop_at_(a0, a1, a2)\n"
  "  static tile_gid_prop_at(tilemap, gid, index) { TilemapProp.fromList(tile_gid_prop_at_(tilemap, gid, index)) }\n"
  "\n"
  "  // Get the number of objects on an object-layer of a tilemap.\n"
  "  foreign static tile_object_count_(a0, a1)\n"
  "  static tile_object_count(tilemap, layer) { tile_object_count_(tilemap, layer) }\n"
  "\n"
  "  // Get an object from an object-layer of a tilemap.\n"
  "  foreign static tile_object_(a0, a1, a2)\n"
  "  static tile_object(tilemap, layer, index) { TilemapObject.fromList(tile_object_(tilemap, layer, index)) }\n"
  "\n"
  "  // Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)\n"
  "  foreign static tile_object_index_(a0, a1, a2)\n"
  "  static tile_object_index(tilemap, layer, name) { tile_object_index_(tilemap, layer, name) }\n"
  "\n"
  "  // Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)\n"
  "  foreign static tile_object_prop_(a0, a1, a2, a3)\n"
  "  static tile_object_prop(tilemap, layer, index, name) { TilemapProp.fromList(tile_object_prop_(tilemap, layer, index, name)) }\n"
  "\n"
  "  // Get the number of custom properties on an object of a tilemap.\n"
  "  foreign static tile_object_prop_count_(a0, a1, a2)\n"
  "  static tile_object_prop_count(tilemap, layer, index) { tile_object_prop_count_(tilemap, layer, index) }\n"
  "\n"
  "  // Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)\n"
  "  foreign static tile_object_prop_at_(a0, a1, a2, a3)\n"
  "  static tile_object_prop_at(tilemap, layer, index, propIndex) { TilemapProp.fromList(tile_object_prop_at_(tilemap, layer, index, propIndex)) }\n"
  "\n"
  "  // TYPES\n"
  "\n"
  "  // UTILITIES\n"
  "\n"
  "  // Get system-time (ms) since unix epoch.\n"
  "  foreign static current_time_\n"
  "  static current_time { current_time_ }\n"
  "\n"
  "  // Get the change in time (seconds) since the last update run.\n"
  "  foreign static delta_time_\n"
  "  static delta_time { delta_time_ }\n"
  "\n"
  "  // Get a random integer between 2 numbers.\n"
  "  foreign static random_int_(a0, a1)\n"
  "  static random_int(min, max) { random_int_(min, max) }\n"
  "\n"
  "  // Get the random-seed.\n"
  "  foreign static random_seed_get_\n"
  "  static random_seed_get { random_seed_get_ }\n"
  "\n"
  "  // Set the random-seed.\n"
  "  foreign static random_seed_set_(a0)\n"
  "  static random_seed_set(seed) { random_seed_set_(seed) }\n"
  "}\n"
  "\n"
  "// The screen is image 0\n"
  "var SCREEN = 0\n"
  "var SCREEN_WIDTH = 640\n"
  "var SCREEN_HEIGHT = 480\n"
  "\n"
  "// The built-in font\n"
  "var FONT_DEFAULT = 0\n"
  "\n"
  "// Colors\n"
  "var LIGHTGRAY = Color.new(200, 200, 200, 255)\n"
  "var GRAY = Color.new(130, 130, 130, 255)\n"
  "var DARKGRAY = Color.new(80, 80, 80, 255)\n"
  "var YELLOW = Color.new(253, 249, 0, 255)\n"
  "var GOLD = Color.new(255, 203, 0, 255)\n"
  "var ORANGE = Color.new(255, 161, 0, 255)\n"
  "var PINK = Color.new(255, 109, 194, 255)\n"
  "var RED = Color.new(230, 41, 55, 255)\n"
  "var MAROON = Color.new(190, 33, 55, 255)\n"
  "var GREEN = Color.new(0, 228, 48, 255)\n"
  "var LIME = Color.new(0, 158, 47, 255)\n"
  "var DARKGREEN = Color.new(0, 117, 44, 255)\n"
  "var SKYBLUE = Color.new(102, 191, 255, 255)\n"
  "var BLUE = Color.new(0, 121, 241, 255)\n"
  "var DARKBLUE = Color.new(0, 82, 172, 255)\n"
  "var PURPLE = Color.new(200, 122, 255, 255)\n"
  "var VIOLET = Color.new(135, 60, 190, 255)\n"
  "var DARKPURPLE = Color.new(112, 31, 126, 255)\n"
  "var BEIGE = Color.new(211, 176, 131, 255)\n"
  "var BROWN = Color.new(127, 106, 79, 255)\n"
  "var DARKBROWN = Color.new(76, 63, 47, 255)\n"
  "var WHITE = Color.new(255, 255, 255, 255)\n"
  "var BLACK = Color.new(0, 0, 0, 255)\n"
  "var BLANK = Color.new(0, 0, 0, 0)\n"
  "var MAGENTA = Color.new(255, 0, 255, 255)\n"
  "var RAYWHITE = Color.new(245, 245, 245, 255)\n"
  "\n"
  "// The current tagged version of null0 engine\n"
  "var NULL0_VERSION = \"0.0.17\"\n"
  "\n"
  "// Potential image-filtering techniques for scale/etc.\n"
  "var FILTER_NEARESTNEIGHBOR = 0\n"
  "var FILTER_BILINEAR = 1\n"
  "var FILTER_SMOOTH = 2\n"
  "\n"
  "// Represents a Sfx preset type.\n"
  "var SFX_COIN = 0\n"
  "var SFX_LASER = 1\n"
  "var SFX_EXPLOSION = 2\n"
  "var SFX_POWERUP = 3\n"
  "var SFX_HURT = 4\n"
  "var SFX_JUMP = 5\n"
  "var SFX_SELECT = 6\n"
  "var SFX_SYNTH = 7\n"
  "\n"
  "// Represents a keyboard key.\n"
  "var KEY_INVALID = 0\n"
  "var KEY_SPACE = 32\n"
  "var KEY_APOSTROPHE = 39\n"
  "var KEY_COMMA = 44\n"
  "var KEY_MINUS = 45\n"
  "var KEY_PERIOD = 46\n"
  "var KEY_SLASH = 47\n"
  "var KEY_0 = 48\n"
  "var KEY_1 = 49\n"
  "var KEY_2 = 50\n"
  "var KEY_3 = 51\n"
  "var KEY_4 = 52\n"
  "var KEY_5 = 53\n"
  "var KEY_6 = 54\n"
  "var KEY_7 = 55\n"
  "var KEY_8 = 56\n"
  "var KEY_9 = 57\n"
  "var KEY_SEMICOLON = 59\n"
  "var KEY_EQUAL = 61\n"
  "var KEY_A = 65\n"
  "var KEY_B = 66\n"
  "var KEY_C = 67\n"
  "var KEY_D = 68\n"
  "var KEY_E = 69\n"
  "var KEY_F = 70\n"
  "var KEY_G = 71\n"
  "var KEY_H = 72\n"
  "var KEY_I = 73\n"
  "var KEY_J = 74\n"
  "var KEY_K = 75\n"
  "var KEY_L = 76\n"
  "var KEY_M = 77\n"
  "var KEY_N = 78\n"
  "var KEY_O = 79\n"
  "var KEY_P = 80\n"
  "var KEY_Q = 81\n"
  "var KEY_R = 82\n"
  "var KEY_S = 83\n"
  "var KEY_T = 84\n"
  "var KEY_U = 85\n"
  "var KEY_V = 86\n"
  "var KEY_W = 87\n"
  "var KEY_X = 88\n"
  "var KEY_Y = 89\n"
  "var KEY_Z = 90\n"
  "var KEY_LEFT_BRACKET = 91\n"
  "var KEY_BACKSLASH = 92\n"
  "var KEY_RIGHT_BRACKET = 93\n"
  "var KEY_GRAVE_ACCENT = 96\n"
  "var KEY_WORLD_1 = 161\n"
  "var KEY_WORLD_2 = 162\n"
  "var KEY_ESCAPE = 256\n"
  "var KEY_ENTER = 257\n"
  "var KEY_TAB = 258\n"
  "var KEY_BACKSPACE = 259\n"
  "var KEY_INSERT = 260\n"
  "var KEY_DELETE = 261\n"
  "var KEY_RIGHT = 262\n"
  "var KEY_LEFT = 263\n"
  "var KEY_DOWN = 264\n"
  "var KEY_UP = 265\n"
  "var KEY_PAGE_UP = 266\n"
  "var KEY_PAGE_DOWN = 267\n"
  "var KEY_HOME = 268\n"
  "var KEY_END = 269\n"
  "var KEY_CAPS_LOCK = 280\n"
  "var KEY_SCROLL_LOCK = 281\n"
  "var KEY_NUM_LOCK = 282\n"
  "var KEY_PRINT_SCREEN = 283\n"
  "var KEY_PAUSE = 284\n"
  "var KEY_F1 = 290\n"
  "var KEY_F2 = 291\n"
  "var KEY_F3 = 292\n"
  "var KEY_F4 = 293\n"
  "var KEY_F5 = 294\n"
  "var KEY_F6 = 295\n"
  "var KEY_F7 = 296\n"
  "var KEY_F8 = 297\n"
  "var KEY_F9 = 298\n"
  "var KEY_F10 = 299\n"
  "var KEY_F11 = 300\n"
  "var KEY_F12 = 301\n"
  "var KEY_F13 = 302\n"
  "var KEY_F14 = 303\n"
  "var KEY_F15 = 304\n"
  "var KEY_F16 = 305\n"
  "var KEY_F17 = 306\n"
  "var KEY_F18 = 307\n"
  "var KEY_F19 = 308\n"
  "var KEY_F20 = 309\n"
  "var KEY_F21 = 310\n"
  "var KEY_F22 = 311\n"
  "var KEY_F23 = 312\n"
  "var KEY_F24 = 313\n"
  "var KEY_F25 = 314\n"
  "var KEY_KP_0 = 320\n"
  "var KEY_KP_1 = 321\n"
  "var KEY_KP_2 = 322\n"
  "var KEY_KP_3 = 323\n"
  "var KEY_KP_4 = 324\n"
  "var KEY_KP_5 = 325\n"
  "var KEY_KP_6 = 326\n"
  "var KEY_KP_7 = 327\n"
  "var KEY_KP_8 = 328\n"
  "var KEY_KP_9 = 329\n"
  "var KEY_KP_DECIMAL = 330\n"
  "var KEY_KP_DIVIDE = 331\n"
  "var KEY_KP_MULTIPLY = 332\n"
  "var KEY_KP_SUBTRACT = 333\n"
  "var KEY_KP_ADD = 334\n"
  "var KEY_KP_ENTER = 335\n"
  "var KEY_KP_EQUAL = 336\n"
  "var KEY_LEFT_SHIFT = 340\n"
  "var KEY_LEFT_CONTROL = 341\n"
  "var KEY_LEFT_ALT = 342\n"
  "var KEY_LEFT_SUPER = 343\n"
  "var KEY_RIGHT_SHIFT = 344\n"
  "var KEY_RIGHT_CONTROL = 345\n"
  "var KEY_RIGHT_ALT = 346\n"
  "var KEY_RIGHT_SUPER = 347\n"
  "var KEY_MENU = 348\n"
  "\n"
  "// Represents a gamepad button.\n"
  "var GAMEPAD_BUTTON_UNKNOWN = 0\n"
  "var GAMEPAD_BUTTON_UP = 1\n"
  "var GAMEPAD_BUTTON_RIGHT = 2\n"
  "var GAMEPAD_BUTTON_DOWN = 3\n"
  "var GAMEPAD_BUTTON_LEFT = 4\n"
  "var GAMEPAD_BUTTON_Y = 5\n"
  "var GAMEPAD_BUTTON_B = 6\n"
  "var GAMEPAD_BUTTON_A = 7\n"
  "var GAMEPAD_BUTTON_X = 8\n"
  "var GAMEPAD_BUTTON_LEFT_SHOULDER = 9\n"
  "var GAMEPAD_BUTTON_LEFT_TRIGGER = 10\n"
  "var GAMEPAD_BUTTON_RIGHT_SHOULDER = 11\n"
  "var GAMEPAD_BUTTON_RIGHT_TRIGGER = 12\n"
  "var GAMEPAD_BUTTON_SELECT = 13\n"
  "var GAMEPAD_BUTTON_MENU = 14\n"
  "var GAMEPAD_BUTTON_START = 15\n"
  "var GAMEPAD_BUTTON_LEFT_THUMB = 16\n"
  "var GAMEPAD_BUTTON_RIGHT_THUMB = 17\n"
  "\n"
  "// Represents a mouse button.\n"
  "var MOUSE_BUTTON_UNKNOWN = 0\n"
  "var MOUSE_BUTTON_LEFT = 1\n"
  "var MOUSE_BUTTON_RIGHT = 2\n"
  "var MOUSE_BUTTON_MIDDLE = 3\n"
  "\n"
  "// The kind of a layer in a tilemap.\n"
  "var LAYER_NONE = 0\n"
  "var LAYER_TILE = 1\n"
  "var LAYER_OBJECT = 2\n"
  "var LAYER_IMAGE = 3\n"
  "var LAYER_GROUP = 4\n"
  "\n"
  "// The type of a tilemap property's value. Tiled's \"file\" properties arrive as PROP_STRING.\n"
  "var PROP_NONE = 0\n"
  "var PROP_INT = 1\n"
  "var PROP_BOOL = 2\n"
  "var PROP_FLOAT = 3\n"
  "var PROP_STRING = 4\n"
  "var PROP_COLOR = 5\n"
  "\n"
;

// ARG/RETURN HELPERS

// wren is dynamically typed, so every arg is checked before it is used
static double number_arg(WrenVM* vm, int slot) {
  return wrenGetSlotType(vm, slot) == WREN_TYPE_NUM ? wrenGetSlotDouble(vm, slot) : 0;
}

static bool bool_arg(WrenVM* vm, int slot) {
  return wrenGetSlotType(vm, slot) == WREN_TYPE_BOOL ? wrenGetSlotBool(vm, slot) : false;
}

static const char* string_arg(WrenVM* vm, int slot) {
  return wrenGetSlotType(vm, slot) == WREN_TYPE_STRING ? wrenGetSlotString(vm, slot) : "";
}

// a Color arrives as a packed rgba number
static Color color_arg(WrenVM* vm, int slot) {
  u32 v = (u32)number_arg(vm, slot);
  Color color = {(u8)((v >> 24) & 0xff), (u8)((v >> 16) & 0xff), (u8)((v >> 8) & 0xff), (u8)(v & 0xff)};
  return color;
}

// wren hands out slots without clearing them, so a fresh scratch-slot is
// nulled right away - the GC walks every slot, and would trip over whatever
// was left in there
static int scratch_slot(WrenVM* vm) {
  int slot = wrenGetSlotCount(vm);
  wrenEnsureSlots(vm, slot + 1);
  wrenSetSlotNull(vm, slot);
  return slot;
}

// read 1 number out of a wren list
static double list_number(WrenVM* vm, int slot, int index, int scratch) {
  wrenGetListElement(vm, slot, index, scratch);
  return number_arg(vm, scratch);
}

// points arrive as a flat list of x/y numbers
static Vector* vectors_arg(WrenVM* vm, int slot, int* count) {
  *count = 0;
  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {
    return NULL;
  }
  int len = wrenGetListCount(vm, slot) / 2;
  if (len < 1) {
    return NULL;
  }
  Vector* points = malloc(sizeof(Vector) * len);
  if (points == NULL) {
    return NULL;
  }
  int scratch = scratch_slot(vm);
  for (int i = 0; i < len; i++) {
    points[i].x = (i32)list_number(vm, slot, i * 2, scratch);
    points[i].y = (i32)list_number(vm, slot, (i * 2) + 1, scratch);
  }
  *count = len;
  return points;
}

// a Rectangle arrives as a list of 4 numbers (x, y, width, height)
static Rectangle rectangle_arg(WrenVM* vm, int slot) {
  Rectangle rect = {0, 0, 0, 0};
  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {
    return rect;
  }
  int scratch = scratch_slot(vm);
  rect.x = (i32)list_number(vm, slot, 0, scratch);
  rect.y = (i32)list_number(vm, slot, 1, scratch);
  rect.width = (i32)list_number(vm, slot, 2, scratch);
  rect.height = (i32)list_number(vm, slot, 3, scratch);
  return rect;
}

// a list of integers arrives as a wren list of numbers
static i32* ints_arg(WrenVM* vm, int slot, int* count) {
  *count = 0;
  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {
    return NULL;
  }
  int len = wrenGetListCount(vm, slot);
  if (len < 1) {
    return NULL;
  }
  i32* ints = malloc(sizeof(i32) * len);
  if (ints == NULL) {
    return NULL;
  }
  int scratch = scratch_slot(vm);
  for (int i = 0; i < len; i++) {
    ints[i] = (i32)list_number(vm, slot, i, scratch);
  }
  *count = len;
  return ints;
}

// a SfxParams arrives as a list of its members
static SfxParams sfxparams_arg(WrenVM* vm, int slot) {
  SfxParams params = {0};
  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {
    return params;
  }
  int len = wrenGetListCount(vm, slot);
  int scratch = scratch_slot(vm);
  if (len > 0) params.randSeed = (u32)list_number(vm, slot, 0, scratch);
  if (len > 1) params.waveType = (i32)list_number(vm, slot, 1, scratch);
  if (len > 2) params.attackTime = (f32)list_number(vm, slot, 2, scratch);
  if (len > 3) params.sustainTime = (f32)list_number(vm, slot, 3, scratch);
  if (len > 4) params.sustainPunch = (f32)list_number(vm, slot, 4, scratch);
  if (len > 5) params.decayTime = (f32)list_number(vm, slot, 5, scratch);
  if (len > 6) params.startFrequency = (f32)list_number(vm, slot, 6, scratch);
  if (len > 7) params.minFrequency = (f32)list_number(vm, slot, 7, scratch);
  if (len > 8) params.slide = (f32)list_number(vm, slot, 8, scratch);
  if (len > 9) params.deltaSlide = (f32)list_number(vm, slot, 9, scratch);
  if (len > 10) params.vibratoDepth = (f32)list_number(vm, slot, 10, scratch);
  if (len > 11) params.vibratoSpeed = (f32)list_number(vm, slot, 11, scratch);
  if (len > 12) params.changeAmount = (f32)list_number(vm, slot, 12, scratch);
  if (len > 13) params.changeSpeed = (f32)list_number(vm, slot, 13, scratch);
  if (len > 14) params.squareDuty = (f32)list_number(vm, slot, 14, scratch);
  if (len > 15) params.dutySweep = (f32)list_number(vm, slot, 15, scratch);
  if (len > 16) params.repeatSpeed = (f32)list_number(vm, slot, 16, scratch);
  if (len > 17) params.phaserOffset = (f32)list_number(vm, slot, 17, scratch);
  if (len > 18) params.phaserSweep = (f32)list_number(vm, slot, 18, scratch);
  if (len > 19) params.lpfCutoff = (f32)list_number(vm, slot, 19, scratch);
  if (len > 20) params.lpfCutoffSweep = (f32)list_number(vm, slot, 20, scratch);
  if (len > 21) params.lpfResonance = (f32)list_number(vm, slot, 21, scratch);
  if (len > 22) params.hpfCutoff = (f32)list_number(vm, slot, 22, scratch);
  if (len > 23) params.hpfCutoffSweep = (f32)list_number(vm, slot, 23, scratch);
  return params;
}

// structs go back to wren as a list of their members
static void list_ret(WrenVM* vm, double* values, int count) {
  int scratch = scratch_slot(vm);
  wrenSetSlotNewList(vm, 0);
  for (int i = 0; i < count; i++) {
    wrenSetSlotDouble(vm, scratch, values[i]);
    wrenInsertInList(vm, 0, -1, scratch);
  }
}

// a Color goes back as a packed rgba number
static void color_ret(WrenVM* vm, Color* color) {
  if (color == NULL) {
    wrenSetSlotNull(vm, 0);
    return;
  }
  wrenSetSlotDouble(vm, 0, (double)(((u32)color->r << 24) | ((u32)color->g << 16) | ((u32)color->b << 8) | (u32)color->a));
}

// a host string goes back as a wren string (NULL becomes "")
static void string_ret(WrenVM* vm, char* value) {
  wrenSetSlotString(vm, 0, value == NULL ? "" : value);
}

static void sfxparams_ret(WrenVM* vm, SfxParams* value) {
  if (value == NULL) {
    wrenSetSlotNull(vm, 0);
    return;
  }
  double values[] = {(double)value->randSeed, (double)value->waveType, (double)value->attackTime, (double)value->sustainTime, (double)value->sustainPunch, (double)value->decayTime, (double)value->startFrequency, (double)value->minFrequency, (double)value->slide, (double)value->deltaSlide, (double)value->vibratoDepth, (double)value->vibratoSpeed, (double)value->changeAmount, (double)value->changeSpeed, (double)value->squareDuty, (double)value->dutySweep, (double)value->repeatSpeed, (double)value->phaserOffset, (double)value->phaserSweep, (double)value->lpfCutoff, (double)value->lpfCutoffSweep, (double)value->lpfResonance, (double)value->hpfCutoff, (double)value->hpfCutoffSweep};
  list_ret(vm, values, 24);
}

static void dimensions_ret(WrenVM* vm, Dimensions* value) {
  if (value == NULL) {
    wrenSetSlotNull(vm, 0);
    return;
  }
  double values[] = {(double)value->width, (double)value->height};
  list_ret(vm, values, 2);
}

static void vector_ret(WrenVM* vm, Vector* value) {
  if (value == NULL) {
    wrenSetSlotNull(vm, 0);
    return;
  }
  double values[] = {(double)value->x, (double)value->y};
  list_ret(vm, values, 2);
}

static void rectangle_ret(WrenVM* vm, Rectangle* value) {
  if (value == NULL) {
    wrenSetSlotNull(vm, 0);
    return;
  }
  double values[] = {(double)value->x, (double)value->y, (double)value->width, (double)value->height};
  list_ret(vm, values, 4);
}

static void tilemapprop_ret(WrenVM* vm, TilemapProp* value) {
  if (value == NULL) {
    wrenSetSlotNull(vm, 0);
    return;
  }
  int scratch = scratch_slot(vm);
  wrenSetSlotNewList(vm, 0);
  wrenSetSlotString(vm, scratch, value->name == NULL ? "" : value->name);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->type);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->integer);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->number);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotString(vm, scratch, value->text == NULL ? "" : value->text);
  wrenInsertInList(vm, 0, -1, scratch);
}

static void tilemapobject_ret(WrenVM* vm, TilemapObject* value) {
  if (value == NULL) {
    wrenSetSlotNull(vm, 0);
    return;
  }
  int scratch = scratch_slot(vm);
  wrenSetSlotNewList(vm, 0);
  wrenSetSlotDouble(vm, scratch, (double)value->id);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotString(vm, scratch, value->name == NULL ? "" : value->name);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotString(vm, scratch, value->type == NULL ? "" : value->type);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->gid);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->x);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->y);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->width);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->height);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->rotation);
  wrenInsertInList(vm, 0, -1, scratch);
  wrenSetSlotDouble(vm, scratch, (double)value->visible);
  wrenInsertInList(vm, 0, -1, scratch);
}

// BINDINGS

// COLORS

// Tint a color with another color.
static void wren_color_tint(WrenVM* vm) {
  Color color = color_arg(vm, 1);
  Color tint = color_arg(vm, 2);
  Color* ret = color_tint(color, tint);
  color_ret(vm, ret);
}

// Fade a color.
static void wren_color_fade(WrenVM* vm) {
  Color color = color_arg(vm, 1);
  f32 alpha = (f32)number_arg(vm, 2);
  Color* ret = color_fade(color, alpha);
  color_ret(vm, ret);
}

// Change the brightness of a color.
static void wren_color_brightness(WrenVM* vm) {
  Color color = color_arg(vm, 1);
  f32 factor = (f32)number_arg(vm, 2);
  Color* ret = color_brightness(color, factor);
  color_ret(vm, ret);
}

// Invert a color.
static void wren_color_invert(WrenVM* vm) {
  Color color = color_arg(vm, 1);
  Color* ret = color_invert(color);
  color_ret(vm, ret);
}

// Blend 2 colors together.
static void wren_color_alpha_blend(WrenVM* vm) {
  Color dst = color_arg(vm, 1);
  Color src = color_arg(vm, 2);
  Color* ret = color_alpha_blend(dst, src);
  color_ret(vm, ret);
}

// Change contrast of a color.
static void wren_color_contrast(WrenVM* vm) {
  Color color = color_arg(vm, 1);
  f32 contrast = (f32)number_arg(vm, 2);
  Color* ret = color_contrast(color, contrast);
  color_ret(vm, ret);
}

// Interpolate colors.
static void wren_color_bilinear_interpolate(WrenVM* vm) {
  Color color00 = color_arg(vm, 1);
  Color color01 = color_arg(vm, 2);
  Color color10 = color_arg(vm, 3);
  Color color11 = color_arg(vm, 4);
  f32 coordinateX = (f32)number_arg(vm, 5);
  f32 coordinateY = (f32)number_arg(vm, 6);
  Color* ret = color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY);
  color_ret(vm, ret);
}


// GRAPHICS

// Create a new blank image.
static void wren_new_image(WrenVM* vm) {
  i32 width = (i32)number_arg(vm, 1);
  i32 height = (i32)number_arg(vm, 2);
  Color color = color_arg(vm, 3);
  u32 ret = new_image(width, height, color);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Copy an image to a new image.
static void wren_image_copy(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  u32 ret = image_copy(image);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Create an image from a region of another image.
static void wren_image_subimage(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  i32 x = (i32)number_arg(vm, 2);
  i32 y = (i32)number_arg(vm, 3);
  i32 width = (i32)number_arg(vm, 4);
  i32 height = (i32)number_arg(vm, 5);
  u32 ret = image_subimage(image, x, y, width, height);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Clear the screen.
static void wren_clear(WrenVM* vm) {
  Color color = color_arg(vm, 1);
  clear(color);
  wrenSetSlotNull(vm, 0);
}

// Draw a single pixel on the screen.
static void wren_draw_point(WrenVM* vm) {
  i32 x = (i32)number_arg(vm, 1);
  i32 y = (i32)number_arg(vm, 2);
  Color color = color_arg(vm, 3);
  draw_point(x, y, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a line on the screen.
static void wren_draw_line(WrenVM* vm) {
  i32 startPosX = (i32)number_arg(vm, 1);
  i32 startPosY = (i32)number_arg(vm, 2);
  i32 endPosX = (i32)number_arg(vm, 3);
  i32 endPosY = (i32)number_arg(vm, 4);
  Color color = color_arg(vm, 5);
  draw_line(startPosX, startPosY, endPosX, endPosY, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled rectangle on the screen.
static void wren_draw_rectangle(WrenVM* vm) {
  i32 posX = (i32)number_arg(vm, 1);
  i32 posY = (i32)number_arg(vm, 2);
  i32 width = (i32)number_arg(vm, 3);
  i32 height = (i32)number_arg(vm, 4);
  Color color = color_arg(vm, 5);
  draw_rectangle(posX, posY, width, height, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled triangle on the screen.
static void wren_draw_triangle(WrenVM* vm) {
  i32 x1 = (i32)number_arg(vm, 1);
  i32 y1 = (i32)number_arg(vm, 2);
  i32 x2 = (i32)number_arg(vm, 3);
  i32 y2 = (i32)number_arg(vm, 4);
  i32 x3 = (i32)number_arg(vm, 5);
  i32 y3 = (i32)number_arg(vm, 6);
  Color color = color_arg(vm, 7);
  draw_triangle(x1, y1, x2, y2, x3, y3, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled ellipse on the screen.
static void wren_draw_ellipse(WrenVM* vm) {
  i32 centerX = (i32)number_arg(vm, 1);
  i32 centerY = (i32)number_arg(vm, 2);
  i32 radiusX = (i32)number_arg(vm, 3);
  i32 radiusY = (i32)number_arg(vm, 4);
  Color color = color_arg(vm, 5);
  draw_ellipse(centerX, centerY, radiusX, radiusY, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled circle on the screen.
static void wren_draw_circle(WrenVM* vm) {
  i32 centerX = (i32)number_arg(vm, 1);
  i32 centerY = (i32)number_arg(vm, 2);
  i32 radius = (i32)number_arg(vm, 3);
  Color color = color_arg(vm, 4);
  draw_circle(centerX, centerY, radius, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled polygon on the screen.
static void wren_draw_polygon(WrenVM* vm) {
  int points_count = 0;
  Vector* points = vectors_arg(vm, 1, &points_count);
  Color color = color_arg(vm, 2);
  draw_polygon(points, points_count, color);
  free(points);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled arc on the screen.
static void wren_draw_arc(WrenVM* vm) {
  i32 centerX = (i32)number_arg(vm, 1);
  i32 centerY = (i32)number_arg(vm, 2);
  f32 radius = (f32)number_arg(vm, 3);
  f32 startAngle = (f32)number_arg(vm, 4);
  f32 endAngle = (f32)number_arg(vm, 5);
  i32 segments = (i32)number_arg(vm, 6);
  Color color = color_arg(vm, 7);
  draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled round-rectangle on the screen.
static void wren_draw_rectangle_rounded(WrenVM* vm) {
  i32 x = (i32)number_arg(vm, 1);
  i32 y = (i32)number_arg(vm, 2);
  i32 width = (i32)number_arg(vm, 3);
  i32 height = (i32)number_arg(vm, 4);
  i32 cornerRadius = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_rectangle_rounded(x, y, width, height, cornerRadius, color);
  wrenSetSlotNull(vm, 0);
}

// Draw an image on the screen.
static void wren_draw_image(WrenVM* vm) {
  u32 src = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  draw_image(src, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Draw a tinted image on the screen.
static void wren_draw_image_tint(WrenVM* vm) {
  u32 src = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  Color tint = color_arg(vm, 4);
  draw_image_tint(src, posX, posY, tint);
  wrenSetSlotNull(vm, 0);
}

// Draw an image, rotated, on the screen.
static void wren_draw_image_rotated(WrenVM* vm) {
  u32 src = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  f32 degrees = (f32)number_arg(vm, 4);
  f32 offsetX = (f32)number_arg(vm, 5);
  f32 offsetY = (f32)number_arg(vm, 6);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 7);
  draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter);
  wrenSetSlotNull(vm, 0);
}

// Draw an image, flipped, on the screen.
static void wren_draw_image_flipped(WrenVM* vm) {
  u32 src = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  bool flipHorizontal = bool_arg(vm, 4);
  bool flipVertical = bool_arg(vm, 5);
  bool flipDiagonal = bool_arg(vm, 6);
  draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
  wrenSetSlotNull(vm, 0);
}

// Draw an image, scaled, on the screen.
static void wren_draw_image_scaled(WrenVM* vm) {
  u32 src = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  f32 scaleX = (f32)number_arg(vm, 4);
  f32 scaleY = (f32)number_arg(vm, 5);
  f32 offsetX = (f32)number_arg(vm, 6);
  f32 offsetY = (f32)number_arg(vm, 7);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 8);
  draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
  wrenSetSlotNull(vm, 0);
}

// Draw some text on the screen.
static void wren_draw_text(WrenVM* vm) {
  u32 font = (u32)number_arg(vm, 1);
  char* text = (char*)string_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  Color color = color_arg(vm, 5);
  draw_text(font, text, posX, posY, color);
  wrenSetSlotNull(vm, 0);
}

// Save an image to persistant storage.
static void wren_save_image(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  char* filename = (char*)string_arg(vm, 2);
  save_image(image, filename);
  wrenSetSlotNull(vm, 0);
}

// Load an image from a file in cart.
static void wren_load_image(WrenVM* vm) {
  char* filename = (char*)string_arg(vm, 1);
  u32 ret = load_image(filename);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Resize an image, return copy.
static void wren_image_resize(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  i32 newWidth = (i32)number_arg(vm, 2);
  i32 newHeight = (i32)number_arg(vm, 3);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 4);
  u32 ret = image_resize(image, newWidth, newHeight, filter);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Scale an image, return copy.
static void wren_image_scale(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  f32 scaleX = (f32)number_arg(vm, 2);
  f32 scaleY = (f32)number_arg(vm, 3);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 4);
  u32 ret = image_scale(image, scaleX, scaleY, filter);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Replace a color in an image, in-place.
static void wren_image_color_replace(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  Color color = color_arg(vm, 2);
  Color replace = color_arg(vm, 3);
  image_color_replace(image, color, replace);
  wrenSetSlotNull(vm, 0);
}

// Tint a color in an image, in-place.
static void wren_image_color_tint(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  Color color = color_arg(vm, 2);
  image_color_tint(image, color);
  wrenSetSlotNull(vm, 0);
}

// Fade a color in an image, in-place.
static void wren_image_color_fade(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  f32 alpha = (f32)number_arg(vm, 2);
  image_color_fade(image, alpha);
  wrenSetSlotNull(vm, 0);
}

// Copy a font to a new font.
static void wren_font_copy(WrenVM* vm) {
  u32 font = (u32)number_arg(vm, 1);
  u32 ret = font_copy(font);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Scale a font, return a new font.
static void wren_font_scale(WrenVM* vm) {
  u32 font = (u32)number_arg(vm, 1);
  f32 scaleX = (f32)number_arg(vm, 2);
  f32 scaleY = (f32)number_arg(vm, 3);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 4);
  u32 ret = font_scale(font, scaleX, scaleY, filter);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Load a BMF font from a file in cart.
static void wren_load_font_bmf(WrenVM* vm) {
  char* filename = (char*)string_arg(vm, 1);
  char* characters = (char*)string_arg(vm, 2);
  u32 ret = load_font_bmf(filename, characters);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Load a BMF font from an image.
static void wren_load_font_bmf_from_image(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  char* characters = (char*)string_arg(vm, 2);
  u32 ret = load_font_bmf_from_image(image, characters);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Measure the size of some text.
static void wren_measure_text(WrenVM* vm) {
  u32 font = (u32)number_arg(vm, 1);
  char* text = (char*)string_arg(vm, 2);
  i32 textLength = (i32)number_arg(vm, 3);
  Dimensions* ret = measure_text(font, text, textLength);
  dimensions_ret(vm, ret);
}

// Meaure an image (use 0 for screen).
static void wren_measure_image(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  Dimensions* ret = measure_image(image);
  dimensions_ret(vm, ret);
}

// Load a TTY font from a file in cart.
static void wren_load_font_tty(WrenVM* vm) {
  char* filename = (char*)string_arg(vm, 1);
  i32 glyphWidth = (i32)number_arg(vm, 2);
  i32 glyphHeight = (i32)number_arg(vm, 3);
  char* characters = (char*)string_arg(vm, 4);
  u32 ret = load_font_tty(filename, glyphWidth, glyphHeight, characters);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Load a TTY font from an image.
static void wren_load_font_tty_from_image(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  i32 glyphWidth = (i32)number_arg(vm, 2);
  i32 glyphHeight = (i32)number_arg(vm, 3);
  char* characters = (char*)string_arg(vm, 4);
  u32 ret = load_font_tty_from_image(image, glyphWidth, glyphHeight, characters);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Load a TTF font from a file in cart.
static void wren_load_font_ttf(WrenVM* vm) {
  char* filename = (char*)string_arg(vm, 1);
  i32 fontSize = (i32)number_arg(vm, 2);
  u32 ret = load_font_ttf(filename, fontSize);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Invert the colors in an image, in-place.
static void wren_image_color_invert(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  image_color_invert(image);
  wrenSetSlotNull(vm, 0);
}

// Calculate a rectangle representing the available alpha border in an image.
static void wren_image_alpha_border(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  f32 threshold = (f32)number_arg(vm, 2);
  Rectangle* ret = image_alpha_border(image, threshold);
  rectangle_ret(vm, ret);
}

// Crop an image, in-place.
static void wren_image_crop(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  i32 x = (i32)number_arg(vm, 2);
  i32 y = (i32)number_arg(vm, 3);
  i32 width = (i32)number_arg(vm, 4);
  i32 height = (i32)number_arg(vm, 5);
  image_crop(image, x, y, width, height);
  wrenSetSlotNull(vm, 0);
}

// Crop an image based on the alpha border, in-place.
static void wren_image_alpha_crop(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  f32 threshold = (f32)number_arg(vm, 2);
  image_alpha_crop(image, threshold);
  wrenSetSlotNull(vm, 0);
}

// Adjust the brightness of an image, in-place.
static void wren_image_color_brightness(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  f32 factor = (f32)number_arg(vm, 2);
  image_color_brightness(image, factor);
  wrenSetSlotNull(vm, 0);
}

// Flip an image, in-place.
static void wren_image_flip(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  bool horizontal = bool_arg(vm, 2);
  bool vertical = bool_arg(vm, 3);
  image_flip(image, horizontal, vertical);
  wrenSetSlotNull(vm, 0);
}

// Change the contrast of an image, in-place.
static void wren_image_color_contrast(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  f32 contrast = (f32)number_arg(vm, 2);
  image_color_contrast(image, contrast);
  wrenSetSlotNull(vm, 0);
}

// Use an image as an alpha-mask on another image.
static void wren_image_alpha_mask(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  u32 alphaMask = (u32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  image_alpha_mask(image, alphaMask, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Create a new image, rotating another image.
static void wren_image_rotate(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  f32 degrees = (f32)number_arg(vm, 2);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 3);
  u32 ret = image_rotate(image, degrees, filter);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Create a new image of a gradient.
static void wren_image_gradient(WrenVM* vm) {
  i32 width = (i32)number_arg(vm, 1);
  i32 height = (i32)number_arg(vm, 2);
  Color topLeft = color_arg(vm, 3);
  Color topRight = color_arg(vm, 4);
  Color bottomLeft = color_arg(vm, 5);
  Color bottomRight = color_arg(vm, 6);
  u32 ret = image_gradient(width, height, topLeft, topRight, bottomLeft, bottomRight);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Unload an image.
static void wren_unload_image(WrenVM* vm) {
  u32 image = (u32)number_arg(vm, 1);
  unload_image(image);
  wrenSetSlotNull(vm, 0);
}

// Unload a font.
static void wren_unload_font(WrenVM* vm) {
  u32 font = (u32)number_arg(vm, 1);
  unload_font(font);
  wrenSetSlotNull(vm, 0);
}

// Clear an image.
static void wren_clear_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  Color color = color_arg(vm, 2);
  clear_image(destination, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a single pixel on an image.
static void wren_draw_point_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 x = (i32)number_arg(vm, 2);
  i32 y = (i32)number_arg(vm, 3);
  Color color = color_arg(vm, 4);
  draw_point_on_image(destination, x, y, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a line on an image.
static void wren_draw_line_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 startPosX = (i32)number_arg(vm, 2);
  i32 startPosY = (i32)number_arg(vm, 3);
  i32 endPosX = (i32)number_arg(vm, 4);
  i32 endPosY = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled rectangle on an image.
static void wren_draw_rectangle_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  i32 width = (i32)number_arg(vm, 4);
  i32 height = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_rectangle_on_image(destination, posX, posY, width, height, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled triangle on an image.
static void wren_draw_triangle_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 x1 = (i32)number_arg(vm, 2);
  i32 y1 = (i32)number_arg(vm, 3);
  i32 x2 = (i32)number_arg(vm, 4);
  i32 y2 = (i32)number_arg(vm, 5);
  i32 x3 = (i32)number_arg(vm, 6);
  i32 y3 = (i32)number_arg(vm, 7);
  Color color = color_arg(vm, 8);
  draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled ellipse on an image.
static void wren_draw_ellipse_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 centerX = (i32)number_arg(vm, 2);
  i32 centerY = (i32)number_arg(vm, 3);
  i32 radiusX = (i32)number_arg(vm, 4);
  i32 radiusY = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a circle on an image.
static void wren_draw_circle_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 centerX = (i32)number_arg(vm, 2);
  i32 centerY = (i32)number_arg(vm, 3);
  i32 radius = (i32)number_arg(vm, 4);
  Color color = color_arg(vm, 5);
  draw_circle_on_image(destination, centerX, centerY, radius, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled polygon on an image.
static void wren_draw_polygon_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  int points_count = 0;
  Vector* points = vectors_arg(vm, 2, &points_count);
  Color color = color_arg(vm, 3);
  draw_polygon_on_image(destination, points, points_count, color);
  free(points);
  wrenSetSlotNull(vm, 0);
}

// Draw a filled round-rectangle on an image.
static void wren_draw_rectangle_rounded_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 x = (i32)number_arg(vm, 2);
  i32 y = (i32)number_arg(vm, 3);
  i32 width = (i32)number_arg(vm, 4);
  i32 height = (i32)number_arg(vm, 5);
  i32 cornerRadius = (i32)number_arg(vm, 6);
  Color color = color_arg(vm, 7);
  draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color);
  wrenSetSlotNull(vm, 0);
}

// Draw an image on an image.
static void wren_draw_image_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  u32 src = (u32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  draw_image_on_image(destination, src, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Draw a tinted image on an image.
static void wren_draw_image_tint_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  u32 src = (u32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  Color tint = color_arg(vm, 5);
  draw_image_tint_on_image(destination, src, posX, posY, tint);
  wrenSetSlotNull(vm, 0);
}

// Draw an image, rotated, on an image.
static void wren_draw_image_rotated_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  u32 src = (u32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  f32 degrees = (f32)number_arg(vm, 5);
  f32 offsetX = (f32)number_arg(vm, 6);
  f32 offsetY = (f32)number_arg(vm, 7);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 8);
  draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter);
  wrenSetSlotNull(vm, 0);
}

// Draw an image, flipped, on an image.
static void wren_draw_image_flipped_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  u32 src = (u32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  bool flipHorizontal = bool_arg(vm, 5);
  bool flipVertical = bool_arg(vm, 6);
  bool flipDiagonal = bool_arg(vm, 7);
  draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal);
  wrenSetSlotNull(vm, 0);
}

// Draw an image, scaled, on an image.
static void wren_draw_image_scaled_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  u32 src = (u32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  f32 scaleX = (f32)number_arg(vm, 5);
  f32 scaleY = (f32)number_arg(vm, 6);
  f32 offsetX = (f32)number_arg(vm, 7);
  f32 offsetY = (f32)number_arg(vm, 8);
  ImageFilter filter = (ImageFilter)(i32)number_arg(vm, 9);
  draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter);
  wrenSetSlotNull(vm, 0);
}

// Draw some text on an image.
static void wren_draw_text_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  u32 font = (u32)number_arg(vm, 2);
  char* text = (char*)string_arg(vm, 3);
  i32 posX = (i32)number_arg(vm, 4);
  i32 posY = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_text_on_image(destination, font, text, posX, posY, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) rectangle on the screen.
static void wren_draw_rectangle_outline(WrenVM* vm) {
  i32 posX = (i32)number_arg(vm, 1);
  i32 posY = (i32)number_arg(vm, 2);
  i32 width = (i32)number_arg(vm, 3);
  i32 height = (i32)number_arg(vm, 4);
  i32 thickness = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_rectangle_outline(posX, posY, width, height, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) triangle on the screen.
static void wren_draw_triangle_outline(WrenVM* vm) {
  i32 x1 = (i32)number_arg(vm, 1);
  i32 y1 = (i32)number_arg(vm, 2);
  i32 x2 = (i32)number_arg(vm, 3);
  i32 y2 = (i32)number_arg(vm, 4);
  i32 x3 = (i32)number_arg(vm, 5);
  i32 y3 = (i32)number_arg(vm, 6);
  i32 thickness = (i32)number_arg(vm, 7);
  Color color = color_arg(vm, 8);
  draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) ellipse on the screen.
static void wren_draw_ellipse_outline(WrenVM* vm) {
  i32 centerX = (i32)number_arg(vm, 1);
  i32 centerY = (i32)number_arg(vm, 2);
  i32 radiusX = (i32)number_arg(vm, 3);
  i32 radiusY = (i32)number_arg(vm, 4);
  i32 thickness = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) circle on the screen.
static void wren_draw_circle_outline(WrenVM* vm) {
  i32 centerX = (i32)number_arg(vm, 1);
  i32 centerY = (i32)number_arg(vm, 2);
  i32 radius = (i32)number_arg(vm, 3);
  i32 thickness = (i32)number_arg(vm, 4);
  Color color = color_arg(vm, 5);
  draw_circle_outline(centerX, centerY, radius, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) polygon on the screen.
static void wren_draw_polygon_outline(WrenVM* vm) {
  int points_count = 0;
  Vector* points = vectors_arg(vm, 1, &points_count);
  i32 thickness = (i32)number_arg(vm, 2);
  Color color = color_arg(vm, 3);
  draw_polygon_outline(points, points_count, thickness, color);
  free(points);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) arc on the screen.
static void wren_draw_arc_outline(WrenVM* vm) {
  i32 centerX = (i32)number_arg(vm, 1);
  i32 centerY = (i32)number_arg(vm, 2);
  f32 radius = (f32)number_arg(vm, 3);
  f32 startAngle = (f32)number_arg(vm, 4);
  f32 endAngle = (f32)number_arg(vm, 5);
  i32 segments = (i32)number_arg(vm, 6);
  i32 thickness = (i32)number_arg(vm, 7);
  Color color = color_arg(vm, 8);
  draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) round-rectangle on the screen.
static void wren_draw_rectangle_rounded_outline(WrenVM* vm) {
  i32 x = (i32)number_arg(vm, 1);
  i32 y = (i32)number_arg(vm, 2);
  i32 width = (i32)number_arg(vm, 3);
  i32 height = (i32)number_arg(vm, 4);
  i32 cornerRadius = (i32)number_arg(vm, 5);
  i32 thickness = (i32)number_arg(vm, 6);
  Color color = color_arg(vm, 7);
  draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) rectangle on an image.
static void wren_draw_rectangle_outline_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  i32 width = (i32)number_arg(vm, 4);
  i32 height = (i32)number_arg(vm, 5);
  i32 thickness = (i32)number_arg(vm, 6);
  Color color = color_arg(vm, 7);
  draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) triangle on an image.
static void wren_draw_triangle_outline_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 x1 = (i32)number_arg(vm, 2);
  i32 y1 = (i32)number_arg(vm, 3);
  i32 x2 = (i32)number_arg(vm, 4);
  i32 y2 = (i32)number_arg(vm, 5);
  i32 x3 = (i32)number_arg(vm, 6);
  i32 y3 = (i32)number_arg(vm, 7);
  i32 thickness = (i32)number_arg(vm, 8);
  Color color = color_arg(vm, 9);
  draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) ellipse on an image.
static void wren_draw_ellipse_outline_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 centerX = (i32)number_arg(vm, 2);
  i32 centerY = (i32)number_arg(vm, 3);
  i32 radiusX = (i32)number_arg(vm, 4);
  i32 radiusY = (i32)number_arg(vm, 5);
  i32 thickness = (i32)number_arg(vm, 6);
  Color color = color_arg(vm, 7);
  draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) circle on an image.
static void wren_draw_circle_outline_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 centerX = (i32)number_arg(vm, 2);
  i32 centerY = (i32)number_arg(vm, 3);
  i32 radius = (i32)number_arg(vm, 4);
  i32 thickness = (i32)number_arg(vm, 5);
  Color color = color_arg(vm, 6);
  draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, color);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) polygon on an image.
static void wren_draw_polygon_outline_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  int points_count = 0;
  Vector* points = vectors_arg(vm, 2, &points_count);
  i32 thickness = (i32)number_arg(vm, 3);
  Color color = color_arg(vm, 4);
  draw_polygon_outline_on_image(destination, points, points_count, thickness, color);
  free(points);
  wrenSetSlotNull(vm, 0);
}

// Draw a outlined (with thickness) round-rectangle on an image.
static void wren_draw_rectangle_rounded_outline_on_image(WrenVM* vm) {
  u32 destination = (u32)number_arg(vm, 1);
  i32 x = (i32)number_arg(vm, 2);
  i32 y = (i32)number_arg(vm, 3);
  i32 width = (i32)number_arg(vm, 4);
  i32 height = (i32)number_arg(vm, 5);
  i32 cornerRadius = (i32)number_arg(vm, 6);
  i32 thickness = (i32)number_arg(vm, 7);
  Color color = color_arg(vm, 8);
  draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, color);
  wrenSetSlotNull(vm, 0);
}


// GUI

// Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.
static void wren_gui_begin_window(WrenVM* vm) {
  char* title = (char*)string_arg(vm, 1);
  Rectangle rect = rectangle_arg(vm, 2);
  bool ret = gui_begin_window(title, rect);
  wrenSetSlotBool(vm, 0, ret);
}

// End the current GUI window.
static void wren_gui_end_window(WrenVM* vm) {
  gui_end_window();
  wrenSetSlotNull(vm, 0);
}

// A button. Returns true when it is clicked.
static void wren_gui_button(WrenVM* vm) {
  char* label = (char*)string_arg(vm, 1);
  bool ret = gui_button(label);
  wrenSetSlotBool(vm, 0, ret);
}

// A static text label.
static void wren_gui_label(WrenVM* vm) {
  char* text = (char*)string_arg(vm, 1);
  gui_label(text);
  wrenSetSlotNull(vm, 0);
}

// A block of wrapping text.
static void wren_gui_text(WrenVM* vm) {
  char* text = (char*)string_arg(vm, 1);
  gui_text(text);
  wrenSetSlotNull(vm, 0);
}

// A checkbox. Returns the (possibly changed) state.
static void wren_gui_checkbox(WrenVM* vm) {
  char* label = (char*)string_arg(vm, 1);
  bool state = bool_arg(vm, 2);
  bool ret = gui_checkbox(label, state);
  wrenSetSlotBool(vm, 0, ret);
}

// A slider. Returns the (possibly changed) value.
static void wren_gui_slider(WrenVM* vm) {
  f32 value = (f32)number_arg(vm, 1);
  f32 low = (f32)number_arg(vm, 2);
  f32 high = (f32)number_arg(vm, 3);
  f32 ret = gui_slider(value, low, high);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Set the current layout row - the column widths (negative for flexible), and the row height.
static void wren_gui_layout_row(WrenVM* vm) {
  int widths_count = 0;
  i32* widths = ints_arg(vm, 1, &widths_count);
  i32 height = (i32)number_arg(vm, 2);
  gui_layout_row(widths, widths_count, height);
  free(widths);
  wrenSetSlotNull(vm, 0);
}

// Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.
static void wren_gui_end(WrenVM* vm) {
  gui_end();
  wrenSetSlotNull(vm, 0);
}

// Draw the GUI to an image (0 is the screen).
static void wren_gui_draw(WrenVM* vm) {
  u32 dst = (u32)number_arg(vm, 1);
  gui_draw(dst);
  wrenSetSlotNull(vm, 0);
}


// INPUT

// Has the key been pressed? (tracks unpress/read correctly.)
static void wren_key_pressed(WrenVM* vm) {
  Key key = (Key)(i32)number_arg(vm, 1);
  bool ret = key_pressed(key);
  wrenSetSlotBool(vm, 0, ret);
}

// Is the key currently down?
static void wren_key_down(WrenVM* vm) {
  Key key = (Key)(i32)number_arg(vm, 1);
  bool ret = key_down(key);
  wrenSetSlotBool(vm, 0, ret);
}

// Has the key been released? (tracks press/read correctly.)
static void wren_key_released(WrenVM* vm) {
  Key key = (Key)(i32)number_arg(vm, 1);
  bool ret = key_released(key);
  wrenSetSlotBool(vm, 0, ret);
}

// Is the key currently up?
static void wren_key_up(WrenVM* vm) {
  Key key = (Key)(i32)number_arg(vm, 1);
  bool ret = key_up(key);
  wrenSetSlotBool(vm, 0, ret);
}

// Has the button been pressed? (tracks unpress/read correctly.)
static void wren_gamepad_button_pressed(WrenVM* vm) {
  i32 gamepad = (i32)number_arg(vm, 1);
  GamepadButton button = (GamepadButton)(i32)number_arg(vm, 2);
  bool ret = gamepad_button_pressed(gamepad, button);
  wrenSetSlotBool(vm, 0, ret);
}

// Is the button currently down?
static void wren_gamepad_button_down(WrenVM* vm) {
  i32 gamepad = (i32)number_arg(vm, 1);
  GamepadButton button = (GamepadButton)(i32)number_arg(vm, 2);
  bool ret = gamepad_button_down(gamepad, button);
  wrenSetSlotBool(vm, 0, ret);
}

// Has the button been released? (tracks press/read correctly.)
static void wren_gamepad_button_released(WrenVM* vm) {
  i32 gamepad = (i32)number_arg(vm, 1);
  GamepadButton button = (GamepadButton)(i32)number_arg(vm, 2);
  bool ret = gamepad_button_released(gamepad, button);
  wrenSetSlotBool(vm, 0, ret);
}

// Get current position of mouse.
static void wren_mouse_position(WrenVM* vm) {
  Vector* ret = mouse_position();
  vector_ret(vm, ret);
}

// Has the button been pressed? (tracks unpress/read correctly.)
static void wren_mouse_button_pressed(WrenVM* vm) {
  MouseButton button = (MouseButton)(i32)number_arg(vm, 1);
  bool ret = mouse_button_pressed(button);
  wrenSetSlotBool(vm, 0, ret);
}

// Is the button currently down?
static void wren_mouse_button_down(WrenVM* vm) {
  MouseButton button = (MouseButton)(i32)number_arg(vm, 1);
  bool ret = mouse_button_down(button);
  wrenSetSlotBool(vm, 0, ret);
}

// Has the button been released? (tracks press/read correctly.)
static void wren_mouse_button_released(WrenVM* vm) {
  MouseButton button = (MouseButton)(i32)number_arg(vm, 1);
  bool ret = mouse_button_released(button);
  wrenSetSlotBool(vm, 0, ret);
}

// Is the button currently up?
static void wren_mouse_button_up(WrenVM* vm) {
  MouseButton button = (MouseButton)(i32)number_arg(vm, 1);
  bool ret = mouse_button_up(button);
  wrenSetSlotBool(vm, 0, ret);
}


// SOUND

// Load a sound from a file in cart.
static void wren_load_sound(WrenVM* vm) {
  char* filename = (char*)string_arg(vm, 1);
  u32 ret = load_sound(filename);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Play a sound.
static void wren_play_sound(WrenVM* vm) {
  u32 sound = (u32)number_arg(vm, 1);
  bool loop = bool_arg(vm, 2);
  play_sound(sound, loop);
  wrenSetSlotNull(vm, 0);
}

// Stop a sound.
static void wren_stop_sound(WrenVM* vm) {
  u32 sound = (u32)number_arg(vm, 1);
  stop_sound(sound);
  wrenSetSlotNull(vm, 0);
}

// Unload a sound.
static void wren_unload_sound(WrenVM* vm) {
  u32 sound = (u32)number_arg(vm, 1);
  unload_sound(sound);
  wrenSetSlotNull(vm, 0);
}

// Speak some text and return a sound. Set things to 0 for defaults.
static void wren_tts_sound(WrenVM* vm) {
  char* text = (char*)string_arg(vm, 1);
  bool phonetic = bool_arg(vm, 2);
  i32 pitch = (i32)number_arg(vm, 3);
  i32 speed = (i32)number_arg(vm, 4);
  i32 throat = (i32)number_arg(vm, 5);
  i32 mouth = (i32)number_arg(vm, 6);
  bool sing = bool_arg(vm, 7);
  u32 ret = tts_sound(text, phonetic, pitch, speed, throat, mouth, sing);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Create Sfx sound.
static void wren_sfx_sound(WrenVM* vm) {
  SfxParams params = sfxparams_arg(vm, 1);
  u32 ret = sfx_sound(params);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Create Sfx parameters.
static void wren_sfx_generate(WrenVM* vm) {
  SfxPresetType type = (SfxPresetType)(i32)number_arg(vm, 1);
  SfxParams* ret = sfx_generate(type);
  sfxparams_ret(vm, ret);
}


// TILE

// Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
static void wren_load_tilemap(WrenVM* vm) {
  char* filename = (char*)string_arg(vm, 1);
  u32 ret = load_tilemap(filename);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Unload a tilemap.
static void wren_unload_tilemap(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  unload_tilemap(tilemap);
  wrenSetSlotNull(vm, 0);
}

// Update a tilemap's animation timers (deltaTime is in seconds).
static void wren_tile_update(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  f32 deltaTime = (f32)number_arg(vm, 2);
  tile_update(tilemap, deltaTime);
  wrenSetSlotNull(vm, 0);
}

// Get the size of a tilemap, in tiles.
static void wren_tile_map_size(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  Dimensions* ret = tile_map_size(tilemap);
  dimensions_ret(vm, ret);
}

// Get the size of a single tile of a tilemap, in pixels.
static void wren_tile_tile_size(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  Dimensions* ret = tile_tile_size(tilemap);
  dimensions_ret(vm, ret);
}

// Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)
static void wren_tile_map_prop(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  char* name = (char*)string_arg(vm, 2);
  TilemapProp* ret = tile_map_prop(tilemap, name);
  tilemapprop_ret(vm, ret);
}

// Get the number of custom properties on a tilemap.
static void wren_tile_map_prop_count(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 ret = tile_map_prop_count(tilemap);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get a custom property of a tilemap, by index (PROP_NONE when out of range.)
static void wren_tile_map_prop_at(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 index = (i32)number_arg(vm, 2);
  TilemapProp* ret = tile_map_prop_at(tilemap, index);
  tilemapprop_ret(vm, ret);
}

// Draw a tilemap on the screen.
static void wren_tile_draw(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  tile_draw(tilemap, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Draw a tilemap on the screen, tinted by a color.
static void wren_tile_draw_tint(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 posX = (i32)number_arg(vm, 2);
  i32 posY = (i32)number_arg(vm, 3);
  Color tint = color_arg(vm, 4);
  tile_draw_tint(tilemap, posX, posY, tint);
  wrenSetSlotNull(vm, 0);
}

// Draw a tilemap on an image.
static void wren_tile_draw_on_image(WrenVM* vm) {
  u32 dst = (u32)number_arg(vm, 1);
  u32 tilemap = (u32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  tile_draw_on_image(dst, tilemap, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Render a whole tilemap to a new image.
static void wren_tilemap_image(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  u32 ret = tilemap_image(tilemap);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.
static void wren_tile_layer_count(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 ret = tile_layer_count(tilemap);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)
static void wren_tile_layer_index(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  char* name = (char*)string_arg(vm, 2);
  i32 ret = tile_layer_index(tilemap, name);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get the name of a layer of a tilemap.
static void wren_tile_layer_name(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  char* ret = tile_layer_name(tilemap, layer);
  string_ret(vm, ret);
}

// Get the kind of a layer of a tilemap.
static void wren_tile_layer_type(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  TileLayerKind ret = tile_layer_type(tilemap, layer);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get the size of a layer of a tilemap, in tiles.
static void wren_tile_layer_size(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  Dimensions* ret = tile_layer_size(tilemap, layer);
  dimensions_ret(vm, ret);
}

// Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.
static void wren_tile_layer_visible(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  bool ret = tile_layer_visible(tilemap, layer);
  wrenSetSlotBool(vm, 0, ret);
}

// Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)
static void wren_tile_layer_prop(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  char* name = (char*)string_arg(vm, 3);
  TilemapProp* ret = tile_layer_prop(tilemap, layer, name);
  tilemapprop_ret(vm, ret);
}

// Get the number of custom properties on a layer of a tilemap.
static void wren_tile_layer_prop_count(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 ret = tile_layer_prop_count(tilemap, layer);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)
static void wren_tile_layer_prop_at(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 index = (i32)number_arg(vm, 3);
  TilemapProp* ret = tile_layer_prop_at(tilemap, layer, index);
  tilemapprop_ret(vm, ret);
}

// Draw a single layer of a tilemap on the screen.
static void wren_tile_draw_layer(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  tile_draw_layer(tilemap, layer, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Draw a single layer of a tilemap on the screen, tinted by a color.
static void wren_tile_draw_layer_tint(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  Color tint = color_arg(vm, 5);
  tile_draw_layer_tint(tilemap, layer, posX, posY, tint);
  wrenSetSlotNull(vm, 0);
}

// Draw a single layer of a tilemap on an image.
static void wren_tile_draw_layer_on_image(WrenVM* vm) {
  u32 dst = (u32)number_arg(vm, 1);
  u32 tilemap = (u32)number_arg(vm, 2);
  i32 layer = (i32)number_arg(vm, 3);
  i32 posX = (i32)number_arg(vm, 4);
  i32 posY = (i32)number_arg(vm, 5);
  tile_draw_layer_on_image(dst, tilemap, layer, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Render a single layer of a tilemap to a new image.
static void wren_tile_layer_image(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  u32 ret = tile_layer_image(tilemap, layer);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get the gid of the tile at a column/row in a tilemap layer.
static void wren_tile_get_tile(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 column = (i32)number_arg(vm, 3);
  i32 row = (i32)number_arg(vm, 4);
  i32 ret = tile_get_tile(tilemap, layer, column, row);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.
static void wren_tile_set_tile(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 column = (i32)number_arg(vm, 3);
  i32 row = (i32)number_arg(vm, 4);
  i32 gid = (i32)number_arg(vm, 5);
  tile_set_tile(tilemap, layer, column, row, gid);
  wrenSetSlotNull(vm, 0);
}

// Draw a single tile from a tilemap on the screen.
static void wren_tile_draw_tile(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 gid = (i32)number_arg(vm, 2);
  i32 posX = (i32)number_arg(vm, 3);
  i32 posY = (i32)number_arg(vm, 4);
  tile_draw_tile(tilemap, gid, posX, posY);
  wrenSetSlotNull(vm, 0);
}

// Get a copy of the image of a single tile in a tilemap.
static void wren_tile_image(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 gid = (i32)number_arg(vm, 2);
  u32 ret = tile_image(tilemap, gid);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.
static void wren_tile_gid_prop(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 gid = (i32)number_arg(vm, 2);
  char* name = (char*)string_arg(vm, 3);
  TilemapProp* ret = tile_gid_prop(tilemap, gid, name);
  tilemapprop_ret(vm, ret);
}

// Get the number of custom properties on a tile of a tilemap.
static void wren_tile_gid_prop_count(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 gid = (i32)number_arg(vm, 2);
  i32 ret = tile_gid_prop_count(tilemap, gid);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)
static void wren_tile_gid_prop_at(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 gid = (i32)number_arg(vm, 2);
  i32 index = (i32)number_arg(vm, 3);
  TilemapProp* ret = tile_gid_prop_at(tilemap, gid, index);
  tilemapprop_ret(vm, ret);
}

// Get the number of objects on an object-layer of a tilemap.
static void wren_tile_object_count(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 ret = tile_object_count(tilemap, layer);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get an object from an object-layer of a tilemap.
static void wren_tile_object(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 index = (i32)number_arg(vm, 3);
  TilemapObject* ret = tile_object(tilemap, layer, index);
  tilemapobject_ret(vm, ret);
}

// Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)
static void wren_tile_object_index(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  char* name = (char*)string_arg(vm, 3);
  i32 ret = tile_object_index(tilemap, layer, name);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)
static void wren_tile_object_prop(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 index = (i32)number_arg(vm, 3);
  char* name = (char*)string_arg(vm, 4);
  TilemapProp* ret = tile_object_prop(tilemap, layer, index, name);
  tilemapprop_ret(vm, ret);
}

// Get the number of custom properties on an object of a tilemap.
static void wren_tile_object_prop_count(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 index = (i32)number_arg(vm, 3);
  i32 ret = tile_object_prop_count(tilemap, layer, index);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)
static void wren_tile_object_prop_at(WrenVM* vm) {
  u32 tilemap = (u32)number_arg(vm, 1);
  i32 layer = (i32)number_arg(vm, 2);
  i32 index = (i32)number_arg(vm, 3);
  i32 propIndex = (i32)number_arg(vm, 4);
  TilemapProp* ret = tile_object_prop_at(tilemap, layer, index, propIndex);
  tilemapprop_ret(vm, ret);
}


// TYPES


// UTILITIES

// Get system-time (ms) since unix epoch.
static void wren_current_time(WrenVM* vm) {
  u64 ret = current_time();
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get the change in time (seconds) since the last update run.
static void wren_delta_time(WrenVM* vm) {
  f32 ret = delta_time();
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get a random integer between 2 numbers.
static void wren_random_int(WrenVM* vm) {
  i32 min = (i32)number_arg(vm, 1);
  i32 max = (i32)number_arg(vm, 2);
  i32 ret = random_int(min, max);
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Get the random-seed.
static void wren_random_seed_get(WrenVM* vm) {
  u64 ret = random_seed_get();
  wrenSetSlotDouble(vm, 0, (double)ret);
}

// Set the random-seed.
static void wren_random_seed_set(WrenVM* vm) {
  u64 seed = (u64)number_arg(vm, 1);
  random_seed_set(seed);
  wrenSetSlotNull(vm, 0);
}

static WrenForeignMethodFn bind_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature) {
  if (strcmp(className, "Null0") != 0) {
    return NULL;
  }
  if (strcmp(signature, "color_tint_(_,_)") == 0) return wren_color_tint;
  if (strcmp(signature, "color_fade_(_,_)") == 0) return wren_color_fade;
  if (strcmp(signature, "color_brightness_(_,_)") == 0) return wren_color_brightness;
  if (strcmp(signature, "color_invert_(_)") == 0) return wren_color_invert;
  if (strcmp(signature, "color_alpha_blend_(_,_)") == 0) return wren_color_alpha_blend;
  if (strcmp(signature, "color_contrast_(_,_)") == 0) return wren_color_contrast;
  if (strcmp(signature, "color_bilinear_interpolate_(_,_,_,_,_,_)") == 0) return wren_color_bilinear_interpolate;
  if (strcmp(signature, "new_image_(_,_,_)") == 0) return wren_new_image;
  if (strcmp(signature, "image_copy_(_)") == 0) return wren_image_copy;
  if (strcmp(signature, "image_subimage_(_,_,_,_,_)") == 0) return wren_image_subimage;
  if (strcmp(signature, "clear_(_)") == 0) return wren_clear;
  if (strcmp(signature, "draw_point_(_,_,_)") == 0) return wren_draw_point;
  if (strcmp(signature, "draw_line_(_,_,_,_,_)") == 0) return wren_draw_line;
  if (strcmp(signature, "draw_rectangle_(_,_,_,_,_)") == 0) return wren_draw_rectangle;
  if (strcmp(signature, "draw_triangle_(_,_,_,_,_,_,_)") == 0) return wren_draw_triangle;
  if (strcmp(signature, "draw_ellipse_(_,_,_,_,_)") == 0) return wren_draw_ellipse;
  if (strcmp(signature, "draw_circle_(_,_,_,_)") == 0) return wren_draw_circle;
  if (strcmp(signature, "draw_polygon_(_,_)") == 0) return wren_draw_polygon;
  if (strcmp(signature, "draw_arc_(_,_,_,_,_,_,_)") == 0) return wren_draw_arc;
  if (strcmp(signature, "draw_rectangle_rounded_(_,_,_,_,_,_)") == 0) return wren_draw_rectangle_rounded;
  if (strcmp(signature, "draw_image_(_,_,_)") == 0) return wren_draw_image;
  if (strcmp(signature, "draw_image_tint_(_,_,_,_)") == 0) return wren_draw_image_tint;
  if (strcmp(signature, "draw_image_rotated_(_,_,_,_,_,_,_)") == 0) return wren_draw_image_rotated;
  if (strcmp(signature, "draw_image_flipped_(_,_,_,_,_,_)") == 0) return wren_draw_image_flipped;
  if (strcmp(signature, "draw_image_scaled_(_,_,_,_,_,_,_,_)") == 0) return wren_draw_image_scaled;
  if (strcmp(signature, "draw_text_(_,_,_,_,_)") == 0) return wren_draw_text;
  if (strcmp(signature, "save_image_(_,_)") == 0) return wren_save_image;
  if (strcmp(signature, "load_image_(_)") == 0) return wren_load_image;
  if (strcmp(signature, "image_resize_(_,_,_,_)") == 0) return wren_image_resize;
  if (strcmp(signature, "image_scale_(_,_,_,_)") == 0) return wren_image_scale;
  if (strcmp(signature, "image_color_replace_(_,_,_)") == 0) return wren_image_color_replace;
  if (strcmp(signature, "image_color_tint_(_,_)") == 0) return wren_image_color_tint;
  if (strcmp(signature, "image_color_fade_(_,_)") == 0) return wren_image_color_fade;
  if (strcmp(signature, "font_copy_(_)") == 0) return wren_font_copy;
  if (strcmp(signature, "font_scale_(_,_,_,_)") == 0) return wren_font_scale;
  if (strcmp(signature, "load_font_bmf_(_,_)") == 0) return wren_load_font_bmf;
  if (strcmp(signature, "load_font_bmf_from_image_(_,_)") == 0) return wren_load_font_bmf_from_image;
  if (strcmp(signature, "measure_text_(_,_,_)") == 0) return wren_measure_text;
  if (strcmp(signature, "measure_image_(_)") == 0) return wren_measure_image;
  if (strcmp(signature, "load_font_tty_(_,_,_,_)") == 0) return wren_load_font_tty;
  if (strcmp(signature, "load_font_tty_from_image_(_,_,_,_)") == 0) return wren_load_font_tty_from_image;
  if (strcmp(signature, "load_font_ttf_(_,_)") == 0) return wren_load_font_ttf;
  if (strcmp(signature, "image_color_invert_(_)") == 0) return wren_image_color_invert;
  if (strcmp(signature, "image_alpha_border_(_,_)") == 0) return wren_image_alpha_border;
  if (strcmp(signature, "image_crop_(_,_,_,_,_)") == 0) return wren_image_crop;
  if (strcmp(signature, "image_alpha_crop_(_,_)") == 0) return wren_image_alpha_crop;
  if (strcmp(signature, "image_color_brightness_(_,_)") == 0) return wren_image_color_brightness;
  if (strcmp(signature, "image_flip_(_,_,_)") == 0) return wren_image_flip;
  if (strcmp(signature, "image_color_contrast_(_,_)") == 0) return wren_image_color_contrast;
  if (strcmp(signature, "image_alpha_mask_(_,_,_,_)") == 0) return wren_image_alpha_mask;
  if (strcmp(signature, "image_rotate_(_,_,_)") == 0) return wren_image_rotate;
  if (strcmp(signature, "image_gradient_(_,_,_,_,_,_)") == 0) return wren_image_gradient;
  if (strcmp(signature, "unload_image_(_)") == 0) return wren_unload_image;
  if (strcmp(signature, "unload_font_(_)") == 0) return wren_unload_font;
  if (strcmp(signature, "clear_image_(_,_)") == 0) return wren_clear_image;
  if (strcmp(signature, "draw_point_on_image_(_,_,_,_)") == 0) return wren_draw_point_on_image;
  if (strcmp(signature, "draw_line_on_image_(_,_,_,_,_,_)") == 0) return wren_draw_line_on_image;
  if (strcmp(signature, "draw_rectangle_on_image_(_,_,_,_,_,_)") == 0) return wren_draw_rectangle_on_image;
  if (strcmp(signature, "draw_triangle_on_image_(_,_,_,_,_,_,_,_)") == 0) return wren_draw_triangle_on_image;
  if (strcmp(signature, "draw_ellipse_on_image_(_,_,_,_,_,_)") == 0) return wren_draw_ellipse_on_image;
  if (strcmp(signature, "draw_circle_on_image_(_,_,_,_,_)") == 0) return wren_draw_circle_on_image;
  if (strcmp(signature, "draw_polygon_on_image_(_,_,_)") == 0) return wren_draw_polygon_on_image;
  if (strcmp(signature, "draw_rectangle_rounded_on_image_(_,_,_,_,_,_,_)") == 0) return wren_draw_rectangle_rounded_on_image;
  if (strcmp(signature, "draw_image_on_image_(_,_,_,_)") == 0) return wren_draw_image_on_image;
  if (strcmp(signature, "draw_image_tint_on_image_(_,_,_,_,_)") == 0) return wren_draw_image_tint_on_image;
  if (strcmp(signature, "draw_image_rotated_on_image_(_,_,_,_,_,_,_,_)") == 0) return wren_draw_image_rotated_on_image;
  if (strcmp(signature, "draw_image_flipped_on_image_(_,_,_,_,_,_,_)") == 0) return wren_draw_image_flipped_on_image;
  if (strcmp(signature, "draw_image_scaled_on_image_(_,_,_,_,_,_,_,_,_)") == 0) return wren_draw_image_scaled_on_image;
  if (strcmp(signature, "draw_text_on_image_(_,_,_,_,_,_)") == 0) return wren_draw_text_on_image;
  if (strcmp(signature, "draw_rectangle_outline_(_,_,_,_,_,_)") == 0) return wren_draw_rectangle_outline;
  if (strcmp(signature, "draw_triangle_outline_(_,_,_,_,_,_,_,_)") == 0) return wren_draw_triangle_outline;
  if (strcmp(signature, "draw_ellipse_outline_(_,_,_,_,_,_)") == 0) return wren_draw_ellipse_outline;
  if (strcmp(signature, "draw_circle_outline_(_,_,_,_,_)") == 0) return wren_draw_circle_outline;
  if (strcmp(signature, "draw_polygon_outline_(_,_,_)") == 0) return wren_draw_polygon_outline;
  if (strcmp(signature, "draw_arc_outline_(_,_,_,_,_,_,_,_)") == 0) return wren_draw_arc_outline;
  if (strcmp(signature, "draw_rectangle_rounded_outline_(_,_,_,_,_,_,_)") == 0) return wren_draw_rectangle_rounded_outline;
  if (strcmp(signature, "draw_rectangle_outline_on_image_(_,_,_,_,_,_,_)") == 0) return wren_draw_rectangle_outline_on_image;
  if (strcmp(signature, "draw_triangle_outline_on_image_(_,_,_,_,_,_,_,_,_)") == 0) return wren_draw_triangle_outline_on_image;
  if (strcmp(signature, "draw_ellipse_outline_on_image_(_,_,_,_,_,_,_)") == 0) return wren_draw_ellipse_outline_on_image;
  if (strcmp(signature, "draw_circle_outline_on_image_(_,_,_,_,_,_)") == 0) return wren_draw_circle_outline_on_image;
  if (strcmp(signature, "draw_polygon_outline_on_image_(_,_,_,_)") == 0) return wren_draw_polygon_outline_on_image;
  if (strcmp(signature, "draw_rectangle_rounded_outline_on_image_(_,_,_,_,_,_,_,_)") == 0) return wren_draw_rectangle_rounded_outline_on_image;
  if (strcmp(signature, "gui_begin_window_(_,_)") == 0) return wren_gui_begin_window;
  if (strcmp(signature, "gui_end_window_") == 0) return wren_gui_end_window;
  if (strcmp(signature, "gui_button_(_)") == 0) return wren_gui_button;
  if (strcmp(signature, "gui_label_(_)") == 0) return wren_gui_label;
  if (strcmp(signature, "gui_text_(_)") == 0) return wren_gui_text;
  if (strcmp(signature, "gui_checkbox_(_,_)") == 0) return wren_gui_checkbox;
  if (strcmp(signature, "gui_slider_(_,_,_)") == 0) return wren_gui_slider;
  if (strcmp(signature, "gui_layout_row_(_,_)") == 0) return wren_gui_layout_row;
  if (strcmp(signature, "gui_end_") == 0) return wren_gui_end;
  if (strcmp(signature, "gui_draw_(_)") == 0) return wren_gui_draw;
  if (strcmp(signature, "key_pressed_(_)") == 0) return wren_key_pressed;
  if (strcmp(signature, "key_down_(_)") == 0) return wren_key_down;
  if (strcmp(signature, "key_released_(_)") == 0) return wren_key_released;
  if (strcmp(signature, "key_up_(_)") == 0) return wren_key_up;
  if (strcmp(signature, "gamepad_button_pressed_(_,_)") == 0) return wren_gamepad_button_pressed;
  if (strcmp(signature, "gamepad_button_down_(_,_)") == 0) return wren_gamepad_button_down;
  if (strcmp(signature, "gamepad_button_released_(_,_)") == 0) return wren_gamepad_button_released;
  if (strcmp(signature, "mouse_position_") == 0) return wren_mouse_position;
  if (strcmp(signature, "mouse_button_pressed_(_)") == 0) return wren_mouse_button_pressed;
  if (strcmp(signature, "mouse_button_down_(_)") == 0) return wren_mouse_button_down;
  if (strcmp(signature, "mouse_button_released_(_)") == 0) return wren_mouse_button_released;
  if (strcmp(signature, "mouse_button_up_(_)") == 0) return wren_mouse_button_up;
  if (strcmp(signature, "load_sound_(_)") == 0) return wren_load_sound;
  if (strcmp(signature, "play_sound_(_,_)") == 0) return wren_play_sound;
  if (strcmp(signature, "stop_sound_(_)") == 0) return wren_stop_sound;
  if (strcmp(signature, "unload_sound_(_)") == 0) return wren_unload_sound;
  if (strcmp(signature, "tts_sound_(_,_,_,_,_,_,_)") == 0) return wren_tts_sound;
  if (strcmp(signature, "sfx_sound_(_)") == 0) return wren_sfx_sound;
  if (strcmp(signature, "sfx_generate_(_)") == 0) return wren_sfx_generate;
  if (strcmp(signature, "load_tilemap_(_)") == 0) return wren_load_tilemap;
  if (strcmp(signature, "unload_tilemap_(_)") == 0) return wren_unload_tilemap;
  if (strcmp(signature, "tile_update_(_,_)") == 0) return wren_tile_update;
  if (strcmp(signature, "tile_map_size_(_)") == 0) return wren_tile_map_size;
  if (strcmp(signature, "tile_tile_size_(_)") == 0) return wren_tile_tile_size;
  if (strcmp(signature, "tile_map_prop_(_,_)") == 0) return wren_tile_map_prop;
  if (strcmp(signature, "tile_map_prop_count_(_)") == 0) return wren_tile_map_prop_count;
  if (strcmp(signature, "tile_map_prop_at_(_,_)") == 0) return wren_tile_map_prop_at;
  if (strcmp(signature, "tile_draw_(_,_,_)") == 0) return wren_tile_draw;
  if (strcmp(signature, "tile_draw_tint_(_,_,_,_)") == 0) return wren_tile_draw_tint;
  if (strcmp(signature, "tile_draw_on_image_(_,_,_,_)") == 0) return wren_tile_draw_on_image;
  if (strcmp(signature, "tilemap_image_(_)") == 0) return wren_tilemap_image;
  if (strcmp(signature, "tile_layer_count_(_)") == 0) return wren_tile_layer_count;
  if (strcmp(signature, "tile_layer_index_(_,_)") == 0) return wren_tile_layer_index;
  if (strcmp(signature, "tile_layer_name_(_,_)") == 0) return wren_tile_layer_name;
  if (strcmp(signature, "tile_layer_type_(_,_)") == 0) return wren_tile_layer_type;
  if (strcmp(signature, "tile_layer_size_(_,_)") == 0) return wren_tile_layer_size;
  if (strcmp(signature, "tile_layer_visible_(_,_)") == 0) return wren_tile_layer_visible;
  if (strcmp(signature, "tile_layer_prop_(_,_,_)") == 0) return wren_tile_layer_prop;
  if (strcmp(signature, "tile_layer_prop_count_(_,_)") == 0) return wren_tile_layer_prop_count;
  if (strcmp(signature, "tile_layer_prop_at_(_,_,_)") == 0) return wren_tile_layer_prop_at;
  if (strcmp(signature, "tile_draw_layer_(_,_,_,_)") == 0) return wren_tile_draw_layer;
  if (strcmp(signature, "tile_draw_layer_tint_(_,_,_,_,_)") == 0) return wren_tile_draw_layer_tint;
  if (strcmp(signature, "tile_draw_layer_on_image_(_,_,_,_,_)") == 0) return wren_tile_draw_layer_on_image;
  if (strcmp(signature, "tile_layer_image_(_,_)") == 0) return wren_tile_layer_image;
  if (strcmp(signature, "tile_get_tile_(_,_,_,_)") == 0) return wren_tile_get_tile;
  if (strcmp(signature, "tile_set_tile_(_,_,_,_,_)") == 0) return wren_tile_set_tile;
  if (strcmp(signature, "tile_draw_tile_(_,_,_,_)") == 0) return wren_tile_draw_tile;
  if (strcmp(signature, "tile_image_(_,_)") == 0) return wren_tile_image;
  if (strcmp(signature, "tile_gid_prop_(_,_,_)") == 0) return wren_tile_gid_prop;
  if (strcmp(signature, "tile_gid_prop_count_(_,_)") == 0) return wren_tile_gid_prop_count;
  if (strcmp(signature, "tile_gid_prop_at_(_,_,_)") == 0) return wren_tile_gid_prop_at;
  if (strcmp(signature, "tile_object_count_(_,_)") == 0) return wren_tile_object_count;
  if (strcmp(signature, "tile_object_(_,_,_)") == 0) return wren_tile_object;
  if (strcmp(signature, "tile_object_index_(_,_,_)") == 0) return wren_tile_object_index;
  if (strcmp(signature, "tile_object_prop_(_,_,_,_)") == 0) return wren_tile_object_prop;
  if (strcmp(signature, "tile_object_prop_count_(_,_,_)") == 0) return wren_tile_object_prop_count;
  if (strcmp(signature, "tile_object_prop_at_(_,_,_,_)") == 0) return wren_tile_object_prop_at;
  if (strcmp(signature, "current_time_") == 0) return wren_current_time;
  if (strcmp(signature, "delta_time_") == 0) return wren_delta_time;
  if (strcmp(signature, "random_int_(_,_)") == 0) return wren_random_int;
  if (strcmp(signature, "random_seed_get_") == 0) return wren_random_seed_get;
  if (strcmp(signature, "random_seed_set_(_)") == 0) return wren_random_seed_set;
  return NULL;
}

// CART

static WrenHandle* call0 = NULL;
static WrenHandle* call1 = NULL;
static WrenHandle* call2 = NULL;
static WrenHandle* cb_buttonUp = NULL;
static WrenHandle* cb_buttonDown = NULL;
static WrenHandle* cb_keyUp = NULL;
static WrenHandle* cb_keyDown = NULL;
static WrenHandle* cb_mouseDown = NULL;
static WrenHandle* cb_mouseUp = NULL;
static WrenHandle* cb_mouseMoved = NULL;
static WrenHandle* cb_update = NULL;
static WrenHandle* cb_unload = NULL;

static void write_fn(WrenVM* vm, const char* text) {
  printf("%s", text);
}

static void error_fn(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message) {
  if (type == WREN_ERROR_STACK_TRACE) {
    printf("  at %s:%d in %s\n", module, line, message);
  } else if (module == NULL) {
    printf("wren: %s\n", message);
  } else {
    printf("wren: %s:%d %s\n", module, line, message);
  }
  fflush(stdout);
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

static void load_module_complete(WrenVM* vm, const char* name, WrenLoadModuleResult result) {
  // the baked-in module is not ours to free
  if (result.source != NULL0_WREN) {
    free((void*)result.source);
  }
}

// `import "null0"` gets the baked-in module, anything else is a file in the cart
static WrenLoadModuleResult load_module(WrenVM* vm, const char* name) {
  WrenLoadModuleResult result = {0};
  if (strcmp(name, "null0") == 0) {
    result.source = NULL0_WREN;
    return result;
  }
  char filename[512];
  snprintf(filename, sizeof(filename), "%s.wren", name);
  result.source = read_file(filename);
  result.onComplete = load_module_complete;
  return result;
}

// callbacks are module-level Fn variables in main.wren
static WrenHandle* get_callback(const char* name) {
  if (!wrenHasVariable(vm, "main", name)) {
    return NULL;
  }
  wrenEnsureSlots(vm, 1);
  wrenGetVariable(vm, "main", name, 0);
  // WREN_TYPE_UNKNOWN is any wren object, so this just skips a var that
  // is obviously not callable (a number, a string, null, ...)
  if (wrenGetSlotType(vm, 0) != WREN_TYPE_UNKNOWN) {
    return NULL;
  }
  return wrenGetSlotHandle(vm, 0);
}

int main() {
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = write_fn;
  config.errorFn = error_fn;
  config.loadModuleFn = load_module;
  config.bindForeignMethodFn = bind_foreign_method;
  vm = wrenNewVM(&config);

  char* source = read_file("main.wren");
  if (source == NULL) {
    printf("wren: no main.wren in cart\n");
    fflush(stdout);
    return 1;
  }

  WrenInterpretResult result = wrenInterpret(vm, "main", source);
  free(source);
  if (result != WREN_RESULT_SUCCESS) {
    fflush(stdout);
    return 1;
  }

  call0 = wrenMakeCallHandle(vm, "call()");
  call1 = wrenMakeCallHandle(vm, "call(_)");
  call2 = wrenMakeCallHandle(vm, "call(_,_)");

  cb_update = get_callback("update");
  cb_unload = get_callback("unload");
  cb_buttonUp = get_callback("buttonUp");
  cb_buttonDown = get_callback("buttonDown");
  cb_keyUp = get_callback("keyUp");
  cb_keyDown = get_callback("keyDown");
  cb_mouseDown = get_callback("mouseDown");
  cb_mouseUp = get_callback("mouseUp");
  cb_mouseMoved = get_callback("mouseMoved");

  // load() is called here, since the host only calls _start on a wasi cart
  WrenHandle* cb_load = get_callback("load");
  if (cb_load != NULL) {
    wrenEnsureSlots(vm, 1);
    wrenSetSlotHandle(vm, 0, cb_load);
    wrenCall(vm, call0);
    wrenReleaseHandle(vm, cb_load);
  }
  fflush(stdout);
  return 0;
}

void update() {
  if (cb_update == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 1);
  wrenSetSlotHandle(vm, 0, cb_update);
  wrenCall(vm, call0);
  fflush(stdout);
}

void unload() {
  if (cb_unload != NULL) {
    wrenEnsureSlots(vm, 1);
    wrenSetSlotHandle(vm, 0, cb_unload);
    wrenCall(vm, call0);
    fflush(stdout);
  }
}

// Mapped controller (keys and gamepad will trigger) callback for when a "button" is unpressed.
void buttonUp(GamepadButton button, u32 player) {
  if (cb_buttonUp == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 3);
  wrenSetSlotHandle(vm, 0, cb_buttonUp);
  wrenSetSlotDouble(vm, 1, (double)button);
  wrenSetSlotDouble(vm, 2, (double)player);
  wrenCall(vm, call2);
  fflush(stdout);
}

// Mapped controller (keys and gamepad will trigger) callback for when a "button" is pressed.
void buttonDown(GamepadButton button, u32 player) {
  if (cb_buttonDown == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 3);
  wrenSetSlotHandle(vm, 0, cb_buttonDown);
  wrenSetSlotDouble(vm, 1, (double)button);
  wrenSetSlotDouble(vm, 2, (double)player);
  wrenCall(vm, call2);
  fflush(stdout);
}

// Called when keys are unpressed.
void keyUp(Key key) {
  if (cb_keyUp == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 2);
  wrenSetSlotHandle(vm, 0, cb_keyUp);
  wrenSetSlotDouble(vm, 1, (double)key);
  wrenCall(vm, call1);
  fflush(stdout);
}

// Called when keys are pressed.
void keyDown(Key key) {
  if (cb_keyDown == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 2);
  wrenSetSlotHandle(vm, 0, cb_keyDown);
  wrenSetSlotDouble(vm, 1, (double)key);
  wrenCall(vm, call1);
  fflush(stdout);
}

// Called when mouse-button is pressed.
void mouseDown(MouseButton button) {
  if (cb_mouseDown == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 2);
  wrenSetSlotHandle(vm, 0, cb_mouseDown);
  wrenSetSlotDouble(vm, 1, (double)button);
  wrenCall(vm, call1);
  fflush(stdout);
}

// Called when mouse-button is released.
void mouseUp(MouseButton button) {
  if (cb_mouseUp == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 2);
  wrenSetSlotHandle(vm, 0, cb_mouseUp);
  wrenSetSlotDouble(vm, 1, (double)button);
  wrenCall(vm, call1);
  fflush(stdout);
}

// Called when mouse is moved.
void mouseMoved(f32 x, f32 y) {
  if (cb_mouseMoved == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 3);
  wrenSetSlotHandle(vm, 0, cb_mouseMoved);
  wrenSetSlotDouble(vm, 1, (double)x);
  wrenSetSlotDouble(vm, 2, (double)y);
  wrenCall(vm, call2);
  fflush(stdout);
}
