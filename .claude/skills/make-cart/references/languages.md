# Cart languages

`<lang>` here is the docker image suffix: `konsumer/null0-cart-<image>`.

## Interpreted (the interpreter is baked into main.wasm; you ship source)

| Language   | Example               | File        | Image     | Callback syntax             | API style                                            |
| ---------- | --------------------- | ----------- | --------- | --------------------------- | ---------------------------------------------------- |
| javascript | `carts/js/simple`       | `main.js`   | `quickjs` | `export function load() {}` | flat globals, ESM imports of other cart files work   |
| python     | `carts/python/simple` | `main.py`   | `python`  | `def load():`               | flat globals, structs are dicts                      |
| lua        | `carts/lua/simple`    | `main.lua`  | `lua`     | `function load() end`       | flat globals, structs are tables, `require` works    |
| wren       | `carts/wren/simple`   | `main.wren` | `wren`    | `var load = Fn.new {}`      | `import "null0" for Null0, BLUE`, methods on `Null0` |

`carts/lua/null0.lua` is LuaLS definitions (editor completion only, not shipped).
`carts/wren/null0.wren` is the real module, baked into the runtime.

## Compiled (your code becomes main.wasm)

| Language       | Example                      | File         | Image            | Callback syntax                         | Notes                                                  |
| -------------- | ---------------------------- | ------------ | ---------------- | --------------------------------------- | ------------------------------------------------------ |
| C              | `carts/c/simple`            | `main.c`     | `c`              | `void update() {}`                      | `#include "null0.h"`, wasi-sdk clang                   |
| rust           | `carts/rust/examples/simple` | `src/lib.rs` | `rust`           | `#[no_mangle] pub extern "C" fn load()` | `no_std`, `crate-type = ["cdylib"]`, `panic = "abort"` |
| zig            | `carts/zig/simple`           | `main.zig`   | `zig`            | `export fn load() void`                 | needs `pub fn main() void {}`                          |
| go             | `carts/go/simple`            | `main.go`    | `go`             | `//export load`                         | tinygo, needs `func main() {}`                         |
| nim            | `carts/nim/simple`           | `main.nim`   | `nim`            | `proc load*() {.wasm.} =`               | `import null0`                                         |
| nelua          | `carts/nelua/simple`          | `main.nelua` | `nelua`          | `local function load() <cexport'load'>` | `require 'null0'`                                      |
| odin           | `carts/odin/simple`          | `main.odin`  | `odin`           | `@(export) load :: proc "c" () {}`      | `import null0 "null0"`                                 |
| c3             | `carts/c3/simple`            | `main.c3`    | `c3`             | `fn void load() @export("load")`        | `module main` + `import null0`                         |
| D              | `carts/d/simple`             | `main.d`     | `d`              | `export extern(C) void load()`          | ldc                                                    |
| onyx           | `carts/onyx/simple`          | `main.onyx`  | `onyx`           | `#export "load" load`                   | `#load "null0.onyx"`, needs `main :: () {}`            |
| grain          | `carts/grain/simple`         | `main.gr`    | `grain`          | `provide let load = () => {}`           | `from "./null0.gr" include Null0`, raw wasm literals (`100n`) |
| assemblyscript | `carts/as/simple`            | `main.ts`    | `assemblyscript` | `export function load(): void`          | `import { clear } from 'null0.ts'`                     |
| WAT            | `carts/wat/simple`           | `main.wat`   | `wat`            | `(export "load" ...)`                   | raw wasm text                                          |
| walt           | `carts/walt/simple`          | `main.walt`  | `walt`           | `export function load()`                | JS-like syntax over raw wasm                           |

## Things that differ per language

- **Colors**: high-level languages give you a `Color` value. In WAT/walt a
  Color is a _pointer to 4 bytes_ you must write into memory yourself - read
  those examples closely. Grain's `null0.gr` module handles this for you:
  call `Null0.initColors()` first thing in `load()`, then pass `Null0.blue`
  and friends directly.
- **Entry point**: some toolchains need a `main` to exist even though null0
  never uses it for gameplay (zig, go, onyx). Keep it empty.
- **Multi-file carts**: js (ESM), lua (`require`), wren (`import`), and the
  compiled languages (normal modules) all support extra files; interpreted carts
  ship those files inside the cart.
