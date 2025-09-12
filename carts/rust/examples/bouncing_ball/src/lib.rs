use null0::*;

// Game state
static mut BALL_X: f32 = 320.0;
static mut BALL_Y: f32 = 240.0;
static mut BALL_VX: f32 = 3.0;
static mut BALL_VY: f32 = 2.0;
static mut BALL_RADIUS: f32 = 20.0;
static mut BALL_COLOR_INDEX: u8 = 0;

const COLORS: [Color; 6] = [RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA];

#[no_mangle]
pub extern "C" fn load() {
    // Initialize ball position in center
    unsafe {
        BALL_X = (SCREEN_WIDTH / 2) as f32;
        BALL_Y = (SCREEN_HEIGHT / 2) as f32;
    }
}

#[no_mangle]
pub extern "C" fn update() {
    // Clear screen
    clear(BLACK);
    
    unsafe {
        // Update ball position
        BALL_X += BALL_VX;
        BALL_Y += BALL_VY;
        
        // Bounce off walls
        if BALL_X - BALL_RADIUS <= 0.0 || BALL_X + BALL_RADIUS >= SCREEN_WIDTH as f32 {
            BALL_VX = -BALL_VX;
            BALL_COLOR_INDEX = (BALL_COLOR_INDEX + 1) % COLORS.len() as u8;
        }
        
        if BALL_Y - BALL_RADIUS <= 0.0 || BALL_Y + BALL_RADIUS >= SCREEN_HEIGHT as f32 {
            BALL_VY = -BALL_VY;
            BALL_COLOR_INDEX = (BALL_COLOR_INDEX + 1) % COLORS.len() as u8;
        }
        
        // Keep ball in bounds
        BALL_X = BALL_X.max(BALL_RADIUS).min(SCREEN_WIDTH as f32 - BALL_RADIUS);
        BALL_Y = BALL_Y.max(BALL_RADIUS).min(SCREEN_HEIGHT as f32 - BALL_RADIUS);
        
        // Draw ball
        let ball_color = COLORS[BALL_COLOR_INDEX as usize];
        draw_circle(BALL_X as i32, BALL_Y as i32, BALL_RADIUS as i32, ball_color);
        
        // Draw ball trail/shadow
        draw_circle(
            (BALL_X - BALL_VX * 2.0) as i32,
            (BALL_Y - BALL_VY * 2.0) as i32,
            (BALL_RADIUS * 0.7) as i32,
            Color::new(ball_color.r / 2, ball_color.g / 2, ball_color.b / 2, 128)
        );
    }
    
    // Draw UI
    draw_text(FONT_DEFAULT, cstr!("Bouncing Ball Demo"), 10, 10, WHITE);
    draw_text(FONT_DEFAULT, cstr!("Press SPACE to change speed"), 10, 30, LIGHTGRAY);
    draw_text(FONT_DEFAULT, cstr!("Press R to reset"), 10, 50, LIGHTGRAY);
    
    // Handle input
    if key_pressed(Key::KeySpace) {
        unsafe {
            BALL_VX *= 1.2;
            BALL_VY *= 1.2;
            
            // Cap maximum speed
            if BALL_VX.abs() > 10.0 {
                BALL_VX = if BALL_VX > 0.0 { 3.0 } else { -3.0 };
                BALL_VY = if BALL_VY > 0.0 { 2.0 } else { -2.0 };
            }
        }
    }
    
    if key_pressed(Key::KeyR) {
        unsafe {
            BALL_X = (SCREEN_WIDTH / 2) as f32;
            BALL_Y = (SCREEN_HEIGHT / 2) as f32;
            BALL_VX = 3.0;
            BALL_VY = 2.0;
            BALL_COLOR_INDEX = 0;
        }
    }
    
    // Draw speed indicator
    unsafe {
        let speed = (BALL_VX * BALL_VX + BALL_VY * BALL_VY).sqrt();
        let bar_width = (speed * 20.0) as i32;
        draw_rectangle(10, 80, bar_width, 10, GREEN);
        draw_rectangle_outline(10, 80, 200, 10, 1, WHITE);
        draw_text(FONT_DEFAULT, cstr!("Speed:"), 10, 95, WHITE);
    }
}

#[no_mangle]
pub extern "C" fn unload() {
    // Cleanup
}
