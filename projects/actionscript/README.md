# null0-template-as

A template to make an actionscript cart, in null0

If you have node installed:

```sh
# install dependencies
npm i

# start a reloading webserver & wasm-builder
npm start

# build a release cart (in build/release/NAME.null0)
npm run build
```

The source of the cart is in `src/`.


If you don't have node installed, but have docker:

```sh
docker run -p 8080 --rm -it -v ${PWD}:/cart konsumer/null0:as

npm i

npm start

npm run build
```