// The per-language half of the API docs.
//
// api/*.yml says what the API *is*; every cart language then spells it its own
// way. Rather than re-implement 23 sets of type-mapping rules here (they
// already live in the gen_cart_* generators, and would drift the moment one
// changed), this file reads the *generated bindings themselves* and pulls the
// real declaration line out of each one. If `npm run gen` produced it, this is
// what a cart author actually sees in their editor.
//
// Each language entry:
//   title       display name
//   image       the image's short name; the full ref is imageRef() below
//   kind        'compiled' | 'interpreted'
//   file        what the cart's source file is called
//   binding     generated file the declarations are read from (null if none)
//   highlight   language id for a syntax highlighter
//   callback    how the cart declares a callback
//   entry       an extra entry-point the toolchain needs, if any
//   notes[]     language-specific gotchas worth putting on the docs page
//   example     the starter cart, copied verbatim into templates/<lang>/src
//   amd64Only   image is linux/amd64 only
//   decls(src)  -> { [apiFunctionName]: 'the declaration, verbatim' }

import { readFile } from 'node:fs/promises'

// Cart images live in this repo's own GitHub package registry, built and
// pushed by CI on every tag. Nothing here is published by hand any more, so
// this is the one place the location is written down - templates, the docs
// site, the README and CI all read it from here (via webroot/api.json).
export const REGISTRY = 'ghcr.io/notnullgames'

export const imageName = (lang) => `${REGISTRY}/null0-cart-${lang.image}`

// `latest` for humans, an exact version for anything that wants to be
// reproducible
export const imageRef = (lang, tag = 'latest') => `${imageName(lang)}:${tag}`

// Most bindings are one declaration per line. `byLine` walks the file and, for
// each line matching `re`, uses capture group 1 as the null0 function name and
// the line itself (minus any comment prefix) as the declaration.
const byLine =
  (re, { strip = null, prefixRe = null } = {}) =>
  (src) => {
    const out = {}
    const lines = src.split('\n')
    for (let i = 0; i < lines.length; i++) {
      const m = lines[i].match(re)
      if (!m) {
        continue
      }
      let decl = lines[i].trim()
      if (strip) {
        decl = decl.replace(strip, '')
      }
      if (prefixRe && i > 0 && prefixRe.test(lines[i - 1])) {
        decl = `${lines[i - 1].trim()}\n${decl}`
      }
      out[m[1]] = decl.trim()
    }
    return out
  }

// Some bindings put the null0 name on an attribute line and the declaration on
// the next one (C's NULL0_IMPORT, assemblyscript's @external, ...).
const byAttr =
  (attrRe, { skip = 0, strip = null } = {}) =>
  (src) => {
    const out = {}
    const lines = src.split('\n')
    for (let i = 0; i < lines.length; i++) {
      const m = lines[i].match(attrRe)
      if (!m) {
        continue
      }
      const decl = lines[i + 1 + skip]
      if (decl) {
        out[m[1]] = (strip ? decl.trim().replace(strip, '') : decl.trim()).trim()
      }
    }
    return out
  }

// go/haskell/haxe wrap a raw import in an ergonomic function. The raw import
// names the null0 function; the wrapper a few lines down is what you call.
const byWrapper =
  (importRe, wrapperRe, { window = 6 } = {}) =>
  (src) => {
    const out = {}
    const lines = src.split('\n')
    for (let i = 0; i < lines.length; i++) {
      const m = lines[i].match(importRe)
      if (!m) {
        continue
      }
      for (let j = i + 1; j < Math.min(i + 1 + window, lines.length); j++) {
        const w = lines[j].match(wrapperRe)
        if (w) {
          out[m[1]] = lines[j].trim().replace(/\s*\{\s*\}?$/, '')
          break
        }
      }
    }
    return out
  }

