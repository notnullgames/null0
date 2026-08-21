// null0 - Wren bindings for the null0 fantasy console
//
// GENERATED FILE - do not edit by hand. See tools/gen_cart_wren.js
//
// This module is baked into the wren cart-runtime, so carts can just do:
//
// ```wren
// import "null0" for Null0, BLUE, RED
//
// var load = Fn.new {
//   Null0.clear(BLUE)
//   Null0.draw_circle(100, 100, 50, RED)
// }
// ```
//
// Callbacks (load/update/unload/buttonUp/buttonDown/keyUp/keyDown/mouseUp/
// mouseDown/mouseMoved) are module-level Fn variables, in main.wren.

// An RGBA color.
class Color {
  construct new(r, g, b) {
    _r = r
    _g = g
    _b = b
    _a = 255
  }

  construct new(r, g, b, a) {
    _r = r
    _g = g
    _b = b
    _a = a
  }

  // Create a Color from a packed rgba number
  static fromValue(v) { Color.new((v >> 24) & 0xff, (v >> 16) & 0xff, (v >> 8) & 0xff, v & 0xff) }

  r { _r }
  r=(v) { _r = v }
  g { _g }
  g=(v) { _g = v }
  b { _b }
  b=(v) { _b = v }
  a { _a }
  a=(v) { _a = v }

  // The color as a single packed rgba number
  value { ((_r & 0xff) << 24) | ((_g & 0xff) << 16) | ((_b & 0xff) << 8) | (_a & 0xff) }

  ==(other) { other is Color && value == other.value }
  !=(other) { !(this == other) }
  toString { "Color(%(_r), %(_g), %(_b), %(_a))" }
}

// The 2D position of something (x/y.)
class Vector {
  construct new(x, y) {
    _x = x
    _y = y
  }

  // Create a Vector from a list of its members
  static fromList(l) { Vector.new(l[0], l[1]) }

  x { _x }
  x=(v) { _x = v }
  y { _y }
  y=(v) { _y = v }

  // The members, in the order the null0 API wants them
  toList { [_x, _y] }

  toString { "Vector(%(_x), %(_y))" }
}

// The 2D position + size of something (x/y/w/h.)
class Rectangle {
  construct new(x, y, width, height) {
    _x = x
    _y = y
    _width = width
    _height = height
  }

  // Create a Rectangle from a list of its members
  static fromList(l) { Rectangle.new(l[0], l[1], l[2], l[3]) }

  x { _x }
  x=(v) { _x = v }
  y { _y }
  y=(v) { _y = v }
  width { _width }
  width=(v) { _width = v }
  height { _height }
  height=(v) { _height = v }

  // The members, in the order the null0 API wants them
  toList { [_x, _y, _width, _height] }

  toString { "Rectangle(%(_x), %(_y), %(_width), %(_height))" }
}

// The 2D size of something (width/height.)
class Dimensions {
  construct new(width, height) {
    _width = width
    _height = height
  }

  // Create a Dimensions from a list of its members
  static fromList(l) { Dimensions.new(l[0], l[1]) }

  width { _width }
  width=(v) { _width = v }
  height { _height }
  height=(v) { _height = v }

  // The members, in the order the null0 API wants them
  toList { [_width, _height] }

  toString { "Dimensions(%(_width), %(_height))" }
}

// Sfx parameters.
class SfxParams {
  // Every member starts at 0 - fill them in with the setters, or
  // start from Null0.sfx_generate(SFX_COIN) and tweak it
  construct new() {
    _randSeed = 0
    _waveType = 0
    _attackTime = 0
    _sustainTime = 0
    _sustainPunch = 0
    _decayTime = 0
    _startFrequency = 0
    _minFrequency = 0
    _slide = 0
    _deltaSlide = 0
    _vibratoDepth = 0
    _vibratoSpeed = 0
    _changeAmount = 0
    _changeSpeed = 0
    _squareDuty = 0
    _dutySweep = 0
    _repeatSpeed = 0
    _phaserOffset = 0
    _phaserSweep = 0
    _lpfCutoff = 0
    _lpfCutoffSweep = 0
    _lpfResonance = 0
    _hpfCutoff = 0
    _hpfCutoffSweep = 0
  }

  // Create a SfxParams from a list of its members
  static fromList(l) {
    var value = SfxParams.new()
    value.randSeed = l[0]
    value.waveType = l[1]
    value.attackTime = l[2]
    value.sustainTime = l[3]
    value.sustainPunch = l[4]
    value.decayTime = l[5]
    value.startFrequency = l[6]
    value.minFrequency = l[7]
    value.slide = l[8]
    value.deltaSlide = l[9]
    value.vibratoDepth = l[10]
    value.vibratoSpeed = l[11]
    value.changeAmount = l[12]
    value.changeSpeed = l[13]
    value.squareDuty = l[14]
    value.dutySweep = l[15]
    value.repeatSpeed = l[16]
    value.phaserOffset = l[17]
    value.phaserSweep = l[18]
    value.lpfCutoff = l[19]
    value.lpfCutoffSweep = l[20]
    value.lpfResonance = l[21]
    value.hpfCutoff = l[22]
    value.hpfCutoffSweep = l[23]
    return value
  }

