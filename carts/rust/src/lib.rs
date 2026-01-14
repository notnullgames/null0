//! # null0 - Rust bindings for the null0 fantasy console
//!
//! This crate provides Rust bindings for the null0 fantasy console API.
//! It allows you to create games that compile to WebAssembly and run in the null0 runtime.
//!
//! ## Usage
//!
//! Add this to your `Cargo.toml`:
//!
//! ```toml
//! [dependencies]
//! null0 = "0.1"
//! ```
//!
//! Then implement the required callbacks:
//!
//! ```rust
//! use null0::*;
//!
//! #[no_mangle]
//! pub extern "C" fn load() {
//!     // Initialize your game
//! }
//!
//! #[no_mangle]
//! pub extern "C" fn update() {
//!     // Update game logic (60 FPS)
//!     clear(BLACK);
//!     draw_text(FONT_DEFAULT, "Hello, null0!", 10, 10, WHITE);
//! }
//! ```

#![no_std]

use core::panic::PanicInfo;

/// Panic handler required for no_std
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

// Type definitions

/// Sfx parameters.
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct SfxParams {
    pub randSeed: u32,
    pub waveType: i32,
    pub attackTime: f32,
    pub sustainTime: f32,
    pub sustainPunch: f32,
    pub decayTime: f32,
    pub startFrequency: f32,
    pub minFrequency: f32,
    pub slide: f32,
    pub deltaSlide: f32,
    pub vibratoDepth: f32,
    pub vibratoSpeed: f32,
    pub changeAmount: f32,
    pub changeSpeed: f32,
    pub squareDuty: f32,
    pub dutySweep: f32,
    pub repeatSpeed: f32,
    pub phaserOffset: f32,
    pub phaserSweep: f32,
    pub lpfCutoff: f32,
    pub lpfCutoffSweep: f32,
    pub lpfResonance: f32,
    pub hpfCutoff: f32,
    pub hpfCutoffSweep: f32,
}

/// The 2D size of something (width/height.)
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Dimensions {
    pub width: i32,
    pub height: i32,
}

/// The 2D position of something (x/y.)
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Vector {
    pub x: i32,
    pub y: i32,
}

/// The 2D position + size of something (x/y/w/h.)
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Rectangle {
    pub x: i32,
    pub y: i32,
    pub width: i32,
    pub height: i32,
}

/// An RGBA color.
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}

/// Potential image-filtering techniques for scale/etc.
#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ImageFilter {
    FILTER_NEARESTNEIGHBOR = 0,
    FILTER_BILINEAR = 1,
    FILTER_SMOOTH = 2,
}

/// Represents a Sfx preset type.
#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SfxPresetType {
    SFX_COIN = 0,
    SFX_LASER = 1,
    SFX_EXPLOSION = 2,
    SFX_POWERUP = 3,
    SFX_HURT = 4,
    SFX_JUMP = 5,
    SFX_SELECT = 6,
    SFX_SYNTH = 7,
}

