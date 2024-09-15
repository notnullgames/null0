let audioLogo: u32 = 0;
let w: f32 = 0;

// called when the cart is loaded
export function load(): void {
  console.log("hello from AS");
  audioLogo = load_sound("assets/notnullgames.ogg");
  play_sound(audioLogo, false);
  const dim: Dimensions = measure_text(0, "Hello from null0");
  w = WIDTH / 2.0 - <f32>dim.width / 2.0;
}

// called on every frame
export function update(): void {
  clear(BLACK);
  draw_text(
    0,
    "Hello from null0",
    <i32>(w + 1.0),
    <i32>(HEIGHT / 2.0 + 1.0),
    BLUE,
  );
  draw_text(0, "Hello from null0", <i32>w, <i32>(HEIGHT / 2.0), RED);
}
