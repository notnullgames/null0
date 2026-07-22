;;; null0 - wisp bindings for the null0 fantasy console
;;;
;;; NOTE: experimental. wisp cannot currently import null0 host functions;
;;; these bindings document the API surface for when it can.
;;;
;;; Usage:
;;;
;;;   (defn load () (clear BLUE) (draw-circle 100 100 50 RED))
;;;
;;; ABI notes:
;;; - handles (Image/Font/Sound), enums and bools are i32
;;; - Color is 4 bytes packed into a single i32: r | g<<8 | b<<16 | a<<24


;;; constants
(def SCREEN 0)
(def SCREEN-WIDTH 640)
(def SCREEN-HEIGHT 480)
(def FONT-DEFAULT 0)

;;; colors (packed r | g<<8 | b<<16 | a<<24)
(def LIGHTGRAY 4291348680) ; rgba(200, 200, 200, 255)
(def GRAY 4286743170) ; rgba(130, 130, 130, 255)
(def DARKGRAY 4283453520) ; rgba(80, 80, 80, 255)
(def YELLOW 4278254077) ; rgba(253, 249, 0, 255)
(def GOLD 4278242303) ; rgba(255, 203, 0, 255)
(def ORANGE 4278231551) ; rgba(255, 161, 0, 255)
(def PINK 4290932223) ; rgba(255, 109, 194, 255)
(def RED 4281805286) ; rgba(230, 41, 55, 255)
(def MAROON 4281803198) ; rgba(190, 33, 55, 255)
(def GREEN 4281394176) ; rgba(0, 228, 48, 255)
(def LIME 4281310720) ; rgba(0, 158, 47, 255)
(def DARKGREEN 4281103616) ; rgba(0, 117, 44, 255)
(def SKYBLUE 4294950758) ; rgba(102, 191, 255, 255)
(def BLUE 4294015232) ; rgba(0, 121, 241, 255)
(def DARKBLUE 4289483264) ; rgba(0, 82, 172, 255)
(def PURPLE 4294933192) ; rgba(200, 122, 255, 255)
(def VIOLET 4290657415) ; rgba(135, 60, 190, 255)
(def DARKPURPLE 4286455664) ; rgba(112, 31, 126, 255)
(def BEIGE 4286820563) ; rgba(211, 176, 131, 255)
(def BROWN 4283394687) ; rgba(127, 106, 79, 255)
(def DARKBROWN 4281286476) ; rgba(76, 63, 47, 255)
(def WHITE 4294967295) ; rgba(255, 255, 255, 255)
(def BLACK 4278190080) ; rgba(0, 0, 0, 255)
(def BLANK 0) ; rgba(0, 0, 0, 0)
(def MAGENTA 4294902015) ; rgba(255, 0, 255, 255)
(def RAYWHITE 4294309365) ; rgba(245, 245, 245, 255)


;;; ImageFilter: Potential image-filtering techniques for scale/etc.
(def FILTER-NEARESTNEIGHBOR 0)
(def FILTER-BILINEAR 1)
(def FILTER-SMOOTH 2)

;;; SfxPresetType: Represents a Sfx preset type.
(def SFX-COIN 0)
(def SFX-LASER 1)
(def SFX-EXPLOSION 2)
(def SFX-POWERUP 3)
(def SFX-HURT 4)
(def SFX-JUMP 5)
(def SFX-SELECT 6)
(def SFX-SYNTH 7)

