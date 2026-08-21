(module
  ;; null0 imports (see ../null0.wat for the full list)
  (import "null0" "clear" (func $clear (param i32)))
  (import "null0" "draw_text" (func $draw_text (param i32 i32 i32 i32 i32)))
  (import "null0" "draw_rectangle" (func $draw_rectangle (param i32 i32 i32 i32 i32)))
  (import "null0" "draw_circle" (func $draw_circle (param i32 i32 i32 i32)))
  (import "null0" "draw_triangle" (func $draw_triangle (param i32 i32 i32 i32 i32 i32 i32)))
  (import "null0" "draw_line" (func $draw_line (param i32 i32 i32 i32 i32)))
  (import "null0" "draw_polygon" (func $draw_polygon (param i32 i32 i32)))

  (memory (export "memory") 2)

  ;; -- constants --
  (global $FONT_DEFAULT i32 (i32.const 0))

  ;; Color is a pointer to 4 bytes (r, g, b, a) - see null0.wat for the list
  (data (i32.const 65536) "\50\50\50\ff") ;; DARKGRAY
  (global $darkgray i32 (i32.const 65536))
  (data (i32.const 65540) "\ff\ff\ff\ff") ;; WHITE
  (global $white i32 (i32.const 65540))
  (data (i32.const 65544) "\e6\29\37\ff") ;; RED
  (global $red i32 (i32.const 65544))
  (data (i32.const 65548) "\00\e4\30\ff") ;; GREEN
  (global $green i32 (i32.const 65548))
  (data (i32.const 65552) "\00\79\f1\ff") ;; BLUE
  (global $blue i32 (i32.const 65552))
  (data (i32.const 65556) "\c8\c8\c8\ff") ;; LIGHTGRAY
  (global $lightgray i32 (i32.const 65556))
  (data (i32.const 65560) "\c8\7a\ff\ff") ;; PURPLE
  (global $purple i32 (i32.const 65560))
  (data (i32.const 65564) "\fd\f9\00\ff") ;; YELLOW
  (global $yellow i32 (i32.const 65564))
  (data (i32.const 65568) "\ff\a1\00\ff") ;; ORANGE
  (global $orange i32 (i32.const 65568))

  ;; strings are null-terminated UTF8 in memory
  (data (i32.const 65600) "null0 demo\00")
  (global $title_str i32 (i32.const 65600))
  (data (i32.const 65700) "shapes + animation + text\00")
  (global $caption_str i32 (i32.const 65700))

  ;; hexagon for draw_polygon: Vector[] is 6 * (i32 x, i32 y) written below
  (global $hex_points i32 (i32.const 65800))

  ;; persistent frame counter, incremented once per update()
  (global $frame (mut i32) (i32.const 0))

  ;; write the hexagon points into memory once at startup
  (func (export "load")
    (i32.store (i32.const 65800) (i32.const 460))
    (i32.store (i32.const 65804) (i32.const 80))
    (i32.store (i32.const 65808) (i32.const 520))
    (i32.store (i32.const 65812) (i32.const 80))
    (i32.store (i32.const 65816) (i32.const 550))
    (i32.store (i32.const 65820) (i32.const 140))
    (i32.store (i32.const 65824) (i32.const 520))
    (i32.store (i32.const 65828) (i32.const 200))
    (i32.store (i32.const 65832) (i32.const 460))
    (i32.store (i32.const 65836) (i32.const 200))
    (i32.store (i32.const 65840) (i32.const 430))
    (i32.store (i32.const 65844) (i32.const 140)))

  ;; called on every frame
  (func (export "update")
    (local $x i32)

    (call $clear (global.get $darkgray))
    (call $draw_text (global.get $FONT_DEFAULT) (global.get $title_str) (i32.const 20) (i32.const 20) (global.get $white))
    (call $draw_rectangle (i32.const 40) (i32.const 80) (i32.const 100) (i32.const 70) (global.get $red))
    (call $draw_circle (i32.const 220) (i32.const 115) (i32.const 45) (global.get $green))
    (call $draw_triangle (i32.const 320) (i32.const 150) (i32.const 400) (i32.const 150) (i32.const 360) (i32.const 60) (global.get $blue))
    (call $draw_line (i32.const 40) (i32.const 250) (i32.const 600) (i32.const 250) (global.get $lightgray))
    (call $draw_polygon (global.get $hex_points) (i32.const 6) (global.get $purple))

    ;; animate a circle sweeping left-to-right across the bottom of the screen
    (global.set $frame (i32.add (global.get $frame) (i32.const 1)))
    (local.set $x (i32.rem_u (global.get $frame) (i32.const 600)))
    (call $draw_circle (i32.add (local.get $x) (i32.const 20)) (i32.const 350) (i32.const 20) (global.get $yellow))

    (call $draw_text (global.get $FONT_DEFAULT) (global.get $caption_str) (i32.const 20) (i32.const 440) (global.get $orange)))

  ;; other callbacks you can implement:
  ;; (func (export "unload"))
  ;; (func (export "buttonUp") (param i32 i32))
  ;; (func (export "buttonDown") (param i32 i32))
  ;; (func (export "keyUp") (param i32))
  ;; (func (export "keyDown") (param i32))
  ;; (func (export "mouseDown") (param i32))
  ;; (func (export "mouseUp") (param i32))
  ;; (func (export "mouseMoved") (param f32 f32))
)
