#!/usr/bin/env node

// Generator for Zen-C's null0 header.
//
// Zen-C transpiles to plain C, and its `include "X.h"` pulls in a real C
// header - carts get the null0 API via `include "null0.h"`, not through
// any zc-syntax bindings. So this writes carts/zenc/null0.h, sharing the
// same preamble (types/structs/enums/constants/callbacks) as carts/c/null0.h
// via tools/c_header_common.js.
//
// One difference from the C header: zc v0.4.4's *own compiler* segfaults
// the moment cart-authored source (not included-header source - the header
// itself is never re-parsed by zc, only the C compiler sees it) writes a
// declaration that names one of the C-interop struct types (Color, Vector,
// Rectangle, Dimensions, SfxParams) - a local var, a function parameter, a
// return-type annotation, anything. Passing an *existing* typed value (a
// predefined color constant, or a `let x = some_call(...)` whose type zc
// infers rather than the author spelling out) is fine; only a cart author
// writing the type name themselves crashes.
//
// That's only a real problem for the 4 functions taking `Vector[]` (there's
// no way to build a polygon's point list without a cart-authored `[N]Vector`
// declaration) - everywhere else (draw_rectangle(..., RED), etc.), passing
// an *existing* predefined color constant needs no new declaration and
// already works fine, so it's left as ordinary `Color` by value.
//
// The fix for the 4: at the actual wasm ABI level, a struct-by-value arg
// (Color) and a struct-array arg (Vector[]) both already cross as a plain
// i32 pointer - the `Color`/`Vector*` C-level typing is just source-level
// sugar wasi-sdk clang lowers away. So those 4 are declared here with
// primitive pointer types (`u8*` for Color's 4 bytes, `i32*` for Vector[]'s
// x/y pairs) instead - same import, same wasm signature, just typed so a
// cart can build the polygon (and, for consistency within the same call, a
// custom fill color) with a plain `[N]byte`/`[N]int` array and never write
// "Color" or "Vector" themselves.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'
import { cPreamble, cArgTypes, cRetTypes, cArgsMap } from './c_header_common.js'

const out = [cPreamble]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// enums cross as ints, structs come back as pointers into cart memory
seedTypes(cRetTypes, { enums, structs }, { structType: (name) => `${name}*` })

// zc-unsafe arg types -> the primitive pointer type they lower to at the
// real wasm ABI level (same underlying import, just a compatible C type)
const zcSafeArgTypes = { Color: 'u8*', 'Vector[]': 'i32*' }

function zcArgsMap(args, useSafeTypes) {
  return Object.entries(args)
    .map(([name, type]) => `${(useSafeTypes && zcSafeArgTypes[type]) || cArgTypes[type] || type} ${name}`)
    .join(', ')
}

for (const [apiName, apiObj] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const needsSafeTypes = Object.values(args).includes('Vector[]')
    out.push(`// ${description}`)
    out.push(`NULL0_IMPORT("${funcName}")`)
    out.push(`extern ${cRetTypes[returns] || returns} ${funcName}(${zcArgsMap(args, needsSafeTypes)});`, '')
  }
}

await mkdir('carts/zenc', { recursive: true })
await writeFile('carts/zenc/null0.h', out.join('\n'))
