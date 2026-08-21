The basic idea here is a small game-engine where you make "carts", in whatever language you like, which will run on native, libretro, or web.

[Read the docs](https://notnull.games/null0) to find out more.

### languages

I'd like to support a lot of cart-languages. For these to be considered "complete", they should have a header that exposes all the functions/types in an ergonomic format, at least 1 example, a docker for building carts, and maybe a template-project. If there are any other languages you would like to see, [make an issue](https://github.com/notnullgames/null0/issues/new?labels=language&title=Add%20New%20Language%3A%20), and I will see if I can add it.

**compiled**

- [x] C (wasi-sdk)
- [x] assemblyscript
- [x] nelua
- [x] rust
- [x] nim
- [x] [go](https://tinygo.org/)
- [x] zig
- [x] [walt](https://github.com/ballercat/walt)
- [x] [onyx](https://onyxlang.io)
- [x] [grain](https://grain-lang.org/)
- [x] [D](https://github.com/ldc-developers/ldc)
- [x] [WAT](https://developer.mozilla.org/en-US/docs/WebAssembly/Guides/Understanding_the_text_format)
- [x] [odin](https://odin-lang.org/)
- [x] [c3](https://c3-lang.org/)
- [x] [Haxe](https://haxe.org/) (via HL/C - no try/catch, wasm has no exception-handling)
- [x] Haskell (via [wasm32-wasi-ghc](https://gitlab.haskell.org/haskell-wasm/ghc-wasm-meta), reactor mode)
- [x] [Zen-C](https://github.com/zenc-lang/zenc) (transpiles to C + wasi-sdk)
- [x] [Jik](https://jik-lang.org/) (also compiles to C + wasi-sdk)

**interpreted**

These include the interpretor in `main.wasm`. This is repetitive (like every js cart has a big quickjs `main.wasm` in it) but it makes them more host-agnostic, and reusable. It also means you can tune your interpretor around your game, if you really need to.

- [x] javascript (ES5/6 via QuickJS)
- [x] python (via RustPython)
- [x] lua (via GopherLua)
- [x] [wren](https://wren.io)
- [x] [cyber](https://github.com/fubark/cyber) (via `persist_main` - see AGENTS.md)

**probably will not support**

These have a concrete technical reason they don't work today, found while
investigating - not just "not gotten to yet". Full details in
[the add-cart-language skill](.claude/skills/add-cart-language/SKILL.md).

- **Kotlin/Wasm** - close, but blocked by a real WAMR bug, not by policy. Its
  `wasm-wasi` target is standalone (no JS needed) and compiles to real wasm-GC
  structs, which null0's host now supports. But its stdlib relies on a wasm-GC
  array with `anyref` elements, and WAMR's loader unconditionally rejects that
  ("Not support using anyref in array element type"). It also needs the
  `-Xwasm-use-traps-instead-of-exceptions` compiler flag, since WAMR's fast
  interpreter can't be built with exception-handling support at all (a hard
  incompatibility, not a missing flag). Worth retrying if WAMR fixes the
  anyref-array gap upstream.
- **dart** (dart2wasm) - its default output isn't standalone wasm: it imports
  a `dart2wasm` JS namespace and the JS-string-builtins proposal, both only
  servable by a real JS engine. Same problem as emscripten-style carts.
- **[janet](https://github.com/janet-lang/janet)**, and lisps/scripting
  languages implemented in C generally - they need setjmp/longjmp, which
  needs the wasm exception-handling proposal. See the Kotlin point above:
  WAMR's fast interpreter and exception-handling don't build together at all,
  so no toolchain flag gets around it.
- **R** ([webR](https://github.com/r-wasm/webr)) - built with Emscripten and
  patched against R's source specifically to run inside an Emscripten JS
  runtime in a browser/Node. There's no standalone WASI build; same JS-glue
  problem as dart2wasm.
- **[julia](https://github.com/tshort/WebAssemblyCompiler.jl)** - still
  experimental (type-stable code only, no exception handling, no
  multi-dimensional arrays or pointers), requires wasm-GC for heap
  allocation, and its docs frame it around exchanging objects with
  JavaScript rather than a standalone WASI import model. Worth another look
  once it's less narrow and less JS-shaped.
- **Ada** - GNAT-LLVM does have a `wasm32` target, but the only real runtime
  built on it ([AdaWebPack](https://github.com/godunko/adawebpack)) is
  purpose-built for browser/Web API interop, not a standalone module with
  custom host imports. No evidence anyone ships a bare wasm32 GNAT runtime
  without that JS-facing layer.
- **[spaceship/orbit](https://github.com/SIE-Libraries/orbit)** - not a wasm
  target at all. It's a shell-replacement language that JIT-compiles to
  native code via LLVM for direct POSIX syscalls; no WebAssembly output
  exists or is planned.
- **[wyzer](https://github.com/Wyzer-Lang/wyzer)** - no WebAssembly target
  exists. It's a choreographic distributed-systems language whose whole
  model is compiling one program into separate binaries per network node -
  that doesn't map onto a single cart wasm module even before a wasm
  backend would exist.

## todo/ideas

You can currently do all of these things yourself, or use a library for your language, but I think it would be cool to abstract them into the engine:

- [x] GUI : [microui](https://github.com/notnullgames/pntr_microui). [nuklear_console](https://github.com/RobLoach/nuklear_console) is also very nice for joystick-driven, but API is a bit more complicated. I may switch to this.
- [x] tiled map/sprite
- [ ] physics
- [ ] FFT for audio/radio
- [ ] behind CLI flag: call native program, native files

## thanks

See [THANKS](THANKS.md) for acknowledgement and thanks for all the great help & code I received to make this.

## license

See [LICENSE](LICENSE) for licensing information.
