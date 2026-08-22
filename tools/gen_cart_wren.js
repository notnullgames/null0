#!/usr/bin/env node

// Generator for the interpreted-Wren null0 cart runtime.
//
// This writes 2 files:
//
// - carts/wren/null0.wren       the module carts `import "null0" for ...`
// - tools/docker/wren-cart.c    the interpreter (wren VM + null0 bindings)
//
// The wren module is baked into the interpreter (so carts don't need to ship
// it) but it's also written out, so it can be read/edited like the headers of
// the other languages.
//
// Wren has no top-level functions, so the API lives on a `Null0` class, and
// carts implement callbacks as module-level `Fn` variables:
//
// ```wren
// import "null0" for Null0, BLUE
//
// var update = Fn.new {
//   Null0.clear(BLUE)
// }
// ```
//
// Structs are wren classes (Color/Vector/Rectangle/Dimensions/SfxParams.) They
// are flattened before they cross into C: a Color travels as a packed rgba
// number, and the other structs as a list of their members.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi, seedTypes } from './utils.js'

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// structs that travel as a list of members (a Color is a packed number instead)
const listStructs = Object.keys(structs).filter((name) => name !== 'Color')

// structs carrying strings can't go through list_ret, which only knows doubles
const hasStrings = (structName) => Object.values(structs[structName].members).includes('string')

// C type for every arg-type
const cTypes = {
  string: 'char*',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'u32',
  Font: 'u32',
  Sound: 'u32',
  Tilemap: 'u32',
  ImageFilter: 'ImageFilter',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  SfxPresetType: 'SfxPresetType',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}

// C type of the value the host hands back (structs come back as pointers into cart-memory)
const cRetTypes = {
  string: 'char*',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'u32',
  u64: 'u64',
  Image: 'u32',
  Font: 'u32',
  Sound: 'u32',
  Tilemap: 'u32',
  Color: 'Color*',
  Vector: 'Vector*',
  Dimensions: 'Dimensions*',
  Rectangle: 'Rectangle*',
  SfxParams: 'SfxParams*'
}

seedTypes(cTypes, { enums, structs }, { enumType: (name) => name, structType: (name) => name })
seedTypes(cRetTypes, { enums, structs }, { enumType: (name) => name, structType: (name) => `${name}*` })

// how to pull an arg out of a wren slot
const cReaders = {
  string: (slot) => `(char*)string_arg(vm, ${slot})`,
  bool: (slot) => `bool_arg(vm, ${slot})`,
  i32: (slot) => `(i32)number_arg(vm, ${slot})`,
  f32: (slot) => `(f32)number_arg(vm, ${slot})`,
  u32: (slot) => `(u32)number_arg(vm, ${slot})`,
  u64: (slot) => `(u64)number_arg(vm, ${slot})`,
  Image: (slot) => `(u32)number_arg(vm, ${slot})`,
  Font: (slot) => `(u32)number_arg(vm, ${slot})`,
  Sound: (slot) => `(u32)number_arg(vm, ${slot})`,
  Tilemap: (slot) => `(u32)number_arg(vm, ${slot})`,
  ImageFilter: (slot) => `(ImageFilter)(i32)number_arg(vm, ${slot})`,
  Key: (slot) => `(Key)(i32)number_arg(vm, ${slot})`,
  GamepadButton: (slot) => `(GamepadButton)(i32)number_arg(vm, ${slot})`,
  MouseButton: (slot) => `(MouseButton)(i32)number_arg(vm, ${slot})`,
  SfxPresetType: (slot) => `(SfxPresetType)(i32)number_arg(vm, ${slot})`,
  Color: (slot) => `color_arg(vm, ${slot})`,
  Rectangle: (slot) => `rectangle_arg(vm, ${slot})`,
  SfxParams: (slot) => `sfxparams_arg(vm, ${slot})`
}

