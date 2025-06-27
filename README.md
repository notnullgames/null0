This combines ideas from [pntr_app_starter](https://github.com/RobLoach/pntr_app_starter) with [wamr](https://github.com/bytecodealliance/wasm-micro-runtime) to make null0 game-engine (native runtime & libretro core.)

You can see a simple web-demo [here](https://notnullgames.github.io/null0) or [read the docs](https://notnullgames.vercel.app/null0).

```bash
# build native-host
npm run build:native

# build example carts
npm run build:carts

# run local watching web-server with webhost
npm start
```

## distribution

To distribute your game, you can either save your cart as main.null0, alongside the native runtime (and name that whatever you want) or you can embed it all in one executable:

```sh
# linux or mac
./tools/embed_cart.js build/host/null0 build/carts/input_c.null0 tester

# windows
node ./tools/embed_cart.js build/host/null0.exe build/carts/input_c.null0 tester.exe

# or

# linux or mac
cat build/host/null0 build/carts/input_c.null0 > tester

# windows
copy /b build/host/null0.exe+build/carts/input_c.null0 tester.exe
```

## thanks

See [THANKS](THANKS.md) for acknowledgement and thanks for all the great help & code I received to make this.

## license

See [LICENSE](LICENSE) for licensing information.
