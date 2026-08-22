#!/usr/bin/env node

// Generator for the interpreted-Cyber null0 cart runtime.
//
// This writes 2 files:
//
// - carts/cyber/null0.cy       the module carts `use null0`
// - tools/docker/cyber-cart.c  the interpreter (Cyber VM + null0 bindings)
//
// Cyber's public embedding API (libcyber) has no way to re-invoke a
// script-defined function after the initial eval - `cl_vm_eval` only runs a
// script once. The fix is `persist_main` (an eval config flag documented
// "for REPL-like behavior"): the main script is eval'd once with
// persist_main, defining `load`/`update`/... as top-level fns, then each
// null0 callback (host-called, possibly many times) re-evals a *tiny*
// snippet like `"update()"` with the same flag - the VM's state (including
// those fns) persists across separate eval calls. Callback arguments are
// passed through two bound globals (__a0/__a1) rather than string-formatted
// into the snippet, to avoid float precision/formatting issues.
//
// Structs cross as pointers (`cl_thread_param`/`cl_thread_ret`), matching
// every other cart language - Cyber's own `struct` types mirror C layout,
// verified with a hand-written r/g/b/a byte-struct round-trip.

import { writeFile, mkdir } from 'node:fs/promises'
import { getApi } from './utils.js'

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

const structNames = Object.keys(structs)
const listArrayTypes = { 'Vector[]': 'Vector', 'i32[]': 'i32' }

// Cyber type for a struct member
const memberCyType = { i32: 'i32', f32: 'f32', u32: 'r32', u8: 'byte', string: 'str' }
for (const name of Object.keys(enums)) memberCyType[name] = 'i32'

// structs carrying strings can't be copied straight across: cyber holds a str
// as a CLstr, so they get a cyber-layout mirror the shim fills in member by member
const cMemberType = { i32: 'int32_t', f32: 'float', u32: 'uint32_t', u8: 'unsigned char', string: 'CLstr' }
const cMirrorType = (type) => cMemberType[type] || 'int32_t'
const stringStructs = Object.keys(structs).filter((name) => Object.values(structs[name].members).includes('string'))

// Cyber type for a null0 arg/return type
const cyType = {
  string: 'str',
  bool: 'bool',
  i32: 'i32',
  f32: 'f32',
  u32: 'r32',
  u64: 'r64',
  Image: 'r32',
  Font: 'r32',
  Sound: 'r32',
  Tilemap: 'r32',
  ImageFilter: 'i32',
  Key: 'i32',
  GamepadButton: 'i32',
  MouseButton: 'i32',
  SfxPresetType: 'i32',
  Color: 'Color',
  Rectangle: 'Rectangle',
  SfxParams: 'SfxParams'
}
for (const s of structNames) cyType[s] = s
for (const name of Object.keys(enums)) cyType[name] = 'i32'

// C type used at the cl_thread_* boundary
const cScalarType = {
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
  ImageFilter: 'i32',
  Key: 'i32',
  GamepadButton: 'i32',
  MouseButton: 'i32',
  SfxPresetType: 'i32'
}
for (const name of Object.keys(enums)) cScalarType[name] = 'i32'

// how to pull a scalar arg out of the CLThread
const cThreadReader = {
  bool: () => 'cl_thread_i32(t) != 0',
  i32: () => 'cl_thread_i32(t)',
  f32: () => 'cl_thread_f32(t)',
  u32: () => '(u32)cl_thread_r32(t)',
  u64: () => '(u64)cl_thread_r64(t)',
  Image: () => '(u32)cl_thread_r32(t)',
  Font: () => '(u32)cl_thread_r32(t)',
  Sound: () => '(u32)cl_thread_r32(t)',
  Tilemap: () => '(u32)cl_thread_r32(t)',
  ImageFilter: () => '(ImageFilter)cl_thread_i32(t)',
  Key: () => '(Key)cl_thread_i32(t)',
  GamepadButton: () => '(GamepadButton)cl_thread_i32(t)',
  MouseButton: () => '(MouseButton)cl_thread_i32(t)',
  SfxPresetType: () => '(SfxPresetType)cl_thread_i32(t)'
}

