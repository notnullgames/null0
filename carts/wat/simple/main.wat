(module
  ;; null0 imports (see null0.wat for the full list)
  (import "null0" "clear" (func $clear (param i32)))
  (import "null0" "draw_circle" (func $draw_circle (param i32 i32 i32 i32)))

  (memory (export "memory") 1)

  ;; called on load
  (func (export "load")
    (call $clear (i32.const 0xfff17900)) ;; BLUE
    (call $draw_circle
      (i32.const 100) (i32.const 100) (i32.const 50)
      (i32.const 0xff3729e6))) ;; RED

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
