The Null0 API is exposed to several languages, but we try to keep the syntax mostly the same. See docs/templates in individual languages for exact syntax, this page is more about what you can do with null0. I will use C-like pseudo-code to describe everything here.

## utilities

#### current_time

Get system-time (ms) since unix epoch

```c
u64 current_time()
```

#### delta_time

Get the change in time (seconds) since the last update run

```c
f32 delta_time()
```

#### random_int

Get a random integer between 2 numbers

```c
i32 random_int(i32 min, i32 max)
```

#### random_seed_get

Get the random-seed

```c
u64 random_seed_get()
```

#### random_seed_set

Set the random-seed

```c
void random_seed_set(u64 seed)
```


## sound

#### load_sound

Load a sound from a file in cart

```c
Sound load_sound(string filename)
```

#### play_sound

Play a sound

```c
void play_sound(Sound sound, bool loop)
```

#### stop_sound

Stop a sound

```c
void stop_sound(Sound sound)
```

#### unload_sound

Unload a sound

```c
void unload_sound(Sound sound)
```


## input

#### key_pressed

Has the key been pressed? (tracks unpress/read correctly)

```c
bool key_pressed(Key key)
```

#### key_down

Is the key currently down?

```c
bool key_down(Key key)
```

#### key_released

Has the key been released? (tracks press/read correctly)

```c
bool key_released(Key key)
```

#### key_up

Is the key currently up?

```c
bool key_up(Key key)
```

#### gamepad_button_pressed

Has the button been pressed? (tracks unpress/read correctly)

```c
bool gamepad_button_pressed(i32 gamepad, GamepadButton button)
```

#### gamepad_button_down

Is the button currently down?

```c
bool gamepad_button_down(i32 gamepad, GamepadButton button)
```

#### gamepad_button_released

Has the button been released? (tracks press/read correctly)

```c
bool gamepad_button_released(i32 gamepad, GamepadButton button)
```

#### mouse_position

Get current position of mouse

```c
Vector mouse_position()
```

#### mouse_button_pressed

Has the button been pressed? (tracks unpress/read correctly)

```c
bool mouse_button_pressed(MouseButton button)
```

#### mouse_button_down

Is the button currently down?

```c
bool mouse_button_down(MouseButton button)
```

#### mouse_button_released

Has the button been released? (tracks press/read correctly)

```c
bool mouse_button_released(MouseButton button)
```

#### mouse_button_up

Is the button currently up?

```c
bool mouse_button_up(MouseButton button)
```


## graphics

#### new_image

Create a new blank image

```c
Image new_image(i32 width, i32 height, Color color)
```

#### image_copy

Copy an image to a new image

```c
Image image_copy(Image image)
```

#### image_subimage

Create an image from a region of another image

```c
Image image_subimage(Image image, i32 x, i32 y, i32 width, i32 height)
```

#### clear

Clear the screen

```c
void clear(Color color)
```

#### draw_point

Draw a single pixel on the screen

```c
void draw_point(i32 x, i32 y, Color color)
```

#### draw_line

Draw a line on the screen

```c
void draw_line(i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color)
```

#### draw_rectangle

Draw a filled rectangle on the screen

```c
void draw_rectangle(i32 posX, i32 posY, i32 width, i32 height, Color color)
```

#### draw_triangle

Draw a filled triangle on the screen

```c
void draw_triangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color)
```

#### draw_ellipse

Draw a filled ellipse on the screen

```c
void draw_ellipse(i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color)
```

#### draw_circle

Draw a filled circle on the screen

```c
void draw_circle(i32 centerX, i32 centerY, i32 radius, Color color)
```

#### draw_polygon

Draw a filled polygon on the screen

```c
void draw_polygon(Vector[] points, i32 numPoints, Color color)
```

#### draw_arc

Draw a filled arc on the screen

```c
void draw_arc(i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, Color color)
```

#### draw_rectangle_rounded

Draw a filled round-rectangle on the screen

```c
void draw_rectangle_rounded(i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color)
```

#### draw_image

Draw an image on the screen

```c
void draw_image(Image src, i32 posX, i32 posY)
```

#### draw_image_tint

Draw a tinted image on the screen

```c
void draw_image_tint(Image src, i32 posX, i32 posY, Color tint)
```

#### draw_image_rotated

Draw an image, rotated, on the screen

```c
void draw_image_rotated(Image src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter)
```

#### draw_image_flipped

Draw an image, flipped, on the screen

```c
void draw_image_flipped(Image src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal)
```

#### draw_image_scaled

Draw an image, scaled, on the screen

```c
void draw_image_scaled(Image src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter)
```

#### draw_text

Draw some text on the screen

```c
void draw_text(Font font, string text, i32 posX, i32 posY, Color color)
```

#### save_image

Save an image to persistant storage

```c
void save_image(Image image, string filename)
```

