//! null0 - D bindings for the null0 fantasy console
//!
//! Usage:
//!
//! ```d
//! import null0;
//!
//! export extern(C) void load() {
//!     clear(BLUE);
//!     draw_circle(100, 100, 50, RED);
//! }
//! ```
module null0;

import ldc.attributes;

alias Image = uint;
alias Font = uint;
alias Sound = uint;

/// An RGBA color, packed into a single uint (ABI-compatible with host)
alias Color = uint;

/// Create a Color from r, g, b, a components
Color rgba(ubyte r, ubyte g, ubyte b, ubyte a) {
    return cast(uint)r | (cast(uint)g << 8) | (cast(uint)b << 16) | (cast(uint)a << 24);
}

/// Create an opaque Color from r, g, b components
Color rgb(ubyte r, ubyte g, ubyte b) {
    return rgba(r, g, b, 255);
}

// basic memory-management from host (used when host returns strings/structs)

extern(C) extern __gshared ubyte __heap_base;
private __gshared ubyte* heapPtr;

export extern(C) void* malloc(size_t size) {
    if (heapPtr is null) heapPtr = &__heap_base;
    void* p = heapPtr;
    heapPtr += (size + 15) & ~cast(size_t)15;
    return p;
}

export extern(C) void free(void* ptr) {
    // carts are short-lived, let the wasm linear-memory absorb it
}

/// Sfx parameters.
struct SfxParams {
    uint randSeed;
    int waveType;
    float attackTime;
    float sustainTime;
    float sustainPunch;
    float decayTime;
    float startFrequency;
    float minFrequency;
    float slide;
    float deltaSlide;
    float vibratoDepth;
    float vibratoSpeed;
    float changeAmount;
    float changeSpeed;
    float squareDuty;
    float dutySweep;
    float repeatSpeed;
    float phaserOffset;
    float phaserSweep;
    float lpfCutoff;
    float lpfCutoffSweep;
    float lpfResonance;
    float hpfCutoff;
    float hpfCutoffSweep;
}

/// The 2D size of something (width/height.)
struct Dimensions {
    int width;
    int height;
}

/// The 2D position of something (x/y.)
struct Vector {
    int x;
    int y;
}

/// The 2D position + size of something (x/y/w/h.)
struct Rectangle {
    int x;
    int y;
    int width;
    int height;
}

/// Potential image-filtering techniques for scale/etc.
enum ImageFilter : int {
    FILTER_NEARESTNEIGHBOR = 0,
    FILTER_BILINEAR = 1,
    FILTER_SMOOTH = 2,
}

