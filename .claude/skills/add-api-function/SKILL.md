---
name: add-api-function
description: Add, change, or remove a function, type, enum, or constant in the null0 API (api/*.yml) and propagate it to the host and every supported language's bindings. Use when someone wants a new engine feature exposed to carts (drawing, sound, input, tilemap, physics, ui) or wants to change an existing API signature.
---

# Change the null0 API

`api/*.yml` is the single source of truth. Everything else - the host
implementation, `API.md`, and every language's bindings - is generated from it.
Editing a generated file by hand is always wrong.

## 1. Describe it in the yml

Pick the group file (`ls api/*.yml` for the current list - each file is a
group, so a new file becomes a new API group automatically):

```yml
draw_star:
  args: # ordered, names become parameter names everywhere
    centerX: i32
    centerY: i32
    radius: i32
    points: i32
    color: Color
  returns: void # omit for void
  description: Draw a filled star on the screen.
```

Only use types that already exist in `api/types.yml` - read it rather than
trusting a remembered list, it grows over time (scalars, resource handles like
`Image`/`Tilemap`, `Vector[]`-style arrays, structs, enums). Every generator
(every `tools/gen_cart_*.js`, plus `gen_host.js` and `gen_api_docs.js`) has a
lookup table keyed by these names, so a **new type means editing all of
them** - avoid it unless it's truly needed.

An array arg is always followed by its count: `points: Vector[]` then
`numPoints: i32`. Generators for high-level languages hide the count.

The `description` becomes the doc-comment in every language and the text in
`API.md`, so write it as a full sentence.

## 2. Implement it in the host

`host/src/host.c` is generated, so the implementation goes in the `functions`
map in `tools/gen_host.js`:

```js
draw_star: 'pntr_draw_star_fill(images[0], ',
```

The value is the literal call prefix; the generator appends the converted args.
Conventions: `images[0]` is the screen for "draw on screen" functions; the
`_on_image` variants take the destination handle instead. If pntr has no such
function, write a `null0_draw_star(...)` helper in `host/src/host_header.h` and
point the map at that.

The generator handles the conversions (`Color` ->
`copy_color_from_cart`, `string` -> `copy_string_from_cart` + `free`, handles ->
`images[]`/`fonts[]`/`sounds[]`, struct returns -> `copy_memory_to_cart`). If
your function needs something it can't express, add the helper host-side rather
than special-casing the generator.

## 3. Regenerate and rebuild

```sh
npm run gen                                   # host.c, API.md, all bindings
cmake --build build --target host             # native host
docker build -f tools/docker/null0-cart-c.Dockerfile -t ghcr.io/notnullgames/null0-cart-c .
```

Images bake the generated headers/glue, so **rebuild every image you intend to
test with**. The interpreted runtimes (`quickjs`, `wren`, `lua`, `python`) bake
generated glue and must be rebuilt for the new function to exist at all.

## 4. Verify in at least two languages

Test C (closest to the ABI) and one high-level language (lua or wren, which
exercise the struct conversions). Use the `run-cart` skill. Print the result and
check the values are sane - a struct return that is off by a byte means the
binding declared it by value instead of as a pointer (AGENTS.md, Rule 2).

## 5. Finish

- `git status` should show the yml, `tools/gen_host.js`, and generated files -
  nothing else.
- If a generator needed a fix, fix the **generator**, then re-run `npm run gen`.
- An empty or half-finished yml file will add empty sections to every binding on
  the next `npm run gen` - don't leave one lying around.
