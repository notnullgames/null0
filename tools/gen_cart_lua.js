#!/usr/bin/env node

// Generator for the interpreted-Lua null0 cart runtime.
//
// This writes 2 files:
//
// - tools/docker/lua-cart/main.go   the interpreter (GopherLua + null0 bindings)
// - carts/lua/null0.lua             LuaLS definitions, for editors & reference
//
// The interpreter is GopherLua (a Lua 5.1 VM written in go) compiled to
// wasm32-wasip1 with real go, not tinygo: lua's error handling needs
// recover(), which tinygo does not implement. It is built as a wasi
// "reactor" (-buildmode=c-shared) so the null0 host can keep calling into
// it - a go command-module calls proc_exit as soon as main returns, which
// would end the cart after 1 frame.
//
// The API is exposed as plain lua globals (same as the JS/python carts), and
// structs (Color/Vector/Rectangle/Dimensions/SfxParams) are plain tables,
// e.g. {r = 0, g = 121, b = 241, a = 255}.

import { writeFile, mkdir } from 'node:fs/promises'
import { execFile } from 'node:child_process'
import { promisify } from 'node:util'
import { getApi } from './utils.js'

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// go type for each arg, as it crosses into the host. structs travel as
// pointers, which is what the wasm C ABI does with them too
const goArgTypes = {
  string: 'unsafe.Pointer',
  bool: 'int32',
  i32: 'int32',
  f32: 'float32',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'uint32',
  Font: 'uint32',
  Sound: 'uint32',
  ImageFilter: 'int32',
  Key: 'int32',
  GamepadButton: 'int32',
  MouseButton: 'int32',
  SfxPresetType: 'int32',
  Color: 'unsafe.Pointer',
  SfxParams: 'unsafe.Pointer',
  'Vector[]': 'unsafe.Pointer'
}

// go type of what the host hands back (structs come back as pointers into cart-memory)
const goRetTypes = {
  bool: 'int32',
  i32: 'int32',
  f32: 'float32',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'uint32',
  Font: 'uint32',
  Sound: 'uint32',
  Color: 'unsafe.Pointer',
  Vector: 'unsafe.Pointer',
  Dimensions: 'unsafe.Pointer',
  Rectangle: 'unsafe.Pointer',
  SfxParams: 'unsafe.Pointer'
}

const goMemberTypes = { i32: 'int32', f32: 'float32', u32: 'uint32', u8: 'uint8' }

// a few API args (sfx_generate's `type`) are go keywords
const goKeywords = new Set(['break', 'case', 'chan', 'const', 'continue', 'default', 'defer', 'else', 'fallthrough', 'for', 'func', 'go', 'goto', 'if', 'import', 'interface', 'map', 'package', 'range', 'return', 'select', 'struct', 'switch', 'type', 'var'])
const goName = (name) => (goKeywords.has(name) ? `${name}Arg` : name)

// lua type-names, for the LuaLS definitions
const luaTypes = {
  void: 'nil',
  string: 'string',
  bool: 'boolean',
  i32: 'integer',
  f32: 'number',
  u32: 'integer',
  u64: 'integer',
  Image: 'integer',
  Font: 'integer',
  Sound: 'integer',
  ImageFilter: 'integer',
  Key: 'integer',
  GamepadButton: 'integer',
  MouseButton: 'integer',
  SfxPresetType: 'integer',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  SfxParams: 'SfxParams',
  'Vector[]': 'Vector[]'
}

const luaMemberTypes = { i32: 'integer', f32: 'number', u32: 'integer', u8: 'integer' }

// go name for a struct-table helper, e.g. Color -> colorArg/colorTable
const lower = (name) => name.charAt(0).toLowerCase() + name.slice(1)