/// Represents a Sfx preset type.
enum SfxPresetType : int {
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
enum Key : int {
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
enum GamepadButton : int {
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
enum MouseButton : int {
    MOUSE_BUTTON_UNKNOWN = 0,
    MOUSE_BUTTON_LEFT = 1,
    MOUSE_BUTTON_RIGHT = 2,
    MOUSE_BUTTON_MIDDLE = 3,
}

// Constants
enum Image SCREEN = 0;
enum int SCREEN_WIDTH = 640;
enum int SCREEN_HEIGHT = 480;
enum Font FONT_DEFAULT = 0;

// Colors
enum Color LIGHTGRAY = 0xffc8c8c8; // rgba(200, 200, 200, 255)
enum Color GRAY = 0xff828282; // rgba(130, 130, 130, 255)
enum Color DARKGRAY = 0xff505050; // rgba(80, 80, 80, 255)
enum Color YELLOW = 0xff00f9fd; // rgba(253, 249, 0, 255)
enum Color GOLD = 0xff00cbff; // rgba(255, 203, 0, 255)
enum Color ORANGE = 0xff00a1ff; // rgba(255, 161, 0, 255)
enum Color PINK = 0xffc26dff; // rgba(255, 109, 194, 255)
enum Color RED = 0xff3729e6; // rgba(230, 41, 55, 255)
enum Color MAROON = 0xff3721be; // rgba(190, 33, 55, 255)
enum Color GREEN = 0xff30e400; // rgba(0, 228, 48, 255)
enum Color LIME = 0xff2f9e00; // rgba(0, 158, 47, 255)
enum Color DARKGREEN = 0xff2c7500; // rgba(0, 117, 44, 255)
enum Color SKYBLUE = 0xffffbf66; // rgba(102, 191, 255, 255)
enum Color BLUE = 0xfff17900; // rgba(0, 121, 241, 255)
enum Color DARKBLUE = 0xffac5200; // rgba(0, 82, 172, 255)
enum Color PURPLE = 0xffff7ac8; // rgba(200, 122, 255, 255)
enum Color VIOLET = 0xffbe3c87; // rgba(135, 60, 190, 255)
enum Color DARKPURPLE = 0xff7e1f70; // rgba(112, 31, 126, 255)
enum Color BEIGE = 0xff83b0d3; // rgba(211, 176, 131, 255)
enum Color BROWN = 0xff4f6a7f; // rgba(127, 106, 79, 255)
enum Color DARKBROWN = 0xff2f3f4c; // rgba(76, 63, 47, 255)
enum Color WHITE = 0xffffffff; // rgba(255, 255, 255, 255)
enum Color BLACK = 0xff000000; // rgba(0, 0, 0, 255)
enum Color BLANK = 0x00000000; // rgba(0, 0, 0, 0)
enum Color MAGENTA = 0xffff00ff; // rgba(255, 0, 255, 255)
enum Color RAYWHITE = 0xfff5f5f5; // rgba(245, 245, 245, 255)

// COLORS
/// Tint a color with another color.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "color_tint"))
extern(C) Color* color_tint(Color color, Color tint);
/// Fade a color.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "color_fade"))
extern(C) Color* color_fade(Color color, float alpha);
/// Change the brightness of a color.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "color_brightness"))
extern(C) Color* color_brightness(Color color, float factor);
/// Invert a color.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "color_invert"))
extern(C) Color* color_invert(Color color);
/// Blend 2 colors together.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "color_alpha_blend"))
extern(C) Color* color_alpha_blend(Color dst, Color src);
/// Change contrast of a color.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "color_contrast"))
extern(C) Color* color_contrast(Color color, float contrast);
/// Interpolate colors.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "color_bilinear_interpolate"))
extern(C) Color* color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, float coordinateX, float coordinateY);

// GRAPHICS
/// Create a new blank image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "new_image"))
extern(C) Image new_image(int width, int height, Color color);
/// Copy an image to a new image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_copy"))
extern(C) Image image_copy(Image image);
/// Create an image from a region of another image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_subimage"))
extern(C) Image image_subimage(Image image, int x, int y, int width, int height);
/// Clear the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "clear"))
extern(C) void clear(Color color);
/// Draw a single pixel on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_point"))
extern(C) void draw_point(int x, int y, Color color);
/// Draw a line on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_line"))
extern(C) void draw_line(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
/// Draw a filled rectangle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle"))
extern(C) void draw_rectangle(int posX, int posY, int width, int height, Color color);
/// Draw a filled triangle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_triangle"))
extern(C) void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color);
/// Draw a filled ellipse on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_ellipse"))
extern(C) void draw_ellipse(int centerX, int centerY, int radiusX, int radiusY, Color color);
/// Draw a filled circle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_circle"))
extern(C) void draw_circle(int centerX, int centerY, int radius, Color color);
/// Draw a filled polygon on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_polygon"))
extern(C) void draw_polygon(const(Vector)* points, int numPoints, Color color);
/// Draw a filled arc on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_arc"))
extern(C) void draw_arc(int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, Color color);
/// Draw a filled round-rectangle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle_rounded"))
extern(C) void draw_rectangle_rounded(int x, int y, int width, int height, int cornerRadius, Color color);
/// Draw an image on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image"))
extern(C) void draw_image(Image src, int posX, int posY);
/// Draw a tinted image on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_tint"))
extern(C) void draw_image_tint(Image src, int posX, int posY, Color tint);
/// Draw an image, rotated, on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_rotated"))
extern(C) void draw_image_rotated(Image src, int posX, int posY, float degrees, float offsetX, float offsetY, ImageFilter filter);
/// Draw an image, flipped, on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_flipped"))
extern(C) void draw_image_flipped(Image src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);
/// Draw an image, scaled, on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_scaled"))
extern(C) void draw_image_scaled(Image src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, ImageFilter filter);
/// Draw some text on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_text"))
extern(C) void draw_text(Font font, const(char)* text, int posX, int posY, Color color);
/// Save an image to persistant storage.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "save_image"))
extern(C) void save_image(Image image, const(char)* filename);
/// Load an image from a file in cart.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "load_image"))
extern(C) Image load_image(const(char)* filename);
/// Resize an image, return copy.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_resize"))
extern(C) Image image_resize(Image image, int newWidth, int newHeight, ImageFilter filter);
/// Scale an image, return copy.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_scale"))
extern(C) Image image_scale(Image image, float scaleX, float scaleY, ImageFilter filter);
/// Replace a color in an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_color_replace"))
extern(C) void image_color_replace(Image image, Color color, Color replace);
/// Tint a color in an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_color_tint"))
extern(C) void image_color_tint(Image image, Color color);
/// Fade a color in an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_color_fade"))
extern(C) void image_color_fade(Image image, float alpha);
/// Copy a font to a new font.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "font_copy"))
extern(C) Font font_copy(Font font);
/// Scale a font, return a new font.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "font_scale"))
extern(C) Font font_scale(Font font, float scaleX, float scaleY, ImageFilter filter);
/// Load a BMF font from a file in cart.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "load_font_bmf"))
extern(C) Font load_font_bmf(const(char)* filename, const(char)* characters);
/// Load a BMF font from an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "load_font_bmf_from_image"))
extern(C) Font load_font_bmf_from_image(Image image, const(char)* characters);
/// Measure the size of some text.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "measure_text"))
extern(C) Dimensions* measure_text(Font font, const(char)* text, int textLength);
/// Meaure an image (use 0 for screen).
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "measure_image"))
extern(C) Dimensions* measure_image(Image image);
/// Load a TTY font from a file in cart.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "load_font_tty"))
extern(C) Font load_font_tty(const(char)* filename, int glyphWidth, int glyphHeight, const(char)* characters);
/// Load a TTY font from an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "load_font_tty_from_image"))
extern(C) Font load_font_tty_from_image(Image image, int glyphWidth, int glyphHeight, const(char)* characters);
/// Load a TTF font from a file in cart.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "load_font_ttf"))
extern(C) Font load_font_ttf(const(char)* filename, int fontSize);
/// Invert the colors in an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_color_invert"))
extern(C) void image_color_invert(Image image);
/// Calculate a rectangle representing the available alpha border in an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_alpha_border"))
extern(C) Rectangle* image_alpha_border(Image image, float threshold);
/// Crop an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_crop"))
extern(C) void image_crop(Image image, int x, int y, int width, int height);
/// Crop an image based on the alpha border, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_alpha_crop"))
extern(C) void image_alpha_crop(Image image, float threshold);
/// Adjust the brightness of an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_color_brightness"))
extern(C) void image_color_brightness(Image image, float factor);
/// Flip an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_flip"))
extern(C) void image_flip(Image image, bool horizontal, bool vertical);
/// Change the contrast of an image, in-place.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_color_contrast"))
extern(C) void image_color_contrast(Image image, float contrast);
/// Use an image as an alpha-mask on another image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_alpha_mask"))
extern(C) void image_alpha_mask(Image image, Image alphaMask, int posX, int posY);
/// Create a new image, rotating another image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_rotate"))
extern(C) Image image_rotate(Image image, float degrees, ImageFilter filter);
/// Create a new image of a gradient.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "image_gradient"))
extern(C) Image image_gradient(int width, int height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight);
/// Unload an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "unload_image"))
extern(C) void unload_image(Image image);
/// Unload a font.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "unload_font"))
extern(C) void unload_font(Font font);
/// Clear an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "clear_image"))
extern(C) void clear_image(Image destination, Color color);
/// Draw a single pixel on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_point_on_image"))
extern(C) void draw_point_on_image(Image destination, int x, int y, Color color);
/// Draw a line on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_line_on_image"))
extern(C) void draw_line_on_image(Image destination, int startPosX, int startPosY, int endPosX, int endPosY, Color color);
/// Draw a filled rectangle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle_on_image"))
extern(C) void draw_rectangle_on_image(Image destination, int posX, int posY, int width, int height, Color color);
/// Draw a filled triangle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_triangle_on_image"))
extern(C) void draw_triangle_on_image(Image destination, int x1, int y1, int x2, int y2, int x3, int y3, Color color);
/// Draw a filled ellipse on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_ellipse_on_image"))
extern(C) void draw_ellipse_on_image(Image destination, int centerX, int centerY, int radiusX, int radiusY, Color color);
/// Draw a circle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_circle_on_image"))
extern(C) void draw_circle_on_image(Image destination, int centerX, int centerY, int radius, Color color);
/// Draw a filled polygon on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_polygon_on_image"))
extern(C) void draw_polygon_on_image(Image destination, const(Vector)* points, int numPoints, Color color);
/// Draw a filled round-rectangle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle_rounded_on_image"))
extern(C) void draw_rectangle_rounded_on_image(Image destination, int x, int y, int width, int height, int cornerRadius, Color color);
/// Draw an image on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_on_image"))
extern(C) void draw_image_on_image(Image destination, Image src, int posX, int posY);
/// Draw a tinted image on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_tint_on_image"))
extern(C) void draw_image_tint_on_image(Image destination, Image src, int posX, int posY, Color tint);
/// Draw an image, rotated, on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_rotated_on_image"))
extern(C) void draw_image_rotated_on_image(Image destination, Image src, int posX, int posY, float degrees, float offsetX, float offsetY, ImageFilter filter);
/// Draw an image, flipped, on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_flipped_on_image"))
extern(C) void draw_image_flipped_on_image(Image destination, Image src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);
/// Draw an image, scaled, on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_image_scaled_on_image"))
extern(C) void draw_image_scaled_on_image(Image destination, Image src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, ImageFilter filter);
/// Draw some text on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_text_on_image"))
extern(C) void draw_text_on_image(Image destination, Font font, const(char)* text, int posX, int posY, Color color);
/// Draw a outlined (with thickness) rectangle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle_outline"))
extern(C) void draw_rectangle_outline(int posX, int posY, int width, int height, int thickness, Color color);
/// Draw a outlined (with thickness) triangle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_triangle_outline"))
extern(C) void draw_triangle_outline(int x1, int y1, int x2, int y2, int x3, int y3, int thickness, Color color);
/// Draw a outlined (with thickness) ellipse on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_ellipse_outline"))
extern(C) void draw_ellipse_outline(int centerX, int centerY, int radiusX, int radiusY, int thickness, Color color);
/// Draw a outlined (with thickness) circle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_circle_outline"))
extern(C) void draw_circle_outline(int centerX, int centerY, int radius, int thickness, Color color);
/// Draw a outlined (with thickness) polygon on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_polygon_outline"))
extern(C) void draw_polygon_outline(const(Vector)* points, int numPoints, int thickness, Color color);
/// Draw a outlined (with thickness) arc on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_arc_outline"))
extern(C) void draw_arc_outline(int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, int thickness, Color color);
/// Draw a outlined (with thickness) round-rectangle on the screen.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle_rounded_outline"))
extern(C) void draw_rectangle_rounded_outline(int x, int y, int width, int height, int cornerRadius, int thickness, Color color);
/// Draw a outlined (with thickness) rectangle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle_outline_on_image"))
extern(C) void draw_rectangle_outline_on_image(Image destination, int posX, int posY, int width, int height, int thickness, Color color);
/// Draw a outlined (with thickness) triangle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_triangle_outline_on_image"))
extern(C) void draw_triangle_outline_on_image(Image destination, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, Color color);
/// Draw a outlined (with thickness) ellipse on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_ellipse_outline_on_image"))
extern(C) void draw_ellipse_outline_on_image(Image destination, int centerX, int centerY, int radiusX, int radiusY, int thickness, Color color);
/// Draw a outlined (with thickness) circle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_circle_outline_on_image"))
extern(C) void draw_circle_outline_on_image(Image destination, int centerX, int centerY, int radius, int thickness, Color color);
/// Draw a outlined (with thickness) polygon on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_polygon_outline_on_image"))
extern(C) void draw_polygon_outline_on_image(Image destination, const(Vector)* points, int numPoints, int thickness, Color color);
/// Draw a outlined (with thickness) round-rectangle on an image.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "draw_rectangle_rounded_outline_on_image"))
extern(C) void draw_rectangle_rounded_outline_on_image(Image destination, int x, int y, int width, int height, int cornerRadius, int thickness, Color color);

