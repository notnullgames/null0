(module
  ;; null0 imports (see null0.wat for the full list)
  (import "null0" "clear" (func $clear (param i32)))
  (import "null0" "draw_circle" (func $draw_circle (param i32 i32 i32 i32)))

  ;; two pages: the colour data segments below are at 65536, which is one page
  ;; in - with 1 page the module fails to instantiate ("data segment is out of
  ;; bounds"), and it must be exported so the host can read Color pointers
  (memory (export "memory") 2)

  ;; Color is a pointer to 4 bytes (r, g, b, a) in your memory, not a packed
  ;; scalar - see null0.wat for the full list of predefined color constants
  (data (i32.const 65536) "\00\79\f1\ff") ;; BLUE = rgba(0, 121, 241, 255)
  (global $blue i32 (i32.const 65536))
  (data (i32.const 65540) "\e6\29\37\ff") ;; RED = rgba(230, 41, 55, 255)
  (global $red i32 (i32.const 65540))

  ;; called on load
  (func (export "load")
    (call $clear (global.get $blue))
    (call $draw_circle
      (i32.const 100) (i32.const 100) (i32.const 50)
      (global.get $red)))

  ;; called on every frame
  (func (export "update"))

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