// how a lua value is read into a go value
const luaReaders = {
  string: (name, i) => `${name}Bytes, ${name} := cstr(L.CheckString(${i}))`,
  bool: (name, i) => `${name} := boolArg(L, ${i})`,
  i32: (name, i) => `${name} := int32(L.CheckInt(${i}))`,
  f32: (name, i) => `${name} := float32(L.CheckNumber(${i}))`,
  u32: (name, i) => `${name} := uint32(L.CheckInt(${i}))`,
  u64: (name, i) => `${name} := uint64(L.CheckNumber(${i}))`,
  Image: (name, i) => `${name} := uint32(L.CheckInt(${i}))`,
  Font: (name, i) => `${name} := uint32(L.CheckInt(${i}))`,
  Sound: (name, i) => `${name} := uint32(L.CheckInt(${i}))`,
  ImageFilter: (name, i) => `${name} := int32(L.CheckInt(${i}))`,
  Key: (name, i) => `${name} := int32(L.CheckInt(${i}))`,
  GamepadButton: (name, i) => `${name} := int32(L.CheckInt(${i}))`,
  MouseButton: (name, i) => `${name} := int32(L.CheckInt(${i}))`,
  SfxPresetType: (name, i) => `${name} := int32(L.CheckInt(${i}))`,
  Color: (name, i) => `${name} := colorArg(L, ${i})`,
  SfxParams: (name, i) => `${name} := sfxParamsArg(L, ${i})`
}

// structs are passed by pointer, everything else by value
const structArgs = new Set(['Color', 'SfxParams'])

// ---- go: the interpreter ----

const go = [
  '// GENERATED FILE - do not edit by hand. See tools/gen_cart_lua.js',
  '//',
  '// The lua cart-runtime: a GopherLua VM with the null0 API bound to it. It',
  '// runs main.lua from the cart, then calls the callbacks the cart defined.',
  '',
  'package main',
  '',
  'import (',
  '\t"fmt"',
  '\t"os"',
  '\t"runtime"',
  '\t"unsafe"',
  '',
  '\tlua "github.com/yuin/gopher-lua"',
  ')',
  ''
]

// ---- struct definitions (must match the wasm C ABI exactly) ----
for (const [structName, structDef] of Object.entries(structs)) {
  go.push(`// ${structDef.description}`)
  go.push(`type ${structName} struct {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    go.push(`\t${memberName.charAt(0).toUpperCase() + memberName.slice(1)} ${goMemberTypes[memberType] || memberType}`)
  }
  go.push('}', '')
}

// ---- host imports ----
go.push('// HOST FUNCTIONS', '')
for (const [apiName, apiObj] of Object.entries(api)) {
  for (const [funcName, { args, returns }] of Object.entries(apiObj)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${goName(name)} ${goArgTypes[type]}`)
      .join(', ')
    go.push(`//go:wasmimport null0 ${funcName}`)
    go.push(`func ${funcName}(${params})${goRetTypes[returns] ? ' ' + goRetTypes[returns] : ''}`)
    go.push('')
  }
}

// ---- helpers ----
go.push(`// HELPERS

// memory the host allocated for us to keep (its malloc/free, in web builds)
var pinned = map[uint32][]byte{}

//go:wasmexport malloc
func malloc(size uint32) uint32 {
\tif size == 0 {
\t\tsize = 1
\t}
\tbuf := make([]byte, size)
\tptr := uint32(uintptr(unsafe.Pointer(&buf[0])))
\tpinned[ptr] = buf
\treturn ptr
}

//go:wasmexport free
func free(ptr uint32) {
\tdelete(pinned, ptr)
}

// a null-terminated copy of a lua string, for the host. keep the bytes
// alive (runtime.KeepAlive) until the host call has returned
func cstr(s string) ([]byte, unsafe.Pointer) {
\tb := append([]byte(s), 0)
\treturn b, unsafe.Pointer(&b[0])
}

func boolArg(L *lua.LState, n int) int32 {
\tif L.ToBool(n) {
\t\treturn 1
\t}
\treturn 0
}

func luaBool(v int32) lua.LBool {
\treturn lua.LBool(v != 0)
}

// a number out of a table-field, defaulting to 0 for anything else
func fieldNumber(t *lua.LTable, name string) float64 {
\tif n, ok := t.RawGetString(name).(lua.LNumber); ok {
\t\treturn float64(n)
\t}
\treturn 0
}
`)