export const languages = {
  c: {
    title: 'C',
    image: 'c',
    kind: 'compiled',
    file: 'main.c',
    binding: 'carts/c/null0.h',
    highlight: 'c',
    callback: 'void update() {}',
    toolchain: 'wasi-sdk clang',
    notes: ['`#include "null0.h"` and you have the whole API. `main()` works as a `load()` if you prefer it.', 'Call `fflush(stdout)` if you want `printf` output to survive a cart being killed.'],
    decls: byAttr(/^NULL0_IMPORT\("(\w+)"\)/)
  },

  rust: {
    title: 'Rust',
    image: 'rust',
    kind: 'compiled',
    file: 'src/lib.rs',
    binding: 'carts/rust/src/lib.rs',
    highlight: 'rust',
    callback: '#[no_mangle] pub extern "C" fn load() {}',
    toolchain: 'cargo, wasm32-unknown-unknown',
    example: 'carts/rust/examples/simple',
    notes: ['`no_std`, `crate-type = ["cdylib"]`, `panic = "abort"`.', 'The declarations live in an `extern "C"` block, so every call is `unsafe`.'],
    decls: byLine(/^\s*pub fn (\w+)\(/)
  },

  zig: {
    title: 'Zig',
    image: 'zig',
    kind: 'compiled',
    file: 'main.zig',
    binding: 'carts/zig/null0.zig',
    highlight: 'zig',
    callback: 'export fn load() void {}',
    entry: 'pub fn main() void {}',
    toolchain: 'zig, wasm32-wasi',
    notes: ['wasm32-wasi executables need a `main`, even though null0 never uses it. Keep it empty.'],
    decls: byLine(/^pub extern "null0" fn (\w+)\(/)
  },

  go: {
    title: 'Go',
    image: 'go',
    kind: 'compiled',
    file: 'main.go',
    binding: 'carts/go/null0/null0.go',
    highlight: 'go',
    callback: '//export load\nfunc load() {}',
    entry: 'func main() {}',
    toolchain: 'tinygo',
    notes: ['The API is `CamelCase` here, wrapping the raw `//go:wasmimport` declarations.', 'There is no working directory - `os.ReadFile("/main.lua")` works, `os.ReadFile("main.lua")` does not.'],
    decls: byWrapper(/^\/\/go:wasmimport null0 (\w+)$/, /^func [A-Z]\w*\(/)
  },

  nim: {
    title: 'Nim',
    image: 'nim',
    kind: 'compiled',
    file: 'main.nim',
    binding: 'carts/nim/null0.nim',
    highlight: 'nim',
    callback: 'proc load*() {.wasm.} =',
    toolchain: 'nim + wasi-sdk clang',
    notes: ['`import null0`.'],
    decls: byLine(/^proc (\w+)\*\(/)
  },

  nelua: {
    title: 'Nelua',
    image: 'nelua',
    kind: 'compiled',
    file: 'main.nelua',
    binding: 'carts/nelua/null0.nelua',
    highlight: 'lua',
    callback: "local function load() <cexport'load'> end",
    toolchain: 'nelua + wasi-sdk clang',
    notes: ["`require 'null0'`. Nelua compiles to C, so it needs null0.h alongside null0.nelua."],
    decls: byLine(/^global function (\w+)\(/)
  },

  as: {
    title: 'AssemblyScript',
    image: 'assemblyscript',
    kind: 'compiled',
    file: 'main.ts',
    binding: 'carts/as/null0.ts',
    highlight: 'typescript',
    callback: 'export function load(): void {}',
    toolchain: 'asc',
    notes: ["Import what you use: `import { clear, draw_circle, BLUE } from 'null0.ts'` - that exact specifier, not a relative path.", 'Built with `--runtime stub`, so there is no GC - treat allocations as permanent.'],
    decls: byAttr(/^@external\("null0", "(\w+)"\)/)
  },

  odin: {
    title: 'Odin',
    image: 'odin',
    kind: 'compiled',
    file: 'main.odin',
    binding: 'carts/odin/null0/null0.odin',
    highlight: 'odin',
    callback: '@(export) load :: proc "c" () {}',
    toolchain: 'odin, freestanding wasm32',
    notes: ['`import null0 "null0"`.'],
    decls: byLine(/^\s*(\w+) :: proc\(.*---\s*$/)
  },

  c3: {
    title: 'C3',
    image: 'c3',
    kind: 'compiled',
    file: 'main.c3',
    binding: 'carts/c3/null0.c3',
    highlight: 'c',
    callback: 'fn void load() @export("load") {}',
    toolchain: 'c3c',
    // c3c only ships x86_64 linux builds - the aarch64 assets are android and
    // windows, so there is nothing to install on arm64
    amd64Only: true,
    notes: ['`module main` plus `import null0`.'],
    decls: byLine(/^extern fn \S+ (\w+)\(/)
  },

  d: {
    title: 'D',
    image: 'd',
    kind: 'compiled',
    file: 'main.d',
    binding: 'carts/d/null0.d',
    highlight: 'd',
    callback: 'export extern(C) void load() {}',
    toolchain: 'ldc2',
    notes: ['`-betterC`, so no druntime and no GC.'],
    decls: byLine(/^extern\(C\) \S+ (\w+)\(/)
  },

  onyx: {
    title: 'Onyx',
    image: 'onyx',
    kind: 'compiled',
    file: 'main.onyx',
    binding: 'carts/onyx/null0.onyx',
    highlight: 'odin',
    callback: '#export "load" load',
    entry: 'main :: () {}',
    toolchain: 'onyx',
    notes: ['`#load "null0.onyx"`, and keep an empty `main` around.'],
    decls: byLine(/^\s*(\w+) :: \(.*\) -> \S+ ---\s*$/)
  },

  grain: {
    title: 'Grain',
    image: 'grain',
    kind: 'compiled',
    file: 'main.gr',
    binding: 'carts/grain/null0.gr',
    highlight: 'rust',
    callback: 'provide let load = () => { void }',
    toolchain: 'grain',
    amd64Only: true,
    notes: ['`from "./null0.gr" include Null0`.', 'Numbers cross the boundary as raw wasm values, so they are written `100n`, not `100`.', 'Call `Null0.initColors()` first thing in `load()`, then `Null0.blue` and friends work.'],
    decls: byLine(/^provide foreign wasm (\w+):/)
  },

  haxe: {
    title: 'Haxe',
    image: 'haxe',
    kind: 'compiled',
    file: 'Main.hx',
    binding: 'carts/haxe/Null0.hx',
    highlight: 'haxe',
    callback: 'Null0.onUpdate = () -> {}',
    toolchain: 'haxe, HL/C + wasi-sdk',
    amd64Only: true,
    notes: ['Callbacks are closures you assign (`Null0.onUpdate = ...`), not exports.', 'No `try`/`catch`: wasm exception-handling is not available in the host interpreter.'],
    decls: byAttr(/^\s*@:hlNative\("null0hx", "(\w+)"\)/, { strip: /\s*\{.*\}$/ })
  },

  haskell: {
    title: 'Haskell',
    image: 'haskell',
    kind: 'compiled',
    file: 'Main.hs',
    binding: 'carts/haskell/Null0.hs',
    highlight: 'haskell',
    callback: 'foreign export ccall update :: IO ()',
    toolchain: 'wasm32-wasi-ghc (reactor mode)',
    notes: ['Everything is in `IO`. Each null0 call is imported through a generated C trampoline.', 'Carts get no environment variables, so anything reading `$PWD` sees nothing.'],
    decls: byWrapper(/^foreign import ccall unsafe "(\w+)" c_\w+ ::/, /^\w+ :: /, { window: 3 })
  },

  zenc: {
    title: 'Zen-C',
    image: 'zenc',
    kind: 'compiled',
    file: 'main.zc',
    binding: 'carts/zenc/null0.h',
    highlight: 'c',
    callback: 'void update() {}',
    toolchain: 'zc (transpiles to C) + wasi-sdk',
    amd64Only: true,
    notes: ['`draw_polygon` and its siblings take plain `i32*`/`u8*`, not structs - the compiler segfaults on a user declaration naming a C-interop struct.'],
    decls: byAttr(/^NULL0_IMPORT\("(\w+)"\)/)
  },

  jik: {
    title: 'Jik',
    image: 'jik',
    kind: 'compiled',
    file: 'main.jik',
    binding: 'carts/jik/null0.jik',
    highlight: 'rust',
    callback: 'export func update() -> void',
    toolchain: 'jik (transpiles to C) + wasi-sdk',
    amd64Only: true,
    reference: true,
    notes: ["Jik's types don't line up with the null0 ABI, so null0.jik is a set of `extern` declarations and C wrappers to copy into your cart's `@embed` block."],
    decls: byLine(/^\/\/ extern func (\w+) as /, { strip: /^\/\/\s?/ })
  },

  wat: {
    title: 'WAT',
    image: 'wat',
    kind: 'compiled',
    file: 'main.wat',
    binding: 'carts/wat/null0.wat',
    highlight: 'lisp',
    callback: '(func (export "update") ...)',
    toolchain: 'wat2wasm',
    reference: true,
    notes: ['Raw wasm text - no include mechanism, so copy the imports you need out of null0.wat.', 'A `Color` is a *pointer to 4 bytes* you write into memory yourself.', 'No `malloc`, so struct-returning functions do not work on the web host.'],
    decls: byLine(/^\(import "null0" "(\w+)"/)
  },

  walt: {
    title: 'Walt',
    image: 'walt',
    kind: 'compiled',
    file: 'main.walt',
    binding: 'carts/walt/null0.walt',
    highlight: 'javascript',
    callback: 'export function update() {}',
    toolchain: 'walt',
    reference: true,
    notes: ['Imports are per-module: copy the `type` + `import` pair for each function you use.', 'You need a local memory (`const memory: Memory = { initial: 1 }`) even for a plain store.', 'A `Color` is a *pointer to 4 bytes* you write into memory yourself.', 'No `malloc`, so struct-returning functions do not work on the web host.'],
    decls: byLine(/^\/\/ import \{ (\w+): \w+ \} from 'null0';/, { strip: /^\/\/\s?/, prefixRe: /^type \w+ = / })
  },

  js: {
    title: 'JavaScript',
    image: 'quickjs',
    kind: 'interpreted',
    file: 'main.js',
    binding: 'carts/js/null0.d.ts',
    highlight: 'typescript',
    callback: 'export function update () {}',
    toolchain: 'QuickJS, baked into main.wasm',
    notes: ['The API is plain globals - nothing to import. Callbacks are ESM exports of `main.js`.', 'Structs are plain objects (`{ r: 0, g: 121, b: 241, a: 255 }`); array args know their own length, so you never pass the count.', '`std` and `os` from QuickJS are available as globals, as is WASI.', 'Drop `null0.d.ts` + `jsconfig.json` next to `main.js` for editor completion and typechecking.'],
    decls: byLine(/^\s*function (\w+)\(/)
  },

  python: {
    title: 'Python',
    image: 'python',
    kind: 'interpreted',
    file: 'main.py',
    binding: 'carts/python/null0.pyi',
    highlight: 'python',
    callback: 'def update():',
    toolchain: 'RustPython, baked into main.wasm',
    notes: ['The API is plain globals - nothing to import. Structs are dicts, and array args know their own length.', 'This is RustPython built without the stdlib: there is no `typing`, no `os`, no `json`.', 'Drop `null0.pyi` next to `main.py` and open your cart with `TYPE_CHECKING = False` / `if TYPE_CHECKING: from null0 import *` for completion.'],
    decls: byLine(/^def (\w+)\(/, { strip: /:$/ })
  },

  lua: {
    title: 'Lua',
    image: 'lua',
    kind: 'interpreted',
    file: 'main.lua',
    binding: 'carts/lua/null0.lua',
    highlight: 'lua',
    callback: 'function update() end',
    toolchain: 'GopherLua, baked into main.wasm',
    notes: ['The API is plain globals, structs are tables, and `require` works for extra cart files.', 'GopherLua, not C Lua - the host interpreter has no exception-handling, which C Lua needs.', '`null0.lua` is LuaLS definitions for your editor; it is not shipped inside the cart.'],
    decls: byLine(/^function (\w+)\(/)
  },

  wren: {
    title: 'Wren',
    image: 'wren',
    kind: 'interpreted',
    file: 'main.wren',
    binding: 'carts/wren/null0.wren',
    highlight: 'dart',
    callback: 'var update = Fn.new {}',
    toolchain: 'wren, baked into main.wasm',
    notes: ['`import "null0" for Null0, BLUE` - the API hangs off the `Null0` class.', 'Callbacks are `Fn` values assigned to top-level variables.'],
    // zero-arg functions become wren getters, so match both forms and drop
    // the forwarding body - it's just plumbing to the `foreign static` import
    decls: byLine(/^\s*static (\w+)\s*[({]/, { strip: /\s*\{.*\}\s*$/ })
  },

  cyber: {
    title: 'Cyber',
    image: 'cyber',
    kind: 'interpreted',
    file: 'main.cy',
    binding: 'carts/cyber/null0.cy',
    highlight: 'rust',
    callback: 'func update():',
    toolchain: 'cyber, baked into main.wasm',
    notes: ['`use null0`, then `null0.clear(null0.BLUE)`.', 'The VM is re-entered per callback via `persist_main`, so top-level state persists across frames.'],
    decls: byLine(/^#\[bind\] fn (\w+)\(/, { strip: /^#\[bind\]\s*/ })
  }
}

// Read every binding and pull the declarations out of it.
export async function getLanguageDocs() {
  const out = {}
  for (const [id, lang] of Object.entries(languages)) {
    const { decls, binding, example, ...meta } = lang
    out[id] = {
      id,
      binding,
      example: example || `carts/${id}/simple`,
      ...meta,
      registry: REGISTRY,
      imageRef: imageRef(lang),
      decls: binding ? decls(await readFile(binding, 'utf8')) : {}
    }
  }
  return out
}
