# mygame

A starter [null0](https://notnull.games/null0) cart, in WAT.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install wat2wasm yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out konsumer/null0-cart-wat mygame
```

## writing your game

Your code is in `cart/main.wat`. A cart implements the callbacks it cares about and the host skips the rest:

```lisp
(func (export "update") ...)
```

### WAT notes

- Raw wasm text - no include mechanism, so copy the imports you need out of null0.wat.
- A `Color` is a *pointer to 4 bytes* you write into memory yourself.
- No `malloc`, so struct-returning functions do not work on the web host.

Run `npm run bindings` to drop the current `null0.wat` into `cart/` for your editor. It is gitignored on purpose - fetch it again whenever you want, rather than letting a stale copy rot in your repo.

## docs

- [WAT carts](https://notnull.games/null0/languages/wat) - the whole API, in WAT
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
