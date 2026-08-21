This directory is docker-builders of different carts.

### available containers

- `konsumer/null0-cart-c`
- `konsumer/null0-cart-quickjs`
- `konsumer/null0-cart-nelua`
- `konsumer/null0-cart-assemblyscript`
- `konsumer/null0-cart-nim`
- `konsumer/null0-cart-zig`
- `konsumer/null0-cart-go` (tinygo)
- `konsumer/null0-cart-wat`
- `konsumer/null0-cart-walt`
- `konsumer/null0-cart-d` (ldc)
- `konsumer/null0-cart-odin`
- `konsumer/null0-cart-c3`
- `konsumer/null0-cart-onyx`
- `konsumer/null0-cart-grain`
- `konsumer/null0-cart-rust`
- `konsumer/null0-cart-wren` (interpreted)
- `konsumer/null0-cart-lua` (interpreted, via GopherLua)
- `konsumer/null0-cart-python` (interpreted, via RustPython)
- `konsumer/null0-cart-haxe` (via HL/C + wasi-sdk, linux/amd64 only)
- `konsumer/null0-cart-zenc` (Zen-C transpiles to C + wasi-sdk, linux/amd64 only)
- `konsumer/null0-cart-jik` (Jik transpiles to C + wasi-sdk, linux/amd64 only)
- `konsumer/null0-cart-haskell` (wasm32-wasi-ghc, reactor mode)
- `konsumer/null0-cart-cyber` (interpreted, via `persist_main`)

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
docker run -it -v .:/src -v ~/Desktop:/out konsumer/null0-cart-c tester
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
        run: docker run -v .:/src -v .:/out konsumer/null0-cart-c tester
      - name: Upload cart artifact
        uses: actions/upload-artifact@v4
        with:
          name: tester
          path: tester.null0
```



This is really just notes for me:

```sh
# 1-time setup
docker buildx create --name multiarch --driver docker-container --bootstrap
docker buildx use multiarch
docker run --privileged --rm tonistiigi/binfmt --install all

# generate headers (needed on API change)
npm i
npm run gen

# just local use (fast, no push)
docker build -t konsumer/null0-cart-c . -f tools/docker/null0-cart-c.Dockerfile
docker build -t konsumer/null0-cart-quickjs . -f tools/docker/null0-cart-quickjs.Dockerfile
docker build -t konsumer/null0-cart-assemblyscript . -f tools/docker/null0-cart-assemblyscript.Dockerfile
docker build -t konsumer/null0-cart-nelua . -f tools/docker/null0-cart-nelua.Dockerfile
docker build -t konsumer/null0-cart-nim . -f tools/docker/null0-cart-nim.Dockerfile
docker build -t konsumer/null0-cart-zig . -f tools/docker/null0-cart-zig.Dockerfile
docker build -t konsumer/null0-cart-go . -f tools/docker/null0-cart-go.Dockerfile
docker build -t konsumer/null0-cart-wat . -f tools/docker/null0-cart-wat.Dockerfile
docker build -t konsumer/null0-cart-walt . -f tools/docker/null0-cart-walt.Dockerfile
docker build -t konsumer/null0-cart-d . -f tools/docker/null0-cart-d.Dockerfile
docker build -t konsumer/null0-cart-odin . -f tools/docker/null0-cart-odin.Dockerfile
docker build -t konsumer/null0-cart-c3 . -f tools/docker/null0-cart-c3.Dockerfile
docker build -t konsumer/null0-cart-onyx . -f tools/docker/null0-cart-onyx.Dockerfile
docker build -t konsumer/null0-cart-grain . -f tools/docker/null0-cart-grain.Dockerfile
docker build -t konsumer/null0-cart-rust . -f tools/docker/null0-cart-rust.Dockerfile
docker build -t konsumer/null0-cart-wren . -f tools/docker/null0-cart-wren.Dockerfile
docker build -t konsumer/null0-cart-lua . -f tools/docker/null0-cart-lua.Dockerfile
docker build -t konsumer/null0-cart-python . -f tools/docker/null0-cart-python.Dockerfile
docker build --platform linux/amd64 -t konsumer/null0-cart-haxe . -f tools/docker/null0-cart-haxe.Dockerfile
docker build --platform linux/amd64 -t konsumer/null0-cart-zenc . -f tools/docker/null0-cart-zenc.Dockerfile
docker build --platform linux/amd64 -t konsumer/null0-cart-jik . -f tools/docker/null0-cart-jik.Dockerfile

