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

# Your .wasm file will be in target/wasm32-unknown-unknown/release/
```

### CMake Integration

If you're using the null0 build system, you can add Rust carts to the main CMake build by adding them to `carts/CMakeLists.txt`:

```cmake
BUILD_CART_RUST("my_game_name")
```

This will:

1. Build your Rust project with `cargo build --target wasm32-unknown-unknown --release`
2. Copy the generated `.wasm` file as `main.wasm`
3. Include any assets from your cart directory
4. Package everything into a `.null0` cart file
