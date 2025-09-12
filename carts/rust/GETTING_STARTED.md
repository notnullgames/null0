# Getting Started with null0 Rust

This guide will help you create your first null0 game in Rust.

## Prerequisites

1. Install Rust: https://rustup.rs/
2. Add the WebAssembly target:
   ```bash
   rustup target add wasm32-unknown-unknown
   ```

## Project Structure

```
my_null0_game/
├── Cargo.toml
├── src/
│   └── lib.rs
└── build.sh (optional)
```

## Step 1: Create Cargo.toml

```toml
[package]
name = "my_null0_game"
version = "0.1.0"
edition = "2021"

[lib]
crate-type = ["cdylib"]

[dependencies]
null0 = { path = "path/to/null0/carts/rust" }

[profile.release]
opt-level = "s"
lto = true
codegen-units = 1
panic = "abort"

[profile.dev]
panic = "abort"
```

## Step 2: Create src/lib.rs

```rust
use null0::*;

#[no_mangle]
pub extern "C" fn load() {
    // Initialize your game here
}

#[no_mangle]
pub extern "C" fn update() {
    // This runs 60 times per second
    clear(DARKBLUE);
    draw_text(FONT_DEFAULT, cstr!("My First null0 Game!"), 10, 10, WHITE);

    // Simple input example
    if key_down(Key::KeySpace) {
        draw_circle(320, 240, 50, RED);
    }
}

#[no_mangle]
pub extern "C" fn unload() {
    // Cleanup when game ends
}
```

## Step 3: Build for WebAssembly

```bash
cargo build --target wasm32-unknown-unknown --release
```

Your game will be compiled to:
`target/wasm32-unknown-unknown/release/my_null0_game.wasm`

## Key Concepts

### Callback Functions

null0 expects these exported functions:

- `load()` - Called once when the game starts
- `update()` - Called 60 times per second for game logic
- `unload()` - Called when the game ends (optional)

### String Handling

Use the `cstr!` macro for string literals:

```rust
draw_text(FONT_DEFAULT, cstr!("Hello World!"), x, y, WHITE);
```

### No Standard Library

The crate uses `#![no_std]` for smaller WebAssembly output. This means:

- No `std::vec::Vec`, use arrays or static data
- No heap allocation
- No `println!`, use `draw_text` for output
- No `std::collections`, use arrays or simple data structures

### Game State

Use static mut variables for global game state:

```rust
static mut PLAYER_X: i32 = 0;
static mut PLAYER_Y: i32 = 0;

#[no_mangle]
pub extern "C" fn update() {
    unsafe {
        if key_down(Key::KeyLeft) {
            PLAYER_X -= 2;
        }
        if key_down(Key::KeyRight) {
            PLAYER_X += 2;
        }

        draw_circle(PLAYER_X, PLAYER_Y, 10, BLUE);
    }
}
```

### Colors and Constants

Pre-defined colors:

- `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`
- `YELLOW`, `CYAN`, `MAGENTA`, `ORANGE`
- `PURPLE`, `BROWN`, `GRAY`, `LIGHTGRAY`, `DARKGRAY`

Screen constants:

- `SCREEN_WIDTH` (640)
- `SCREEN_HEIGHT` (480)
- `FONT_DEFAULT` (0)

## Common Patterns

### Simple Animation

```rust
static mut FRAME: u32 = 0;

#[no_mangle]
pub extern "C" fn update() {
    unsafe { FRAME += 1; }

    clear(BLACK);
    let x = 320 + ((unsafe { FRAME } as f32 * 0.1).sin() * 100.0) as i32;
    draw_circle(x, 240, 20, RED);
}
```

### Input Handling

```rust
#[no_mangle]
pub extern "C" fn update() {
    if key_pressed(Key::KeySpace) {
        // Just pressed this frame
    }

    if key_down(Key::KeySpace) {
        // Held down
    }

    if key_released(Key::KeySpace) {
        // Just released this frame
    }
}
```

### Drawing Shapes

```rust
// Basic shapes
draw_point(x, y, WHITE);
draw_line(x1, y1, x2, y2, RED);
draw_rectangle(x, y, width, height, BLUE);
draw_circle(x, y, radius, GREEN);

// Outlined shapes
draw_rectangle_outline(x, y, width, height, thickness, WHITE);
draw_circle_outline(x, y, radius, thickness, RED);
```

## Examples

Check out the examples in `examples/` directory:

- `simple/` - Basic template
- `bouncing_ball/` - Interactive bouncing ball with physics

## Building for Release

For optimal file size:

```bash
cargo build --target wasm32-unknown-unknown --release
```

The release profile is configured for minimal size with:

- `opt-level = "s"` - Optimize for size
- `lto = true` - Link-time optimization
- `codegen-units = 1` - Single codegen unit for better optimization
- `panic = "abort"` - Smaller panic handler

## Troubleshooting

### "function signature mismatch" errors

Make sure your callback functions are exactly:

```rust
#[no_mangle]
pub extern "C" fn load() { }

#[no_mangle]
pub extern "C" fn update() { }

#[no_mangle]
pub extern "C" fn unload() { }
```

### String issues

Always use `cstr!("text")` for string literals passed to null0 functions.

### Large file sizes

- Use `--release` mode
- Avoid pulling in large dependencies
- Use `#![no_std]` (already configured)
- Consider using `wee_alloc` if you need allocation