;;; Key: Represents a keyboard key.
(def KEY-INVALID 0)
(def KEY-SPACE 32)
(def KEY-APOSTROPHE 39)
(def KEY-COMMA 44)
(def KEY-MINUS 45)
(def KEY-PERIOD 46)
(def KEY-SLASH 47)
(def KEY-0 48)
(def KEY-1 49)
(def KEY-2 50)
(def KEY-3 51)
(def KEY-4 52)
(def KEY-5 53)
(def KEY-6 54)
(def KEY-7 55)
(def KEY-8 56)
(def KEY-9 57)
(def KEY-SEMICOLON 59)
(def KEY-EQUAL 61)
(def KEY-A 65)
(def KEY-B 66)
(def KEY-C 67)
(def KEY-D 68)
(def KEY-E 69)
(def KEY-F 70)
(def KEY-G 71)
(def KEY-H 72)
(def KEY-I 73)
(def KEY-J 74)
(def KEY-K 75)
(def KEY-L 76)
(def KEY-M 77)
(def KEY-N 78)
(def KEY-O 79)
(def KEY-P 80)
(def KEY-Q 81)
(def KEY-R 82)
(def KEY-S 83)
(def KEY-T 84)
(def KEY-U 85)
(def KEY-V 86)
(def KEY-W 87)
(def KEY-X 88)
(def KEY-Y 89)
(def KEY-Z 90)
(def KEY-LEFT-BRACKET 91)
(def KEY-BACKSLASH 92)
(def KEY-RIGHT-BRACKET 93)
(def KEY-GRAVE-ACCENT 96)
(def KEY-WORLD-1 161)
(def KEY-WORLD-2 162)
(def KEY-ESCAPE 256)
(def KEY-ENTER 257)
(def KEY-TAB 258)
(def KEY-BACKSPACE 259)
(def KEY-INSERT 260)
(def KEY-DELETE 261)
(def KEY-RIGHT 262)
(def KEY-LEFT 263)
(def KEY-DOWN 264)
(def KEY-UP 265)
(def KEY-PAGE-UP 266)
(def KEY-PAGE-DOWN 267)
(def KEY-HOME 268)
(def KEY-END 269)
(def KEY-CAPS-LOCK 280)
(def KEY-SCROLL-LOCK 281)
(def KEY-NUM-LOCK 282)
(def KEY-PRINT-SCREEN 283)
(def KEY-PAUSE 284)
(def KEY-F1 290)
(def KEY-F2 291)
(def KEY-F3 292)
(def KEY-F4 293)
(def KEY-F5 294)
(def KEY-F6 295)
(def KEY-F7 296)
(def KEY-F8 297)
(def KEY-F9 298)
(def KEY-F10 299)
(def KEY-F11 300)
(def KEY-F12 301)
(def KEY-F13 302)
(def KEY-F14 303)
(def KEY-F15 304)
(def KEY-F16 305)
(def KEY-F17 306)
(def KEY-F18 307)
(def KEY-F19 308)
(def KEY-F20 309)
(def KEY-F21 310)
(def KEY-F22 311)
(def KEY-F23 312)
(def KEY-F24 313)
(def KEY-F25 314)
(def KEY-KP-0 320)
(def KEY-KP-1 321)
(def KEY-KP-2 322)
(def KEY-KP-3 323)
(def KEY-KP-4 324)
(def KEY-KP-5 325)
(def KEY-KP-6 326)
(def KEY-KP-7 327)
(def KEY-KP-8 328)
(def KEY-KP-9 329)
(def KEY-KP-DECIMAL 330)
(def KEY-KP-DIVIDE 331)
(def KEY-KP-MULTIPLY 332)
(def KEY-KP-SUBTRACT 333)
(def KEY-KP-ADD 334)
(def KEY-KP-ENTER 335)
(def KEY-KP-EQUAL 336)
(def KEY-LEFT-SHIFT 340)
(def KEY-LEFT-CONTROL 341)
(def KEY-LEFT-ALT 342)
(def KEY-LEFT-SUPER 343)
(def KEY-RIGHT-SHIFT 344)
(def KEY-RIGHT-CONTROL 345)
(def KEY-RIGHT-ALT 346)
(def KEY-RIGHT-SUPER 347)
(def KEY-MENU 348)

