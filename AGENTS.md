# AGENTS.md

Notes for LLM agents working on null0. Read this before changing anything: most of
the mistakes people make here come from not knowing which files are generated,
and from the wasm ABI rules the whole engine is built on.

You can find skills in `.claude/skills/`.

## What this is

null0 is a small fantasy console. A game is a **cart** (`.null0` = a zip with
`main.wasm` at the root, plus assets). The **host** loads the cart's wasm, gives
it the null0 API as wasm imports, and calls exported callbacks (`update`,
`keyDown`, ...) as the game runs. Carts can be written in 18 languages, so most
work here is "teach another language to talk to the same ABI".

Hosts: native (raylib + WAMR) and web (emscripten + browser WebAssembly). The
README mentions libretro, but there is no libretro code in the tree yet.

## Repo map

| Path                | What it is                                                                                          |
| ------------------- | --------------------------------------------------------------------------------------------------- |
| `api/*.yml`         | **The source of truth.** Every function, type, constant, callback.                                  |
| `tools/gen_*.js`    | Generators. Each reads `api/*.yml` and writes bindings/glue.                                        |
| `tools/utils.js`    | `getApi()` - parses the yml into `{ enums, structs, scalars, constants, callbacks, ...apiGroups }`. |
| `tools/docker/`     | One Dockerfile + one `build_<lang>.sh` per language, plus baked interpreter sources.                |
| `carts/<lang>/`     | The language's null0 header/bindings + example carts.                                               |
| `host/src/`         | The engine. Mostly hand-written; `host.c` is generated.                                             |
| `webroot/`          | The web player (`null0.js` loads the emscripten host, then the cart).                               |
| `build/`, `wbuild/` | Native and web build output (gitignored).                                                           |

## Rule 1: know what is generated

Running `npm run gen` regenerates all of these. **Never hand-edit them** - your
change will vanish, and reviewers will assume the generator produced it:

- `host/src/host.c` (from `tools/gen_host.js`)
- `API.md` (from `tools/gen_api_docs.js`)
- `carts/*/null0.*` - every language's bindings (`null0.h`, `null0.zig`, `null0.wren`, `null0.lua`, ...)
- `tools/docker/quickjs-cart.c`, `tools/docker/wren-cart.c`, `tools/docker/lua-cart/main.go`, `tools/docker/python-cart/src/main.rs`

Hand-written host code lives in `host_header.h` (helpers, memory copying,
`add_image`/`add_font`/`add_sound`), `host.h` (the `HOST_FUNCTION` macro),
`fs.c`, `wasi_physfs.h`, `cart_wamr.c`, `cart_emscripten.c`, `main.c`.

### How `host.c` is generated

`gen_host.js` has a `functions` map from null0 API name -> the pntr call that
implements it (`draw_circle: 'pntr_draw_circle_fill(images[0], '`). It builds
each `HOST_FUNCTION` body from the arg/return types in the yml. So to add a host
function you edit **two** places: the yml (signature/doc) and that map (the
implementation). If the pntr call needs something the API doesn't express, add a
`null0_*` wrapper in `host_header.h` and point the map at it.

`HOST_FUNCTION` expands to a WAMR native symbol on native, and an
`EMSCRIPTEN_KEEPALIVE host_*` export on web (the web loader maps `_host_x` ->
import `null0.x`). Adding an API function therefore wires up both hosts for free.

### The `api/*.yml` schema

```yml
draw_circle:
  args: # ordered; names matter (they become param names)
    centerX: i32
    centerY: i32
    radius: i32
    color: Color
  returns: Image # omit for void
  description: Draw a filled circle on the screen.
```

`api/types.yml` holds scalars, `enums:` (Key, GamepadButton, ...) and `members:`
structs (Color, Vector, Rectangle, Dimensions, SfxParams). `api/constants.yml`
holds the colors. `api/callbacks.yml` describes the input callbacks the _cart_ exports - note it
does **not** list `load`/`update`/`unload`, so a generator has to emit those
three itself.

After **any** yml change: `npm run gen`, then rebuild the docker images for the
languages that bake generated glue (quickjs, wren, lua, python) - the images
carry a copy of the header/glue from build time.

## Rule 2: the wasm ABI, which is where the bugs are