// Cyber's reserved words that show up as null0 arg names
const cyKeywords = new Set([
  'if', 'else', 'switch', 'case', 'while', 'for', 'break', 'continue', 'pass', 'or', 'and', 'not',
  'var', 'global', 'fn', 'return', 'move', 'yield', 'type', 'with', 'try', 'use',
  'self', 'Self', 'struct', 'cstruct', 'enum', 'cunion', 'trait', 'scope', 'sink', 'void',
  'true', 'false', 'error', 'none', 'undef'
])
const escapeArg = (name) => (cyKeywords.has(name) ? `${name}_` : name)

// plan a function's args: how it looks in Cyber source and in the C binding
function plan(rawArgs) {
  const entries = Object.entries(rawArgs).map(([name, type]) => [escapeArg(name), type])
  const cyParams = [] // "name type" for the #[bind] fn decl
  const reads = [] // C lines pulling args out of the thread (after the ret pointer is acquired)
  const callArgs = [] // C expressions to pass to the null0 import
  const frees = [] // C lines to run after the call

  for (let i = 0; i < entries.length; i++) {
    const [name, type] = entries[i]

    if (listArrayTypes[type]) {
      const elem = listArrayTypes[type]
      cyParams.push(`${name} []${cyType[elem]}`)
      reads.push(`  CLSlice ${name}_slice = cl_thread_slice(t);`)
      callArgs.push(name, `(u32)${name}_slice.len`)
      if (elem === 'Vector') {
        reads.push(`  Vector* ${name} = (Vector*)${name}_slice.ptr;`)
      } else {
        reads.push(`  i32* ${name} = (i32*)${name}_slice.ptr;`)
      }
      i++ // the yml's trailing count arg is implicit in the slice length
      continue
    }

    cyParams.push(`${name} ${cyType[type]}`)

    if (type === 'string') {
      // CLstr's bytes are not null-terminated, but null0's C API expects
      // char* - copy into a scratch buffer we null-terminate ourselves
      reads.push(
        `  CLstr ${name}_s = cl_thread_str(t);`,
        `  CLBytes ${name}_b = cl_str_bytes(${name}_s);`,
        `  char* ${name} = malloc(${name}_b.len + 1);`,
        `  memcpy(${name}, ${name}_b.ptr, ${name}_b.len);`,
        `  ${name}[${name}_b.len] = '\\0';`
      )
      callArgs.push(name)
      frees.push(`  free(${name});`)
    } else if (structNames.includes(type)) {
      reads.push(`  ${type}* ${name} = (${type}*)cl_thread_param(t, sizeof(${type}));`)
      callArgs.push(`*${name}`)
    } else {
      reads.push(`  ${cScalarType[type]} ${name} = ${cThreadReader[type]()};`)
      callArgs.push(name)
    }
  }

  return { cyParams, reads, callArgs, frees }
}

// ==================================================================
// carts/cyber/null0.cy
// ==================================================================

const cy = [
  '-- null0 - Cyber bindings for the null0 fantasy console',
  '--',
  '-- GENERATED FILE - do not edit by hand. See tools/gen_cart_cyber.js',
  '--',
  '-- This module is baked into the cyber cart-runtime, so carts can just do:',
  '--',
  '-- ```cyber',
  '-- use null0',
  '--',
  '-- fn load():',
  '--   null0.clear(null0.BLUE)',
  '--   null0.draw_circle(100, 100, 50, null0.RED)',
  '-- ```',
  '--',
  '-- Callbacks (load/update/unload/buttonUp/buttonDown/keyUp/keyDown/mouseUp/',
  '-- mouseDown/mouseMoved) are top-level fns in main.cy - implement the ones',
  '-- you need.',
  ''
]

