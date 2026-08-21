const null0 = @import("null0.zig");

// zig needs an entry-point for wasm32-wasi executables
pub fn main() void {}

// a richer demo: shapes, text, a polygon (array-arg), and per-frame animation state

var frame_count: u32 = 0;

export fn update() void {
    frame_count += 1;

    null0.clear(null0.DARKGRAY);
    null0.draw_text(null0.FONT_DEFAULT, "null0 demo", 20, 20, null0.WHITE);

    null0.draw_rectangle(40, 80, 100, 70, null0.RED);
    null0.draw_circle(220, 115, 45, null0.GREEN);
    null0.draw_triangle(320, 150, 400, 150, 360, 60, null0.BLUE);
    null0.draw_line(40, 250, 600, 250, null0.LIGHTGRAY);

    const hexagon = [_]null0.Vector{
        .{ .x = 460, .y = 80 },
        .{ .x = 520, .y = 80 },
        .{ .x = 550, .y = 140 },
        .{ .x = 520, .y = 200 },
        .{ .x = 460, .y = 200 },
        .{ .x = 430, .y = 140 },
    };
    null0.draw_polygon(&hexagon, hexagon.len, null0.PURPLE);

    const x: i32 = @intCast(frame_count % 600);
    null0.draw_circle(x + 20, 350, 20, null0.YELLOW);

    null0.draw_text(null0.FONT_DEFAULT, "shapes + animation + text", 20, 440, null0.ORANGE);
}

// callbacks (optional - implement as needed)

// export fn load() void {}
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
