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
- `API.md` and `webroot/api.json` (from `tools/gen_api_docs.js`)
- `carts/*/null0.*` - every language's bindings (`null0.h`, `null0.zig`, `null0.wren`, `null0.lua`, ...)
- `carts/js/null0.d.ts` + `carts/js/jsconfig.json`, `carts/python/null0.pyi` +
  `carts/python/pyrightconfig.json` - editor-only definitions, the same job
  `carts/lua/null0.lua` does for LuaLS. Not shipped inside a cart (the
  `build_*.sh` scripts delete them).
- `templates/<lang>/` - the starter project published as each `cart_<lang>`
  template repo (from `tools/gen_templates.js`). The
  `Sync cart templates` workflow pushes these out; it is manual, dry-run by
  default, and refuses to run if `templates/` doesn't match the generator, so
  never hand-edit one - fix `gen_templates.js` and regenerate.
- `tools/docker/quickjs-cart.c`, `tools/docker/wren-cart.c`, `tools/docker/lua-cart/main.go`, `tools/docker/python-cart/src/main.rs`, `tools/docker/haxe-cart/null0_shim.c`

`gen` runs in two phases, and it has to: `gen_api_docs.js` and
`gen_templates.js` both go through `tools/lang_docs.js`, which *reads* the
generated bindings to pull each language's real declaration for every API
function. Run them alongside the `gen_cart_*` scripts that write those files
and you race. Phase one is `gen:host` + `gen:cart_*` in parallel, phase two is
`gen:api_docs` then `gen:templates`.

Hand-written host code lives in `host_header.h` (helpers, memory copying,
`add_image`/`add_font`/`add_sound`), `host.h` (the `HOST_FUNCTION` macro),
`fs.c`, `wasi_physfs.h`, `cart_wamr.c`, `cart_emscripten.c`, `main.c`.

### How `host.c` is generated

### Where per-language docs come from

`tools/lang_docs.js` is the one place that knows a language exists as a
*language* rather than as a generator: display name, docker image, cart
filename, callback syntax, gotchas worth telling a human. Its `decls()`
extractors then read the generated binding and pull out the real declaration
line per API function - deliberately, instead of re-deriving 23 sets of type
maps that would drift the moment a generator changed. `webroot/api.json` is
that data plus the yml, published to
https://notnullgames.github.io/null0/api.json so the docs site renders a
per-language API without keeping a copy of any of it.

Adding a language therefore means one entry in `lang_docs.js` too - and its
`decls` regex must find all of them. There's no partial credit here: if the
count doesn't match the API, the docs quietly lose functions.

`gen_host.js` has a `functions` map from null0 API name -> the pntr call that
implements it (`draw_circle: 'pntr_draw_circle_fill(images[0], '`). It builds
each `HOST_FUNCTION` body from the arg/return types in the yml. So to add a host
function you edit **two** places: the yml (signature/doc) and that map (the
implementation). If the pntr call needs something the API doesn't express, add a
`null0_*` wrapper in `host_header.h` and point the map at it.

`HOST_FUNCTION` expands to a WAMR native symbol on native, and an
`EMSCRIPTEN_KEEPALIVE host_*` export on web (the web loader maps `_host_x` ->
import `null0.x`). Adding an API function therefore wires up both hosts for free.

### Adding a *type* (not just a function)

A new function built from types that already exist is free: yml + the
`functions` map + `npm run gen`. A new **enum or struct** costs more, because
every generator carries its own type maps (`retTypes`, `memberTypes`, ...).
`seedTypes()` in `tools/utils.js` fills in whatever a generator hasn't named
explicitly - enums as that language's int, structs as its pointer-to-struct -
so most generators need one line, not one entry per type. What still needs
thought per language: how a struct **member** of a new kind is marshalled, and
what a new type's default value looks like (zig wants `@enumFromInt(0)` and
`undefined`, rust needs `r#type` for a member named `type`).

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
  length) but must still pass it to the host. Arrays are **input-only** - there
  is no way to return one, so bulk data comes back as a struct or not at all.
- **Every struct member is 4 bytes.** `members:` takes scalars only (`i32`,
  `f32`, `u32`, `string`), a bool is an `i32` of 0/1, and an enum member is its
  int value. That keeps one layout for all 23 languages - no per-language
  padding rules, and `Color`'s four `u8`s still pack into 4 bytes.