/// Represents a keyboard key.
#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Key {
    KEY_INVALID = 0,
    KEY_SPACE = 32,
    KEY_APOSTROPHE = 39,
    KEY_COMMA = 44,
    KEY_MINUS = 45,
    KEY_PERIOD = 46,
    KEY_SLASH = 47,
    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,
    KEY_SEMICOLON = 59,
    KEY_EQUAL = 61,
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,
    KEY_LEFT_BRACKET = 91,
    KEY_BACKSLASH = 92,
    KEY_RIGHT_BRACKET = 93,
    KEY_GRAVE_ACCENT = 96,
    KEY_WORLD_1 = 161,
    KEY_WORLD_2 = 162,
    KEY_ESCAPE = 256,
    KEY_ENTER = 257,
    KEY_TAB = 258,
    KEY_BACKSPACE = 259,
    KEY_INSERT = 260,
    KEY_DELETE = 261,
    KEY_RIGHT = 262,
    KEY_LEFT = 263,
    KEY_DOWN = 264,
    KEY_UP = 265,
    KEY_PAGE_UP = 266,
    KEY_PAGE_DOWN = 267,
    KEY_HOME = 268,
    KEY_END = 269,
    KEY_CAPS_LOCK = 280,
    KEY_SCROLL_LOCK = 281,
    KEY_NUM_LOCK = 282,
    KEY_PRINT_SCREEN = 283,
    KEY_PAUSE = 284,
    KEY_F1 = 290,
    KEY_F2 = 291,
    KEY_F3 = 292,
    KEY_F4 = 293,
    KEY_F5 = 294,
    KEY_F6 = 295,
    KEY_F7 = 296,
    KEY_F8 = 297,
    KEY_F9 = 298,
    KEY_F10 = 299,
    KEY_F11 = 300,
    KEY_F12 = 301,
    KEY_F13 = 302,
    KEY_F14 = 303,
    KEY_F15 = 304,
    KEY_F16 = 305,
    KEY_F17 = 306,
    KEY_F18 = 307,
    KEY_F19 = 308,
    KEY_F20 = 309,
    KEY_F21 = 310,
    KEY_F22 = 311,
    KEY_F23 = 312,
    KEY_F24 = 313,
    KEY_F25 = 314,
    KEY_KP_0 = 320,
    KEY_KP_1 = 321,
    KEY_KP_2 = 322,
    KEY_KP_3 = 323,
    KEY_KP_4 = 324,
    KEY_KP_5 = 325,
    KEY_KP_6 = 326,
    KEY_KP_7 = 327,
    KEY_KP_8 = 328,
    KEY_KP_9 = 329,
    KEY_KP_DECIMAL = 330,
    KEY_KP_DIVIDE = 331,
    KEY_KP_MULTIPLY = 332,
    KEY_KP_SUBTRACT = 333,
    KEY_KP_ADD = 334,
    KEY_KP_ENTER = 335,
    KEY_KP_EQUAL = 336,
    KEY_LEFT_SHIFT = 340,
    KEY_LEFT_CONTROL = 341,
    KEY_LEFT_ALT = 342,
    KEY_LEFT_SUPER = 343,
    KEY_RIGHT_SHIFT = 344,
    KEY_RIGHT_CONTROL = 345,
    KEY_RIGHT_ALT = 346,
    KEY_RIGHT_SUPER = 347,
    KEY_MENU = 348,
}

/// Represents a gamepad button.
#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum GamepadButton {
    GAMEPAD_BUTTON_UNKNOWN = 0,
    GAMEPAD_BUTTON_UP = 1,
    GAMEPAD_BUTTON_RIGHT = 2,
    GAMEPAD_BUTTON_DOWN = 3,
    GAMEPAD_BUTTON_LEFT = 4,
    GAMEPAD_BUTTON_Y = 5,
    GAMEPAD_BUTTON_B = 6,
    GAMEPAD_BUTTON_A = 7,
    GAMEPAD_BUTTON_X = 8,
    GAMEPAD_BUTTON_LEFT_SHOULDER = 9,
    GAMEPAD_BUTTON_LEFT_TRIGGER = 10,
    GAMEPAD_BUTTON_RIGHT_SHOULDER = 11,
    GAMEPAD_BUTTON_RIGHT_TRIGGER = 12,
    GAMEPAD_BUTTON_SELECT = 13,
    GAMEPAD_BUTTON_MENU = 14,
    GAMEPAD_BUTTON_START = 15,
    GAMEPAD_BUTTON_LEFT_THUMB = 16,
    GAMEPAD_BUTTON_RIGHT_THUMB = 17,
}

/// Represents a mouse button.
#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum MouseButton {
    MOUSE_BUTTON_UNKNOWN = 0,
    MOUSE_BUTTON_LEFT = 1,
    MOUSE_BUTTON_RIGHT = 2,
    MOUSE_BUTTON_MIDDLE = 3,
}

