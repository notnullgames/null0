This contains the native runtime & api library for [null0 game engine](https://notnullgames.vercel.app/).

It also contains tools for creating various cart-headers and some native examples (not carts.)

```
# install dev-libs
npm i

# build the native runtime & examples
npm run build
```

Here are some you will problably not need to run, because they should all be run for you:

```
# Generate the (stubbed) C headers for full API
npm run gen:host:api

# Generate the C headers for WAMR native wasm-host
npm run gen:host:wamr

# Generate the C cart-header
npm run gen:cart:c
```