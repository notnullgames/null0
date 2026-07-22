;; null0 - WAT bindings for the null0 fantasy console
;;
;; WAT has no include-system, so copy the imports you need from this file
;; into your own (module ...) and call them like:
;;
;;   (module
;;     (import "null0" "clear" (func $clear (param i32)))
;;     (func (export "load")
;;       (call $clear (i32.const 0xfff17900)))) ;; BLUE
;;
;; ABI notes:
;; - all handles (Image/Font/Sound), enums, bools and pointers are i32
;; - string is a pointer to a null-terminated UTF8 string in memory (i32)
;; - Color is 4 bytes packed into a single i32: r | g<<8 | b<<16 | a<<24
;; - functions returning structs (Vector/Dimensions/Rectangle/Color/SfxParams)
;;   return a pointer (i32) into your memory, read the fields with i32.load

;; -- constants --

(global $SCREEN i32 (i32.const 0))
(global $SCREEN_WIDTH i32 (i32.const 640))
(global $SCREEN_HEIGHT i32 (i32.const 480))
(global $FONT_DEFAULT i32 (i32.const 0))

;; colors (i32 constants)
(global $lightgray i32 (i32.const 0xffc8c8c8)) ;; LIGHTGRAY = rgba(200, 200, 200, 255)
(global $gray i32 (i32.const 0xff828282)) ;; GRAY = rgba(130, 130, 130, 255)
(global $darkgray i32 (i32.const 0xff505050)) ;; DARKGRAY = rgba(80, 80, 80, 255)
(global $yellow i32 (i32.const 0xff00f9fd)) ;; YELLOW = rgba(253, 249, 0, 255)
(global $gold i32 (i32.const 0xff00cbff)) ;; GOLD = rgba(255, 203, 0, 255)
(global $orange i32 (i32.const 0xff00a1ff)) ;; ORANGE = rgba(255, 161, 0, 255)
(global $pink i32 (i32.const 0xffc26dff)) ;; PINK = rgba(255, 109, 194, 255)
(global $red i32 (i32.const 0xff3729e6)) ;; RED = rgba(230, 41, 55, 255)
(global $maroon i32 (i32.const 0xff3721be)) ;; MAROON = rgba(190, 33, 55, 255)
(global $green i32 (i32.const 0xff30e400)) ;; GREEN = rgba(0, 228, 48, 255)
(global $lime i32 (i32.const 0xff2f9e00)) ;; LIME = rgba(0, 158, 47, 255)
(global $darkgreen i32 (i32.const 0xff2c7500)) ;; DARKGREEN = rgba(0, 117, 44, 255)
(global $skyblue i32 (i32.const 0xffffbf66)) ;; SKYBLUE = rgba(102, 191, 255, 255)
(global $blue i32 (i32.const 0xfff17900)) ;; BLUE = rgba(0, 121, 241, 255)
(global $darkblue i32 (i32.const 0xffac5200)) ;; DARKBLUE = rgba(0, 82, 172, 255)
(global $purple i32 (i32.const 0xffff7ac8)) ;; PURPLE = rgba(200, 122, 255, 255)
(global $violet i32 (i32.const 0xffbe3c87)) ;; VIOLET = rgba(135, 60, 190, 255)
(global $darkpurple i32 (i32.const 0xff7e1f70)) ;; DARKPURPLE = rgba(112, 31, 126, 255)
(global $beige i32 (i32.const 0xff83b0d3)) ;; BEIGE = rgba(211, 176, 131, 255)
(global $brown i32 (i32.const 0xff4f6a7f)) ;; BROWN = rgba(127, 106, 79, 255)
(global $darkbrown i32 (i32.const 0xff2f3f4c)) ;; DARKBROWN = rgba(76, 63, 47, 255)
(global $white i32 (i32.const 0xffffffff)) ;; WHITE = rgba(255, 255, 255, 255)
(global $black i32 (i32.const 0xff000000)) ;; BLACK = rgba(0, 0, 0, 255)
(global $blank i32 (i32.const 0x00000000)) ;; BLANK = rgba(0, 0, 0, 0)
(global $magenta i32 (i32.const 0xffff00ff)) ;; MAGENTA = rgba(255, 0, 255, 255)
(global $raywhite i32 (i32.const 0xfff5f5f5)) ;; RAYWHITE = rgba(245, 245, 245, 255)


