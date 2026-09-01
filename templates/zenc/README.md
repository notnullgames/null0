# mygame

A starter [null0](https://notnull.games/null0) cart, in Zen-C.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install zc (transpiles to C) + wasi-sdk yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

```sh
npm start
```

That builds `webroot/mygame.null0`, serves `webroot/`, and rebuilds whenever you edit something in `cart/`. To build once, without the server:

```sh
npm run build
```

Or call docker yourself:

```sh
rm -f webroot/mygame.null0
docker run --rm --user $(id -u):$(id -g) --platform linux/amd64 -v ./cart:/src -v ./webroot:/out ghcr.io/notnullgames/null0-cart-zenc:latest mygame
```

> This image is `linux/amd64` only, so on Apple Silicon it runs under emulation. That works, it is just slow.

## writing your game

Your code is in `cart/main.zc`. A cart implements the callbacks it cares about and the host skips the rest:

```c
void update() {}
```

### Zen-C notes

- `draw_polygon` and its siblings take plain `i32*`/`u8*`, not structs - the compiler segfaults on a user declaration naming a C-interop struct.

You do not need to copy any null0 bindings into this project - the docker image bakes the current [`carts/zenc/null0.h`](https://raw.githubusercontent.com/notnullgames/null0/main/carts/zenc/null0.h) in for you.

## docs

- [Zen-C carts](https://notnull.games/null0/languages/zenc) - the whole API, in Zen-C
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
