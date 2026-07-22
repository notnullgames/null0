const null0 = @import("null0.zig");

// zig needs an entry-point for wasm32-wasi executables
pub fn main() void {}

export fn load() void {
    null0.clear(null0.BLUE);
    null0.draw_circle(100, 100, 50, null0.RED);
}

// callbacks (optional - implement as needed)

// export fn update() void {}
// export fn unload() void {}
// export fn buttonUp(button: null0.GamepadButton, player: u32) void {
//     _ = button;
//     _ = player;
// }
// export fn buttonDown(button: null0.GamepadButton, player: u32) void {
//     _ = button;
//     _ = player;
// }
// export fn keyUp(key: null0.Key) void {
//     _ = key;
// }
// export fn keyDown(key: null0.Key) void {
//     _ = key;
// }
// export fn mouseDown(button: null0.MouseButton) void {
//     _ = button;
// }
// export fn mouseUp(button: null0.MouseButton) void {
//     _ = button;
// }
// export fn mouseMoved(x: f32, y: f32) void {
//     _ = x;
//     _ = y;
// }
