# null0

This is a very simple cross-platform (including web, and fast native) game library that uses wasm on all platforms (compile once and distribute.) It takes inspiration from love2d and wasm4, but it's way less complete. Initially, it will just be a demo project for building your own stuff, but I hope to make a CLI tool for getting started quick, and maybe a libretro core and a few modules you can optionally use (networking for example.)

You can think of it as a "fantasy console", but it's not nearly as constrained or complete as other really awesome ones, like wasm4, TIC80, etc. If you want something more like a gameboy, try wasm4 or TIC80. If you want a complete game-making library, try raylib (with many native language bindings) or love2d (fun, lua-based wrapper around SDL, that is easy to work with, if you don't need anything else.)

You can see the current demo [here](https://null0.surge.sh/).

# features

- use any language like, that compiles to wasm (C, rust, assemblyscript, nim, etc)
- sound - audio-files & mod-music
- graphics - 320x240, any colors, driven by images/sprites, not really shapes/pixels/etc
- input - mapped from keys & joystick, A, B, X, Y, L, R, start, select, digital directional

You can write your games in any language that compiles to wasm (simialr to wasm4, where you import the header for the language you prefer.)

One idea is to setup fast/easy live-reloading dev in a browser, then later you can use that same wasm file with a local native runtime, or deploy on the web.

Currently, I am putting it all together, so it's mostly just a demo/dev project. You can install deps with `npm i`, and get a menu with `npm start`

## thanks

- [TIC80](https://tic80.com/) & [wasm4](https://wasm4.org/) are a constant source of inspiration
- [Raylib](https://www.raylib.com/) is so nice. Easy & fun to work with, fast, and has a ton of features, and Ray & the community around Raylib are incredibly helpful.
- [Node-raylib](https://github.com/RobLoach/node-raylib) is extremely helpful for prototyping & the other people that are working on it (@twuky and @RobLoach) have been really helpful discussing things, and hammering out ideas with.
- Gulrak wrote the [utf8 lib](https://gist.github.com/gulrak/2eda01eacebdb308787b639fa30958b3) that makes dealing with assemblyscript strings much easier, and was helpful with inciteful discussion.
