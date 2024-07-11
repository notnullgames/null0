This combines ideas from [pntr_app_starter](https://github.com/RobLoach/pntr_app_starter) with [wamr](https://github.com/bytecodealliance/wasm-micro-runtime) to make null0 game-engine (native runtime & libretro core.)

You can see a simple web-demo [here](https://notnullgames.github.io/null0) or [read the docs](https://notnullgames.vercel.app/null0).

## native

After you have the `null0` runtime built or [downloaded](https://github.com/notnullgames/null0/releases), you can run it like this:

```sh
./null0 yourcart.null0
```

## web

You don't need to build anything to use null0 in your own page.

### web-component

This is easiest, and will insert your cart as a running game.

Put this anywhere in your page:

```html
<script type="module" src="https://notnullgames.github.io/null0/null0_wc.js"></script>
```

Now, you can use it like this:

```html
<null0-cart src="https://notnullgames.github.io/null0/cart/input.null0"></null0-cart>
```

You can use any cart-url in `src`.

### js

You can also use it without a web-componment, if you want:

```html
<script type="module">
import { setupCart } from 'https://notnullgames.github.io/null0/null0.js'
const {host, cart} = await setupCart('mycart.null0')
</script>
```

2nd param is `canvas`, if you want to force it to use your existing canvas.

## building

In order to build carts, you will need the [wasi-sdk](https://github.com/WebAssembly/wasi-sdk/releases) installed. You can set `WASI_SDK_PREFIX` to the location, if it's not `/opt/wasi-sdk`

Common tasks have been wrapped with npm scripts:

```sh
npm run build:site  # build website in docs
npm run start       # run local (reloading) dev-server
npm run clean       # delete all built files

npm run build:carts # build just the demo-carts
npm run build:host  # build just the native host
npm run build:web   # build just the web-host
npm run build:retro # build just the libretro core that can load null0 files
```

You will need cmake, ninja & emscripten installed.

### more on cmake

I like ninja, in the tasks above, because it builds a bit faster, but it's optional, if yuou use cmake directly.

Essentially, there are 2 options:

- `CARTS` - Should carts be built? 
- `HOST_TYPE` - What sort of host are you building (OFF/WEB/RAYLIB/SDL/RETRO)

You can only build 1 `HOST_TYPE` at a time. `CARTS` can be paired with any `HOST_TYPE`, but not `WEB`, and `WEB` requires emscripten (and should probably be built in a seperate root.)

#### examples

There are 2 steps: configure & build.

```sh
# configure without ninja (plain make) build only carts
cmake -B build -DCARTS=ON -DHOST_TYPE=OFF

# configure for ninja, build only carts
cmake -GNinja -B build -DCARTS=ON -DHOST_TYPE=OFF

# configure for ninja, build only raylib host
cmake -GNinja -B build -DCARTS=OFF -DHOST_TYPE=RAYLIB

# configure for ninja, build only SDL host
cmake -GNinja -B build -DCARTS=OFF -DHOST_TYPE=SDL

# configure for ninja, build only libretro-core
cmake -GNinja -B build -DCARTS=OFF -DHOST_TYPE=RETRO

# configure for ninja, build only web-host (in wbuild/)
emcmake cmake -GNinja -B wbuild

# after configure, build build
cmake --build build

# after configure, build wbuild (for web)
cmake --build wbuild
```

## todo

### immediate

- generate headers for other cart-languages (not just C)
- update website with docs generated from the api defs
- add web-component & carts from this repo's gh-pages to main-docs
- libretro core
- switch sfx to use pntr_sfx. it's currently broke on web

#### carts

- rework flappybird assets. There are some [nice ones](https://flappybird.io/). [this](https://studio.code.org/flappy) has nice backgrounds. nice ideas [here](https://youtu.be/3IdOCxHGMIo?list=PLhQjrBD2T383Vx9-4vJYFsJbvZ_D17Qzh)


### longterm

- test everything, maybe a full battery of wasm-side tests (every single function)
- add TTS libs & API functions
- setup a ESP32 host
- AI? would be cool to embed llama, with a flag (disabled by default)
- Networking? would be cool to at least do basic HTTP, with a flag (disabled by default)
- standalone DLL for iwasm
- add complete WASI support to hosts (instead of my IO wrappers, etc)
- more games! maybe have a game-contest or something.
- web-based editor/compiler - I think no installation would be really nice, anmd I could setup editor-environments for specific languages, and even add other editors (like basic tilemap/sprite stuff.)

## thanks

See [THANKS](THANKS.md) for acknowledgement and thanks for all the great help & code I received to make this.


## license

See [LICENSE](LICENSE) for licensing information.