// INPUT
/// Has the key been pressed? (tracks unpress/read correctly.)
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "key_pressed"))
extern(C) bool key_pressed(Key key);
/// Is the key currently down?
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "key_down"))
extern(C) bool key_down(Key key);
/// Has the key been released? (tracks press/read correctly.)
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "key_released"))
extern(C) bool key_released(Key key);
/// Is the key currently up?
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "key_up"))
extern(C) bool key_up(Key key);
/// Has the button been pressed? (tracks unpress/read correctly.)
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "gamepad_button_pressed"))
extern(C) bool gamepad_button_pressed(int gamepad, GamepadButton button);
/// Is the button currently down?
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "gamepad_button_down"))
extern(C) bool gamepad_button_down(int gamepad, GamepadButton button);
/// Has the button been released? (tracks press/read correctly.)
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "gamepad_button_released"))
extern(C) bool gamepad_button_released(int gamepad, GamepadButton button);
/// Get current position of mouse.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "mouse_position"))
extern(C) Vector* mouse_position();
/// Has the button been pressed? (tracks unpress/read correctly.)
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "mouse_button_pressed"))
extern(C) bool mouse_button_pressed(MouseButton button);
/// Is the button currently down?
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "mouse_button_down"))
extern(C) bool mouse_button_down(MouseButton button);
/// Has the button been released? (tracks press/read correctly.)
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "mouse_button_released"))
extern(C) bool mouse_button_released(MouseButton button);
/// Is the button currently up?
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "mouse_button_up"))
extern(C) bool mouse_button_up(MouseButton button);

