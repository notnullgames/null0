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
alias Tilemap = uint;

// Create a Color from r, g, b, a components
fn Color rgba(char r, char g, char b, char a) {
    return { r, g, b, a };
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

// An RGBA color.
struct Color {
    char r;
    char g;
    char b;
    char a;
}

// A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`.
struct TilemapProp {
    char* name;
    TilePropType type;
    int integer;
    float number;
    char* text;
}

// An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it.
struct TilemapObject {
    int id;
    char* name;
    char* type;
    int gid;
    float x;
    float y;
    float width;
    float height;
    float rotation;
    int visible;
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

// The kind of a layer in a tilemap.
constdef TileLayerKind : int {
    LAYER_NONE = 0,
    LAYER_TILE = 1,
    LAYER_OBJECT = 2,
    LAYER_IMAGE = 3,
    LAYER_GROUP = 4,
}

// The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING.
constdef TilePropType : int {
    PROP_NONE = 0,
    PROP_INT = 1,
    PROP_BOOL = 2,
    PROP_FLOAT = 3,
    PROP_STRING = 4,
    PROP_COLOR = 5,
}

// Constants
const Image SCREEN = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const Font FONT_DEFAULT = 0;

// Colors
const Color LIGHTGRAY = { 200, 200, 200, 255 };
const Color GRAY = { 130, 130, 130, 255 };
const Color DARKGRAY = { 80, 80, 80, 255 };
const Color YELLOW = { 253, 249, 0, 255 };
const Color GOLD = { 255, 203, 0, 255 };
const Color ORANGE = { 255, 161, 0, 255 };
const Color PINK = { 255, 109, 194, 255 };
const Color RED = { 230, 41, 55, 255 };
const Color MAROON = { 190, 33, 55, 255 };
const Color GREEN = { 0, 228, 48, 255 };
const Color LIME = { 0, 158, 47, 255 };
const Color DARKGREEN = { 0, 117, 44, 255 };
const Color SKYBLUE = { 102, 191, 255, 255 };
const Color BLUE = { 0, 121, 241, 255 };
const Color DARKBLUE = { 0, 82, 172, 255 };
const Color PURPLE = { 200, 122, 255, 255 };
const Color VIOLET = { 135, 60, 190, 255 };
const Color DARKPURPLE = { 112, 31, 126, 255 };
const Color BEIGE = { 211, 176, 131, 255 };
const Color BROWN = { 127, 106, 79, 255 };
const Color DARKBROWN = { 76, 63, 47, 255 };
const Color WHITE = { 255, 255, 255, 255 };
const Color BLACK = { 0, 0, 0, 255 };
const Color BLANK = { 0, 0, 0, 0 };
const Color MAGENTA = { 255, 0, 255, 255 };
const Color RAYWHITE = { 245, 245, 245, 255 };

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

// GUI
// Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.
extern fn bool gui_begin_window(char* title, Rectangle rect) @wasm("null0", "gui_begin_window");
// End the current GUI window.
extern fn void gui_end_window() @wasm("null0", "gui_end_window");
// A button. Returns true when it is clicked.
extern fn bool gui_button(char* label) @wasm("null0", "gui_button");
// A static text label.
extern fn void gui_label(char* text) @wasm("null0", "gui_label");
// A block of wrapping text.
extern fn void gui_text(char* text) @wasm("null0", "gui_text");
// A checkbox. Returns the (possibly changed) state.
extern fn bool gui_checkbox(char* label, bool state) @wasm("null0", "gui_checkbox");
// A slider. Returns the (possibly changed) value.
extern fn float gui_slider(float value, float low, float high) @wasm("null0", "gui_slider");
// Set the current layout row - the column widths (negative for flexible), and the row height.
extern fn void gui_layout_row(int* widths, int numWidths, int height) @wasm("null0", "gui_layout_row");
// Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.
extern fn void gui_end() @wasm("null0", "gui_end");
// Draw the GUI to an image (0 is the screen).
extern fn void gui_draw(Image dst) @wasm("null0", "gui_draw");

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

// TILE
// Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
extern fn Tilemap load_tilemap(char* filename) @wasm("null0", "load_tilemap");
// Unload a tilemap.
extern fn void unload_tilemap(Tilemap tilemap) @wasm("null0", "unload_tilemap");
// Update a tilemap's animation timers (deltaTime is in seconds).
extern fn void tile_update(Tilemap tilemap, float deltaTime) @wasm("null0", "tile_update");
// Get the size of a tilemap, in tiles.
extern fn Dimensions* tile_map_size(Tilemap tilemap) @wasm("null0", "tile_map_size");
// Get the size of a single tile of a tilemap, in pixels.
extern fn Dimensions* tile_tile_size(Tilemap tilemap) @wasm("null0", "tile_tile_size");
// Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)
extern fn TilemapProp* tile_map_prop(Tilemap tilemap, char* name) @wasm("null0", "tile_map_prop");
// Get the number of custom properties on a tilemap.
extern fn int tile_map_prop_count(Tilemap tilemap) @wasm("null0", "tile_map_prop_count");
// Get a custom property of a tilemap, by index (PROP_NONE when out of range.)
extern fn TilemapProp* tile_map_prop_at(Tilemap tilemap, int index) @wasm("null0", "tile_map_prop_at");
// Draw a tilemap on the screen.
extern fn void tile_draw(Tilemap tilemap, int posX, int posY) @wasm("null0", "tile_draw");
// Draw a tilemap on the screen, tinted by a color.
extern fn void tile_draw_tint(Tilemap tilemap, int posX, int posY, Color tint) @wasm("null0", "tile_draw_tint");
// Draw a tilemap on an image.
extern fn void tile_draw_on_image(Image dst, Tilemap tilemap, int posX, int posY) @wasm("null0", "tile_draw_on_image");
// Render a whole tilemap to a new image.
extern fn Image tilemap_image(Tilemap tilemap) @wasm("null0", "tilemap_image");
// Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.
extern fn int tile_layer_count(Tilemap tilemap) @wasm("null0", "tile_layer_count");
// Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)
extern fn int tile_layer_index(Tilemap tilemap, char* name) @wasm("null0", "tile_layer_index");
// Get the name of a layer of a tilemap.
extern fn char* tile_layer_name(Tilemap tilemap, int layer) @wasm("null0", "tile_layer_name");
// Get the kind of a layer of a tilemap.
extern fn TileLayerKind tile_layer_type(Tilemap tilemap, int layer) @wasm("null0", "tile_layer_type");
// Get the size of a layer of a tilemap, in tiles.
extern fn Dimensions* tile_layer_size(Tilemap tilemap, int layer) @wasm("null0", "tile_layer_size");
// Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.
extern fn bool tile_layer_visible(Tilemap tilemap, int layer) @wasm("null0", "tile_layer_visible");
// Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)
extern fn TilemapProp* tile_layer_prop(Tilemap tilemap, int layer, char* name) @wasm("null0", "tile_layer_prop");
// Get the number of custom properties on a layer of a tilemap.
extern fn int tile_layer_prop_count(Tilemap tilemap, int layer) @wasm("null0", "tile_layer_prop_count");
// Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)
extern fn TilemapProp* tile_layer_prop_at(Tilemap tilemap, int layer, int index) @wasm("null0", "tile_layer_prop_at");
// Draw a single layer of a tilemap on the screen.
extern fn void tile_draw_layer(Tilemap tilemap, int layer, int posX, int posY) @wasm("null0", "tile_draw_layer");
// Draw a single layer of a tilemap on the screen, tinted by a color.
extern fn void tile_draw_layer_tint(Tilemap tilemap, int layer, int posX, int posY, Color tint) @wasm("null0", "tile_draw_layer_tint");
// Draw a single layer of a tilemap on an image.
extern fn void tile_draw_layer_on_image(Image dst, Tilemap tilemap, int layer, int posX, int posY) @wasm("null0", "tile_draw_layer_on_image");
// Render a single layer of a tilemap to a new image.
extern fn Image tile_layer_image(Tilemap tilemap, int layer) @wasm("null0", "tile_layer_image");
// Get the gid of the tile at a column/row in a tilemap layer.
extern fn int tile_get_tile(Tilemap tilemap, int layer, int column, int row) @wasm("null0", "tile_get_tile");
// Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.
extern fn void tile_set_tile(Tilemap tilemap, int layer, int column, int row, int gid) @wasm("null0", "tile_set_tile");
// Draw a single tile from a tilemap on the screen.
extern fn void tile_draw_tile(Tilemap tilemap, int gid, int posX, int posY) @wasm("null0", "tile_draw_tile");
// Get a copy of the image of a single tile in a tilemap.
extern fn Image tile_image(Tilemap tilemap, int gid) @wasm("null0", "tile_image");
// Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.
extern fn TilemapProp* tile_gid_prop(Tilemap tilemap, int gid, char* name) @wasm("null0", "tile_gid_prop");
// Get the number of custom properties on a tile of a tilemap.
extern fn int tile_gid_prop_count(Tilemap tilemap, int gid) @wasm("null0", "tile_gid_prop_count");
// Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)
extern fn TilemapProp* tile_gid_prop_at(Tilemap tilemap, int gid, int index) @wasm("null0", "tile_gid_prop_at");
// Get the number of objects on an object-layer of a tilemap.
extern fn int tile_object_count(Tilemap tilemap, int layer) @wasm("null0", "tile_object_count");
// Get an object from an object-layer of a tilemap.
extern fn TilemapObject* tile_object(Tilemap tilemap, int layer, int index) @wasm("null0", "tile_object");
// Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)
extern fn int tile_object_index(Tilemap tilemap, int layer, char* name) @wasm("null0", "tile_object_index");
// Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)
extern fn TilemapProp* tile_object_prop(Tilemap tilemap, int layer, int index, char* name) @wasm("null0", "tile_object_prop");
// Get the number of custom properties on an object of a tilemap.
extern fn int tile_object_prop_count(Tilemap tilemap, int layer, int index) @wasm("null0", "tile_object_prop_count");
// Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)
extern fn TilemapProp* tile_object_prop_at(Tilemap tilemap, int layer, int index, int propIndex) @wasm("null0", "tile_object_prop_at");

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