for (const structName of structNames) {
  const members = Object.entries(structs[structName].members)
  cy.push(`-- ${structs[structName].description}`)
  cy.push(`type ${structName} struct:`)
  for (const [name, type] of members) {
    cy.push(`  ${name} ${memberCyType[type]}`)
  }
  cy.push('')
}

for (const [apiName, apiObj] of Object.entries(api)) {
  cy.push(`-- ${apiName.toUpperCase()}`)
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const { cyParams } = plan(args)
    const ret = returns === 'void' ? '' : ` -> ${cyType[returns]}`
    cy.push(`-- ${description}`)
    cy.push(`#[bind] fn ${funcName}(${cyParams.join(', ')})${ret}`)
  }
  cy.push('')
}

// These are all fixed at generate time (screen/font handles are always 0,
// colors/enum values are yml literals) - plain `global NAME TYPE = value`
// declarations, not `#[bind]`. That matters beyond style: `#[bind] global`
// panics the compiler past a few dozen (verified: fine as a fn param/return
// or struct member, only breaks as a *bound* global, and only at scale -
// one alone is fine, ~150 of them is not). Plain globals have no such limit.
cy.push('-- The screen is image 0', 'global SCREEN i32 = 0')
cy.push('global SCREEN_WIDTH i32 = 640')
cy.push('global SCREEN_HEIGHT i32 = 480')
cy.push('-- The built-in font', 'global FONT_DEFAULT i32 = 0')
cy.push('')
for (const [name, def] of Object.entries(constants)) {
  if (def.type === 'Color') {
    const [r, g, b, a] = def.value
    cy.push(`global ${name} Color = Color{r=${r}, g=${g}, b=${b}, a=${a}}`)
  } else if (def.type === 'string') {
    cy.push(`-- ${def.description}`, `global ${name} str = '${def.value}'`)
  }
}
cy.push('')
for (const [enumName, enumDef] of Object.entries(enums)) {
  cy.push(`-- ${enumDef.description}`)
  for (const [entryName, entryValue] of Object.entries(enumDef.enums)) {
    cy.push(`global ${entryName} i32 = ${entryValue}`)
  }
}
cy.push('')

const cySource = cy.join('\n')

// ==================================================================
// tools/docker/cyber-cart.c
// ==================================================================

const c = [
  '// GENERATED FILE - do not edit by hand. See tools/gen_cart_cyber.js',
  '//',
  '// The cyber cart-runtime: a Cyber VM with the null0 API bound to it. It',
  '// evals main.cy from the cart once (with persist_main, so its top-level',
  '// fns/vars stay in scope), then re-evals tiny snippets like "update()" to',
  '// invoke callbacks - see the comment in gen_cart_cyber.js for why.',
  '',
  '#include "null0.h"',
  '#include "cyber.h"',
  '#include <string.h>',
  '',
  'static CLVM* vm = NULL;',
  'static CLEvalConfig persist_cfg;',
  '',
  '// two generic slots for passing callback args into a snippet eval,',
  '// without string-formatting numbers into source text',
  'static f32 g_a0 = 0;',
  'static f32 g_a1 = 0;',
  '',
  '// the null0 module, baked in so carts do not have to ship it',
  'static const char* NULL0_CY =',
  cySource
    .split('\n')
    .map((line) => `  "${line.replace(/\\/g, '\\\\').replace(/"/g, '\\"')}\\n"`)
    .join('\n'),
  ';',
  ''
]

// Color/Vector/Rectangle/Dimensions/SfxParams are already declared by
// null0.h (included above) - no need to redeclare them here.