#### load_image

Load an image from a file in cart

```c
Image load_image(string filename)
```

#### image_resize

Resize an image, return copy

```c
Image image_resize(Image image, i32 newWidth, i32 newHeight, ImageFilter filter)
```

#### image_scale

Scale an image, return copy

```c
Image image_scale(Image image, f32 scaleX, f32 scaleY, ImageFilter filter)
```

#### image_color_replace

Replace a color in an image, in-place

```c
void image_color_replace(Image image, Color color, Color replace)
```

#### image_color_tint

Tint a color in an image, in-place

```c
void image_color_tint(Image image, Color color)
```

#### image_color_fade

Fade a color in an image, in-place

```c
void image_color_fade(Image image, f32 alpha)
```

#### font_copy

Copy a font to a new font

```c
Font font_copy(Font font)
```

#### font_scale

Scale a font, return a new font

```c
Font font_scale(Font font, f32 scaleX, f32 scaleY, ImageFilter filter)
```

#### load_font_bmf

Load a BMF font from a file in cart

```c
Font load_font_bmf(string filename, string characters)
```

#### load_font_bmf_from_image

Load a BMF font from an image

```c
Font load_font_bmf_from_image(Image image, string characters)
```

#### measure_text

Measure the size of some text

```c
Dimensions measure_text(Font font, string text, i32 textLength)
```

#### measure_image

Meaure an image (use 0 for screen)

```c
Dimensions measure_image(Image image)
```

#### load_font_tty

Load a TTY font from a file in cart

```c
Font load_font_tty(string filename, i32 glyphWidth, i32 glyphHeight, string characters)
```

#### load_font_tty_from_image

Load a TTY font from an image

```c
Font load_font_tty_from_image(Image image, i32 glyphWidth, i32 glyphHeight, string characters)
```

#### load_font_ttf

Load a TTF font from a file in cart

```c
Font load_font_ttf(string filename, i32 fontSize)
```

#### image_color_invert

Invert the colors in an image, in-place

```c
void image_color_invert(Image image)
```

#### image_alpha_border

Calculate a rectangle representing the available alpha border in an image

```c
Rectangle image_alpha_border(Image image, f32 threshold)
```

#### image_crop

Crop an image, in-place

```c
void image_crop(Image image, i32 x, i32 y, i32 width, i32 height)
```

#### image_alpha_crop

Crop an image based on the alpha border, in-place

```c
void image_alpha_crop(Image image, f32 threshold)
```

#### image_color_brightness

Adjust the brightness of an image, in-place

```c
void image_color_brightness(Image image, f32 factor)
```

#### image_flip

Flip an image, in-place

```c
void image_flip(Image image, bool horizontal, bool vertical)
```

#### image_color_contrast

Change the contrast of an image, in-place

```c
void image_color_contrast(Image image, f32 contrast)
```

#### image_alpha_mask

Use an image as an alpha-mask on another image

```c
void image_alpha_mask(Image image, Image alphaMask, i32 posX, i32 posY)
```

#### image_rotate

Create a new image, rotating another image

```c
Image image_rotate(Image image, f32 degrees, ImageFilter filter)
```

#### image_gradient

Create a new image of a gradient

```c
Image image_gradient(i32 width, i32 height, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight)
```

#### unload_image

Unload an image

```c
void unload_image(Image image)
```

#### unload_font

Unload a font

```c
void unload_font(Font font)
```

#### clear_image

Clear an image

```c
void clear_image(Image destination, Color color)
```

#### draw_point_on_image

Draw a single pixel on an image

```c
void draw_point_on_image(Image destination, i32 x, i32 y, Color color)
```

#### draw_line_on_image

Draw a line on an image

```c
void draw_line_on_image(Image destination, i32 startPosX, i32 startPosY, i32 endPosX, i32 endPosY, Color color)
```

#### draw_rectangle_on_image

Draw a filled rectangle on an image

```c
void draw_rectangle_on_image(Image destination, i32 posX, i32 posY, i32 width, i32 height, Color color)
```

#### draw_triangle_on_image

Draw a filled triangle on an image

```c
void draw_triangle_on_image(Image destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, Color color)
```

#### draw_ellipse_on_image

Draw a filled ellipse on an image

```c
void draw_ellipse_on_image(Image destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, Color color)
```

#### draw_circle_on_image

Draw a circle on an image

```c
void draw_circle_on_image(Image destination, i32 centerX, i32 centerY, i32 radius, Color color)
```

#### draw_polygon_on_image

Draw a filled polygon on an image

```c
void draw_polygon_on_image(Image destination, Vector[] points, i32 numPoints, Color color)
```

#### draw_rectangle_rounded_on_image

Draw a filled round-rectangle on an image

```c
void draw_rectangle_rounded_on_image(Image destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, Color color)
```

