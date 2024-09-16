import { RED, BLUE, BLACK } from "../colors";

let audioLogo: u32 = 0;
let w: i32 = 95;

// called when the cart is loaded
export function load(): void {
  console.log("Hello from assemblyscript");
  // audioLogo = load_sound("assets/notnullgames.ogg");
  // play_sound(audioLogo, false);
}

// called on every frame
export function update(): void {
  clear(BLACK);
  draw_text(0, "Hello from null0", w, i32(HEIGHT) / 2 + 1, BLUE);
  draw_text(0, "Hello from null0", w, i32(HEIGHT) / 2, RED);
}
