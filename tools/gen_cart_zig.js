#!/usr/bin/env node

// Generator for Zig null0 API bindings
// Generates Zig code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'

const out = [
  `//! null0 - Zig bindings for the null0 fantasy console
//!
//! Usage:
//!
//! \`\`\`zig
//! const null0 = @import("null0.zig");
//!
//! export fn load() void {
//!     null0.clear(null0.BLUE);
//!     null0.draw_circle(100, 100, 50, null0.RED);
//! }
//! \`\`\`

const std = @import("std");

// basic memory-management from host (used when host returns strings/structs)

export fn malloc(size: usize) ?*anyopaque {
    const buf = std.heap.wasm_allocator.alloc(u8, size) catch return null;
    return @ptrCast(buf.ptr);
}

export fn free(ptr: ?*anyopaque) void {
    // carts are short-lived, let the wasm linear-memory absorb it
    _ = ptr;
}

// scalar types`
]

// map of def-types into across-wasm types
// NOTE: host passes string/struct types as u32 pointers. Color/Vector/etc
// are `extern struct`s so zig's own wasm32 ABI passes them by reference to
// match - do NOT use `packed struct(u32)` for these, it makes zig pack the
// struct into a register value instead of passing a pointer, which the host
// doesn't expect
const argTypes = {
  string: '[*:0]const u8',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
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
  'Vector[]': '[*]const Vector',
  'i32[]': '[*]const i32',
  SfxParams: '*const SfxParams',
  SfxPresetType: 'SfxPresetType'
}

// host returns structs/strings as pointers into cart-memory
const retTypes = {
  void: 'void',
  string: '[*:0]u8',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  Vector: '*Vector',
  Dimensions: '*Dimensions',
  Color: '*Color',
  Rectangle: '*Rectangle',
  SfxParams: '*SfxParams',
  SfxPresetType: 'SfxPresetType'
}

const memberTypes = {
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u8: 'u8',
  string: '[*:0]u8'
}

// zig wants a valid default for every field, and 0 is only one for the numbers
const memberDefault = (type) => (type === 'string' ? 'undefined' : enums[type] ? '@enumFromInt(0)' : '0')

const argsMap = (args) =>
  Object.entries(args)
    .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
    .join(', ')

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// a new struct fills itself in: passed by reference, and returned as a
// pointer into cart memory. enums already carry their own type name through
seedTypes(argTypes, { structs }, { structType: (name) => name })
seedTypes(retTypes, { structs }, { structType: (name) => `*${name}` })

out.push('pub const Image = u32;')
out.push('pub const Font = u32;')
out.push('pub const Sound = u32;')
out.push('pub const Tilemap = u32;')
out.push('')
// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `/// ${structDef.description}`)
  out.push(`pub const ${structName} = extern struct {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberName}: ${memberTypes[memberType] || memberType} = ${memberDefault(memberType)},`)
  }
  out.push('};')
}

out.push('')
out.push('/// Create a Color from r, g, b, a components')
out.push('pub fn rgba(r: u8, g: u8, b: u8, a: u8) Color {')
out.push('    return .{ .r = r, .g = g, .b = b, .a = a };')
out.push('}')
out.push('')
out.push('/// Create an opaque Color from r, g, b components')
out.push('pub fn rgb(r: u8, g: u8, b: u8) Color {')
out.push('    return rgba(r, g, b, 255);')
out.push('}')

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `/// ${enumDef.description}`)
  out.push(`pub const ${enumName} = enum(i32) {`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`    ${enumValue} = ${enumNumber},`)
  }
  out.push('};')
}

// Generate constants
out.push('', '// Constants')
out.push('pub const SCREEN: Image = 0;')
out.push('pub const SCREEN_WIDTH: i32 = 640;')
out.push('pub const SCREEN_HEIGHT: i32 = 480;')
out.push('pub const FONT_DEFAULT: Font = 0;')
out.push('')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`pub const ${colorName}: Color = .{ .r = ${r}, .g = ${g}, .b = ${b}, .a = ${a} };`)
  }
}

// Generate function declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `// ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    out.push(`/// ${description}`)
    out.push(`pub extern "null0" fn ${funcName}(${argsMap(args)}) ${retTypes[returns] || returns};`)
  }
}

out.push('')

await mkdir('carts/zig', { recursive: true })
await writeFile('carts/zig/null0.zig', out.join('\n'))
