// Package null0 provides Go (tinygo) bindings for the null0 fantasy console.
//
// Usage:
//
// ```go
// package main
//
// import null0 "null0"
//
// //export load
// func load() {
//     null0.Clear(null0.BLUE)
//     null0.DrawCircle(100, 100, 50, null0.RED)
// }
//
// func main() {}
// ```
package null0

import "unsafe"

// Image is a handle to an image. 0 is "the screen".
type Image = uint32

// Font is a handle to a font. 0 is "the default font".
type Font = uint32

// Sound is a handle to a sound.
type Sound = uint32

// Tilemap is a handle to a tilemap (a Tiled map, exported as JSON).
type Tilemap = uint32

// NewColor creates a Color from r, g, b, a components.
func NewColor(r, g, b, a uint8) Color {
	return Color{R: r, G: g, B: b, A: a}
}

// RGB creates an opaque Color from r, g, b components.
func RGB(r, g, b uint8) Color {
	return NewColor(r, g, b, 255)
}

// cstr converts a Go string into a null-terminated string pointer.
func cstr(s string) unsafe.Pointer {
	b := append([]byte(s), 0)
	return unsafe.Pointer(&b[0])
}

// ptrToString converts a null-terminated string pointer into a Go string.
func ptrToString(p unsafe.Pointer) string {
	if p == nil {
		return ""
	}
	b := make([]byte, 0, 16)
	for i := uintptr(0); ; i++ {
		c := *(*byte)(unsafe.Add(p, i))
		if c == 0 {
			break
		}
		b = append(b, c)
	}
	return string(b)
}

// Sfx parameters.
type SfxParams struct {
	RandSeed uint32
	WaveType int32
	AttackTime float32
	SustainTime float32
	SustainPunch float32
	DecayTime float32
	StartFrequency float32
	MinFrequency float32
	Slide float32
	DeltaSlide float32
	VibratoDepth float32
	VibratoSpeed float32
	ChangeAmount float32
	ChangeSpeed float32
	SquareDuty float32
	DutySweep float32
	RepeatSpeed float32
	PhaserOffset float32
	PhaserSweep float32
	LpfCutoff float32
	LpfCutoffSweep float32
	LpfResonance float32
	HpfCutoff float32
	HpfCutoffSweep float32
}

// The 2D size of something (width/height.)
type Dimensions struct {
	Width int32
	Height int32
}

// The 2D position of something (x/y.)
type Vector struct {
	X int32
	Y int32
}

// The 2D position + size of something (x/y/w/h.)
type Rectangle struct {
	X int32
	Y int32
	Width int32
	Height int32
}

// An RGBA color.
type Color struct {
	R uint8
	G uint8
	B uint8
	A uint8
}

// Potential image-filtering techniques for scale/etc.
type ImageFilter int32

const (
	FILTER_NEARESTNEIGHBOR ImageFilter = 0
	FILTER_BILINEAR ImageFilter = 1
	FILTER_SMOOTH ImageFilter = 2
)

// Represents a Sfx preset type.
type SfxPresetType int32

const (
	SFX_COIN SfxPresetType = 0
	SFX_LASER SfxPresetType = 1
	SFX_EXPLOSION SfxPresetType = 2
	SFX_POWERUP SfxPresetType = 3
	SFX_HURT SfxPresetType = 4
	SFX_JUMP SfxPresetType = 5
	SFX_SELECT SfxPresetType = 6
	SFX_SYNTH SfxPresetType = 7
)

// Represents a keyboard key.
type Key int32

const (
	KEY_INVALID Key = 0
	KEY_SPACE Key = 32
	KEY_APOSTROPHE Key = 39
	KEY_COMMA Key = 44
	KEY_MINUS Key = 45
	KEY_PERIOD Key = 46
	KEY_SLASH Key = 47
	KEY_0 Key = 48
	KEY_1 Key = 49
	KEY_2 Key = 50
	KEY_3 Key = 51
	KEY_4 Key = 52
	KEY_5 Key = 53
	KEY_6 Key = 54
	KEY_7 Key = 55
	KEY_8 Key = 56
	KEY_9 Key = 57
	KEY_SEMICOLON Key = 59
	KEY_EQUAL Key = 61
	KEY_A Key = 65
	KEY_B Key = 66
	KEY_C Key = 67
	KEY_D Key = 68
	KEY_E Key = 69
	KEY_F Key = 70
	KEY_G Key = 71
	KEY_H Key = 72
	KEY_I Key = 73
	KEY_J Key = 74
	KEY_K Key = 75
	KEY_L Key = 76
	KEY_M Key = 77
	KEY_N Key = 78
	KEY_O Key = 79
	KEY_P Key = 80
	KEY_Q Key = 81
	KEY_R Key = 82
	KEY_S Key = 83
	KEY_T Key = 84
	KEY_U Key = 85
	KEY_V Key = 86
	KEY_W Key = 87
	KEY_X Key = 88
	KEY_Y Key = 89
	KEY_Z Key = 90
	KEY_LEFT_BRACKET Key = 91
	KEY_BACKSLASH Key = 92
	KEY_RIGHT_BRACKET Key = 93
	KEY_GRAVE_ACCENT Key = 96
	KEY_WORLD_1 Key = 161
	KEY_WORLD_2 Key = 162
	KEY_ESCAPE Key = 256
	KEY_ENTER Key = 257
	KEY_TAB Key = 258
	KEY_BACKSPACE Key = 259
	KEY_INSERT Key = 260
	KEY_DELETE Key = 261
	KEY_RIGHT Key = 262
	KEY_LEFT Key = 263
	KEY_DOWN Key = 264
	KEY_UP Key = 265
	KEY_PAGE_UP Key = 266
	KEY_PAGE_DOWN Key = 267
	KEY_HOME Key = 268
	KEY_END Key = 269
	KEY_CAPS_LOCK Key = 280
	KEY_SCROLL_LOCK Key = 281
	KEY_NUM_LOCK Key = 282
	KEY_PRINT_SCREEN Key = 283
	KEY_PAUSE Key = 284
	KEY_F1 Key = 290
	KEY_F2 Key = 291
	KEY_F3 Key = 292
	KEY_F4 Key = 293
	KEY_F5 Key = 294
	KEY_F6 Key = 295
	KEY_F7 Key = 296
	KEY_F8 Key = 297
	KEY_F9 Key = 298
	KEY_F10 Key = 299
	KEY_F11 Key = 300
	KEY_F12 Key = 301
	KEY_F13 Key = 302
	KEY_F14 Key = 303
	KEY_F15 Key = 304
	KEY_F16 Key = 305
	KEY_F17 Key = 306
	KEY_F18 Key = 307
	KEY_F19 Key = 308
	KEY_F20 Key = 309
	KEY_F21 Key = 310
	KEY_F22 Key = 311
	KEY_F23 Key = 312
	KEY_F24 Key = 313
	KEY_F25 Key = 314
	KEY_KP_0 Key = 320
	KEY_KP_1 Key = 321
	KEY_KP_2 Key = 322
	KEY_KP_3 Key = 323
	KEY_KP_4 Key = 324
	KEY_KP_5 Key = 325
	KEY_KP_6 Key = 326
	KEY_KP_7 Key = 327
	KEY_KP_8 Key = 328
	KEY_KP_9 Key = 329
	KEY_KP_DECIMAL Key = 330
	KEY_KP_DIVIDE Key = 331
	KEY_KP_MULTIPLY Key = 332
	KEY_KP_SUBTRACT Key = 333
	KEY_KP_ADD Key = 334
	KEY_KP_ENTER Key = 335
	KEY_KP_EQUAL Key = 336
	KEY_LEFT_SHIFT Key = 340
	KEY_LEFT_CONTROL Key = 341
	KEY_LEFT_ALT Key = 342
	KEY_LEFT_SUPER Key = 343
	KEY_RIGHT_SHIFT Key = 344
	KEY_RIGHT_CONTROL Key = 345
	KEY_RIGHT_ALT Key = 346
	KEY_RIGHT_SUPER Key = 347
	KEY_MENU Key = 348
)

