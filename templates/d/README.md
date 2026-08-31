# mygame

A starter [null0](https://notnull.games/null0) cart, in D.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install ldc2 yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out konsumer/null0-cart-d mygame
```

## writing your game

Your code is in `cart/main.d`. A cart implements the callbacks it cares about and the host skips the rest:

```d
export extern(C) void load() {}
```

### D notes

- `-betterC`, so no druntime and no GC.

You do not need to copy any null0 bindings into this project - the docker image bakes the current [`carts/d/null0.d`](https://raw.githubusercontent.com/notnullgames/null0/main/carts/d/null0.d) in for you.

## docs

- [D carts](https://notnull.games/null0/languages/d) - the whole API, in D
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