;; ImageFilter: Potential image-filtering techniques for scale/etc.
(global $filter_nearestneighbor i32 (i32.const 0))
(global $filter_bilinear i32 (i32.const 1))
(global $filter_smooth i32 (i32.const 2))

;; SfxPresetType: Represents a Sfx preset type.
(global $sfx_coin i32 (i32.const 0))
(global $sfx_laser i32 (i32.const 1))
(global $sfx_explosion i32 (i32.const 2))
(global $sfx_powerup i32 (i32.const 3))
(global $sfx_hurt i32 (i32.const 4))
(global $sfx_jump i32 (i32.const 5))
(global $sfx_select i32 (i32.const 6))
(global $sfx_synth i32 (i32.const 7))

;; Key: Represents a keyboard key.
(global $key_invalid i32 (i32.const 0))
(global $key_space i32 (i32.const 32))
(global $key_apostrophe i32 (i32.const 39))
(global $key_comma i32 (i32.const 44))
(global $key_minus i32 (i32.const 45))
(global $key_period i32 (i32.const 46))
(global $key_slash i32 (i32.const 47))
(global $key_0 i32 (i32.const 48))
(global $key_1 i32 (i32.const 49))
(global $key_2 i32 (i32.const 50))
(global $key_3 i32 (i32.const 51))
(global $key_4 i32 (i32.const 52))
(global $key_5 i32 (i32.const 53))
(global $key_6 i32 (i32.const 54))
(global $key_7 i32 (i32.const 55))
(global $key_8 i32 (i32.const 56))
(global $key_9 i32 (i32.const 57))
(global $key_semicolon i32 (i32.const 59))
(global $key_equal i32 (i32.const 61))
(global $key_a i32 (i32.const 65))
(global $key_b i32 (i32.const 66))
(global $key_c i32 (i32.const 67))
(global $key_d i32 (i32.const 68))
(global $key_e i32 (i32.const 69))
(global $key_f i32 (i32.const 70))
(global $key_g i32 (i32.const 71))
(global $key_h i32 (i32.const 72))
(global $key_i i32 (i32.const 73))
(global $key_j i32 (i32.const 74))
(global $key_k i32 (i32.const 75))
(global $key_l i32 (i32.const 76))
(global $key_m i32 (i32.const 77))
(global $key_n i32 (i32.const 78))
(global $key_o i32 (i32.const 79))
(global $key_p i32 (i32.const 80))
(global $key_q i32 (i32.const 81))
(global $key_r i32 (i32.const 82))
(global $key_s i32 (i32.const 83))
(global $key_t i32 (i32.const 84))
(global $key_u i32 (i32.const 85))
(global $key_v i32 (i32.const 86))
(global $key_w i32 (i32.const 87))
(global $key_x i32 (i32.const 88))
(global $key_y i32 (i32.const 89))
(global $key_z i32 (i32.const 90))
(global $key_left_bracket i32 (i32.const 91))
(global $key_backslash i32 (i32.const 92))
(global $key_right_bracket i32 (i32.const 93))
(global $key_grave_accent i32 (i32.const 96))
(global $key_world_1 i32 (i32.const 161))
(global $key_world_2 i32 (i32.const 162))
(global $key_escape i32 (i32.const 256))
(global $key_enter i32 (i32.const 257))
(global $key_tab i32 (i32.const 258))
(global $key_backspace i32 (i32.const 259))
(global $key_insert i32 (i32.const 260))
(global $key_delete i32 (i32.const 261))
(global $key_right i32 (i32.const 262))
(global $key_left i32 (i32.const 263))
(global $key_down i32 (i32.const 264))
(global $key_up i32 (i32.const 265))
(global $key_page_up i32 (i32.const 266))
(global $key_page_down i32 (i32.const 267))
(global $key_home i32 (i32.const 268))
(global $key_end i32 (i32.const 269))
(global $key_caps_lock i32 (i32.const 280))
(global $key_scroll_lock i32 (i32.const 281))
(global $key_num_lock i32 (i32.const 282))
(global $key_print_screen i32 (i32.const 283))
(global $key_pause i32 (i32.const 284))
(global $key_f1 i32 (i32.const 290))
(global $key_f2 i32 (i32.const 291))
(global $key_f3 i32 (i32.const 292))
(global $key_f4 i32 (i32.const 293))
(global $key_f5 i32 (i32.const 294))
(global $key_f6 i32 (i32.const 295))
(global $key_f7 i32 (i32.const 296))
(global $key_f8 i32 (i32.const 297))
(global $key_f9 i32 (i32.const 298))
(global $key_f10 i32 (i32.const 299))
(global $key_f11 i32 (i32.const 300))
(global $key_f12 i32 (i32.const 301))
(global $key_f13 i32 (i32.const 302))
(global $key_f14 i32 (i32.const 303))
(global $key_f15 i32 (i32.const 304))
(global $key_f16 i32 (i32.const 305))
(global $key_f17 i32 (i32.const 306))
(global $key_f18 i32 (i32.const 307))
(global $key_f19 i32 (i32.const 308))
(global $key_f20 i32 (i32.const 309))
(global $key_f21 i32 (i32.const 310))
(global $key_f22 i32 (i32.const 311))
(global $key_f23 i32 (i32.const 312))
(global $key_f24 i32 (i32.const 313))
(global $key_f25 i32 (i32.const 314))
(global $key_kp_0 i32 (i32.const 320))
(global $key_kp_1 i32 (i32.const 321))
(global $key_kp_2 i32 (i32.const 322))
(global $key_kp_3 i32 (i32.const 323))
(global $key_kp_4 i32 (i32.const 324))
(global $key_kp_5 i32 (i32.const 325))
(global $key_kp_6 i32 (i32.const 326))
(global $key_kp_7 i32 (i32.const 327))
(global $key_kp_8 i32 (i32.const 328))
(global $key_kp_9 i32 (i32.const 329))
(global $key_kp_decimal i32 (i32.const 330))
(global $key_kp_divide i32 (i32.const 331))
(global $key_kp_multiply i32 (i32.const 332))
(global $key_kp_subtract i32 (i32.const 333))
(global $key_kp_add i32 (i32.const 334))
(global $key_kp_enter i32 (i32.const 335))
(global $key_kp_equal i32 (i32.const 336))
(global $key_left_shift i32 (i32.const 340))
(global $key_left_control i32 (i32.const 341))
(global $key_left_alt i32 (i32.const 342))
(global $key_left_super i32 (i32.const 343))
(global $key_right_shift i32 (i32.const 344))
(global $key_right_control i32 (i32.const 345))
(global $key_right_alt i32 (i32.const 346))
(global $key_right_super i32 (i32.const 347))
(global $key_menu i32 (i32.const 348))

