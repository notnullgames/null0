#![no_std]

use null0::*;

static mut FRAME_COUNT: u32 = 0;

#[no_mangle]
pub extern "C" fn load() {
    // Game initialization
}

#[no_mangle]
pub extern "C" fn update() {
    unsafe {
        FRAME_COUNT += 1;
        
        // Clear screen with dark blue
        clear(DARKBLUE);
        
        // Draw some shapes
        draw_rectangle(50, 50, 100, 60, RED);
        draw_circle(200, 100, 30, GREEN);
        draw_triangle(300, 50, 350, 150, 250, 150, YELLOW);
        
        // Draw some text
        draw_text(FONT_DEFAULT, cstr!("Hello from Rust!"), 50, 200, WHITE);
        draw_text(FONT_DEFAULT, cstr!("null0 Fantasy Console"), 50, 220, LIGHTGRAY);
        
        // Draw frame counter
        let frame_text = if FRAME_COUNT % 60 < 30 {
            cstr!("Frame counter blinking")
        } else {
            cstr!("                     ")
        };
        draw_text(FONT_DEFAULT, frame_text, 50, 250, SKYBLUE);
        
        // Draw some input-responsive elements
        if key_down(Key::KEY_SPACE) {
            draw_text(FONT_DEFAULT, cstr!("SPACE is pressed!"), 50, 280, ORANGE);
        }
        
        if key_pressed(Key::KEY_ENTER) {
            draw_rectangle(400, 200, 50, 50, MAGENTA);
        }
    }
}

#[no_mangle]
pub extern "C" fn unload() {
    // Cleanup when cart is unloaded
}