// struct <-> table helpers
for (const [structName, structDef] of Object.entries(structs)) {
  const members = Object.entries(structDef.members)
  go.push(`// ${structName} arrives from lua as a table, e.g. {${members.map(([name]) => `${name} = 0`).join(', ')}}`)
  go.push(`func ${lower(structName)}Arg(L *lua.LState, n int) ${structName} {`)
  go.push('\tt := L.CheckTable(n)')
  go.push(`\treturn ${structName}{`)
  for (const [memberName, memberType] of members) {
    go.push(`\t\t${memberName.charAt(0).toUpperCase() + memberName.slice(1)}: ${goMemberTypes[memberType]}(fieldNumber(t, "${memberName}")),`)
  }
  go.push('\t}')
  go.push('}', '')

  go.push(`// ${structName} goes back to lua as a table`)
  go.push(`func ${lower(structName)}Table(L *lua.LState, v unsafe.Pointer) lua.LValue {`)
  go.push('\tif v == nil {')
  go.push('\t\treturn lua.LNil')
  go.push('\t}')
  go.push(`\ts := (*${structName})(v)`)
  go.push('\tt := L.NewTable()')
  for (const [memberName] of members) {
    go.push(`\tt.RawSetString("${memberName}", lua.LNumber(s.${memberName.charAt(0).toUpperCase() + memberName.slice(1)}))`)
  }
  go.push('\treturn t')
  go.push('}', '')
}

// a list of points arrives as an array-table of Vector tables
go.push(`// points arrive as an array of Vector tables, e.g. {{x = 1, y = 2}, ...}
func vectorsArg(L *lua.LState, n int) []Vector {
\tt := L.CheckTable(n)
\tcount := t.Len()
\tpoints := make([]Vector, 0, count)
\tfor i := 1; i <= count; i++ {
\t\tif item, ok := t.RawGetInt(i).(*lua.LTable); ok {
\t\t\tpoints = append(points, Vector{
\t\t\t\tX: int32(fieldNumber(item, "x")),
\t\t\t\tY: int32(fieldNumber(item, "y")),
\t\t\t})
\t\t}
\t}
\treturn points
}

// the address of the first point, or nil for an empty list
func pointsPtr(points []Vector) unsafe.Pointer {
\tif len(points) == 0 {
\t\treturn nil
\t}
\treturn unsafe.Pointer(&points[0])
}
`)

// ---- bindings ----

const registrations = []

go.push('// BINDINGS', '')

for (const [apiName, apiObj] of Object.entries(api)) {
  go.push(`// ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const entries = Object.entries(args)
    const lines = []
    const callArgs = []
    const keepAlive = []
    let luaIndex = 1

    for (let i = 0; i < entries.length; i++) {
      const [name, type] = entries[i]

      // a `T[]` arg is followed by its count in the API, but lua tables know
      // their own length, so the cart never passes it
      const goArg = goName(name)

      if (type === 'Vector[]') {
        lines.push(`\t${goArg} := vectorsArg(L, ${luaIndex})`)
        callArgs.push(`pointsPtr(${goArg})`, `int32(len(${goArg}))`)
        luaIndex++
        i++
        continue
      }

      lines.push(`\t${luaReaders[type](goArg, luaIndex)}`)
      callArgs.push(structArgs.has(type) ? `unsafe.Pointer(&${goArg})` : goArg)
      if (type === 'string') {
        keepAlive.push(`\truntime.KeepAlive(${goArg}Bytes)`)
      }
      luaIndex++
    }

    go.push(`// ${description}`)
    go.push(`func lua_${funcName}(L *lua.LState) int {`)
    go.push(...lines)

    const call = `${funcName}(${callArgs.join(', ')})`
    if (returns === 'void') {
      go.push(`\t${call}`)
      go.push(...keepAlive)
      go.push('\treturn 0')
    } else {
      go.push(`\tret := ${call}`)
      go.push(...keepAlive)
      if (returns === 'bool') {
        go.push('\tL.Push(luaBool(ret))')
      } else if (goRetTypes[returns] === 'unsafe.Pointer') {
        go.push(`\tL.Push(${lower(returns)}Table(L, ret))`)
      } else {
        go.push('\tL.Push(lua.LNumber(ret))')
      }
      go.push('\treturn 1')
    }
    go.push('}', '')

    registrations.push(`\tL.SetGlobal("${funcName}", L.NewFunction(lua_${funcName}))`)
  }
}