;; GamepadButton: Represents a gamepad button.
(global $gamepad_button_unknown i32 (i32.const 0))
(global $gamepad_button_up i32 (i32.const 1))
(global $gamepad_button_right i32 (i32.const 2))
(global $gamepad_button_down i32 (i32.const 3))
(global $gamepad_button_left i32 (i32.const 4))
(global $gamepad_button_y i32 (i32.const 5))
(global $gamepad_button_b i32 (i32.const 6))
(global $gamepad_button_a i32 (i32.const 7))
(global $gamepad_button_x i32 (i32.const 8))
(global $gamepad_button_left_shoulder i32 (i32.const 9))
(global $gamepad_button_left_trigger i32 (i32.const 10))
(global $gamepad_button_right_shoulder i32 (i32.const 11))
(global $gamepad_button_right_trigger i32 (i32.const 12))
(global $gamepad_button_select i32 (i32.const 13))
(global $gamepad_button_menu i32 (i32.const 14))
(global $gamepad_button_start i32 (i32.const 15))
(global $gamepad_button_left_thumb i32 (i32.const 16))
(global $gamepad_button_right_thumb i32 (i32.const 17))

;; MouseButton: Represents a mouse button.
(global $mouse_button_unknown i32 (i32.const 0))
(global $mouse_button_left i32 (i32.const 1))
(global $mouse_button_right i32 (i32.const 2))
(global $mouse_button_middle i32 (i32.const 3))