  randSeed { _randSeed }
  randSeed=(v) { _randSeed = v }
  waveType { _waveType }
  waveType=(v) { _waveType = v }
  attackTime { _attackTime }
  attackTime=(v) { _attackTime = v }
  sustainTime { _sustainTime }
  sustainTime=(v) { _sustainTime = v }
  sustainPunch { _sustainPunch }
  sustainPunch=(v) { _sustainPunch = v }
  decayTime { _decayTime }
  decayTime=(v) { _decayTime = v }
  startFrequency { _startFrequency }
  startFrequency=(v) { _startFrequency = v }
  minFrequency { _minFrequency }
  minFrequency=(v) { _minFrequency = v }
  slide { _slide }
  slide=(v) { _slide = v }
  deltaSlide { _deltaSlide }
  deltaSlide=(v) { _deltaSlide = v }
  vibratoDepth { _vibratoDepth }
  vibratoDepth=(v) { _vibratoDepth = v }
  vibratoSpeed { _vibratoSpeed }
  vibratoSpeed=(v) { _vibratoSpeed = v }
  changeAmount { _changeAmount }
  changeAmount=(v) { _changeAmount = v }
  changeSpeed { _changeSpeed }
  changeSpeed=(v) { _changeSpeed = v }
  squareDuty { _squareDuty }
  squareDuty=(v) { _squareDuty = v }
  dutySweep { _dutySweep }
  dutySweep=(v) { _dutySweep = v }
  repeatSpeed { _repeatSpeed }
  repeatSpeed=(v) { _repeatSpeed = v }
  phaserOffset { _phaserOffset }
  phaserOffset=(v) { _phaserOffset = v }
  phaserSweep { _phaserSweep }
  phaserSweep=(v) { _phaserSweep = v }
  lpfCutoff { _lpfCutoff }
  lpfCutoff=(v) { _lpfCutoff = v }
  lpfCutoffSweep { _lpfCutoffSweep }
  lpfCutoffSweep=(v) { _lpfCutoffSweep = v }
  lpfResonance { _lpfResonance }
  lpfResonance=(v) { _lpfResonance = v }
  hpfCutoff { _hpfCutoff }
  hpfCutoff=(v) { _hpfCutoff = v }
  hpfCutoffSweep { _hpfCutoffSweep }
  hpfCutoffSweep=(v) { _hpfCutoffSweep = v }

  // The members, in the order the null0 API wants them
  toList { [_randSeed, _waveType, _attackTime, _sustainTime, _sustainPunch, _decayTime, _startFrequency, _minFrequency, _slide, _deltaSlide, _vibratoDepth, _vibratoSpeed, _changeAmount, _changeSpeed, _squareDuty, _dutySweep, _repeatSpeed, _phaserOffset, _phaserSweep, _lpfCutoff, _lpfCutoffSweep, _lpfResonance, _hpfCutoff, _hpfCutoffSweep] }

  toString { "SfxParams(%(_randSeed), %(_waveType), %(_attackTime), %(_sustainTime), %(_sustainPunch), %(_decayTime), %(_startFrequency), %(_minFrequency), %(_slide), %(_deltaSlide), %(_vibratoDepth), %(_vibratoSpeed), %(_changeAmount), %(_changeSpeed), %(_squareDuty), %(_dutySweep), %(_repeatSpeed), %(_phaserOffset), %(_phaserSweep), %(_lpfCutoff), %(_lpfCutoffSweep), %(_lpfResonance), %(_hpfCutoff), %(_hpfCutoffSweep))" }
}

// The null0 API
class Null0 {

  // COLORS

  // Tint a color with another color.
  foreign static color_tint_(a0, a1)
  static color_tint(color, tint) { Color.fromValue(color_tint_(color.value, tint.value)) }

  // Fade a color.
  foreign static color_fade_(a0, a1)
  static color_fade(color, alpha) { Color.fromValue(color_fade_(color.value, alpha)) }

  // Change the brightness of a color.
  foreign static color_brightness_(a0, a1)
  static color_brightness(color, factor) { Color.fromValue(color_brightness_(color.value, factor)) }

  // Invert a color.
  foreign static color_invert_(a0)
  static color_invert(color) { Color.fromValue(color_invert_(color.value)) }

  // Blend 2 colors together.
  foreign static color_alpha_blend_(a0, a1)
  static color_alpha_blend(dst, src) { Color.fromValue(color_alpha_blend_(dst.value, src.value)) }

  // Change contrast of a color.
  foreign static color_contrast_(a0, a1)
  static color_contrast(color, contrast) { Color.fromValue(color_contrast_(color.value, contrast)) }

  // Interpolate colors.
  foreign static color_bilinear_interpolate_(a0, a1, a2, a3, a4, a5)
  static color_bilinear_interpolate(color00, color01, color10, color11, coordinateX, coordinateY) { Color.fromValue(color_bilinear_interpolate_(color00.value, color01.value, color10.value, color11.value, coordinateX, coordinateY)) }

  // GRAPHICS

  // Create a new blank image.
  foreign static new_image_(a0, a1, a2)
  static new_image(width, height, color) { new_image_(width, height, color.value) }