// Represents a gamepad button.
type GamepadButton int32

const (
	GAMEPAD_BUTTON_UNKNOWN GamepadButton = 0
	GAMEPAD_BUTTON_UP GamepadButton = 1
	GAMEPAD_BUTTON_RIGHT GamepadButton = 2
	GAMEPAD_BUTTON_DOWN GamepadButton = 3
	GAMEPAD_BUTTON_LEFT GamepadButton = 4
	GAMEPAD_BUTTON_Y GamepadButton = 5
	GAMEPAD_BUTTON_B GamepadButton = 6
	GAMEPAD_BUTTON_A GamepadButton = 7
	GAMEPAD_BUTTON_X GamepadButton = 8
	GAMEPAD_BUTTON_LEFT_SHOULDER GamepadButton = 9
	GAMEPAD_BUTTON_LEFT_TRIGGER GamepadButton = 10
	GAMEPAD_BUTTON_RIGHT_SHOULDER GamepadButton = 11
	GAMEPAD_BUTTON_RIGHT_TRIGGER GamepadButton = 12
	GAMEPAD_BUTTON_SELECT GamepadButton = 13
	GAMEPAD_BUTTON_MENU GamepadButton = 14
	GAMEPAD_BUTTON_START GamepadButton = 15
	GAMEPAD_BUTTON_LEFT_THUMB GamepadButton = 16
	GAMEPAD_BUTTON_RIGHT_THUMB GamepadButton = 17
)

// Represents a mouse button.
type MouseButton int32

const (
	MOUSE_BUTTON_UNKNOWN MouseButton = 0
	MOUSE_BUTTON_LEFT MouseButton = 1
	MOUSE_BUTTON_RIGHT MouseButton = 2
	MOUSE_BUTTON_MIDDLE MouseButton = 3
)

// Constants
const (
	SCREEN Image = 0
	SCREEN_WIDTH int32 = 640
	SCREEN_HEIGHT int32 = 480
	FONT_DEFAULT Font = 0
)

// Colors
var (
	LIGHTGRAY = Color{R: 200, G: 200, B: 200, A: 255}
	GRAY = Color{R: 130, G: 130, B: 130, A: 255}
	DARKGRAY = Color{R: 80, G: 80, B: 80, A: 255}
	YELLOW = Color{R: 253, G: 249, B: 0, A: 255}
	GOLD = Color{R: 255, G: 203, B: 0, A: 255}
	ORANGE = Color{R: 255, G: 161, B: 0, A: 255}
	PINK = Color{R: 255, G: 109, B: 194, A: 255}
	RED = Color{R: 230, G: 41, B: 55, A: 255}
	MAROON = Color{R: 190, G: 33, B: 55, A: 255}
	GREEN = Color{R: 0, G: 228, B: 48, A: 255}
	LIME = Color{R: 0, G: 158, B: 47, A: 255}
	DARKGREEN = Color{R: 0, G: 117, B: 44, A: 255}
	SKYBLUE = Color{R: 102, G: 191, B: 255, A: 255}
	BLUE = Color{R: 0, G: 121, B: 241, A: 255}
	DARKBLUE = Color{R: 0, G: 82, B: 172, A: 255}
	PURPLE = Color{R: 200, G: 122, B: 255, A: 255}
	VIOLET = Color{R: 135, G: 60, B: 190, A: 255}
	DARKPURPLE = Color{R: 112, G: 31, B: 126, A: 255}
	BEIGE = Color{R: 211, G: 176, B: 131, A: 255}
	BROWN = Color{R: 127, G: 106, B: 79, A: 255}
	DARKBROWN = Color{R: 76, G: 63, B: 47, A: 255}
	WHITE = Color{R: 255, G: 255, B: 255, A: 255}
	BLACK = Color{R: 0, G: 0, B: 0, A: 255}
	BLANK = Color{R: 0, G: 0, B: 0, A: 0}
	MAGENTA = Color{R: 255, G: 0, B: 255, A: 255}
	RAYWHITE = Color{R: 245, G: 245, B: 245, A: 255}
)

// helpers used by wrappers

func boolToUint32(b bool) uint32 {
	if b {
		return 1
	}
	return 0
}

func vectorSliceToPtr(vectors []Vector) unsafe.Pointer {
	if len(vectors) == 0 {
		return nil
	}
	return unsafe.Pointer(&vectors[0])
}

// COLORS

//go:wasmimport null0 color_tint
func color_tint(color unsafe.Pointer, tint unsafe.Pointer) unsafe.Pointer