// ---- constants ----

go.push('// CONSTANTS', '')
go.push('func registerConstants(L *lua.LState) {')
go.push('\tL.SetGlobal("SCREEN", lua.LNumber(0))')
go.push('\tL.SetGlobal("SCREEN_WIDTH", lua.LNumber(640))')
go.push('\tL.SetGlobal("SCREEN_HEIGHT", lua.LNumber(480))')
go.push('\tL.SetGlobal("FONT_DEFAULT", lua.LNumber(0))')
for (const [name, def] of Object.entries(constants)) {
  if (def.type === 'Color') {
    const [r, g, b, a] = def.value
    go.push(`\tL.SetGlobal("${name}", colorTable(L, unsafe.Pointer(&Color{R: ${r}, G: ${g}, B: ${b}, A: ${a}})))`)
  } else if (def.type === 'string') {
    go.push(`\tL.SetGlobal("${name}", lua.LString(${JSON.stringify(def.value)}))`)
  }
}
for (const [enumName, enumDef] of Object.entries(enums)) {
  for (const [entryName, entryValue] of Object.entries(enumDef.enums)) {
    go.push(`\tL.SetGlobal("${entryName}", lua.LNumber(${entryValue}))`)
  }
}
go.push('}', '')

go.push('func registerAPI(L *lua.LState) {')
go.push(...registrations)
go.push('\tregisterConstants(L)')
go.push('}', '')

// ---- cart harness ----

go.push(`// CART

var L *lua.LState

// lua has a load() of its own, so the globals a callback could shadow are
// remembered before the cart runs: if one still holds the same value
// afterwards, the cart did not define that callback and we leave it alone
var stdGlobals = map[string]lua.LValue{}

func rememberStdGlobals(names ...string) {
\tfor _, name := range names {
\t\tstdGlobals[name] = L.GetGlobal(name)
\t}
}

// call a global lua function, if the cart defined one. errors are printed
// (Protect uses lua's pcall under the hood) instead of killing the cart
func callCart(name string, args ...lua.LValue) {
\tif L == nil {
\t\treturn
\t}
\tvalue := L.GetGlobal(name)
\tif std, isStd := stdGlobals[name]; isStd && std == value {
\t\treturn
\t}
\tfn, ok := value.(*lua.LFunction)
\tif !ok {
\t\treturn
\t}
\tif err := L.CallByParam(lua.P{Fn: fn, NRet: 0, Protect: true}, args...); err != nil {
\t\tfmt.Println("lua:", err)
\t}
}

//go:wasmexport load
func load() {
\t// cart files are read with an absolute path: go's wasip1 has no working
\t// directory to resolve a relative one against
\tsource, err := os.ReadFile("/main.lua")
\tif err != nil {
\t\tfmt.Println("lua: no main.lua in cart")
\t\treturn
\t}

\tL = lua.NewState()
\tregisterAPI(L)

\t// so require("thing") finds thing.lua in the cart
\tif pkg, ok := L.GetGlobal("package").(*lua.LTable); ok {
\t\tpkg.RawSetString("path", lua.LString("/?.lua;/?/init.lua"))
\t}

\trememberStdGlobals(${['load', 'update', 'unload'].concat(Object.keys(callbacks)).map((name) => `"${name}"`).join(', ')})

\tif err := L.DoString(string(source)); err != nil {
\t\tfmt.Println("lua:", err)
\t\tL = nil
\t\treturn
\t}

\tcallCart("load")
}

//go:wasmexport update
func update() {
\tcallCart("update")
}

//go:wasmexport unload
func unload() {
\tcallCart("unload")
\tif L != nil {
\t\tL.Close()
\t\tL = nil
\t}
}
`)

for (const [name, { args, description }] of Object.entries(callbacks)) {
  const entries = Object.entries(args)
  go.push(`// ${description}`)
  go.push(`//go:wasmexport ${name}`)
  go.push(`func ${name}(${entries.map(([argName, type]) => `${goName(argName)} ${goArgTypes[type]}`).join(', ')}) {`)
  go.push(`\tcallCart("${name}"${entries.length ? ', ' + entries.map(([argName]) => `lua.LNumber(${goName(argName)})`).join(', ') : ''})`)
  go.push('}', '')
}