  // Copy an image to a new image.
  foreign static image_copy_(a0)
  static image_copy(image) { image_copy_(image) }

  // Create an image from a region of another image.
  foreign static image_subimage_(a0, a1, a2, a3, a4)
  static image_subimage(image, x, y, width, height) { image_subimage_(image, x, y, width, height) }

  // Clear the screen.
  foreign static clear_(a0)
  static clear(color) { clear_(color.value) }

  // Draw a single pixel on the screen.
  foreign static draw_point_(a0, a1, a2)
  static draw_point(x, y, color) { draw_point_(x, y, color.value) }

  // Draw a line on the screen.
  foreign static draw_line_(a0, a1, a2, a3, a4)
  static draw_line(startPosX, startPosY, endPosX, endPosY, color) { draw_line_(startPosX, startPosY, endPosX, endPosY, color.value) }

  // Draw a filled rectangle on the screen.
  foreign static draw_rectangle_(a0, a1, a2, a3, a4)
  static draw_rectangle(posX, posY, width, height, color) { draw_rectangle_(posX, posY, width, height, color.value) }

  // Draw a filled triangle on the screen.
  foreign static draw_triangle_(a0, a1, a2, a3, a4, a5, a6)
  static draw_triangle(x1, y1, x2, y2, x3, y3, color) { draw_triangle_(x1, y1, x2, y2, x3, y3, color.value) }

  // Draw a filled ellipse on the screen.
  foreign static draw_ellipse_(a0, a1, a2, a3, a4)
  static draw_ellipse(centerX, centerY, radiusX, radiusY, color) { draw_ellipse_(centerX, centerY, radiusX, radiusY, color.value) }

  // Draw a filled circle on the screen.
  foreign static draw_circle_(a0, a1, a2, a3)
  static draw_circle(centerX, centerY, radius, color) { draw_circle_(centerX, centerY, radius, color.value) }

  // Draw a filled polygon on the screen.
  foreign static draw_polygon_(a0, a1)
  static draw_polygon(points, color) {
    var flat_points = []
    for (v in points) {
      flat_points.add(v.x)
      flat_points.add(v.y)
    }
    return draw_polygon_(flat_points, color.value)
  }

