(module
  ;; every language's `simple` cart draws exactly this - see carts/wat/null0.wat
  ;; for the full import list
  (import "null0" "clear" (func $clear (param i32)))
  (import "null0" "draw_circle" (func $draw_circle (param i32 i32 i32 i32)))
  (import "null0" "draw_text" (func $draw_text (param i32 i32 i32 i32 i32)))

  ;; two pages: the data below sits at 65536, which is one page in - with 1
  ;; page the module fails to instantiate ("data segment is out of bounds").
  ;; exported because the host reads Color and string pointers out of it.
  (memory (export "memory") 2)

  (data (i32.const 65536) "\00\79\f1\ff") ;; BLUE = rgba(0, 121, 241, 255)
  (global $blue i32 (i32.const 65536))
  (data (i32.const 65540) "\e6\29\37\ff") ;; RED = rgba(230, 41, 55, 255)
  (global $red i32 (i32.const 65540))
  (data (i32.const 65544) "\ff\ff\ff\ff") ;; WHITE = rgba(255, 255, 255, 255)
  (global $white i32 (i32.const 65544))

  ;; "hello from WAT", null-terminated
  (data (i32.const 65548) "\68\65\6c\6c\6f\20\66\72\6f\6d\20\57\41\54\00")
  (global $text i32 (i32.const 65548))

  (func (export "load")
    (call $clear (global.get $blue))
    (call $draw_circle
      (i32.const 100) (i32.const 100) (i32.const 50)
      (global.get $red))
    (call $draw_text
      (i32.const 0)            ;; FONT_DEFAULT
      (global.get $text)
      (i32.const 170) (i32.const 92)
      (global.get $white)))

  (func (export "update"))
)
