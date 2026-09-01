#![no_std]

use null0::*;

#[no_mangle]
pub extern "C" fn load() {
    unsafe {
        clear(BLUE);
        draw_circle(100, 100, 50, RED);
        draw_text(FONT_DEFAULT, cstr!("hello from Rust"), 170, 92, WHITE);
    }
}

// callbacks (optional - implement as needed)
//
//   #[no_mangle]
//   pub extern "C" fn update() {}
