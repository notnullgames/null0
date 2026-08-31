# mygame

A starter [null0](https://notnull.games/null0) cart, in Go.

Press **Use this template** to make your own, then search the project for `mygame` and rename it to whatever your game is called.

## building

Everything is built inside docker, so you never install tinygo yourself. All you need is [docker](https://docs.docker.com/get-started/get-docker/), plus [node](https://nodejs.org/) for the shortcuts below.

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
docker run --rm --user $(id -u):$(id -g) -v ./cart:/src -v ./webroot:/out ghcr.io/notnullgames/null0-cart-go:latest mygame
```

## writing your game

Your code is in `cart/main.go`. A cart implements the callbacks it cares about and the host skips the rest:

```go
//export load
func load() {}
```

This toolchain also needs an entry point to exist, even though null0 never uses it for gameplay. Leave it empty:

```go
func main() {}
```

### Go notes

- The API is `CamelCase` here, wrapping the raw `//go:wasmimport` declarations.
- There is no working directory - `os.ReadFile("/main.lua")` works, `os.ReadFile("main.lua")` does not.

You do not need to copy any null0 bindings into this project - the docker image bakes the current [`carts/go/null0/null0.go`](https://raw.githubusercontent.com/notnullgames/null0/main/carts/go/null0/null0.go) in for you.

## docs

- [Go carts](https://notnull.games/null0/languages/go) - the whole API, in Go
- [Anatomy of a cart](https://notnull.games/null0/cart) - callbacks, input, distribution
- [API reference](https://notnull.games/null0/api)

## publishing

Two workflows come with this template:

- **Publish** builds the cart and deploys `webroot/` to github-pages on every push to `main`, so anyone can play your game in a browser without installing anything.
- **Release** attaches `mygame.null0` to any github release you create.

Players who want it natively can grab [the runtime](https://github.com/notnullgames/null0/releases) and run `null0 mygame.null0`.
