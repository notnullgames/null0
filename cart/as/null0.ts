// include this in your null0 cart
// asc --config ./node_modules/@assemblyscript/wasi-shim/asconfig.json --lib ./null0.ts src/main.ts

export class Color {
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

export class Dimensions {
  constructor(width:u32 = 0, height:u32 = 0) {
    this.width = width;
    this.height = height;
  }
  width: u32;
  height: u32;
}

export const HEIGHT:f32 = 240.0;
export const WIDTH:f32 = 320.0;

export const RED = new Color(230, 41, 55, 255);
export const BLUE = new Color(0, 121, 241, 255);
export const BLACK = new Color(0, 0, 0, 255);

@external("null0", "load_sound")
declare function _null0_load_sound(filename: ArrayBuffer): u32
export function load_sound(filename: String):u32 {
  return _null0_load_sound(String.UTF8.encode(filename, true));
}

@external("null0", "play_sound")
export declare function play_sound(sound: u32, loop: bool):void;

@external("null0", "measure_text")
declare function _null0_measure_text(ret:Dimensions, font: u32, text: ArrayBuffer): void;
export function measure_text(font: u32, text: String): Dimensions {
  const ret = new Dimensions();
  _null0_measure_text(ret, font, String.UTF8.encode(text, true));
  return ret;
}

@external("null0", "clear")
export declare function clear(color: Color): void;

@external("null0", "draw_text")
declare function _null0_draw_text(font: u32, text: ArrayBuffer, posX: i32, posY: i32, color: Color): void;
export function draw_text(font: u32, text: String, posX: i32, posY: i32, color: Color): void {
  _null0_draw_text(font, String.UTF8.encode(text, true), posX, posY, color);
}
