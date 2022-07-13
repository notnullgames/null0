# null0-docker

This is a collection of docker-containers to make it easier to get started making games with [null0](https://github.com/notnullgames/null0), in any supported language.

You only need docker installed to use these.

Once it's finished it will auto-publish on push, so no need to manually use it at all.

I got a lot of ideas from [wasm4](https://github.com/christopher-kleine/wasm4-docker).


You can use them standalone as a way to compile & interact with your code:

```
# assemblyscript tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:as

# c/wasi tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:c

# D language tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:d

# tinygo tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:go

# nelua tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:lua

# nim tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:nim

# odin tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:odin

# rust tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:rust

# zig tools
docker run -it --rm -v ${PWD}:/cart konsumer/null0:zig
```


## Examples


### C

```sh
docker run -it --rm -v ${PWD}:/cart konsumer/null0:c

# if you want full wasi
clang --target=wasm32-wasi --sysroot=/opt/wasi-sysroot -Wl,--no-entry -Wl,--export-all -nostartfiles -o build/hello.wasm src/main.c
```