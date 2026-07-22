// null0 - C3 bindings for the null0 fantasy console
//
// Usage:
//
// ```c3
// import null0;
//
// fn void load() @export("load") {
//     null0::clear(null0::BLUE);
//     null0::draw_circle(100, 100, 50, null0::RED);
// }
// ```
module null0;

// handle types
alias Image = uint;
alias Font = uint;
alias Sound = uint;

// An RGBA color, packed into a single uint (ABI-compatible with host)
alias Color = uint;

// Create a Color from r, g, b, a components
fn Color rgba(char r, char g, char b, char a) {
    return (Color)r | ((Color)g << 8) | ((Color)b << 16) | ((Color)a << 24);
}

// Create an opaque Color from r, g, b components
fn Color rgb(char r, char g, char b) {
    return rgba(r, g, b, 255);
}


// Sfx parameters.
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

// The 2D size of something (width/height.)
struct Dimensions {
    int width;
    int height;
}

// The 2D position of something (x/y.)
struct Vector {
    int x;
    int y;
}

// The 2D position + size of something (x/y/w/h.)
struct Rectangle {
    int x;
    int y;
    int width;
    int height;
}

// Potential image-filtering techniques for scale/etc.
constdef ImageFilter : int {
    FILTER_NEARESTNEIGHBOR = 0,
    FILTER_BILINEAR = 1,
    FILTER_SMOOTH = 2,
}

// Represents a Sfx preset type.
constdef SfxPresetType : int {
    SFX_COIN = 0,
    SFX_LASER = 1,
    SFX_EXPLOSION = 2,
    SFX_POWERUP = 3,
    SFX_HURT = 4,
    SFX_JUMP = 5,
    SFX_SELECT = 6,
    SFX_SYNTH = 7,
}

