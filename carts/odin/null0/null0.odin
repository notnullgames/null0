// null0 - Odin bindings for the null0 fantasy console
//
// Usage:
//
// ```odin
// package main
//
// import null0 "null0"
//
// @(export)
// load :: proc "c" () {
//     null0.clear(null0.BLUE)
//     null0.draw_circle(100, 100, 50, null0.RED)
// }
// ```
package null0

// handle types
Image :: distinct u32
Font :: distinct u32
Sound :: distinct u32
Tilemap :: distinct u32

// Create a Color from r, g, b, a components
rgba :: proc(r, g, b, a: u8) -> Color {
    return Color{r, g, b, a}
}

// Create an opaque Color from r, g, b components
rgb :: proc(r, g, b: u8) -> Color {
    return rgba(r, g, b, 255)
}


// Sfx parameters.
SfxParams :: struct {
    randSeed: u32,
    waveType: i32,
    attackTime: f32,
    sustainTime: f32,
    sustainPunch: f32,
    decayTime: f32,
    startFrequency: f32,
    minFrequency: f32,
    slide: f32,
    deltaSlide: f32,
    vibratoDepth: f32,
    vibratoSpeed: f32,
    changeAmount: f32,
    changeSpeed: f32,
    squareDuty: f32,
    dutySweep: f32,
    repeatSpeed: f32,
    phaserOffset: f32,
    phaserSweep: f32,
    lpfCutoff: f32,
    lpfCutoffSweep: f32,
    lpfResonance: f32,
    hpfCutoff: f32,
    hpfCutoffSweep: f32,
}

// The 2D size of something (width/height.)
Dimensions :: struct {
    width: i32,
    height: i32,
}

// The 2D position of something (x/y.)
Vector :: struct {
    x: i32,
    y: i32,
}

// The 2D position + size of something (x/y/w/h.)
Rectangle :: struct {
    x: i32,
    y: i32,
    width: i32,
    height: i32,
}

// An RGBA color.
Color :: struct {
    r: u8,
    g: u8,
    b: u8,
    a: u8,
}

// A custom property on a tilemap, layer, object, or tile. Only the member named by `type` is meaningful - a PROP_BOOL is 0/1 in `integer`, and a PROP_COLOR is RGBA bytes in `integer`.
TilemapProp :: struct {
    name: cstring,
    type: TilePropType,
    integer: i32,
    number: f32,
    text: cstring,
}

// An object from an object-layer of a tilemap. This is the map's initial state - carts own whatever they spawn from it.
TilemapObject :: struct {
    id: i32,
    name: cstring,
    type: cstring,
    gid: i32,
    x: f32,
    y: f32,
    width: f32,
    height: f32,
    rotation: f32,
    visible: i32,
}

// Potential image-filtering techniques for scale/etc.
ImageFilter :: enum i32 {
    FILTER_NEARESTNEIGHBOR = 0,
    FILTER_BILINEAR = 1,
    FILTER_SMOOTH = 2,
}

