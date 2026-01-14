This directory is docker-builders of different carts.

### available containers

- `konsumer/null0-cart-c`
- `konsumer/null0-cart-quickjs`
- `konsumer/null0-cart-nelua`
- `konsumer/null0-cart-assemblyscript`
- `konsumer/null0-cart-nim`

I haven't finished demos/headers/etc for these:

- `konsumer/null0-cart-zig`
- `konsumer/null0-cart-rust`
- `konsumer/null0-cart-py2wasm`

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

# build & publish (needed on API change)
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-c . -f tools/docker/null0-cart-c.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-quickjs . -f tools/docker/null0-cart-quickjs.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-assemblyscript . -f tools/docker/null0-cart-assemblyscript.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-nelua . -f tools/docker/null0-cart-nelua.Dockerfile
docker buildx build --push --platform linux/amd64,linux/arm64 -t konsumer/null0-cart-nim . -f tools/docker/null0-cart-nim.Dockerfile

# test
docker run -it -v ./carts/c/colorbars:/src -v ./webroot/carts:/out konsumer/null0-cart-c colorbars_c
docker run -it -v ./carts/c/example:/src -v ./webroot/carts:/out konsumer/null0-cart-c example_c
docker run -it -v ./carts/c/gradient:/src -v ./webroot/carts:/out konsumer/null0-cart-c gradient_c
docker run -it -v ./carts/c/input:/src -v ./webroot/carts:/out konsumer/null0-cart-c input_c
docker run -it -v ./carts/c/sfx:/src -v ./webroot/carts:/out konsumer/null0-cart-c sfx_c
docker run -it -v ./carts/c/speak:/src -v ./webroot/carts:/out konsumer/null0-cart-c speak_c
docker run -it -v ./carts/c/wasi_demo:/src -v ./webroot/carts:/out konsumer/null0-cart-c wasi_demo_c

docker run -it -v ./carts/js/demo:/src -v ./webroot/carts:/out konsumer/null0-cart-quickjs demo_js
docker run -it -v ./carts/js/input:/src -v ./webroot/carts:/out konsumer/null0-cart-quickjs input_js

docker run -it -v ./carts/as/simple:/src -v ./webroot/carts:/out konsumer/null0-cart-assemblyscript simple_as

docker run -it -v ./carts/nelua/basic:/src -v ./webroot/carts:/out konsumer/null0-cart-nelua basic_nelua
docker run -it -v ./carts/nelua/colorbars:/src -v ./webroot/carts:/out konsumer/null0-cart-nelua colorbars_nelua

docker run -it -v ./carts/nim/simple:/src -v ./webroot/carts:/out konsumer/null0-cart-nim simple_nim
```
