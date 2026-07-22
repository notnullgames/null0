//! null0 - Zig bindings for the null0 fantasy console
//!
//! Usage:
//!
//! ```zig
//! const null0 = @import("null0.zig");
//!
//! export fn load() void {
//!     null0.clear(null0.BLUE);
//!     null0.draw_circle(100, 100, 50, null0.RED);
//! }
//! ```

const std = @import("std");

// basic memory-management from host (used when host returns strings/structs)

export fn malloc(size: usize) ?*anyopaque {
    const buf = std.heap.wasm_allocator.alloc(u8, size) catch return null;
    return @ptrCast(buf.ptr);
}

export fn free(ptr: ?*anyopaque) void {
    // carts are short-lived, let the wasm linear-memory absorb it
    _ = ptr;
}

// scalar types
pub const Image = u32;
pub const Font = u32;
pub const Sound = u32;

/// An RGBA color, packed into a single u32 (ABI-compatible with host)
pub const Color = packed struct(u32) {
    r: u8,
    g: u8,
    b: u8,
    a: u8,

    pub fn rgb(r: u8, g: u8, b: u8) Color {
        return .{ .r = r, .g = g, .b = b, .a = 255 };
    }
};

/// Sfx parameters.
pub const SfxParams = extern struct {
    randSeed: u32 = 0,
    waveType: i32 = 0,
    attackTime: f32 = 0,
    sustainTime: f32 = 0,
    sustainPunch: f32 = 0,
    decayTime: f32 = 0,
    startFrequency: f32 = 0,
    minFrequency: f32 = 0,
    slide: f32 = 0,
    deltaSlide: f32 = 0,
    vibratoDepth: f32 = 0,
    vibratoSpeed: f32 = 0,
    changeAmount: f32 = 0,
    changeSpeed: f32 = 0,
    squareDuty: f32 = 0,
    dutySweep: f32 = 0,
    repeatSpeed: f32 = 0,
    phaserOffset: f32 = 0,
    phaserSweep: f32 = 0,
    lpfCutoff: f32 = 0,
    lpfCutoffSweep: f32 = 0,
    lpfResonance: f32 = 0,
    hpfCutoff: f32 = 0,
    hpfCutoffSweep: f32 = 0,
};

/// The 2D size of something (width/height.)
pub const Dimensions = extern struct {
    width: i32 = 0,
    height: i32 = 0,
};

/// The 2D position of something (x/y.)
pub const Vector = extern struct {
    x: i32 = 0,
    y: i32 = 0,
};

/// The 2D position + size of something (x/y/w/h.)
pub const Rectangle = extern struct {
    x: i32 = 0,
    y: i32 = 0,
    width: i32 = 0,
    height: i32 = 0,
};

/// Potential image-filtering techniques for scale/etc.
pub const ImageFilter = enum(i32) {
    FILTER_NEARESTNEIGHBOR = 0,
    FILTER_BILINEAR = 1,
    FILTER_SMOOTH = 2,
};

/// Represents a Sfx preset type.
pub const SfxPresetType = enum(i32) {
    SFX_COIN = 0,
    SFX_LASER = 1,
    SFX_EXPLOSION = 2,
    SFX_POWERUP = 3,
    SFX_HURT = 4,
    SFX_JUMP = 5,
    SFX_SELECT = 6,
    SFX_SYNTH = 7,
};

/// Represents a keyboard key.
pub const Key = enum(i32) {
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
};

/// Represents a gamepad button.
pub const GamepadButton = enum(i32) {
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
};

/// Represents a mouse button.
pub const MouseButton = enum(i32) {
    MOUSE_BUTTON_UNKNOWN = 0,
    MOUSE_BUTTON_LEFT = 1,
    MOUSE_BUTTON_RIGHT = 2,
    MOUSE_BUTTON_MIDDLE = 3,
};

// Constants
pub const SCREEN: Image = 0;
pub const SCREEN_WIDTH: i32 = 640;
pub const SCREEN_HEIGHT: i32 = 480;
pub const FONT_DEFAULT: Font = 0;