  // Draw a filled arc on the screen.
  foreign static draw_arc_(a0, a1, a2, a3, a4, a5, a6)
  static draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, color) { draw_arc_(centerX, centerY, radius, startAngle, endAngle, segments, color.value) }

  // Draw a filled round-rectangle on the screen.
  foreign static draw_rectangle_rounded_(a0, a1, a2, a3, a4, a5)
  static draw_rectangle_rounded(x, y, width, height, cornerRadius, color) { draw_rectangle_rounded_(x, y, width, height, cornerRadius, color.value) }

  // Draw an image on the screen.
  foreign static draw_image_(a0, a1, a2)
  static draw_image(src, posX, posY) { draw_image_(src, posX, posY) }

  // Draw a tinted image on the screen.
  foreign static draw_image_tint_(a0, a1, a2, a3)
  static draw_image_tint(src, posX, posY, tint) { draw_image_tint_(src, posX, posY, tint.value) }

  // Draw an image, rotated, on the screen.
  foreign static draw_image_rotated_(a0, a1, a2, a3, a4, a5, a6)
  static draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter) { draw_image_rotated_(src, posX, posY, degrees, offsetX, offsetY, filter) }

  // Draw an image, flipped, on the screen.
  foreign static draw_image_flipped_(a0, a1, a2, a3, a4, a5)
  static draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) { draw_image_flipped_(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) }

  // Draw an image, scaled, on the screen.
  foreign static draw_image_scaled_(a0, a1, a2, a3, a4, a5, a6, a7)
  static draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) { draw_image_scaled_(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) }

  // Draw some text on the screen.
  foreign static draw_text_(a0, a1, a2, a3, a4)
  static draw_text(font, text, posX, posY, color) { draw_text_(font, text, posX, posY, color.value) }

  // Save an image to persistant storage.
  foreign static save_image_(a0, a1)
  static save_image(image, filename) { save_image_(image, filename) }

  // Load an image from a file in cart.
  foreign static load_image_(a0)
  static load_image(filename) { load_image_(filename) }

  // Resize an image, return copy.
  foreign static image_resize_(a0, a1, a2, a3)
  static image_resize(image, newWidth, newHeight, filter) { image_resize_(image, newWidth, newHeight, filter) }

  // Scale an image, return copy.
  foreign static image_scale_(a0, a1, a2, a3)
  static image_scale(image, scaleX, scaleY, filter) { image_scale_(image, scaleX, scaleY, filter) }

  // Replace a color in an image, in-place.
  foreign static image_color_replace_(a0, a1, a2)
  static image_color_replace(image, color, replace) { image_color_replace_(image, color.value, replace.value) }

  // Tint a color in an image, in-place.
  foreign static image_color_tint_(a0, a1)
  static image_color_tint(image, color) { image_color_tint_(image, color.value) }

  // Fade a color in an image, in-place.
  foreign static image_color_fade_(a0, a1)
  static image_color_fade(image, alpha) { image_color_fade_(image, alpha) }

  // Copy a font to a new font.
  foreign static font_copy_(a0)
  static font_copy(font) { font_copy_(font) }

  // Scale a font, return a new font.
  foreign static font_scale_(a0, a1, a2, a3)
  static font_scale(font, scaleX, scaleY, filter) { font_scale_(font, scaleX, scaleY, filter) }

  // Load a BMF font from a file in cart.
  foreign static load_font_bmf_(a0, a1)
  static load_font_bmf(filename, characters) { load_font_bmf_(filename, characters) }

  // Load a BMF font from an image.
  foreign static load_font_bmf_from_image_(a0, a1)
  static load_font_bmf_from_image(image, characters) { load_font_bmf_from_image_(image, characters) }

  // Measure the size of some text.
  foreign static measure_text_(a0, a1, a2)
  static measure_text(font, text, textLength) { Dimensions.fromList(measure_text_(font, text, textLength)) }

  // Meaure an image (use 0 for screen).
  foreign static measure_image_(a0)
  static measure_image(image) { Dimensions.fromList(measure_image_(image)) }

  // Load a TTY font from a file in cart.
  foreign static load_font_tty_(a0, a1, a2, a3)
  static load_font_tty(filename, glyphWidth, glyphHeight, characters) { load_font_tty_(filename, glyphWidth, glyphHeight, characters) }

  // Load a TTY font from an image.
  foreign static load_font_tty_from_image_(a0, a1, a2, a3)
  static load_font_tty_from_image(image, glyphWidth, glyphHeight, characters) { load_font_tty_from_image_(image, glyphWidth, glyphHeight, characters) }

  // Load a TTF font from a file in cart.
  foreign static load_font_ttf_(a0, a1)
  static load_font_ttf(filename, fontSize) { load_font_ttf_(filename, fontSize) }

  // Invert the colors in an image, in-place.
  foreign static image_color_invert_(a0)
  static image_color_invert(image) { image_color_invert_(image) }

  // Calculate a rectangle representing the available alpha border in an image.
  foreign static image_alpha_border_(a0, a1)
  static image_alpha_border(image, threshold) { Rectangle.fromList(image_alpha_border_(image, threshold)) }

  // Crop an image, in-place.
  foreign static image_crop_(a0, a1, a2, a3, a4)
  static image_crop(image, x, y, width, height) { image_crop_(image, x, y, width, height) }

  // Crop an image based on the alpha border, in-place.
  foreign static image_alpha_crop_(a0, a1)
  static image_alpha_crop(image, threshold) { image_alpha_crop_(image, threshold) }

  // Adjust the brightness of an image, in-place.
  foreign static image_color_brightness_(a0, a1)
  static image_color_brightness(image, factor) { image_color_brightness_(image, factor) }

  // Flip an image, in-place.
  foreign static image_flip_(a0, a1, a2)
  static image_flip(image, horizontal, vertical) { image_flip_(image, horizontal, vertical) }

  // Change the contrast of an image, in-place.
  foreign static image_color_contrast_(a0, a1)
  static image_color_contrast(image, contrast) { image_color_contrast_(image, contrast) }

  // Use an image as an alpha-mask on another image.
  foreign static image_alpha_mask_(a0, a1, a2, a3)
  static image_alpha_mask(image, alphaMask, posX, posY) { image_alpha_mask_(image, alphaMask, posX, posY) }

  // Create a new image, rotating another image.
  foreign static image_rotate_(a0, a1, a2)
  static image_rotate(image, degrees, filter) { image_rotate_(image, degrees, filter) }

  // Create a new image of a gradient.
  foreign static image_gradient_(a0, a1, a2, a3, a4, a5)
  static image_gradient(width, height, topLeft, topRight, bottomLeft, bottomRight) { image_gradient_(width, height, topLeft.value, topRight.value, bottomLeft.value, bottomRight.value) }

  // Unload an image.
  foreign static unload_image_(a0)
  static unload_image(image) { unload_image_(image) }

  // Unload a font.
  foreign static unload_font_(a0)
  static unload_font(font) { unload_font_(font) }

  // Clear an image.
  foreign static clear_image_(a0, a1)
  static clear_image(destination, color) { clear_image_(destination, color.value) }

  // Draw a single pixel on an image.
  foreign static draw_point_on_image_(a0, a1, a2, a3)
  static draw_point_on_image(destination, x, y, color) { draw_point_on_image_(destination, x, y, color.value) }

  // Draw a line on an image.
  foreign static draw_line_on_image_(a0, a1, a2, a3, a4, a5)
  static draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, color) { draw_line_on_image_(destination, startPosX, startPosY, endPosX, endPosY, color.value) }

  // Draw a filled rectangle on an image.
  foreign static draw_rectangle_on_image_(a0, a1, a2, a3, a4, a5)
  static draw_rectangle_on_image(destination, posX, posY, width, height, color) { draw_rectangle_on_image_(destination, posX, posY, width, height, color.value) }

  // Draw a filled triangle on an image.
  foreign static draw_triangle_on_image_(a0, a1, a2, a3, a4, a5, a6, a7)
  static draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, color) { draw_triangle_on_image_(destination, x1, y1, x2, y2, x3, y3, color.value) }

  // Draw a filled ellipse on an image.
  foreign static draw_ellipse_on_image_(a0, a1, a2, a3, a4, a5)
  static draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, color) { draw_ellipse_on_image_(destination, centerX, centerY, radiusX, radiusY, color.value) }

  // Draw a circle on an image.
  foreign static draw_circle_on_image_(a0, a1, a2, a3, a4)
  static draw_circle_on_image(destination, centerX, centerY, radius, color) { draw_circle_on_image_(destination, centerX, centerY, radius, color.value) }

  // Draw a filled polygon on an image.
  foreign static draw_polygon_on_image_(a0, a1, a2)
  static draw_polygon_on_image(destination, points, color) {
    var flat_points = []
    for (v in points) {
      flat_points.add(v.x)
      flat_points.add(v.y)
    }
    return draw_polygon_on_image_(destination, flat_points, color.value)
  }

  // Draw a filled round-rectangle on an image.
  foreign static draw_rectangle_rounded_on_image_(a0, a1, a2, a3, a4, a5, a6)
  static draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, color) { draw_rectangle_rounded_on_image_(destination, x, y, width, height, cornerRadius, color.value) }

  // Draw an image on an image.
  foreign static draw_image_on_image_(a0, a1, a2, a3)
  static draw_image_on_image(destination, src, posX, posY) { draw_image_on_image_(destination, src, posX, posY) }

  // Draw a tinted image on an image.
  foreign static draw_image_tint_on_image_(a0, a1, a2, a3, a4)
  static draw_image_tint_on_image(destination, src, posX, posY, tint) { draw_image_tint_on_image_(destination, src, posX, posY, tint.value) }

  // Draw an image, rotated, on an image.
  foreign static draw_image_rotated_on_image_(a0, a1, a2, a3, a4, a5, a6, a7)
  static draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter) { draw_image_rotated_on_image_(destination, src, posX, posY, degrees, offsetX, offsetY, filter) }

  // Draw an image, flipped, on an image.
  foreign static draw_image_flipped_on_image_(a0, a1, a2, a3, a4, a5, a6)
  static draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) { draw_image_flipped_on_image_(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal) }

  // Draw an image, scaled, on an image.
  foreign static draw_image_scaled_on_image_(a0, a1, a2, a3, a4, a5, a6, a7, a8)
  static draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) { draw_image_scaled_on_image_(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter) }

  // Draw some text on an image.
  foreign static draw_text_on_image_(a0, a1, a2, a3, a4, a5)
  static draw_text_on_image(destination, font, text, posX, posY, color) { draw_text_on_image_(destination, font, text, posX, posY, color.value) }

  // Draw a outlined (with thickness) rectangle on the screen.
  foreign static draw_rectangle_outline_(a0, a1, a2, a3, a4, a5)
  static draw_rectangle_outline(posX, posY, width, height, thickness, color) { draw_rectangle_outline_(posX, posY, width, height, thickness, color.value) }

  // Draw a outlined (with thickness) triangle on the screen.
  foreign static draw_triangle_outline_(a0, a1, a2, a3, a4, a5, a6, a7)
  static draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, color) { draw_triangle_outline_(x1, y1, x2, y2, x3, y3, thickness, color.value) }

  // Draw a outlined (with thickness) ellipse on the screen.
  foreign static draw_ellipse_outline_(a0, a1, a2, a3, a4, a5)
  static draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, color) { draw_ellipse_outline_(centerX, centerY, radiusX, radiusY, thickness, color.value) }

  // Draw a outlined (with thickness) circle on the screen.
  foreign static draw_circle_outline_(a0, a1, a2, a3, a4)
  static draw_circle_outline(centerX, centerY, radius, thickness, color) { draw_circle_outline_(centerX, centerY, radius, thickness, color.value) }

  // Draw a outlined (with thickness) polygon on the screen.
  foreign static draw_polygon_outline_(a0, a1, a2)
  static draw_polygon_outline(points, thickness, color) {
    var flat_points = []
    for (v in points) {
      flat_points.add(v.x)
      flat_points.add(v.y)
    }
    return draw_polygon_outline_(flat_points, thickness, color.value)
  }

  // Draw a outlined (with thickness) arc on the screen.
  foreign static draw_arc_outline_(a0, a1, a2, a3, a4, a5, a6, a7)
  static draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color) { draw_arc_outline_(centerX, centerY, radius, startAngle, endAngle, segments, thickness, color.value) }

  // Draw a outlined (with thickness) round-rectangle on the screen.
  foreign static draw_rectangle_rounded_outline_(a0, a1, a2, a3, a4, a5, a6)
  static draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, color) { draw_rectangle_rounded_outline_(x, y, width, height, cornerRadius, thickness, color.value) }

  // Draw a outlined (with thickness) rectangle on an image.
  foreign static draw_rectangle_outline_on_image_(a0, a1, a2, a3, a4, a5, a6)
  static draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, color) { draw_rectangle_outline_on_image_(destination, posX, posY, width, height, thickness, color.value) }

  // Draw a outlined (with thickness) triangle on an image.
  foreign static draw_triangle_outline_on_image_(a0, a1, a2, a3, a4, a5, a6, a7, a8)
  static draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, color) { draw_triangle_outline_on_image_(destination, x1, y1, x2, y2, x3, y3, thickness, color.value) }

  // Draw a outlined (with thickness) ellipse on an image.
  foreign static draw_ellipse_outline_on_image_(a0, a1, a2, a3, a4, a5, a6)
  static draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, color) { draw_ellipse_outline_on_image_(destination, centerX, centerY, radiusX, radiusY, thickness, color.value) }

  // Draw a outlined (with thickness) circle on an image.
  foreign static draw_circle_outline_on_image_(a0, a1, a2, a3, a4, a5)
  static draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, color) { draw_circle_outline_on_image_(destination, centerX, centerY, radius, thickness, color.value) }

  // Draw a outlined (with thickness) polygon on an image.
  foreign static draw_polygon_outline_on_image_(a0, a1, a2, a3)
  static draw_polygon_outline_on_image(destination, points, thickness, color) {
    var flat_points = []
    for (v in points) {
      flat_points.add(v.x)
      flat_points.add(v.y)
    }
    return draw_polygon_outline_on_image_(destination, flat_points, thickness, color.value)
  }

  // Draw a outlined (with thickness) round-rectangle on an image.
  foreign static draw_rectangle_rounded_outline_on_image_(a0, a1, a2, a3, a4, a5, a6, a7)
  static draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, color) { draw_rectangle_rounded_outline_on_image_(destination, x, y, width, height, cornerRadius, thickness, color.value) }

  // INPUT

  // Has the key been pressed? (tracks unpress/read correctly.)
  foreign static key_pressed_(a0)
  static key_pressed(key) { key_pressed_(key) }

  // Is the key currently down?
  foreign static key_down_(a0)
  static key_down(key) { key_down_(key) }

  // Has the key been released? (tracks press/read correctly.)
  foreign static key_released_(a0)
  static key_released(key) { key_released_(key) }

  // Is the key currently up?
  foreign static key_up_(a0)
  static key_up(key) { key_up_(key) }

  // Has the button been pressed? (tracks unpress/read correctly.)
  foreign static gamepad_button_pressed_(a0, a1)
  static gamepad_button_pressed(gamepad, button) { gamepad_button_pressed_(gamepad, button) }

  // Is the button currently down?
  foreign static gamepad_button_down_(a0, a1)
  static gamepad_button_down(gamepad, button) { gamepad_button_down_(gamepad, button) }

  // Has the button been released? (tracks press/read correctly.)
  foreign static gamepad_button_released_(a0, a1)
  static gamepad_button_released(gamepad, button) { gamepad_button_released_(gamepad, button) }

  // Get current position of mouse.
  foreign static mouse_position_
  static mouse_position { Vector.fromList(mouse_position_) }

  // Has the button been pressed? (tracks unpress/read correctly.)
  foreign static mouse_button_pressed_(a0)
  static mouse_button_pressed(button) { mouse_button_pressed_(button) }

  // Is the button currently down?
  foreign static mouse_button_down_(a0)
  static mouse_button_down(button) { mouse_button_down_(button) }

  // Has the button been released? (tracks press/read correctly.)
  foreign static mouse_button_released_(a0)
  static mouse_button_released(button) { mouse_button_released_(button) }

  // Is the button currently up?
  foreign static mouse_button_up_(a0)
  static mouse_button_up(button) { mouse_button_up_(button) }

  // SOUND

  // Load a sound from a file in cart.
  foreign static load_sound_(a0)
  static load_sound(filename) { load_sound_(filename) }

  // Play a sound.
  foreign static play_sound_(a0, a1)
  static play_sound(sound, loop) { play_sound_(sound, loop) }

  // Stop a sound.
  foreign static stop_sound_(a0)
  static stop_sound(sound) { stop_sound_(sound) }

  // Unload a sound.
  foreign static unload_sound_(a0)
  static unload_sound(sound) { unload_sound_(sound) }

  // Speak some text and return a sound. Set things to 0 for defaults.
  foreign static tts_sound_(a0, a1, a2, a3, a4, a5, a6)
  static tts_sound(text, phonetic, pitch, speed, throat, mouth, sing) { tts_sound_(text, phonetic, pitch, speed, throat, mouth, sing) }

  // Create Sfx sound.
  foreign static sfx_sound_(a0)
  static sfx_sound(params) { sfx_sound_(params.toList) }

  // Create Sfx parameters.
  foreign static sfx_generate_(a0)
  static sfx_generate(type) { SfxParams.fromList(sfx_generate_(type)) }

  // TILE

  // Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
  foreign static load_tilemap_(a0)
  static load_tilemap(filename) { load_tilemap_(filename) }

  // Unload a tilemap.
  foreign static unload_tilemap_(a0)
  static unload_tilemap(tilemap) { unload_tilemap_(tilemap) }

  // Update a tilemap's animation timers (deltaTime is in seconds).
  foreign static tile_update_(a0, a1)
  static tile_update(tilemap, deltaTime) { tile_update_(tilemap, deltaTime) }

  // Draw a tilemap on the screen.
  foreign static tile_draw_(a0, a1, a2)
  static tile_draw(tilemap, posX, posY) { tile_draw_(tilemap, posX, posY) }

  // Draw a tilemap on the screen, tinted by a color.
  foreign static tile_draw_tint_(a0, a1, a2, a3)
  static tile_draw_tint(tilemap, posX, posY, tint) { tile_draw_tint_(tilemap, posX, posY, tint.value) }

  // Draw a tilemap on an image.
  foreign static tile_draw_on_image_(a0, a1, a2, a3)
  static tile_draw_on_image(dst, tilemap, posX, posY) { tile_draw_on_image_(dst, tilemap, posX, posY) }

  // Draw a single tile from a tilemap on the screen.
  foreign static tile_draw_tile_(a0, a1, a2, a3)
  static tile_draw_tile(tilemap, gid, posX, posY) { tile_draw_tile_(tilemap, gid, posX, posY) }

  // Get the number of layers in a tilemap.
  foreign static tile_layer_count_(a0)
  static tile_layer_count(tilemap) { tile_layer_count_(tilemap) }

  // Get the gid of the tile at a column/row in a tilemap layer.
  foreign static tile_get_tile_(a0, a1, a2, a3)
  static tile_get_tile(tilemap, layer, column, row) { tile_get_tile_(tilemap, layer, column, row) }

  // Set the gid of the tile at a column/row in a tilemap layer.
  foreign static tile_set_tile_(a0, a1, a2, a3, a4)
  static tile_set_tile(tilemap, layer, column, row, gid) { tile_set_tile_(tilemap, layer, column, row, gid) }

  // Get a copy of the image of a single tile in a tilemap.
  foreign static tile_image_(a0, a1)
  static tile_image(tilemap, gid) { tile_image_(tilemap, gid) }

  // Render a whole tilemap to a new image.
  foreign static tilemap_image_(a0)
  static tilemap_image(tilemap) { tilemap_image_(tilemap) }

  // TYPES

  // UTILITIES

  // Get system-time (ms) since unix epoch.
  foreign static current_time_
  static current_time { current_time_ }

  // Get the change in time (seconds) since the last update run.
  foreign static delta_time_
  static delta_time { delta_time_ }

  // Get a random integer between 2 numbers.
  foreign static random_int_(a0, a1)
  static random_int(min, max) { random_int_(min, max) }

  // Get the random-seed.
  foreign static random_seed_get_
  static random_seed_get { random_seed_get_ }

  // Set the random-seed.
  foreign static random_seed_set_(a0)
  static random_seed_set(seed) { random_seed_set_(seed) }
}

