#!/usr/bin/env node

// Generator for Rust null0 API bindings
// Generates Rust code from the API definitions

import { writeFile } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `//! # null0 - Rust bindings for the null0 fantasy console
//!
//! This crate provides Rust bindings for the null0 fantasy console API.
//! It allows you to create games that compile to WebAssembly and run in the null0 runtime.
//!
//! ## Usage
//!
//! Add this to your \`Cargo.toml\`:
//!
//! \`\`\`toml
//! [dependencies]
//! null0 = "0.1"
//! \`\`\`
//!
//! Then implement the required callbacks:
//!
//! \`\`\`rust
//! use null0::*;
//!
//! #[no_mangle]
//! pub extern "C" fn load() {
//!     // Initialize your game
//! }
//!
//! #[no_mangle]
//! pub extern "C" fn update() {
//!     // Update game logic (60 FPS)
//!     clear(BLACK);
//!     draw_text(FONT_DEFAULT, "Hello, null0!", 10, 10, WHITE);
//! }
//! \`\`\`

#![no_std]

// Type definitions`
]

// Type mapping from API types to Rust types
const argTypes = {
  string: '*const u8',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'u32',
  Font: 'u32',
  Sound: 'u32',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': '*const Vector',
  SfxParams: 'SfxParams',
  SfxPresetType: 'SfxPresetType'
}

const retTypes = {
  void: null, // void functions have no return type
  string: '*const u8',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'u32',
  Font: 'u32',
  Sound: 'u32',
  Vector: 'Vector',
  Dimensions: 'Dimensions',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}

// Type mapping for struct member types
const memberTypes = {
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u8: 'u8'
}

// Reserved keywords in Rust that need to be escaped
const rustReservedKeywords = new Set(['type', 'impl', 'trait', 'struct', 'enum', 'fn', 'let', 'mut', 'const', 'static', 'if', 'else', 'match', 'for', 'while', 'loop', 'break', 'continue', 'return', 'mod', 'pub', 'use', 'extern', 'crate', 'super', 'self', 'Self', 'where', 'unsafe', 'async', 'await', 'move', 'ref', 'in', 'as', 'dyn', 'abstract', 'become', 'box', 'do', 'final', 'macro', 'override', 'priv', 'typeof', 'unsized', 'virtual', 'yield', 'try'])

// Generate parameter list for function signature
const argsMap = (args) => {
  const params = Object.entries(args).map(([name, type]) => {
    // Escape reserved keywords by adding r# prefix
    const paramName = rustReservedKeywords.has(name) ? `r#${name}` : name
    return `${paramName}: ${argTypes[type] || type}`
  })
  return params.join(', ')
}

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  out.push('', `/// ${structDef.description}`)
  out.push(`#[repr(C)]`)
  out.push(`#[derive(Debug, Clone, Copy, PartialEq)]`)
  out.push(`pub struct ${structName} {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    pub ${memberName}: ${memberTypes[memberType] || memberType},`)
  }
  out.push(`}`)
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `/// ${enumDef.description}`)
  out.push(`#[repr(i32)]`)
  out.push(`#[derive(Debug, Clone, Copy, PartialEq, Eq)]`)
  out.push(`pub enum ${enumName} {`)
  const enumEntries = Object.entries(enumDef.enums)
  for (const [enumValue, enumNumber] of enumEntries) {
    out.push(`    ${enumValue} = ${enumNumber},`)
  }
  out.push(`}`)
}

// Generate constants
out.push('', '// Screen and font constants')
out.push('pub const SCREEN: u32 = 0;')
out.push('pub const SCREEN_WIDTH: i32 = 640;')
out.push('pub const SCREEN_HEIGHT: i32 = 480;')
out.push('pub const FONT_DEFAULT: u32 = 0;')

out.push('', '// Color constants')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    out.push(`pub const ${colorName}: Color = Color { r: ${r}, g: ${g}, b: ${b}, a: ${a} };`)
  }
}

// Generate extern "C" block for imported functions
out.push('', 'extern "C" {')

// Generate function declarations
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push(`    // ${apiName.charAt(0).toUpperCase() + apiName.slice(1)} functions`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const rustReturn = retTypes[returns]
    const paramList = argsMap(args)
    const returnType = rustReturn ? ` -> ${rustReturn}` : ''

    // Generate function declaration with description
    out.push(`    /// ${description}`)
    out.push(`    pub fn ${funcName}(${paramList})${returnType};`)
  }
  out.push('')
}

out.push('}')

// Generate convenience functions and implementations
out.push('', '// Convenience implementations')

// Add Color constructor
out.push(`impl Color {
    /// Create a new Color
    pub const fn new(r: u8, g: u8, b: u8, a: u8) -> Self {
        Self { r, g, b, a }
    }
    
    /// Create a new Color with full opacity
    pub const fn rgb(r: u8, g: u8, b: u8) -> Self {
        Self { r, g, b, a: 255 }
    }
}`)

// Add Vector constructor
out.push(`
impl Vector {
    /// Create a new Vector
    pub const fn new(x: i32, y: i32) -> Self {
        Self { x, y }
    }
}`)

// Add Rectangle constructor
out.push(`
impl Rectangle {
    /// Create a new Rectangle
    pub const fn new(x: i32, y: i32, width: i32, height: i32) -> Self {
        Self { x, y, width, height }
    }
}`)

// Add Dimensions constructor
out.push(`
impl Dimensions {
    /// Create a new Dimensions
    pub const fn new(width: u32, height: u32) -> Self {
        Self { width, height }
    }
}`)

// Add string helper functions
out.push(`
/// Convert a Rust string to a C-compatible string pointer
/// 
/// # Safety
/// The returned pointer is only valid as long as the input string slice is valid.
/// The string must be null-terminated.
pub fn str_to_cstr(s: &str) -> *const u8 {
    s.as_ptr()
}

/// Helper macro to create null-terminated string literals
#[macro_export]
macro_rules! cstr {
    ($s:expr) => {
        concat!($s, "\\0").as_ptr()
    };
}

/// Re-export everything for convenience
pub use self::*;`)

await writeFile('carts/rust/src/lib.rs', out.join('\n'))