pub const LIGHTGRAY: Color = .{ .r = 200, .g = 200, .b = 200, .a = 255 };
pub const GRAY: Color = .{ .r = 130, .g = 130, .b = 130, .a = 255 };
pub const DARKGRAY: Color = .{ .r = 80, .g = 80, .b = 80, .a = 255 };
pub const YELLOW: Color = .{ .r = 253, .g = 249, .b = 0, .a = 255 };
pub const GOLD: Color = .{ .r = 255, .g = 203, .b = 0, .a = 255 };
pub const ORANGE: Color = .{ .r = 255, .g = 161, .b = 0, .a = 255 };
pub const PINK: Color = .{ .r = 255, .g = 109, .b = 194, .a = 255 };
pub const RED: Color = .{ .r = 230, .g = 41, .b = 55, .a = 255 };
pub const MAROON: Color = .{ .r = 190, .g = 33, .b = 55, .a = 255 };
pub const GREEN: Color = .{ .r = 0, .g = 228, .b = 48, .a = 255 };
pub const LIME: Color = .{ .r = 0, .g = 158, .b = 47, .a = 255 };
pub const DARKGREEN: Color = .{ .r = 0, .g = 117, .b = 44, .a = 255 };
pub const SKYBLUE: Color = .{ .r = 102, .g = 191, .b = 255, .a = 255 };
pub const BLUE: Color = .{ .r = 0, .g = 121, .b = 241, .a = 255 };
pub const DARKBLUE: Color = .{ .r = 0, .g = 82, .b = 172, .a = 255 };
pub const PURPLE: Color = .{ .r = 200, .g = 122, .b = 255, .a = 255 };
pub const VIOLET: Color = .{ .r = 135, .g = 60, .b = 190, .a = 255 };
pub const DARKPURPLE: Color = .{ .r = 112, .g = 31, .b = 126, .a = 255 };
pub const BEIGE: Color = .{ .r = 211, .g = 176, .b = 131, .a = 255 };
pub const BROWN: Color = .{ .r = 127, .g = 106, .b = 79, .a = 255 };
pub const DARKBROWN: Color = .{ .r = 76, .g = 63, .b = 47, .a = 255 };
pub const WHITE: Color = .{ .r = 255, .g = 255, .b = 255, .a = 255 };
pub const BLACK: Color = .{ .r = 0, .g = 0, .b = 0, .a = 255 };
pub const BLANK: Color = .{ .r = 0, .g = 0, .b = 0, .a = 0 };
pub const MAGENTA: Color = .{ .r = 255, .g = 0, .b = 255, .a = 255 };
pub const RAYWHITE: Color = .{ .r = 245, .g = 245, .b = 245, .a = 255 };

// COLORS
/// Tint a color with another color.
pub extern "null0" fn color_tint(color: Color, tint: Color) *Color;
/// Fade a color.
pub extern "null0" fn color_fade(color: Color, alpha: f32) *Color;
/// Change the brightness of a color.
pub extern "null0" fn color_brightness(color: Color, factor: f32) *Color;
/// Invert a color.
pub extern "null0" fn color_invert(color: Color) *Color;
/// Blend 2 colors together.
pub extern "null0" fn color_alpha_blend(dst: Color, src: Color) *Color;
/// Change contrast of a color.
pub extern "null0" fn color_contrast(color: Color, contrast: f32) *Color;
/// Interpolate colors.
pub extern "null0" fn color_bilinear_interpolate(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: f32, coordinateY: f32) *Color;

