# mygame

A starter [null0](https://notnull.games/null0) cart, in Onyx.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install onyx yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out ghcr.io/notnullgames/null0-cart-onyx:latest mygame
```

## writing your game

Your code is in `cart/main.onyx`. A cart implements the callbacks it cares about and the host skips the rest:

```odin
#export "load" load
```

This toolchain also needs an entry point to exist, even though null0 never uses it for gameplay. Leave it empty:

```odin
main :: () {}
```

### Onyx notes

- `#load "null0.onyx"`, and keep an empty `main` around.
- Text takes a `u32` pointer, not a `str` - onyx cannot alias a foreign import name, so wrap literals with `cstr("...")` from the bindings.

You do not need to copy any null0 bindings into this project - the docker image bakes the current [`carts/onyx/null0.onyx`](https://raw.githubusercontent.com/notnullgames/null0/main/carts/onyx/null0.onyx) in for you.

## docs

- [Onyx carts](https://notnull.games/null0/languages/onyx) - the whole API, in Onyx
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches the cart *and* a standalone native game for every platform to any github release you create.

So each release of your game ships:

| asset | what it is |
| --- | --- |
| `mygame.null0` | the cart itself - play it in a browser, or with `null0 mygame.null0` |
| `mygame_linux_x86-64.zip` | a single native executable, nothing to install |
| `mygame_macos.zip` | the same, universal (Intel and Apple Silicon) |
| `mygame_windows_x64.zip` | the same, as `mygame.exe` |

### standalone games

The runtime mounts a zip appended to its own executable, so a standalone game is just the null0 runtime with your cart concatenated onto the end. The **Release** workflow does that for you, but it is one command by hand - grab a runtime from [null0 releases](https://github.com/notnullgames/null0/releases) and:

```sh
# linux or mac
cat null0 mygame.null0 > mygame && chmod +x mygame
```

```bat
REM windows
copy /b null0.exe+mygame.null0 mygame.exe
```

The result is an ordinary executable that needs no arguments and no null0 installed. Players who already have the runtime can still just run `null0 mygame.null0`.
