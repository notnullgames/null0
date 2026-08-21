package main

import null0 "null0"

// a richer demo: shapes, text, a polygon (array-arg), and per-frame animation state

var frameCount int32 = 0

//export update
func update() {
	frameCount++

	null0.Clear(null0.DARKGRAY)
	null0.DrawText(null0.FONT_DEFAULT, "null0 demo", 20, 20, null0.WHITE)

	null0.DrawRectangle(40, 80, 100, 70, null0.RED)
	null0.DrawCircle(220, 115, 45, null0.GREEN)
	null0.DrawTriangle(320, 150, 400, 150, 360, 60, null0.BLUE)
	null0.DrawLine(40, 250, 600, 250, null0.LIGHTGRAY)

	hexagon := []null0.Vector{
		{X: 460, Y: 80},
		{X: 520, Y: 80},
		{X: 550, Y: 140},
		{X: 520, Y: 200},
		{X: 460, Y: 200},
		{X: 430, Y: 140},
	}
	null0.DrawPolygon(hexagon, int32(len(hexagon)), null0.PURPLE)

	x := frameCount % 600
	null0.DrawCircle(x+20, 350, 20, null0.YELLOW)

	null0.DrawText(null0.FONT_DEFAULT, "shapes + animation + text", 20, 440, null0.ORANGE)
}

// callbacks (optional - implement as needed)

// //export load
// func load() {}

// //export unload
// func unload() {}

// //export buttonUp
// func buttonUp(button null0.GamepadButton, player uint32) {}

// //export buttonDown
// func buttonDown(button null0.GamepadButton, player uint32) {}

// //export keyUp
// func keyUp(key null0.Key) {}

// //export keyDown
// func keyDown(key null0.Key) {}

// //export mouseDown
// func mouseDown(button null0.MouseButton) {}

// //export mouseUp
// func mouseUp(button null0.MouseButton) {}

// //export mouseMoved
// func mouseMoved(x, y float32) {}

func main() {}
