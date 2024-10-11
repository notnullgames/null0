// this code will be injected at the top of your cart-code

// expose memory-management
// this might not be strictly needed, since host passes return pointers as param
// but I include it for use in this header, so I can wrap pointers here

export function malloc(size: usize, id: u32 = 0): usize {
   const pout = __new(size, id)
  __pin(pout)
  return pout
}

export function free(pointer:usize): void {
  __unpin(pointer)
}


// classes

class Color {
  constructor(r:u8 = 0, g:u8 = 0, b:u8 = 0, a:u8 = 0) {
    this.r = r;
    this.g = g;
    this.b = b;
    this.a = a;
  }
  
  r: u8;
  g: u8;
  b: u8;
  a: u8;
}

class Dimensions {
  constructor(width:u32 = 0, height:u32 = 0) {
    this.width = width;
    this.height = height;
  }

  width: u32;
  height: u32;
}

// definitions
const HEIGHT: f32 = 240.0;
const WIDTH: f32 = 320.0;

const LIGHTGRAY: Color = new Color(200, 200, 200, 255);
const GRAY: Color = new Color(130, 130, 130, 255);
const DARKGRAY: Color = new Color(80, 80, 80, 255);
const YELLOW: Color = new Color(253, 249, 0, 255);
const GOLD: Color = new Color(255, 203, 0, 255);
const ORANGE: Color = new Color(255, 161, 0, 255);
const PINK: Color = new Color(255, 109, 194, 255);
const RED: Color = new Color(230, 41, 55, 255);
const MAROON: Color = new Color(190, 33, 55, 255);
const GREEN: Color = new Color(0, 228, 48, 255);
const LIME: Color = new Color(0, 158, 47, 255);
const DARKGREEN: Color = new Color(0, 117, 44, 255);
const SKYBLUE: Color = new Color(102, 191, 255, 255);
const BLUE: Color = new Color(0, 121, 241, 255);
const DARKBLUE: Color = new Color(0, 82, 172, 255);
const PURPLE: Color = new Color(200, 122, 255, 255);
const VIOLET: Color = new Color(135, 60, 190, 255);
const DARKPURPLE: Color = new Color(112, 31, 126, 255);
const BEIGE: Color = new Color(211, 176, 131, 255);
const BROWN: Color = new Color(127, 106, 79, 255);
const DARKBROWN: Color = new Color(76, 63, 47, 255);
const WHITE: Color = new Color(255, 255, 255, 255);
const BLACK: Color = new Color(0, 0, 0, 255);
const BLANK: Color = new Color(0, 0, 0, 0);
const MAGENTA: Color = new Color(255, 0, 255, 255);
const RAYWHITE: Color = new Color(245, 245, 245, 255)

// functions

@external("null0", "load_sound")
declare function _null0_load_sound(filename: ArrayBuffer): u32
function load_sound(filename: String):u32 {
  return _null0_load_sound(String.UTF8.encode(filename, true));
}

@external("null0", "play_sound")
declare function play_sound(sound: u32, loop: bool):void

@external("null0", "measure_text")
declare function _null0_measure_text(ret:usize, font: u32, text: ArrayBuffer): void;
function measure_text(font: u32, text: String): Dimensions {
  const r = new Dimensions()
  _null0_measure_text(changetype<usize>(r), font, String.UTF8.encode(text, true))
  return r
}

@external("null0", "clear")
declare function clear(color: Color): void

@external("null0", "draw_text")
declare function _null0_draw_text(font: u32, text: ArrayBuffer, posX: i32, posY: i32, color: Color): void
function draw_text(font: u32, text: String, posX: i32, posY: i32, color: Color): void {
  _null0_draw_text(font, String.UTF8.encode(text, true), posX, posY, color)
}
