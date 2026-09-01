const null0 = @import("null0.zig");

// zig needs an entry-point for wasm32-wasi executables
pub fn main() void {}

export fn load() void {
    null0.clear(null0.BLUE);
    null0.draw_circle(100, 100, 50, null0.RED);
    null0.draw_text(null0.FONT_DEFAULT, "hello from Zig", 170, 92, null0.WHITE);
}

// callbacks (optional - implement as needed)

// export fn update() void {}
// export fn unload() void {}
