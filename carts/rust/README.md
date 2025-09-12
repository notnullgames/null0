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

### Manual Building

To compile your game to WebAssembly for null0:

```bash
# Install the WebAssembly target
rustup target add wasm32-unknown-unknown

# Build in release mode for optimal size
cargo build --target wasm32-unknown-unknown --release

# Your .wasm file will be in target/wasm32-unknown-unknown/release/ which you put in a zip as main.wasm
```