;;; GamepadButton: Represents a gamepad button.
(def GAMEPAD-BUTTON-UNKNOWN 0)
(def GAMEPAD-BUTTON-UP 1)
(def GAMEPAD-BUTTON-RIGHT 2)
(def GAMEPAD-BUTTON-DOWN 3)
(def GAMEPAD-BUTTON-LEFT 4)
(def GAMEPAD-BUTTON-Y 5)
(def GAMEPAD-BUTTON-B 6)
(def GAMEPAD-BUTTON-A 7)
(def GAMEPAD-BUTTON-X 8)
(def GAMEPAD-BUTTON-LEFT-SHOULDER 9)
(def GAMEPAD-BUTTON-LEFT-TRIGGER 10)
(def GAMEPAD-BUTTON-RIGHT-SHOULDER 11)
(def GAMEPAD-BUTTON-RIGHT-TRIGGER 12)
(def GAMEPAD-BUTTON-SELECT 13)
(def GAMEPAD-BUTTON-MENU 14)
(def GAMEPAD-BUTTON-START 15)
(def GAMEPAD-BUTTON-LEFT-THUMB 16)
(def GAMEPAD-BUTTON-RIGHT-THUMB 17)

;;; MouseButton: Represents a mouse button.
(def MOUSE-BUTTON-UNKNOWN 0)
(def MOUSE-BUTTON-LEFT 1)
(def MOUSE-BUTTON-RIGHT 2)
(def MOUSE-BUTTON-MIDDLE 3)


;;; -- COLORS --
;;; Tint a color with another color.
;;; (color-tint color tint) -> Color
;;; Fade a color.
;;; (color-fade color alpha) -> Color
;;; Change the brightness of a color.
;;; (color-brightness color factor) -> Color
;;; Invert a color.
;;; (color-invert color) -> Color
;;; Blend 2 colors together.
;;; (color-alpha-blend dst src) -> Color
;;; Change contrast of a color.
;;; (color-contrast color contrast) -> Color
;;; Interpolate colors.
;;; (color-bilinear-interpolate color00 color01 color10 color11 coordinateX coordinateY) -> Color