// Screen and font constants
pub const SCREEN: u32 = 0;
pub const SCREEN_WIDTH: i32 = 640;
pub const SCREEN_HEIGHT: i32 = 480;
pub const FONT_DEFAULT: u32 = 0;

// Color constants
pub const LIGHTGRAY: Color = Color { r: 200, g: 200, b: 200, a: 255 };
pub const GRAY: Color = Color { r: 130, g: 130, b: 130, a: 255 };
pub const DARKGRAY: Color = Color { r: 80, g: 80, b: 80, a: 255 };
pub const YELLOW: Color = Color { r: 253, g: 249, b: 0, a: 255 };
pub const GOLD: Color = Color { r: 255, g: 203, b: 0, a: 255 };
pub const ORANGE: Color = Color { r: 255, g: 161, b: 0, a: 255 };
pub const PINK: Color = Color { r: 255, g: 109, b: 194, a: 255 };
pub const RED: Color = Color { r: 230, g: 41, b: 55, a: 255 };
pub const MAROON: Color = Color { r: 190, g: 33, b: 55, a: 255 };
pub const GREEN: Color = Color { r: 0, g: 228, b: 48, a: 255 };
pub const LIME: Color = Color { r: 0, g: 158, b: 47, a: 255 };
pub const DARKGREEN: Color = Color { r: 0, g: 117, b: 44, a: 255 };
pub const SKYBLUE: Color = Color { r: 102, g: 191, b: 255, a: 255 };
pub const BLUE: Color = Color { r: 0, g: 121, b: 241, a: 255 };
pub const DARKBLUE: Color = Color { r: 0, g: 82, b: 172, a: 255 };
pub const PURPLE: Color = Color { r: 200, g: 122, b: 255, a: 255 };
pub const VIOLET: Color = Color { r: 135, g: 60, b: 190, a: 255 };
pub const DARKPURPLE: Color = Color { r: 112, g: 31, b: 126, a: 255 };
pub const BEIGE: Color = Color { r: 211, g: 176, b: 131, a: 255 };
pub const BROWN: Color = Color { r: 127, g: 106, b: 79, a: 255 };
pub const DARKBROWN: Color = Color { r: 76, g: 63, b: 47, a: 255 };
pub const WHITE: Color = Color { r: 255, g: 255, b: 255, a: 255 };
pub const BLACK: Color = Color { r: 0, g: 0, b: 0, a: 255 };
pub const BLANK: Color = Color { r: 0, g: 0, b: 0, a: 0 };
pub const MAGENTA: Color = Color { r: 255, g: 0, b: 255, a: 255 };
pub const RAYWHITE: Color = Color { r: 245, g: 245, b: 245, a: 255 };

