The basic idea here is a small game-engine where you make "carts", in whatever language you like, which will run on native, libretro, or web.

[Read the docs](https://notnull.games/null0) to find out more.

## todo/ideas

You can currently do all of these things yourself, or use a library for your language, but I think it would be cool to abstract them into the engine:

- [ ] [ui](https://github.com/rxi/microui)
- [ ] tiled map/sprite
- [ ] physics

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
