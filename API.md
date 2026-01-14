The Null0 API is exposed to several languages, but we try to keep the syntax mostly the same. See docs/templates in individual languages for exact syntax, this page is more about what you can do with null0. I will use C-like pseudo-code to describe everything here.

## types

These are the types of parameters or things that functions can return.

```c
// This function does not return anything.
void

// Signed integer, 32 bits (4 bytes.)
i32

// Unsigned integer, 32 bits (4 bytes.)
u32

// Unsigned integer, 64 bits (8 bytes.)
u64

// Floating-point decimal, 32 bits (4 bytes.)
f32

// Boolean (true/false.)
bool

// An image. 0 is "the screen".
Image

// A font. 0 is "the default font".
Font

// A sound.
Sound

// Pointer to a null-terminated UTF8 string. (char*)
string

// An array of Vectors.
Vector[]

```


### structs

This is a compound-object, like a row in a spreadsheet. These are used to pass multiple values as a single object.

```c
// Sfx parameters.
struct SfxParams {
  u32 randSeed,
  i32 waveType,
  f32 attackTime,
  f32 sustainTime,
  f32 sustainPunch,
  f32 decayTime,
  f32 startFrequency,
  f32 minFrequency,
  f32 slide,
  f32 deltaSlide,
  f32 vibratoDepth,
  f32 vibratoSpeed,
  f32 changeAmount,
  f32 changeSpeed,
  f32 squareDuty,
  f32 dutySweep,
  f32 repeatSpeed,
  f32 phaserOffset,
  f32 phaserSweep,
  f32 lpfCutoff,
  f32 lpfCutoffSweep,
  f32 lpfResonance,
  f32 hpfCutoff,
  f32 hpfCutoffSweep
}

// The 2D size of something (width/height.)
struct Dimensions {
  i32 width,
  i32 height
}

// The 2D position of something (x/y.)
struct Vector {
  i32 x,
  i32 y
}

// The 2D position + size of something (x/y/w/h.)
struct Rectangle {
  i32 x,
  i32 y,
  i32 width,
  i32 height
}

// An RGBA color.
struct Color {
  u8 r,
  u8 g,
  u8 b,
  u8 a
}

```


### enums

This is a textual way to describe some possible options for an integer field.

```c
// Potential image-filtering techniques for scale/etc.
enum ImageFilter {
  FILTER_NEARESTNEIGHBOR = 0,
  FILTER_BILINEAR = 1,
  FILTER_SMOOTH = 2
}

// Represents a Sfx preset type.
enum SfxPresetType {
  SFX_COIN = 0,
  SFX_LASER = 1,
  SFX_EXPLOSION = 2,
  SFX_POWERUP = 3,
  SFX_HURT = 4,
  SFX_JUMP = 5,
  SFX_SELECT = 6,
  SFX_SYNTH = 7
}

// Represents a keyboard key.
enum Key {
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
  KEY_MENU = 348
}

// Represents a gamepad button.
enum GamepadButton {
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
  GAMEPAD_BUTTON_RIGHT_THUMB = 17
}

// Represents a mouse button.
enum MouseButton {
  MOUSE_BUTTON_UNKNOWN = 0,
  MOUSE_BUTTON_LEFT = 1,
  MOUSE_BUTTON_RIGHT = 2,
  MOUSE_BUTTON_MIDDLE = 3
}

```


### colors

These colors are pre-defined in most cart-languages:

- `LIGHTGRAY`
- `GRAY`
- `DARKGRAY`
- `YELLOW`
- `GOLD`
- `ORANGE`
- `PINK`
- `RED`
- `MAROON`
- `GREEN`
- `LIME`
- `DARKGREEN`
- `SKYBLUE`
- `BLUE`
- `DARKBLUE`
- `PURPLE`
- `VIOLET`
- `DARKPURPLE`
- `BEIGE`
- `BROWN`
- `DARKBROWN`
- `WHITE`
- `BLACK`
- `BLANK` - Completely transparent.
- `MAGENTA`
- `RAYWHITE` - A nice off-white, from Raylib.


## callbacks

