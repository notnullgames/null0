// GENERATED FILE - do not edit by hand. See tools/gen_cart_lua.js
//
// The lua cart-runtime: a GopherLua VM with the null0 API bound to it. It
// runs main.lua from the cart, then calls the callbacks the cart defined.

package main

import (
	"fmt"
	"os"
	"runtime"
	"unsafe"

	lua "github.com/yuin/gopher-lua"
)

// Sfx parameters.
type SfxParams struct {
	RandSeed       uint32
	WaveType       int32
	AttackTime     float32
	SustainTime    float32
	SustainPunch   float32
	DecayTime      float32
	StartFrequency float32
	MinFrequency   float32
	Slide          float32
	DeltaSlide     float32
	VibratoDepth   float32
	VibratoSpeed   float32
	ChangeAmount   float32
	ChangeSpeed    float32
	SquareDuty     float32
	DutySweep      float32
	RepeatSpeed    float32
	PhaserOffset   float32
	PhaserSweep    float32
	LpfCutoff      float32
	LpfCutoffSweep float32
	LpfResonance   float32
	HpfCutoff      float32
	HpfCutoffSweep float32
}

// The 2D size of something (width/height.)
type Dimensions struct {
	Width  int32
	Height int32
}

// The 2D position of something (x/y.)
type Vector struct {
	X int32
	Y int32
}

// The 2D position + size of something (x/y/w/h.)
type Rectangle struct {
	X      int32
	Y      int32
	Width  int32
	Height int32
}

// An RGBA color.
type Color struct {
	R uint8
	G uint8
	B uint8
	A uint8
}

// HOST FUNCTIONS

//go:wasmimport null0 color_tint
func color_tint(color unsafe.Pointer, tint unsafe.Pointer) unsafe.Pointer

//go:wasmimport null0 color_fade
func color_fade(color unsafe.Pointer, alpha float32) unsafe.Pointer

//go:wasmimport null0 color_brightness
func color_brightness(color unsafe.Pointer, factor float32) unsafe.Pointer

//go:wasmimport null0 color_invert
func color_invert(color unsafe.Pointer) unsafe.Pointer

//go:wasmimport null0 color_alpha_blend
func color_alpha_blend(dst unsafe.Pointer, src unsafe.Pointer) unsafe.Pointer

//go:wasmimport null0 color_contrast
func color_contrast(color unsafe.Pointer, contrast float32) unsafe.Pointer

//go:wasmimport null0 color_bilinear_interpolate
func color_bilinear_interpolate(color00 unsafe.Pointer, color01 unsafe.Pointer, color10 unsafe.Pointer, color11 unsafe.Pointer, coordinateX float32, coordinateY float32) unsafe.Pointer

//go:wasmimport null0 new_image
func new_image(width int32, height int32, color unsafe.Pointer) uint32

//go:wasmimport null0 image_copy
func image_copy(image uint32) uint32

//go:wasmimport null0 image_subimage
func image_subimage(image uint32, x int32, y int32, width int32, height int32) uint32

//go:wasmimport null0 clear
func clear(color unsafe.Pointer)

//go:wasmimport null0 draw_point
func draw_point(x int32, y int32, color unsafe.Pointer)