# build & publish (needed on API change)
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-c . -f tools/docker/null0-cart-c.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-quickjs . -f tools/docker/null0-cart-quickjs.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-assemblyscript . -f tools/docker/null0-cart-assemblyscript.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-nelua . -f tools/docker/null0-cart-nelua.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-nim . -f tools/docker/null0-cart-nim.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-zig . -f tools/docker/null0-cart-zig.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-go . -f tools/docker/null0-cart-go.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-wat . -f tools/docker/null0-cart-wat.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-walt . -f tools/docker/null0-cart-walt.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-d . -f tools/docker/null0-cart-d.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-odin . -f tools/docker/null0-cart-odin.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-c3 . -f tools/docker/null0-cart-c3.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-onyx . -f tools/docker/null0-cart-onyx.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-grain . -f tools/docker/null0-cart-grain.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-rust . -f tools/docker/null0-cart-rust.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-wren . -f tools/docker/null0-cart-wren.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-lua . -f tools/docker/null0-cart-lua.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-python . -f tools/docker/null0-cart-python.Dockerfile
docker buildx build --push --platform linux/amd64 -t konsumer/null0-cart-haxe . -f tools/docker/null0-cart-haxe.Dockerfile
docker buildx build --push --platform linux/amd64 -t konsumer/null0-cart-zenc . -f tools/docker/null0-cart-zenc.Dockerfile
docker buildx build --push --platform linux/amd64 -t konsumer/null0-cart-jik . -f tools/docker/null0-cart-jik.Dockerfile

# test
docker run -it -v ./carts/c/colorbars:/src -v ./build/carts:/out konsumer/null0-cart-c colorbars_c
docker run -it -v ./carts/c/example:/src -v ./build/carts:/out konsumer/null0-cart-c example_c
docker run -it -v ./carts/c/gradient:/src -v ./build/carts:/out konsumer/null0-cart-c gradient_c
docker run -it -v ./carts/c/input:/src -v ./build/carts:/out konsumer/null0-cart-c input_c
docker run -it -v ./carts/c/sfx:/src -v ./build/carts:/out konsumer/null0-cart-c sfx_c
docker run -it -v ./carts/c/speak:/src -v ./build/carts:/out konsumer/null0-cart-c speak_c
docker run -it -v ./carts/c/wasi_demo:/src -v ./build/carts:/out konsumer/null0-cart-c wasi_demo_c

docker run -it -v ./carts/js/demo:/src -v ./build/carts:/out konsumer/null0-cart-quickjs demo_js
docker run -it -v ./carts/js/input:/src -v ./build/carts:/out konsumer/null0-cart-quickjs input_js

docker run -it -v ./carts/as/simple:/src -v ./build/carts:/out konsumer/null0-cart-assemblyscript simple_as

docker run -it -v ./carts/nelua/basic:/src -v ./build/carts:/out konsumer/null0-cart-nelua basic_nelua
docker run -it -v ./carts/nelua/colorbars:/src -v ./build/carts:/out konsumer/null0-cart-nelua colorbars_nelua

docker run -it -v ./carts/nim/simple:/src -v ./build/carts:/out konsumer/null0-cart-nim simple_nim

docker run -it -v ./carts/zig/simple:/src -v ./build/carts:/out konsumer/null0-cart-zig simple_zig
docker run -it -v ./carts/go/simple:/src -v ./build/carts:/out konsumer/null0-cart-go simple_go
docker run -it -v ./carts/wat/simple:/src -v ./build/carts:/out konsumer/null0-cart-wat simple_wat
docker run -it -v ./carts/walt/simple:/src -v ./build/carts:/out konsumer/null0-cart-walt simple_walt
docker run -it -v ./carts/d/simple:/src -v ./build/carts:/out konsumer/null0-cart-d simple_d
docker run -it -v ./carts/odin/simple:/src -v ./build/carts:/out konsumer/null0-cart-odin simple_odin
docker run -it -v ./carts/c3/simple:/src -v ./build/carts:/out konsumer/null0-cart-c3 simple_c3
docker run -it -v ./carts/onyx/simple:/src -v ./build/carts:/out konsumer/null0-cart-onyx simple_onyx
docker run -it -v ./carts/grain/simple:/src -v ./build/carts:/out konsumer/null0-cart-grain simple_grain

docker run -it -v ./carts/rust/examples/simple:/src -v ./build/carts:/out konsumer/null0-cart-rust simple_rust

docker run -it -v ./carts/python/simple:/src -v ./build/carts:/out konsumer/null0-cart-python simple_python
docker run -it -v ./carts/wren/simple:/src -v ./build/carts:/out konsumer/null0-cart-wren simple_wren
docker run -it -v ./carts/lua/simple:/src -v ./build/carts:/out konsumer/null0-cart-lua simple_lua

docker run -it --platform linux/amd64 -v ./carts/haxe/simple:/src -v ./build/carts:/out konsumer/null0-cart-haxe simple_haxe

docker run -it --platform linux/amd64 -v ./carts/zenc/simple:/src -v ./build/carts:/out konsumer/null0-cart-zenc simple_zenc
docker run -it --platform linux/amd64 -v ./carts/jik/simple:/src -v ./build/carts:/out konsumer/null0-cart-jik simple_jik
```