// GRAPHICS
/// Create a new blank image.
pub extern "null0" fn new_image(width: i32, height: i32, color: Color) Image;
/// Copy an image to a new image.
pub extern "null0" fn image_copy(image: Image) Image;
/// Create an image from a region of another image.
pub extern "null0" fn image_subimage(image: Image, x: i32, y: i32, width: i32, height: i32) Image;
/// Clear the screen.
pub extern "null0" fn clear(color: Color) void;
/// Draw a single pixel on the screen.
pub extern "null0" fn draw_point(x: i32, y: i32, color: Color) void;
/// Draw a line on the screen.
pub extern "null0" fn draw_line(startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color) void;
/// Draw a filled rectangle on the screen.
pub extern "null0" fn draw_rectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color) void;
/// Draw a filled triangle on the screen.
pub extern "null0" fn draw_triangle(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color) void;
/// Draw a filled ellipse on the screen.
pub extern "null0" fn draw_ellipse(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color) void;
/// Draw a filled circle on the screen.
pub extern "null0" fn draw_circle(centerX: i32, centerY: i32, radius: i32, color: Color) void;
/// Draw a filled polygon on the screen.
pub extern "null0" fn draw_polygon(points: [*]const Vector, numPoints: i32, color: Color) void;
/// Draw a filled arc on the screen.
pub extern "null0" fn draw_arc(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, color: Color) void;
/// Draw a filled round-rectangle on the screen.
pub extern "null0" fn draw_rectangle_rounded(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color) void;
/// Draw an image on the screen.
pub extern "null0" fn draw_image(src: Image, posX: i32, posY: i32) void;
/// Draw a tinted image on the screen.
pub extern "null0" fn draw_image_tint(src: Image, posX: i32, posY: i32, tint: Color) void;
/// Draw an image, rotated, on the screen.
pub extern "null0" fn draw_image_rotated(src: Image, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) void;
/// Draw an image, flipped, on the screen.
pub extern "null0" fn draw_image_flipped(src: Image, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) void;
/// Draw an image, scaled, on the screen.
pub extern "null0" fn draw_image_scaled(src: Image, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) void;
/// Draw some text on the screen.
pub extern "null0" fn draw_text(font: Font, text: [*:0]const u8, posX: i32, posY: i32, color: Color) void;
/// Save an image to persistant storage.
pub extern "null0" fn save_image(image: Image, filename: [*:0]const u8) void;
/// Load an image from a file in cart.
pub extern "null0" fn load_image(filename: [*:0]const u8) Image;
/// Resize an image, return copy.
pub extern "null0" fn image_resize(image: Image, newWidth: i32, newHeight: i32, filter: ImageFilter) Image;
/// Scale an image, return copy.
pub extern "null0" fn image_scale(image: Image, scaleX: f32, scaleY: f32, filter: ImageFilter) Image;
/// Replace a color in an image, in-place.
pub extern "null0" fn image_color_replace(image: Image, color: Color, replace: Color) void;
/// Tint a color in an image, in-place.
pub extern "null0" fn image_color_tint(image: Image, color: Color) void;
/// Fade a color in an image, in-place.
pub extern "null0" fn image_color_fade(image: Image, alpha: f32) void;
/// Copy a font to a new font.
pub extern "null0" fn font_copy(font: Font) Font;
/// Scale a font, return a new font.
pub extern "null0" fn font_scale(font: Font, scaleX: f32, scaleY: f32, filter: ImageFilter) Font;
/// Load a BMF font from a file in cart.
pub extern "null0" fn load_font_bmf(filename: [*:0]const u8, characters: [*:0]const u8) Font;
/// Load a BMF font from an image.
pub extern "null0" fn load_font_bmf_from_image(image: Image, characters: [*:0]const u8) Font;
/// Measure the size of some text.
pub extern "null0" fn measure_text(font: Font, text: [*:0]const u8, textLength: i32) *Dimensions;
/// Meaure an image (use 0 for screen).
pub extern "null0" fn measure_image(image: Image) *Dimensions;
/// Load a TTY font from a file in cart.
pub extern "null0" fn load_font_tty(filename: [*:0]const u8, glyphWidth: i32, glyphHeight: i32, characters: [*:0]const u8) Font;
/// Load a TTY font from an image.
pub extern "null0" fn load_font_tty_from_image(image: Image, glyphWidth: i32, glyphHeight: i32, characters: [*:0]const u8) Font;
/// Load a TTF font from a file in cart.
pub extern "null0" fn load_font_ttf(filename: [*:0]const u8, fontSize: i32) Font;
/// Invert the colors in an image, in-place.
pub extern "null0" fn image_color_invert(image: Image) void;
/// Calculate a rectangle representing the available alpha border in an image.
pub extern "null0" fn image_alpha_border(image: Image, threshold: f32) *Rectangle;
/// Crop an image, in-place.
pub extern "null0" fn image_crop(image: Image, x: i32, y: i32, width: i32, height: i32) void;
/// Crop an image based on the alpha border, in-place.
pub extern "null0" fn image_alpha_crop(image: Image, threshold: f32) void;
/// Adjust the brightness of an image, in-place.
pub extern "null0" fn image_color_brightness(image: Image, factor: f32) void;
/// Flip an image, in-place.
pub extern "null0" fn image_flip(image: Image, horizontal: bool, vertical: bool) void;
/// Change the contrast of an image, in-place.
pub extern "null0" fn image_color_contrast(image: Image, contrast: f32) void;
/// Use an image as an alpha-mask on another image.
pub extern "null0" fn image_alpha_mask(image: Image, alphaMask: Image, posX: i32, posY: i32) void;
/// Create a new image, rotating another image.
pub extern "null0" fn image_rotate(image: Image, degrees: f32, filter: ImageFilter) Image;
/// Create a new image of a gradient.
pub extern "null0" fn image_gradient(width: i32, height: i32, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color) Image;
/// Unload an image.
pub extern "null0" fn unload_image(image: Image) void;
/// Unload a font.
pub extern "null0" fn unload_font(font: Font) void;
/// Clear an image.
pub extern "null0" fn clear_image(destination: Image, color: Color) void;
/// Draw a single pixel on an image.
pub extern "null0" fn draw_point_on_image(destination: Image, x: i32, y: i32, color: Color) void;
/// Draw a line on an image.
pub extern "null0" fn draw_line_on_image(destination: Image, startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color) void;
/// Draw a filled rectangle on an image.
pub extern "null0" fn draw_rectangle_on_image(destination: Image, posX: i32, posY: i32, width: i32, height: i32, color: Color) void;
/// Draw a filled triangle on an image.
pub extern "null0" fn draw_triangle_on_image(destination: Image, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color) void;
/// Draw a filled ellipse on an image.
pub extern "null0" fn draw_ellipse_on_image(destination: Image, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color) void;
/// Draw a circle on an image.
pub extern "null0" fn draw_circle_on_image(destination: Image, centerX: i32, centerY: i32, radius: i32, color: Color) void;
/// Draw a filled polygon on an image.
pub extern "null0" fn draw_polygon_on_image(destination: Image, points: [*]const Vector, numPoints: i32, color: Color) void;
/// Draw a filled round-rectangle on an image.
pub extern "null0" fn draw_rectangle_rounded_on_image(destination: Image, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color) void;
/// Draw an image on an image.
pub extern "null0" fn draw_image_on_image(destination: Image, src: Image, posX: i32, posY: i32) void;
/// Draw a tinted image on an image.
pub extern "null0" fn draw_image_tint_on_image(destination: Image, src: Image, posX: i32, posY: i32, tint: Color) void;
/// Draw an image, rotated, on an image.
pub extern "null0" fn draw_image_rotated_on_image(destination: Image, src: Image, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) void;
/// Draw an image, flipped, on an image.
pub extern "null0" fn draw_image_flipped_on_image(destination: Image, src: Image, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) void;
/// Draw an image, scaled, on an image.
pub extern "null0" fn draw_image_scaled_on_image(destination: Image, src: Image, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) void;
/// Draw some text on an image.
pub extern "null0" fn draw_text_on_image(destination: Image, font: Font, text: [*:0]const u8, posX: i32, posY: i32, color: Color) void;
/// Draw a outlined (with thickness) rectangle on the screen.
pub extern "null0" fn draw_rectangle_outline(posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) triangle on the screen.
pub extern "null0" fn draw_triangle_outline(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) ellipse on the screen.
pub extern "null0" fn draw_ellipse_outline(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) circle on the screen.
pub extern "null0" fn draw_circle_outline(centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) polygon on the screen.
pub extern "null0" fn draw_polygon_outline(points: [*]const Vector, numPoints: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) arc on the screen.
pub extern "null0" fn draw_arc_outline(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) round-rectangle on the screen.
pub extern "null0" fn draw_rectangle_rounded_outline(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) rectangle on an image.
pub extern "null0" fn draw_rectangle_outline_on_image(destination: Image, posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) triangle on an image.
pub extern "null0" fn draw_triangle_outline_on_image(destination: Image, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) ellipse on an image.
pub extern "null0" fn draw_ellipse_outline_on_image(destination: Image, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) circle on an image.
pub extern "null0" fn draw_circle_outline_on_image(destination: Image, centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) polygon on an image.
pub extern "null0" fn draw_polygon_outline_on_image(destination: Image, points: [*]const Vector, numPoints: i32, thickness: i32, color: Color) void;
/// Draw a outlined (with thickness) round-rectangle on an image.
pub extern "null0" fn draw_rectangle_rounded_outline_on_image(destination: Image, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color) void;

