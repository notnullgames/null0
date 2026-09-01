package main

import null0 "null0"

//export load
func load() {
	null0.Clear(null0.BLUE)
	null0.DrawCircle(100, 100, 50, null0.RED)
	null0.DrawText(null0.FONT_DEFAULT, "hello from Go", 170, 92, null0.WHITE)
}

// tinygo needs a main, even though null0 never calls it
func main() {}

// callbacks (optional - implement as needed)
//
//	//export update
//	func update() {}