// Represents a keyboard key.
constdef Key : int {
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

// Represents a gamepad button.
constdef GamepadButton : int {
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

// Represents a mouse button.
constdef MouseButton : int {
    MOUSE_BUTTON_UNKNOWN = 0,
    MOUSE_BUTTON_LEFT = 1,
    MOUSE_BUTTON_RIGHT = 2,
    MOUSE_BUTTON_MIDDLE = 3,
}

// Constants
const Image SCREEN = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const Font FONT_DEFAULT = 0;

// Colors
const Color LIGHTGRAY = 0xffc8c8c8; // rgba(200, 200, 200, 255)
const Color GRAY = 0xff828282; // rgba(130, 130, 130, 255)
const Color DARKGRAY = 0xff505050; // rgba(80, 80, 80, 255)
const Color YELLOW = 0xff00f9fd; // rgba(253, 249, 0, 255)
const Color GOLD = 0xff00cbff; // rgba(255, 203, 0, 255)
const Color ORANGE = 0xff00a1ff; // rgba(255, 161, 0, 255)
const Color PINK = 0xffc26dff; // rgba(255, 109, 194, 255)
const Color RED = 0xff3729e6; // rgba(230, 41, 55, 255)
const Color MAROON = 0xff3721be; // rgba(190, 33, 55, 255)
const Color GREEN = 0xff30e400; // rgba(0, 228, 48, 255)
const Color LIME = 0xff2f9e00; // rgba(0, 158, 47, 255)
const Color DARKGREEN = 0xff2c7500; // rgba(0, 117, 44, 255)
const Color SKYBLUE = 0xffffbf66; // rgba(102, 191, 255, 255)
const Color BLUE = 0xfff17900; // rgba(0, 121, 241, 255)
const Color DARKBLUE = 0xffac5200; // rgba(0, 82, 172, 255)
const Color PURPLE = 0xffff7ac8; // rgba(200, 122, 255, 255)
const Color VIOLET = 0xffbe3c87; // rgba(135, 60, 190, 255)
const Color DARKPURPLE = 0xff7e1f70; // rgba(112, 31, 126, 255)
const Color BEIGE = 0xff83b0d3; // rgba(211, 176, 131, 255)
const Color BROWN = 0xff4f6a7f; // rgba(127, 106, 79, 255)
const Color DARKBROWN = 0xff2f3f4c; // rgba(76, 63, 47, 255)
const Color WHITE = 0xffffffff; // rgba(255, 255, 255, 255)
const Color BLACK = 0xff000000; // rgba(0, 0, 0, 255)
const Color BLANK = 0x00000000; // rgba(0, 0, 0, 0)
const Color MAGENTA = 0xffff00ff; // rgba(255, 0, 255, 255)
const Color RAYWHITE = 0xfff5f5f5; // rgba(245, 245, 245, 255)

// COLORS
// Tint a color with another color.
extern fn Color* color_tint(Color color, Color tint) @wasm("null0", "color_tint");
// Fade a color.
extern fn Color* color_fade(Color color, float alpha) @wasm("null0", "color_fade");
// Change the brightness of a color.
extern fn Color* color_brightness(Color color, float factor) @wasm("null0", "color_brightness");
// Invert a color.
extern fn Color* color_invert(Color color) @wasm("null0", "color_invert");
// Blend 2 colors together.
extern fn Color* color_alpha_blend(Color dst, Color src) @wasm("null0", "color_alpha_blend");
// Change contrast of a color.
extern fn Color* color_contrast(Color color, float contrast) @wasm("null0", "color_contrast");
// Interpolate colors.
extern fn Color* color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, float coordinateX, float coordinateY) @wasm("null0", "color_bilinear_interpolate");

// GRAPHICS
// Create a new blank image.
extern fn Image new_image(int width, int height, Color color) @wasm("null0", "new_image");
// Copy an image to a new image.
extern fn Image image_copy(Image image) @wasm("null0", "image_copy");
// Create an image from a region of another image.
extern fn Image image_subimage(Image image, int x, int y, int width, int height) @wasm("null0", "image_subimage");
// Clear the screen.
extern fn void clear(Color color) @wasm("null0", "clear");
// Draw a single pixel on the screen.
extern fn void draw_point(int x, int y, Color color) @wasm("null0", "draw_point");
// Draw a line on the screen.
extern fn void draw_line(int startPosX, int startPosY, int endPosX, int endPosY, Color color) @wasm("null0", "draw_line");
// Draw a filled rectangle on the screen.
extern fn void draw_rectangle(int posX, int posY, int width, int height, Color color) @wasm("null0", "draw_rectangle");
// Draw a filled triangle on the screen.
extern fn void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color) @wasm("null0", "draw_triangle");
// Draw a filled ellipse on the screen.
extern fn void draw_ellipse(int centerX, int centerY, int radiusX, int radiusY, Color color) @wasm("null0", "draw_ellipse");
// Draw a filled circle on the screen.
extern fn void draw_circle(int centerX, int centerY, int radius, Color color) @wasm("null0", "draw_circle");
// Draw a filled polygon on the screen.
extern fn void draw_polygon(Vector* points, int numPoints, Color color) @wasm("null0", "draw_polygon");
// Draw a filled arc on the screen.
extern fn void draw_arc(int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, Color color) @wasm("null0", "draw_arc");
// Draw a filled round-rectangle on the screen.
extern fn void draw_rectangle_rounded(int x, int y, int width, int height, int cornerRadius, Color color) @wasm("null0", "draw_rectangle_rounded");
// Draw an image on the screen.
extern fn void draw_image(Image src, int posX, int posY) @wasm("null0", "draw_image");
// Draw a tinted image on the screen.
extern fn void draw_image_tint(Image src, int posX, int posY, Color tint) @wasm("null0", "draw_image_tint");
// Draw an image, rotated, on the screen.
extern fn void draw_image_rotated(Image src, int posX, int posY, float degrees, float offsetX, float offsetY, int filter) @wasm("null0", "draw_image_rotated");
// Draw an image, flipped, on the screen.
extern fn void draw_image_flipped(Image src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) @wasm("null0", "draw_image_flipped");
// Draw an image, scaled, on the screen.
extern fn void draw_image_scaled(Image src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, int filter) @wasm("null0", "draw_image_scaled");
// Draw some text on the screen.
extern fn void draw_text(Font font, char* text, int posX, int posY, Color color) @wasm("null0", "draw_text");
// Save an image to persistant storage.
extern fn void save_image(Image image, char* filename) @wasm("null0", "save_image");
// Load an image from a file in cart.
extern fn Image load_image(char* filename) @wasm("null0", "load_image");
// Resize an image, return copy.
extern fn Image image_resize(Image image, int newWidth, int newHeight, int filter) @wasm("null0", "image_resize");
// Scale an image, return copy.
extern fn Image image_scale(Image image, float scaleX, float scaleY, int filter) @wasm("null0", "image_scale");
// Replace a color in an image, in-place.
extern fn void image_color_replace(Image image, Color color, Color replace) @wasm("null0", "image_color_replace");
// Tint a color in an image, in-place.
extern fn void image_color_tint(Image image, Color color) @wasm("null0", "image_color_tint");
// Fade a color in an image, in-place.
extern fn void image_color_fade(Image image, float alpha) @wasm("null0", "image_color_fade");
// Copy a font to a new font.
extern fn Font font_copy(Font font) @wasm("null0", "font_copy");
// Scale a font, return a new font.
extern fn Font font_scale(Font font, float scaleX, float scaleY, int filter) @wasm("null0", "font_scale");
// Load a BMF font from a file in cart.
extern fn Font load_font_bmf(char* filename, char* characters) @wasm("null0", "load_font_bmf");
// Load a BMF font from an image.
extern fn Font load_font_bmf_from_image(Image image, char* characters) @wasm("null0", "load_font_bmf_from_image");
// Measure the size of some text.
extern fn Dimensions* measure_text(Font font, char* text, int textLength) @wasm("null0", "measure_text");
// Meaure an image (use 0 for screen).
extern fn Dimensions* measure_image(Image image) @wasm("null0", "measure_image");
// Load a TTY font from a file in cart.
extern fn Font load_font_tty(char* filename, int glyphWidth, int glyphHeight, char* characters) @wasm("null0", "load_font_tty");
// Load a TTY font from an image.
extern fn Font load_font_tty_from_image(Image image, int glyphWidth, int glyphHeight, char* characters) @wasm("null0", "load_font_tty_from_image");
// Load a TTF font from a file in cart.
extern fn Font load_font_ttf(char* filename, int fontSize) @wasm("null0", "load_font_ttf");
// Invert the colors in an image, in-place.
extern fn void image_color_invert(Image image) @wasm("null0", "image_color_invert");
// Calculate a rectangle representing the available alpha border in an image.
extern fn Rectangle* image_alpha_border(Image image, float threshold) @wasm("null0", "image_alpha_border");
// Crop an image, in-place.
extern fn void image_crop(Image image, int x, int y, int width, int height) @wasm("null0", "image_crop");
// Crop an image based on the alpha border, in-place.
extern fn void image_alpha_crop(Image image, float threshold) @wasm("null0", "image_alpha_crop");
// Adjust the brightness of an image, in-place.
extern fn void image_color_brightness(Image image, float factor) @wasm("null0", "image_color_brightness");
// Flip an image, in-place.
extern fn void image_flip(Image image, bool horizontal, bool vertical) @wasm("null0", "image_flip");
// Change the contrast of an image, in-place.
extern fn void image_color_contrast(Image image, float contrast) @wasm("null0", "image_color_contrast");
// Use an image as an alpha-mask on another image.
extern fn void image_alpha_mask(Image image, Image alphaMask, int posX, int posY) @wasm("null0", "image_alpha_mask");
// Create a new image, rotating another image.
extern fn Image image_rotate(Image image, float degrees, int filter) @wasm("null0", "image_rotate");
// Create a new image of a gradient.
extern fn Image image_gradient(int width, int height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight) @wasm("null0", "image_gradient");
// Unload an image.
extern fn void unload_image(Image image) @wasm("null0", "unload_image");
// Unload a font.
extern fn void unload_font(Font font) @wasm("null0", "unload_font");
// Clear an image.
extern fn void clear_image(Image destination, Color color) @wasm("null0", "clear_image");
// Draw a single pixel on an image.
extern fn void draw_point_on_image(Image destination, int x, int y, Color color) @wasm("null0", "draw_point_on_image");
// Draw a line on an image.
extern fn void draw_line_on_image(Image destination, int startPosX, int startPosY, int endPosX, int endPosY, Color color) @wasm("null0", "draw_line_on_image");
// Draw a filled rectangle on an image.
extern fn void draw_rectangle_on_image(Image destination, int posX, int posY, int width, int height, Color color) @wasm("null0", "draw_rectangle_on_image");
// Draw a filled triangle on an image.
extern fn void draw_triangle_on_image(Image destination, int x1, int y1, int x2, int y2, int x3, int y3, Color color) @wasm("null0", "draw_triangle_on_image");
// Draw a filled ellipse on an image.
extern fn void draw_ellipse_on_image(Image destination, int centerX, int centerY, int radiusX, int radiusY, Color color) @wasm("null0", "draw_ellipse_on_image");
// Draw a circle on an image.
extern fn void draw_circle_on_image(Image destination, int centerX, int centerY, int radius, Color color) @wasm("null0", "draw_circle_on_image");
// Draw a filled polygon on an image.
extern fn void draw_polygon_on_image(Image destination, Vector* points, int numPoints, Color color) @wasm("null0", "draw_polygon_on_image");
// Draw a filled round-rectangle on an image.
extern fn void draw_rectangle_rounded_on_image(Image destination, int x, int y, int width, int height, int cornerRadius, Color color) @wasm("null0", "draw_rectangle_rounded_on_image");
// Draw an image on an image.
extern fn void draw_image_on_image(Image destination, Image src, int posX, int posY) @wasm("null0", "draw_image_on_image");
// Draw a tinted image on an image.
extern fn void draw_image_tint_on_image(Image destination, Image src, int posX, int posY, Color tint) @wasm("null0", "draw_image_tint_on_image");
// Draw an image, rotated, on an image.
extern fn void draw_image_rotated_on_image(Image destination, Image src, int posX, int posY, float degrees, float offsetX, float offsetY, int filter) @wasm("null0", "draw_image_rotated_on_image");
// Draw an image, flipped, on an image.
extern fn void draw_image_flipped_on_image(Image destination, Image src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) @wasm("null0", "draw_image_flipped_on_image");
// Draw an image, scaled, on an image.
extern fn void draw_image_scaled_on_image(Image destination, Image src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, int filter) @wasm("null0", "draw_image_scaled_on_image");
// Draw some text on an image.
extern fn void draw_text_on_image(Image destination, Font font, char* text, int posX, int posY, Color color) @wasm("null0", "draw_text_on_image");
// Draw a outlined (with thickness) rectangle on the screen.
extern fn void draw_rectangle_outline(int posX, int posY, int width, int height, int thickness, Color color) @wasm("null0", "draw_rectangle_outline");
// Draw a outlined (with thickness) triangle on the screen.
extern fn void draw_triangle_outline(int x1, int y1, int x2, int y2, int x3, int y3, int thickness, Color color) @wasm("null0", "draw_triangle_outline");
// Draw a outlined (with thickness) ellipse on the screen.
extern fn void draw_ellipse_outline(int centerX, int centerY, int radiusX, int radiusY, int thickness, Color color) @wasm("null0", "draw_ellipse_outline");
// Draw a outlined (with thickness) circle on the screen.
extern fn void draw_circle_outline(int centerX, int centerY, int radius, int thickness, Color color) @wasm("null0", "draw_circle_outline");
// Draw a outlined (with thickness) polygon on the screen.
extern fn void draw_polygon_outline(Vector* points, int numPoints, int thickness, Color color) @wasm("null0", "draw_polygon_outline");
// Draw a outlined (with thickness) arc on the screen.
extern fn void draw_arc_outline(int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, int thickness, Color color) @wasm("null0", "draw_arc_outline");
// Draw a outlined (with thickness) round-rectangle on the screen.
extern fn void draw_rectangle_rounded_outline(int x, int y, int width, int height, int cornerRadius, int thickness, Color color) @wasm("null0", "draw_rectangle_rounded_outline");
// Draw a outlined (with thickness) rectangle on an image.
extern fn void draw_rectangle_outline_on_image(Image destination, int posX, int posY, int width, int height, int thickness, Color color) @wasm("null0", "draw_rectangle_outline_on_image");
// Draw a outlined (with thickness) triangle on an image.
extern fn void draw_triangle_outline_on_image(Image destination, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, Color color) @wasm("null0", "draw_triangle_outline_on_image");
// Draw a outlined (with thickness) ellipse on an image.
extern fn void draw_ellipse_outline_on_image(Image destination, int centerX, int centerY, int radiusX, int radiusY, int thickness, Color color) @wasm("null0", "draw_ellipse_outline_on_image");
// Draw a outlined (with thickness) circle on an image.
extern fn void draw_circle_outline_on_image(Image destination, int centerX, int centerY, int radius, int thickness, Color color) @wasm("null0", "draw_circle_outline_on_image");
// Draw a outlined (with thickness) polygon on an image.
extern fn void draw_polygon_outline_on_image(Image destination, Vector* points, int numPoints, int thickness, Color color) @wasm("null0", "draw_polygon_outline_on_image");
// Draw a outlined (with thickness) round-rectangle on an image.
extern fn void draw_rectangle_rounded_outline_on_image(Image destination, int x, int y, int width, int height, int cornerRadius, int thickness, Color color) @wasm("null0", "draw_rectangle_rounded_outline_on_image");

