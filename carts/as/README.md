# null0 - AssemblyScript Bindings

AssemblyScript bindings for the null0 fantasy console API.

## Installation

First, install AssemblyScript:

```bash
npm install -g assemblyscript
```

Or install locally in your project:

```bash
npm install assemblyscript
```

## Usage

Create a simple game by implementing the required callback functions:

```typescript
import { clear, draw_circle, draw_text, key_down, FONT_DEFAULT, BLACK, RED, WHITE, Key, stringToPtr } from '../null0'

export function load(): void {
  // Initialize your game here
}

export function update(): void {
  // Game logic runs at 60 FPS
  clear(BLACK)
  draw_text(FONT_DEFAULT, stringToPtr('Hello, null0!'), 10, 10, WHITE)

  if (key_down(Key.KEY_SPACE)) {
    draw_circle(100, 100, 50, RED)
  }
}

export function unload(): void {
  // Cleanup when the cart is unloaded
}
```

## Building for WebAssembly

### Manual Building

To compile your game to WebAssembly for null0:

```bash
# Build in release mode for optimal size
npx asc main.ts --target release --exportRuntime --bindings esm --use abort= -o main.wasm

# Or build in debug mode for development
npx asc main.ts --target debug --exportRuntime --bindings esm --use abort= -o main.wasm
```

### Using the Build Script

Each example includes a `build.sh` script:

```bash
cd carts/as/simple
./build.sh
```

### CMake Integration

If you're using the null0 build system, you can add AssemblyScript carts to the main CMake build by adding them to `carts/CMakeLists.txt`:

```cmake
BUILD_CART_AS("my_game_name")
```

This will:

1. Build your AssemblyScript project with `npx asc`
2. Copy the generated `.wasm` file as `main.wasm`
3. Include any assets from your cart directory
4. Package everything into a `.null0` cart file

The CMake function expects your AssemblyScript project to be in `carts/as/my_game_name/`.

## API Reference

The module provides bindings for all null0 API functions:

### Graphics Functions

- `clear(color: Color)` - Clear the screen
- `draw_circle(centerX: i32, centerY: i32, radius: i32, color: Color)` - Draw a circle
- `draw_rectangle(posX: i32, posY: i32, width: i32, height: i32, color: Color)` - Draw a rectangle
- `draw_text(font: u32, text: usize, posX: i32, posY: i32, color: Color)` - Draw text

### Input Functions

- `key_down(key: Key): bool` - Check if key is currently pressed
- `key_pressed(key: Key): bool` - Check if key was just pressed this frame

### Utility Functions

- `current_time(): u64` - Get current time in milliseconds
- `delta_time(): f32` - Get time since last frame in seconds
- `random_int(min: i32, max: i32): i32` - Get random integer

### Helper Functions

- `stringToPtr(str: string): usize` - Convert string to C string pointer
- `vectorArrayToPtr(vectors: StaticArray<Vector>): usize` - Convert Vector array to pointer

### Types

- `Color` - RGBA color with r, g, b, a components (u8)
- `Vector` - 2D position with x, y components (i32)
- `Rectangle` - 2D rectangle with x, y, width, height (i32)
- `Dimensions` - 2D size with width, height (i32)

### Constants

All standard colors are available: `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`, `YELLOW`, etc.

## Examples

- `simple` - Basic template showing graphics, input, and text rendering

## Notes

- All external function calls use the `@external("null0", "function_name")` decorator
- String handling requires `stringToPtr()` helper for C FFI compatibility
- Vector arrays use `StaticArray<Vector>` and `vectorArrayToPtr()` helper
- The `--use abort=` flag disables AssemblyScript's abort handler for smaller WASM files