// The screen is image 0
var SCREEN = 0
var SCREEN_WIDTH = 640
var SCREEN_HEIGHT = 480

// The built-in font
var FONT_DEFAULT = 0

// Colors
var LIGHTGRAY = Color.new(200, 200, 200, 255)
var GRAY = Color.new(130, 130, 130, 255)
var DARKGRAY = Color.new(80, 80, 80, 255)
var YELLOW = Color.new(253, 249, 0, 255)
var GOLD = Color.new(255, 203, 0, 255)
var ORANGE = Color.new(255, 161, 0, 255)
var PINK = Color.new(255, 109, 194, 255)
var RED = Color.new(230, 41, 55, 255)
var MAROON = Color.new(190, 33, 55, 255)
var GREEN = Color.new(0, 228, 48, 255)
var LIME = Color.new(0, 158, 47, 255)
var DARKGREEN = Color.new(0, 117, 44, 255)
var SKYBLUE = Color.new(102, 191, 255, 255)
var BLUE = Color.new(0, 121, 241, 255)
var DARKBLUE = Color.new(0, 82, 172, 255)
var PURPLE = Color.new(200, 122, 255, 255)
var VIOLET = Color.new(135, 60, 190, 255)
var DARKPURPLE = Color.new(112, 31, 126, 255)
var BEIGE = Color.new(211, 176, 131, 255)
var BROWN = Color.new(127, 106, 79, 255)
var DARKBROWN = Color.new(76, 63, 47, 255)
var WHITE = Color.new(255, 255, 255, 255)
var BLACK = Color.new(0, 0, 0, 255)
var BLANK = Color.new(0, 0, 0, 0)
var MAGENTA = Color.new(255, 0, 255, 255)
var RAYWHITE = Color.new(245, 245, 245, 255)

