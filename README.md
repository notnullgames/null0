This combines ideas from [pntr_app_starter](https://github.com/RobLoach/pntr_app_starter) with [wamr](https://github.com/bytecodealliance/wasm-micro-runtime) to make null0 game-engine (native runtime & libretro core.)

## building

In order to build carts, you will need the [wasi-sdk](https://github.com/WebAssembly/wasi-sdk/releases) installed. You can set `WASI_SDK_PREFIX` to the location, if it's not `/opt/wasi-sdk`

```
# config
cmake -B build

# build runtime
cmake --build build

# configure for web
emcmake cmake -B wbuild

# build web runtime
emmake make -C wbuild
```

These cmake-flags will effect the build:

```
// Build Null0 libretro Host (don't do this in web-build)
LIBRETRO:BOOL=OFF

// Build Null0 NATIVE Host (don't do this in web-build)
NATIVE:BOOL=ON

// Use SDL in hosts
SDL:BOOL=ON

// Build Null0 raylib Host
RAYLIB:BOOL=OFF

// Build Demo Null0 Carts
CARTS:BOOL=ON

// Unit tests
TESTS:BOOL=OFF
```

You can set them like this:

```
# don't build demo carts, use defaults
cmake -B build -DCARTS=0

# don't buid anything but the carts (since LIBRETRO is off by default)
cmake -B build -DNATIVE=0

# just build unit-tests
cmake -B build -DNATIVE=0 -DTESTS=1 -DCARTS=0
cmake --build build
./build/test/test_colors
```

## todo

### immediate

- merge web into native as "runtime" and put lots of emscripten checks in a single entry-point
- move null0_api to null0_core
- test everything, maybe a full battery of wasm-side tests (every single function)
- auto-generate more code from api defs
- generate headers for other cart-languages (not just C)
- update website with docs generated from the api defs

#### carts

- filesystem is referencing removed `file_embed`, and needs some testing
- hello is not doing `measure_text` right (probly needs wamr def fixed, see `color_`)
- input needs event-handlers setup
- sound segfaults


### longterm

- add TTS libs & API functions
- setup a ESP32 host
- AI? would be cool to embed llama, with a flag (disabled by default)
- Networking? would be cool to at least do basic HTTP, with a flag (disabled by default)


## thanks

See [THANKS](THANKS.md) for acknowledgement and thanks for all the great help & code I received to make this.


## license

See [LICENSE](LICENSE) for licensing information.