//go:wasmimport null0 draw_line
func draw_line(startPosX int32, startPosY int32, endPosX int32, endPosY int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle
func draw_rectangle(posX int32, posY int32, width int32, height int32, color unsafe.Pointer)

//go:wasmimport null0 draw_triangle
func draw_triangle(x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, color unsafe.Pointer)

//go:wasmimport null0 draw_ellipse
func draw_ellipse(centerX int32, centerY int32, radiusX int32, radiusY int32, color unsafe.Pointer)

//go:wasmimport null0 draw_circle
func draw_circle(centerX int32, centerY int32, radius int32, color unsafe.Pointer)

//go:wasmimport null0 draw_polygon
func draw_polygon(points unsafe.Pointer, numPoints int32, color unsafe.Pointer)

//go:wasmimport null0 draw_arc
func draw_arc(centerX int32, centerY int32, radius float32, startAngle float32, endAngle float32, segments int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle_rounded
func draw_rectangle_rounded(x int32, y int32, width int32, height int32, cornerRadius int32, color unsafe.Pointer)

//go:wasmimport null0 draw_image
func draw_image(src uint32, posX int32, posY int32)

//go:wasmimport null0 draw_image_tint
func draw_image_tint(src uint32, posX int32, posY int32, tint unsafe.Pointer)

//go:wasmimport null0 draw_image_rotated
func draw_image_rotated(src uint32, posX int32, posY int32, degrees float32, offsetX float32, offsetY float32, filter int32)

//go:wasmimport null0 draw_image_flipped
func draw_image_flipped(src uint32, posX int32, posY int32, flipHorizontal int32, flipVertical int32, flipDiagonal int32)

//go:wasmimport null0 draw_image_scaled
func draw_image_scaled(src uint32, posX int32, posY int32, scaleX float32, scaleY float32, offsetX float32, offsetY float32, filter int32)

//go:wasmimport null0 draw_text
func draw_text(font uint32, text unsafe.Pointer, posX int32, posY int32, color unsafe.Pointer)

//go:wasmimport null0 save_image
func save_image(image uint32, filename unsafe.Pointer)

//go:wasmimport null0 load_image
func load_image(filename unsafe.Pointer) uint32

//go:wasmimport null0 image_resize
func image_resize(image uint32, newWidth int32, newHeight int32, filter int32) uint32

//go:wasmimport null0 image_scale
func image_scale(image uint32, scaleX float32, scaleY float32, filter int32) uint32

//go:wasmimport null0 image_color_replace
func image_color_replace(image uint32, color unsafe.Pointer, replace unsafe.Pointer)

//go:wasmimport null0 image_color_tint
func image_color_tint(image uint32, color unsafe.Pointer)

//go:wasmimport null0 image_color_fade
func image_color_fade(image uint32, alpha float32)

//go:wasmimport null0 font_copy
func font_copy(font uint32) uint32

//go:wasmimport null0 font_scale
func font_scale(font uint32, scaleX float32, scaleY float32, filter int32) uint32

//go:wasmimport null0 load_font_bmf
func load_font_bmf(filename unsafe.Pointer, characters unsafe.Pointer) uint32

//go:wasmimport null0 load_font_bmf_from_image
func load_font_bmf_from_image(image uint32, characters unsafe.Pointer) uint32

//go:wasmimport null0 measure_text
func measure_text(font uint32, text unsafe.Pointer, textLength int32) unsafe.Pointer

//go:wasmimport null0 measure_image
func measure_image(image uint32) unsafe.Pointer

//go:wasmimport null0 load_font_tty
func load_font_tty(filename unsafe.Pointer, glyphWidth int32, glyphHeight int32, characters unsafe.Pointer) uint32

//go:wasmimport null0 load_font_tty_from_image
func load_font_tty_from_image(image uint32, glyphWidth int32, glyphHeight int32, characters unsafe.Pointer) uint32

//go:wasmimport null0 load_font_ttf
func load_font_ttf(filename unsafe.Pointer, fontSize int32) uint32

//go:wasmimport null0 image_color_invert
func image_color_invert(image uint32)

//go:wasmimport null0 image_alpha_border
func image_alpha_border(image uint32, threshold float32) unsafe.Pointer

//go:wasmimport null0 image_crop
func image_crop(image uint32, x int32, y int32, width int32, height int32)

//go:wasmimport null0 image_alpha_crop
func image_alpha_crop(image uint32, threshold float32)

//go:wasmimport null0 image_color_brightness
func image_color_brightness(image uint32, factor float32)

//go:wasmimport null0 image_flip
func image_flip(image uint32, horizontal int32, vertical int32)

//go:wasmimport null0 image_color_contrast
func image_color_contrast(image uint32, contrast float32)

//go:wasmimport null0 image_alpha_mask
func image_alpha_mask(image uint32, alphaMask uint32, posX int32, posY int32)

//go:wasmimport null0 image_rotate
func image_rotate(image uint32, degrees float32, filter int32) uint32

//go:wasmimport null0 image_gradient
func image_gradient(width int32, height int32, topLeft unsafe.Pointer, topRight unsafe.Pointer, bottomLeft unsafe.Pointer, bottomRight unsafe.Pointer) uint32

//go:wasmimport null0 unload_image
func unload_image(image uint32)

//go:wasmimport null0 unload_font
func unload_font(font uint32)

//go:wasmimport null0 clear_image
func clear_image(destination uint32, color unsafe.Pointer)

//go:wasmimport null0 draw_point_on_image
func draw_point_on_image(destination uint32, x int32, y int32, color unsafe.Pointer)

//go:wasmimport null0 draw_line_on_image
func draw_line_on_image(destination uint32, startPosX int32, startPosY int32, endPosX int32, endPosY int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle_on_image
func draw_rectangle_on_image(destination uint32, posX int32, posY int32, width int32, height int32, color unsafe.Pointer)

//go:wasmimport null0 draw_triangle_on_image
func draw_triangle_on_image(destination uint32, x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, color unsafe.Pointer)

//go:wasmimport null0 draw_ellipse_on_image
func draw_ellipse_on_image(destination uint32, centerX int32, centerY int32, radiusX int32, radiusY int32, color unsafe.Pointer)

//go:wasmimport null0 draw_circle_on_image
func draw_circle_on_image(destination uint32, centerX int32, centerY int32, radius int32, color unsafe.Pointer)

//go:wasmimport null0 draw_polygon_on_image
func draw_polygon_on_image(destination uint32, points unsafe.Pointer, numPoints int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle_rounded_on_image
func draw_rectangle_rounded_on_image(destination uint32, x int32, y int32, width int32, height int32, cornerRadius int32, color unsafe.Pointer)

//go:wasmimport null0 draw_image_on_image
func draw_image_on_image(destination uint32, src uint32, posX int32, posY int32)

//go:wasmimport null0 draw_image_tint_on_image
func draw_image_tint_on_image(destination uint32, src uint32, posX int32, posY int32, tint unsafe.Pointer)

//go:wasmimport null0 draw_image_rotated_on_image
func draw_image_rotated_on_image(destination uint32, src uint32, posX int32, posY int32, degrees float32, offsetX float32, offsetY float32, filter int32)

//go:wasmimport null0 draw_image_flipped_on_image
func draw_image_flipped_on_image(destination uint32, src uint32, posX int32, posY int32, flipHorizontal int32, flipVertical int32, flipDiagonal int32)

//go:wasmimport null0 draw_image_scaled_on_image
func draw_image_scaled_on_image(destination uint32, src uint32, posX int32, posY int32, scaleX float32, scaleY float32, offsetX float32, offsetY float32, filter int32)

//go:wasmimport null0 draw_text_on_image
func draw_text_on_image(destination uint32, font uint32, text unsafe.Pointer, posX int32, posY int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle_outline
func draw_rectangle_outline(posX int32, posY int32, width int32, height int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_triangle_outline
func draw_triangle_outline(x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_ellipse_outline
func draw_ellipse_outline(centerX int32, centerY int32, radiusX int32, radiusY int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_circle_outline
func draw_circle_outline(centerX int32, centerY int32, radius int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_polygon_outline
func draw_polygon_outline(points unsafe.Pointer, numPoints int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_arc_outline
func draw_arc_outline(centerX int32, centerY int32, radius float32, startAngle float32, endAngle float32, segments int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle_rounded_outline
func draw_rectangle_rounded_outline(x int32, y int32, width int32, height int32, cornerRadius int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle_outline_on_image
func draw_rectangle_outline_on_image(destination uint32, posX int32, posY int32, width int32, height int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_triangle_outline_on_image
func draw_triangle_outline_on_image(destination uint32, x1 int32, y1 int32, x2 int32, y2 int32, x3 int32, y3 int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_ellipse_outline_on_image
func draw_ellipse_outline_on_image(destination uint32, centerX int32, centerY int32, radiusX int32, radiusY int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_circle_outline_on_image
func draw_circle_outline_on_image(destination uint32, centerX int32, centerY int32, radius int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_polygon_outline_on_image
func draw_polygon_outline_on_image(destination uint32, points unsafe.Pointer, numPoints int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 draw_rectangle_rounded_outline_on_image
func draw_rectangle_rounded_outline_on_image(destination uint32, x int32, y int32, width int32, height int32, cornerRadius int32, thickness int32, color unsafe.Pointer)

//go:wasmimport null0 key_pressed
func key_pressed(key int32) int32

//go:wasmimport null0 key_down
func key_down(key int32) int32

//go:wasmimport null0 key_released
func key_released(key int32) int32

//go:wasmimport null0 key_up
func key_up(key int32) int32

//go:wasmimport null0 gamepad_button_pressed
func gamepad_button_pressed(gamepad int32, button int32) int32

//go:wasmimport null0 gamepad_button_down
func gamepad_button_down(gamepad int32, button int32) int32

//go:wasmimport null0 gamepad_button_released
func gamepad_button_released(gamepad int32, button int32) int32

//go:wasmimport null0 mouse_position
func mouse_position() unsafe.Pointer

//go:wasmimport null0 mouse_button_pressed
func mouse_button_pressed(button int32) int32

//go:wasmimport null0 mouse_button_down
func mouse_button_down(button int32) int32

//go:wasmimport null0 mouse_button_released
func mouse_button_released(button int32) int32

//go:wasmimport null0 mouse_button_up
func mouse_button_up(button int32) int32

//go:wasmimport null0 load_sound
func load_sound(filename unsafe.Pointer) uint32

//go:wasmimport null0 play_sound
func play_sound(sound uint32, loop int32)

//go:wasmimport null0 stop_sound
func stop_sound(sound uint32)

//go:wasmimport null0 unload_sound
func unload_sound(sound uint32)

//go:wasmimport null0 tts_sound
func tts_sound(text unsafe.Pointer, phonetic int32, pitch int32, speed int32, throat int32, mouth int32, sing int32) uint32

//go:wasmimport null0 sfx_sound
func sfx_sound(params unsafe.Pointer) uint32

//go:wasmimport null0 sfx_generate
func sfx_generate(typeArg int32) unsafe.Pointer

//go:wasmimport null0 load_tilemap
func load_tilemap(filename unsafe.Pointer) uint32

//go:wasmimport null0 unload_tilemap
func unload_tilemap(tilemap uint32)

//go:wasmimport null0 tile_update
func tile_update(tilemap uint32, deltaTime float32)

//go:wasmimport null0 tile_draw
func tile_draw(tilemap uint32, posX int32, posY int32)

//go:wasmimport null0 tile_draw_tint
func tile_draw_tint(tilemap uint32, posX int32, posY int32, tint unsafe.Pointer)

//go:wasmimport null0 tile_draw_on_image
func tile_draw_on_image(dst uint32, tilemap uint32, posX int32, posY int32)

//go:wasmimport null0 tile_draw_tile
func tile_draw_tile(tilemap uint32, gid int32, posX int32, posY int32)

//go:wasmimport null0 tile_layer_count
func tile_layer_count(tilemap uint32) int32

//go:wasmimport null0 tile_get_tile
func tile_get_tile(tilemap uint32, layer int32, column int32, row int32) int32

//go:wasmimport null0 tile_set_tile
func tile_set_tile(tilemap uint32, layer int32, column int32, row int32, gid int32)

//go:wasmimport null0 tile_image
func tile_image(tilemap uint32, gid int32) uint32

//go:wasmimport null0 tilemap_image
func tilemap_image(tilemap uint32) uint32

//go:wasmimport null0 current_time
func current_time() uint64

//go:wasmimport null0 delta_time
func delta_time() float32

//go:wasmimport null0 random_int
func random_int(min int32, max int32) int32

//go:wasmimport null0 random_seed_get
func random_seed_get() uint64

//go:wasmimport null0 random_seed_set
func random_seed_set(seed uint64)

// HELPERS

// memory the host allocated for us to keep (its malloc/free, in web builds)
var pinned = map[uint32][]byte{}

//go:wasmexport malloc
func malloc(size uint32) uint32 {
	if size == 0 {
		size = 1
	}
	buf := make([]byte, size)
	ptr := uint32(uintptr(unsafe.Pointer(&buf[0])))
	pinned[ptr] = buf
	return ptr
}

//go:wasmexport free
func free(ptr uint32) {
	delete(pinned, ptr)
}

// a null-terminated copy of a lua string, for the host. keep the bytes
// alive (runtime.KeepAlive) until the host call has returned
func cstr(s string) ([]byte, unsafe.Pointer) {
	b := append([]byte(s), 0)
	return b, unsafe.Pointer(&b[0])
}

func boolArg(L *lua.LState, n int) int32 {
	if L.ToBool(n) {
		return 1
	}
	return 0
}

func luaBool(v int32) lua.LBool {
	return lua.LBool(v != 0)
}

// a number out of a table-field, defaulting to 0 for anything else
func fieldNumber(t *lua.LTable, name string) float64 {
	if n, ok := t.RawGetString(name).(lua.LNumber); ok {
		return float64(n)
	}
	return 0
}

// SfxParams arrives from lua as a table, e.g. {randSeed = 0, waveType = 0, attackTime = 0, sustainTime = 0, sustainPunch = 0, decayTime = 0, startFrequency = 0, minFrequency = 0, slide = 0, deltaSlide = 0, vibratoDepth = 0, vibratoSpeed = 0, changeAmount = 0, changeSpeed = 0, squareDuty = 0, dutySweep = 0, repeatSpeed = 0, phaserOffset = 0, phaserSweep = 0, lpfCutoff = 0, lpfCutoffSweep = 0, lpfResonance = 0, hpfCutoff = 0, hpfCutoffSweep = 0}
func sfxParamsArg(L *lua.LState, n int) SfxParams {
	t := L.CheckTable(n)
	return SfxParams{
		RandSeed:       uint32(fieldNumber(t, "randSeed")),
		WaveType:       int32(fieldNumber(t, "waveType")),
		AttackTime:     float32(fieldNumber(t, "attackTime")),
		SustainTime:    float32(fieldNumber(t, "sustainTime")),
		SustainPunch:   float32(fieldNumber(t, "sustainPunch")),
		DecayTime:      float32(fieldNumber(t, "decayTime")),
		StartFrequency: float32(fieldNumber(t, "startFrequency")),
		MinFrequency:   float32(fieldNumber(t, "minFrequency")),
		Slide:          float32(fieldNumber(t, "slide")),
		DeltaSlide:     float32(fieldNumber(t, "deltaSlide")),
		VibratoDepth:   float32(fieldNumber(t, "vibratoDepth")),
		VibratoSpeed:   float32(fieldNumber(t, "vibratoSpeed")),
		ChangeAmount:   float32(fieldNumber(t, "changeAmount")),
		ChangeSpeed:    float32(fieldNumber(t, "changeSpeed")),
		SquareDuty:     float32(fieldNumber(t, "squareDuty")),
		DutySweep:      float32(fieldNumber(t, "dutySweep")),
		RepeatSpeed:    float32(fieldNumber(t, "repeatSpeed")),
		PhaserOffset:   float32(fieldNumber(t, "phaserOffset")),
		PhaserSweep:    float32(fieldNumber(t, "phaserSweep")),
		LpfCutoff:      float32(fieldNumber(t, "lpfCutoff")),
		LpfCutoffSweep: float32(fieldNumber(t, "lpfCutoffSweep")),
		LpfResonance:   float32(fieldNumber(t, "lpfResonance")),
		HpfCutoff:      float32(fieldNumber(t, "hpfCutoff")),
		HpfCutoffSweep: float32(fieldNumber(t, "hpfCutoffSweep")),
	}
}

// SfxParams goes back to lua as a table
func sfxParamsTable(L *lua.LState, v unsafe.Pointer) lua.LValue {
	if v == nil {
		return lua.LNil
	}
	s := (*SfxParams)(v)
	t := L.NewTable()
	t.RawSetString("randSeed", lua.LNumber(s.RandSeed))
	t.RawSetString("waveType", lua.LNumber(s.WaveType))
	t.RawSetString("attackTime", lua.LNumber(s.AttackTime))
	t.RawSetString("sustainTime", lua.LNumber(s.SustainTime))
	t.RawSetString("sustainPunch", lua.LNumber(s.SustainPunch))
	t.RawSetString("decayTime", lua.LNumber(s.DecayTime))
	t.RawSetString("startFrequency", lua.LNumber(s.StartFrequency))
	t.RawSetString("minFrequency", lua.LNumber(s.MinFrequency))
	t.RawSetString("slide", lua.LNumber(s.Slide))
	t.RawSetString("deltaSlide", lua.LNumber(s.DeltaSlide))
	t.RawSetString("vibratoDepth", lua.LNumber(s.VibratoDepth))
	t.RawSetString("vibratoSpeed", lua.LNumber(s.VibratoSpeed))
	t.RawSetString("changeAmount", lua.LNumber(s.ChangeAmount))
	t.RawSetString("changeSpeed", lua.LNumber(s.ChangeSpeed))
	t.RawSetString("squareDuty", lua.LNumber(s.SquareDuty))
	t.RawSetString("dutySweep", lua.LNumber(s.DutySweep))
	t.RawSetString("repeatSpeed", lua.LNumber(s.RepeatSpeed))
	t.RawSetString("phaserOffset", lua.LNumber(s.PhaserOffset))
	t.RawSetString("phaserSweep", lua.LNumber(s.PhaserSweep))
	t.RawSetString("lpfCutoff", lua.LNumber(s.LpfCutoff))
	t.RawSetString("lpfCutoffSweep", lua.LNumber(s.LpfCutoffSweep))
	t.RawSetString("lpfResonance", lua.LNumber(s.LpfResonance))
	t.RawSetString("hpfCutoff", lua.LNumber(s.HpfCutoff))
	t.RawSetString("hpfCutoffSweep", lua.LNumber(s.HpfCutoffSweep))
	return t
}

// Dimensions arrives from lua as a table, e.g. {width = 0, height = 0}
func dimensionsArg(L *lua.LState, n int) Dimensions {
	t := L.CheckTable(n)
	return Dimensions{
		Width:  int32(fieldNumber(t, "width")),
		Height: int32(fieldNumber(t, "height")),
	}
}

// Dimensions goes back to lua as a table
func dimensionsTable(L *lua.LState, v unsafe.Pointer) lua.LValue {
	if v == nil {
		return lua.LNil
	}
	s := (*Dimensions)(v)
	t := L.NewTable()
	t.RawSetString("width", lua.LNumber(s.Width))
	t.RawSetString("height", lua.LNumber(s.Height))
	return t
}

// Vector arrives from lua as a table, e.g. {x = 0, y = 0}
func vectorArg(L *lua.LState, n int) Vector {
	t := L.CheckTable(n)
	return Vector{
		X: int32(fieldNumber(t, "x")),
		Y: int32(fieldNumber(t, "y")),
	}
}

// Vector goes back to lua as a table
func vectorTable(L *lua.LState, v unsafe.Pointer) lua.LValue {
	if v == nil {
		return lua.LNil
	}
	s := (*Vector)(v)
	t := L.NewTable()
	t.RawSetString("x", lua.LNumber(s.X))
	t.RawSetString("y", lua.LNumber(s.Y))
	return t
}

// Rectangle arrives from lua as a table, e.g. {x = 0, y = 0, width = 0, height = 0}
func rectangleArg(L *lua.LState, n int) Rectangle {
	t := L.CheckTable(n)
	return Rectangle{
		X:      int32(fieldNumber(t, "x")),
		Y:      int32(fieldNumber(t, "y")),
		Width:  int32(fieldNumber(t, "width")),
		Height: int32(fieldNumber(t, "height")),
	}
}

// Rectangle goes back to lua as a table
func rectangleTable(L *lua.LState, v unsafe.Pointer) lua.LValue {
	if v == nil {
		return lua.LNil
	}
	s := (*Rectangle)(v)
	t := L.NewTable()
	t.RawSetString("x", lua.LNumber(s.X))
	t.RawSetString("y", lua.LNumber(s.Y))
	t.RawSetString("width", lua.LNumber(s.Width))
	t.RawSetString("height", lua.LNumber(s.Height))
	return t
}

// Color arrives from lua as a table, e.g. {r = 0, g = 0, b = 0, a = 0}
func colorArg(L *lua.LState, n int) Color {
	t := L.CheckTable(n)
	return Color{
		R: uint8(fieldNumber(t, "r")),
		G: uint8(fieldNumber(t, "g")),
		B: uint8(fieldNumber(t, "b")),
		A: uint8(fieldNumber(t, "a")),
	}
}

// Color goes back to lua as a table
func colorTable(L *lua.LState, v unsafe.Pointer) lua.LValue {
	if v == nil {
		return lua.LNil
	}
	s := (*Color)(v)
	t := L.NewTable()
	t.RawSetString("r", lua.LNumber(s.R))
	t.RawSetString("g", lua.LNumber(s.G))
	t.RawSetString("b", lua.LNumber(s.B))
	t.RawSetString("a", lua.LNumber(s.A))
	return t
}

// points arrive as an array of Vector tables, e.g. {{x = 1, y = 2}, ...}
func vectorsArg(L *lua.LState, n int) []Vector {
	t := L.CheckTable(n)
	count := t.Len()
	points := make([]Vector, 0, count)
	for i := 1; i <= count; i++ {
		if item, ok := t.RawGetInt(i).(*lua.LTable); ok {
			points = append(points, Vector{
				X: int32(fieldNumber(item, "x")),
				Y: int32(fieldNumber(item, "y")),
			})
		}
	}
	return points
}

// the address of the first point, or nil for an empty list
func pointsPtr(points []Vector) unsafe.Pointer {
	if len(points) == 0 {
		return nil
	}
	return unsafe.Pointer(&points[0])
}

// BINDINGS

// COLORS

// Tint a color with another color.
func lua_color_tint(L *lua.LState) int {
	color := colorArg(L, 1)
	tint := colorArg(L, 2)
	ret := color_tint(unsafe.Pointer(&color), unsafe.Pointer(&tint))
	L.Push(colorTable(L, ret))
	return 1
}

// Fade a color.
func lua_color_fade(L *lua.LState) int {
	color := colorArg(L, 1)
	alpha := float32(L.CheckNumber(2))
	ret := color_fade(unsafe.Pointer(&color), alpha)
	L.Push(colorTable(L, ret))
	return 1
}

// Change the brightness of a color.
func lua_color_brightness(L *lua.LState) int {
	color := colorArg(L, 1)
	factor := float32(L.CheckNumber(2))
	ret := color_brightness(unsafe.Pointer(&color), factor)
	L.Push(colorTable(L, ret))
	return 1
}

// Invert a color.
func lua_color_invert(L *lua.LState) int {
	color := colorArg(L, 1)
	ret := color_invert(unsafe.Pointer(&color))
	L.Push(colorTable(L, ret))
	return 1
}

// Blend 2 colors together.
func lua_color_alpha_blend(L *lua.LState) int {
	dst := colorArg(L, 1)
	src := colorArg(L, 2)
	ret := color_alpha_blend(unsafe.Pointer(&dst), unsafe.Pointer(&src))
	L.Push(colorTable(L, ret))
	return 1
}

// Change contrast of a color.
func lua_color_contrast(L *lua.LState) int {
	color := colorArg(L, 1)
	contrast := float32(L.CheckNumber(2))
	ret := color_contrast(unsafe.Pointer(&color), contrast)
	L.Push(colorTable(L, ret))
	return 1
}

// Interpolate colors.
func lua_color_bilinear_interpolate(L *lua.LState) int {
	color00 := colorArg(L, 1)
	color01 := colorArg(L, 2)
	color10 := colorArg(L, 3)
	color11 := colorArg(L, 4)
	coordinateX := float32(L.CheckNumber(5))
	coordinateY := float32(L.CheckNumber(6))
	ret := color_bilinear_interpolate(unsafe.Pointer(&color00), unsafe.Pointer(&color01), unsafe.Pointer(&color10), unsafe.Pointer(&color11), coordinateX, coordinateY)
	L.Push(colorTable(L, ret))
	return 1
}

// GRAPHICS

// Create a new blank image.
func lua_new_image(L *lua.LState) int {
	width := int32(L.CheckInt(1))
	height := int32(L.CheckInt(2))
	color := colorArg(L, 3)
	ret := new_image(width, height, unsafe.Pointer(&color))
	L.Push(lua.LNumber(ret))
	return 1
}

// Copy an image to a new image.
func lua_image_copy(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	ret := image_copy(image)
	L.Push(lua.LNumber(ret))
	return 1
}

// Create an image from a region of another image.
func lua_image_subimage(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	x := int32(L.CheckInt(2))
	y := int32(L.CheckInt(3))
	width := int32(L.CheckInt(4))
	height := int32(L.CheckInt(5))
	ret := image_subimage(image, x, y, width, height)
	L.Push(lua.LNumber(ret))
	return 1
}

// Clear the screen.
func lua_clear(L *lua.LState) int {
	color := colorArg(L, 1)
	clear(unsafe.Pointer(&color))
	return 0
}

// Draw a single pixel on the screen.
func lua_draw_point(L *lua.LState) int {
	x := int32(L.CheckInt(1))
	y := int32(L.CheckInt(2))
	color := colorArg(L, 3)
	draw_point(x, y, unsafe.Pointer(&color))
	return 0
}

// Draw a line on the screen.
func lua_draw_line(L *lua.LState) int {
	startPosX := int32(L.CheckInt(1))
	startPosY := int32(L.CheckInt(2))
	endPosX := int32(L.CheckInt(3))
	endPosY := int32(L.CheckInt(4))
	color := colorArg(L, 5)
	draw_line(startPosX, startPosY, endPosX, endPosY, unsafe.Pointer(&color))
	return 0
}

// Draw a filled rectangle on the screen.
func lua_draw_rectangle(L *lua.LState) int {
	posX := int32(L.CheckInt(1))
	posY := int32(L.CheckInt(2))
	width := int32(L.CheckInt(3))
	height := int32(L.CheckInt(4))
	color := colorArg(L, 5)
	draw_rectangle(posX, posY, width, height, unsafe.Pointer(&color))
	return 0
}

// Draw a filled triangle on the screen.
func lua_draw_triangle(L *lua.LState) int {
	x1 := int32(L.CheckInt(1))
	y1 := int32(L.CheckInt(2))
	x2 := int32(L.CheckInt(3))
	y2 := int32(L.CheckInt(4))
	x3 := int32(L.CheckInt(5))
	y3 := int32(L.CheckInt(6))
	color := colorArg(L, 7)
	draw_triangle(x1, y1, x2, y2, x3, y3, unsafe.Pointer(&color))
	return 0
}

// Draw a filled ellipse on the screen.
func lua_draw_ellipse(L *lua.LState) int {
	centerX := int32(L.CheckInt(1))
	centerY := int32(L.CheckInt(2))
	radiusX := int32(L.CheckInt(3))
	radiusY := int32(L.CheckInt(4))
	color := colorArg(L, 5)
	draw_ellipse(centerX, centerY, radiusX, radiusY, unsafe.Pointer(&color))
	return 0
}

// Draw a filled circle on the screen.
func lua_draw_circle(L *lua.LState) int {
	centerX := int32(L.CheckInt(1))
	centerY := int32(L.CheckInt(2))
	radius := int32(L.CheckInt(3))
	color := colorArg(L, 4)
	draw_circle(centerX, centerY, radius, unsafe.Pointer(&color))
	return 0
}

// Draw a filled polygon on the screen.
func lua_draw_polygon(L *lua.LState) int {
	points := vectorsArg(L, 1)
	color := colorArg(L, 2)
	draw_polygon(pointsPtr(points), int32(len(points)), unsafe.Pointer(&color))
	return 0
}

// Draw a filled arc on the screen.
func lua_draw_arc(L *lua.LState) int {
	centerX := int32(L.CheckInt(1))
	centerY := int32(L.CheckInt(2))
	radius := float32(L.CheckNumber(3))
	startAngle := float32(L.CheckNumber(4))
	endAngle := float32(L.CheckNumber(5))
	segments := int32(L.CheckInt(6))
	color := colorArg(L, 7)
	draw_arc(centerX, centerY, radius, startAngle, endAngle, segments, unsafe.Pointer(&color))
	return 0
}

// Draw a filled round-rectangle on the screen.
func lua_draw_rectangle_rounded(L *lua.LState) int {
	x := int32(L.CheckInt(1))
	y := int32(L.CheckInt(2))
	width := int32(L.CheckInt(3))
	height := int32(L.CheckInt(4))
	cornerRadius := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_rectangle_rounded(x, y, width, height, cornerRadius, unsafe.Pointer(&color))
	return 0
}

// Draw an image on the screen.
func lua_draw_image(L *lua.LState) int {
	src := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	draw_image(src, posX, posY)
	return 0
}

// Draw a tinted image on the screen.
func lua_draw_image_tint(L *lua.LState) int {
	src := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	tint := colorArg(L, 4)
	draw_image_tint(src, posX, posY, unsafe.Pointer(&tint))
	return 0
}

// Draw an image, rotated, on the screen.
func lua_draw_image_rotated(L *lua.LState) int {
	src := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	degrees := float32(L.CheckNumber(4))
	offsetX := float32(L.CheckNumber(5))
	offsetY := float32(L.CheckNumber(6))
	filter := int32(L.CheckInt(7))
	draw_image_rotated(src, posX, posY, degrees, offsetX, offsetY, filter)
	return 0
}

// Draw an image, flipped, on the screen.
func lua_draw_image_flipped(L *lua.LState) int {
	src := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	flipHorizontal := boolArg(L, 4)
	flipVertical := boolArg(L, 5)
	flipDiagonal := boolArg(L, 6)
	draw_image_flipped(src, posX, posY, flipHorizontal, flipVertical, flipDiagonal)
	return 0
}

// Draw an image, scaled, on the screen.
func lua_draw_image_scaled(L *lua.LState) int {
	src := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	scaleX := float32(L.CheckNumber(4))
	scaleY := float32(L.CheckNumber(5))
	offsetX := float32(L.CheckNumber(6))
	offsetY := float32(L.CheckNumber(7))
	filter := int32(L.CheckInt(8))
	draw_image_scaled(src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter)
	return 0
}

// Draw some text on the screen.
func lua_draw_text(L *lua.LState) int {
	font := uint32(L.CheckInt(1))
	textBytes, text := cstr(L.CheckString(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	color := colorArg(L, 5)
	draw_text(font, text, posX, posY, unsafe.Pointer(&color))
	runtime.KeepAlive(textBytes)
	return 0
}

// Save an image to persistant storage.
func lua_save_image(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	filenameBytes, filename := cstr(L.CheckString(2))
	save_image(image, filename)
	runtime.KeepAlive(filenameBytes)
	return 0
}

// Load an image from a file in cart.
func lua_load_image(L *lua.LState) int {
	filenameBytes, filename := cstr(L.CheckString(1))
	ret := load_image(filename)
	runtime.KeepAlive(filenameBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Resize an image, return copy.
func lua_image_resize(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	newWidth := int32(L.CheckInt(2))
	newHeight := int32(L.CheckInt(3))
	filter := int32(L.CheckInt(4))
	ret := image_resize(image, newWidth, newHeight, filter)
	L.Push(lua.LNumber(ret))
	return 1
}

// Scale an image, return copy.
func lua_image_scale(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	scaleX := float32(L.CheckNumber(2))
	scaleY := float32(L.CheckNumber(3))
	filter := int32(L.CheckInt(4))
	ret := image_scale(image, scaleX, scaleY, filter)
	L.Push(lua.LNumber(ret))
	return 1
}

// Replace a color in an image, in-place.
func lua_image_color_replace(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	color := colorArg(L, 2)
	replace := colorArg(L, 3)
	image_color_replace(image, unsafe.Pointer(&color), unsafe.Pointer(&replace))
	return 0
}

// Tint a color in an image, in-place.
func lua_image_color_tint(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	color := colorArg(L, 2)
	image_color_tint(image, unsafe.Pointer(&color))
	return 0
}

// Fade a color in an image, in-place.
func lua_image_color_fade(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	alpha := float32(L.CheckNumber(2))
	image_color_fade(image, alpha)
	return 0
}

// Copy a font to a new font.
func lua_font_copy(L *lua.LState) int {
	font := uint32(L.CheckInt(1))
	ret := font_copy(font)
	L.Push(lua.LNumber(ret))
	return 1
}

// Scale a font, return a new font.
func lua_font_scale(L *lua.LState) int {
	font := uint32(L.CheckInt(1))
	scaleX := float32(L.CheckNumber(2))
	scaleY := float32(L.CheckNumber(3))
	filter := int32(L.CheckInt(4))
	ret := font_scale(font, scaleX, scaleY, filter)
	L.Push(lua.LNumber(ret))
	return 1
}

// Load a BMF font from a file in cart.
func lua_load_font_bmf(L *lua.LState) int {
	filenameBytes, filename := cstr(L.CheckString(1))
	charactersBytes, characters := cstr(L.CheckString(2))
	ret := load_font_bmf(filename, characters)
	runtime.KeepAlive(filenameBytes)
	runtime.KeepAlive(charactersBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Load a BMF font from an image.
func lua_load_font_bmf_from_image(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	charactersBytes, characters := cstr(L.CheckString(2))
	ret := load_font_bmf_from_image(image, characters)
	runtime.KeepAlive(charactersBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Measure the size of some text.
func lua_measure_text(L *lua.LState) int {
	font := uint32(L.CheckInt(1))
	textBytes, text := cstr(L.CheckString(2))
	textLength := int32(L.CheckInt(3))
	ret := measure_text(font, text, textLength)
	runtime.KeepAlive(textBytes)
	L.Push(dimensionsTable(L, ret))
	return 1
}

// Meaure an image (use 0 for screen).
func lua_measure_image(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	ret := measure_image(image)
	L.Push(dimensionsTable(L, ret))
	return 1
}

// Load a TTY font from a file in cart.
func lua_load_font_tty(L *lua.LState) int {
	filenameBytes, filename := cstr(L.CheckString(1))
	glyphWidth := int32(L.CheckInt(2))
	glyphHeight := int32(L.CheckInt(3))
	charactersBytes, characters := cstr(L.CheckString(4))
	ret := load_font_tty(filename, glyphWidth, glyphHeight, characters)
	runtime.KeepAlive(filenameBytes)
	runtime.KeepAlive(charactersBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Load a TTY font from an image.
func lua_load_font_tty_from_image(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	glyphWidth := int32(L.CheckInt(2))
	glyphHeight := int32(L.CheckInt(3))
	charactersBytes, characters := cstr(L.CheckString(4))
	ret := load_font_tty_from_image(image, glyphWidth, glyphHeight, characters)
	runtime.KeepAlive(charactersBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Load a TTF font from a file in cart.
func lua_load_font_ttf(L *lua.LState) int {
	filenameBytes, filename := cstr(L.CheckString(1))
	fontSize := int32(L.CheckInt(2))
	ret := load_font_ttf(filename, fontSize)
	runtime.KeepAlive(filenameBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Invert the colors in an image, in-place.
func lua_image_color_invert(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	image_color_invert(image)
	return 0
}

// Calculate a rectangle representing the available alpha border in an image.
func lua_image_alpha_border(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	threshold := float32(L.CheckNumber(2))
	ret := image_alpha_border(image, threshold)
	L.Push(rectangleTable(L, ret))
	return 1
}

// Crop an image, in-place.
func lua_image_crop(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	x := int32(L.CheckInt(2))
	y := int32(L.CheckInt(3))
	width := int32(L.CheckInt(4))
	height := int32(L.CheckInt(5))
	image_crop(image, x, y, width, height)
	return 0
}

// Crop an image based on the alpha border, in-place.
func lua_image_alpha_crop(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	threshold := float32(L.CheckNumber(2))
	image_alpha_crop(image, threshold)
	return 0
}

// Adjust the brightness of an image, in-place.
func lua_image_color_brightness(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	factor := float32(L.CheckNumber(2))
	image_color_brightness(image, factor)
	return 0
}

// Flip an image, in-place.
func lua_image_flip(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	horizontal := boolArg(L, 2)
	vertical := boolArg(L, 3)
	image_flip(image, horizontal, vertical)
	return 0
}

// Change the contrast of an image, in-place.
func lua_image_color_contrast(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	contrast := float32(L.CheckNumber(2))
	image_color_contrast(image, contrast)
	return 0
}

// Use an image as an alpha-mask on another image.
func lua_image_alpha_mask(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	alphaMask := uint32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	image_alpha_mask(image, alphaMask, posX, posY)
	return 0
}

// Create a new image, rotating another image.
func lua_image_rotate(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	degrees := float32(L.CheckNumber(2))
	filter := int32(L.CheckInt(3))
	ret := image_rotate(image, degrees, filter)
	L.Push(lua.LNumber(ret))
	return 1
}

// Create a new image of a gradient.
func lua_image_gradient(L *lua.LState) int {
	width := int32(L.CheckInt(1))
	height := int32(L.CheckInt(2))
	topLeft := colorArg(L, 3)
	topRight := colorArg(L, 4)
	bottomLeft := colorArg(L, 5)
	bottomRight := colorArg(L, 6)
	ret := image_gradient(width, height, unsafe.Pointer(&topLeft), unsafe.Pointer(&topRight), unsafe.Pointer(&bottomLeft), unsafe.Pointer(&bottomRight))
	L.Push(lua.LNumber(ret))
	return 1
}

// Unload an image.
func lua_unload_image(L *lua.LState) int {
	image := uint32(L.CheckInt(1))
	unload_image(image)
	return 0
}

// Unload a font.
func lua_unload_font(L *lua.LState) int {
	font := uint32(L.CheckInt(1))
	unload_font(font)
	return 0
}

// Clear an image.
func lua_clear_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	color := colorArg(L, 2)
	clear_image(destination, unsafe.Pointer(&color))
	return 0
}

// Draw a single pixel on an image.
func lua_draw_point_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	x := int32(L.CheckInt(2))
	y := int32(L.CheckInt(3))
	color := colorArg(L, 4)
	draw_point_on_image(destination, x, y, unsafe.Pointer(&color))
	return 0
}

// Draw a line on an image.
func lua_draw_line_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	startPosX := int32(L.CheckInt(2))
	startPosY := int32(L.CheckInt(3))
	endPosX := int32(L.CheckInt(4))
	endPosY := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_line_on_image(destination, startPosX, startPosY, endPosX, endPosY, unsafe.Pointer(&color))
	return 0
}

// Draw a filled rectangle on an image.
func lua_draw_rectangle_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	width := int32(L.CheckInt(4))
	height := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_rectangle_on_image(destination, posX, posY, width, height, unsafe.Pointer(&color))
	return 0
}

// Draw a filled triangle on an image.
func lua_draw_triangle_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	x1 := int32(L.CheckInt(2))
	y1 := int32(L.CheckInt(3))
	x2 := int32(L.CheckInt(4))
	y2 := int32(L.CheckInt(5))
	x3 := int32(L.CheckInt(6))
	y3 := int32(L.CheckInt(7))
	color := colorArg(L, 8)
	draw_triangle_on_image(destination, x1, y1, x2, y2, x3, y3, unsafe.Pointer(&color))
	return 0
}

// Draw a filled ellipse on an image.
func lua_draw_ellipse_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	centerX := int32(L.CheckInt(2))
	centerY := int32(L.CheckInt(3))
	radiusX := int32(L.CheckInt(4))
	radiusY := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_ellipse_on_image(destination, centerX, centerY, radiusX, radiusY, unsafe.Pointer(&color))
	return 0
}

// Draw a circle on an image.
func lua_draw_circle_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	centerX := int32(L.CheckInt(2))
	centerY := int32(L.CheckInt(3))
	radius := int32(L.CheckInt(4))
	color := colorArg(L, 5)
	draw_circle_on_image(destination, centerX, centerY, radius, unsafe.Pointer(&color))
	return 0
}

// Draw a filled polygon on an image.
func lua_draw_polygon_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	points := vectorsArg(L, 2)
	color := colorArg(L, 3)
	draw_polygon_on_image(destination, pointsPtr(points), int32(len(points)), unsafe.Pointer(&color))
	return 0
}

// Draw a filled round-rectangle on an image.
func lua_draw_rectangle_rounded_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	x := int32(L.CheckInt(2))
	y := int32(L.CheckInt(3))
	width := int32(L.CheckInt(4))
	height := int32(L.CheckInt(5))
	cornerRadius := int32(L.CheckInt(6))
	color := colorArg(L, 7)
	draw_rectangle_rounded_on_image(destination, x, y, width, height, cornerRadius, unsafe.Pointer(&color))
	return 0
}

// Draw an image on an image.
func lua_draw_image_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	src := uint32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	draw_image_on_image(destination, src, posX, posY)
	return 0
}

// Draw a tinted image on an image.
func lua_draw_image_tint_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	src := uint32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	tint := colorArg(L, 5)
	draw_image_tint_on_image(destination, src, posX, posY, unsafe.Pointer(&tint))
	return 0
}

// Draw an image, rotated, on an image.
func lua_draw_image_rotated_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	src := uint32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	degrees := float32(L.CheckNumber(5))
	offsetX := float32(L.CheckNumber(6))
	offsetY := float32(L.CheckNumber(7))
	filter := int32(L.CheckInt(8))
	draw_image_rotated_on_image(destination, src, posX, posY, degrees, offsetX, offsetY, filter)
	return 0
}

// Draw an image, flipped, on an image.
func lua_draw_image_flipped_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	src := uint32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	flipHorizontal := boolArg(L, 5)
	flipVertical := boolArg(L, 6)
	flipDiagonal := boolArg(L, 7)
	draw_image_flipped_on_image(destination, src, posX, posY, flipHorizontal, flipVertical, flipDiagonal)
	return 0
}

// Draw an image, scaled, on an image.
func lua_draw_image_scaled_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	src := uint32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	scaleX := float32(L.CheckNumber(5))
	scaleY := float32(L.CheckNumber(6))
	offsetX := float32(L.CheckNumber(7))
	offsetY := float32(L.CheckNumber(8))
	filter := int32(L.CheckInt(9))
	draw_image_scaled_on_image(destination, src, posX, posY, scaleX, scaleY, offsetX, offsetY, filter)
	return 0
}

// Draw some text on an image.
func lua_draw_text_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	font := uint32(L.CheckInt(2))
	textBytes, text := cstr(L.CheckString(3))
	posX := int32(L.CheckInt(4))
	posY := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_text_on_image(destination, font, text, posX, posY, unsafe.Pointer(&color))
	runtime.KeepAlive(textBytes)
	return 0
}

// Draw a outlined (with thickness) rectangle on the screen.
func lua_draw_rectangle_outline(L *lua.LState) int {
	posX := int32(L.CheckInt(1))
	posY := int32(L.CheckInt(2))
	width := int32(L.CheckInt(3))
	height := int32(L.CheckInt(4))
	thickness := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_rectangle_outline(posX, posY, width, height, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) triangle on the screen.
func lua_draw_triangle_outline(L *lua.LState) int {
	x1 := int32(L.CheckInt(1))
	y1 := int32(L.CheckInt(2))
	x2 := int32(L.CheckInt(3))
	y2 := int32(L.CheckInt(4))
	x3 := int32(L.CheckInt(5))
	y3 := int32(L.CheckInt(6))
	thickness := int32(L.CheckInt(7))
	color := colorArg(L, 8)
	draw_triangle_outline(x1, y1, x2, y2, x3, y3, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) ellipse on the screen.
func lua_draw_ellipse_outline(L *lua.LState) int {
	centerX := int32(L.CheckInt(1))
	centerY := int32(L.CheckInt(2))
	radiusX := int32(L.CheckInt(3))
	radiusY := int32(L.CheckInt(4))
	thickness := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_ellipse_outline(centerX, centerY, radiusX, radiusY, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) circle on the screen.
func lua_draw_circle_outline(L *lua.LState) int {
	centerX := int32(L.CheckInt(1))
	centerY := int32(L.CheckInt(2))
	radius := int32(L.CheckInt(3))
	thickness := int32(L.CheckInt(4))
	color := colorArg(L, 5)
	draw_circle_outline(centerX, centerY, radius, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) polygon on the screen.
func lua_draw_polygon_outline(L *lua.LState) int {
	points := vectorsArg(L, 1)
	thickness := int32(L.CheckInt(2))
	color := colorArg(L, 3)
	draw_polygon_outline(pointsPtr(points), int32(len(points)), thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) arc on the screen.
func lua_draw_arc_outline(L *lua.LState) int {
	centerX := int32(L.CheckInt(1))
	centerY := int32(L.CheckInt(2))
	radius := float32(L.CheckNumber(3))
	startAngle := float32(L.CheckNumber(4))
	endAngle := float32(L.CheckNumber(5))
	segments := int32(L.CheckInt(6))
	thickness := int32(L.CheckInt(7))
	color := colorArg(L, 8)
	draw_arc_outline(centerX, centerY, radius, startAngle, endAngle, segments, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) round-rectangle on the screen.
func lua_draw_rectangle_rounded_outline(L *lua.LState) int {
	x := int32(L.CheckInt(1))
	y := int32(L.CheckInt(2))
	width := int32(L.CheckInt(3))
	height := int32(L.CheckInt(4))
	cornerRadius := int32(L.CheckInt(5))
	thickness := int32(L.CheckInt(6))
	color := colorArg(L, 7)
	draw_rectangle_rounded_outline(x, y, width, height, cornerRadius, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) rectangle on an image.
func lua_draw_rectangle_outline_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	width := int32(L.CheckInt(4))
	height := int32(L.CheckInt(5))
	thickness := int32(L.CheckInt(6))
	color := colorArg(L, 7)
	draw_rectangle_outline_on_image(destination, posX, posY, width, height, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) triangle on an image.
func lua_draw_triangle_outline_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	x1 := int32(L.CheckInt(2))
	y1 := int32(L.CheckInt(3))
	x2 := int32(L.CheckInt(4))
	y2 := int32(L.CheckInt(5))
	x3 := int32(L.CheckInt(6))
	y3 := int32(L.CheckInt(7))
	thickness := int32(L.CheckInt(8))
	color := colorArg(L, 9)
	draw_triangle_outline_on_image(destination, x1, y1, x2, y2, x3, y3, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) ellipse on an image.
func lua_draw_ellipse_outline_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	centerX := int32(L.CheckInt(2))
	centerY := int32(L.CheckInt(3))
	radiusX := int32(L.CheckInt(4))
	radiusY := int32(L.CheckInt(5))
	thickness := int32(L.CheckInt(6))
	color := colorArg(L, 7)
	draw_ellipse_outline_on_image(destination, centerX, centerY, radiusX, radiusY, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) circle on an image.
func lua_draw_circle_outline_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	centerX := int32(L.CheckInt(2))
	centerY := int32(L.CheckInt(3))
	radius := int32(L.CheckInt(4))
	thickness := int32(L.CheckInt(5))
	color := colorArg(L, 6)
	draw_circle_outline_on_image(destination, centerX, centerY, radius, thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) polygon on an image.
func lua_draw_polygon_outline_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	points := vectorsArg(L, 2)
	thickness := int32(L.CheckInt(3))
	color := colorArg(L, 4)
	draw_polygon_outline_on_image(destination, pointsPtr(points), int32(len(points)), thickness, unsafe.Pointer(&color))
	return 0
}

// Draw a outlined (with thickness) round-rectangle on an image.
func lua_draw_rectangle_rounded_outline_on_image(L *lua.LState) int {
	destination := uint32(L.CheckInt(1))
	x := int32(L.CheckInt(2))
	y := int32(L.CheckInt(3))
	width := int32(L.CheckInt(4))
	height := int32(L.CheckInt(5))
	cornerRadius := int32(L.CheckInt(6))
	thickness := int32(L.CheckInt(7))
	color := colorArg(L, 8)
	draw_rectangle_rounded_outline_on_image(destination, x, y, width, height, cornerRadius, thickness, unsafe.Pointer(&color))
	return 0
}

// INPUT

// Has the key been pressed? (tracks unpress/read correctly.)
func lua_key_pressed(L *lua.LState) int {
	key := int32(L.CheckInt(1))
	ret := key_pressed(key)
	L.Push(luaBool(ret))
	return 1
}

// Is the key currently down?
func lua_key_down(L *lua.LState) int {
	key := int32(L.CheckInt(1))
	ret := key_down(key)
	L.Push(luaBool(ret))
	return 1
}

// Has the key been released? (tracks press/read correctly.)
func lua_key_released(L *lua.LState) int {
	key := int32(L.CheckInt(1))
	ret := key_released(key)
	L.Push(luaBool(ret))
	return 1
}

// Is the key currently up?
func lua_key_up(L *lua.LState) int {
	key := int32(L.CheckInt(1))
	ret := key_up(key)
	L.Push(luaBool(ret))
	return 1
}

// Has the button been pressed? (tracks unpress/read correctly.)
func lua_gamepad_button_pressed(L *lua.LState) int {
	gamepad := int32(L.CheckInt(1))
	button := int32(L.CheckInt(2))
	ret := gamepad_button_pressed(gamepad, button)
	L.Push(luaBool(ret))
	return 1
}

// Is the button currently down?
func lua_gamepad_button_down(L *lua.LState) int {
	gamepad := int32(L.CheckInt(1))
	button := int32(L.CheckInt(2))
	ret := gamepad_button_down(gamepad, button)
	L.Push(luaBool(ret))
	return 1
}

// Has the button been released? (tracks press/read correctly.)
func lua_gamepad_button_released(L *lua.LState) int {
	gamepad := int32(L.CheckInt(1))
	button := int32(L.CheckInt(2))
	ret := gamepad_button_released(gamepad, button)
	L.Push(luaBool(ret))
	return 1
}

// Get current position of mouse.
func lua_mouse_position(L *lua.LState) int {
	ret := mouse_position()
	L.Push(vectorTable(L, ret))
	return 1
}

// Has the button been pressed? (tracks unpress/read correctly.)
func lua_mouse_button_pressed(L *lua.LState) int {
	button := int32(L.CheckInt(1))
	ret := mouse_button_pressed(button)
	L.Push(luaBool(ret))
	return 1
}

// Is the button currently down?
func lua_mouse_button_down(L *lua.LState) int {
	button := int32(L.CheckInt(1))
	ret := mouse_button_down(button)
	L.Push(luaBool(ret))
	return 1
}

// Has the button been released? (tracks press/read correctly.)
func lua_mouse_button_released(L *lua.LState) int {
	button := int32(L.CheckInt(1))
	ret := mouse_button_released(button)
	L.Push(luaBool(ret))
	return 1
}

// Is the button currently up?
func lua_mouse_button_up(L *lua.LState) int {
	button := int32(L.CheckInt(1))
	ret := mouse_button_up(button)
	L.Push(luaBool(ret))
	return 1
}

// SOUND

// Load a sound from a file in cart.
func lua_load_sound(L *lua.LState) int {
	filenameBytes, filename := cstr(L.CheckString(1))
	ret := load_sound(filename)
	runtime.KeepAlive(filenameBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Play a sound.
func lua_play_sound(L *lua.LState) int {
	sound := uint32(L.CheckInt(1))
	loop := boolArg(L, 2)
	play_sound(sound, loop)
	return 0
}

// Stop a sound.
func lua_stop_sound(L *lua.LState) int {
	sound := uint32(L.CheckInt(1))
	stop_sound(sound)
	return 0
}

// Unload a sound.
func lua_unload_sound(L *lua.LState) int {
	sound := uint32(L.CheckInt(1))
	unload_sound(sound)
	return 0
}

// Speak some text and return a sound. Set things to 0 for defaults.
func lua_tts_sound(L *lua.LState) int {
	textBytes, text := cstr(L.CheckString(1))
	phonetic := boolArg(L, 2)
	pitch := int32(L.CheckInt(3))
	speed := int32(L.CheckInt(4))
	throat := int32(L.CheckInt(5))
	mouth := int32(L.CheckInt(6))
	sing := boolArg(L, 7)
	ret := tts_sound(text, phonetic, pitch, speed, throat, mouth, sing)
	runtime.KeepAlive(textBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Create Sfx sound.
func lua_sfx_sound(L *lua.LState) int {
	params := sfxParamsArg(L, 1)
	ret := sfx_sound(unsafe.Pointer(&params))
	L.Push(lua.LNumber(ret))
	return 1
}

// Create Sfx parameters.
func lua_sfx_generate(L *lua.LState) int {
	typeArg := int32(L.CheckInt(1))
	ret := sfx_generate(typeArg)
	L.Push(sfxParamsTable(L, ret))
	return 1
}

// TILE

// Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
func lua_load_tilemap(L *lua.LState) int {
	filenameBytes, filename := cstr(L.CheckString(1))
	ret := load_tilemap(filename)
	runtime.KeepAlive(filenameBytes)
	L.Push(lua.LNumber(ret))
	return 1
}

// Unload a tilemap.
func lua_unload_tilemap(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	unload_tilemap(tilemap)
	return 0
}

// Update a tilemap's animation timers (deltaTime is in seconds).
func lua_tile_update(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	deltaTime := float32(L.CheckNumber(2))
	tile_update(tilemap, deltaTime)
	return 0
}

// Draw a tilemap on the screen.
func lua_tile_draw(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	tile_draw(tilemap, posX, posY)
	return 0
}

// Draw a tilemap on the screen, tinted by a color.
func lua_tile_draw_tint(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	posX := int32(L.CheckInt(2))
	posY := int32(L.CheckInt(3))
	tint := colorArg(L, 4)
	tile_draw_tint(tilemap, posX, posY, unsafe.Pointer(&tint))
	return 0
}

// Draw a tilemap on an image.
func lua_tile_draw_on_image(L *lua.LState) int {
	dst := uint32(L.CheckInt(1))
	tilemap := uint32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	tile_draw_on_image(dst, tilemap, posX, posY)
	return 0
}

// Draw a single tile from a tilemap on the screen.
func lua_tile_draw_tile(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	gid := int32(L.CheckInt(2))
	posX := int32(L.CheckInt(3))
	posY := int32(L.CheckInt(4))
	tile_draw_tile(tilemap, gid, posX, posY)
	return 0
}

// Get the number of layers in a tilemap.
func lua_tile_layer_count(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	ret := tile_layer_count(tilemap)
	L.Push(lua.LNumber(ret))
	return 1
}

// Get the gid of the tile at a column/row in a tilemap layer.
func lua_tile_get_tile(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	layer := int32(L.CheckInt(2))
	column := int32(L.CheckInt(3))
	row := int32(L.CheckInt(4))
	ret := tile_get_tile(tilemap, layer, column, row)
	L.Push(lua.LNumber(ret))
	return 1
}

// Set the gid of the tile at a column/row in a tilemap layer.
func lua_tile_set_tile(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	layer := int32(L.CheckInt(2))
	column := int32(L.CheckInt(3))
	row := int32(L.CheckInt(4))
	gid := int32(L.CheckInt(5))
	tile_set_tile(tilemap, layer, column, row, gid)
	return 0
}

// Get a copy of the image of a single tile in a tilemap.
func lua_tile_image(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	gid := int32(L.CheckInt(2))
	ret := tile_image(tilemap, gid)
	L.Push(lua.LNumber(ret))
	return 1
}

// Render a whole tilemap to a new image.
func lua_tilemap_image(L *lua.LState) int {
	tilemap := uint32(L.CheckInt(1))
	ret := tilemap_image(tilemap)
	L.Push(lua.LNumber(ret))
	return 1
}

// TYPES

// UTILITIES

// Get system-time (ms) since unix epoch.
func lua_current_time(L *lua.LState) int {
	ret := current_time()
	L.Push(lua.LNumber(ret))
	return 1
}

// Get the change in time (seconds) since the last update run.
func lua_delta_time(L *lua.LState) int {
	ret := delta_time()
	L.Push(lua.LNumber(ret))
	return 1
}

// Get a random integer between 2 numbers.
func lua_random_int(L *lua.LState) int {
	min := int32(L.CheckInt(1))
	max := int32(L.CheckInt(2))
	ret := random_int(min, max)
	L.Push(lua.LNumber(ret))
	return 1
}

// Get the random-seed.
func lua_random_seed_get(L *lua.LState) int {
	ret := random_seed_get()
	L.Push(lua.LNumber(ret))
	return 1
}

// Set the random-seed.
func lua_random_seed_set(L *lua.LState) int {
	seed := uint64(L.CheckNumber(1))
	random_seed_set(seed)
	return 0
}

// CONSTANTS

func registerConstants(L *lua.LState) {
	L.SetGlobal("SCREEN", lua.LNumber(0))
	L.SetGlobal("SCREEN_WIDTH", lua.LNumber(640))
	L.SetGlobal("SCREEN_HEIGHT", lua.LNumber(480))
	L.SetGlobal("FONT_DEFAULT", lua.LNumber(0))
	L.SetGlobal("LIGHTGRAY", colorTable(L, unsafe.Pointer(&Color{R: 200, G: 200, B: 200, A: 255})))
	L.SetGlobal("GRAY", colorTable(L, unsafe.Pointer(&Color{R: 130, G: 130, B: 130, A: 255})))
	L.SetGlobal("DARKGRAY", colorTable(L, unsafe.Pointer(&Color{R: 80, G: 80, B: 80, A: 255})))
	L.SetGlobal("YELLOW", colorTable(L, unsafe.Pointer(&Color{R: 253, G: 249, B: 0, A: 255})))
	L.SetGlobal("GOLD", colorTable(L, unsafe.Pointer(&Color{R: 255, G: 203, B: 0, A: 255})))
	L.SetGlobal("ORANGE", colorTable(L, unsafe.Pointer(&Color{R: 255, G: 161, B: 0, A: 255})))
	L.SetGlobal("PINK", colorTable(L, unsafe.Pointer(&Color{R: 255, G: 109, B: 194, A: 255})))
	L.SetGlobal("RED", colorTable(L, unsafe.Pointer(&Color{R: 230, G: 41, B: 55, A: 255})))
	L.SetGlobal("MAROON", colorTable(L, unsafe.Pointer(&Color{R: 190, G: 33, B: 55, A: 255})))
	L.SetGlobal("GREEN", colorTable(L, unsafe.Pointer(&Color{R: 0, G: 228, B: 48, A: 255})))
	L.SetGlobal("LIME", colorTable(L, unsafe.Pointer(&Color{R: 0, G: 158, B: 47, A: 255})))
	L.SetGlobal("DARKGREEN", colorTable(L, unsafe.Pointer(&Color{R: 0, G: 117, B: 44, A: 255})))
	L.SetGlobal("SKYBLUE", colorTable(L, unsafe.Pointer(&Color{R: 102, G: 191, B: 255, A: 255})))
	L.SetGlobal("BLUE", colorTable(L, unsafe.Pointer(&Color{R: 0, G: 121, B: 241, A: 255})))
	L.SetGlobal("DARKBLUE", colorTable(L, unsafe.Pointer(&Color{R: 0, G: 82, B: 172, A: 255})))
	L.SetGlobal("PURPLE", colorTable(L, unsafe.Pointer(&Color{R: 200, G: 122, B: 255, A: 255})))
	L.SetGlobal("VIOLET", colorTable(L, unsafe.Pointer(&Color{R: 135, G: 60, B: 190, A: 255})))
	L.SetGlobal("DARKPURPLE", colorTable(L, unsafe.Pointer(&Color{R: 112, G: 31, B: 126, A: 255})))
	L.SetGlobal("BEIGE", colorTable(L, unsafe.Pointer(&Color{R: 211, G: 176, B: 131, A: 255})))
	L.SetGlobal("BROWN", colorTable(L, unsafe.Pointer(&Color{R: 127, G: 106, B: 79, A: 255})))
	L.SetGlobal("DARKBROWN", colorTable(L, unsafe.Pointer(&Color{R: 76, G: 63, B: 47, A: 255})))
	L.SetGlobal("WHITE", colorTable(L, unsafe.Pointer(&Color{R: 255, G: 255, B: 255, A: 255})))
	L.SetGlobal("BLACK", colorTable(L, unsafe.Pointer(&Color{R: 0, G: 0, B: 0, A: 255})))
	L.SetGlobal("BLANK", colorTable(L, unsafe.Pointer(&Color{R: 0, G: 0, B: 0, A: 0})))
	L.SetGlobal("MAGENTA", colorTable(L, unsafe.Pointer(&Color{R: 255, G: 0, B: 255, A: 255})))
	L.SetGlobal("RAYWHITE", colorTable(L, unsafe.Pointer(&Color{R: 245, G: 245, B: 245, A: 255})))
	L.SetGlobal("NULL0_VERSION", lua.LString("0.0.8"))
	L.SetGlobal("FILTER_NEARESTNEIGHBOR", lua.LNumber(0))
	L.SetGlobal("FILTER_BILINEAR", lua.LNumber(1))
	L.SetGlobal("FILTER_SMOOTH", lua.LNumber(2))
	L.SetGlobal("SFX_COIN", lua.LNumber(0))
	L.SetGlobal("SFX_LASER", lua.LNumber(1))
	L.SetGlobal("SFX_EXPLOSION", lua.LNumber(2))
	L.SetGlobal("SFX_POWERUP", lua.LNumber(3))
	L.SetGlobal("SFX_HURT", lua.LNumber(4))
	L.SetGlobal("SFX_JUMP", lua.LNumber(5))
	L.SetGlobal("SFX_SELECT", lua.LNumber(6))
	L.SetGlobal("SFX_SYNTH", lua.LNumber(7))
	L.SetGlobal("KEY_INVALID", lua.LNumber(0))
	L.SetGlobal("KEY_SPACE", lua.LNumber(32))
	L.SetGlobal("KEY_APOSTROPHE", lua.LNumber(39))
	L.SetGlobal("KEY_COMMA", lua.LNumber(44))
	L.SetGlobal("KEY_MINUS", lua.LNumber(45))
	L.SetGlobal("KEY_PERIOD", lua.LNumber(46))
	L.SetGlobal("KEY_SLASH", lua.LNumber(47))
	L.SetGlobal("KEY_0", lua.LNumber(48))
	L.SetGlobal("KEY_1", lua.LNumber(49))
	L.SetGlobal("KEY_2", lua.LNumber(50))
	L.SetGlobal("KEY_3", lua.LNumber(51))
	L.SetGlobal("KEY_4", lua.LNumber(52))
	L.SetGlobal("KEY_5", lua.LNumber(53))
	L.SetGlobal("KEY_6", lua.LNumber(54))
	L.SetGlobal("KEY_7", lua.LNumber(55))
	L.SetGlobal("KEY_8", lua.LNumber(56))
	L.SetGlobal("KEY_9", lua.LNumber(57))
	L.SetGlobal("KEY_SEMICOLON", lua.LNumber(59))
	L.SetGlobal("KEY_EQUAL", lua.LNumber(61))
	L.SetGlobal("KEY_A", lua.LNumber(65))
	L.SetGlobal("KEY_B", lua.LNumber(66))
	L.SetGlobal("KEY_C", lua.LNumber(67))
	L.SetGlobal("KEY_D", lua.LNumber(68))
	L.SetGlobal("KEY_E", lua.LNumber(69))
	L.SetGlobal("KEY_F", lua.LNumber(70))
	L.SetGlobal("KEY_G", lua.LNumber(71))
	L.SetGlobal("KEY_H", lua.LNumber(72))
	L.SetGlobal("KEY_I", lua.LNumber(73))
	L.SetGlobal("KEY_J", lua.LNumber(74))
	L.SetGlobal("KEY_K", lua.LNumber(75))
	L.SetGlobal("KEY_L", lua.LNumber(76))
	L.SetGlobal("KEY_M", lua.LNumber(77))
	L.SetGlobal("KEY_N", lua.LNumber(78))
	L.SetGlobal("KEY_O", lua.LNumber(79))
	L.SetGlobal("KEY_P", lua.LNumber(80))
	L.SetGlobal("KEY_Q", lua.LNumber(81))
	L.SetGlobal("KEY_R", lua.LNumber(82))
	L.SetGlobal("KEY_S", lua.LNumber(83))
	L.SetGlobal("KEY_T", lua.LNumber(84))
	L.SetGlobal("KEY_U", lua.LNumber(85))
	L.SetGlobal("KEY_V", lua.LNumber(86))
	L.SetGlobal("KEY_W", lua.LNumber(87))
	L.SetGlobal("KEY_X", lua.LNumber(88))
	L.SetGlobal("KEY_Y", lua.LNumber(89))
	L.SetGlobal("KEY_Z", lua.LNumber(90))
	L.SetGlobal("KEY_LEFT_BRACKET", lua.LNumber(91))
	L.SetGlobal("KEY_BACKSLASH", lua.LNumber(92))
	L.SetGlobal("KEY_RIGHT_BRACKET", lua.LNumber(93))
	L.SetGlobal("KEY_GRAVE_ACCENT", lua.LNumber(96))
	L.SetGlobal("KEY_WORLD_1", lua.LNumber(161))
	L.SetGlobal("KEY_WORLD_2", lua.LNumber(162))
	L.SetGlobal("KEY_ESCAPE", lua.LNumber(256))
	L.SetGlobal("KEY_ENTER", lua.LNumber(257))
	L.SetGlobal("KEY_TAB", lua.LNumber(258))
	L.SetGlobal("KEY_BACKSPACE", lua.LNumber(259))
	L.SetGlobal("KEY_INSERT", lua.LNumber(260))
	L.SetGlobal("KEY_DELETE", lua.LNumber(261))
	L.SetGlobal("KEY_RIGHT", lua.LNumber(262))
	L.SetGlobal("KEY_LEFT", lua.LNumber(263))
	L.SetGlobal("KEY_DOWN", lua.LNumber(264))
	L.SetGlobal("KEY_UP", lua.LNumber(265))
	L.SetGlobal("KEY_PAGE_UP", lua.LNumber(266))
	L.SetGlobal("KEY_PAGE_DOWN", lua.LNumber(267))
	L.SetGlobal("KEY_HOME", lua.LNumber(268))
	L.SetGlobal("KEY_END", lua.LNumber(269))
	L.SetGlobal("KEY_CAPS_LOCK", lua.LNumber(280))
	L.SetGlobal("KEY_SCROLL_LOCK", lua.LNumber(281))
	L.SetGlobal("KEY_NUM_LOCK", lua.LNumber(282))
	L.SetGlobal("KEY_PRINT_SCREEN", lua.LNumber(283))
	L.SetGlobal("KEY_PAUSE", lua.LNumber(284))
	L.SetGlobal("KEY_F1", lua.LNumber(290))
	L.SetGlobal("KEY_F2", lua.LNumber(291))
	L.SetGlobal("KEY_F3", lua.LNumber(292))
	L.SetGlobal("KEY_F4", lua.LNumber(293))
	L.SetGlobal("KEY_F5", lua.LNumber(294))
	L.SetGlobal("KEY_F6", lua.LNumber(295))
	L.SetGlobal("KEY_F7", lua.LNumber(296))
	L.SetGlobal("KEY_F8", lua.LNumber(297))
	L.SetGlobal("KEY_F9", lua.LNumber(298))
	L.SetGlobal("KEY_F10", lua.LNumber(299))
	L.SetGlobal("KEY_F11", lua.LNumber(300))
	L.SetGlobal("KEY_F12", lua.LNumber(301))
	L.SetGlobal("KEY_F13", lua.LNumber(302))
	L.SetGlobal("KEY_F14", lua.LNumber(303))
	L.SetGlobal("KEY_F15", lua.LNumber(304))
	L.SetGlobal("KEY_F16", lua.LNumber(305))
	L.SetGlobal("KEY_F17", lua.LNumber(306))
	L.SetGlobal("KEY_F18", lua.LNumber(307))
	L.SetGlobal("KEY_F19", lua.LNumber(308))
	L.SetGlobal("KEY_F20", lua.LNumber(309))
	L.SetGlobal("KEY_F21", lua.LNumber(310))
	L.SetGlobal("KEY_F22", lua.LNumber(311))
	L.SetGlobal("KEY_F23", lua.LNumber(312))
	L.SetGlobal("KEY_F24", lua.LNumber(313))
	L.SetGlobal("KEY_F25", lua.LNumber(314))
	L.SetGlobal("KEY_KP_0", lua.LNumber(320))
	L.SetGlobal("KEY_KP_1", lua.LNumber(321))
	L.SetGlobal("KEY_KP_2", lua.LNumber(322))
	L.SetGlobal("KEY_KP_3", lua.LNumber(323))
	L.SetGlobal("KEY_KP_4", lua.LNumber(324))
	L.SetGlobal("KEY_KP_5", lua.LNumber(325))
	L.SetGlobal("KEY_KP_6", lua.LNumber(326))
	L.SetGlobal("KEY_KP_7", lua.LNumber(327))
	L.SetGlobal("KEY_KP_8", lua.LNumber(328))
	L.SetGlobal("KEY_KP_9", lua.LNumber(329))
	L.SetGlobal("KEY_KP_DECIMAL", lua.LNumber(330))
	L.SetGlobal("KEY_KP_DIVIDE", lua.LNumber(331))
	L.SetGlobal("KEY_KP_MULTIPLY", lua.LNumber(332))
	L.SetGlobal("KEY_KP_SUBTRACT", lua.LNumber(333))
	L.SetGlobal("KEY_KP_ADD", lua.LNumber(334))
	L.SetGlobal("KEY_KP_ENTER", lua.LNumber(335))
	L.SetGlobal("KEY_KP_EQUAL", lua.LNumber(336))
	L.SetGlobal("KEY_LEFT_SHIFT", lua.LNumber(340))
	L.SetGlobal("KEY_LEFT_CONTROL", lua.LNumber(341))
	L.SetGlobal("KEY_LEFT_ALT", lua.LNumber(342))
	L.SetGlobal("KEY_LEFT_SUPER", lua.LNumber(343))
	L.SetGlobal("KEY_RIGHT_SHIFT", lua.LNumber(344))
	L.SetGlobal("KEY_RIGHT_CONTROL", lua.LNumber(345))
	L.SetGlobal("KEY_RIGHT_ALT", lua.LNumber(346))
	L.SetGlobal("KEY_RIGHT_SUPER", lua.LNumber(347))
	L.SetGlobal("KEY_MENU", lua.LNumber(348))
	L.SetGlobal("GAMEPAD_BUTTON_UNKNOWN", lua.LNumber(0))
	L.SetGlobal("GAMEPAD_BUTTON_UP", lua.LNumber(1))
	L.SetGlobal("GAMEPAD_BUTTON_RIGHT", lua.LNumber(2))
	L.SetGlobal("GAMEPAD_BUTTON_DOWN", lua.LNumber(3))
	L.SetGlobal("GAMEPAD_BUTTON_LEFT", lua.LNumber(4))
	L.SetGlobal("GAMEPAD_BUTTON_Y", lua.LNumber(5))
	L.SetGlobal("GAMEPAD_BUTTON_B", lua.LNumber(6))
	L.SetGlobal("GAMEPAD_BUTTON_A", lua.LNumber(7))
	L.SetGlobal("GAMEPAD_BUTTON_X", lua.LNumber(8))
	L.SetGlobal("GAMEPAD_BUTTON_LEFT_SHOULDER", lua.LNumber(9))
	L.SetGlobal("GAMEPAD_BUTTON_LEFT_TRIGGER", lua.LNumber(10))
	L.SetGlobal("GAMEPAD_BUTTON_RIGHT_SHOULDER", lua.LNumber(11))
	L.SetGlobal("GAMEPAD_BUTTON_RIGHT_TRIGGER", lua.LNumber(12))
	L.SetGlobal("GAMEPAD_BUTTON_SELECT", lua.LNumber(13))
	L.SetGlobal("GAMEPAD_BUTTON_MENU", lua.LNumber(14))
	L.SetGlobal("GAMEPAD_BUTTON_START", lua.LNumber(15))
	L.SetGlobal("GAMEPAD_BUTTON_LEFT_THUMB", lua.LNumber(16))
	L.SetGlobal("GAMEPAD_BUTTON_RIGHT_THUMB", lua.LNumber(17))
	L.SetGlobal("MOUSE_BUTTON_UNKNOWN", lua.LNumber(0))
	L.SetGlobal("MOUSE_BUTTON_LEFT", lua.LNumber(1))
	L.SetGlobal("MOUSE_BUTTON_RIGHT", lua.LNumber(2))
	L.SetGlobal("MOUSE_BUTTON_MIDDLE", lua.LNumber(3))
}

func registerAPI(L *lua.LState) {
	L.SetGlobal("color_tint", L.NewFunction(lua_color_tint))
	L.SetGlobal("color_fade", L.NewFunction(lua_color_fade))
	L.SetGlobal("color_brightness", L.NewFunction(lua_color_brightness))
	L.SetGlobal("color_invert", L.NewFunction(lua_color_invert))
	L.SetGlobal("color_alpha_blend", L.NewFunction(lua_color_alpha_blend))
	L.SetGlobal("color_contrast", L.NewFunction(lua_color_contrast))
	L.SetGlobal("color_bilinear_interpolate", L.NewFunction(lua_color_bilinear_interpolate))
	L.SetGlobal("new_image", L.NewFunction(lua_new_image))
	L.SetGlobal("image_copy", L.NewFunction(lua_image_copy))
	L.SetGlobal("image_subimage", L.NewFunction(lua_image_subimage))
	L.SetGlobal("clear", L.NewFunction(lua_clear))
	L.SetGlobal("draw_point", L.NewFunction(lua_draw_point))
	L.SetGlobal("draw_line", L.NewFunction(lua_draw_line))
	L.SetGlobal("draw_rectangle", L.NewFunction(lua_draw_rectangle))
	L.SetGlobal("draw_triangle", L.NewFunction(lua_draw_triangle))
	L.SetGlobal("draw_ellipse", L.NewFunction(lua_draw_ellipse))
	L.SetGlobal("draw_circle", L.NewFunction(lua_draw_circle))
	L.SetGlobal("draw_polygon", L.NewFunction(lua_draw_polygon))
	L.SetGlobal("draw_arc", L.NewFunction(lua_draw_arc))
	L.SetGlobal("draw_rectangle_rounded", L.NewFunction(lua_draw_rectangle_rounded))
	L.SetGlobal("draw_image", L.NewFunction(lua_draw_image))
	L.SetGlobal("draw_image_tint", L.NewFunction(lua_draw_image_tint))
	L.SetGlobal("draw_image_rotated", L.NewFunction(lua_draw_image_rotated))
	L.SetGlobal("draw_image_flipped", L.NewFunction(lua_draw_image_flipped))
	L.SetGlobal("draw_image_scaled", L.NewFunction(lua_draw_image_scaled))
	L.SetGlobal("draw_text", L.NewFunction(lua_draw_text))
	L.SetGlobal("save_image", L.NewFunction(lua_save_image))
	L.SetGlobal("load_image", L.NewFunction(lua_load_image))
	L.SetGlobal("image_resize", L.NewFunction(lua_image_resize))
	L.SetGlobal("image_scale", L.NewFunction(lua_image_scale))
	L.SetGlobal("image_color_replace", L.NewFunction(lua_image_color_replace))
	L.SetGlobal("image_color_tint", L.NewFunction(lua_image_color_tint))
	L.SetGlobal("image_color_fade", L.NewFunction(lua_image_color_fade))
	L.SetGlobal("font_copy", L.NewFunction(lua_font_copy))
	L.SetGlobal("font_scale", L.NewFunction(lua_font_scale))
	L.SetGlobal("load_font_bmf", L.NewFunction(lua_load_font_bmf))
	L.SetGlobal("load_font_bmf_from_image", L.NewFunction(lua_load_font_bmf_from_image))
	L.SetGlobal("measure_text", L.NewFunction(lua_measure_text))
	L.SetGlobal("measure_image", L.NewFunction(lua_measure_image))
	L.SetGlobal("load_font_tty", L.NewFunction(lua_load_font_tty))
	L.SetGlobal("load_font_tty_from_image", L.NewFunction(lua_load_font_tty_from_image))
	L.SetGlobal("load_font_ttf", L.NewFunction(lua_load_font_ttf))
	L.SetGlobal("image_color_invert", L.NewFunction(lua_image_color_invert))
	L.SetGlobal("image_alpha_border", L.NewFunction(lua_image_alpha_border))
	L.SetGlobal("image_crop", L.NewFunction(lua_image_crop))
	L.SetGlobal("image_alpha_crop", L.NewFunction(lua_image_alpha_crop))
	L.SetGlobal("image_color_brightness", L.NewFunction(lua_image_color_brightness))
	L.SetGlobal("image_flip", L.NewFunction(lua_image_flip))
	L.SetGlobal("image_color_contrast", L.NewFunction(lua_image_color_contrast))
	L.SetGlobal("image_alpha_mask", L.NewFunction(lua_image_alpha_mask))
	L.SetGlobal("image_rotate", L.NewFunction(lua_image_rotate))
	L.SetGlobal("image_gradient", L.NewFunction(lua_image_gradient))
	L.SetGlobal("unload_image", L.NewFunction(lua_unload_image))
	L.SetGlobal("unload_font", L.NewFunction(lua_unload_font))
	L.SetGlobal("clear_image", L.NewFunction(lua_clear_image))
	L.SetGlobal("draw_point_on_image", L.NewFunction(lua_draw_point_on_image))
	L.SetGlobal("draw_line_on_image", L.NewFunction(lua_draw_line_on_image))
	L.SetGlobal("draw_rectangle_on_image", L.NewFunction(lua_draw_rectangle_on_image))
	L.SetGlobal("draw_triangle_on_image", L.NewFunction(lua_draw_triangle_on_image))
	L.SetGlobal("draw_ellipse_on_image", L.NewFunction(lua_draw_ellipse_on_image))
	L.SetGlobal("draw_circle_on_image", L.NewFunction(lua_draw_circle_on_image))
	L.SetGlobal("draw_polygon_on_image", L.NewFunction(lua_draw_polygon_on_image))
	L.SetGlobal("draw_rectangle_rounded_on_image", L.NewFunction(lua_draw_rectangle_rounded_on_image))
	L.SetGlobal("draw_image_on_image", L.NewFunction(lua_draw_image_on_image))
	L.SetGlobal("draw_image_tint_on_image", L.NewFunction(lua_draw_image_tint_on_image))
	L.SetGlobal("draw_image_rotated_on_image", L.NewFunction(lua_draw_image_rotated_on_image))
	L.SetGlobal("draw_image_flipped_on_image", L.NewFunction(lua_draw_image_flipped_on_image))
	L.SetGlobal("draw_image_scaled_on_image", L.NewFunction(lua_draw_image_scaled_on_image))
	L.SetGlobal("draw_text_on_image", L.NewFunction(lua_draw_text_on_image))
	L.SetGlobal("draw_rectangle_outline", L.NewFunction(lua_draw_rectangle_outline))
	L.SetGlobal("draw_triangle_outline", L.NewFunction(lua_draw_triangle_outline))
	L.SetGlobal("draw_ellipse_outline", L.NewFunction(lua_draw_ellipse_outline))
	L.SetGlobal("draw_circle_outline", L.NewFunction(lua_draw_circle_outline))
	L.SetGlobal("draw_polygon_outline", L.NewFunction(lua_draw_polygon_outline))
	L.SetGlobal("draw_arc_outline", L.NewFunction(lua_draw_arc_outline))
	L.SetGlobal("draw_rectangle_rounded_outline", L.NewFunction(lua_draw_rectangle_rounded_outline))
	L.SetGlobal("draw_rectangle_outline_on_image", L.NewFunction(lua_draw_rectangle_outline_on_image))
	L.SetGlobal("draw_triangle_outline_on_image", L.NewFunction(lua_draw_triangle_outline_on_image))
	L.SetGlobal("draw_ellipse_outline_on_image", L.NewFunction(lua_draw_ellipse_outline_on_image))
	L.SetGlobal("draw_circle_outline_on_image", L.NewFunction(lua_draw_circle_outline_on_image))
	L.SetGlobal("draw_polygon_outline_on_image", L.NewFunction(lua_draw_polygon_outline_on_image))
	L.SetGlobal("draw_rectangle_rounded_outline_on_image", L.NewFunction(lua_draw_rectangle_rounded_outline_on_image))
	L.SetGlobal("key_pressed", L.NewFunction(lua_key_pressed))
	L.SetGlobal("key_down", L.NewFunction(lua_key_down))
	L.SetGlobal("key_released", L.NewFunction(lua_key_released))
	L.SetGlobal("key_up", L.NewFunction(lua_key_up))
	L.SetGlobal("gamepad_button_pressed", L.NewFunction(lua_gamepad_button_pressed))
	L.SetGlobal("gamepad_button_down", L.NewFunction(lua_gamepad_button_down))
	L.SetGlobal("gamepad_button_released", L.NewFunction(lua_gamepad_button_released))
	L.SetGlobal("mouse_position", L.NewFunction(lua_mouse_position))
	L.SetGlobal("mouse_button_pressed", L.NewFunction(lua_mouse_button_pressed))
	L.SetGlobal("mouse_button_down", L.NewFunction(lua_mouse_button_down))
	L.SetGlobal("mouse_button_released", L.NewFunction(lua_mouse_button_released))
	L.SetGlobal("mouse_button_up", L.NewFunction(lua_mouse_button_up))
	L.SetGlobal("load_sound", L.NewFunction(lua_load_sound))
	L.SetGlobal("play_sound", L.NewFunction(lua_play_sound))
	L.SetGlobal("stop_sound", L.NewFunction(lua_stop_sound))
	L.SetGlobal("unload_sound", L.NewFunction(lua_unload_sound))
	L.SetGlobal("tts_sound", L.NewFunction(lua_tts_sound))
	L.SetGlobal("sfx_sound", L.NewFunction(lua_sfx_sound))
	L.SetGlobal("sfx_generate", L.NewFunction(lua_sfx_generate))
	L.SetGlobal("load_tilemap", L.NewFunction(lua_load_tilemap))
	L.SetGlobal("unload_tilemap", L.NewFunction(lua_unload_tilemap))
	L.SetGlobal("tile_update", L.NewFunction(lua_tile_update))
	L.SetGlobal("tile_draw", L.NewFunction(lua_tile_draw))
	L.SetGlobal("tile_draw_tint", L.NewFunction(lua_tile_draw_tint))
	L.SetGlobal("tile_draw_on_image", L.NewFunction(lua_tile_draw_on_image))
	L.SetGlobal("tile_draw_tile", L.NewFunction(lua_tile_draw_tile))
	L.SetGlobal("tile_layer_count", L.NewFunction(lua_tile_layer_count))
	L.SetGlobal("tile_get_tile", L.NewFunction(lua_tile_get_tile))
	L.SetGlobal("tile_set_tile", L.NewFunction(lua_tile_set_tile))
	L.SetGlobal("tile_image", L.NewFunction(lua_tile_image))
	L.SetGlobal("tilemap_image", L.NewFunction(lua_tilemap_image))
	L.SetGlobal("current_time", L.NewFunction(lua_current_time))
	L.SetGlobal("delta_time", L.NewFunction(lua_delta_time))
	L.SetGlobal("random_int", L.NewFunction(lua_random_int))
	L.SetGlobal("random_seed_get", L.NewFunction(lua_random_seed_get))
	L.SetGlobal("random_seed_set", L.NewFunction(lua_random_seed_set))
	registerConstants(L)
}

// CART

var L *lua.LState

// lua has a load() of its own, so the globals a callback could shadow are
// remembered before the cart runs: if one still holds the same value
// afterwards, the cart did not define that callback and we leave it alone
var stdGlobals = map[string]lua.LValue{}

func rememberStdGlobals(names ...string) {
	for _, name := range names {
		stdGlobals[name] = L.GetGlobal(name)
	}
}

// call a global lua function, if the cart defined one. errors are printed
// (Protect uses lua's pcall under the hood) instead of killing the cart
func callCart(name string, args ...lua.LValue) {
	if L == nil {
		return
	}
	value := L.GetGlobal(name)
	if std, isStd := stdGlobals[name]; isStd && std == value {
		return
	}
	fn, ok := value.(*lua.LFunction)
	if !ok {
		return
	}
	if err := L.CallByParam(lua.P{Fn: fn, NRet: 0, Protect: true}, args...); err != nil {
		fmt.Println("lua:", err)
	}
}

//go:wasmexport load
func load() {
	// cart files are read with an absolute path: go's wasip1 has no working
	// directory to resolve a relative one against
	source, err := os.ReadFile("/main.lua")
	if err != nil {
		fmt.Println("lua: no main.lua in cart")
		return
	}

	L = lua.NewState()
	registerAPI(L)

	// so require("thing") finds thing.lua in the cart
	if pkg, ok := L.GetGlobal("package").(*lua.LTable); ok {
		pkg.RawSetString("path", lua.LString("/?.lua;/?/init.lua"))
	}

	rememberStdGlobals("load", "update", "unload", "buttonUp", "buttonDown", "keyUp", "keyDown", "mouseDown", "mouseUp", "mouseMoved")

	if err := L.DoString(string(source)); err != nil {
		fmt.Println("lua:", err)
		L = nil
		return
	}

	callCart("load")
}

//go:wasmexport update
func update() {
	callCart("update")
}

//go:wasmexport unload
func unload() {
	callCart("unload")
	if L != nil {
		L.Close()
		L = nil
	}
}

// Mapped controller (keys and gamepad will trigger) callback for when a "button" is unpressed.
//
//go:wasmexport buttonUp
func buttonUp(button int32, player uint32) {
	callCart("buttonUp", lua.LNumber(button), lua.LNumber(player))
}

// Mapped controller (keys and gamepad will trigger) callback for when a "button" is pressed.
//
//go:wasmexport buttonDown
func buttonDown(button int32, player uint32) {
	callCart("buttonDown", lua.LNumber(button), lua.LNumber(player))
}

// Called when keys are unpressed.
//
//go:wasmexport keyUp
func keyUp(key int32) {
	callCart("keyUp", lua.LNumber(key))
}

// Called when keys are pressed.
//
//go:wasmexport keyDown
func keyDown(key int32) {
	callCart("keyDown", lua.LNumber(key))
}

// Called when mouse-button is pressed.
//
//go:wasmexport mouseDown
func mouseDown(button int32) {
	callCart("mouseDown", lua.LNumber(button))
}

// Called when mouse-button is released.
//
//go:wasmexport mouseUp
func mouseUp(button int32) {
	callCart("mouseUp", lua.LNumber(button))
}

// Called when mouse is moved.
//
//go:wasmexport mouseMoved
func mouseMoved(x float32, y float32) {
	callCart("mouseMoved", lua.LNumber(x), lua.LNumber(y))
}

// go needs a main, but the host never calls it: this is built as a wasi
// reactor, so the runtime starts up in _initialize instead
func main() {}
