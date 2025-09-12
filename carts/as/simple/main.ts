// AssemblyScript null0 cart example

let frameCount: u32 = 0;

export function load(): void {
  // Game initialization
}

export function update(): void {
  frameCount++;
  
  // Clear screen with dark blue
  clear(DARKBLUE);
  
  // Draw some shapes
  draw_rectangle(50, 50, 100, 60, RED);
  draw_circle(200, 100, 30, GREEN);
  draw_triangle(300, 50, 350, 150, 250, 150, YELLOW);
  
  // Draw some text
  draw_text(FONT_DEFAULT, stringToPtr("Hello from AssemblyScript!"), 50, 200, WHITE);
  draw_text(FONT_DEFAULT, stringToPtr("null0 Fantasy Console"), 50, 220, LIGHTGRAY);
  
  // Draw frame counter (blinking text)
  if (frameCount % 60 < 30) {
    draw_text(FONT_DEFAULT, stringToPtr("Frame counter blinking"), 50, 250, SKYBLUE);
  }
  
  // Draw some input-responsive elements
  if (key_down(Key.KEY_SPACE)) {
    draw_text(FONT_DEFAULT, stringToPtr("SPACE is pressed!"), 50, 280, ORANGE);
  }
  
  if (key_pressed(Key.KEY_ENTER)) {
    draw_rectangle(400, 200, 50, 50, MAGENTA);
  }
}

export function unload(): void {
  // Cleanup when cart is unloaded
}

