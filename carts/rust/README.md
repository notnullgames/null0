# null0 - Rust Bindings

Rust bindings for the null0 fantasy console API.

## Installation

Add this to your `Cargo.toml`:

```toml
[dependencies]
null0 = { path = "path/to/null0/carts/rust" }

[lib]
crate-type = ["cdylib"]

[profile.release]
opt-level = "s"
lto = true
codegen-units = 1
panic = "abort"
```

## Usage

Create a simple game by implementing the required callback functions:

```rust
use null0::*;

#[no_mangle]
pub extern "C" fn load() {
    // Initialize your game here
}

#[no_mangle]
pub extern "C" fn update() {
    // Game logic runs at 60 FPS
    clear(BLACK);
    draw_text(FONT_DEFAULT, cstr!("Hello, null0!"), 10, 10, WHITE);

    if key_pressed(Key::KeySpace) {
        draw_circle(100, 100, 50, RED);
    }
}

#[no_mangle]
pub extern "C" fn unload() {
    // Cleanup when the cart is unloaded
}
```

## Building for WebAssembly

To compile your game to WebAssembly for null0:

```bash
# Install the WebAssembly target
rustup target add wasm32-unknown-unknown

# Build in release mode for optimal size
cargo build --target wasm32-unknown-unknown --release

# Your .wasm file will be in target/wasm32-unknown-unknown/release/
```

## API Reference

The crate provides bindings for all null0 API functions:

### Graphics

- `clear(color)` - Clear the screen
- `draw_point(x, y, color)` - Draw a pixel
- `draw_line(x1, y1, x2, y2, color)` - Draw a line
- `draw_rectangle(x, y, width, height, color)` - Draw a rectangle
- `draw_circle(x, y, radius, color)` - Draw a circle
- `draw_text(font, text, x, y, color)` - Draw text
- And many more...

### Input

- `key_pressed(key)` - Check if key was just pressed
- `key_down(key)` - Check if key is currently held
- `key_released(key)` - Check if key was just released
- `key_up(key)` - Check if key is not pressed

### Audio

- `load_sound(filename)` - Load a sound file
- `play_sound(sound, loop)` - Play a sound
- `stop_sound(sound)` - Stop a sound
- `sfx_generate(preset)` - Generate sound effects

### Utilities

- `current_time()` - Get current time
- `delta_time()` - Get delta time
- `random_int(min, max)` - Generate random integer

## String Handling

Use the `cstr!` macro for string literals that need to be passed to null0 functions:

```rust
draw_text(FONT_DEFAULT, cstr!("Hello World!"), 10, 10, WHITE);
```

## Types

The crate provides these main types:

- `Color { r, g, b, a }` - RGBA color
- `Vector { x, y }` - 2D position
- `Rectangle { x, y, width, height }` - 2D rectangle
- `Dimensions { width, height }` - 2D size

## Constants

Pre-defined colors are available:

- `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`
- `YELLOW`, `CYAN`, `MAGENTA`, `ORANGE`
- `PURPLE`, `BROWN`, `GRAY`, `LIGHTGRAY`, `DARKGRAY`
- And more...

Screen constants:

- `SCREEN` - Screen image ID (0)
- `SCREEN_WIDTH` - Screen width (640)
- `SCREEN_HEIGHT` - Screen height (480)
- `FONT_DEFAULT` - Default font ID (0)
