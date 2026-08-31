# mygame

A starter [null0](https://notnull.games/null0) cart, in Haxe.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install haxe, HL/C + wasi-sdk yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) --platform linux/amd64 -v ./cart:/src -v ./webroot:/out konsumer/null0-cart-haxe mygame
```

> This image is `linux/amd64` only, so on Apple Silicon it runs under emulation. That works, it is just slow.

## writing your game

Your code is in `cart/Main.hx`. A cart implements the callbacks it cares about and the host skips the rest:

```haxe
Null0.onUpdate = () -> {}
```

### Haxe notes

- Callbacks are closures you assign (`Null0.onUpdate = ...`), not exports.
- No `try`/`catch`: wasm exception-handling is not available in the host interpreter.

You do not need to copy any null0 bindings into this project - the docker image bakes the current [`carts/haxe/Null0.hx`](https://raw.githubusercontent.com/notnullgames/null0/main/carts/haxe/Null0.hx) in for you.

## docs

- [Haxe carts](https://notnull.games/null0/languages/haxe) - the whole API, in Haxe
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