// ColorTint: Tint a color with another color.
func ColorTint(color Color, tint Color) Color {
	return *(*Color)(color_tint(unsafe.Pointer(&color), unsafe.Pointer(&tint)))
}

//go:wasmimport null0 color_fade
func color_fade(color unsafe.Pointer, alpha float32) unsafe.Pointer

// ColorFade: Fade a color.
func ColorFade(color Color, alpha float32) Color {
	return *(*Color)(color_fade(unsafe.Pointer(&color), alpha))
}

//go:wasmimport null0 color_brightness
func color_brightness(color unsafe.Pointer, factor float32) unsafe.Pointer

// ColorBrightness: Change the brightness of a color.
func ColorBrightness(color Color, factor float32) Color {
	return *(*Color)(color_brightness(unsafe.Pointer(&color), factor))
}

//go:wasmimport null0 color_invert
func color_invert(color unsafe.Pointer) unsafe.Pointer

// ColorInvert: Invert a color.
func ColorInvert(color Color) Color {
	return *(*Color)(color_invert(unsafe.Pointer(&color)))
}

//go:wasmimport null0 color_alpha_blend
func color_alpha_blend(dst unsafe.Pointer, src unsafe.Pointer) unsafe.Pointer

// ColorAlphaBlend: Blend 2 colors together.
func ColorAlphaBlend(dst Color, src Color) Color {
	return *(*Color)(color_alpha_blend(unsafe.Pointer(&dst), unsafe.Pointer(&src)))
}

//go:wasmimport null0 color_contrast
func color_contrast(color unsafe.Pointer, contrast float32) unsafe.Pointer

// ColorContrast: Change contrast of a color.
func ColorContrast(color Color, contrast float32) Color {
	return *(*Color)(color_contrast(unsafe.Pointer(&color), contrast))
}

//go:wasmimport null0 color_bilinear_interpolate
func color_bilinear_interpolate(color00 unsafe.Pointer, color01 unsafe.Pointer, color10 unsafe.Pointer, color11 unsafe.Pointer, coordinateX float32, coordinateY float32) unsafe.Pointer

// ColorBilinearInterpolate: Interpolate colors.
func ColorBilinearInterpolate(color00 Color, color01 Color, color10 Color, color11 Color, coordinateX float32, coordinateY float32) Color {
	return *(*Color)(color_bilinear_interpolate(unsafe.Pointer(&color00), unsafe.Pointer(&color01), unsafe.Pointer(&color10), unsafe.Pointer(&color11), coordinateX, coordinateY))
}

// GRAPHICS

//go:wasmimport null0 new_image
func new_image(width int32, height int32, color unsafe.Pointer) uint32

// NewImage: Create a new blank image.
func NewImage(width int32, height int32, color Color) Image {
	return new_image(width, height, unsafe.Pointer(&color))
}

//go:wasmimport null0 image_copy
func image_copy(image uint32) uint32

// ImageCopy: Copy an image to a new image.
func ImageCopy(image Image) Image {
	return image_copy(image)
}

//go:wasmimport null0 image_subimage
func image_subimage(image uint32, x int32, y int32, width int32, height int32) uint32

// ImageSubimage: Create an image from a region of another image.
func ImageSubimage(image Image, x int32, y int32, width int32, height int32) Image {
	return image_subimage(image, x, y, width, height)
}

//go:wasmimport null0 clear
func clear(color unsafe.Pointer)