Callbacks are how you define your game. See [cart](https://notnull.games/null0/cart) for more info.


#### buttonUp

Mapped controller (keys and gamepad will trigger) callback for when a "button" is unpressed.

```c
void buttonUp(GamepadButton button, u32 player)
```


#### buttonDown

Mapped controller (keys and gamepad will trigger) callback for when a "button" is pressed.

```c
void buttonDown(GamepadButton button, u32 player)
```


#### keyUp

Called when keys are unpressed.

```c
void keyUp(Key key)
```


#### keyDown

Called when keys are pressed.

```c
void keyDown(Key key)
```


#### mouseDown

Called when mouse-button is pressed.

```c
void mouseDown(MouseButton button)
```


#### mouseUp

Called when mouse-button is released.

```c
void mouseUp(MouseButton button)
```


#### mouseMoved

Called when mouse is moved.

```c
void mouseMoved(f32 x, f32 y)
```


## api

These are what make up the things you can do in your game.


### colors

#### color_tint

Tint a color with another color.

```c
Color color_tint(Color color, Color tint)
```


#### color_fade

Fade a color.

```c
Color color_fade(Color color, f32 alpha)
```


#### color_brightness

Change the brightness of a color.

```c
Color color_brightness(Color color, f32 factor)
```


#### color_invert

Invert a color.

```c
Color color_invert(Color color)
```


#### color_alpha_blend

Blend 2 colors together.

```c
Color color_alpha_blend(Color dst, Color src)
```


#### color_contrast

Change contrast of a color.

```c
Color color_contrast(Color color, f32 contrast)
```


#### color_bilinear_interpolate

Interpolate colors.

```c
Color color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, f32 coordinateX, f32 coordinateY)
```

---

### graphics

#### new_image

Create a new blank image.

```c
Image new_image(i32 width, i32 height, Color color)
```


#### image_copy

Copy an image to a new image.

```c
Image image_copy(Image image)
```


#### image_subimage

Create an image from a region of another image.

```c
Image image_subimage(Image image, i32 x, i32 y, i32 width, i32 height)
```


#### clear

Clear the screen.

```c
void clear(Color color)
```


#### draw_point

Draw a single pixel on the screen.

```c
void draw_point(i32 x, i32 y, Color color)
```


#### draw_line

Draw a line on the screen.

```c
void draw_line(i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color)
```


#### draw_rectangle

Draw a filled rectangle on the screen.

```c
void draw_rectangle(i32 posX, i32 posY, i32 width, i32 height, Color color)
```


#### draw_triangle

Draw a filled triangle on the screen.

```c
void draw_triangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color)
```


#### draw_ellipse

Draw a filled ellipse on the screen.

```c
void draw_ellipse(i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color)
```


#### draw_circle

Draw a filled circle on the screen.

```c
void draw_circle(i32 centerX, i32 centerY, i32 radius, Color color)
```


#### draw_polygon

Draw a filled polygon on the screen.

```c
void draw_polygon(Vector[] points, i32 numPoints, Color color)
```


#### draw_arc

Draw a filled arc on the screen.

```c
void draw_arc(i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, Color color)
```


#### draw_rectangle_rounded

Draw a filled round-rectangle on the screen.

```c
void draw_rectangle_rounded(i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color)
```


#### draw_image

Draw an image on the screen.

```c
void draw_image(Image src, i32 posX, i32 posY)
```


#### draw_image_tint

Draw a tinted image on the screen.

```c
void draw_image_tint(Image src, i32 posX, i32 posY, Color tint)
```


#### draw_image_rotated

Draw an image, rotated, on the screen.

```c
void draw_image_rotated(Image src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter)
```


#### draw_image_flipped

Draw an image, flipped, on the screen.

```c
void draw_image_flipped(Image src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal)
```


#### draw_image_scaled

Draw an image, scaled, on the screen.

```c
void draw_image_scaled(Image src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter)
```


#### draw_text

Draw some text on the screen.

```c
void draw_text(Font font, string text, i32 posX, i32 posY, Color color)
```


#### save_image

Save an image to persistant storage.

```c
void save_image(Image image, string filename)
```


#### load_image

Load an image from a file in cart.

```c
Image load_image(string filename)
```


#### image_resize

Resize an image, return copy.

```c
Image image_resize(Image image, i32 newWidth, i32 newHeight, ImageFilter filter)
```


#### image_scale

Scale an image, return copy.

```c
Image image_scale(Image image, f32 scaleX, f32 scaleY, ImageFilter filter)
```


#### image_color_replace

Replace a color in an image, in-place.

```c
void image_color_replace(Image image, Color color, Color replace)
```


#### image_color_tint

Tint a color in an image, in-place.

```c
void image_color_tint(Image image, Color color)
```


#### image_color_fade

Fade a color in an image, in-place.

```c
void image_color_fade(Image image, f32 alpha)
```


#### font_copy

Copy a font to a new font.

```c
Font font_copy(Font font)
```


#### font_scale

Scale a font, return a new font.

```c
Font font_scale(Font font, f32 scaleX, f32 scaleY, ImageFilter filter)
```


#### load_font_bmf

Load a BMF font from a file in cart.

```c
Font load_font_bmf(string filename, string characters)
```


#### load_font_bmf_from_image

Load a BMF font from an image.

```c
Font load_font_bmf_from_image(Image image, string characters)
```


#### measure_text

Measure the size of some text.

```c
Dimensions measure_text(Font font, string text, i32 textLength)
```


#### measure_image

Meaure an image (use 0 for screen).

```c
Dimensions measure_image(Image image)
```


#### load_font_tty

Load a TTY font from a file in cart.

```c
Font load_font_tty(string filename, i32 glyphWidth, i32 glyphHeight, string characters)
```


#### load_font_tty_from_image

Load a TTY font from an image.

```c
Font load_font_tty_from_image(Image image, i32 glyphWidth, i32 glyphHeight, string characters)
```


#### load_font_ttf

Load a TTF font from a file in cart.

```c
Font load_font_ttf(string filename, i32 fontSize)
```


#### image_color_invert

Invert the colors in an image, in-place.

```c
void image_color_invert(Image image)
```


#### image_alpha_border

Calculate a rectangle representing the available alpha border in an image.

```c
Rectangle image_alpha_border(Image image, f32 threshold)
```


#### image_crop

Crop an image, in-place.

```c
void image_crop(Image image, i32 x, i32 y, i32 width, i32 height)
```


#### image_alpha_crop

Crop an image based on the alpha border, in-place.

```c
void image_alpha_crop(Image image, f32 threshold)
```


#### image_color_brightness

Adjust the brightness of an image, in-place.

```c
void image_color_brightness(Image image, f32 factor)
```


#### image_flip

Flip an image, in-place.

```c
void image_flip(Image image, bool horizontal, bool vertical)
```


#### image_color_contrast

Change the contrast of an image, in-place.

```c
void image_color_contrast(Image image, f32 contrast)
```


#### image_alpha_mask

Use an image as an alpha-mask on another image.

```c
void image_alpha_mask(Image image, Image alphaMask, i32 posX, i32 posY)
```


#### image_rotate

Create a new image, rotating another image.

```c
Image image_rotate(Image image, f32 degrees, ImageFilter filter)
```


#### image_gradient

Create a new image of a gradient.

```c
Image image_gradient(i32 width, i32 height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight)
```


#### unload_image

Unload an image.

```c
void unload_image(Image image)
```


#### unload_font

Unload a font.

```c
void unload_font(Font font)
```


#### clear_image

Clear an image.

```c
void clear_image(Image destination, Color color)
```


#### draw_point_on_image

Draw a single pixel on an image.

```c
void draw_point_on_image(Image destination, i32 x, i32 y, Color color)
```


#### draw_line_on_image

Draw a line on an image.

```c
void draw_line_on_image(Image destination, i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color)
```


#### draw_rectangle_on_image

Draw a filled rectangle on an image.

```c
void draw_rectangle_on_image(Image destination, i32 posX, i32 posY, i32 width, i32 height, Color color)
```


#### draw_triangle_on_image

Draw a filled triangle on an image.

```c
void draw_triangle_on_image(Image destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color)
```


#### draw_ellipse_on_image

Draw a filled ellipse on an image.

```c
void draw_ellipse_on_image(Image destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color)
```


#### draw_circle_on_image

Draw a circle on an image.

```c
void draw_circle_on_image(Image destination, i32 centerX, i32 centerY, i32 radius, Color color)
```


#### draw_polygon_on_image

Draw a filled polygon on an image.

```c
void draw_polygon_on_image(Image destination, Vector[] points, i32 numPoints, Color color)
```


#### draw_rectangle_rounded_on_image

Draw a filled round-rectangle on an image.

```c
void draw_rectangle_rounded_on_image(Image destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color)
```


#### draw_image_on_image

Draw an image on an image.

```c
void draw_image_on_image(Image destination, Image src, i32 posX, i32 posY)
```


#### draw_image_tint_on_image

Draw a tinted image on an image.

```c
void draw_image_tint_on_image(Image destination, Image src, i32 posX, i32 posY, Color tint)
```


#### draw_image_rotated_on_image

Draw an image, rotated, on an image.

```c
void draw_image_rotated_on_image(Image destination, Image src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter)
```


#### draw_image_flipped_on_image

Draw an image, flipped, on an image.

```c
void draw_image_flipped_on_image(Image destination, Image src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal)
```


#### draw_image_scaled_on_image

Draw an image, scaled, on an image.

```c
void draw_image_scaled_on_image(Image destination, Image src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter)
```


#### draw_text_on_image

Draw some text on an image.

```c
void draw_text_on_image(Image destination, Font font, string text, i32 posX, i32 posY, Color color)
```


#### draw_rectangle_outline

Draw a outlined (with thickness) rectangle on the screen.

```c
void draw_rectangle_outline(i32 posX, i32 posY, i32 width, i32 height, i32 thickness, Color color)
```


#### draw_triangle_outline

Draw a outlined (with thickness) triangle on the screen.

```c
void draw_triangle_outline(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 thickness, Color color)
```


#### draw_ellipse_outline

Draw a outlined (with thickness) ellipse on the screen.

```c
void draw_ellipse_outline(i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, i32 thickness, Color color)
```


#### draw_circle_outline

Draw a outlined (with thickness) circle on the screen.

```c
void draw_circle_outline(i32 centerX, i32 centerY, i32 radius, i32 thickness, Color color)
```


#### draw_polygon_outline

Draw a outlined (with thickness) polygon on the screen.

```c
void draw_polygon_outline(Vector[] points, i32 numPoints, i32 thickness, Color color)
```


#### draw_arc_outline

Draw a outlined (with thickness) arc on the screen.

```c
void draw_arc_outline(i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, i32 thickness, Color color)
```


#### draw_rectangle_rounded_outline

Draw a outlined (with thickness) round-rectangle on the screen.

```c
void draw_rectangle_rounded_outline(i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, i32 thickness, Color color)
```


#### draw_rectangle_outline_on_image

Draw a outlined (with thickness) rectangle on an image.

```c
void draw_rectangle_outline_on_image(Image destination, i32 posX, i32 posY, i32 width, i32 height, i32 thickness, Color color)
```


#### draw_triangle_outline_on_image

Draw a outlined (with thickness) triangle on an image.

```c
void draw_triangle_outline_on_image(Image destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 thickness, Color color)
```


#### draw_ellipse_outline_on_image

Draw a outlined (with thickness) ellipse on an image.

```c
void draw_ellipse_outline_on_image(Image destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, i32 thickness, Color color)
```


#### draw_circle_outline_on_image

Draw a outlined (with thickness) circle on an image.

```c
void draw_circle_outline_on_image(Image destination, i32 centerX, i32 centerY, i32 radius, i32 thickness, Color color)
```


#### draw_polygon_outline_on_image

Draw a outlined (with thickness) polygon on an image.

```c
void draw_polygon_outline_on_image(Image destination, Vector[] points, i32 numPoints, i32 thickness, Color color)
```


#### draw_rectangle_rounded_outline_on_image

Draw a outlined (with thickness) round-rectangle on an image.

```c
void draw_rectangle_rounded_outline_on_image(Image destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, i32 thickness, Color color)
```

---

### input

#### key_pressed

Has the key been pressed? (tracks unpress/read correctly.)

```c
bool key_pressed(Key key)
```


#### key_down

Is the key currently down?

```c
bool key_down(Key key)
```


#### key_released

Has the key been released? (tracks press/read correctly.)

```c
bool key_released(Key key)
```


#### key_up

Is the key currently up?

```c
bool key_up(Key key)
```


#### gamepad_button_pressed

Has the button been pressed? (tracks unpress/read correctly.)

```c
bool gamepad_button_pressed(i32 gamepad, GamepadButton button)
```


#### gamepad_button_down

Is the button currently down?

```c
bool gamepad_button_down(i32 gamepad, GamepadButton button)
```


#### gamepad_button_released

Has the button been released? (tracks press/read correctly.)

```c
bool gamepad_button_released(i32 gamepad, GamepadButton button)
```


#### mouse_position

Get current position of mouse.

```c
Vector mouse_position()
```


#### mouse_button_pressed

Has the button been pressed? (tracks unpress/read correctly.)

```c
bool mouse_button_pressed(MouseButton button)
```


#### mouse_button_down

Is the button currently down?

```c
bool mouse_button_down(MouseButton button)
```


#### mouse_button_released

Has the button been released? (tracks press/read correctly.)

```c
bool mouse_button_released(MouseButton button)
```


#### mouse_button_up

Is the button currently up?

```c
bool mouse_button_up(MouseButton button)
```

---

### sound

#### load_sound

Load a sound from a file in cart.

```c
Sound load_sound(string filename)
```


#### play_sound

Play a sound.

```c
void play_sound(Sound sound, bool loop)
```


#### stop_sound

Stop a sound.

```c
void stop_sound(Sound sound)
```


#### unload_sound

Unload a sound.

```c
void unload_sound(Sound sound)
```


#### tts_sound

Speak some text and return a sound. Set things to 0 for defaults.

```c
Sound tts_sound(string text, bool phonetic, i32 pitch, i32 speed, i32 throat, i32 mouth, bool sing)
```


#### sfx_sound

Create Sfx sound.

```c
Sound sfx_sound(SfxParams params)
```


#### sfx_generate

Create Sfx parameters.

```c
SfxParams sfx_generate(SfxPresetType type)
```

---

### utilities

#### current_time

Get system-time (ms) since unix epoch.

```c
u64 current_time()
```


#### delta_time

Get the change in time (seconds) since the last update run.

```c
f32 delta_time()
```


#### random_int

Get a random integer between 2 numbers.

```c
i32 random_int(i32 min, i32 max)
```


#### random_seed_get

Get the random-seed.

```c
u64 random_seed_get()
```


#### random_seed_set

Set the random-seed.

```c
void random_seed_set(u64 seed)
```