// cyber lays a `str` field out as a CLstr, so a struct carrying one can't be
// copied straight from the host - these mirrors are filled member by member
for (const structName of stringStructs) {
  c.push(`// ${structName} as cyber lays it out`)
  c.push('typedef struct {')
  for (const [name, type] of Object.entries(structs[structName].members)) {
    c.push(`  ${cMirrorType(type)} ${name};`)
  }
  c.push(`} Cy${structName};`, '')
}

c.push('// BINDINGS', '')

const cBinds = []

for (const [apiName, apiObj] of Object.entries(api)) {
  c.push('', `// ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const { reads, callArgs, frees } = plan(args)
    c.push(`// ${description}`)
    c.push(`static CLRet cyber_${funcName}(CLThread* t) {`)
    // cl_thread_ret() MUST be called first, even for void - it sets fp_end,
    // the pointer params are read relative to. Reading params before this
    // corrupts them.
    if (returns === 'void') {
      c.push('  cl_thread_ret(t, 0);')
    } else if (stringStructs.includes(returns)) {
      c.push(`  Cy${returns}* out = (Cy${returns}*)cl_thread_ret(t, sizeof(Cy${returns}));`)
    } else if (structNames.includes(returns)) {
      c.push(`  ${returns}* out = (${returns}*)cl_thread_ret(t, sizeof(${returns}));`)
    } else if (returns === 'string') {
      c.push('  CLstr* out = (CLstr*)cl_thread_ret(t, sizeof(CLstr));')
    } else {
      c.push(`  ${cScalarType[returns]}* out = (${cScalarType[returns]}*)cl_thread_ret(t, sizeof(${cScalarType[returns]}));`)
    }
    c.push(...reads)
    const call = `${funcName}(${callArgs.join(', ')})`
    if (returns === 'void') {
      c.push(`  ${call};`)
    } else if (stringStructs.includes(returns)) {
      c.push(`  ${returns}* ret = ${call};`)
      for (const [name, type] of Object.entries(structs[returns].members)) {
        c.push(
          type === 'string'
            ? `  out->${name} = cl_ustr_init(t, CL_BYTES(ret->${name} == NULL ? "" : ret->${name}));`
            : `  out->${name} = ret->${name};`
        )
      }
    } else if (structNames.includes(returns)) {
      c.push(`  ${returns}* ret = ${call};`)
      c.push('  *out = *ret;')
    } else if (returns === 'string') {
      c.push(`  char* ret = ${call};`)
      c.push('  *out = cl_ustr_init(t, CL_BYTES(ret));')
    } else {
      c.push(`  ${cScalarType[returns]} ret = ${call};`)
      c.push('  *out = ret;')
    }
    c.push(...frees)
    c.push('  return CL_RET_OK;', '}', '')
    cBinds.push(`  cl_mod_add_func(mod, CL_BYTES("${funcName}"), CL_BIND_FUNC(cyber_${funcName}));`)
  }
}

c.push(
  '// module loader: `use null0` resolves to the baked-in module above.',
  '// Screen/font handles, colors and enum values are all plain `global',
  '// NAME TYPE = value` declarations inside NULL0_CY, not `#[bind] global`',
  '// - see gen_cart_cyber.js for why. Only the two frame-arg slots below',
  '// are real host-bound globals (they need to be host-writable).',
  'static bool module_loader(CLVM* vmp, CLSym* mod, CLBytes uri, CLLoaderResult* res) {',
  '  if (uri.len == 5 && strncmp(uri.ptr, "null0", 5) == 0) {',
  ...cBinds,
  '    cl_mod_add_global(mod, CL_BYTES("__a0"), CL_BIND_GLOBAL(&g_a0));',
  '    cl_mod_add_global(mod, CL_BYTES("__a1"), CL_BIND_GLOBAL(&g_a1));',
  '    res->src = CL_BYTES(NULL0_CY);',
  '    res->manage_src = false;',
  '    return true;',
  '  }',
  '  return cl_default_loader(vmp, mod, uri, res);',
  '}',
  '',
  '// eval a small persisted snippet (a callback call). Errors are logged but',
  '// not fatal - a cart is not required to define every callback, and an',
  '// undeclared-function error is how a missing one shows up.',
  'static void eval_snippet(const char* src) {',
  '  CLBytes s = { .ptr = (char*)src, .len = strlen(src) };',
  '  CLBytes uri = CL_BYTES("frame");',
  '  CLEvalResult res;',
  '  cl_vm_evalx(vm, uri, s, persist_cfg, &res);',
  '}',
  '',
  '// read a whole file from the cart',
  'static char* read_file(const char* filename) {',
  '  FILE* file = fopen(filename, "rb");',
  '  if (file == NULL) {',
  '    return NULL;',
  '  }',
  '  fseek(file, 0, SEEK_END);',
  '  long size = ftell(file);',
  '  fseek(file, 0, SEEK_SET);',
  '  char* text = malloc(size + 1);',
  '  if (text == NULL) {',
  '    fclose(file);',
  '    return NULL;',
  '  }',
  '  size_t read = fread(text, 1, size, file);',
  '  text[read] = \'\\0\';',
  '  fclose(file);',
  '  return text;',
  '}',
  ''
)