;;; -- GRAPHICS --
;;; Create a new blank image.
;;; (new-image width height color) -> Image
;;; Copy an image to a new image.
;;; (image-copy image) -> Image
;;; Create an image from a region of another image.
;;; (image-subimage image x y width height) -> Image
;;; Clear the screen.
;;; (clear color)
;;; Draw a single pixel on the screen.
;;; (draw-point x y color)
;;; Draw a line on the screen.
;;; (draw-line startPosX startPosY endPosX endPosY color)
;;; Draw a filled rectangle on the screen.
;;; (draw-rectangle posX posY width height color)
;;; Draw a filled triangle on the screen.
;;; (draw-triangle x1 y1 x2 y2 x3 y3 color)
;;; Draw a filled ellipse on the screen.
;;; (draw-ellipse centerX centerY radiusX radiusY color)
;;; Draw a filled circle on the screen.
;;; (draw-circle centerX centerY radius color)
;;; Draw a filled polygon on the screen.
;;; (draw-polygon points numPoints color)
;;; Draw a filled arc on the screen.
;;; (draw-arc centerX centerY radius startAngle endAngle segments color)
;;; Draw a filled round-rectangle on the screen.
;;; (draw-rectangle-rounded x y width height cornerRadius color)
;;; Draw an image on the screen.
;;; (draw-image src posX posY)
;;; Draw a tinted image on the screen.
;;; (draw-image-tint src posX posY tint)
;;; Draw an image, rotated, on the screen.
;;; (draw-image-rotated src posX posY degrees offsetX offsetY filter)
;;; Draw an image, flipped, on the screen.
;;; (draw-image-flipped src posX posY flipHorizontal flipVertical flipDiagonal)
;;; Draw an image, scaled, on the screen.
;;; (draw-image-scaled src posX posY scaleX scaleY offsetX offsetY filter)
;;; Draw some text on the screen.
;;; (draw-text font text posX posY color)
;;; Save an image to persistant storage.
;;; (save-image image filename)
;;; Load an image from a file in cart.
;;; (load-image filename) -> Image
;;; Resize an image, return copy.
;;; (image-resize image newWidth newHeight filter) -> Image
;;; Scale an image, return copy.
;;; (image-scale image scaleX scaleY filter) -> Image
;;; Replace a color in an image, in-place.
;;; (image-color-replace image color replace)
;;; Tint a color in an image, in-place.
;;; (image-color-tint image color)
;;; Fade a color in an image, in-place.
;;; (image-color-fade image alpha)
;;; Copy a font to a new font.
;;; (font-copy font) -> Font
;;; Scale a font, return a new font.
;;; (font-scale font scaleX scaleY filter) -> Font
;;; Load a BMF font from a file in cart.
;;; (load-font-bmf filename characters) -> Font
;;; Load a BMF font from an image.
;;; (load-font-bmf-from-image image characters) -> Font
;;; Measure the size of some text.
;;; (measure-text font text textLength) -> Dimensions
;;; Meaure an image (use 0 for screen).
;;; (measure-image image) -> Dimensions
;;; Load a TTY font from a file in cart.
;;; (load-font-tty filename glyphWidth glyphHeight characters) -> Font
;;; Load a TTY font from an image.
;;; (load-font-tty-from-image image glyphWidth glyphHeight characters) -> Font
;;; Load a TTF font from a file in cart.
;;; (load-font-ttf filename fontSize) -> Font
;;; Invert the colors in an image, in-place.
;;; (image-color-invert image)
;;; Calculate a rectangle representing the available alpha border in an image.
;;; (image-alpha-border image threshold) -> Rectangle
;;; Crop an image, in-place.
;;; (image-crop image x y width height)
;;; Crop an image based on the alpha border, in-place.
;;; (image-alpha-crop image threshold)
;;; Adjust the brightness of an image, in-place.
;;; (image-color-brightness image factor)
;;; Flip an image, in-place.
;;; (image-flip image horizontal vertical)
;;; Change the contrast of an image, in-place.
;;; (image-color-contrast image contrast)
;;; Use an image as an alpha-mask on another image.
;;; (image-alpha-mask image alphaMask posX posY)
;;; Create a new image, rotating another image.
;;; (image-rotate image degrees filter) -> Image
;;; Create a new image of a gradient.
;;; (image-gradient width height topLeft topRight bottomLeft bottomRight) -> Image
;;; Unload an image.
;;; (unload-image image)
;;; Unload a font.
;;; (unload-font font)
;;; Clear an image.
;;; (clear-image destination color)
;;; Draw a single pixel on an image.
;;; (draw-point-on-image destination x y color)
;;; Draw a line on an image.
;;; (draw-line-on-image destination startPosX startPosY endPosX endPosY color)
;;; Draw a filled rectangle on an image.
;;; (draw-rectangle-on-image destination posX posY width height color)
;;; Draw a filled triangle on an image.
;;; (draw-triangle-on-image destination x1 y1 x2 y2 x3 y3 color)
;;; Draw a filled ellipse on an image.
;;; (draw-ellipse-on-image destination centerX centerY radiusX radiusY color)
;;; Draw a circle on an image.
;;; (draw-circle-on-image destination centerX centerY radius color)
;;; Draw a filled polygon on an image.
;;; (draw-polygon-on-image destination points numPoints color)
;;; Draw a filled round-rectangle on an image.
;;; (draw-rectangle-rounded-on-image destination x y width height cornerRadius color)
;;; Draw an image on an image.
;;; (draw-image-on-image destination src posX posY)
;;; Draw a tinted image on an image.
;;; (draw-image-tint-on-image destination src posX posY tint)
;;; Draw an image, rotated, on an image.
;;; (draw-image-rotated-on-image destination src posX posY degrees offsetX offsetY filter)
;;; Draw an image, flipped, on an image.
;;; (draw-image-flipped-on-image destination src posX posY flipHorizontal flipVertical flipDiagonal)
;;; Draw an image, scaled, on an image.
;;; (draw-image-scaled-on-image destination src posX posY scaleX scaleY offsetX offsetY filter)
;;; Draw some text on an image.
;;; (draw-text-on-image destination font text posX posY color)
;;; Draw a outlined (with thickness) rectangle on the screen.
;;; (draw-rectangle-outline posX posY width height thickness color)
;;; Draw a outlined (with thickness) triangle on the screen.
;;; (draw-triangle-outline x1 y1 x2 y2 x3 y3 thickness color)
;;; Draw a outlined (with thickness) ellipse on the screen.
;;; (draw-ellipse-outline centerX centerY radiusX radiusY thickness color)
;;; Draw a outlined (with thickness) circle on the screen.
;;; (draw-circle-outline centerX centerY radius thickness color)
;;; Draw a outlined (with thickness) polygon on the screen.
;;; (draw-polygon-outline points numPoints thickness color)
;;; Draw a outlined (with thickness) arc on the screen.
;;; (draw-arc-outline centerX centerY radius startAngle endAngle segments thickness color)
;;; Draw a outlined (with thickness) round-rectangle on the screen.
;;; (draw-rectangle-rounded-outline x y width height cornerRadius thickness color)
;;; Draw a outlined (with thickness) rectangle on an image.
;;; (draw-rectangle-outline-on-image destination posX posY width height thickness color)
;;; Draw a outlined (with thickness) triangle on an image.
;;; (draw-triangle-outline-on-image destination x1 y1 x2 y2 x3 y3 thickness color)
;;; Draw a outlined (with thickness) ellipse on an image.
;;; (draw-ellipse-outline-on-image destination centerX centerY radiusX radiusY thickness color)
;;; Draw a outlined (with thickness) circle on an image.
;;; (draw-circle-outline-on-image destination centerX centerY radius thickness color)
;;; Draw a outlined (with thickness) polygon on an image.
;;; (draw-polygon-outline-on-image destination points numPoints thickness color)
;;; Draw a outlined (with thickness) round-rectangle on an image.
;;; (draw-rectangle-rounded-outline-on-image destination x y width height cornerRadius thickness color)