// SOUND
/// Load a sound from a file in cart.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "load_sound"))
extern(C) Sound load_sound(const(char)* filename);
/// Play a sound.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "play_sound"))
extern(C) void play_sound(Sound sound, bool loop);
/// Stop a sound.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "stop_sound"))
extern(C) void stop_sound(Sound sound);
/// Unload a sound.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "unload_sound"))
extern(C) void unload_sound(Sound sound);
/// Speak some text and return a sound. Set things to 0 for defaults.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "tts_sound"))
extern(C) Sound tts_sound(const(char)* text, bool phonetic, int pitch, int speed, int throat, int mouth, bool sing);
/// Create Sfx sound.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "sfx_sound"))
extern(C) Sound sfx_sound(const(SfxParams)* params);
/// Create Sfx parameters.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "sfx_generate"))
extern(C) SfxParams* sfx_generate(SfxPresetType type);

// TYPES

// UTILITIES
/// Get system-time (ms) since unix epoch.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "current_time"))
extern(C) ulong current_time();
/// Get the change in time (seconds) since the last update run.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "delta_time"))
extern(C) float delta_time();
/// Get a random integer between 2 numbers.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "random_int"))
extern(C) int random_int(int min, int max);
/// Get the random-seed.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "random_seed_get"))
extern(C) ulong random_seed_get();
/// Set the random-seed.
@(llvmAttr("wasm-import-module", "null0"), llvmAttr("wasm-import-name", "random_seed_set"))
extern(C) void random_seed_set(ulong seed);