- **A `string` member is a pointer into cart memory.** `gen_host.js` generates a
  cart-layout mirror of any struct carrying one (`Null0CartTilemapProp`) plus a
  converter that copies each string over with `copy_string_to_cart` - the host's
  own struct keeps `char*`. High-level bindings (lua, wren, js, python, go,
  cyber, haskell) read those pointers into native strings; the thin ones (C,
  zig, rust, odin, ...) hand the cart a `char*` to read itself.
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
- **`environ_get`/`environ_sizes_get` always report zero variables**
  (`wasi_physfs.h`) - carts get no environment, sandboxed like the filesystem.
  A runtime whose libc trusts `$PWD` for `chdir`/`getcwd` (GHC's RTS does, on
  startup) just sees it unset and no-ops, rather than chdir'ing to some real
  host path that isn't the cart's one preopened `/`.
- Writes go to a per-cart pref dir (`fs_set_write_dir` in `fs.c`), mounted last
  so cart files still win. `~/Library/Application Support/<cart>/` on mac,
  `~/.local/share/null0/<cart>/` on linux.

## Rule 4: the GUI wrappers are load-bearing, don't "simplify" them

`null0_gui_checkbox` / `null0_gui_slider` in `host_header.h` look like they do
pointless work. They don't. Three separate bugs live here, and all three only
showed up on the **web** host - the native one worked the whole time, which is
what made them so slow to find.

**microui identifies a control by the address of the state you hand it**, not
by its label. Its own API expects that state to belong to the caller:

```c
mu_checkbox(ctx, "Checkbox 1", &checks[0]);
mu_checkbox(ctx, "Checkbox 2", &checks[1]);
```

so the address is stable frame to frame *and* different per widget for free.
null0's API passes state by value (carts in 23 languages can't all hand out
pointers), so the host has to supply that address:

- A plain local **will not do**. `-sASYNCIFY` unwinds and rewinds the C stack,
  so a local's address moves between frames, the id moves with it, and a click
  never matches the `hover` recorded on the previous frame. The control simply
  never responds in a browser.
- One shared static fixes the address but gives every checkbox the same id.
- What works: a slot per widget, keyed by call order in the frame
  (`gui_checkbox_slots[n]`), reset each frame. Same shape as microui's
  `&checks[0]` / `&checks[1]`. Order-keyed identity is the immediate-mode
  contract - a cart that shows widgets conditionally can shift microui's
  transient hover/focus by one for a frame, which is inherent and harmless
  (the cart owns the values).

**Mouse buttons are queued, not fed on arrival** (`gui_mouse_queue`). Two
reasons. `pntr_microui_update` derives edges as `down && !downLast`, and on the
web those are always gone by the time it looks: browser events land between
frames, and `pntr_app_pre_events` copies `down` into `downLast` at the top of
the frame. And with Asyncify a JS callback can run while the C frame is
suspended, so feeding microui at event time can land after the widgets ran but
before `mu_end()` clears `mouse_pressed`. Draining at a fixed point in the
frame fixes both.

**One transition per frame.** microui resolves a press against the `hover` from
the previous frame, so a press and its release applied in the same widget pass
cancel out. A fast click therefore resolves over two frames.

If you change any of this, test it **in a browser**, not just natively - and
test with more than one checkbox on screen. `carts/c/gui` has several
deliberately, because a single one of each passes even when identity is broken.

## Adding a cart language

There are two shapes. Copy the closest existing one instead of inventing.

**Compiled** (c3, odin, zig, ...): the cart source compiles straight to wasm.
The generator writes a header of `import`-declarations; the cart exports
`load`/`update`/... directly. (haxe is a hybrid: the cart compiles to wasm,
but via the HL/C target, so it also links a trimmed libhl runtime and a
generated C shim from `tools/docker/haxe-cart/`; callbacks are closures
registered through `Null0.onUpdate = ...` rather than exports.) (haskell is
also a hybrid: `wasm32-wasi-ghc` builds a WASI _reactor_ module - a wasm
import's host module name can only be set from C, so every null0 function is
imported through a generated C trampoline, `tools/docker/haskell-cart/imports.c`,
which also runs `hs_init` from a `__attribute__((constructor))` since GHC's
FFI has no `foreign export "name" name` main-wrapping story that fits null0's
repeated-callback model.)

