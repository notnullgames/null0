---
name: add-cart-language
description: Add support for a new cart language to null0 (a generator, bindings, docker build image, and example) or finish support for one that is unchecked in the README. Use when someone wants carts written in a language null0 does not support yet, or asks to "check off" a language.
---

# Add a cart language

Supporting a language means: a generator that writes its bindings from
`api/*.yml`, a docker image that compiles a cart, at least one example, and docs.
Only tick the README box after you have **run** a cart in that language.

## 0. Check it can work at all, before writing anything

The native host runs WAMR's fast interpreter. A toolchain is unusable if it
needs:

- **setjmp/longjmp / wasm exception-handling proposal** - rules out C
  implementations of lua, janet, and most C lisps, and any toolchain that
  emits a `Tag` section (Kotlin/Wasm does by default). WAMR's fast interpreter
  and exception-handling are a hard-incompatible combination at the WAMR
  build-config level (not just untested) - there's no flag to get both.
  Symptom: `WASM module load failed: invalid section id`.
- **wasm GC** - basic struct types work: `WAMR_BUILD_GC 1` in
  `host/cmake/Findwamr.cmake` (native only - the web host just uses the
  browser's own engine, no flag needed there). Verified with a hand-written
  `.wat` using `struct.new`/`struct.get`, and confirmed zero regressions
  across all existing cart languages. But WAMR's GC loader has real gaps:
  it unconditionally rejects any array type with `anyref` elements
  (`wasm_loader.c` in wamr-src, "Not support using anyref in array element
  type") - this sits deep in Kotlin/Wasm's stdlib (even a 2-line `wasm-wasi`
  program hits it) and isn't something cart code can route around. Combined
  with the EH point above (Kotlin needs `-Xwasm-use-traps-instead-of-exceptions`
  just to drop the Tag section), Kotlin/Wasm is still blocked, but by a
  specific WAMR limitation, not "GC" as a category - re-test if WAMR fixes
  that loader gap. dart2wasm is separately ruled out by the JS-glue point
  below: its default output imports a `dart2wasm` namespace and the
  JS-string-builtins proposal, neither servable by a non-JS host.
- **JS glue** to run at all (emscripten-style) - carts must be standalone wasm.

Also check: can it declare an import from a **custom module name** (`null0`),
and can it **export** functions? Without both it cannot be a cart.

Prove it early with a throwaway 10-line program that imports one null0 function
(e.g. `clear`), exports `update`, and runs in the host. Do that before building
the generator - it costs 10 minutes and saves hours.

## 1. Choose the shape

**Compiled** - the cart source becomes `main.wasm`. Copy `tools/gen_cart_c3.js`
and `tools/docker/null0-cart-c3.Dockerfile` as your model.

**Interpreted** - `main.wasm` is an interpreter you bake into the image, and the
cart ships its script. Copy the wren pair (`tools/gen_cart_wren.js`,
`null0-cart-wren.Dockerfile`) for a C VM, or the lua pair for a VM written in
another language. The interpreter reads its script from the cart at startup,
runs it, then forwards host callbacks into it.

## 2. Write the generator

`tools/gen_cart_<lang>.js`, run by `npm run gen:cart_<lang>`:

```js
import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'
const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()
```

Then loop `api` (the groups) and emit one declaration per function. Use lookup
tables keyed by API type name for args and returns - every existing generator
does this, and it makes missing cases obvious.

The ABI rules you must respect (getting these wrong is the #1 bug here):

- struct args (`Color`, `SfxParams`) cross as a **pointer** to the bytes;
- struct returns come back as a **pointer into cart memory** - declare the
  return as a pointer/u32 and dereference. Declaring it by value produces sret
  and silently shifts every argument;
- `T[]` args are followed by a count arg - hide it from the cart author if the
  language has real lists, but still pass it;
- `load`/`update`/`unload` are **not** in `api/callbacks.yml`; emit them yourself
  alongside the input callbacks that are.

Make the output idiomatic, not a literal transcription: use the language's
naming, its struct/record type, and its doc-comment syntax, and carry over the
`description` from the yml. Aim for what a native library in that language would
look like.

## 3. Docker image

`tools/docker/null0-cart-<lang>.Dockerfile` and `tools/docker/build_<lang>.sh`:

- pin the toolchain version with an `ARG`;
- copy the generated bindings into the image (`COPY carts/<lang>/null0.x /usr/local/include/`);
- `build_<lang>.sh` takes one arg (the cart name), copies `/src` to a temp dir,
  supplies the bindings if the cart doesn't ship them, compiles to `main.wasm`,
  and calls `/usr/local/bin/zipcart.sh <name> <dir> /out`;
- compiled languages package only `main.wasm` + `assets/`; interpreted ones
  package the whole source dir plus the baked `main.wasm`.

## 4. Example + wiring

- `carts/<lang>/simple/main.<ext>` - `load`/`update` doing something visible,
  with the other callbacks listed in comments (copy the tone of the existing
  examples).
- `package.json`: `gen:cart_<lang>`, `cart:simple_<lang>`, `docker:cart_<lang>`,
  `docker_publish:cart_<lang>` (the `*` globs pick them up).
- `tools/docker/README.md`: the container list, the local-build list, the
  publish list, and the test line.
- `README.md`: tick the box.
- Optionally a CI job in `.github/workflows/ci.yml` (it currently only covers
  c/js/as/nelua).

## 5. Verify for real

Use the `run-cart` skill: build the image, build `simple_<lang>`, run it in the
host, and print-test the awkward calls (`color_tint`, `measure_image`,
`mouse_position`, `image_alpha_border`, `sfx_generate`, a polygon list). Then
screenshot to confirm it actually draws, and load the cart in the web host too.

A green build is not a passing test - a binding with the wrong struct ABI
compiles fine and returns garbage.