The cart and host talk in the wasm C ABI. Get these wrong and you get silent
garbage or a SIGSEGV in the host:

- **Structs are passed by pointer, not by value.** A `Color` arg is a _cart
  address_ of 4 bytes; the host does `copy_color_from_cart(ptr)`. In C/Rust/Go
  you write it as a by-value struct and the compiler passes the pointer for you.
  In a hand-written binding (wren, lua, wat, walt) you must pass an address.
- **Struct returns come back as a cart pointer too.** The host allocates in cart
  memory (`cart_malloc`) and returns the address, so the binding must declare the
  return as a pointer/u32 and dereference it. Declaring `-> Color` or
  `-> Rectangle` by value produces sret and shifts every argument - this exact
  bug shipped in the C, JS and python bindings and crashed the host.
- **`T[]` args are followed by a count arg** in the yml (`points: Vector[]`,
  `numPoints: i32`). High-level bindings hide the count (the list knows its own
  length) but must still pass it to the host.
- **Struct returns are freed after the callback.** Everything the host copies
  into cart memory (struct/string returns) is tracked and freed by `cart_gc()`
  when the current cart callback (`load`/`update`/event) returns. A binding
  must copy out what it needs during the call and never stash the pointer.
- Handles (`Image`, `Font`, `Sound`) are `u32` indexes into host-side vectors.
  `0` is the screen / default font. Handles are bounds-checked: an out-of-range
  handle logs a warning and the call is skipped (returns 0) rather than
  crashing the host.

## Rule 3: what the host runtime can and cannot do

The native host runs WAMR's **fast interpreter**, with these consequences:

- **No exception-handling proposal, and it can't be added.** `WAMR_BUILD_GC`
  and fast-interp fine, but `WAMR_BUILD_EXCE_HANDLING` + fast-interp is a
  build-level error in WAMR itself (`unsupported_combination.cmake`) - not
  just "not turned on". No `setjmp`/`longjmp`, and any C VM that needs it
  (Lua 5.4, Janet, s7...) _cannot_ be a cart runtime: the module fails to load
  with `WASM module load failed: invalid section id`. This is why lua is
  GopherLua (go) and not C lua.
- **wasm GC proposal is supported** (`WAMR_BUILD_GC 1` in
  `host/cmake/Findwamr.cmake`, native only - the web host runs carts through
  the browser's own engine, which already has GC). Verified with a
  hand-written `.wat` using `struct.new`/`struct.get`. Kotlin/Wasm's
  `wasm-wasi` target is standalone and GC-based but still blocked: its stdlib
  hits a real WAMR loader gap (rejects any GC array with `anyref` elements),
  and it needs `-Xwasm-use-traps-instead-of-exceptions` to dodge the EH point
  above. dart2wasm is blocked separately - its default output isn't
  standalone wasm (see below). Both listed in README's "probably will not
  support".
- **`proc_exit` ends the cart.** After it, the host skips all callbacks
  (`wasi_cart_has_exited`). A go command-module calls `proc_exit` when `main`
  returns, which is why the lua runtime is built as a wasi _reactor_
  (`-buildmode=c-shared`, exports `_initialize`). The host calls `_start`, else
  `_initialize`, else `main`, then `load`.
- **WASI is a hand-written subset** (`host/src/wasi_physfs.h`) backed by physfs.
  One preopen, `/`, and **no working directory** - go's `os.ReadFile("main.lua")`
  fails, `os.ReadFile("/main.lua")` works. wasi-libc's relative paths do work.
- Writes go to a per-cart pref dir (`fs_set_write_dir` in `fs.c`), mounted last
  so cart files still win. `~/Library/Application Support/<cart>/` on mac,
  `~/.local/share/null0/<cart>/` on linux.

## Adding a cart language

There are two shapes. Copy the closest existing one instead of inventing.

**Compiled** (c3, odin, zig, ...): the cart source compiles straight to wasm.
The generator writes a header of `import`-declarations; the cart exports
`load`/`update`/... directly.

**Interpreted** (js, python, wren, lua): `main.wasm` is an _interpreter_ baked
into the docker image at image-build time; the cart ships its script next to it.
The generator writes the interpreter's glue (bindings + a harness that loads the
script and forwards callbacks).