c.push(`int main() {
  vm = cl_vm_init();
  cl_vm_set_loader(vm, module_loader);
  persist_cfg = clDefaultEvalConfig();
  persist_cfg.persist_main = true;

  char* source = read_file("main.cy");
  if (source == NULL) {
    printf("cyber: no main.cy in cart\\n");
    fflush(stdout);
    return 1;
  }

  CLBytes src = { .ptr = source, .len = strlen(source) };
  CLBytes uri = CL_BYTES("main");
  CLEvalResult eval;
  CLResultCode code = cl_vm_evalx(vm, uri, src, persist_cfg, &eval);
  free(source);
  if (code != CL_SUCCESS) {
    CLBytes summary = cl_vm_error_summary(vm);
    printf("cyber: %.*s\\n", (int)summary.len, summary.ptr);
    fflush(stdout);
    return 1;
  }

  // load() is called here, since the host only calls _start on a wasi cart
  eval_snippet("load()");
  fflush(stdout);
  return 0;
}

void update() {
  eval_snippet("update()");
  fflush(stdout);
}

void unload() {
  eval_snippet("unload()");
  fflush(stdout);
}
`)

// the C signature null0.h itself declares for each callback export - must
// match exactly (a mismatch is a compile error, not a warning)
const callbackCType = {
  buttonUp: 'void buttonUp(GamepadButton button, unsigned int player)',
  buttonDown: 'void buttonDown(GamepadButton button, unsigned int player)',
  keyUp: 'void keyUp(Key key)',
  keyDown: 'void keyDown(Key key)',
  mouseDown: 'void mouseDown(unsigned int button)',
  mouseUp: 'void mouseUp(unsigned int button)',
  mouseMoved: 'void mouseMoved(float x, float y)'
}

// the input-callbacks all look the same: stash args in g_a0/g_a1, then
// eval a snippet that casts them back to the right type per-param
for (const [name, { args, description }] of Object.entries(callbacks)) {
  const entries = Object.entries(args)
  const intArgs = { GamepadButton: true, u32: true, Key: true, MouseButton: true }
  c.push(`// ${description}`)
  c.push(`${callbackCType[name]} {`)
  entries.forEach(([argName], i) => {
    c.push(`  g_a${i} = (f32)${argName};`)
  })
  const callExpr = entries.map(([, type], i) => (intArgs[type] ? `int(null0.__a${i})` : `null0.__a${i}`)).join(', ')
  c.push(`  eval_snippet("${name}(${callExpr})");`)
  c.push('  fflush(stdout);')
  c.push('}', '')
}

await mkdir('carts/cyber', { recursive: true })
await writeFile('carts/cyber/null0.cy', cySource)
await writeFile('tools/docker/cyber-cart.c', c.join('\n'))
