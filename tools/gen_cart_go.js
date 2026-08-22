#!/usr/bin/env node

// Generator for Go (tinygo) null0 API bindings
// Generates Go code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'

// snake_case -> PascalCase
const lowerFirst = (name) => name.charAt(0).toLowerCase() + name.slice(1)
const pascal = (name) => name.split('_').map((p) => p.charAt(0).toUpperCase() + p.slice(1)).join('')

// Go keywords can't be used as parameter names
const goKeywords = new Set(['break', 'case', 'chan', 'const', 'continue', 'default', 'defer', 'else', 'fallthrough', 'for', 'func', 'go', 'goto', 'if', 'import', 'interface', 'map', 'package', 'range', 'return', 'select', 'struct', 'switch', 'type', 'var'])
const param = (name) => (goKeywords.has(name) ? `${name}_` : name)

const out = [
  `// Package null0 provides Go (tinygo) bindings for the null0 fantasy console.
//
// Usage:
//
// \`\`\`go
// package main
//
// import null0 "null0"
//
// //export load
// func load() {
//     null0.Clear(null0.BLUE)
//     null0.DrawCircle(100, 100, 50, null0.RED)
// }
//
// func main() {}
// \`\`\`
package null0

import "unsafe"

// Image is a handle to an image. 0 is "the screen".
type Image = uint32

// Font is a handle to a font. 0 is "the default font".
type Font = uint32

// Sound is a handle to a sound.
type Sound = uint32

// Tilemap is a handle to a tilemap (a Tiled map, exported as JSON).
type Tilemap = uint32

// NewColor creates a Color from r, g, b, a components.
func NewColor(r, g, b, a uint8) Color {
	return Color{R: r, G: g, B: b, A: a}
}

// RGB creates an opaque Color from r, g, b components.
func RGB(r, g, b uint8) Color {
	return NewColor(r, g, b, 255)
}

// cstr converts a Go string into a null-terminated string pointer.
func cstr(s string) unsafe.Pointer {
	b := append([]byte(s), 0)
	return unsafe.Pointer(&b[0])
}

// ptrToString converts a null-terminated string pointer into a Go string.
func ptrToString(p unsafe.Pointer) string {
	if p == nil {
		return ""
	}
	b := make([]byte, 0, 16)
	for i := uintptr(0); ; i++ {
		c := *(*byte)(unsafe.Add(p, i))
		if c == 0 {
			break
		}
		b = append(b, c)
	}
	return string(b)
}`
]

// raw (wasmimport) types: only numerics + pointers are allowed
const rawArgTypes = {
  string: 'unsafe.Pointer',
  bool: 'uint32',
  i32: 'int32',
  f32: 'float32',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'uint32',
  Font: 'uint32',
  Sound: 'uint32',
  Tilemap: 'uint32',
  ImageFilter: 'int32',
  Key: 'int32',
  GamepadButton: 'int32',
  MouseButton: 'int32',
  Color: 'unsafe.Pointer',
  Vector: 'unsafe.Pointer',
  Rectangle: 'unsafe.Pointer',
  Dimensions: 'unsafe.Pointer',
  'Vector[]': 'unsafe.Pointer',
  'i32[]': 'unsafe.Pointer',
  SfxParams: 'unsafe.Pointer',
  SfxPresetType: 'int32'
}

// nice wrapper types
const niceArgTypes = {
  string: 'string',
  bool: 'bool',
  i32: 'int32',
  f32: 'float32',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': '[]Vector',
  'i32[]': '[]int32',
  SfxParams: 'SfxParams',
  SfxPresetType: 'SfxPresetType'
}

const rawRetTypes = {
  void: null,
  string: 'unsafe.Pointer',
  bool: 'uint32',
  i32: 'int32',
  f32: 'float32',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'uint32',
  Font: 'uint32',
  Sound: 'uint32',
  Tilemap: 'uint32',
  Vector: 'unsafe.Pointer',
  Dimensions: 'unsafe.Pointer',
  Color: 'unsafe.Pointer',
  Rectangle: 'unsafe.Pointer',
  SfxParams: 'unsafe.Pointer',
  SfxPresetType: 'int32'
}