Checklist:

1. `tools/gen_cart_<lang>.js` - writes `carts/<lang>/null0.<ext>` and, for an
   interpreted language, the interpreter glue in `tools/docker/`.
2. `carts/<lang>/simple/` - at least one example. Mirror `carts/lua/simple` in
   tone: show `load`/`update`, list the other callbacks in comments.
3. `tools/docker/null0-cart-<lang>.Dockerfile` + `tools/docker/build_<lang>.sh`
   (copy `/src` -> tmp, build, then `zipcart.sh <name> <dir> /out`). Pin the
   toolchain version with an `ARG`. Bake the generated bindings into the image
   (`COPY carts/<lang>/null0.* /usr/local/include/`) and have `build_<lang>.sh`
   copy them next to the source when the user didn't ship their own, so a cart
   project is self-contained - for interpreted languages the baked `main.wasm`
   plays this role. (wat/walt can't: no include mechanism, their generated
   files are reference copies of the import list.)
4. `package.json`: `gen:cart_<lang>`, `cart:simple_<lang>`, `docker:cart_<lang>`,
   `docker_publish:cart_<lang>` - the `*` globs in `gen`/`carts`/`docker` pick
   them up automatically.
5. `tools/docker/README.md` (3 lists + the test line) and the README checkbox.
6. Verify it actually runs (below), then tick the box - not before.

Naming: image `konsumer/null0-cart-<lang>`, cart output `<example>_<lang>.null0`.

Ergonomics matter more than a 1:1 mapping. Use the language's idioms (wren gets
classes and getters, lua gets plain globals and tables, go gets `CamelCase`), and
generate doc-comments from the yml `description`.

## How to verify (do this, don't skip it)

```sh
# 1. build the native host once (incremental after that)
cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --target host

# 2. build a cart. call docker directly, or use `npm run cart:simple_lua`
#    (the scripts no longer use `-it`, so they work without a TTY)
docker run --rm --user $(id -u):$(id -g) \
  -v ./carts/lua/simple:/src -v ./build/carts:/out \
  konsumer/null0-cart-lua simple_lua

# 3. run it. it opens a window, so always use a timeout
timeout 8 ./build/host/null0 build/carts/simple_lua.null0
```

Print-based checks are the fastest way to test bindings: write a throwaway cart
that calls the awkward functions (`color_tint`, `measure_text`, `mouse_position`,
`image_alpha_border`, `sfx_generate`, a polygon list) and prints the results.
Correct values look like `Color(0, 19, 51, 255)`, `Dimensions(640, 480)`.

To check _rendering_, screenshot the window (mac): run the host in the
background, `sleep 4`, then `screencapture -x -o shot.png` and read the image.

To check the **web** host:

```sh
npm run host:web   # needs emscripten
(cd build/carts && ls *.null0 > list.txt)
npx -y live-server --no-browser --port=8111 \
  --mount=/carts:./build/carts --mount=/null0.mjs:./wbuild/host/null0.mjs webroot
# then open http://localhost:8111/#simple_lua - the hash loads one cart
```

Gotchas while testing: C carts need `fflush(stdout)` or output is lost when the
timeout kills the process; a cart with no `main()` logs a harmless
`undefined_weak:main` trap.

## Conventions

- Formatting: `.clang-format` for C, `.prettierrc` for JS (2 spaces, no
  semicolons, single quotes), `gofmt` for go. Note prettier's `printWidth: 9999`
  will collapse a generator's multi-line string arrays into one giant line -
  keep those readable and don't reformat files you didn't otherwise touch.
- Generated code should look like a human wrote it: comments from the yml
  descriptions, the target language's idioms, no `TODO` noise.
- Commit messages: one line, <=40 chars, no AI attribution. Only commit when
  asked.
- Don't tick a README checkbox for a language you have not run.

## Known rough edges

- The docker images bake generated headers/glue, so a stale image silently builds
  carts against an old API. Rebuild after `npm run gen`. CI builds carts with
  the _published_ images, so publish them before tagging a release that changed
  the API.
- On the web host, struct/string returns need the cart to export `malloc`
  (and `free` for the gc) - carts without them (wat/walt/grain) can't use
  struct-returning functions on the web.