// how to push a return-value into slot 0
const cWriters = {
  bool: (v) => `wrenSetSlotBool(vm, 0, ${v});`,
  i32: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  f32: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  u32: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  u64: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  Image: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  Font: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  Sound: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  Tilemap: (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`,
  Color: (v) => `color_ret(vm, ${v});`,
  Vector: (v) => `vector_ret(vm, ${v});`,
  Dimensions: (v) => `dimensions_ret(vm, ${v});`,
  Rectangle: (v) => `rectangle_ret(vm, ${v});`,
  SfxParams: (v) => `sfxparams_ret(vm, ${v});`,
  string: (v) => `string_ret(vm, ${v});`
}

for (const name of Object.keys(enums)) {
  cWriters[name] = (v) => `wrenSetSlotDouble(vm, 0, (double)${v});`
}
for (const name of listStructs) {
  cWriters[name] = (v) => `${name.toLowerCase()}_ret(vm, ${v});`
}

// how a wren value is flattened for the foreign call
const wrenFlatten = {
  Color: (name) => `${name}.value`,
  Rectangle: (name) => `${name}.toList`,
  SfxParams: (name) => `${name}.toList`
}

// how a flattened return-value is turned back into a wren object
const wrenUnflatten = {
  Color: (expr) => `Color.fromValue(${expr})`,
  Vector: (expr) => `Vector.fromList(${expr})`,
  Dimensions: (expr) => `Dimensions.fromList(${expr})`,
  Rectangle: (expr) => `Rectangle.fromList(${expr})`,
  SfxParams: (expr) => `SfxParams.fromList(${expr})`
}

for (const name of listStructs) {
  wrenUnflatten[name] = (expr) => `${name}.fromList(${expr})`
}

// wren numbers are all doubles, so every member is read the same way
const memberCasts = { i32: 'i32', f32: 'f32', u32: 'u32', u8: 'u8' }

// work out how a function looks on both sides of the boundary
function plan(funcName, args) {
  const entries = Object.entries(args)
  const wrenArgs = [] // args the cart passes
  const rawArgs = [] // args handed to the foreign method
  const flatten = [] // wren lines that build a flat list first
  const reads = [] // C lines that pull args out of slots
  const callArgs = [] // args handed to the host
  const frees = [] // C lines to run after the call
  let slot = 1

  for (let i = 0; i < entries.length; i++) {
    const [name, type] = entries[i]

    // a `T[]` arg is followed by its count in the API, but the count is
    // implied by the wren list, so it never shows up in the cart's call
    if (type === 'Vector[]') {
      wrenArgs.push(name)
      rawArgs.push(`flat_${name}`)
      flatten.push(`    var flat_${name} = []`, `    for (v in ${name}) {`, `      flat_${name}.add(v.x)`, `      flat_${name}.add(v.y)`, '    }')
      reads.push(`  int ${name}_count = 0;`, `  Vector* ${name} = vectors_arg(vm, ${slot}, &${name}_count);`)
      callArgs.push(name, `${name}_count`)
      frees.push(`  free(${name});`)
      slot++
      i++
      continue
    }

    // a list of integers needs no flattening - it is read directly
    if (type === 'i32[]') {
      wrenArgs.push(name)
      rawArgs.push(name)
      reads.push(`  int ${name}_count = 0;`, `  i32* ${name} = ints_arg(vm, ${slot}, &${name}_count);`)
      callArgs.push(name, `${name}_count`)
      frees.push(`  free(${name});`)
      slot++
      i++
      continue
    }

    wrenArgs.push(name)
    rawArgs.push(wrenFlatten[type] ? wrenFlatten[type](name) : name)
    reads.push(`  ${cTypes[type]} ${name} = ${cReaders[type](slot)};`)
    callArgs.push(name)
    slot++
  }

  return { wrenArgs, rawArgs, flatten, reads, callArgs, frees }
}

// ---- wren module ----

const w = [
  '// null0 - Wren bindings for the null0 fantasy console',
  '//',
  '// GENERATED FILE - do not edit by hand. See tools/gen_cart_wren.js',
  '//',
  '// This module is baked into the wren cart-runtime, so carts can just do:',
  '//',
  '// ```wren',
  '// import "null0" for Null0, BLUE, RED',
  '//',
  '// var load = Fn.new {',
  '//   Null0.clear(BLUE)',
  '//   Null0.draw_circle(100, 100, 50, RED)',
  '// }',
  '// ```',
  '//',
  '// Callbacks (load/update/unload/buttonUp/buttonDown/keyUp/keyDown/mouseUp/',
  '// mouseDown/mouseMoved) are module-level Fn variables, in main.wren.',
  ''
]

// Color is packed into a single number when it crosses into C
w.push(
  `// ${structs.Color.description}`,
  'class Color {',
  '  construct new(r, g, b) {',
  '    _r = r',
  '    _g = g',
  '    _b = b',
  '    _a = 255',
  '  }',
  '',
  '  construct new(r, g, b, a) {',
  '    _r = r',
  '    _g = g',
  '    _b = b',
  '    _a = a',
  '  }',
  '',
  '  // Create a Color from a packed rgba number',
  '  static fromValue(v) { Color.new((v >> 24) & 0xff, (v >> 16) & 0xff, (v >> 8) & 0xff, v & 0xff) }',
  '',
  '  r { _r }',
  '  r=(v) { _r = v }',
  '  g { _g }',
  '  g=(v) { _g = v }',
  '  b { _b }',
  '  b=(v) { _b = v }',
  '  a { _a }',
  '  a=(v) { _a = v }',
  '',
  '  // The color as a single packed rgba number',
  '  value { ((_r & 0xff) << 24) | ((_g & 0xff) << 16) | ((_b & 0xff) << 8) | (_a & 0xff) }',
  '',
  '  ==(other) { other is Color && value == other.value }',
  '  !=(other) { !(this == other) }',
  '  toString { "Color(%(_r), %(_g), %(_b), %(_a))" }',
  '}',
  ''
)

// the rest of the structs travel as a list of their members
for (const structName of listStructs) {
  const members = Object.keys(structs[structName].members)
  w.push(`// ${structs[structName].description}`)
  w.push(`class ${structName} {`)

  // wren methods max out at 16 params, so a wide struct (SfxParams) starts
  // empty and gets filled in with its setters instead
  if (members.length > 16) {
    w.push('  // Every member starts at 0 - fill them in with the setters, or')
    w.push('  // start from Null0.sfx_generate(SFX_COIN) and tweak it')
    w.push('  construct new() {')
    for (const member of members) {
      w.push(`    _${member} = 0`)
    }
    w.push('  }', '')
    w.push(`  // Create a ${structName} from a list of its members`)
    w.push('  static fromList(l) {')
    w.push(`    var value = ${structName}.new()`)
    members.forEach((member, i) => {
      w.push(`    value.${member} = l[${i}]`)
    })
    w.push('    return value')
    w.push('  }')
  } else {
    w.push(`  construct new(${members.join(', ')}) {`)
    for (const member of members) {
      w.push(`    _${member} = ${member}`)
    }
    w.push('  }', '')
    w.push(`  // Create a ${structName} from a list of its members`)
    w.push(`  static fromList(l) { ${structName}.new(${members.map((m, i) => `l[${i}]`).join(', ')}) }`)
  }
  w.push('')
  for (const member of members) {
    w.push(`  ${member} { _${member} }`)
    w.push(`  ${member}=(v) { _${member} = v }`)
  }
  w.push('')
  w.push(`  // The members, in the order the null0 API wants them`)
  w.push(`  toList { [${members.map((m) => `_${m}`).join(', ')}] }`)
  w.push('')
  w.push(`  toString { "${structName}(${members.map((m) => `%(_${m})`).join(', ')})" }`)
  w.push('}', '')
}

w.push('// The null0 API', 'class Null0 {')

const cFuncs = []
const cBinds = []

for (const [apiName, apiObj] of Object.entries(api)) {
  w.push('', `  // ${apiName.toUpperCase()}`)
  cFuncs.push('', `// ${apiName.toUpperCase()}`, '')

  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const { wrenArgs, rawArgs, flatten, reads, callArgs, frees } = plan(funcName, args)
    const raw = `${funcName}_`

    // a wren method with no args is a getter, both to declare and to call
    const rawDecl = wrenArgs.length ? `${raw}(${rawArgs.map((a, i) => `a${i}`).join(', ')})` : raw
    const rawCall = wrenArgs.length ? `${raw}(${rawArgs.join(', ')})` : raw
    const wrapDecl = wrenArgs.length ? `${funcName}(${wrenArgs.join(', ')})` : funcName
    const result = wrenUnflatten[returns] ? wrenUnflatten[returns](rawCall) : rawCall

    w.push('')
    w.push(`  // ${description}`)
    w.push(`  foreign static ${rawDecl}`)
    if (flatten.length) {
      w.push(`  static ${wrapDecl} {`, ...flatten, `    return ${result}`, '  }')
    } else {
      w.push(`  static ${wrapDecl} { ${returns === 'void' ? rawCall : result} }`)
    }

    // the C side of the same function
    cFuncs.push(`// ${description}`)
    cFuncs.push(`static void wren_${funcName}(WrenVM* vm) {`)
    cFuncs.push(...reads)
    const call = `${funcName}(${callArgs.join(', ')})`
    if (returns === 'void') {
      cFuncs.push(`  ${call};`)
      cFuncs.push(...frees)
      cFuncs.push('  wrenSetSlotNull(vm, 0);')
    } else {
      cFuncs.push(`  ${cRetTypes[returns]} ret = ${call};`)
      cFuncs.push(...frees)
      cFuncs.push(`  ${cWriters[returns]('ret')}`)
    }
    cFuncs.push('}', '')

    const signature = wrenArgs.length ? `${raw}(${wrenArgs.map(() => '_').join(',')})` : raw
    cBinds.push(`  if (strcmp(signature, "${signature}") == 0) return wren_${funcName};`)
  }
}

w.push('}', '')

// ---- constants ----

w.push('// The screen is image 0', 'var SCREEN = 0')
w.push('var SCREEN_WIDTH = 640')
w.push('var SCREEN_HEIGHT = 480')
w.push('', '// The built-in font', 'var FONT_DEFAULT = 0')

w.push('', '// Colors')
for (const [name, def] of Object.entries(constants)) {
  if (def.type === 'Color') {
    const [r, g, b, a] = def.value
    w.push(`var ${name} = Color.new(${r}, ${g}, ${b}, ${a})`)
  } else if (def.type === 'string') {
    w.push('', `// ${def.description}`, `var ${name} = ${JSON.stringify(def.value)}`)
  }
}

for (const [enumName, enumDef] of Object.entries(enums)) {
  w.push('', `// ${enumDef.description}`)
  for (const [entryName, entryValue] of Object.entries(enumDef.enums)) {
    w.push(`var ${entryName} = ${entryValue}`)
  }
}

w.push('')

const wrenSource = w.join('\n')

// ---- C interpreter ----

// bake the wren module in as a string-literal, 1 line at a time
const cString = wrenSource
  .split('\n')
  .map((line) => `  "${line.replace(/\\/g, '\\\\').replace(/"/g, '\\"')}\\n"`)
  .join('\n')

const sfxMembers = Object.entries(structs.SfxParams.members)

const c = [
  '// GENERATED FILE - do not edit by hand. See tools/gen_cart_wren.js',
  '//',
  '// The wren cart-runtime: a wren VM with the null0 API bound to it. It runs',
  '// main.wren from the cart, then calls the callbacks the cart defined.',
  '',
  '#include "null0.h"',
  '#include "wren.h"',
  '',
  'static WrenVM* vm = NULL;',
  '',
  '// the null0 module, baked in so carts do not have to ship it',
  'static const char* NULL0_WREN =',
  cString,
  ';',
  '',
  '// ARG/RETURN HELPERS',
  '',
  '// wren is dynamically typed, so every arg is checked before it is used',
  'static double number_arg(WrenVM* vm, int slot) {',
  '  return wrenGetSlotType(vm, slot) == WREN_TYPE_NUM ? wrenGetSlotDouble(vm, slot) : 0;',
  '}',
  '',
  'static bool bool_arg(WrenVM* vm, int slot) {',
  '  return wrenGetSlotType(vm, slot) == WREN_TYPE_BOOL ? wrenGetSlotBool(vm, slot) : false;',
  '}',
  '',
  'static const char* string_arg(WrenVM* vm, int slot) {',
  '  return wrenGetSlotType(vm, slot) == WREN_TYPE_STRING ? wrenGetSlotString(vm, slot) : "";',
  '}',
  '',
  '// a Color arrives as a packed rgba number',
  'static Color color_arg(WrenVM* vm, int slot) {',
  '  u32 v = (u32)number_arg(vm, slot);',
  '  Color color = {(u8)((v >> 24) & 0xff), (u8)((v >> 16) & 0xff), (u8)((v >> 8) & 0xff), (u8)(v & 0xff)};',
  '  return color;',
  '}',
  '',
  '// wren hands out slots without clearing them, so a fresh scratch-slot is',
  '// nulled right away - the GC walks every slot, and would trip over whatever',
  '// was left in there',
  'static int scratch_slot(WrenVM* vm) {',
  '  int slot = wrenGetSlotCount(vm);',
  '  wrenEnsureSlots(vm, slot + 1);',
  '  wrenSetSlotNull(vm, slot);',
  '  return slot;',
  '}',
  '',
  '// read 1 number out of a wren list',
  'static double list_number(WrenVM* vm, int slot, int index, int scratch) {',
  '  wrenGetListElement(vm, slot, index, scratch);',
  '  return number_arg(vm, scratch);',
  '}',
  '',
  '// points arrive as a flat list of x/y numbers',
  'static Vector* vectors_arg(WrenVM* vm, int slot, int* count) {',
  '  *count = 0;',
  '  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {',
  '    return NULL;',
  '  }',
  '  int len = wrenGetListCount(vm, slot) / 2;',
  '  if (len < 1) {',
  '    return NULL;',
  '  }',
  '  Vector* points = malloc(sizeof(Vector) * len);',
  '  if (points == NULL) {',
  '    return NULL;',
  '  }',
  '  int scratch = scratch_slot(vm);',
  '  for (int i = 0; i < len; i++) {',
  '    points[i].x = (i32)list_number(vm, slot, i * 2, scratch);',
  '    points[i].y = (i32)list_number(vm, slot, (i * 2) + 1, scratch);',
  '  }',
  '  *count = len;',
  '  return points;',
  '}',
  '',
  '// a Rectangle arrives as a list of 4 numbers (x, y, width, height)',
  'static Rectangle rectangle_arg(WrenVM* vm, int slot) {',
  '  Rectangle rect = {0, 0, 0, 0};',
  '  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {',
  '    return rect;',
  '  }',
  '  int scratch = scratch_slot(vm);',
  '  rect.x = (i32)list_number(vm, slot, 0, scratch);',
  '  rect.y = (i32)list_number(vm, slot, 1, scratch);',
  '  rect.width = (i32)list_number(vm, slot, 2, scratch);',
  '  rect.height = (i32)list_number(vm, slot, 3, scratch);',
  '  return rect;',
  '}',
  '',
  '// a list of integers arrives as a wren list of numbers',
  'static i32* ints_arg(WrenVM* vm, int slot, int* count) {',
  '  *count = 0;',
  '  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {',
  '    return NULL;',
  '  }',
  '  int len = wrenGetListCount(vm, slot);',
  '  if (len < 1) {',
  '    return NULL;',
  '  }',
  '  i32* ints = malloc(sizeof(i32) * len);',
  '  if (ints == NULL) {',
  '    return NULL;',
  '  }',
  '  int scratch = scratch_slot(vm);',
  '  for (int i = 0; i < len; i++) {',
  '    ints[i] = (i32)list_number(vm, slot, i, scratch);',
  '  }',
  '  *count = len;',
  '  return ints;',
  '}',
  '',
  '// a SfxParams arrives as a list of its members',
  'static SfxParams sfxparams_arg(WrenVM* vm, int slot) {',
  '  SfxParams params = {0};',
  '  if (wrenGetSlotType(vm, slot) != WREN_TYPE_LIST) {',
  '    return params;',
  '  }',
  '  int len = wrenGetListCount(vm, slot);',
  '  int scratch = scratch_slot(vm);',
  ...sfxMembers.map(([name, type], i) => `  if (len > ${i}) params.${name} = (${memberCasts[type] || type})list_number(vm, slot, ${i}, scratch);`),
  '  return params;',
  '}',
  '',
  '// structs go back to wren as a list of their members',
  'static void list_ret(WrenVM* vm, double* values, int count) {',
  '  int scratch = scratch_slot(vm);',
  '  wrenSetSlotNewList(vm, 0);',
  '  for (int i = 0; i < count; i++) {',
  '    wrenSetSlotDouble(vm, scratch, values[i]);',
  '    wrenInsertInList(vm, 0, -1, scratch);',
  '  }',
  '}',
  '',
  '// a Color goes back as a packed rgba number',
  'static void color_ret(WrenVM* vm, Color* color) {',
  '  if (color == NULL) {',
  '    wrenSetSlotNull(vm, 0);',
  '    return;',
  '  }',
  '  wrenSetSlotDouble(vm, 0, (double)(((u32)color->r << 24) | ((u32)color->g << 16) | ((u32)color->b << 8) | (u32)color->a));',
  '}',
  ''
]

c.push('// a host string goes back as a wren string (NULL becomes "")')
c.push('static void string_ret(WrenVM* vm, char* value) {')
c.push('  wrenSetSlotString(vm, 0, value == NULL ? "" : value);')
c.push('}', '')

for (const structName of listStructs) {
  const members = Object.entries(structs[structName].members)
  c.push(`static void ${structName.toLowerCase()}_ret(WrenVM* vm, ${structName}* value) {`)
  c.push('  if (value == NULL) {')
  c.push('    wrenSetSlotNull(vm, 0);')
  c.push('    return;')
  c.push('  }')
  if (hasStrings(structName)) {
    // strings and numbers in one list, so push a member at a time
    c.push('  int scratch = scratch_slot(vm);')
    c.push('  wrenSetSlotNewList(vm, 0);')
    for (const [name, type] of members) {
      c.push(
        type === 'string'
          ? `  wrenSetSlotString(vm, scratch, value->${name} == NULL ? "" : value->${name});`
          : `  wrenSetSlotDouble(vm, scratch, (double)value->${name});`
      )
      c.push('  wrenInsertInList(vm, 0, -1, scratch);')
    }
  } else {
    c.push(`  double values[] = {${members.map(([name]) => `(double)value->${name}`).join(', ')}};`)
    c.push(`  list_ret(vm, values, ${members.length});`)
  }
  c.push('}', '')
}

c.push('// BINDINGS')
c.push(...cFuncs)

c.push('static WrenForeignMethodFn bind_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature) {')
c.push('  if (strcmp(className, "Null0") != 0) {')
c.push('    return NULL;')
c.push('  }')
c.push(...cBinds)
c.push('  return NULL;')
c.push('}')
c.push('')

// ---- cart harness ----

const cbSlots = { 0: 'call0', 1: 'call1', 2: 'call2' }

c.push(`// CART

static WrenHandle* call0 = NULL;
static WrenHandle* call1 = NULL;
static WrenHandle* call2 = NULL;
${Object.keys(callbacks)
  .concat(['update', 'unload'])
  .map((name) => `static WrenHandle* cb_${name} = NULL;`)
  .join('\n')}

static void write_fn(WrenVM* vm, const char* text) {
  printf("%s", text);
}

static void error_fn(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message) {
  if (type == WREN_ERROR_STACK_TRACE) {
    printf("  at %s:%d in %s\\n", module, line, message);
  } else if (module == NULL) {
    printf("wren: %s\\n", message);
  } else {
    printf("wren: %s:%d %s\\n", module, line, message);
  }
  fflush(stdout);
}

// read a whole file from the cart
static char* read_file(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char* text = malloc(size + 1);
  if (text == NULL) {
    fclose(file);
    return NULL;
  }
  size_t read = fread(text, 1, size, file);
  text[read] = '\\0';
  fclose(file);
  return text;
}

static void load_module_complete(WrenVM* vm, const char* name, WrenLoadModuleResult result) {
  // the baked-in module is not ours to free
  if (result.source != NULL0_WREN) {
    free((void*)result.source);
  }
}

// \`import "null0"\` gets the baked-in module, anything else is a file in the cart
static WrenLoadModuleResult load_module(WrenVM* vm, const char* name) {
  WrenLoadModuleResult result = {0};
  if (strcmp(name, "null0") == 0) {
    result.source = NULL0_WREN;
    return result;
  }
  char filename[512];
  snprintf(filename, sizeof(filename), "%s.wren", name);
  result.source = read_file(filename);
  result.onComplete = load_module_complete;
  return result;
}

// callbacks are module-level Fn variables in main.wren
static WrenHandle* get_callback(const char* name) {
  if (!wrenHasVariable(vm, "main", name)) {
    return NULL;
  }
  wrenEnsureSlots(vm, 1);
  wrenGetVariable(vm, "main", name, 0);
  // WREN_TYPE_UNKNOWN is any wren object, so this just skips a var that
  // is obviously not callable (a number, a string, null, ...)
  if (wrenGetSlotType(vm, 0) != WREN_TYPE_UNKNOWN) {
    return NULL;
  }
  return wrenGetSlotHandle(vm, 0);
}

int main() {
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = write_fn;
  config.errorFn = error_fn;
  config.loadModuleFn = load_module;
  config.bindForeignMethodFn = bind_foreign_method;
  vm = wrenNewVM(&config);

  char* source = read_file("main.wren");
  if (source == NULL) {
    printf("wren: no main.wren in cart\\n");
    fflush(stdout);
    return 1;
  }

  WrenInterpretResult result = wrenInterpret(vm, "main", source);
  free(source);
  if (result != WREN_RESULT_SUCCESS) {
    fflush(stdout);
    return 1;
  }

  call0 = wrenMakeCallHandle(vm, "call()");
  call1 = wrenMakeCallHandle(vm, "call(_)");
  call2 = wrenMakeCallHandle(vm, "call(_,_)");

${['update', 'unload']
  .concat(Object.keys(callbacks))
  .map((name) => `  cb_${name} = get_callback("${name}");`)
  .join('\n')}

  // load() is called here, since the host only calls _start on a wasi cart
  WrenHandle* cb_load = get_callback("load");
  if (cb_load != NULL) {
    wrenEnsureSlots(vm, 1);
    wrenSetSlotHandle(vm, 0, cb_load);
    wrenCall(vm, call0);
    wrenReleaseHandle(vm, cb_load);
  }
  fflush(stdout);
  return 0;
}

void update() {
  if (cb_update == NULL) {
    return;
  }
  wrenEnsureSlots(vm, 1);
  wrenSetSlotHandle(vm, 0, cb_update);
  wrenCall(vm, call0);
  fflush(stdout);
}

void unload() {
  if (cb_unload != NULL) {
    wrenEnsureSlots(vm, 1);
    wrenSetSlotHandle(vm, 0, cb_unload);
    wrenCall(vm, call0);
    fflush(stdout);
  }
}
`)

// the input-callbacks all look the same: set up the args, then call the Fn
for (const [name, { args, description }] of Object.entries(callbacks)) {
  const entries = Object.entries(args)
  c.push(`// ${description}`)
  c.push(`void ${name}(${entries.map(([argName, type]) => `${cTypes[type]} ${argName}`).join(', ')}) {`)
  c.push(`  if (cb_${name} == NULL) {`)
  c.push('    return;')
  c.push('  }')
  c.push(`  wrenEnsureSlots(vm, ${entries.length + 1});`)
  c.push(`  wrenSetSlotHandle(vm, 0, cb_${name});`)
  entries.forEach(([argName], i) => {
    c.push(`  wrenSetSlotDouble(vm, ${i + 1}, (double)${argName});`)
  })
  c.push(`  wrenCall(vm, ${cbSlots[entries.length]});`)
  c.push('  fflush(stdout);')
  c.push('}', '')
}

await mkdir('carts/wren', { recursive: true })
await writeFile('carts/wren/null0.wren', wrenSource)
await writeFile('tools/docker/wren-cart.c', c.join('\n'))