const niceRetTypes = {
  void: null,
  string: 'string',
  bool: 'bool',
  i32: 'int32',
  f32: 'float32',
  u32: 'uint32',
  u64: 'uint64',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  Vector: 'Vector',
  Dimensions: 'Dimensions',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams',
  SfxPresetType: 'SfxPresetType'
}

const memberTypes = {
  i32: 'int32',
  f32: 'float32',
  u32: 'uint32',
  u8: 'uint8',
  string: 'string'
}

// what a member looks like in the struct the host actually wrote into cart
// memory: every member 4 bytes, strings as pointers
const rawMemberTypes = { i32: 'int32', f32: 'float32', u32: 'uint32', u8: 'uint8', string: 'uint32' }
const rawMemberType = (type) => rawMemberTypes[type] || 'int32'

// convert a nice arg into its raw form for the wasmimport call
const rawConvert = (name, type) => {
  switch (type) {
    case 'string':
      return `cstr(${name})`
    case 'bool':
      return `boolToUint32(${name})`
    case 'Color':
    case 'Vector':
    case 'Dimensions':
    case 'Rectangle':
      return `unsafe.Pointer(&${name})`
    case 'Vector[]':
      return `vectorSliceToPtr(${name})`
    case 'i32[]':
      return `int32SliceToPtr(${name})`
    case 'SfxParams':
      return `unsafe.Pointer(&${name})`
    case 'Image':
    case 'Font':
    case 'Sound':
    case 'Tilemap':
    case 'i32':
    case 'f32':
    case 'u32':
    case 'u64':
      return name
    default:
      // enums
      return `int32(${name})`
  }
}

// convert raw result into nice type
const niceConvert = (type, expr) => {
  // a struct with strings in it needs its own reader (see stringStructs)
  if (stringStructs[type]) {
    return `${lowerFirst(type)}FromPtr(${expr})`
  }
  switch (type) {
    case 'string':
      return `ptrToString(${expr})`
    case 'bool':
      return `${expr} != 0`
    case 'Color':
    case 'Vector':
    case 'Dimensions':
    case 'Rectangle':
    case 'SfxParams':
      return `*(*${type})(${expr})`
    case 'Image':
    case 'Font':
    case 'Sound':
    case 'Tilemap':
    case 'i32':
    case 'f32':
    case 'u32':
    case 'u64':
      return expr
    default:
      return `${type}(${expr})`
  }
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// a new enum/struct fills its own type-map entries in
seedTypes(rawArgTypes, { enums, structs }, { enumType: 'int32', structType: 'unsafe.Pointer' })
seedTypes(niceArgTypes, { enums, structs }, { enumType: (name) => name, structType: (name) => name })
seedTypes(rawRetTypes, { enums, structs }, { enumType: 'int32', structType: 'unsafe.Pointer' })
seedTypes(niceRetTypes, { enums, structs }, { enumType: (name) => name, structType: (name) => name })

// structs carrying strings can't be copied straight out of cart memory - a Go
// string is not a pointer - so they get a cart-layout mirror and a converter
const stringStructs = Object.fromEntries(Object.entries(structs).filter(([, def]) => Object.values(def.members).includes('string')))

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `// ${structDef.description}`)
  out.push(`type ${structName} struct {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    const niceMemberName = pascal(memberName)
    out.push(`\t${niceMemberName} ${memberTypes[memberType] || memberType}`)
  }
  out.push('}')
}

// cart-layout mirrors + converters for the structs that carry strings
for (const [structName, structDef] of Object.entries(stringStructs)) {
  const members = Object.entries(structDef.members)
  out.push('', `// ${structName} as the host writes it into cart memory`)
  out.push(`type raw${structName} struct {`)
  for (const [memberName, memberType] of members) {
    out.push(`\t${pascal(memberName)} ${rawMemberType(memberType)}`)
  }
  out.push('}', '')
  out.push(`// copy a ${structName} out of cart memory, while it is still ours to read`)
  out.push(`func ${lowerFirst(structName)}FromPtr(p unsafe.Pointer) ${structName} {`)
  out.push(`\tif p == nil {`)
  out.push(`\t\treturn ${structName}{}`)
  out.push('\t}')
  out.push(`\tr := (*raw${structName})(p)`)
  out.push(`\treturn ${structName}{`)
  for (const [memberName, memberType] of members) {
    const field = pascal(memberName)
    if (memberType === 'string') {
      out.push(`\t\t${field}: ptrToString(unsafe.Pointer(uintptr(r.${field}))),`)
    } else if (enums[memberType]) {
      out.push(`\t\t${field}: ${memberType}(r.${field}),`)
    } else {
      out.push(`\t\t${field}: r.${field},`)
    }
  }
  out.push('\t}')
  out.push('}')
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `// ${enumDef.description}`)
  out.push(`type ${enumName} int32`, '', 'const (')
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`\t${enumValue} ${enumName} = ${enumNumber}`)
  }
  out.push(')')
}