;; struct SfxParams: Sfx parameters.
;;   offset 0: randSeed (u32, read with i32.load)
;;   offset 4: waveType (i32, read with i32.load)
;;   offset 8: attackTime (f32, read with f32.load)
;;   offset 12: sustainTime (f32, read with f32.load)
;;   offset 16: sustainPunch (f32, read with f32.load)
;;   offset 20: decayTime (f32, read with f32.load)
;;   offset 24: startFrequency (f32, read with f32.load)
;;   offset 28: minFrequency (f32, read with f32.load)
;;   offset 32: slide (f32, read with f32.load)
;;   offset 36: deltaSlide (f32, read with f32.load)
;;   offset 40: vibratoDepth (f32, read with f32.load)
;;   offset 44: vibratoSpeed (f32, read with f32.load)
;;   offset 48: changeAmount (f32, read with f32.load)
;;   offset 52: changeSpeed (f32, read with f32.load)
;;   offset 56: squareDuty (f32, read with f32.load)
;;   offset 60: dutySweep (f32, read with f32.load)
;;   offset 64: repeatSpeed (f32, read with f32.load)
;;   offset 68: phaserOffset (f32, read with f32.load)
;;   offset 72: phaserSweep (f32, read with f32.load)
;;   offset 76: lpfCutoff (f32, read with f32.load)
;;   offset 80: lpfCutoffSweep (f32, read with f32.load)
;;   offset 84: lpfResonance (f32, read with f32.load)
;;   offset 88: hpfCutoff (f32, read with f32.load)
;;   offset 92: hpfCutoffSweep (f32, read with f32.load)

;; struct Dimensions: The 2D size of something (width/height.)
;;   offset 0: width (i32, read with i32.load)
;;   offset 4: height (i32, read with i32.load)

;; struct Vector: The 2D position of something (x/y.)
;;   offset 0: x (i32, read with i32.load)
;;   offset 4: y (i32, read with i32.load)

;; struct Rectangle: The 2D position + size of something (x/y/w/h.)
;;   offset 0: x (i32, read with i32.load)
;;   offset 4: y (i32, read with i32.load)
;;   offset 8: width (i32, read with i32.load)
;;   offset 12: height (i32, read with i32.load)

;; struct Color: An RGBA color.
;;   offset 0: r (u8, read with i32.load8_u)
;;   offset 1: g (u8, read with i32.load8_u)
;;   offset 2: b (u8, read with i32.load8_u)
;;   offset 3: a (u8, read with i32.load8_u)


;; -- COLORS --

;; Tint a color with another color.
(import "null0" "color_tint" (func $color_tint (param i32 i32) (result i32)))
;; Fade a color.
(import "null0" "color_fade" (func $color_fade (param i32 f32) (result i32)))
;; Change the brightness of a color.
(import "null0" "color_brightness" (func $color_brightness (param i32 f32) (result i32)))
;; Invert a color.
(import "null0" "color_invert" (func $color_invert (param i32) (result i32)))
;; Blend 2 colors together.
(import "null0" "color_alpha_blend" (func $color_alpha_blend (param i32 i32) (result i32)))
;; Change contrast of a color.
(import "null0" "color_contrast" (func $color_contrast (param i32 f32) (result i32)))
;; Interpolate colors.
(import "null0" "color_bilinear_interpolate" (func $color_bilinear_interpolate (param i32 i32 i32 i32 f32 f32) (result i32)))

;; -- GRAPHICS --

