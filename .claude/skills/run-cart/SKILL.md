---
name: run-cart
description: Build, run, and visually verify a null0 cart or host change - the build/test loop for this repo. Use when asked to test a cart, check that a change works, reproduce a bug, take a screenshot of a cart, run carts in the browser, or debug a cart that crashes or shows nothing.
---

# Run and verify a null0 cart

Never report that something works without doing this loop. The host opens a
window and runs forever, so **always** run it under `timeout`.

## Build the host (once, then incremental)

```sh
cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --target host
# after editing host/src/*: just
cmake --build build --target host
```

## Build a cart

Call docker directly, or use the `npm run cart:*` scripts (they no longer
pass `-it`, so they work without a TTY):

```sh
mkdir -p build/carts
docker run --rm --user $(id -u):$(id -g) \
  -v ./carts/lua/simple:/src -v ./build/carts:/out \
  ghcr.io/notnullgames/null0-cart-lua simple_lua
```

`npm run carts` builds every example cart in parallel; CI builds them
per-language with `npx npm-run-all --parallel 'cart:*_<lang>'`.

If the image is missing: `docker build -f tools/docker/null0-cart-lua.Dockerfile -t ghcr.io/notnullgames/null0-cart-lua .`
(or pull it). **Rebuild the image after `npm run gen`** - images bake a copy of
the generated bindings, so a stale image compiles against the old API.

## Run it

```sh
timeout 8 ./build/host/null0 build/carts/simple_lua.null0 2>&1 | head -20
```

`printf`/`print` from the cart lands on stdout. C carts should `fflush(stdout)`,
or output is lost when the timeout kills the process.

## Check the bindings, not just "it didn't crash"

The fastest real test is a throwaway cart that prints results of the awkward
calls, then comparing against known-good values:

```lua
print(color_tint(RED, BLUE))     -- Color(0, 19, 51, 255)
print(measure_image(SCREEN))     -- 640x480
print(measure_text(FONT_DEFAULT, 'hello', 5))
print(mouse_position())
print(image_alpha_border(new_image(64, 32, RED), 0.5))  -- 0,0,64,32
print(sfx_generate(SFX_COIN))
```

Wrong-looking numbers (shifted bytes, huge values) almost always mean a
struct-passing ABI mistake, not a logic bug - see AGENTS.md "Rule 2".

## Check rendering (macOS)

```sh
(timeout 12 ./build/host/null0 build/carts/simple_lua.null0 >/dev/null 2>&1 &) \
  && sleep 4 && screencapture -x -o /tmp/shot.png
```

Then read `/tmp/shot.png`. The window takes focus while it runs.

## Check the web host too

Cart runtimes can behave differently in the browser (different WASI shim), so
verify both when you touch a runtime or the host:

```sh
npm run host:web                    # needs emscripten
(cd build/carts && ls *.null0 > list.txt)
npx -y live-server --no-browser --port=8111 \
  --mount=/carts:./build/carts --mount=/null0.mjs:./wbuild/host/null0.mjs webroot
```

Open `http://localhost:8111/#simple_lua` - the hash loads a single cart. Cart
`print` output shows in the browser console.

## Error messages and what they mean

| Message                                          | Meaning                                                                                                                        |
| ------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------ |
| `WASM module load failed: invalid section id`    | the wasm uses a proposal WAMR's fast interpreter lacks (exception-handling / GC). The toolchain choice is wrong, not the code. |
| `Exception: cart called proc_exit`               | the cart's runtime exited (a go command-module, or a failed startup). After this the host skips all callbacks.                 |
| `Exception: unreachable` + `undefined_weak:main` | the cart has no `main()`. Harmless for C carts that only define callbacks.                                                     |
| `Could not find file x.png (not found)`          | physfs could not find it in the cart zip or the write dir. Check `assets/` really got packaged.                                |
| nothing drawn, no output                         | `update()` is not exported under that exact name - check the export syntax for the language.                                   |
| host segfaults (SIGSEGV/SIGBUS)                  | a host-side NULL/bad index, usually a bad handle or an ABI mismatch. Reproduce with the smallest possible cart before fixing.  |

## Regression pass

After host or generator changes, re-run one cart per family - they exercise
different toolchains:

```sh
for c in simple_c simple_js simple_wren simple_lua simple_python simple_zig; do
  printf "%-14s " "$c"; timeout 5 ./build/host/null0 build/carts/$c.null0 2>&1 | head -1
done
```