// The current tagged version of null0 engine
var NULL0_VERSION = "0.0.8"

// Potential image-filtering techniques for scale/etc.
var FILTER_NEARESTNEIGHBOR = 0
var FILTER_BILINEAR = 1
var FILTER_SMOOTH = 2

// Represents a Sfx preset type.
var SFX_COIN = 0
var SFX_LASER = 1
var SFX_EXPLOSION = 2
var SFX_POWERUP = 3
var SFX_HURT = 4
var SFX_JUMP = 5
var SFX_SELECT = 6
var SFX_SYNTH = 7

// Represents a keyboard key.
var KEY_INVALID = 0
var KEY_SPACE = 32
var KEY_APOSTROPHE = 39
var KEY_COMMA = 44
var KEY_MINUS = 45
var KEY_PERIOD = 46
var KEY_SLASH = 47
var KEY_0 = 48
var KEY_1 = 49
var KEY_2 = 50
var KEY_3 = 51
var KEY_4 = 52
var KEY_5 = 53
var KEY_6 = 54
var KEY_7 = 55
var KEY_8 = 56
var KEY_9 = 57
var KEY_SEMICOLON = 59
var KEY_EQUAL = 61
var KEY_A = 65
var KEY_B = 66
var KEY_C = 67
var KEY_D = 68
var KEY_E = 69
var KEY_F = 70
var KEY_G = 71
var KEY_H = 72
var KEY_I = 73
var KEY_J = 74
var KEY_K = 75
var KEY_L = 76
var KEY_M = 77
var KEY_N = 78
var KEY_O = 79
var KEY_P = 80
var KEY_Q = 81
var KEY_R = 82
var KEY_S = 83
var KEY_T = 84
var KEY_U = 85
var KEY_V = 86
var KEY_W = 87
var KEY_X = 88
var KEY_Y = 89
var KEY_Z = 90
var KEY_LEFT_BRACKET = 91
var KEY_BACKSLASH = 92
var KEY_RIGHT_BRACKET = 93
var KEY_GRAVE_ACCENT = 96
var KEY_WORLD_1 = 161
var KEY_WORLD_2 = 162
var KEY_ESCAPE = 256
var KEY_ENTER = 257
var KEY_TAB = 258
var KEY_BACKSPACE = 259
var KEY_INSERT = 260
var KEY_DELETE = 261
var KEY_RIGHT = 262
var KEY_LEFT = 263
var KEY_DOWN = 264
var KEY_UP = 265
var KEY_PAGE_UP = 266
var KEY_PAGE_DOWN = 267
var KEY_HOME = 268
var KEY_END = 269
var KEY_CAPS_LOCK = 280
var KEY_SCROLL_LOCK = 281
var KEY_NUM_LOCK = 282
var KEY_PRINT_SCREEN = 283
var KEY_PAUSE = 284
var KEY_F1 = 290
var KEY_F2 = 291
var KEY_F3 = 292
var KEY_F4 = 293
var KEY_F5 = 294
var KEY_F6 = 295
var KEY_F7 = 296
var KEY_F8 = 297
var KEY_F9 = 298
var KEY_F10 = 299
var KEY_F11 = 300
var KEY_F12 = 301
var KEY_F13 = 302
var KEY_F14 = 303
var KEY_F15 = 304
var KEY_F16 = 305
var KEY_F17 = 306
var KEY_F18 = 307
var KEY_F19 = 308
var KEY_F20 = 309
var KEY_F21 = 310
var KEY_F22 = 311
var KEY_F23 = 312
var KEY_F24 = 313
var KEY_F25 = 314
var KEY_KP_0 = 320
var KEY_KP_1 = 321
var KEY_KP_2 = 322
var KEY_KP_3 = 323
var KEY_KP_4 = 324
var KEY_KP_5 = 325
var KEY_KP_6 = 326
var KEY_KP_7 = 327
var KEY_KP_8 = 328
var KEY_KP_9 = 329
var KEY_KP_DECIMAL = 330
var KEY_KP_DIVIDE = 331
var KEY_KP_MULTIPLY = 332
var KEY_KP_SUBTRACT = 333
var KEY_KP_ADD = 334
var KEY_KP_ENTER = 335
var KEY_KP_EQUAL = 336
var KEY_LEFT_SHIFT = 340
var KEY_LEFT_CONTROL = 341
var KEY_LEFT_ALT = 342
var KEY_LEFT_SUPER = 343
var KEY_RIGHT_SHIFT = 344
var KEY_RIGHT_CONTROL = 345
var KEY_RIGHT_ALT = 346
var KEY_RIGHT_SUPER = 347
var KEY_MENU = 348

