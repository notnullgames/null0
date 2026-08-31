package main

import null0 "null0"

//export load
func load() {
	null0.Clear(null0.BLUE)
	null0.DrawCircle(100, 100, 50, null0.RED)
}

// callbacks (optional - implement as needed)

// //export update
// func update() {}

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
