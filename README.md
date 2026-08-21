The basic idea here is a small game-engine where you make "carts", in whatever language you like, which will run on native, libretro, or web.

[Read the docs](https://notnull.games/null0) to find out more.

### languages

I'd like to support a lot of cart-languages. For these to be considered "complete", they should have a header that exposes all the functions/types in an ergonomic format, at least 1 example, a docker for building carts, and maybe a template-project.

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
- [ ] R
- [ ] [julia](https://github.com/tshort/WebAssemblyCompiler.jl)
- [ ] Haskell
- [ ] Ada
- [ ] [spaceship/orbit](https://github.com/SIE-Libraries/orbit)
- [ ] [Zen-C](https://github.com/z-libs/Zen-C)
- [ ] [Haxe](https://github.com/back2dos/wasmix)
- [ ] [Jik](https://jik-lang.org/)
- [ ] [wyzer](https://github.com/Wyzer-Lang/wyzer)

**interpreted**

- [x] javascript (ESM, via QuickJS)
- [x] python (interpreted, via RustPython)
- [x] lua (interpreted, via GopherLua)
- [x] [wren](https://wren.io)
- [ ] [cyber](https://github.com/fubark/cyber)

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
