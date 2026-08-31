# mygame

A starter [null0](https://notnull.games/null0) cart, in JavaScript.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install QuickJS, baked into main.wasm yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out konsumer/null0-cart-quickjs mygame
```

## writing your game

Your code is in `cart/main.js`. A cart implements the callbacks it cares about and the host skips the rest:

```typescript
export function update () {}
```

### JavaScript notes

- The API is plain globals - nothing to import. Callbacks are ESM exports of `main.js`.
- Structs are plain objects (`{ r: 0, g: 121, b: 241, a: 255 }`); array args know their own length, so you never pass the count.
- `std` and `os` from QuickJS are available as globals, as is WASI.
- Drop `null0.d.ts` + `jsconfig.json` next to `main.js` for editor completion and typechecking.

Run `npm run bindings` to drop the current `null0.d.ts` into `cart/` for your editor. It is gitignored on purpose - fetch it again whenever you want, rather than letting a stale copy rot in your repo.

## docs

- [JavaScript carts](https://notnull.games/null0/languages/js) - the whole API, in JavaScript
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