#[link(wasm_import_module = "null0")]
extern "C" {
    // Colors functions
    /// Tint a color with another color.
    pub fn color_tint(color: Color, tint: Color) -> Color;
    /// Fade a color.
    pub fn color_fade(color: Color, alpha: f32) -> Color;
    /// Change the brightness of a color.
    pub fn color_brightness(color: Color, factor: f32) -> Color;
    /// Invert a color.
    pub fn color_invert(color: Color) -> Color;
    /// Blend 2 colors together.
    pub fn color_alpha_blend(dst: Color, src: Color) -> Color;
    /// Change contrast of a color.
    pub fn color_contrast(color: Color, contrast: f32) -> Color;
    /// Interpolate colors.
    pub fn color_bilinear_interpolate(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: f32, coordinateY: f32) -> Color;

    // Graphics functions
    /// Create a new blank image.
    pub fn new_image(width: i32, height: i32, color: Color) -> u32;
    /// Copy an image to a new image.
    pub fn image_copy(image: u32) -> u32;
    /// Create an image from a region of another image.
    pub fn image_subimage(image: u32, x: i32, y: i32, width: i32, height: i32) -> u32;
    /// Clear the screen.
    pub fn clear(color: Color);
    /// Draw a single pixel on the screen.
    pub fn draw_point(x: i32, y: i32, color: Color);
    /// Draw a line on the screen.
    pub fn draw_line(startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color);
    /// Draw a filled rectangle on the screen.
    pub fn draw_rectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color);
    /// Draw a filled triangle on the screen.
    pub fn draw_triangle(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color);
    /// Draw a filled ellipse on the screen.
    pub fn draw_ellipse(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color);
    /// Draw a filled circle on the screen.
    pub fn draw_circle(centerX: i32, centerY: i32, radius: i32, color: Color);
    /// Draw a filled polygon on the screen.
    pub fn draw_polygon(points: *const Vector, numPoints: i32, color: Color);
    /// Draw a filled arc on the screen.
    pub fn draw_arc(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, color: Color);
    /// Draw a filled round-rectangle on the screen.
    pub fn draw_rectangle_rounded(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color);
    /// Draw an image on the screen.
    pub fn draw_image(src: u32, posX: i32, posY: i32);
    /// Draw a tinted image on the screen.
    pub fn draw_image_tint(src: u32, posX: i32, posY: i32, tint: Color);
    /// Draw an image, rotated, on the screen.
    pub fn draw_image_rotated(src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter);
    /// Draw an image, flipped, on the screen.
    pub fn draw_image_flipped(src: u32, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool);
    /// Draw an image, scaled, on the screen.
    pub fn draw_image_scaled(src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter);
    /// Draw some text on the screen.
    pub fn draw_text(font: u32, text: *const u8, posX: i32, posY: i32, color: Color);
    /// Save an image to persistant storage.
    pub fn save_image(image: u32, filename: *const u8);
    /// Load an image from a file in cart.
    pub fn load_image(filename: *const u8) -> u32;
    /// Resize an image, return copy.
    pub fn image_resize(image: u32, newWidth: i32, newHeight: i32, filter: ImageFilter) -> u32;
    /// Scale an image, return copy.
    pub fn image_scale(image: u32, scaleX: f32, scaleY: f32, filter: ImageFilter) -> u32;
    /// Replace a color in an image, in-place.
    pub fn image_color_replace(image: u32, color: Color, replace: Color);
    /// Tint a color in an image, in-place.
    pub fn image_color_tint(image: u32, color: Color);
    /// Fade a color in an image, in-place.
    pub fn image_color_fade(image: u32, alpha: f32);
    /// Copy a font to a new font.
    pub fn font_copy(font: u32) -> u32;
    /// Scale a font, return a new font.
    pub fn font_scale(font: u32, scaleX: f32, scaleY: f32, filter: ImageFilter) -> u32;
    /// Load a BMF font from a file in cart.
    pub fn load_font_bmf(filename: *const u8, characters: *const u8) -> u32;
    /// Load a BMF font from an image.
    pub fn load_font_bmf_from_image(image: u32, characters: *const u8) -> u32;
    /// Measure the size of some text.
    pub fn measure_text(font: u32, text: *const u8, textLength: i32) -> Dimensions;
    /// Meaure an image (use 0 for screen).
    pub fn measure_image(image: u32) -> Dimensions;
    /// Load a TTY font from a file in cart.
    pub fn load_font_tty(filename: *const u8, glyphWidth: i32, glyphHeight: i32, characters: *const u8) -> u32;
    /// Load a TTY font from an image.
    pub fn load_font_tty_from_image(image: u32, glyphWidth: i32, glyphHeight: i32, characters: *const u8) -> u32;
    /// Load a TTF font from a file in cart.
    pub fn load_font_ttf(filename: *const u8, fontSize: i32) -> u32;
    /// Invert the colors in an image, in-place.
    pub fn image_color_invert(image: u32);
    /// Calculate a rectangle representing the available alpha border in an image.
    pub fn image_alpha_border(image: u32, threshold: f32) -> Rectangle;
    /// Crop an image, in-place.
    pub fn image_crop(image: u32, x: i32, y: i32, width: i32, height: i32);
    /// Crop an image based on the alpha border, in-place.
    pub fn image_alpha_crop(image: u32, threshold: f32);
    /// Adjust the brightness of an image, in-place.
    pub fn image_color_brightness(image: u32, factor: f32);
    /// Flip an image, in-place.
    pub fn image_flip(image: u32, horizontal: bool, vertical: bool);
    /// Change the contrast of an image, in-place.
    pub fn image_color_contrast(image: u32, contrast: f32);
    /// Use an image as an alpha-mask on another image.
    pub fn image_alpha_mask(image: u32, alphaMask: u32, posX: i32, posY: i32);
    /// Create a new image, rotating another image.
    pub fn image_rotate(image: u32, degrees: f32, filter: ImageFilter) -> u32;
    /// Create a new image of a gradient.
    pub fn image_gradient(width: i32, height: i32, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color) -> u32;
    /// Unload an image.
    pub fn unload_image(image: u32);
    /// Unload a font.
    pub fn unload_font(font: u32);
    /// Clear an image.
    pub fn clear_image(destination: u32, color: Color);
    /// Draw a single pixel on an image.
    pub fn draw_point_on_image(destination: u32, x: i32, y: i32, color: Color);
    /// Draw a line on an image.
    pub fn draw_line_on_image(destination: u32, startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color);
    /// Draw a filled rectangle on an image.
    pub fn draw_rectangle_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, color: Color);
    /// Draw a filled triangle on an image.
    pub fn draw_triangle_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color);
    /// Draw a filled ellipse on an image.
    pub fn draw_ellipse_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color);
    /// Draw a circle on an image.
    pub fn draw_circle_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, color: Color);
    /// Draw a filled polygon on an image.
    pub fn draw_polygon_on_image(destination: u32, points: *const Vector, numPoints: i32, color: Color);
    /// Draw a filled round-rectangle on an image.
    pub fn draw_rectangle_rounded_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color);
    /// Draw an image on an image.
    pub fn draw_image_on_image(destination: u32, src: u32, posX: i32, posY: i32);
    /// Draw a tinted image on an image.
    pub fn draw_image_tint_on_image(destination: u32, src: u32, posX: i32, posY: i32, tint: Color);
    /// Draw an image, rotated, on an image.
    pub fn draw_image_rotated_on_image(destination: u32, src: u32, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter);
    /// Draw an image, flipped, on an image.
    pub fn draw_image_flipped_on_image(destination: u32, src: u32, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool);
    /// Draw an image, scaled, on an image.
    pub fn draw_image_scaled_on_image(destination: u32, src: u32, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter);
    /// Draw some text on an image.
    pub fn draw_text_on_image(destination: u32, font: u32, text: *const u8, posX: i32, posY: i32, color: Color);
    /// Draw a outlined (with thickness) rectangle on the screen.
    pub fn draw_rectangle_outline(posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) triangle on the screen.
    pub fn draw_triangle_outline(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) ellipse on the screen.
    pub fn draw_ellipse_outline(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) circle on the screen.
    pub fn draw_circle_outline(centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) polygon on the screen.
    pub fn draw_polygon_outline(points: *const Vector, numPoints: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) arc on the screen.
    pub fn draw_arc_outline(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) round-rectangle on the screen.
    pub fn draw_rectangle_rounded_outline(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) rectangle on an image.
    pub fn draw_rectangle_outline_on_image(destination: u32, posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) triangle on an image.
    pub fn draw_triangle_outline_on_image(destination: u32, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) ellipse on an image.
    pub fn draw_ellipse_outline_on_image(destination: u32, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) circle on an image.
    pub fn draw_circle_outline_on_image(destination: u32, centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) polygon on an image.
    pub fn draw_polygon_outline_on_image(destination: u32, points: *const Vector, numPoints: i32, thickness: i32, color: Color);
    /// Draw a outlined (with thickness) round-rectangle on an image.
    pub fn draw_rectangle_rounded_outline_on_image(destination: u32, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color);

    // Input functions
    /// Has the key been pressed? (tracks unpress/read correctly.)
    pub fn key_pressed(key: Key) -> bool;
    /// Is the key currently down?
    pub fn key_down(key: Key) -> bool;
    /// Has the key been released? (tracks press/read correctly.)
    pub fn key_released(key: Key) -> bool;
    /// Is the key currently up?
    pub fn key_up(key: Key) -> bool;
    /// Has the button been pressed? (tracks unpress/read correctly.)
    pub fn gamepad_button_pressed(gamepad: i32, button: GamepadButton) -> bool;
    /// Is the button currently down?
    pub fn gamepad_button_down(gamepad: i32, button: GamepadButton) -> bool;
    /// Has the button been released? (tracks press/read correctly.)
    pub fn gamepad_button_released(gamepad: i32, button: GamepadButton) -> bool;
    /// Get current position of mouse.
    pub fn mouse_position() -> Vector;
    /// Has the button been pressed? (tracks unpress/read correctly.)
    pub fn mouse_button_pressed(button: MouseButton) -> bool;
    /// Is the button currently down?
    pub fn mouse_button_down(button: MouseButton) -> bool;
    /// Has the button been released? (tracks press/read correctly.)
    pub fn mouse_button_released(button: MouseButton) -> bool;
    /// Is the button currently up?
    pub fn mouse_button_up(button: MouseButton) -> bool;

    // Sound functions
    /// Load a sound from a file in cart.
    pub fn load_sound(filename: *const u8) -> u32;
    /// Play a sound.
    pub fn play_sound(sound: u32, r#loop: bool);
    /// Stop a sound.
    pub fn stop_sound(sound: u32);
    /// Unload a sound.
    pub fn unload_sound(sound: u32);
    /// Speak some text and return a sound. Set things to 0 for defaults.
    pub fn tts_sound(text: *const u8, phonetic: bool, pitch: i32, speed: i32, throat: i32, mouth: i32, sing: bool) -> u32;
    /// Create Sfx sound.
    pub fn sfx_sound(params: SfxParams) -> u32;
    /// Create Sfx parameters.
    pub fn sfx_generate(r#type: SfxPresetType) -> SfxParams;

    // Types functions

    // Utilities functions
    /// Get system-time (ms) since unix epoch.
    pub fn current_time() -> u64;
    /// Get the change in time (seconds) since the last update run.
    pub fn delta_time() -> f32;
    /// Get a random integer between 2 numbers.
    pub fn random_int(min: i32, max: i32) -> i32;
    /// Get the random-seed.
    pub fn random_seed_get() -> u64;
    /// Set the random-seed.
    pub fn random_seed_set(seed: u64);

}

// Convenience implementations
impl Color {
    /// Create a new Color
    pub const fn new(r: u8, g: u8, b: u8, a: u8) -> Self {
        Self { r, g, b, a }
    }
    
    /// Create a new Color with full opacity
    pub const fn rgb(r: u8, g: u8, b: u8) -> Self {
        Self { r, g, b, a: 255 }
    }
}

impl Vector {
    /// Create a new Vector
    pub const fn new(x: i32, y: i32) -> Self {
        Self { x, y }
    }
}

impl Rectangle {
    /// Create a new Rectangle
    pub const fn new(x: i32, y: i32, width: i32, height: i32) -> Self {
        Self { x, y, width, height }
    }
}

impl Dimensions {
    /// Create a new Dimensions
    pub const fn new(width: i32, height: i32) -> Self {
        Self { width, height }
    }
}

/// Convert a Rust string to a C-compatible string pointer
/// 
/// # Safety
/// The returned pointer is only valid as long as the input string slice is valid.
/// The string must be null-terminated.
pub fn str_to_cstr(s: &str) -> *const u8 {
    s.as_ptr()
}

/// Helper macro to create null-terminated string literals
#[macro_export]
macro_rules! cstr {
    ($s:expr) => {
        concat!($s, "\0").as_ptr()
    };
}

// Types are already public in this module, no need to re-export