// INPUT
// Has the key been pressed? (tracks unpress/read correctly.)
extern fn bool key_pressed(int key) @wasm("null0", "key_pressed");
// Is the key currently down?
extern fn bool key_down(int key) @wasm("null0", "key_down");
// Has the key been released? (tracks press/read correctly.)
extern fn bool key_released(int key) @wasm("null0", "key_released");
// Is the key currently up?
extern fn bool key_up(int key) @wasm("null0", "key_up");
// Has the button been pressed? (tracks unpress/read correctly.)
extern fn bool gamepad_button_pressed(int gamepad, int button) @wasm("null0", "gamepad_button_pressed");
// Is the button currently down?
extern fn bool gamepad_button_down(int gamepad, int button) @wasm("null0", "gamepad_button_down");
// Has the button been released? (tracks press/read correctly.)
extern fn bool gamepad_button_released(int gamepad, int button) @wasm("null0", "gamepad_button_released");
// Get current position of mouse.
extern fn Vector* mouse_position() @wasm("null0", "mouse_position");
// Has the button been pressed? (tracks unpress/read correctly.)
extern fn bool mouse_button_pressed(int button) @wasm("null0", "mouse_button_pressed");
// Is the button currently down?
extern fn bool mouse_button_down(int button) @wasm("null0", "mouse_button_down");
// Has the button been released? (tracks press/read correctly.)
extern fn bool mouse_button_released(int button) @wasm("null0", "mouse_button_released");
// Is the button currently up?
extern fn bool mouse_button_up(int button) @wasm("null0", "mouse_button_up");

