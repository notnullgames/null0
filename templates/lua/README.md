# mygame

A starter [null0](https://notnull.games/null0) cart, in Lua.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install GopherLua, baked into main.wasm yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out konsumer/null0-cart-lua mygame
```

## writing your game

Your code is in `cart/main.lua`. A cart implements the callbacks it cares about and the host skips the rest:

```lua
function update() end
```

### Lua notes

- The API is plain globals, structs are tables, and `require` works for extra cart files.
- GopherLua, not C Lua - the host interpreter has no exception-handling, which C Lua needs.
- `null0.lua` is LuaLS definitions for your editor; it is not shipped inside the cart.

Run `npm run bindings` to drop the current `null0.lua` into `cart/` for your editor. It is gitignored on purpose - fetch it again whenever you want, rather than letting a stale copy rot in your repo.

## docs

- [Lua carts](https://notnull.games/null0/languages/lua) - the whole API, in Lua
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