// INPUT
/// Has the key been pressed? (tracks unpress/read correctly.)
pub extern "null0" fn key_pressed(key: Key) bool;
/// Is the key currently down?
pub extern "null0" fn key_down(key: Key) bool;
/// Has the key been released? (tracks press/read correctly.)
pub extern "null0" fn key_released(key: Key) bool;
/// Is the key currently up?
pub extern "null0" fn key_up(key: Key) bool;
/// Has the button been pressed? (tracks unpress/read correctly.)
pub extern "null0" fn gamepad_button_pressed(gamepad: i32, button: GamepadButton) bool;
/// Is the button currently down?
pub extern "null0" fn gamepad_button_down(gamepad: i32, button: GamepadButton) bool;
/// Has the button been released? (tracks press/read correctly.)
pub extern "null0" fn gamepad_button_released(gamepad: i32, button: GamepadButton) bool;
/// Get current position of mouse.
pub extern "null0" fn mouse_position() *Vector;
/// Has the button been pressed? (tracks unpress/read correctly.)
pub extern "null0" fn mouse_button_pressed(button: MouseButton) bool;
/// Is the button currently down?
pub extern "null0" fn mouse_button_down(button: MouseButton) bool;
/// Has the button been released? (tracks press/read correctly.)
pub extern "null0" fn mouse_button_released(button: MouseButton) bool;
/// Is the button currently up?
pub extern "null0" fn mouse_button_up(button: MouseButton) bool;

