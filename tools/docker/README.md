This directory is docker-builders of different carts.

### available containers

- `ghcr.io/notnullgames/null0-cart-c`
- `ghcr.io/notnullgames/null0-cart-quickjs`
- `ghcr.io/notnullgames/null0-cart-nelua`
- `ghcr.io/notnullgames/null0-cart-assemblyscript`
- `ghcr.io/notnullgames/null0-cart-nim`
- `ghcr.io/notnullgames/null0-cart-zig`
- `ghcr.io/notnullgames/null0-cart-go` (tinygo)
- `ghcr.io/notnullgames/null0-cart-wat`
- `ghcr.io/notnullgames/null0-cart-walt`
- `ghcr.io/notnullgames/null0-cart-d` (ldc)
- `ghcr.io/notnullgames/null0-cart-odin`
- `ghcr.io/notnullgames/null0-cart-c3`
- `ghcr.io/notnullgames/null0-cart-onyx`
- `ghcr.io/notnullgames/null0-cart-grain`
- `ghcr.io/notnullgames/null0-cart-rust`
- `ghcr.io/notnullgames/null0-cart-wren` (interpreted)
- `ghcr.io/notnullgames/null0-cart-lua` (interpreted, via GopherLua)
- `ghcr.io/notnullgames/null0-cart-python` (interpreted, via RustPython)
- `ghcr.io/notnullgames/null0-cart-haxe` (via HL/C + wasi-sdk, linux/amd64 only)
- `ghcr.io/notnullgames/null0-cart-zenc` (Zen-C transpiles to C + wasi-sdk, linux/amd64 only)
- `ghcr.io/notnullgames/null0-cart-jik` (Jik transpiles to C + wasi-sdk, linux/amd64 only)
- `ghcr.io/notnullgames/null0-cart-haskell` (wasm32-wasi-ghc, reactor mode)
- `ghcr.io/notnullgames/null0-cart-cyber` (interpreted, via `persist_main`)

### how carts get their bindings

You don't ship the null0 bindings with your cart source. Compiled-language
images bake the generated `null0.*` header/module into the image and the build
script copies it next to your source if it's missing (or adds it to the
include/module path); interpreted-language images bake a `main.wasm`
interpreter instead. (wat and walt are the exception: neither toolchain has an
include mechanism, so their generated files in the image are reference copies
of the import list to paste from.)

### example usage

```sh
# build a cart from main.c (and assets) in current dir, output to ~/Desktop/tester.null0
docker run --rm -v .:/src -v ~/Desktop:/out ghcr.io/notnullgames/null0-cart-c tester
```

## usage in Github CI to build your cart for you

you can easily use it in Github Actions:

```yml
# github/workflows/publish.yml

on: push

jobs:
  build:
    name: Build & Publish Cart
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4
      - name: Build C Cart
        run: docker run -v .:/src -v .:/out ghcr.io/notnullgames/null0-cart-c tester
      - name: Upload cart artifact
        uses: actions/upload-artifact@v4
        with:
          name: tester
          path: tester.null0
```



## building these images

You don't. CI does, on every tag: it builds each image for amd64 and arm64 on
native runners and pushes a multi-arch manifest to
`ghcr.io/notnullgames/null0-cart-<image>`, tagged with the release version and
`latest`. Publishing by hand is what kept the baked bindings out of sync with
the engine, and it eats a lot of disk.

Every push (not just tags) builds each image and then builds that language's
carts *with the image it just built*, so a binding change and the image baking
it can never drift apart.

Every image is self-contained - none is built `FROM` another. nelua, nim,
quickjs and wren used to derive from the C image, which meant they baked
whatever `null0.h` the last *published* C image happened to carry. They now
start from the wasi-sdk image and repeat the small preamble (zip, zipcart.sh,
the toolchain env, `null0.h`) instead. If you change that preamble, change it
in all five.

To build one locally for debugging (`npm run gen` first, so the bindings it
bakes are current):

```sh
npm run docker:cart_c        # builds ghcr.io/notnullgames/null0-cart-c:latest
npm run cart:simple_c        # then builds a cart with it
```
