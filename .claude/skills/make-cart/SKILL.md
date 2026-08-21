---
name: make-cart
description: Create or extend a null0 game cart in any supported language (C, rust, zig, go, lua, wren, javascript, python, nim, nelua, odin, c3, D, onyx, grain, assemblyscript, WAT, walt). Use when someone wants to start a game, add gameplay to an existing cart, or asks how to draw/play sound/read input from their language of choice.
---

# Make a null0 cart

A cart is a zip named `<name>.null0` containing `main.wasm` (+ optional
`assets/`). You never make that zip by hand - a docker image for your language
compiles and packages it.

## 1. Pick the language, then copy its example

Every supported language has a working example in `carts/<lang>/`. **Read it
first** - it shows the exact export syntax for that language, which is the part
people get wrong. `references/languages.md` in this skill has the table:
directory, source filename, docker image, and how callbacks are declared.

Start a new cart by copying an example into its own directory:

```sh
cp -R carts/lua/simple ~/mygame     # or carts/zig/simple, carts/zig/simple, ...
```

The cart directory holds **only your source** (`main.lua`, `main.c`, ...) plus
an optional `assets/` dir. Do not copy `null0.h` / `null0.lua` / `null0.zig`
into it - the build image supplies the bindings automatically.

## 2. Write the game

The API is identical in every language; only the spelling changes. `API.md` (in
the repo root) documents every function, and `carts/<lang>/null0.*` is the
generated binding for your language - grep it for a function name to see the
exact signature you can call.

Callbacks the host calls, all optional:

| Callback                                                  | When                |
| --------------------------------------------------------- | ------------------- |
| `load()`                                                  | once, at startup    |
| `update()`                                                | every frame (60fps) |
| `unload()`                                                | when the cart stops |
| `buttonDown(button, player)` / `buttonUp(button, player)` | mapped gamepad/keys |
| `keyDown(key)` / `keyUp(key)`                             | raw keys            |
| `mouseDown(button)` / `mouseUp(button)`                   | mouse buttons       |
| `mouseMoved(x, y)`                                        | mouse motion        |

Drawing happens in `update()`: `clear(BLUE)` then draw. The screen is image `0`
(`SCREEN`), the built-in font is `0` (`FONT_DEFAULT`).

Assets: put files in `assets/` and load them by relative path -
`load_image("assets/logo.png")`, `load_sound("assets/song.ogg")`,
`load_font_ttf("assets/font.ttf", 20)`. That path is resolved by the host inside
the cart zip, so it works the same on native and web. Add a `.cartignore`
(gitignore syntax) to keep files out of the packaged cart.

## 3. Build and run it

```sh
# build: <src dir> -> <out dir>/<name>.null0
mkdir -p ~/mygame/out
docker run --rm --user $(id -u):$(id -g) \
  -v ~/mygame:/src -v ~/mygame/out:/out \
  konsumer/null0-cart-lua mygame

# run it (opens a window)
./build/host/null0 ~/mygame/out/mygame.null0
```

If `./build/host/null0` does not exist yet:
`cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --target host`

Use the `run-cart` skill for the full build/test/screenshot loop, including how
to test in a browser and what the common error messages mean.

## Rules of thumb

- Struct-ish values (Color, Vector, Rectangle, Dimensions, SfxParams) are
  whatever is natural in that language: a struct in C/rust/zig, a table in lua,
  a dict in python, an object in JS, a class in wren.
- Colors have named constants (`BLUE`, `RAYWHITE`, ...) in every language.
- Functions that return a struct (`color_tint`, `measure_text`) hand you a
  pointer into cart memory that the host frees when the current callback
  returns - copy the fields out, never stash the pointer across frames.
- If a cart prints nothing, remember output is buffered - C carts should
  `fflush(stdout)` after `printf`.
- Never claim a cart works without running it.