// SOUND
/// Load a sound from a file in cart.
pub extern "null0" fn load_sound(filename: [*:0]const u8) Sound;
/// Play a sound.
pub extern "null0" fn play_sound(sound: Sound, loop: bool) void;
/// Stop a sound.
pub extern "null0" fn stop_sound(sound: Sound) void;
/// Unload a sound.
pub extern "null0" fn unload_sound(sound: Sound) void;
/// Speak some text and return a sound. Set things to 0 for defaults.
pub extern "null0" fn tts_sound(text: [*:0]const u8, phonetic: bool, pitch: i32, speed: i32, throat: i32, mouth: i32, sing: bool) Sound;
/// Create Sfx sound.
pub extern "null0" fn sfx_sound(params: *const SfxParams) Sound;
/// Create Sfx parameters.
pub extern "null0" fn sfx_generate(type: SfxPresetType) *SfxParams;

// TYPES

// UTILITIES
/// Get system-time (ms) since unix epoch.
pub extern "null0" fn current_time() u64;
/// Get the change in time (seconds) since the last update run.
pub extern "null0" fn delta_time() f32;
/// Get a random integer between 2 numbers.
pub extern "null0" fn random_int(min: i32, max: i32) i32;
/// Get the random-seed.
pub extern "null0" fn random_seed_get() u64;
/// Set the random-seed.
pub extern "null0" fn random_seed_set(seed: u64) void;
