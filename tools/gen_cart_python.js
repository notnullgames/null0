#!/usr/bin/env node

// Generator for Python null0 API bindings
// Generates Python code from the API definitions
//
// NOTE: py2wasm (CPython -> wasm) cannot currently declare custom host
// imports, so these bindings document the API surface. Functions call
// _host(), which a future runtime (or a CPython wasm build with null0
// imports) can provide.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const out = [
  `"""null0 - Python bindings for the null0 fantasy console.

Usage:

\`\`\`python
import null0

def load():
    null0.clear(null0.BLUE)
    null0.draw_circle(100, 100, 50, null0.RED)
\`\`\`

NOTE: py2wasm (CPython -> WebAssembly) cannot yet declare custom host
imports. These bindings document the full API surface; functions call
_host(), which a null0-aware Python runtime can provide.

ABI notes:
- handles (Image/Font/Sound), enums and bools are ints
- Color is 4 bytes packed into a single int: r | g<<8 | b<<16 | a<<24
- functions returning structs (Vector/Dimensions/Rectangle/Color/SfxParams)
  return a pointer (int) into cart memory
"""

from enum import IntEnum
from dataclasses import dataclass


def _host(name: str, *args):
    """Call a host function. Provided by a null0-aware Python runtime."""
    raise NotImplementedError(f"null0 host function '{name}' is not available in this runtime")


def rgba(r: int, g: int, b: int, a: int) -> int:
    """Create a Color from r, g, b, a components."""
    return (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | ((a & 0xFF) << 24)


def rgb(r: int, g: int, b: int) -> int:
    """Create an opaque Color from r, g, b components."""
    return rgba(r, g, b, 255)


# handle types
Image = int
Font = int
Sound = int
Color = int
`
]

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Generate structs
for (const [structName, structDef] of Object.entries(structs)) {
  if (structName === 'Color') continue
  out.push('', `# ${structDef.description}`, '@dataclass', `class ${structName}:`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    ${memberName}: ${memberType === 'u8' ? 'int' : memberType === 'f32' ? 'float' : 'int'}`)
  }
}

// Generate enums
for (const [enumName, enumDef] of Object.entries(enums)) {
  out.push('', `# ${enumDef.description}`, `class ${enumName}(IntEnum):`)
  for (const [enumValue, enumNumber] of Object.entries(enumDef.enums)) {
    out.push(`    ${enumValue} = ${enumNumber}`)
  }
}

// Generate constants
out.push('', '# Constants')
out.push('SCREEN: Image = 0')
out.push('SCREEN_WIDTH: int = 640')
out.push('SCREEN_HEIGHT: int = 480')
out.push('FONT_DEFAULT: Font = 0')
out.push('', '# Colors')
for (const [colorName, colorDef] of Object.entries(constants)) {
  if (colorDef.type === 'Color') {
    const [r, g, b, a] = colorDef.value
    const packed = ((a << 24) | (b << 16) | (g << 8) | r) >>> 0
    out.push(`${colorName}: Color = 0x${packed.toString(16).padStart(8, '0')}  # rgba(${r}, ${g}, ${b}, ${a})`)
  }
}

// type mapping for annotations
const pyType = (type) => {
  switch (type) {
    case 'f32':
      return 'float'
    case 'bool':
      return 'bool'
    case 'string':
      return 'str'
    case 'void':
      return 'None'
    default:
      return 'int'
  }
}

// Generate function stubs
for (const [apiName, funcDef] of Object.entries(api)) {
  out.push('', `# ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(funcDef)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${name}: ${pyType(type)}`)
      .join(', ')
    out.push('', `def ${funcName}(${params}) -> ${pyType(returns)}:`)
    out.push(`    """${description}"""`)
    const callArgs = ['funcName', ...Object.keys(args)].map((a) => (a === 'funcName' ? `"${funcName}"` : a)).join(', ')
    out.push(`    return _host(${callArgs})`)
  }
}

out.push('')

await mkdir('carts/python/null0', { recursive: true })
await writeFile('carts/python/null0/__init__.py', out.join('\n'))
