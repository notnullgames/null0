#![no_std]

use null0::*;

// a richer demo: shapes, text, a polygon (array-arg), and per-frame animation state

static mut FRAME_COUNT: u32 = 0;

#[no_mangle]
pub extern "C" fn update() {
    unsafe {
        FRAME_COUNT += 1;

        clear(DARKGRAY);
        draw_text(FONT_DEFAULT, cstr!("null0 demo"), 20, 20, WHITE);

        draw_rectangle(40, 80, 100, 70, RED);
        draw_circle(220, 115, 45, GREEN);
        draw_triangle(320, 150, 400, 150, 360, 60, BLUE);
        draw_line(40, 250, 600, 250, LIGHTGRAY);

        let hexagon: [Vector; 6] = [
            Vector::new(460, 80),
            Vector::new(520, 80),
            Vector::new(550, 140),
            Vector::new(520, 200),
            Vector::new(460, 200),
            Vector::new(430, 140),
        ];
        draw_polygon(hexagon.as_ptr(), hexagon.len() as i32, PURPLE);

        let x = (FRAME_COUNT % 600) as i32;
        draw_circle(x + 20, 350, 20, YELLOW);

        draw_text(FONT_DEFAULT, cstr!("shapes + animation + text"), 20, 440, ORANGE);
    }
}

#[no_mangle]
pub extern "C" fn load() {
    // Game initialization
}

#[no_mangle]
pub extern "C" fn unload() {
    // Cleanup when cart is unloaded
}