// Clear: Clear the screen.
func Clear(color Color) {
	clear(unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_point
func draw_point(x int32, y int32, color unsafe.Pointer)

// DrawPoint: Draw a single pixel on the screen.
func DrawPoint(x int32, y int32, color Color) {
	draw_point(x, y, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_line
func draw_line(startPosX int32, startPosY int32, endPosX int32, endPosY int32, color unsafe.Pointer)

// DrawLine: Draw a line on the screen.
func DrawLine(startPosX int32, startPosY int32, endPosX int32, endPosY int32, color Color) {
	draw_line(startPosX, startPosY, endPosX, endPosY, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle
func draw_rectangle(posX int32, posY int32, width int32, height int32, color unsafe.Pointer)

// DrawRectangle: Draw a filled rectangle on the screen.
func DrawRectangle(posX int32, posY int32, width int32, height int32, color Color) {
	draw_rectangle(posX, posY, width, height, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_triangle
func draw_triangle(x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, color unsafe.Pointer)

// DrawTriangle: Draw a filled triangle on the screen.
func DrawTriangle(x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, color Color) {
	draw_triangle(x1, y1, x2, y2, x3, y3, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_ellipse
func draw_ellipse(centerX int32, centerY int32, radiusX int32, radiusY int32, color unsafe.Pointer)

// DrawEllipse: Draw a filled ellipse on the screen.
func DrawEllipse(centerX int32, centerY int32, radiusX int32, radiusY int32, color Color) {
	draw_ellipse(centerX, centerY, radiusX, radiusY, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_circle
func draw_circle(centerX int32, centerY int32, radius int32, color unsafe.Pointer)

// DrawCircle: Draw a filled circle on the screen.
func DrawCircle(centerX int32, centerY int32, radius int32, color Color) {
	draw_circle(centerX, centerY, radius, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_polygon
func draw_polygon(points unsafe.Pointer, numPoints int32, color unsafe.Pointer)

// DrawPolygon: Draw a filled polygon on the screen.
func DrawPolygon(points []Vector, numPoints int32, color Color) {
	draw_polygon(vectorSliceToPtr(points), numPoints, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_arc
func draw_arc(centerX int32, centerY int32, radius float32, startAngle float32, endAngle float32, segments int32, color unsafe.Pointer)

// DrawArc: Draw a filled arc on the screen.
func DrawArc(centerX int32, centerY int32, radius float32, startAngle float32, endAngle float32, segments int32, color Color) {
	draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle_rounded
func draw_rectangle_rounded(x int32, y int32, width int32, height int32, cornerRadius int32, color unsafe.Pointer)

// DrawRectangleRounded: Draw a filled round-rectangle on the screen.
func DrawRectangleRounded(x int32, y int32, width int32, height int32, cornerRadius int32, color Color) {
	draw_rectangle_rounded(x, y, width, height, cornerRadius, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_image
func draw_image(src uint32, posX int32, posY int32)

// DrawImage: Draw an image on the screen.
func DrawImage(src Image, posX int32, posY int32) {
	draw_image(src, posX, posY)
}

//go:wasmimport null0 draw_image_tint
func draw_image_tint(src uint32, posX int32, posY int32, tint unsafe.Pointer)

// DrawImageTint: Draw a tinted image on the screen.
func DrawImageTint(src Image, posX int32, posY int32, tint Color) {
	draw_image_tint(src, posX, posY, unsafe.Pointer(&tint))
}

//go:wasmimport null0 draw_image_rotated
func draw_image_rotated(src uint32, posX int32, posY int32, degrees float32, offsetX float32, offsetY float32, filter int32)

// DrawImageRotated: Draw an image, rotated, on the screen.
func DrawImageRotated(src Image, posX int32, posY int32, degrees float32, offsetX float32, offsetY float32, filter ImageFilter) {
	draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, int32(filter))
}

//go:wasmimport null0 draw_image_flipped
func draw_image_flipped(src uint32, posX int32, posY int32, flipHorizontal uint32, flipVertical uint32, flipDiagonal uint32)

// DrawImageFlipped: Draw an image, flipped, on the screen.
func DrawImageFlipped(src Image, posX int32, posY int32, flipHorizontal bool, flipVertical bool, flipDiagonal bool) {
	draw_image_flipped(src, posX, posY, boolToUint32(flipHorizontal), boolToUint32(flipVertical), boolToUint32(flipDiagonal))
}

//go:wasmimport null0 draw_image_scaled
func draw_image_scaled(src uint32, posX int32, posY int32, scaleX float32, scaleY float32, offsetX float32, offsetY float32, filter int32)

// DrawImageScaled: Draw an image, scaled, on the screen.
func DrawImageScaled(src Image, posX int32, posY int32, scaleX float32, scaleY float32, offsetX float32, offsetY float32, filter ImageFilter) {
	draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, int32(filter))
}

//go:wasmimport null0 draw_text
func draw_text(font uint32, text unsafe.Pointer, posX int32, posY int32, color unsafe.Pointer)

// DrawText: Draw some text on the screen.
func DrawText(font Font, text string, posX int32, posY int32, color Color) {
	draw_text(font, cstr(text), posX, posY, unsafe.Pointer(&color))
}

//go:wasmimport null0 save_image
func save_image(image uint32, filename unsafe.Pointer)

// SaveImage: Save an image to persistant storage.
func SaveImage(image Image, filename string) {
	save_image(image, cstr(filename))
}

//go:wasmimport null0 load_image
func load_image(filename unsafe.Pointer) uint32

// LoadImage: Load an image from a file in cart.
func LoadImage(filename string) Image {
	return load_image(cstr(filename))
}

//go:wasmimport null0 image_resize
func image_resize(image uint32, newWidth int32, newHeight int32, filter int32) uint32

// ImageResize: Resize an image, return copy.
func ImageResize(image Image, newWidth int32, newHeight int32, filter ImageFilter) Image {
	return image_resize(image, newWidth, newHeight, int32(filter))
}

//go:wasmimport null0 image_scale
func image_scale(image uint32, scaleX float32, scaleY float32, filter int32) uint32

// ImageScale: Scale an image, return copy.
func ImageScale(image Image, scaleX float32, scaleY float32, filter ImageFilter) Image {
	return image_scale(image, scaleX, scaleY, int32(filter))
}

//go:wasmimport null0 image_color_replace
func image_color_replace(image uint32, color unsafe.Pointer, replace unsafe.Pointer)

// ImageColorReplace: Replace a color in an image, in-place.
func ImageColorReplace(image Image, color Color, replace Color) {
	image_color_replace(image, unsafe.Pointer(&color), unsafe.Pointer(&replace))
}

//go:wasmimport null0 image_color_tint
func image_color_tint(image uint32, color unsafe.Pointer)

// ImageColorTint: Tint a color in an image, in-place.
func ImageColorTint(image Image, color Color) {
	image_color_tint(image, unsafe.Pointer(&color))
}

//go:wasmimport null0 image_color_fade
func image_color_fade(image uint32, alpha float32)

// ImageColorFade: Fade a color in an image, in-place.
func ImageColorFade(image Image, alpha float32) {
	image_color_fade(image, alpha)
}

//go:wasmimport null0 font_copy
func font_copy(font uint32) uint32

// FontCopy: Copy a font to a new font.
func FontCopy(font Font) Font {
	return font_copy(font)
}

//go:wasmimport null0 font_scale
func font_scale(font uint32, scaleX float32, scaleY float32, filter int32) uint32

// FontScale: Scale a font, return a new font.
func FontScale(font Font, scaleX float32, scaleY float32, filter ImageFilter) Font {
	return font_scale(font, scaleX, scaleY, int32(filter))
}

//go:wasmimport null0 load_font_bmf
func load_font_bmf(filename unsafe.Pointer, characters unsafe.Pointer) uint32

// LoadFontBmf: Load a BMF font from a file in cart.
func LoadFontBmf(filename string, characters string) Font {
	return load_font_bmf(cstr(filename), cstr(characters))
}

//go:wasmimport null0 load_font_bmf_from_image
func load_font_bmf_from_image(image uint32, characters unsafe.Pointer) uint32

// LoadFontBmfFromImage: Load a BMF font from an image.
func LoadFontBmfFromImage(image Image, characters string) Font {
	return load_font_bmf_from_image(image, cstr(characters))
}

//go:wasmimport null0 measure_text
func measure_text(font uint32, text unsafe.Pointer, textLength int32) unsafe.Pointer

// MeasureText: Measure the size of some text.
func MeasureText(font Font, text string, textLength int32) Dimensions {
	return *(*Dimensions)(measure_text(font, cstr(text), textLength))
}

//go:wasmimport null0 measure_image
func measure_image(image uint32) unsafe.Pointer

// MeasureImage: Meaure an image (use 0 for screen).
func MeasureImage(image Image) Dimensions {
	return *(*Dimensions)(measure_image(image))
}

//go:wasmimport null0 load_font_tty
func load_font_tty(filename unsafe.Pointer, glyphWidth int32, glyphHeight int32, characters unsafe.Pointer) uint32

// LoadFontTty: Load a TTY font from a file in cart.
func LoadFontTty(filename string, glyphWidth int32, glyphHeight int32, characters string) Font {
	return load_font_tty(cstr(filename), glyphWidth, glyphHeight, cstr(characters))
}

//go:wasmimport null0 load_font_tty_from_image
func load_font_tty_from_image(image uint32, glyphWidth int32, glyphHeight int32, characters unsafe.Pointer) uint32

// LoadFontTtyFromImage: Load a TTY font from an image.
func LoadFontTtyFromImage(image Image, glyphWidth int32, glyphHeight int32, characters string) Font {
	return load_font_tty_from_image(image, glyphWidth, glyphHeight, cstr(characters))
}

//go:wasmimport null0 load_font_ttf
func load_font_ttf(filename unsafe.Pointer, fontSize int32) uint32

// LoadFontTtf: Load a TTF font from a file in cart.
func LoadFontTtf(filename string, fontSize int32) Font {
	return load_font_ttf(cstr(filename), fontSize)
}

//go:wasmimport null0 image_color_invert
func image_color_invert(image uint32)

// ImageColorInvert: Invert the colors in an image, in-place.
func ImageColorInvert(image Image) {
	image_color_invert(image)
}

//go:wasmimport null0 image_alpha_border
func image_alpha_border(image uint32, threshold float32) unsafe.Pointer

// ImageAlphaBorder: Calculate a rectangle representing the available alpha border in an image.
func ImageAlphaBorder(image Image, threshold float32) Rectangle {
	return *(*Rectangle)(image_alpha_border(image, threshold))
}

//go:wasmimport null0 image_crop
func image_crop(image uint32, x int32, y int32, width int32, height int32)

// ImageCrop: Crop an image, in-place.
func ImageCrop(image Image, x int32, y int32, width int32, height int32) {
	image_crop(image, x, y, width, height)
}

//go:wasmimport null0 image_alpha_crop
func image_alpha_crop(image uint32, threshold float32)

// ImageAlphaCrop: Crop an image based on the alpha border, in-place.
func ImageAlphaCrop(image Image, threshold float32) {
	image_alpha_crop(image, threshold)
}

//go:wasmimport null0 image_color_brightness
func image_color_brightness(image uint32, factor float32)

// ImageColorBrightness: Adjust the brightness of an image, in-place.
func ImageColorBrightness(image Image, factor float32) {
	image_color_brightness(image, factor)
}

//go:wasmimport null0 image_flip
func image_flip(image uint32, horizontal uint32, vertical uint32)

// ImageFlip: Flip an image, in-place.
func ImageFlip(image Image, horizontal bool, vertical bool) {
	image_flip(image, boolToUint32(horizontal), boolToUint32(vertical))
}

//go:wasmimport null0 image_color_contrast
func image_color_contrast(image uint32, contrast float32)

// ImageColorContrast: Change the contrast of an image, in-place.
func ImageColorContrast(image Image, contrast float32) {
	image_color_contrast(image, contrast)
}

//go:wasmimport null0 image_alpha_mask
func image_alpha_mask(image uint32, alphaMask uint32, posX int32, posY int32)

// ImageAlphaMask: Use an image as an alpha-mask on another image.
func ImageAlphaMask(image Image, alphaMask Image, posX int32, posY int32) {
	image_alpha_mask(image, alphaMask, posX, posY)
}

//go:wasmimport null0 image_rotate
func image_rotate(image uint32, degrees float32, filter int32) uint32

// ImageRotate: Create a new image, rotating another image.
func ImageRotate(image Image, degrees float32, filter ImageFilter) Image {
	return image_rotate(image, degrees, int32(filter))
}

//go:wasmimport null0 image_gradient
func image_gradient(width int32, height int32, topLeft unsafe.Pointer, topRight unsafe.Pointer, bottomLeft unsafe.Pointer, bottomRight unsafe.Pointer) uint32

// ImageGradient: Create a new image of a gradient.
func ImageGradient(width int32, height int32, topLeft Color, topRight Color, bottomLeft Color, bottomRight Color) Image {
	return image_gradient(width, height, unsafe.Pointer(&topLeft), unsafe.Pointer(&topRight), unsafe.Pointer(&bottomLeft), unsafe.Pointer(&bottomRight))
}

//go:wasmimport null0 unload_image
func unload_image(image uint32)

// UnloadImage: Unload an image.
func UnloadImage(image Image) {
	unload_image(image)
}

//go:wasmimport null0 unload_font
func unload_font(font uint32)

// UnloadFont: Unload a font.
func UnloadFont(font Font) {
	unload_font(font)
}

//go:wasmimport null0 clear_image
func clear_image(destination uint32, color unsafe.Pointer)

// ClearImage: Clear an image.
func ClearImage(destination Image, color Color) {
	clear_image(destination, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_point_on_image
func draw_point_on_image(destination uint32, x int32, y int32, color unsafe.Pointer)

// DrawPointOnImage: Draw a single pixel on an image.
func DrawPointOnImage(destination Image, x int32, y int32, color Color) {
	draw_point_on_image(destination, x, y, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_line_on_image
func draw_line_on_image(destination uint32, startPosX int32, startPosY int32, endPosX int32, endPosY int32, color unsafe.Pointer)

// DrawLineOnImage: Draw a line on an image.
func DrawLineOnImage(destination Image, startPosX int32, startPosY int32, endPosX int32, endPosY int32, color Color) {
	draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle_on_image
func draw_rectangle_on_image(destination uint32, posX int32, posY int32, width int32, height int32, color unsafe.Pointer)

// DrawRectangleOnImage: Draw a filled rectangle on an image.
func DrawRectangleOnImage(destination Image, posX int32, posY int32, width int32, height int32, color Color) {
	draw_rectangle_on_image(destination, posX, posY, width, height, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_triangle_on_image
func draw_triangle_on_image(destination uint32, x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, color unsafe.Pointer)

// DrawTriangleOnImage: Draw a filled triangle on an image.
func DrawTriangleOnImage(destination Image, x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, color Color) {
	draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_ellipse_on_image
func draw_ellipse_on_image(destination uint32, centerX int32, centerY int32, radiusX int32, radiusY int32, color unsafe.Pointer)

// DrawEllipseOnImage: Draw a filled ellipse on an image.
func DrawEllipseOnImage(destination Image, centerX int32, centerY int32, radiusX int32, radiusY int32, color Color) {
	draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_circle_on_image
func draw_circle_on_image(destination uint32, centerX int32, centerY int32, radius int32, color unsafe.Pointer)

// DrawCircleOnImage: Draw a circle on an image.
func DrawCircleOnImage(destination Image, centerX int32, centerY int32, radius int32, color Color) {
	draw_circle_on_image(destination, centerX, centerY, radius, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_polygon_on_image
func draw_polygon_on_image(destination uint32, points unsafe.Pointer, numPoints int32, color unsafe.Pointer)

// DrawPolygonOnImage: Draw a filled polygon on an image.
func DrawPolygonOnImage(destination Image, points []Vector, numPoints int32, color Color) {
	draw_polygon_on_image(destination, vectorSliceToPtr(points), numPoints, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle_rounded_on_image
func draw_rectangle_rounded_on_image(destination uint32, x int32, y int32, width int32, height int32, cornerRadius int32, color unsafe.Pointer)

// DrawRectangleRoundedOnImage: Draw a filled round-rectangle on an image.
func DrawRectangleRoundedOnImage(destination Image, x int32, y int32, width int32, height int32, cornerRadius int32, color Color) {
	draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_image_on_image
func draw_image_on_image(destination uint32, src uint32, posX int32, posY int32)

// DrawImageOnImage: Draw an image on an image.
func DrawImageOnImage(destination Image, src Image, posX int32, posY int32) {
	draw_image_on_image(destination, src, posX, posY)
}

//go:wasmimport null0 draw_image_tint_on_image
func draw_image_tint_on_image(destination uint32, src uint32, posX int32, posY int32, tint unsafe.Pointer)

// DrawImageTintOnImage: Draw a tinted image on an image.
func DrawImageTintOnImage(destination Image, src Image, posX int32, posY int32, tint Color) {
	draw_image_tint_on_image(destination, src, posX, posY, unsafe.Pointer(&tint))
}

//go:wasmimport null0 draw_image_rotated_on_image
func draw_image_rotated_on_image(destination uint32, src uint32, posX int32, posY int32, degrees float32, offsetX float32, offsetY float32, filter int32)

// DrawImageRotatedOnImage: Draw an image, rotated, on an image.
func DrawImageRotatedOnImage(destination Image, src Image, posX int32, posY int32, degrees float32, offsetX float32, offsetY float32, filter ImageFilter) {
	draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, int32(filter))
}

//go:wasmimport null0 draw_image_flipped_on_image
func draw_image_flipped_on_image(destination uint32, src uint32, posX int32, posY int32, flipHorizontal uint32, flipVertical uint32, flipDiagonal uint32)

// DrawImageFlippedOnImage: Draw an image, flipped, on an image.
func DrawImageFlippedOnImage(destination Image, src Image, posX int32, posY int32, flipHorizontal bool, flipVertical bool, flipDiagonal bool) {
	draw_image_flipped_on_image(destination, src, posX, posY, boolToUint32(flipHorizontal), boolToUint32(flipVertical), boolToUint32(flipDiagonal))
}

//go:wasmimport null0 draw_image_scaled_on_image
func draw_image_scaled_on_image(destination uint32, src uint32, posX int32, posY int32, scaleX float32, scaleY float32, offsetX float32, offsetY float32, filter int32)

// DrawImageScaledOnImage: Draw an image, scaled, on an image.
func DrawImageScaledOnImage(destination Image, src Image, posX int32, posY int32, scaleX float32, scaleY float32, offsetX float32, offsetY float32, filter ImageFilter) {
	draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, int32(filter))
}

//go:wasmimport null0 draw_text_on_image
func draw_text_on_image(destination uint32, font uint32, text unsafe.Pointer, posX int32, posY int32, color unsafe.Pointer)

// DrawTextOnImage: Draw some text on an image.
func DrawTextOnImage(destination Image, font Font, text string, posX int32, posY int32, color Color) {
	draw_text_on_image(destination, font, cstr(text), posX, posY, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle_outline
func draw_rectangle_outline(posX int32, posY int32, width int32, height int32, thickness int32, color unsafe.Pointer)

// DrawRectangleOutline: Draw a outlined (with thickness) rectangle on the screen.
func DrawRectangleOutline(posX int32, posY int32, width int32, height int32, thickness int32, color Color) {
	draw_rectangle_outline(posX, posY, width, height, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_triangle_outline
func draw_triangle_outline(x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, thickness int32, color unsafe.Pointer)

// DrawTriangleOutline: Draw a outlined (with thickness) triangle on the screen.
func DrawTriangleOutline(x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, thickness int32, color Color) {
	draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_ellipse_outline
func draw_ellipse_outline(centerX int32, centerY int32, radiusX int32, radiusY int32, thickness int32, color unsafe.Pointer)

// DrawEllipseOutline: Draw a outlined (with thickness) ellipse on the screen.
func DrawEllipseOutline(centerX int32, centerY int32, radiusX int32, radiusY int32, thickness int32, color Color) {
	draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_circle_outline
func draw_circle_outline(centerX int32, centerY int32, radius int32, thickness int32, color unsafe.Pointer)

// DrawCircleOutline: Draw a outlined (with thickness) circle on the screen.
func DrawCircleOutline(centerX int32, centerY int32, radius int32, thickness int32, color Color) {
	draw_circle_outline(centerX, centerY, radius, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_polygon_outline
func draw_polygon_outline(points unsafe.Pointer, numPoints int32, thickness int32, color unsafe.Pointer)

// DrawPolygonOutline: Draw a outlined (with thickness) polygon on the screen.
func DrawPolygonOutline(points []Vector, numPoints int32, thickness int32, color Color) {
	draw_polygon_outline(vectorSliceToPtr(points), numPoints, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_arc_outline
func draw_arc_outline(centerX int32, centerY int32, radius float32, startAngle float32, endAngle float32, segments int32, thickness int32, color unsafe.Pointer)

// DrawArcOutline: Draw a outlined (with thickness) arc on the screen.
func DrawArcOutline(centerX int32, centerY int32, radius float32, startAngle float32, endAngle float32, segments int32, thickness int32, color Color) {
	draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle_rounded_outline
func draw_rectangle_rounded_outline(x int32, y int32, width int32, height int32, cornerRadius int32, thickness int32, color unsafe.Pointer)

// DrawRectangleRoundedOutline: Draw a outlined (with thickness) round-rectangle on the screen.
func DrawRectangleRoundedOutline(x int32, y int32, width int32, height int32, cornerRadius int32, thickness int32, color Color) {
	draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle_outline_on_image
func draw_rectangle_outline_on_image(destination uint32, posX int32, posY int32, width int32, height int32, thickness int32, color unsafe.Pointer)

// DrawRectangleOutlineOnImage: Draw a outlined (with thickness) rectangle on an image.
func DrawRectangleOutlineOnImage(destination Image, posX int32, posY int32, width int32, height int32, thickness int32, color Color) {
	draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_triangle_outline_on_image
func draw_triangle_outline_on_image(destination uint32, x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, thickness int32, color unsafe.Pointer)

// DrawTriangleOutlineOnImage: Draw a outlined (with thickness) triangle on an image.
func DrawTriangleOutlineOnImage(destination Image, x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, thickness int32, color Color) {
	draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_ellipse_outline_on_image
func draw_ellipse_outline_on_image(destination uint32, centerX int32, centerY int32, radiusX int32, radiusY int32, thickness int32, color unsafe.Pointer)

// DrawEllipseOutlineOnImage: Draw a outlined (with thickness) ellipse on an image.
func DrawEllipseOutlineOnImage(destination Image, centerX int32, centerY int32, radiusX int32, radiusY int32, thickness int32, color Color) {
	draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_circle_outline_on_image
func draw_circle_outline_on_image(destination uint32, centerX int32, centerY int32, radius int32, thickness int32, color unsafe.Pointer)

// DrawCircleOutlineOnImage: Draw a outlined (with thickness) circle on an image.
func DrawCircleOutlineOnImage(destination Image, centerX int32, centerY int32, radius int32, thickness int32, color Color) {
	draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_polygon_outline_on_image
func draw_polygon_outline_on_image(destination uint32, points unsafe.Pointer, numPoints int32, thickness int32, color unsafe.Pointer)

// DrawPolygonOutlineOnImage: Draw a outlined (with thickness) polygon on an image.
func DrawPolygonOutlineOnImage(destination Image, points []Vector, numPoints int32, thickness int32, color Color) {
	draw_polygon_outline_on_image(destination, vectorSliceToPtr(points), numPoints, thickness, unsafe.Pointer(&color))
}

//go:wasmimport null0 draw_rectangle_rounded_outline_on_image
func draw_rectangle_rounded_outline_on_image(destination uint32, x int32, y int32, width int32, height int32, cornerRadius int32, thickness int32, color unsafe.Pointer)

// DrawRectangleRoundedOutlineOnImage: Draw a outlined (with thickness) round-rectangle on an image.
func DrawRectangleRoundedOutlineOnImage(destination Image, x int32, y int32, width int32, height int32, cornerRadius int32, thickness int32, color Color) {
	draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, unsafe.Pointer(&color))
}

// INPUT

//go:wasmimport null0 key_pressed
func key_pressed(key int32) uint32

// KeyPressed: Has the key been pressed? (tracks unpress/read correctly.)
func KeyPressed(key Key) bool {
	return key_pressed(int32(key)) != 0
}

//go:wasmimport null0 key_down
func key_down(key int32) uint32

// KeyDown: Is the key currently down?
func KeyDown(key Key) bool {
	return key_down(int32(key)) != 0
}

//go:wasmimport null0 key_released
func key_released(key int32) uint32

// KeyReleased: Has the key been released? (tracks press/read correctly.)
func KeyReleased(key Key) bool {
	return key_released(int32(key)) != 0
}

//go:wasmimport null0 key_up
func key_up(key int32) uint32

// KeyUp: Is the key currently up?
func KeyUp(key Key) bool {
	return key_up(int32(key)) != 0
}

//go:wasmimport null0 gamepad_button_pressed
func gamepad_button_pressed(gamepad int32, button int32) uint32

// GamepadButtonPressed: Has the button been pressed? (tracks unpress/read correctly.)
func GamepadButtonPressed(gamepad int32, button GamepadButton) bool {
	return gamepad_button_pressed(gamepad, int32(button)) != 0
}

//go:wasmimport null0 gamepad_button_down
func gamepad_button_down(gamepad int32, button int32) uint32

// GamepadButtonDown: Is the button currently down?
func GamepadButtonDown(gamepad int32, button GamepadButton) bool {
	return gamepad_button_down(gamepad, int32(button)) != 0
}

//go:wasmimport null0 gamepad_button_released
func gamepad_button_released(gamepad int32, button int32) uint32

// GamepadButtonReleased: Has the button been released? (tracks press/read correctly.)
func GamepadButtonReleased(gamepad int32, button GamepadButton) bool {
	return gamepad_button_released(gamepad, int32(button)) != 0
}

//go:wasmimport null0 mouse_position
func mouse_position() unsafe.Pointer

// MousePosition: Get current position of mouse.
func MousePosition() Vector {
	return *(*Vector)(mouse_position())
}

//go:wasmimport null0 mouse_button_pressed
func mouse_button_pressed(button int32) uint32

// MouseButtonPressed: Has the button been pressed? (tracks unpress/read correctly.)
func MouseButtonPressed(button MouseButton) bool {
	return mouse_button_pressed(int32(button)) != 0
}

//go:wasmimport null0 mouse_button_down
func mouse_button_down(button int32) uint32

// MouseButtonDown: Is the button currently down?
func MouseButtonDown(button MouseButton) bool {
	return mouse_button_down(int32(button)) != 0
}

//go:wasmimport null0 mouse_button_released
func mouse_button_released(button int32) uint32

// MouseButtonReleased: Has the button been released? (tracks press/read correctly.)
func MouseButtonReleased(button MouseButton) bool {
	return mouse_button_released(int32(button)) != 0
}

//go:wasmimport null0 mouse_button_up
func mouse_button_up(button int32) uint32

// MouseButtonUp: Is the button currently up?
func MouseButtonUp(button MouseButton) bool {
	return mouse_button_up(int32(button)) != 0
}

// SOUND

//go:wasmimport null0 load_sound
func load_sound(filename unsafe.Pointer) uint32

// LoadSound: Load a sound from a file in cart.
func LoadSound(filename string) Sound {
	return load_sound(cstr(filename))
}

//go:wasmimport null0 play_sound
func play_sound(sound uint32, loop uint32)

// PlaySound: Play a sound.
func PlaySound(sound Sound, loop bool) {
	play_sound(sound, boolToUint32(loop))
}

//go:wasmimport null0 stop_sound
func stop_sound(sound uint32)

// StopSound: Stop a sound.
func StopSound(sound Sound) {
	stop_sound(sound)
}

//go:wasmimport null0 unload_sound
func unload_sound(sound uint32)

// UnloadSound: Unload a sound.
func UnloadSound(sound Sound) {
	unload_sound(sound)
}

//go:wasmimport null0 tts_sound
func tts_sound(text unsafe.Pointer, phonetic uint32, pitch int32, speed int32, throat int32, mouth int32, sing uint32) uint32

// TtsSound: Speak some text and return a sound. Set things to 0 for defaults.
func TtsSound(text string, phonetic bool, pitch int32, speed int32, throat int32, mouth int32, sing bool) Sound {
	return tts_sound(cstr(text), boolToUint32(phonetic), pitch, speed, throat, mouth, boolToUint32(sing))
}

//go:wasmimport null0 sfx_sound
func sfx_sound(params unsafe.Pointer) uint32

// SfxSound: Create Sfx sound.
func SfxSound(params SfxParams) Sound {
	return sfx_sound(unsafe.Pointer(&params))
}

//go:wasmimport null0 sfx_generate
func sfx_generate(type_ int32) unsafe.Pointer

// SfxGenerate: Create Sfx parameters.
func SfxGenerate(type_ SfxPresetType) SfxParams {
	return *(*SfxParams)(sfx_generate(int32(type_)))
}

// TILE

//go:wasmimport null0 load_tilemap
func load_tilemap(filename unsafe.Pointer) uint32

// LoadTilemap: Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
func LoadTilemap(filename string) Tilemap {
	return load_tilemap(cstr(filename))
}

//go:wasmimport null0 unload_tilemap
func unload_tilemap(tilemap uint32)

// UnloadTilemap: Unload a tilemap.
func UnloadTilemap(tilemap Tilemap) {
	unload_tilemap(tilemap)
}

//go:wasmimport null0 tile_update
func tile_update(tilemap uint32, deltaTime float32)

// TileUpdate: Update a tilemap's animation timers (deltaTime is in seconds).
func TileUpdate(tilemap Tilemap, deltaTime float32) {
	tile_update(tilemap, deltaTime)
}

//go:wasmimport null0 tile_draw
func tile_draw(tilemap uint32, posX int32, posY int32)

// TileDraw: Draw a tilemap on the screen.
func TileDraw(tilemap Tilemap, posX int32, posY int32) {
	tile_draw(tilemap, posX, posY)
}

//go:wasmimport null0 tile_draw_tint
func tile_draw_tint(tilemap uint32, posX int32, posY int32, tint unsafe.Pointer)

// TileDrawTint: Draw a tilemap on the screen, tinted by a color.
func TileDrawTint(tilemap Tilemap, posX int32, posY int32, tint Color) {
	tile_draw_tint(tilemap, posX, posY, unsafe.Pointer(&tint))
}

//go:wasmimport null0 tile_draw_on_image
func tile_draw_on_image(dst uint32, tilemap uint32, posX int32, posY int32)

// TileDrawOnImage: Draw a tilemap on an image.
func TileDrawOnImage(dst Image, tilemap Tilemap, posX int32, posY int32) {
	tile_draw_on_image(dst, tilemap, posX, posY)
}

//go:wasmimport null0 tile_draw_tile
func tile_draw_tile(tilemap uint32, gid int32, posX int32, posY int32)

// TileDrawTile: Draw a single tile from a tilemap on the screen.
func TileDrawTile(tilemap Tilemap, gid int32, posX int32, posY int32) {
	tile_draw_tile(tilemap, gid, posX, posY)
}

//go:wasmimport null0 tile_layer_count
func tile_layer_count(tilemap uint32) int32

// TileLayerCount: Get the number of layers in a tilemap.
func TileLayerCount(tilemap Tilemap) int32 {
	return tile_layer_count(tilemap)
}

//go:wasmimport null0 tile_get_tile
func tile_get_tile(tilemap uint32, layer int32, column int32, row int32) int32

// TileGetTile: Get the gid of the tile at a column/row in a tilemap layer.
func TileGetTile(tilemap Tilemap, layer int32, column int32, row int32) int32 {
	return tile_get_tile(tilemap, layer, column, row)
}

//go:wasmimport null0 tile_set_tile
func tile_set_tile(tilemap uint32, layer int32, column int32, row int32, gid int32)

// TileSetTile: Set the gid of the tile at a column/row in a tilemap layer.
func TileSetTile(tilemap Tilemap, layer int32, column int32, row int32, gid int32) {
	tile_set_tile(tilemap, layer, column, row, gid)
}

//go:wasmimport null0 tile_image
func tile_image(tilemap uint32, gid int32) uint32

// TileImage: Get a copy of the image of a single tile in a tilemap.
func TileImage(tilemap Tilemap, gid int32) Image {
	return tile_image(tilemap, gid)
}

//go:wasmimport null0 tilemap_image
func tilemap_image(tilemap uint32) uint32

// TilemapImage: Render a whole tilemap to a new image.
func TilemapImage(tilemap Tilemap) Image {
	return tilemap_image(tilemap)
}

// TYPES

// UTILITIES

//go:wasmimport null0 current_time
func current_time() uint64

// CurrentTime: Get system-time (ms) since unix epoch.
func CurrentTime() uint64 {
	return current_time()
}

//go:wasmimport null0 delta_time
func delta_time() float32

// DeltaTime: Get the change in time (seconds) since the last update run.
func DeltaTime() float32 {
	return delta_time()
}

//go:wasmimport null0 random_int
func random_int(min int32, max int32) int32

// RandomInt: Get a random integer between 2 numbers.
func RandomInt(min int32, max int32) int32 {
	return random_int(min, max)
}

//go:wasmimport null0 random_seed_get
func random_seed_get() uint64

// RandomSeedGet: Get the random-seed.
func RandomSeedGet() uint64 {
	return random_seed_get()
}

//go:wasmimport null0 random_seed_set
func random_seed_set(seed uint64)

// RandomSeedSet: Set the random-seed.
func RandomSeedSet(seed uint64) {
	random_seed_set(seed)
}