;; Create a new blank image.
(import "null0" "new_image" (func $new_image (param i32 i32 i32) (result i32)))
;; Copy an image to a new image.
(import "null0" "image_copy" (func $image_copy (param i32) (result i32)))
;; Create an image from a region of another image.
(import "null0" "image_subimage" (func $image_subimage (param i32 i32 i32 i32 i32) (result i32)))
;; Clear the screen.
(import "null0" "clear" (func $clear (param i32)))
;; Draw a single pixel on the screen.
(import "null0" "draw_point" (func $draw_point (param i32 i32 i32)))
;; Draw a line on the screen.
(import "null0" "draw_line" (func $draw_line (param i32 i32 i32 i32 i32)))
;; Draw a filled rectangle on the screen.
(import "null0" "draw_rectangle" (func $draw_rectangle (param i32 i32 i32 i32 i32)))
;; Draw a filled triangle on the screen.
(import "null0" "draw_triangle" (func $draw_triangle (param i32 i32 i32 i32 i32 i32 i32)))
;; Draw a filled ellipse on the screen.
(import "null0" "draw_ellipse" (func $draw_ellipse (param i32 i32 i32 i32 i32)))
;; Draw a filled circle on the screen.
(import "null0" "draw_circle" (func $draw_circle (param i32 i32 i32 i32)))
;; Draw a filled polygon on the screen.
(import "null0" "draw_polygon" (func $draw_polygon (param i32 i32 i32)))
;; Draw a filled arc on the screen.
(import "null0" "draw_arc" (func $draw_arc (param i32 i32 f32 f32 f32 i32 i32)))
;; Draw a filled round-rectangle on the screen.
(import "null0" "draw_rectangle_rounded" (func $draw_rectangle_rounded (param i32 i32 i32 i32 i32 i32)))
;; Draw an image on the screen.
(import "null0" "draw_image" (func $draw_image (param i32 i32 i32)))
;; Draw a tinted image on the screen.
(import "null0" "draw_image_tint" (func $draw_image_tint (param i32 i32 i32 i32)))
;; Draw an image, rotated, on the screen.
(import "null0" "draw_image_rotated" (func $draw_image_rotated (param i32 i32 i32 f32 f32 f32 i32)))
;; Draw an image, flipped, on the screen.
(import "null0" "draw_image_flipped" (func $draw_image_flipped (param i32 i32 i32 i32 i32 i32)))
;; Draw an image, scaled, on the screen.
(import "null0" "draw_image_scaled" (func $draw_image_scaled (param i32 i32 i32 f32 f32 f32 f32 i32)))
;; Draw some text on the screen.
(import "null0" "draw_text" (func $draw_text (param i32 i32 i32 i32 i32)))
;; Save an image to persistant storage.
(import "null0" "save_image" (func $save_image (param i32 i32)))
;; Load an image from a file in cart.
(import "null0" "load_image" (func $load_image (param i32) (result i32)))
;; Resize an image, return copy.
(import "null0" "image_resize" (func $image_resize (param i32 i32 i32 i32) (result i32)))
;; Scale an image, return copy.
(import "null0" "image_scale" (func $image_scale (param i32 f32 f32 i32) (result i32)))
;; Replace a color in an image, in-place.
(import "null0" "image_color_replace" (func $image_color_replace (param i32 i32 i32)))
;; Tint a color in an image, in-place.
(import "null0" "image_color_tint" (func $image_color_tint (param i32 i32)))
;; Fade a color in an image, in-place.
(import "null0" "image_color_fade" (func $image_color_fade (param i32 f32)))
;; Copy a font to a new font.
(import "null0" "font_copy" (func $font_copy (param i32) (result i32)))
;; Scale a font, return a new font.
(import "null0" "font_scale" (func $font_scale (param i32 f32 f32 i32) (result i32)))
;; Load a BMF font from a file in cart.
(import "null0" "load_font_bmf" (func $load_font_bmf (param i32 i32) (result i32)))
;; Load a BMF font from an image.
(import "null0" "load_font_bmf_from_image" (func $load_font_bmf_from_image (param i32 i32) (result i32)))
;; Measure the size of some text.
(import "null0" "measure_text" (func $measure_text (param i32 i32 i32) (result i32)))
;; Meaure an image (use 0 for screen).
(import "null0" "measure_image" (func $measure_image (param i32) (result i32)))
;; Load a TTY font from a file in cart.
(import "null0" "load_font_tty" (func $load_font_tty (param i32 i32 i32 i32) (result i32)))
;; Load a TTY font from an image.
(import "null0" "load_font_tty_from_image" (func $load_font_tty_from_image (param i32 i32 i32 i32) (result i32)))
;; Load a TTF font from a file in cart.
(import "null0" "load_font_ttf" (func $load_font_ttf (param i32 i32) (result i32)))
;; Invert the colors in an image, in-place.
(import "null0" "image_color_invert" (func $image_color_invert (param i32)))
;; Calculate a rectangle representing the available alpha border in an image.
(import "null0" "image_alpha_border" (func $image_alpha_border (param i32 f32) (result i32)))
;; Crop an image, in-place.
(import "null0" "image_crop" (func $image_crop (param i32 i32 i32 i32 i32)))
;; Crop an image based on the alpha border, in-place.
(import "null0" "image_alpha_crop" (func $image_alpha_crop (param i32 f32)))
;; Adjust the brightness of an image, in-place.
(import "null0" "image_color_brightness" (func $image_color_brightness (param i32 f32)))
;; Flip an image, in-place.
(import "null0" "image_flip" (func $image_flip (param i32 i32 i32)))
;; Change the contrast of an image, in-place.
(import "null0" "image_color_contrast" (func $image_color_contrast (param i32 f32)))
;; Use an image as an alpha-mask on another image.
(import "null0" "image_alpha_mask" (func $image_alpha_mask (param i32 i32 i32 i32)))
;; Create a new image, rotating another image.
(import "null0" "image_rotate" (func $image_rotate (param i32 f32 i32) (result i32)))
;; Create a new image of a gradient.
(import "null0" "image_gradient" (func $image_gradient (param i32 i32 i32 i32 i32 i32) (result i32)))
;; Unload an image.
(import "null0" "unload_image" (func $unload_image (param i32)))
;; Unload a font.
(import "null0" "unload_font" (func $unload_font (param i32)))
;; Clear an image.
(import "null0" "clear_image" (func $clear_image (param i32 i32)))
;; Draw a single pixel on an image.
(import "null0" "draw_point_on_image" (func $draw_point_on_image (param i32 i32 i32 i32)))
;; Draw a line on an image.
(import "null0" "draw_line_on_image" (func $draw_line_on_image (param i32 i32 i32 i32 i32 i32)))
;; Draw a filled rectangle on an image.
(import "null0" "draw_rectangle_on_image" (func $draw_rectangle_on_image (param i32 i32 i32 i32 i32 i32)))
;; Draw a filled triangle on an image.
(import "null0" "draw_triangle_on_image" (func $draw_triangle_on_image (param i32 i32 i32 i32 i32 i32 i32 i32)))
;; Draw a filled ellipse on an image.
(import "null0" "draw_ellipse_on_image" (func $draw_ellipse_on_image (param i32 i32 i32 i32 i32 i32)))
;; Draw a circle on an image.
(import "null0" "draw_circle_on_image" (func $draw_circle_on_image (param i32 i32 i32 i32 i32)))
;; Draw a filled polygon on an image.
(import "null0" "draw_polygon_on_image" (func $draw_polygon_on_image (param i32 i32 i32 i32)))
;; Draw a filled round-rectangle on an image.
(import "null0" "draw_rectangle_rounded_on_image" (func $draw_rectangle_rounded_on_image (param i32 i32 i32 i32 i32 i32 i32)))
;; Draw an image on an image.
(import "null0" "draw_image_on_image" (func $draw_image_on_image (param i32 i32 i32 i32)))
;; Draw a tinted image on an image.
(import "null0" "draw_image_tint_on_image" (func $draw_image_tint_on_image (param i32 i32 i32 i32 i32)))
;; Draw an image, rotated, on an image.
(import "null0" "draw_image_rotated_on_image" (func $draw_image_rotated_on_image (param i32 i32 i32 i32 f32 f32 f32 i32)))
;; Draw an image, flipped, on an image.
(import "null0" "draw_image_flipped_on_image" (func $draw_image_flipped_on_image (param i32 i32 i32 i32 i32 i32 i32)))
;; Draw an image, scaled, on an image.
(import "null0" "draw_image_scaled_on_image" (func $draw_image_scaled_on_image (param i32 i32 i32 i32 f32 f32 f32 f32 i32)))
;; Draw some text on an image.
(import "null0" "draw_text_on_image" (func $draw_text_on_image (param i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) rectangle on the screen.
(import "null0" "draw_rectangle_outline" (func $draw_rectangle_outline (param i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) triangle on the screen.
(import "null0" "draw_triangle_outline" (func $draw_triangle_outline (param i32 i32 i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) ellipse on the screen.
(import "null0" "draw_ellipse_outline" (func $draw_ellipse_outline (param i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) circle on the screen.
(import "null0" "draw_circle_outline" (func $draw_circle_outline (param i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) polygon on the screen.
(import "null0" "draw_polygon_outline" (func $draw_polygon_outline (param i32 i32 i32 i32)))
;; Draw a outlined (with thickness) arc on the screen.
(import "null0" "draw_arc_outline" (func $draw_arc_outline (param i32 i32 f32 f32 f32 i32 i32 i32)))
;; Draw a outlined (with thickness) round-rectangle on the screen.
(import "null0" "draw_rectangle_rounded_outline" (func $draw_rectangle_rounded_outline (param i32 i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) rectangle on an image.
(import "null0" "draw_rectangle_outline_on_image" (func $draw_rectangle_outline_on_image (param i32 i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) triangle on an image.
(import "null0" "draw_triangle_outline_on_image" (func $draw_triangle_outline_on_image (param i32 i32 i32 i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) ellipse on an image.
(import "null0" "draw_ellipse_outline_on_image" (func $draw_ellipse_outline_on_image (param i32 i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) circle on an image.
(import "null0" "draw_circle_outline_on_image" (func $draw_circle_outline_on_image (param i32 i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) polygon on an image.
(import "null0" "draw_polygon_outline_on_image" (func $draw_polygon_outline_on_image (param i32 i32 i32 i32 i32)))
;; Draw a outlined (with thickness) round-rectangle on an image.
(import "null0" "draw_rectangle_rounded_outline_on_image" (func $draw_rectangle_rounded_outline_on_image (param i32 i32 i32 i32 i32 i32 i32 i32)))

;; -- INPUT --

;; Has the key been pressed? (tracks unpress/read correctly.)
(import "null0" "key_pressed" (func $key_pressed (param i32) (result i32)))
;; Is the key currently down?
(import "null0" "key_down" (func $key_down (param i32) (result i32)))
;; Has the key been released? (tracks press/read correctly.)
(import "null0" "key_released" (func $key_released (param i32) (result i32)))
;; Is the key currently up?
(import "null0" "key_up" (func $key_up (param i32) (result i32)))
;; Has the button been pressed? (tracks unpress/read correctly.)
(import "null0" "gamepad_button_pressed" (func $gamepad_button_pressed (param i32 i32) (result i32)))
;; Is the button currently down?
(import "null0" "gamepad_button_down" (func $gamepad_button_down (param i32 i32) (result i32)))
;; Has the button been released? (tracks press/read correctly.)
(import "null0" "gamepad_button_released" (func $gamepad_button_released (param i32 i32) (result i32)))
;; Get current position of mouse.
(import "null0" "mouse_position" (func $mouse_position (result i32)))
;; Has the button been pressed? (tracks unpress/read correctly.)
(import "null0" "mouse_button_pressed" (func $mouse_button_pressed (param i32) (result i32)))
;; Is the button currently down?
(import "null0" "mouse_button_down" (func $mouse_button_down (param i32) (result i32)))
;; Has the button been released? (tracks press/read correctly.)
(import "null0" "mouse_button_released" (func $mouse_button_released (param i32) (result i32)))
;; Is the button currently up?
(import "null0" "mouse_button_up" (func $mouse_button_up (param i32) (result i32)))

;; -- SOUND --

;; Load a sound from a file in cart.
(import "null0" "load_sound" (func $load_sound (param i32) (result i32)))
;; Play a sound.
(import "null0" "play_sound" (func $play_sound (param i32 i32)))
;; Stop a sound.
(import "null0" "stop_sound" (func $stop_sound (param i32)))
;; Unload a sound.
(import "null0" "unload_sound" (func $unload_sound (param i32)))
;; Speak some text and return a sound. Set things to 0 for defaults.
(import "null0" "tts_sound" (func $tts_sound (param i32 i32 i32 i32 i32 i32 i32) (result i32)))
;; Create Sfx sound.
(import "null0" "sfx_sound" (func $sfx_sound (param i32) (result i32)))
;; Create Sfx parameters.
(import "null0" "sfx_generate" (func $sfx_generate (param i32) (result i32)))

;; -- TYPES --


;; -- UTILITIES --

;; Get system-time (ms) since unix epoch.
(import "null0" "current_time" (func $current_time (result i64)))
;; Get the change in time (seconds) since the last update run.
(import "null0" "delta_time" (func $delta_time (result f32)))
;; Get a random integer between 2 numbers.
(import "null0" "random_int" (func $random_int (param i32 i32) (result i32)))
;; Get the random-seed.
(import "null0" "random_seed_get" (func $random_seed_get (result i64)))
;; Set the random-seed.
(import "null0" "random_seed_set" (func $random_seed_set (param i64)))