// SOUND
// Load a sound from a file in cart.
extern fn Sound load_sound(char* filename) @wasm("null0", "load_sound");
// Play a sound.
extern fn void play_sound(Sound sound, bool loop) @wasm("null0", "play_sound");
// Stop a sound.
extern fn void stop_sound(Sound sound) @wasm("null0", "stop_sound");
// Unload a sound.
extern fn void unload_sound(Sound sound) @wasm("null0", "unload_sound");
// Speak some text and return a sound. Set things to 0 for defaults.
extern fn Sound tts_sound(char* text, bool phonetic, int pitch, int speed, int throat, int mouth, bool sing) @wasm("null0", "tts_sound");
// Create Sfx sound.
extern fn Sound sfx_sound(SfxParams* params) @wasm("null0", "sfx_sound");
// Create Sfx parameters.
extern fn SfxParams* sfx_generate(int type) @wasm("null0", "sfx_generate");

// TYPES

// UTILITIES
// Get system-time (ms) since unix epoch.
extern fn ulong current_time() @wasm("null0", "current_time");
// Get the change in time (seconds) since the last update run.
extern fn float delta_time() @wasm("null0", "delta_time");
// Get a random integer between 2 numbers.
extern fn int random_int(int min, int max) @wasm("null0", "random_int");
// Get the random-seed.
extern fn ulong random_seed_get() @wasm("null0", "random_seed_get");
// Set the random-seed.
extern fn void random_seed_set(ulong seed) @wasm("null0", "random_seed_set");