// Represents a gamepad button.
var GAMEPAD_BUTTON_UNKNOWN = 0
var GAMEPAD_BUTTON_UP = 1
var GAMEPAD_BUTTON_RIGHT = 2
var GAMEPAD_BUTTON_DOWN = 3
var GAMEPAD_BUTTON_LEFT = 4
var GAMEPAD_BUTTON_Y = 5
var GAMEPAD_BUTTON_B = 6
var GAMEPAD_BUTTON_A = 7
var GAMEPAD_BUTTON_X = 8
var GAMEPAD_BUTTON_LEFT_SHOULDER = 9
var GAMEPAD_BUTTON_LEFT_TRIGGER = 10
var GAMEPAD_BUTTON_RIGHT_SHOULDER = 11
var GAMEPAD_BUTTON_RIGHT_TRIGGER = 12
var GAMEPAD_BUTTON_SELECT = 13
var GAMEPAD_BUTTON_MENU = 14
var GAMEPAD_BUTTON_START = 15
var GAMEPAD_BUTTON_LEFT_THUMB = 16
var GAMEPAD_BUTTON_RIGHT_THUMB = 17

// Represents a mouse button.
var MOUSE_BUTTON_UNKNOWN = 0
var MOUSE_BUTTON_LEFT = 1
var MOUSE_BUTTON_RIGHT = 2
var MOUSE_BUTTON_MIDDLE = 3
