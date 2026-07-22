      *> null0 - COBOL bindings for the null0 fantasy console
      *> (copybook - COPY null0 in WORKING-STORAGE SECTION.)
      *>
      *> Usage:
      *>
      *>     IDENTIFICATION DIVISION.
      *>     PROGRAM-ID. simple.
      *>     DATA DIVISION.
      *>     WORKING-STORAGE SECTION.
      *>     COPY null0.
      *>     PROCEDURE DIVISION.
      *>         CALL "clear" USING BY VALUE BLUE
      *>         CALL "draw_circle" USING BY VALUE 100 100 50 RED
      *>         STOP RUN.
      *>
      *> ABI notes:
      *> - handles (Image/Font/Sound), enums and bools are PIC 9(9) COMP-5
      *> - Color is 4 bytes packed: r | g<<8 | b<<16 | a<<24
      *> - strings are null-terminated (use Z"..." literals)


      *> constants
       78 NULL0-SCREEN     VALUE 0.
       78 SCREEN-WIDTH     VALUE 640.
       78 SCREEN-HEIGHT    VALUE 480.
       78 FONT-DEFAULT     VALUE 0.

      *> colors (packed r | g<<8 | b<<16 | a<<24)
       01  LIGHTGRAY     PIC 9(10) COMP-5 VALUE 4291348680. *> rgba(200, 200, 200, 255)
       01  GRAY          PIC 9(10) COMP-5 VALUE 4286743170. *> rgba(130, 130, 130, 255)
       01  DARKGRAY      PIC 9(10) COMP-5 VALUE 4283453520. *> rgba(80, 80, 80, 255)
       01  YELLOW        PIC 9(10) COMP-5 VALUE 4278254077. *> rgba(253, 249, 0, 255)
       01  GOLD          PIC 9(10) COMP-5 VALUE 4278242303. *> rgba(255, 203, 0, 255)
       01  ORANGE        PIC 9(10) COMP-5 VALUE 4278231551. *> rgba(255, 161, 0, 255)
       01  PINK          PIC 9(10) COMP-5 VALUE 4290932223. *> rgba(255, 109, 194, 255)
       01  RED           PIC 9(10) COMP-5 VALUE 4281805286. *> rgba(230, 41, 55, 255)
       01  MAROON        PIC 9(10) COMP-5 VALUE 4281803198. *> rgba(190, 33, 55, 255)
       01  GREEN         PIC 9(10) COMP-5 VALUE 4281394176. *> rgba(0, 228, 48, 255)
       01  LIME          PIC 9(10) COMP-5 VALUE 4281310720. *> rgba(0, 158, 47, 255)
       01  DARKGREEN     PIC 9(10) COMP-5 VALUE 4281103616. *> rgba(0, 117, 44, 255)
       01  SKYBLUE       PIC 9(10) COMP-5 VALUE 4294950758. *> rgba(102, 191, 255, 255)
       01  BLUE          PIC 9(10) COMP-5 VALUE 4294015232. *> rgba(0, 121, 241, 255)
       01  DARKBLUE      PIC 9(10) COMP-5 VALUE 4289483264. *> rgba(0, 82, 172, 255)
       01  PURPLE        PIC 9(10) COMP-5 VALUE 4294933192. *> rgba(200, 122, 255, 255)
       01  VIOLET        PIC 9(10) COMP-5 VALUE 4290657415. *> rgba(135, 60, 190, 255)
       01  DARKPURPLE    PIC 9(10) COMP-5 VALUE 4286455664. *> rgba(112, 31, 126, 255)
       01  BEIGE         PIC 9(10) COMP-5 VALUE 4286820563. *> rgba(211, 176, 131, 255)
       01  BROWN         PIC 9(10) COMP-5 VALUE 4283394687. *> rgba(127, 106, 79, 255)
       01  DARKBROWN     PIC 9(10) COMP-5 VALUE 4281286476. *> rgba(76, 63, 47, 255)
       01  WHITE         PIC 9(10) COMP-5 VALUE 4294967295. *> rgba(255, 255, 255, 255)
       01  BLACK         PIC 9(10) COMP-5 VALUE 4278190080. *> rgba(0, 0, 0, 255)
       01  NULL0-BLANK   PIC 9(10) COMP-5 VALUE 0. *> rgba(0, 0, 0, 0)
       01  MAGENTA       PIC 9(10) COMP-5 VALUE 4294902015. *> rgba(255, 0, 255, 255)
       01  RAYWHITE      PIC 9(10) COMP-5 VALUE 4294309365. *> rgba(245, 245, 245, 255)


      *> ImageFilter: Potential image-filtering techniques for scale/etc.
       78 FILTER-NEARESTNEIGHBOR        VALUE 0.
       78 FILTER-BILINEAR               VALUE 1.
       78 FILTER-SMOOTH                 VALUE 2.

      *> SfxPresetType: Represents a Sfx preset type.
       78 SFX-COIN                      VALUE 0.
       78 SFX-LASER                     VALUE 1.
       78 SFX-EXPLOSION                 VALUE 2.
       78 SFX-POWERUP                   VALUE 3.
       78 SFX-HURT                      VALUE 4.
       78 SFX-JUMP                      VALUE 5.
       78 SFX-SELECT                    VALUE 6.
       78 SFX-SYNTH                     VALUE 7.

      *> Key: Represents a keyboard key.
       78 KEY-INVALID                   VALUE 0.
       78 KEY-SPACE                     VALUE 32.
       78 KEY-APOSTROPHE                VALUE 39.
       78 KEY-COMMA                     VALUE 44.
       78 KEY-MINUS                     VALUE 45.
       78 KEY-PERIOD                    VALUE 46.
       78 KEY-SLASH                     VALUE 47.
       78 KEY-0                         VALUE 48.
       78 KEY-1                         VALUE 49.
       78 KEY-2                         VALUE 50.
       78 KEY-3                         VALUE 51.
       78 KEY-4                         VALUE 52.
       78 KEY-5                         VALUE 53.
       78 KEY-6                         VALUE 54.
       78 KEY-7                         VALUE 55.
       78 KEY-8                         VALUE 56.
       78 KEY-9                         VALUE 57.
       78 KEY-SEMICOLON                 VALUE 59.
       78 KEY-EQUAL                     VALUE 61.
       78 KEY-A                         VALUE 65.
       78 KEY-B                         VALUE 66.
       78 KEY-C                         VALUE 67.
       78 KEY-D                         VALUE 68.
       78 KEY-E                         VALUE 69.
       78 KEY-F                         VALUE 70.
       78 KEY-G                         VALUE 71.
       78 KEY-H                         VALUE 72.
       78 KEY-I                         VALUE 73.
       78 KEY-J                         VALUE 74.
       78 KEY-K                         VALUE 75.
       78 KEY-L                         VALUE 76.
       78 KEY-M                         VALUE 77.
       78 KEY-N                         VALUE 78.
       78 KEY-O                         VALUE 79.
       78 KEY-P                         VALUE 80.
       78 KEY-Q                         VALUE 81.
       78 KEY-R                         VALUE 82.
       78 KEY-S                         VALUE 83.
       78 KEY-T                         VALUE 84.
       78 KEY-U                         VALUE 85.
       78 KEY-V                         VALUE 86.
       78 KEY-W                         VALUE 87.
       78 KEY-X                         VALUE 88.
       78 KEY-Y                         VALUE 89.
       78 KEY-Z                         VALUE 90.
       78 KEY-LEFT-BRACKET              VALUE 91.
       78 KEY-BACKSLASH                 VALUE 92.
       78 KEY-RIGHT-BRACKET             VALUE 93.
       78 KEY-GRAVE-ACCENT              VALUE 96.
       78 KEY-WORLD-1                   VALUE 161.
       78 KEY-WORLD-2                   VALUE 162.
       78 KEY-ESCAPE                    VALUE 256.
       78 KEY-ENTER                     VALUE 257.
       78 KEY-TAB                       VALUE 258.
       78 KEY-BACKSPACE                 VALUE 259.
       78 KEY-INSERT                    VALUE 260.
       78 KEY-DELETE                    VALUE 261.
       78 KEY-RIGHT                     VALUE 262.
       78 KEY-LEFT                      VALUE 263.
       78 KEY-DOWN                      VALUE 264.
       78 KEY-UP                        VALUE 265.
       78 KEY-PAGE-UP                   VALUE 266.
       78 KEY-PAGE-DOWN                 VALUE 267.
       78 KEY-HOME                      VALUE 268.
       78 KEY-END                       VALUE 269.
       78 KEY-CAPS-LOCK                 VALUE 280.
       78 KEY-SCROLL-LOCK               VALUE 281.
       78 KEY-NUM-LOCK                  VALUE 282.
       78 KEY-PRINT-SCREEN              VALUE 283.
       78 KEY-PAUSE                     VALUE 284.
       78 KEY-F1                        VALUE 290.
       78 KEY-F2                        VALUE 291.
       78 KEY-F3                        VALUE 292.
       78 KEY-F4                        VALUE 293.
       78 KEY-F5                        VALUE 294.
       78 KEY-F6                        VALUE 295.
       78 KEY-F7                        VALUE 296.
       78 KEY-F8                        VALUE 297.
       78 KEY-F9                        VALUE 298.
       78 KEY-F10                       VALUE 299.
       78 KEY-F11                       VALUE 300.
       78 KEY-F12                       VALUE 301.
       78 KEY-F13                       VALUE 302.
       78 KEY-F14                       VALUE 303.
       78 KEY-F15                       VALUE 304.
       78 KEY-F16                       VALUE 305.
       78 KEY-F17                       VALUE 306.
       78 KEY-F18                       VALUE 307.
       78 KEY-F19                       VALUE 308.
       78 KEY-F20                       VALUE 309.
       78 KEY-F21                       VALUE 310.
       78 KEY-F22                       VALUE 311.
       78 KEY-F23                       VALUE 312.
       78 KEY-F24                       VALUE 313.
       78 KEY-F25                       VALUE 314.
       78 KEY-KP-0                      VALUE 320.
       78 KEY-KP-1                      VALUE 321.
       78 KEY-KP-2                      VALUE 322.
       78 KEY-KP-3                      VALUE 323.
       78 KEY-KP-4                      VALUE 324.
       78 KEY-KP-5                      VALUE 325.
       78 KEY-KP-6                      VALUE 326.
       78 KEY-KP-7                      VALUE 327.
       78 KEY-KP-8                      VALUE 328.
       78 KEY-KP-9                      VALUE 329.
       78 KEY-KP-DECIMAL                VALUE 330.
       78 KEY-KP-DIVIDE                 VALUE 331.
       78 KEY-KP-MULTIPLY               VALUE 332.
       78 KEY-KP-SUBTRACT               VALUE 333.
       78 KEY-KP-ADD                    VALUE 334.
       78 KEY-KP-ENTER                  VALUE 335.
       78 KEY-KP-EQUAL                  VALUE 336.
       78 KEY-LEFT-SHIFT                VALUE 340.
       78 KEY-LEFT-CONTROL              VALUE 341.
       78 KEY-LEFT-ALT                  VALUE 342.
       78 KEY-LEFT-SUPER                VALUE 343.
       78 KEY-RIGHT-SHIFT               VALUE 344.
       78 KEY-RIGHT-CONTROL             VALUE 345.
       78 KEY-RIGHT-ALT                 VALUE 346.
       78 KEY-RIGHT-SUPER               VALUE 347.
       78 KEY-MENU                      VALUE 348.

      *> GamepadButton: Represents a gamepad button.
       78 GAMEPAD-BUTTON-UNKNOWN        VALUE 0.
       78 GAMEPAD-BUTTON-UP             VALUE 1.
       78 GAMEPAD-BUTTON-RIGHT          VALUE 2.
       78 GAMEPAD-BUTTON-DOWN           VALUE 3.
       78 GAMEPAD-BUTTON-LEFT           VALUE 4.
       78 GAMEPAD-BUTTON-Y              VALUE 5.
       78 GAMEPAD-BUTTON-B              VALUE 6.
       78 GAMEPAD-BUTTON-A              VALUE 7.
       78 GAMEPAD-BUTTON-X              VALUE 8.
       78 GAMEPAD-BUTTON-LEFT-SHOULDER  VALUE 9.
       78 GAMEPAD-BUTTON-LEFT-TRIGGER   VALUE 10.
       78 GAMEPAD-BUTTON-RIGHT-SHOULDER VALUE 11.
       78 GAMEPAD-BUTTON-RIGHT-TRIGGER  VALUE 12.
       78 GAMEPAD-BUTTON-SELECT         VALUE 13.
       78 GAMEPAD-BUTTON-MENU           VALUE 14.
       78 GAMEPAD-BUTTON-START          VALUE 15.
       78 GAMEPAD-BUTTON-LEFT-THUMB     VALUE 16.
       78 GAMEPAD-BUTTON-RIGHT-THUMB    VALUE 17.

      *> MouseButton: Represents a mouse button.
       78 MOUSE-BUTTON-UNKNOWN          VALUE 0.
       78 MOUSE-BUTTON-LEFT             VALUE 1.
       78 MOUSE-BUTTON-RIGHT            VALUE 2.
       78 MOUSE-BUTTON-MIDDLE           VALUE 3.


      *> struct SfxParams: Sfx parameters.
      *>   offset 0: randSeed (u32)
      *>   offset 4: waveType (i32)
      *>   offset 8: attackTime (f32)
      *>   offset 12: sustainTime (f32)
      *>   offset 16: sustainPunch (f32)
      *>   offset 20: decayTime (f32)
      *>   offset 24: startFrequency (f32)
      *>   offset 28: minFrequency (f32)
      *>   offset 32: slide (f32)
      *>   offset 36: deltaSlide (f32)
      *>   offset 40: vibratoDepth (f32)
      *>   offset 44: vibratoSpeed (f32)
      *>   offset 48: changeAmount (f32)
      *>   offset 52: changeSpeed (f32)
      *>   offset 56: squareDuty (f32)
      *>   offset 60: dutySweep (f32)
      *>   offset 64: repeatSpeed (f32)
      *>   offset 68: phaserOffset (f32)
      *>   offset 72: phaserSweep (f32)
      *>   offset 76: lpfCutoff (f32)
      *>   offset 80: lpfCutoffSweep (f32)
      *>   offset 84: lpfResonance (f32)
      *>   offset 88: hpfCutoff (f32)
      *>   offset 92: hpfCutoffSweep (f32)

      *> struct Dimensions: The 2D size of something (width/height.)
      *>   offset 0: width (i32)
      *>   offset 4: height (i32)

      *> struct Vector: The 2D position of something (x/y.)
      *>   offset 0: x (i32)
      *>   offset 4: y (i32)

      *> struct Rectangle: The 2D position + size of something (x/y/w/h.)
      *>   offset 0: x (i32)
      *>   offset 4: y (i32)
      *>   offset 8: width (i32)
      *>   offset 12: height (i32)

      *> struct Color: An RGBA color.
      *>   offset 0: r (u8)
      *>   offset 1: g (u8)
      *>   offset 2: b (u8)
      *>   offset 3: a (u8)


      *> -- COLORS --
      *> Tint a color with another color.
      *>   CALL "color_tint" USING BY VALUE C-O-L-O-R T-I-N-T RETURNING RESULT
      *> Fade a color.
      *>   CALL "color_fade" USING BY VALUE C-O-L-O-R A-L-P-H-A RETURNING RESULT
      *> Change the brightness of a color.
      *>   CALL "color_brightness" USING BY VALUE C-O-L-O-R F-A-C-T-O-R RETURNING RESULT
      *> Invert a color.
      *>   CALL "color_invert" USING BY VALUE C-O-L-O-R RETURNING RESULT
      *> Blend 2 colors together.
      *>   CALL "color_alpha_blend" USING BY VALUE D-S-T S-R-C RETURNING RESULT
      *> Change contrast of a color.
      *>   CALL "color_contrast" USING BY VALUE C-O-L-O-R C-O-N-T-R-A-S-T RETURNING RESULT
      *> Interpolate colors.
      *>   CALL "color_bilinear_interpolate" USING BY VALUE C-O-L-O-R00 C-O-L-O-R01 C-O-L-O-R10 C-O-L-O-R11 C-O-O-R-D-I-N-A-T-E-X C-O-O-R-D-I-N-A-T-E-Y RETURNING RESULT

      *> -- GRAPHICS --
      *> Create a new blank image.
      *>   CALL "new_image" USING BY VALUE W-I-D-T-H H-E-I-G-H-T C-O-L-O-R RETURNING RESULT
      *> Copy an image to a new image.
      *>   CALL "image_copy" USING BY VALUE I-M-A-G-E RETURNING RESULT
      *> Create an image from a region of another image.
      *>   CALL "image_subimage" USING BY VALUE I-M-A-G-E X Y W-I-D-T-H H-E-I-G-H-T RETURNING RESULT
      *> Clear the screen.
      *>   CALL "clear" USING BY VALUE C-O-L-O-R
      *> Draw a single pixel on the screen.
      *>   CALL "draw_point" USING BY VALUE X Y C-O-L-O-R
      *> Draw a line on the screen.
      *>   CALL "draw_line" USING BY VALUE S-T-A-R-T-P-O-S-X S-T-A-R-T-P-O-S-Y E-N-D-P-O-S-X E-N-D-P-O-S-Y C-O-L-O-R
      *> Draw a filled rectangle on the screen.
      *>   CALL "draw_rectangle" USING BY VALUE P-O-S-X P-O-S-Y W-I-D-T-H H-E-I-G-H-T C-O-L-O-R
      *> Draw a filled triangle on the screen.
      *>   CALL "draw_triangle" USING BY VALUE X1 Y1 X2 Y2 X3 Y3 C-O-L-O-R
      *> Draw a filled ellipse on the screen.
      *>   CALL "draw_ellipse" USING BY VALUE C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S-X R-A-D-I-U-S-Y C-O-L-O-R
      *> Draw a filled circle on the screen.
      *>   CALL "draw_circle" USING BY VALUE C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S C-O-L-O-R
      *> Draw a filled polygon on the screen.
      *>   CALL "draw_polygon" USING BY VALUE P-O-I-N-T-S N-U-M-P-O-I-N-T-S C-O-L-O-R
      *> Draw a filled arc on the screen.
      *>   CALL "draw_arc" USING BY VALUE C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S S-T-A-R-T-A-N-G-L-E E-N-D-A-N-G-L-E S-E-G-M-E-N-T-S C-O-L-O-R
      *> Draw a filled round-rectangle on the screen.
      *>   CALL "draw_rectangle_rounded" USING BY VALUE X Y W-I-D-T-H H-E-I-G-H-T C-O-R-N-E-R-R-A-D-I-U-S C-O-L-O-R
      *> Draw an image on the screen.
      *>   CALL "draw_image" USING BY VALUE S-R-C P-O-S-X P-O-S-Y
      *> Draw a tinted image on the screen.
      *>   CALL "draw_image_tint" USING BY VALUE S-R-C P-O-S-X P-O-S-Y T-I-N-T
      *> Draw an image, rotated, on the screen.
      *>   CALL "draw_image_rotated" USING BY VALUE S-R-C P-O-S-X P-O-S-Y D-E-G-R-E-E-S O-F-F-S-E-T-X O-F-F-S-E-T-Y F-I-L-T-E-R
      *> Draw an image, flipped, on the screen.
      *>   CALL "draw_image_flipped" USING BY VALUE S-R-C P-O-S-X P-O-S-Y F-L-I-P-H-O-R-I-Z-O-N-T-A-L F-L-I-P-V-E-R-T-I-C-A-L F-L-I-P-D-I-A-G-O-N-A-L
      *> Draw an image, scaled, on the screen.
      *>   CALL "draw_image_scaled" USING BY VALUE S-R-C P-O-S-X P-O-S-Y S-C-A-L-E-X S-C-A-L-E-Y O-F-F-S-E-T-X O-F-F-S-E-T-Y F-I-L-T-E-R
      *> Draw some text on the screen.
      *>   CALL "draw_text" USING BY VALUE F-O-N-T T-E-X-T P-O-S-X P-O-S-Y C-O-L-O-R
      *> Save an image to persistant storage.
      *>   CALL "save_image" USING BY VALUE I-M-A-G-E F-I-L-E-N-A-M-E
      *> Load an image from a file in cart.
      *>   CALL "load_image" USING BY VALUE F-I-L-E-N-A-M-E RETURNING RESULT
      *> Resize an image, return copy.
      *>   CALL "image_resize" USING BY VALUE I-M-A-G-E N-E-W-W-I-D-T-H N-E-W-H-E-I-G-H-T F-I-L-T-E-R RETURNING RESULT
      *> Scale an image, return copy.
      *>   CALL "image_scale" USING BY VALUE I-M-A-G-E S-C-A-L-E-X S-C-A-L-E-Y F-I-L-T-E-R RETURNING RESULT
      *> Replace a color in an image, in-place.
      *>   CALL "image_color_replace" USING BY VALUE I-M-A-G-E C-O-L-O-R R-E-P-L-A-C-E
      *> Tint a color in an image, in-place.
      *>   CALL "image_color_tint" USING BY VALUE I-M-A-G-E C-O-L-O-R
      *> Fade a color in an image, in-place.
      *>   CALL "image_color_fade" USING BY VALUE I-M-A-G-E A-L-P-H-A
      *> Copy a font to a new font.
      *>   CALL "font_copy" USING BY VALUE F-O-N-T RETURNING RESULT
      *> Scale a font, return a new font.
      *>   CALL "font_scale" USING BY VALUE F-O-N-T S-C-A-L-E-X S-C-A-L-E-Y F-I-L-T-E-R RETURNING RESULT
      *> Load a BMF font from a file in cart.
      *>   CALL "load_font_bmf" USING BY VALUE F-I-L-E-N-A-M-E C-H-A-R-A-C-T-E-R-S RETURNING RESULT
      *> Load a BMF font from an image.
      *>   CALL "load_font_bmf_from_image" USING BY VALUE I-M-A-G-E C-H-A-R-A-C-T-E-R-S RETURNING RESULT
      *> Measure the size of some text.
      *>   CALL "measure_text" USING BY VALUE F-O-N-T T-E-X-T T-E-X-T-L-E-N-G-T-H RETURNING RESULT
      *> Meaure an image (use 0 for screen).
      *>   CALL "measure_image" USING BY VALUE I-M-A-G-E RETURNING RESULT
      *> Load a TTY font from a file in cart.
      *>   CALL "load_font_tty" USING BY VALUE F-I-L-E-N-A-M-E G-L-Y-P-H-W-I-D-T-H G-L-Y-P-H-H-E-I-G-H-T C-H-A-R-A-C-T-E-R-S RETURNING RESULT
      *> Load a TTY font from an image.
      *>   CALL "load_font_tty_from_image" USING BY VALUE I-M-A-G-E G-L-Y-P-H-W-I-D-T-H G-L-Y-P-H-H-E-I-G-H-T C-H-A-R-A-C-T-E-R-S RETURNING RESULT
      *> Load a TTF font from a file in cart.
      *>   CALL "load_font_ttf" USING BY VALUE F-I-L-E-N-A-M-E F-O-N-T-S-I-Z-E RETURNING RESULT
      *> Invert the colors in an image, in-place.
      *>   CALL "image_color_invert" USING BY VALUE I-M-A-G-E
      *> Calculate a rectangle representing the available alpha border in an image.
      *>   CALL "image_alpha_border" USING BY VALUE I-M-A-G-E T-H-R-E-S-H-O-L-D RETURNING RESULT
      *> Crop an image, in-place.
      *>   CALL "image_crop" USING BY VALUE I-M-A-G-E X Y W-I-D-T-H H-E-I-G-H-T
      *> Crop an image based on the alpha border, in-place.
      *>   CALL "image_alpha_crop" USING BY VALUE I-M-A-G-E T-H-R-E-S-H-O-L-D
      *> Adjust the brightness of an image, in-place.
      *>   CALL "image_color_brightness" USING BY VALUE I-M-A-G-E F-A-C-T-O-R
      *> Flip an image, in-place.
      *>   CALL "image_flip" USING BY VALUE I-M-A-G-E H-O-R-I-Z-O-N-T-A-L V-E-R-T-I-C-A-L
      *> Change the contrast of an image, in-place.
      *>   CALL "image_color_contrast" USING BY VALUE I-M-A-G-E C-O-N-T-R-A-S-T
      *> Use an image as an alpha-mask on another image.
      *>   CALL "image_alpha_mask" USING BY VALUE I-M-A-G-E A-L-P-H-A-M-A-S-K P-O-S-X P-O-S-Y
      *> Create a new image, rotating another image.
      *>   CALL "image_rotate" USING BY VALUE I-M-A-G-E D-E-G-R-E-E-S F-I-L-T-E-R RETURNING RESULT
      *> Create a new image of a gradient.
      *>   CALL "image_gradient" USING BY VALUE W-I-D-T-H H-E-I-G-H-T T-O-P-L-E-F-T T-O-P-R-I-G-H-T B-O-T-T-O-M-L-E-F-T B-O-T-T-O-M-R-I-G-H-T RETURNING RESULT
      *> Unload an image.
      *>   CALL "unload_image" USING BY VALUE I-M-A-G-E
      *> Unload a font.
      *>   CALL "unload_font" USING BY VALUE F-O-N-T
      *> Clear an image.
      *>   CALL "clear_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N C-O-L-O-R
      *> Draw a single pixel on an image.
      *>   CALL "draw_point_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N X Y C-O-L-O-R
      *> Draw a line on an image.
      *>   CALL "draw_line_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N S-T-A-R-T-P-O-S-X S-T-A-R-T-P-O-S-Y E-N-D-P-O-S-X E-N-D-P-O-S-Y C-O-L-O-R
      *> Draw a filled rectangle on an image.
      *>   CALL "draw_rectangle_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N P-O-S-X P-O-S-Y W-I-D-T-H H-E-I-G-H-T C-O-L-O-R
      *> Draw a filled triangle on an image.
      *>   CALL "draw_triangle_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N X1 Y1 X2 Y2 X3 Y3 C-O-L-O-R
      *> Draw a filled ellipse on an image.
      *>   CALL "draw_ellipse_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S-X R-A-D-I-U-S-Y C-O-L-O-R
      *> Draw a circle on an image.
      *>   CALL "draw_circle_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S C-O-L-O-R
      *> Draw a filled polygon on an image.
      *>   CALL "draw_polygon_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N P-O-I-N-T-S N-U-M-P-O-I-N-T-S C-O-L-O-R
      *> Draw a filled round-rectangle on an image.
      *>   CALL "draw_rectangle_rounded_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N X Y W-I-D-T-H H-E-I-G-H-T C-O-R-N-E-R-R-A-D-I-U-S C-O-L-O-R
      *> Draw an image on an image.
      *>   CALL "draw_image_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N S-R-C P-O-S-X P-O-S-Y
      *> Draw a tinted image on an image.
      *>   CALL "draw_image_tint_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N S-R-C P-O-S-X P-O-S-Y T-I-N-T
      *> Draw an image, rotated, on an image.
      *>   CALL "draw_image_rotated_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N S-R-C P-O-S-X P-O-S-Y D-E-G-R-E-E-S O-F-F-S-E-T-X O-F-F-S-E-T-Y F-I-L-T-E-R
      *> Draw an image, flipped, on an image.
      *>   CALL "draw_image_flipped_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N S-R-C P-O-S-X P-O-S-Y F-L-I-P-H-O-R-I-Z-O-N-T-A-L F-L-I-P-V-E-R-T-I-C-A-L F-L-I-P-D-I-A-G-O-N-A-L
      *> Draw an image, scaled, on an image.
      *>   CALL "draw_image_scaled_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N S-R-C P-O-S-X P-O-S-Y S-C-A-L-E-X S-C-A-L-E-Y O-F-F-S-E-T-X O-F-F-S-E-T-Y F-I-L-T-E-R
      *> Draw some text on an image.
      *>   CALL "draw_text_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N F-O-N-T T-E-X-T P-O-S-X P-O-S-Y C-O-L-O-R
      *> Draw a outlined (with thickness) rectangle on the screen.
      *>   CALL "draw_rectangle_outline" USING BY VALUE P-O-S-X P-O-S-Y W-I-D-T-H H-E-I-G-H-T T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) triangle on the screen.
      *>   CALL "draw_triangle_outline" USING BY VALUE X1 Y1 X2 Y2 X3 Y3 T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) ellipse on the screen.
      *>   CALL "draw_ellipse_outline" USING BY VALUE C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S-X R-A-D-I-U-S-Y T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) circle on the screen.
      *>   CALL "draw_circle_outline" USING BY VALUE C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) polygon on the screen.
      *>   CALL "draw_polygon_outline" USING BY VALUE P-O-I-N-T-S N-U-M-P-O-I-N-T-S T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) arc on the screen.
      *>   CALL "draw_arc_outline" USING BY VALUE C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S S-T-A-R-T-A-N-G-L-E E-N-D-A-N-G-L-E S-E-G-M-E-N-T-S T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) round-rectangle on the screen.
      *>   CALL "draw_rectangle_rounded_outline" USING BY VALUE X Y W-I-D-T-H H-E-I-G-H-T C-O-R-N-E-R-R-A-D-I-U-S T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) rectangle on an image.
      *>   CALL "draw_rectangle_outline_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N P-O-S-X P-O-S-Y W-I-D-T-H H-E-I-G-H-T T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) triangle on an image.
      *>   CALL "draw_triangle_outline_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N X1 Y1 X2 Y2 X3 Y3 T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) ellipse on an image.
      *>   CALL "draw_ellipse_outline_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S-X R-A-D-I-U-S-Y T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) circle on an image.
      *>   CALL "draw_circle_outline_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N C-E-N-T-E-R-X C-E-N-T-E-R-Y R-A-D-I-U-S T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) polygon on an image.
      *>   CALL "draw_polygon_outline_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N P-O-I-N-T-S N-U-M-P-O-I-N-T-S T-H-I-C-K-N-E-S-S C-O-L-O-R
      *> Draw a outlined (with thickness) round-rectangle on an image.
      *>   CALL "draw_rectangle_rounded_outline_on_image" USING BY VALUE D-E-S-T-I-N-A-T-I-O-N X Y W-I-D-T-H H-E-I-G-H-T C-O-R-N-E-R-R-A-D-I-U-S T-H-I-C-K-N-E-S-S C-O-L-O-R

      *> -- INPUT --
      *> Has the key been pressed? (tracks unpress/read correctly.)
      *>   CALL "key_pressed" USING BY VALUE K-E-Y RETURNING RESULT
      *> Is the key currently down?
      *>   CALL "key_down" USING BY VALUE K-E-Y RETURNING RESULT
      *> Has the key been released? (tracks press/read correctly.)
      *>   CALL "key_released" USING BY VALUE K-E-Y RETURNING RESULT
      *> Is the key currently up?
      *>   CALL "key_up" USING BY VALUE K-E-Y RETURNING RESULT
      *> Has the button been pressed? (tracks unpress/read correctly.)
      *>   CALL "gamepad_button_pressed" USING BY VALUE G-A-M-E-P-A-D B-U-T-T-O-N RETURNING RESULT
      *> Is the button currently down?
      *>   CALL "gamepad_button_down" USING BY VALUE G-A-M-E-P-A-D B-U-T-T-O-N RETURNING RESULT
      *> Has the button been released? (tracks press/read correctly.)
      *>   CALL "gamepad_button_released" USING BY VALUE G-A-M-E-P-A-D B-U-T-T-O-N RETURNING RESULT
      *> Get current position of mouse.
      *>   CALL "mouse_position" RETURNING RESULT
      *> Has the button been pressed? (tracks unpress/read correctly.)
      *>   CALL "mouse_button_pressed" USING BY VALUE B-U-T-T-O-N RETURNING RESULT
      *> Is the button currently down?
      *>   CALL "mouse_button_down" USING BY VALUE B-U-T-T-O-N RETURNING RESULT
      *> Has the button been released? (tracks press/read correctly.)
      *>   CALL "mouse_button_released" USING BY VALUE B-U-T-T-O-N RETURNING RESULT
      *> Is the button currently up?
      *>   CALL "mouse_button_up" USING BY VALUE B-U-T-T-O-N RETURNING RESULT

      *> -- SOUND --
      *> Load a sound from a file in cart.
      *>   CALL "load_sound" USING BY VALUE F-I-L-E-N-A-M-E RETURNING RESULT
      *> Play a sound.
      *>   CALL "play_sound" USING BY VALUE S-O-U-N-D L-O-O-P
      *> Stop a sound.
      *>   CALL "stop_sound" USING BY VALUE S-O-U-N-D
      *> Unload a sound.
      *>   CALL "unload_sound" USING BY VALUE S-O-U-N-D
      *> Speak some text and return a sound. Set things to 0 for defaults.
      *>   CALL "tts_sound" USING BY VALUE T-E-X-T P-H-O-N-E-T-I-C P-I-T-C-H S-P-E-E-D T-H-R-O-A-T M-O-U-T-H S-I-N-G RETURNING RESULT
      *> Create Sfx sound.
      *>   CALL "sfx_sound" USING BY VALUE P-A-R-A-M-S RETURNING RESULT
      *> Create Sfx parameters.
      *>   CALL "sfx_generate" USING BY VALUE T-Y-P-E RETURNING RESULT

      *> -- TYPES --

      *> -- UTILITIES --
      *> Get system-time (ms) since unix epoch.
      *>   CALL "current_time" RETURNING RESULT
      *> Get the change in time (seconds) since the last update run.
      *>   CALL "delta_time" RETURNING RESULT
      *> Get a random integer between 2 numbers.
      *>   CALL "random_int" USING BY VALUE M-I-N M-A-X RETURNING RESULT
      *> Get the random-seed.
      *>   CALL "random_seed_get" RETURNING RESULT
      *> Set the random-seed.
      *>   CALL "random_seed_set" USING BY VALUE S-E-E-D