// Generate constants
out.push('', '// Constants', 'const (')
out.push('\tSCREEN Image = 0')
out.push('\tSCREEN_WIDTH int32 = 640')
out.push('\tSCREEN_HEIGHT int32 = 480')
out.push('\tFONT_DEFAULT Font = 0')
out.push(')')
out.push('', '// Colors')
out.push('var (')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`\t${colorName} = Color{R: ${r}, G: ${g}, B: ${b}, A: ${a}}`)
  }
}
out.push(')')

out.push('', '// helpers used by wrappers', '', 'func boolToUint32(b bool) uint32 {', '\tif b {', '\t\treturn 1', '\t}', '\treturn 0', '}', '', 'func vectorSliceToPtr(vectors []Vector) unsafe.Pointer {', '\tif len(vectors) == 0 {', '\t\treturn nil', '\t}', '\treturn unsafe.Pointer(&vectors[0])', '}', '', 'func int32SliceToPtr(ints []int32) unsafe.Pointer {', '\tif len(ints) == 0 {', '\t\treturn nil', '\t}', '\treturn unsafe.Pointer(&ints[0])', '}')

// go puts types and funcs in one namespace, so a function whose pascal name
// matches a type (tile_layer_type vs a TileLayerType enum) will not compile.
// catch it here rather than in a cart build.
const goTypeNames = new Set([...Object.keys(structs), ...Object.keys(enums), 'Image', 'Font', 'Sound', 'Tilemap'])
for (const funcDef of Object.values(api)) {
  for (const funcName of Object.keys(funcDef)) {
    if (goTypeNames.has(pascal(funcName))) {
      throw new Error(`api function "${funcName}" collides with the go type ${pascal(funcName)} - rename one of them`)
    }
  }
}

// Generate raw wasmimport declarations + nice wrappers
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const rawParams = Object.entries(args).map(([name, type]) => `${param(name)} ${rawArgTypes[type] || type}`).join(', ')
    const rawRet = rawRetTypes[returns] ? ` ${rawRetTypes[returns]}` : ''

    out.push('', `//go:wasmimport null0 ${funcName}`)
    out.push(`func ${funcName}(${rawParams})${rawRet}`)

    const niceName = pascal(funcName)
    const niceParams = Object.entries(args).map(([name, type]) => `${param(name)} ${niceArgTypes[type] || type}`).join(', ')
    const niceRet = niceRetTypes[returns] ? ` ${niceRetTypes[returns]}` : ''
    const rawCallArgs = Object.entries(args).map(([name, type]) => rawConvert(param(name), type)).join(', ')
    const call = `${funcName}(${rawCallArgs})`

    out.push('', `// ${niceName}: ${description}`)
    out.push(`func ${niceName}(${niceParams})${niceRet} {`)
    if (rawRetTypes[returns]) {
      out.push(`\treturn ${niceConvert(returns, call)}`)
    } else {
      out.push(`\t${call}`)
    }
    out.push('}')
  }
}

out.push('')

await mkdir('carts/go/null0', { recursive: true })
await writeFile('carts/go/null0/null0.go', out.join('\n'))
await writeFile('carts/go/null0/go.mod', 'module null0\n\ngo 1.21\n')
