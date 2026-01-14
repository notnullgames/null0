This combines ideas from [pntr_app_starter](https://github.com/RobLoach/pntr_app_starter) with [wamr](https://github.com/bytecodealliance/wasm-micro-runtime) to make null0 game-engine (native runtime & libretro core.)

[Read the docs](https://notnullgames.vercel.app/null0) to find out more.

## todo/ideas

- [ ] [ui](https://github.com/rxi/microui)
- [ ] tiled map/sprite support
- [ ] physics
- [ ] share wasm interpretors: all js carts should not have to include quickjs, for example

### languages

I'd like to support a lot of cart-languages. For these to be considered "complete", they should have a header that exposes all the functions/types in an ergonomic format, at least 1 example, and maybe a template-project.

**compiled**

- [X] C
- [X] assemblyscript
- [X] nelua
- [X] rust
- [X] nim
- [ ] [python](https://github.com/wasmerio/py2wasm)
- [ ] [go](https://tinygo.org/)
- [ ] zig
- [ ] [walt](https://github.com/ballercat/walt)
- [ ] [COBOL](https://github.com/cloudflare/cobweb)
- [ ] [onyx](https://onyxlang.io)
- [ ] [grain](https://grain-lang.org/)
- [ ] [never](https://github.com/never-lang/never)
- [ ] [lisp](https://github.com/mbrock/wisp)
- [ ] Kotlin
- [ ] dart
- [ ] [D](https://github.com/ldc-developers/ldc)
- [ ] R
- [ ] [julia](https://github.com/tshort/WebAssemblyCompiler.jl)
- [ ] Haskell
- [ ] [WAT](https://developer.mozilla.org/en-US/docs/WebAssembly/Guides/Understanding_the_text_format)
- [ ] Ada
- [ ] [spaceship/orbit](https://github.com/SIE-Libraries/orbit)
- [ ] [Zen-C](https://github.com/z-libs/Zen-C)

**interpreted**

- [X] javascript
- [ ] python
- [ ] lua
- [ ] [wren](https://wren.io)
- [ ] [lisp](https://github.com/janet-lang/janet)
- [ ] [cyber](https://github.com/fubark/cyber)


**config graph**

These can sort of define functions, as a kind of graph. Think of it as an interpretor.

- [ ] [KDL](https://kdl.dev/)
- [ ] YAML
- [ ] JSON


## thanks

See [THANKS](THANKS.md) for acknowledgement and thanks for all the great help & code I received to make this.

## license

See [LICENSE](LICENSE) for licensing information.
