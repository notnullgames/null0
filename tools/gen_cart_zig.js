#!/usr/bin/env node

// Generator for Zig null0 API bindings
// Generates Zig code from the API definitions

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

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
// NOTE: host passes string/struct types as u32 pointers, Color is a single u32 (4 x u8)
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
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': '[*]const Vector',
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
  u8: 'u8'
}

const argsMap = (args) =>
  Object.entries(args)
    .map(([name, type]) => `${name}: ${argTypes[type] || type}`)
    .join(', ')

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

out.push('pub const Image = u32;')
out.push('pub const Font = u32;')
out.push('pub const Sound = u32;')
out.push('')
out.push('/// An RGBA color, packed into a single u32 (ABI-compatible with host)')
out.push('pub const Color = packed struct(u32) {')
out.push('    r: u8,')
out.push('    g: u8,')
out.push('    b: u8,')
out.push('    a: u8,')
out.push('')
out.push('    pub fn rgb(r: u8, g: u8, b: u8) Color {')
out.push('        return .{ .r = r, .g = g, .b = b, .a = 255 };')
out.push('    }')
out.push('};')

// Generate structs (Color handled above, since it is packed)
for (const [structName, structDef] of Object.entries(structs)) {
  if (structName === 'Color') continue
  out.push('', `/// ${structDef.description}`)
  out.push(`pub const ${structName} = extern struct {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberName}: ${memberTypes[memberType] || memberType} = 0,`)
  }
  out.push('};')
}

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