go.push('// go needs a main, but the host never calls it: this is built as a wasi')
go.push('// reactor, so the runtime starts up in _initialize instead')
go.push('func main() {}')
go.push('')

// ---- lua: LuaLS definitions ----

const luaDef = [
  '---@meta',
  '',
  '-- null0 - lua definitions for the null0 fantasy console',
  '--',
  '-- GENERATED FILE - do not edit by hand. See tools/gen_cart_lua.js',
  '--',
  '-- The null0 API is available as plain globals in your cart - no require()',
  '-- needed, same as the JS/python carts. This file is only here so editors',
  '-- (any LuaLS-based one) can complete & check your cart:',
  '--',
  '-- ```lua',
  '-- function load()',
  '--   clear(BLUE)',
  '--   draw_circle(100, 100, 50, RED)',
  '-- end',
  '-- ```',
  ''
]

for (const [structName, structDef] of Object.entries(structs)) {
  luaDef.push(`---${structDef.description}`)
  luaDef.push(`---@class ${structName}`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    luaDef.push(`---@field ${memberName} ${luaMemberTypes[memberType] || memberType}`)
  }
  luaDef.push('')
}

for (const [apiName, apiObj] of Object.entries(api)) {
  luaDef.push(`-- ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const entries = Object.entries(args)
    const params = []
    luaDef.push(`---${description}`)
    for (let i = 0; i < entries.length; i++) {
      const [name, type] = entries[i]
      luaDef.push(`---@param ${name} ${luaTypes[type] || type}`)
      params.push(name)
      // the count that follows a `T[]` is implied by the table
      if (type === 'Vector[]') {
        i++
      }
    }
    if (returns !== 'void') {
      luaDef.push(`---@return ${luaTypes[returns] || returns}`)
    }
    luaDef.push(`function ${funcName}(${params.join(', ')}) end`)
    luaDef.push('')
  }
}

luaDef.push('-- CONSTANTS', '')
luaDef.push('---The screen is image 0')
luaDef.push('SCREEN = 0')
luaDef.push('SCREEN_WIDTH = 640')
luaDef.push('SCREEN_HEIGHT = 480')
luaDef.push('---The built-in font')
luaDef.push('FONT_DEFAULT = 0')
luaDef.push('')

for (const [name, def] of Object.entries(constants)) {
  if (def.type === 'Color') {
    const [r, g, b, a] = def.value
    luaDef.push('---@type Color')
    luaDef.push(`${name} = { r = ${r}, g = ${g}, b = ${b}, a = ${a} }`)
  } else if (def.type === 'string') {
    luaDef.push(`---${def.description}`)
    luaDef.push(`${name} = ${JSON.stringify(def.value)}`)
  }
}

for (const [enumName, enumDef] of Object.entries(enums)) {
  luaDef.push('', `-- ${enumDef.description}`)
  for (const [entryName, entryValue] of Object.entries(enumDef.enums)) {
    luaDef.push(`${entryName} = ${entryValue}`)
  }
}

luaDef.push('')
luaDef.push('-- CALLBACKS (implement the ones you need, in main.lua)')
luaDef.push('')
for (const [name, { args, description }] of Object.entries({ load: { args: {}, description: 'Called when the cart is loaded.' }, update: { args: {}, description: 'Called on every frame.' }, unload: { args: {}, description: 'Called when the cart is unloaded.' }, ...callbacks })) {
  luaDef.push(`---${description}`)
  for (const [argName, type] of Object.entries(args)) {
    luaDef.push(`---@param ${argName} ${luaTypes[type] || type}`)
  }
  luaDef.push(`function ${name}(${Object.keys(args).join(', ')}) end`)
  luaDef.push('')
}

await mkdir('tools/docker/lua-cart', { recursive: true })
await mkdir('carts/lua', { recursive: true })
await writeFile('tools/docker/lua-cart/main.go', go.join('\n'))
await writeFile('carts/lua/null0.lua', luaDef.join('\n'))

// tidy the generated go, if there is a gofmt around to do it
try {
  await promisify(execFile)('gofmt', ['-w', 'tools/docker/lua-cart/main.go'])
} catch {}