**Interpreted** (js, python, wren, lua): `main.wasm` is an _interpreter_ baked
into the docker image at image-build time; the cart ships its script next to it.
The generator writes the interpreter's glue (bindings + a harness that loads the
script and forwards callbacks). (cyber is a harder case than the others: its
public C API (`libcyber`) has no way to re-invoke a script-defined function
after the initial `cl_vm_eval` - no `cl_call_value`, and the fiber/task-resume
path is commented out in its own source. The fix is `persist_main` (a
`CLEvalConfig` flag documented "for REPL-like behavior"): eval main.cy once
with it, then re-eval a *tiny* snippet like `"update()"` per callback, same
flag - the VM's state, including `load`/`update`/... themselves, persists
across those separate eval calls. Two upstream bugs to know about if you
touch this: `persist_main`'s symbol-copy loop panics unless it skips
`@program_init`/`@program_deinit`, patched at image-build time in
`null0-cart-cyber.Dockerfile` (not filed upstream, per project owner - see
git blame); and `#[bind] global` panics past roughly a few dozen declared at
once (fine as a fn param/return/struct member, fine as one global, not as
~150 of them) - worked around by making null0's constants/enums *plain*
`global NAME TYPE = value` declarations in `carts/cyber/null0.cy` instead of
host-bound ones, since they're fixed at generate time anyway.)

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
4b. `tools/lang_docs.js` - one entry, including a `decls` extractor that finds
   every API function in the binding you just generated. This is what puts the
   language on the website and gives it a `templates/<lang>/` starter project.
5. `tools/docker/README.md` (3 lists + the test line) and the README checkbox.
6. Verify it actually runs (below), then tick the box - not before.

Naming: image `ghcr.io/notnullgames/null0-cart-<lang>`, cart output `<example>_<lang>.null0`.

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
  ghcr.io/notnullgames/null0-cart-lua simple_lua

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

## Releasing

`npm version patch` (or minor/major). The `version` script regenerates and
stages everything first, so the bump and its regenerated output are one commit
- both 0.0.13 and 0.0.14 shipped without that and failed CI's drift check.
Then `git push --follow-tags`.

A normal push only runs the cheap half: the generated-files drift check and
the four host builds. Building 23 images, 23 manifests and 23 cart jobs is ~75
jobs, which is far too much for a one-line change - and the engine is only
ever consumed at a release anyway. If you've touched a Dockerfile, a
generator, or the API and want that checked *before* burning a version number,
run the workflow by hand: Actions -> CI -> Run workflow. It does everything a
tag does except create the release.

The tag does the rest: builds and pushes every cart image to
`ghcr.io/notnullgames/null0-cart-*` (amd64 + arm64, native runners), builds all
the carts and hosts, creates the release, deploys the web player and
`api.json` to pages, and triggers a docs-site rebuild. Nothing is published by
hand.

The docs trigger and the template sync both use one secret, `NULL0_BOT_TOKEN`
(a PAT with repo scope - the built-in `GITHUB_TOKEN` can't reach another
repo). Without it the release still succeeds and the docs job just warns.

Two things a tag does *not* do: sync the `cart_<lang>` template repos (run the
`Sync cart templates` workflow, dry-run first), and make a brand-new GHCR
package public.

A newly created package is private, and there is no API and no org-wide
default that changes that - the org's "Package Creation" setting only controls
which visibilities are *allowed*, and a package inherits a linked repo's
access but explicitly not its visibility. So it is once per package, by hand:

    https://github.com/orgs/notnullgames/packages/container/null0-cart-<image>/settings

then Danger Zone -> Change visibility -> Public. The release job prints all of
those links into its run summary so they're in one place. Only needed the
first time an image is published; after that the setting sticks.

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

- The docker images bake generated headers/glue, so a stale image builds carts
  against an old API. Locally that's on you: `npm run gen`, then
  `npm run docker:cart_<lang>` before `npm run cart:*_<lang>`. CI doesn't have
  the problem - it builds each image and that language's carts in the same job,
  so they always match.
- On the web host, struct/string returns need the cart to export `malloc`
  (and `free` for the gc) - carts without them (wat/walt/grain) can't use
  struct-returning functions on the web.