#### draw_image_on_image

Draw an image on an image

```c
void draw_image_on_image(Image destination, Image src, i32 posX, i32 posY)
```

#### draw_image_tint_on_image

Draw a tinted image on an image

```c
void draw_image_tint_on_image(Image destination, Image src, i32 posX, i32 posY, Color tint)
```

#### draw_image_rotated_on_image

Draw an image, rotated, on an image

```c
void draw_image_rotated_on_image(Image destination, Image src, i32 posX, i32 posY, f32 degrees, f32 offsetX, f32 offsetY, ImageFilter filter)
```

#### draw_image_flipped_on_image

Draw an image, flipped, on an image

```c
void draw_image_flipped_on_image(Image destination, Image src, i32 posX, i32 posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal)
```

#### draw_image_scaled_on_image

Draw an image, scaled, on an image

```c
void draw_image_scaled_on_image(Image destination, Image src, i32 posX, i32 posY, f32 scaleX, f32 scaleY, f32 offsetX, f32 offsetY, ImageFilter filter)
```

#### draw_text_on_image

Draw some text on an image

```c
void draw_text_on_image(Image destination, Font font, string text, i32 posX, i32 posY, Color color)
```

#### draw_rectangle_outline

Draw a outlined (with thickness) rectangle on the screen

```c
void draw_rectangle_outline(i32 posX, i32 posY, i32 width, i32 height, i32 thickness, Color color)
```

#### draw_triangle_outline

Draw a outlined (with thickness) triangle on the screen

```c
void draw_triangle_outline(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 thickness, Color color)
```

#### draw_ellipse_outline

Draw a outlined (with thickness) ellipse on the screen

```c
void draw_ellipse_outline(i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, i32 thickness, Color color)
```

#### draw_circle_outline

Draw a outlined (with thickness) circle on the screen

```c
void draw_circle_outline(i32 centerX, i32 centerY, i32 radius, i32 thickness, Color color)
```

#### draw_polygon_outline

Draw a outlined (with thickness) polygon on the screen

```c
void draw_polygon_outline(Vector[] points, i32 numPoints, i32 thickness, Color color)
```

#### draw_arc_outline

Draw a outlined (with thickness) arc on the screen

```c
void draw_arc_outline(i32 centerX, i32 centerY, f32 radius, f32 startAngle, f32 endAngle, i32 segments, i32 thickness, Color color)
```

#### draw_rectangle_rounded_outline

Draw a outlined (with thickness) round-rectangle on the screen

```c
void draw_rectangle_rounded_outline(i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, i32 thickness, Color color)
```

#### draw_rectangle_outline_on_image

Draw a outlined (with thickness) rectangle on an image

```c
void draw_rectangle_outline_on_image(Image destination, i32 posX, i32 posY, i32 width, i32 height, i32 thickness, Color color)
```

#### draw_triangle_outline_on_image

Draw a outlined (with thickness) triangle on an image

```c
void draw_triangle_outline_on_image(Image destination, i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 thickness, Color color)
```

#### draw_ellipse_outline_on_image

Draw a outlined (with thickness) ellipse on an image

```c
void draw_ellipse_outline_on_image(Image destination, i32 centerX, i32 centerY, i32 radiusX, i32 radiusY, i32 thickness, Color color)
```

#### draw_circle_outline_on_image

Draw a outlined (with thickness) circle on an image

```c
void draw_circle_outline_on_image(Image destination, i32 centerX, i32 centerY, i32 radius, i32 thickness, Color color)
```

#### draw_polygon_outline_on_image

Draw a outlined (with thickness) polygon on an image

```c
void draw_polygon_outline_on_image(Image destination, Vector[] points, i32 numPoints, i32 thickness, Color color)
```

#### draw_rectangle_rounded_outline_on_image

Draw a outlined (with thickness) round-rectangle on an image

```c
void draw_rectangle_rounded_outline_on_image(Image destination, i32 x, i32 y, i32 width, i32 height, i32 cornerRadius, i32 thickness, Color color)
```


## colors

#### color_tint

Tint a color with another color

```c
Color color_tint(Color color, Color tint)
```

#### color_fade

Fade a color

```c
Color color_fade(Color color, f32 alpha)
```

#### color_brightness

Change the brightness of a color

```c
Color color_brightness(Color color, f32 factor)
```

#### color_invert

Invert a color

```c
Color color_invert(Color color)
```

#### color_alpha_blend

Blend 2 colors together

```c
Color color_alpha_blend(Color dst, Color src)
```

#### color_contrast

Change contrast of a color

```c
Color color_contrast(Color color, f32 contrast)
```

#### color_bilinear_interpolate

Interpolate colors

```c
Color color_bilinear_interpolate(Color color00, Color color01, Color color10, Color color11, f32 coordinateX, f32 coordinateY)
```
