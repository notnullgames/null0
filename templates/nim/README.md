# mygame

A starter [null0](https://notnull.games/null0) cart, in Nim.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install nim + wasi-sdk clang yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out konsumer/null0-cart-nim mygame
```

## writing your game

Your code is in `cart/main.nim`. A cart implements the callbacks it cares about and the host skips the rest:

```nim
proc load*() {.wasm.} =
```

### Nim notes

- `import null0`.

You do not need to copy any null0 bindings into this project - the docker image bakes the current [`carts/nim/null0.nim`](https://raw.githubusercontent.com/notnullgames/null0/main/carts/nim/null0.nim) in for you.

## docs

- [Nim carts](https://notnull.games/null0/languages/nim) - the whole API, in Nim
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