// Represents a Sfx preset type.
SfxPresetType :: enum i32 {
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
Key :: enum i32 {
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
GamepadButton :: enum i32 {
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
MouseButton :: enum i32 {
    MOUSE_BUTTON_UNKNOWN = 0,
    MOUSE_BUTTON_LEFT = 1,
    MOUSE_BUTTON_RIGHT = 2,
    MOUSE_BUTTON_MIDDLE = 3,
}

// The kind of a layer in a tilemap.
TileLayerKind :: enum i32 {
    LAYER_NONE = 0,
    LAYER_TILE = 1,
    LAYER_OBJECT = 2,
    LAYER_IMAGE = 3,
    LAYER_GROUP = 4,
}

// The type of a tilemap property's value. Tiled's "file" properties arrive as PROP_STRING.
TilePropType :: enum i32 {
    PROP_NONE = 0,
    PROP_INT = 1,
    PROP_BOOL = 2,
    PROP_FLOAT = 3,
    PROP_STRING = 4,
    PROP_COLOR = 5,
}

// Constants
SCREEN :: Image(0)
SCREEN_WIDTH :: 640
SCREEN_HEIGHT :: 480
FONT_DEFAULT :: Font(0)

// Colors
LIGHTGRAY :: Color{200, 200, 200, 255}
GRAY :: Color{130, 130, 130, 255}
DARKGRAY :: Color{80, 80, 80, 255}
YELLOW :: Color{253, 249, 0, 255}
GOLD :: Color{255, 203, 0, 255}
ORANGE :: Color{255, 161, 0, 255}
PINK :: Color{255, 109, 194, 255}
RED :: Color{230, 41, 55, 255}
MAROON :: Color{190, 33, 55, 255}
GREEN :: Color{0, 228, 48, 255}
LIME :: Color{0, 158, 47, 255}
DARKGREEN :: Color{0, 117, 44, 255}
SKYBLUE :: Color{102, 191, 255, 255}
BLUE :: Color{0, 121, 241, 255}
DARKBLUE :: Color{0, 82, 172, 255}
PURPLE :: Color{200, 122, 255, 255}
VIOLET :: Color{135, 60, 190, 255}
DARKPURPLE :: Color{112, 31, 126, 255}
BEIGE :: Color{211, 176, 131, 255}
BROWN :: Color{127, 106, 79, 255}
DARKBROWN :: Color{76, 63, 47, 255}
WHITE :: Color{255, 255, 255, 255}
BLACK :: Color{0, 0, 0, 255}
BLANK :: Color{0, 0, 0, 0}
MAGENTA :: Color{255, 0, 255, 255}
RAYWHITE :: Color{245, 245, 245, 255}

foreign import null0_api "null0"

@(default_calling_convention="c")
foreign null0_api {

    // COLORS
    // Tint a color with another color.
    color_tint :: proc(color: Color, tint: Color) -> ^Color ---
    // Fade a color.
    color_fade :: proc(color: Color, alpha: f32) -> ^Color ---
    // Change the brightness of a color.
    color_brightness :: proc(color: Color, factor: f32) -> ^Color ---
    // Invert a color.
    color_invert :: proc(color: Color) -> ^Color ---
    // Blend 2 colors together.
    color_alpha_blend :: proc(dst: Color, src: Color) -> ^Color ---
    // Change contrast of a color.
    color_contrast :: proc(color: Color, contrast: f32) -> ^Color ---
    // Interpolate colors.
    color_bilinear_interpolate :: proc(color00: Color, color01: Color, color10: Color, color11: Color, coordinateX: f32, coordinateY: f32) -> ^Color ---

    // GRAPHICS
    // Create a new blank image.
    new_image :: proc(width: i32, height: i32, color: Color) -> Image ---
    // Copy an image to a new image.
    image_copy :: proc(image: Image) -> Image ---
    // Create an image from a region of another image.
    image_subimage :: proc(image: Image, x: i32, y: i32, width: i32, height: i32) -> Image ---
    // Clear the screen.
    clear :: proc(color: Color) ---
    // Draw a single pixel on the screen.
    draw_point :: proc(x: i32, y: i32, color: Color) ---
    // Draw a line on the screen.
    draw_line :: proc(startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color) ---
    // Draw a filled rectangle on the screen.
    draw_rectangle :: proc(posX: i32, posY: i32, width: i32, height: i32, color: Color) ---
    // Draw a filled triangle on the screen.
    draw_triangle :: proc(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color) ---
    // Draw a filled ellipse on the screen.
    draw_ellipse :: proc(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color) ---
    // Draw a filled circle on the screen.
    draw_circle :: proc(centerX: i32, centerY: i32, radius: i32, color: Color) ---
    // Draw a filled polygon on the screen.
    draw_polygon :: proc(points: [^]Vector, numPoints: i32, color: Color) ---
    // Draw a filled arc on the screen.
    draw_arc :: proc(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, color: Color) ---
    // Draw a filled round-rectangle on the screen.
    draw_rectangle_rounded :: proc(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color) ---
    // Draw an image on the screen.
    draw_image :: proc(src: Image, posX: i32, posY: i32) ---
    // Draw a tinted image on the screen.
    draw_image_tint :: proc(src: Image, posX: i32, posY: i32, tint: Color) ---
    // Draw an image, rotated, on the screen.
    draw_image_rotated :: proc(src: Image, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) ---
    // Draw an image, flipped, on the screen.
    draw_image_flipped :: proc(src: Image, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) ---
    // Draw an image, scaled, on the screen.
    draw_image_scaled :: proc(src: Image, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) ---
    // Draw some text on the screen.
    draw_text :: proc(font: Font, text: cstring, posX: i32, posY: i32, color: Color) ---
    // Save an image to persistant storage.
    save_image :: proc(image: Image, filename: cstring) ---
    // Load an image from a file in cart.
    load_image :: proc(filename: cstring) -> Image ---
    // Resize an image, return copy.
    image_resize :: proc(image: Image, newWidth: i32, newHeight: i32, filter: ImageFilter) -> Image ---
    // Scale an image, return copy.
    image_scale :: proc(image: Image, scaleX: f32, scaleY: f32, filter: ImageFilter) -> Image ---
    // Replace a color in an image, in-place.
    image_color_replace :: proc(image: Image, color: Color, replace: Color) ---
    // Tint a color in an image, in-place.
    image_color_tint :: proc(image: Image, color: Color) ---
    // Fade a color in an image, in-place.
    image_color_fade :: proc(image: Image, alpha: f32) ---
    // Copy a font to a new font.
    font_copy :: proc(font: Font) -> Font ---
    // Scale a font, return a new font.
    font_scale :: proc(font: Font, scaleX: f32, scaleY: f32, filter: ImageFilter) -> Font ---
    // Load a BMF font from a file in cart.
    load_font_bmf :: proc(filename: cstring, characters: cstring) -> Font ---
    // Load a BMF font from an image.
    load_font_bmf_from_image :: proc(image: Image, characters: cstring) -> Font ---
    // Measure the size of some text.
    measure_text :: proc(font: Font, text: cstring, textLength: i32) -> ^Dimensions ---
    // Meaure an image (use 0 for screen).
    measure_image :: proc(image: Image) -> ^Dimensions ---
    // Load a TTY font from a file in cart.
    load_font_tty :: proc(filename: cstring, glyphWidth: i32, glyphHeight: i32, characters: cstring) -> Font ---
    // Load a TTY font from an image.
    load_font_tty_from_image :: proc(image: Image, glyphWidth: i32, glyphHeight: i32, characters: cstring) -> Font ---
    // Load a TTF font from a file in cart.
    load_font_ttf :: proc(filename: cstring, fontSize: i32) -> Font ---
    // Invert the colors in an image, in-place.
    image_color_invert :: proc(image: Image) ---
    // Calculate a rectangle representing the available alpha border in an image.
    image_alpha_border :: proc(image: Image, threshold: f32) -> ^Rectangle ---
    // Crop an image, in-place.
    image_crop :: proc(image: Image, x: i32, y: i32, width: i32, height: i32) ---
    // Crop an image based on the alpha border, in-place.
    image_alpha_crop :: proc(image: Image, threshold: f32) ---
    // Adjust the brightness of an image, in-place.
    image_color_brightness :: proc(image: Image, factor: f32) ---
    // Flip an image, in-place.
    image_flip :: proc(image: Image, horizontal: bool, vertical: bool) ---
    // Change the contrast of an image, in-place.
    image_color_contrast :: proc(image: Image, contrast: f32) ---
    // Use an image as an alpha-mask on another image.
    image_alpha_mask :: proc(image: Image, alphaMask: Image, posX: i32, posY: i32) ---
    // Create a new image, rotating another image.
    image_rotate :: proc(image: Image, degrees: f32, filter: ImageFilter) -> Image ---
    // Create a new image of a gradient.
    image_gradient :: proc(width: i32, height: i32, topLeft: Color, topRight: Color, bottomLeft: Color, bottomRight: Color) -> Image ---
    // Unload an image.
    unload_image :: proc(image: Image) ---
    // Unload a font.
    unload_font :: proc(font: Font) ---
    // Clear an image.
    clear_image :: proc(destination: Image, color: Color) ---
    // Draw a single pixel on an image.
    draw_point_on_image :: proc(destination: Image, x: i32, y: i32, color: Color) ---
    // Draw a line on an image.
    draw_line_on_image :: proc(destination: Image, startPosX: i32, startPosY: i32, endPosX: i32, endPosY: i32, color: Color) ---
    // Draw a filled rectangle on an image.
    draw_rectangle_on_image :: proc(destination: Image, posX: i32, posY: i32, width: i32, height: i32, color: Color) ---
    // Draw a filled triangle on an image.
    draw_triangle_on_image :: proc(destination: Image, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, color: Color) ---
    // Draw a filled ellipse on an image.
    draw_ellipse_on_image :: proc(destination: Image, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, color: Color) ---
    // Draw a circle on an image.
    draw_circle_on_image :: proc(destination: Image, centerX: i32, centerY: i32, radius: i32, color: Color) ---
    // Draw a filled polygon on an image.
    draw_polygon_on_image :: proc(destination: Image, points: [^]Vector, numPoints: i32, color: Color) ---
    // Draw a filled round-rectangle on an image.
    draw_rectangle_rounded_on_image :: proc(destination: Image, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, color: Color) ---
    // Draw an image on an image.
    draw_image_on_image :: proc(destination: Image, src: Image, posX: i32, posY: i32) ---
    // Draw a tinted image on an image.
    draw_image_tint_on_image :: proc(destination: Image, src: Image, posX: i32, posY: i32, tint: Color) ---
    // Draw an image, rotated, on an image.
    draw_image_rotated_on_image :: proc(destination: Image, src: Image, posX: i32, posY: i32, degrees: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) ---
    // Draw an image, flipped, on an image.
    draw_image_flipped_on_image :: proc(destination: Image, src: Image, posX: i32, posY: i32, flipHorizontal: bool, flipVertical: bool, flipDiagonal: bool) ---
    // Draw an image, scaled, on an image.
    draw_image_scaled_on_image :: proc(destination: Image, src: Image, posX: i32, posY: i32, scaleX: f32, scaleY: f32, offsetX: f32, offsetY: f32, filter: ImageFilter) ---
    // Draw some text on an image.
    draw_text_on_image :: proc(destination: Image, font: Font, text: cstring, posX: i32, posY: i32, color: Color) ---
    // Draw a outlined (with thickness) rectangle on the screen.
    draw_rectangle_outline :: proc(posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) triangle on the screen.
    draw_triangle_outline :: proc(x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) ellipse on the screen.
    draw_ellipse_outline :: proc(centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) circle on the screen.
    draw_circle_outline :: proc(centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) polygon on the screen.
    draw_polygon_outline :: proc(points: [^]Vector, numPoints: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) arc on the screen.
    draw_arc_outline :: proc(centerX: i32, centerY: i32, radius: f32, startAngle: f32, endAngle: f32, segments: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) round-rectangle on the screen.
    draw_rectangle_rounded_outline :: proc(x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) rectangle on an image.
    draw_rectangle_outline_on_image :: proc(destination: Image, posX: i32, posY: i32, width: i32, height: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) triangle on an image.
    draw_triangle_outline_on_image :: proc(destination: Image, x1: i32, y1: i32, x2: i32, y2: i32, x3: i32, y3: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) ellipse on an image.
    draw_ellipse_outline_on_image :: proc(destination: Image, centerX: i32, centerY: i32, radiusX: i32, radiusY: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) circle on an image.
    draw_circle_outline_on_image :: proc(destination: Image, centerX: i32, centerY: i32, radius: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) polygon on an image.
    draw_polygon_outline_on_image :: proc(destination: Image, points: [^]Vector, numPoints: i32, thickness: i32, color: Color) ---
    // Draw a outlined (with thickness) round-rectangle on an image.
    draw_rectangle_rounded_outline_on_image :: proc(destination: Image, x: i32, y: i32, width: i32, height: i32, cornerRadius: i32, thickness: i32, color: Color) ---

    // GUI
    // Begin a GUI window. Returns false if the window is collapsed or closed - skip its contents, but still call gui_end_window.
    gui_begin_window :: proc(title: cstring, rect: Rectangle) -> bool ---
    // End the current GUI window.
    gui_end_window :: proc() ---
    // A button. Returns true when it is clicked.
    gui_button :: proc(label: cstring) -> bool ---
    // A static text label.
    gui_label :: proc(text: cstring) ---
    // A block of wrapping text.
    gui_text :: proc(text: cstring) ---
    // A checkbox. Returns the (possibly changed) state.
    gui_checkbox :: proc(label: cstring, state: bool) -> bool ---
    // A slider. Returns the (possibly changed) value.
    gui_slider :: proc(value: f32, low: f32, high: f32) -> f32 ---
    // Set the current layout row - the column widths (negative for flexible), and the row height.
    gui_layout_row :: proc(widths: [^]i32, numWidths: i32, height: i32) ---
    // Finish building the GUI for this frame. Called automatically at the end of update if you do not call it.
    gui_end :: proc() ---
    // Draw the GUI to an image (0 is the screen).
    gui_draw :: proc(dst: Image) ---

    // INPUT
    // Has the key been pressed? (tracks unpress/read correctly.)
    key_pressed :: proc(key: Key) -> bool ---
    // Is the key currently down?
    key_down :: proc(key: Key) -> bool ---
    // Has the key been released? (tracks press/read correctly.)
    key_released :: proc(key: Key) -> bool ---
    // Is the key currently up?
    key_up :: proc(key: Key) -> bool ---
    // Has the button been pressed? (tracks unpress/read correctly.)
    gamepad_button_pressed :: proc(gamepad: i32, button: GamepadButton) -> bool ---
    // Is the button currently down?
    gamepad_button_down :: proc(gamepad: i32, button: GamepadButton) -> bool ---
    // Has the button been released? (tracks press/read correctly.)
    gamepad_button_released :: proc(gamepad: i32, button: GamepadButton) -> bool ---
    // Get current position of mouse.
    mouse_position :: proc() -> ^Vector ---
    // Has the button been pressed? (tracks unpress/read correctly.)
    mouse_button_pressed :: proc(button: MouseButton) -> bool ---
    // Is the button currently down?
    mouse_button_down :: proc(button: MouseButton) -> bool ---
    // Has the button been released? (tracks press/read correctly.)
    mouse_button_released :: proc(button: MouseButton) -> bool ---
    // Is the button currently up?
    mouse_button_up :: proc(button: MouseButton) -> bool ---

    // SOUND
    // Load a sound from a file in cart.
    load_sound :: proc(filename: cstring) -> Sound ---
    // Play a sound.
    play_sound :: proc(sound: Sound, loop: bool) ---
    // Stop a sound.
    stop_sound :: proc(sound: Sound) ---
    // Unload a sound.
    unload_sound :: proc(sound: Sound) ---
    // Speak some text and return a sound. Set things to 0 for defaults.
    tts_sound :: proc(text: cstring, phonetic: bool, pitch: i32, speed: i32, throat: i32, mouth: i32, sing: bool) -> Sound ---
    // Create Sfx sound.
    sfx_sound :: proc(params: ^SfxParams) -> Sound ---
    // Create Sfx parameters.
    sfx_generate :: proc(type: SfxPresetType) -> ^SfxParams ---

    // TILE
    // Load a tilemap (a Tiled map, exported as JSON) from a file in cart.
    load_tilemap :: proc(filename: cstring) -> Tilemap ---
    // Unload a tilemap.
    unload_tilemap :: proc(tilemap: Tilemap) ---
    // Update a tilemap's animation timers (deltaTime is in seconds).
    tile_update :: proc(tilemap: Tilemap, deltaTime: f32) ---
    // Get the size of a tilemap, in tiles.
    tile_map_size :: proc(tilemap: Tilemap) -> ^Dimensions ---
    // Get the size of a single tile of a tilemap, in pixels.
    tile_tile_size :: proc(tilemap: Tilemap) -> ^Dimensions ---
    // Get a custom property of a tilemap, by name (PROP_NONE when there is no such property.)
    tile_map_prop :: proc(tilemap: Tilemap, name: cstring) -> ^TilemapProp ---
    // Get the number of custom properties on a tilemap.
    tile_map_prop_count :: proc(tilemap: Tilemap) -> i32 ---
    // Get a custom property of a tilemap, by index (PROP_NONE when out of range.)
    tile_map_prop_at :: proc(tilemap: Tilemap, index: i32) -> ^TilemapProp ---
    // Draw a tilemap on the screen.
    tile_draw :: proc(tilemap: Tilemap, posX: i32, posY: i32) ---
    // Draw a tilemap on the screen, tinted by a color.
    tile_draw_tint :: proc(tilemap: Tilemap, posX: i32, posY: i32, tint: Color) ---
    // Draw a tilemap on an image.
    tile_draw_on_image :: proc(dst: Image, tilemap: Tilemap, posX: i32, posY: i32) ---
    // Render a whole tilemap to a new image.
    tilemap_image :: proc(tilemap: Tilemap) -> Image ---
    // Get the number of layers in a tilemap. Layers are numbered depth-first, so the children of a group layer have their own indexes too.
    tile_layer_count :: proc(tilemap: Tilemap) -> i32 ---
    // Get the index of a layer of a tilemap, by name (-1 when there is no such layer.)
    tile_layer_index :: proc(tilemap: Tilemap, name: cstring) -> i32 ---
    // Get the name of a layer of a tilemap.
    tile_layer_name :: proc(tilemap: Tilemap, layer: i32) -> cstring ---
    // Get the kind of a layer of a tilemap.
    tile_layer_type :: proc(tilemap: Tilemap, layer: i32) ---
    // Get the size of a layer of a tilemap, in tiles.
    tile_layer_size :: proc(tilemap: Tilemap, layer: i32) -> ^Dimensions ---
    // Get whether a layer of a tilemap is visible. Drawing a layer that Tiled marked hidden draws nothing.
    tile_layer_visible :: proc(tilemap: Tilemap, layer: i32) -> bool ---
    // Get a custom property of a layer of a tilemap, by name (PROP_NONE when there is no such property.)
    tile_layer_prop :: proc(tilemap: Tilemap, layer: i32, name: cstring) -> ^TilemapProp ---
    // Get the number of custom properties on a layer of a tilemap.
    tile_layer_prop_count :: proc(tilemap: Tilemap, layer: i32) -> i32 ---
    // Get a custom property of a layer of a tilemap, by index (PROP_NONE when out of range.)
    tile_layer_prop_at :: proc(tilemap: Tilemap, layer: i32, index: i32) -> ^TilemapProp ---
    // Draw a single layer of a tilemap on the screen.
    tile_draw_layer :: proc(tilemap: Tilemap, layer: i32, posX: i32, posY: i32) ---
    // Draw a single layer of a tilemap on the screen, tinted by a color.
    tile_draw_layer_tint :: proc(tilemap: Tilemap, layer: i32, posX: i32, posY: i32, tint: Color) ---
    // Draw a single layer of a tilemap on an image.
    tile_draw_layer_on_image :: proc(dst: Image, tilemap: Tilemap, layer: i32, posX: i32, posY: i32) ---
    // Render a single layer of a tilemap to a new image.
    tile_layer_image :: proc(tilemap: Tilemap, layer: i32) -> Image ---
    // Get the gid of the tile at a column/row in a tilemap layer.
    tile_get_tile :: proc(tilemap: Tilemap, layer: i32, column: i32, row: i32) -> i32 ---
    // Set the gid of the tile at a column/row in a tilemap layer. Swapping a gid is how a cart keeps changing state in the map itself.
    tile_set_tile :: proc(tilemap: Tilemap, layer: i32, column: i32, row: i32, gid: i32) ---
    // Draw a single tile from a tilemap on the screen.
    tile_draw_tile :: proc(tilemap: Tilemap, gid: i32, posX: i32, posY: i32) ---
    // Get a copy of the image of a single tile in a tilemap.
    tile_image :: proc(tilemap: Tilemap, gid: i32) -> Image ---
    // Get a custom property of a tile of a tilemap, by name (PROP_NONE when there is no such property.) These come from the tileset, so every tile with this gid shares them.
    tile_gid_prop :: proc(tilemap: Tilemap, gid: i32, name: cstring) -> ^TilemapProp ---
    // Get the number of custom properties on a tile of a tilemap.
    tile_gid_prop_count :: proc(tilemap: Tilemap, gid: i32) -> i32 ---
    // Get a custom property of a tile of a tilemap, by index (PROP_NONE when out of range.)
    tile_gid_prop_at :: proc(tilemap: Tilemap, gid: i32, index: i32) -> ^TilemapProp ---
    // Get the number of objects on an object-layer of a tilemap.
    tile_object_count :: proc(tilemap: Tilemap, layer: i32) -> i32 ---
    // Get an object from an object-layer of a tilemap.
    tile_object :: proc(tilemap: Tilemap, layer: i32, index: i32) -> ^TilemapObject ---
    // Get the index of an object on an object-layer of a tilemap, by name (-1 when there is no such object.)
    tile_object_index :: proc(tilemap: Tilemap, layer: i32, name: cstring) -> i32 ---
    // Get a custom property of an object of a tilemap, by name (PROP_NONE when there is no such property.)
    tile_object_prop :: proc(tilemap: Tilemap, layer: i32, index: i32, name: cstring) -> ^TilemapProp ---
    // Get the number of custom properties on an object of a tilemap.
    tile_object_prop_count :: proc(tilemap: Tilemap, layer: i32, index: i32) -> i32 ---
    // Get a custom property of an object of a tilemap, by index (PROP_NONE when out of range.)
    tile_object_prop_at :: proc(tilemap: Tilemap, layer: i32, index: i32, propIndex: i32) -> ^TilemapProp ---

    // TYPES

    // UTILITIES
    // Get system-time (ms) since unix epoch.
    current_time :: proc() -> u64 ---
    // Get the change in time (seconds) since the last update run.
    delta_time :: proc() -> f32 ---
    // Get a random integer between 2 numbers.
    random_int :: proc(min: i32, max: i32) -> i32 ---
    // Get the random-seed.
    random_seed_get :: proc() -> u64 ---
    // Set the random-seed.
    random_seed_set :: proc(seed: u64) ---
}
