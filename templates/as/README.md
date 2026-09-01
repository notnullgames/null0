# mygame

A starter [null0](https://notnull.games/null0) cart, in AssemblyScript.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install asc yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out ghcr.io/notnullgames/null0-cart-assemblyscript:latest mygame
```

## writing your game

Your code is in `cart/main.ts`. A cart implements the callbacks it cares about and the host skips the rest:

```typescript
export function load(): void {}
```

### AssemblyScript notes

- Import what you use: `import { clear, draw_circle, BLUE } from 'null0.ts'` - that exact specifier, not a relative path.
- Built with `--runtime stub`, so there is no GC - treat allocations as permanent.

You do not need to copy any null0 bindings into this project - the docker image bakes the current [`carts/as/null0.ts`](https://raw.githubusercontent.com/notnullgames/null0/main/carts/as/null0.ts) in for you.

## docs

- [AssemblyScript carts](https://notnull.games/null0/languages/as) - the whole API, in AssemblyScript
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