;;; -- INPUT --
;;; Has the key been pressed? (tracks unpress/read correctly.)
;;; (key-pressed key) -> bool
;;; Is the key currently down?
;;; (key-down key) -> bool
;;; Has the key been released? (tracks press/read correctly.)
;;; (key-released key) -> bool
;;; Is the key currently up?
;;; (key-up key) -> bool
;;; Has the button been pressed? (tracks unpress/read correctly.)
;;; (gamepad-button-pressed gamepad button) -> bool
;;; Is the button currently down?
;;; (gamepad-button-down gamepad button) -> bool
;;; Has the button been released? (tracks press/read correctly.)
;;; (gamepad-button-released gamepad button) -> bool
;;; Get current position of mouse.
;;; (mouse-position) -> Vector
;;; Has the button been pressed? (tracks unpress/read correctly.)
;;; (mouse-button-pressed button) -> bool
;;; Is the button currently down?
;;; (mouse-button-down button) -> bool
;;; Has the button been released? (tracks press/read correctly.)
;;; (mouse-button-released button) -> bool
;;; Is the button currently up?
;;; (mouse-button-up button) -> bool

;;; -- SOUND --
;;; Load a sound from a file in cart.
;;; (load-sound filename) -> Sound
;;; Play a sound.
;;; (play-sound sound loop)
;;; Stop a sound.
;;; (stop-sound sound)
;;; Unload a sound.
;;; (unload-sound sound)
;;; Speak some text and return a sound. Set things to 0 for defaults.
;;; (tts-sound text phonetic pitch speed throat mouth sing) -> Sound
;;; Create Sfx sound.
;;; (sfx-sound params) -> Sound
;;; Create Sfx parameters.
;;; (sfx-generate type) -> SfxParams

;;; -- TYPES --

;;; -- UTILITIES --
;;; Get system-time (ms) since unix epoch.
;;; (current-time) -> u64
;;; Get the change in time (seconds) since the last update run.
;;; (delta-time) -> f32
;;; Get a random integer between 2 numbers.
;;; (random-int min max) -> i32
;;; Get the random-seed.
;;; (random-seed-get) -> u64
;;; Set the random-seed.
;;; (random-seed-set seed)
