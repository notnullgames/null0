#!/usr/bin/env node

// Generator for the interpreted-Python null0 cart runtime.
// Embeds RustPython (targeting wasm32-wasip1) and exposes the null0 API as
// plain Python globals (same convention as the JS carts: no `import null0`,
// functions/constants just exist in the script's global scope).
//
// Struct types (Color/Vector/Rectangle/Dimensions/SfxParams) are represented
// on the Python side as dicts, e.g. {'r':.., 'g':.., 'b':.., 'a':..}.

import { writeFile } from 'node:fs/promises'
import { getApi, indent, seedTypes } from './utils.js'

const { constants, enums, structs, scalars, callbacks, ...api } = await getApi()

// Rust extern type for each API type (matches the real null0 host ABI, as
// proven by the existing, complete carts/rust bindings).
const externTypes = {
  string: '*const u8',
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
  SfxPresetType: 'i32',
  Color: 'Color',
  Vector: 'Vector',
  Rectangle: 'Rectangle',
  Dimensions: 'Dimensions',
  'Vector[]': '*const Vector',
  'i32[]': '*const i32',
  SfxParams: 'SfxParams'
}

// the host returns structs by writing them into cart-memory and handing back
// the address, so those come back as a u32 to be read from
const externRetTypes = {
  Color: 'u32',
  Vector: 'u32',
  Rectangle: 'u32',
  Dimensions: 'u32',
  SfxParams: 'u32'
}

const memberTypes = { i32: 'i32', f32: 'f32', u32: 'u32', u8: 'u8', string: '*const u8' }

// Reserved keywords in Rust that need to be escaped
const rustReservedKeywords = new Set(['type', 'impl', 'trait', 'struct', 'enum', 'fn', 'let', 'mut', 'const', 'static', 'if', 'else', 'match', 'for', 'while', 'loop', 'break', 'continue', 'return', 'mod', 'pub', 'use', 'extern', 'crate', 'super', 'self', 'Self', 'where', 'unsafe', 'async', 'await', 'move', 'ref', 'in', 'as', 'dyn', 'abstract', 'become', 'box', 'do', 'final', 'macro', 'override', 'priv', 'typeof', 'unsized', 'virtual', 'yield', 'try'])
const rustName = (name) => (rustReservedKeywords.has(name) ? `r#${name}` : name)

// struct types get converted to/from a python dict via generated helpers
const structArgTypes = new Set(['Color', 'Vector', 'Rectangle', 'Dimensions', 'SfxParams'])
const isStruct = (type) => Boolean(structs[type])

// this shim has no enum types of its own (the values reach python as ints),
// and a struct return is the u32 address the host allocated in cart memory
seedTypes(externTypes, { enums, structs }, { enumType: 'i32', structType: (name) => name })
seedTypes(externRetTypes, { enums, structs }, { enumType: 'i32', structType: 'u32' })
seedTypes(memberTypes, { enums }, { enumType: 'i32' })

const out = ['// GENERATED FILE - do not edit by hand. See tools/gen_cart_python.js', '#![allow(non_snake_case, non_upper_case_globals, unused_unsafe, dead_code)]', '', 'use rustpython_vm as vm;', 'use std::cell::OnceCell;', 'use std::ffi::CString;', 'use vm::function::FuncArgs;', 'use vm::scope::Scope;', 'use vm::{Interpreter, PyObjectRef, PyResult, VirtualMachine};', '']

// ---- struct definitions (must match the wasm C ABI exactly) ----
for (const [structName, structDef] of Object.entries(structs)) {
  out.push(`/// ${structDef.description}`)
  out.push('#[repr(C)]')
  out.push('#[derive(Debug, Clone, Copy, PartialEq)]')
  out.push(`pub struct ${structName} {`)
  for (const [memberName, memberType] of Object.entries(structDef.members)) {
    out.push(`    pub ${rustName(memberName)}: ${memberTypes[memberType] || memberType},`)
  }
  out.push('}')
  out.push('')
}

// ---- host imports ----
out.push('#[link(wasm_import_module = "null0")]')
out.push('extern "C" {')
for (const [apiName, funcDef] of Object.entries(api)) {
  for (const [funcName, { args, returns }] of Object.entries(funcDef)) {
    const params = Object.entries(args)
      .map(([name, type]) => `${rustName(name)}: ${externTypes[type] || type}`)
      .join(', ')
    const ret = returns === 'void' ? '' : ` -> ${externRetTypes[returns] || externTypes[returns] || returns}`
    out.push(`    pub fn ${funcName}(${params})${ret};`)
  }
}
out.push('}')
out.push('')

// ---- helpers ----
out.push(
  `// a host string (bytes in our own memory, valid until this callback returns)
fn cstr_to_py(p: *const u8, vm: &VirtualMachine) -> PyObjectRef {
    if p.is_null() {
        return vm.ctx.new_str("").into();
    }
    let mut len = 0usize;
    unsafe {
        while *p.add(len) != 0 {
            len += 1;
        }
        let bytes = core::slice::from_raw_parts(p, len);
        vm.ctx.new_str(String::from_utf8_lossy(bytes).into_owned()).into()
    }
}
`,
  ''
)

// ---- dict <-> struct conversion helpers ----
const convHelper = (structName) => {
  const members = Object.entries(structs[structName].members)
  const lines = []
  if (structArgTypes.has(structName)) {
    lines.push(`fn ${structName.toLowerCase()}_from_py(obj: &PyObjectRef, vm: &VirtualMachine) -> PyResult<${structName}> {`)
    lines.push(`    Ok(${structName} {`)
    for (const [memberName, memberType] of members) {
      lines.push(`        ${rustName(memberName)}: obj.get_item("${memberName}", vm)?.try_into_value::<${memberTypes[memberType]}>(vm)?,`)
    }
    lines.push('    })')
    lines.push('}')
    lines.push('')
  }
  lines.push(`fn ${structName.toLowerCase()}_to_py(v: ${structName}, vm: &VirtualMachine) -> PyObjectRef {`)
  lines.push('    let d = vm.ctx.new_dict();')
  for (const [memberName, memberType] of members) {
    if (memberType === 'string') {
      lines.push(`    d.set_item("${memberName}", cstr_to_py(v.${rustName(memberName)}, vm), vm).unwrap();`)
      continue
    }
    const ctor = memberType === 'f32' ? 'new_float' : 'new_int'
    const cast = memberType === 'f32' ? ' as f64' : ''
    lines.push(`    d.set_item("${memberName}", vm.ctx.${ctor}(v.${rustName(memberName)}${cast}).into(), vm).unwrap();`)
  }
  lines.push('    d.into()')
  lines.push('}')
  return lines.join('\n')
}
for (const structName of Object.keys(structs)) {
  out.push(convHelper(structName), '')
}

// ---- per-function python-callable wrappers ----
// python-facing args skip the implicit "count" arg that follows a `T[]` arg
// (the length is derived from the python list instead), same convention the
// JS bindings use.
const argFromPy = (idx, type, rawName) => {
  const varName = rustName(rawName)
  if (type === 'string') {
    return `let ${varName}_cs = CString::new(args.args[${idx}].clone().try_into_value::<String>(vm)?).unwrap();\n    let ${varName} = ${varName}_cs.as_ptr() as *const u8;`
  }
  if (structArgTypes.has(type)) {
    return `let ${varName} = ${type.toLowerCase()}_from_py(&args.args[${idx}], vm)?;`
  }
  if (type === 'Vector[]') {
    return `let ${varName}_vec: Vec<Vector> = { let list = args.args[${idx}].clone().try_into_value::<vm::builtins::PyListRef>(vm)?; let mut v = Vec::with_capacity(list.borrow_vec().len()); for item in list.borrow_vec().iter() { v.push(vector_from_py(item, vm)?); } v };\n    let ${varName} = ${varName}_vec.as_ptr();\n    let ${varName}_len = ${varName}_vec.len() as i32;`
  }
  if (type === 'i32[]') {
    return `let ${varName}_vec: Vec<i32> = args.args[${idx}].clone().try_into_value::<Vec<i32>>(vm)?;\n    let ${varName} = ${varName}_vec.as_ptr();\n    let ${varName}_len = ${varName}_vec.len() as i32;`
  }
  const rustType = externTypes[type] || type
  return `let ${varName} = args.args[${idx}].clone().try_into_value::<${rustType}>(vm)?;`
}

const funcs = []
const registrations = []

for (const [apiName, apiObj] of Object.entries(api)) {
  out.push(`// ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    const argEntries = Object.entries(args)

    // figure out python-facing arg indices (skip the count arg after a `T[]`)
    let pyIdx = 0
    const lines = []
    const callArgs = []
    for (let i = 0; i < argEntries.length; i++) {
      const [name, type] = argEntries[i]
      if (type.endsWith('[]')) {
        lines.push('    ' + argFromPy(pyIdx, type, name))
        callArgs.push(rustName(name))
        callArgs.push(`${rustName(name)}_len`)
        pyIdx++
        i++ // skip the following count arg entirely (not exposed to python)
        continue
      }
      lines.push('    ' + argFromPy(pyIdx, type, name))
      callArgs.push(rustName(name))
      pyIdx++
    }

    const argsParam = argEntries.length === 0 ? '_args: FuncArgs' : 'args: FuncArgs'
    out.push(`/// ${description}`)
    out.push(`fn nf_${funcName}(${argsParam}, vm: &VirtualMachine) -> PyResult<PyObjectRef> {`)
    out.push(...lines)
    const call = `unsafe { ${funcName}(${callArgs.join(', ')}) }`
    if (returns === 'void') {
      out.push(`    ${call};`)
      out.push('    Ok(vm.ctx.none())')
    } else if (isStruct(returns)) {
      out.push(`    let ret = ${call} as *const ${returns};`)
      out.push('    if ret.is_null() {')
      out.push('        return Ok(vm.ctx.none());')
      out.push('    }')
      out.push(`    Ok(${returns.toLowerCase()}_to_py(unsafe { *ret }, vm))`)
    } else if (returns === 'string') {
      out.push(`    let ret = ${call};`)
      out.push('    Ok(cstr_to_py(ret as *const u8, vm))')
    } else {
      const ctor = returns === 'f32' ? 'new_float' : returns === 'bool' ? 'new_bool' : 'new_int'
      const cast = returns === 'f32' ? ' as f64' : ''
      out.push(`    let ret = ${call};`)
      out.push(`    Ok(vm.ctx.${ctor}(ret${cast}).into())`)
    }
    out.push('}')
    out.push('')

    registrations.push(`    scope.globals.set_item("${funcName}", vm.new_function("${funcName}", nf_${funcName}).into(), vm).unwrap();`)
  }
}

// ---- constants ----
out.push('// CONSTANTS', '')
out.push('fn register_constants(scope: &Scope, vm: &VirtualMachine) {')
out.push('    scope.globals.set_item("SCREEN", vm.ctx.new_int(0).into(), vm).unwrap();')
out.push('    scope.globals.set_item("SCREEN_WIDTH", vm.ctx.new_int(640).into(), vm).unwrap();')
out.push('    scope.globals.set_item("SCREEN_HEIGHT", vm.ctx.new_int(480).into(), vm).unwrap();')
out.push('    scope.globals.set_item("FONT_DEFAULT", vm.ctx.new_int(0).into(), vm).unwrap();')
for (const [name, def] of Object.entries(constants)) {
  if (def.type === 'Color') {
    const [r, g, b, a] = def.value
    out.push(`    scope.globals.set_item("${name}", color_to_py(Color { r: ${r}, g: ${g}, b: ${b}, a: ${a} }, vm), vm).unwrap();`)
  } else if (def.type === 'string') {
    out.push(`    scope.globals.set_item("${name}", vm.ctx.new_str(${JSON.stringify(def.value)}).into(), vm).unwrap();`)
  }
}
for (const [enumName, enumDef] of Object.entries(enums)) {
  for (const [entryName, entryValue] of Object.entries(enumDef.enums)) {
    out.push(`    scope.globals.set_item("${entryName}", vm.ctx.new_int(${entryValue}).into(), vm).unwrap();`)
  }
}
out.push('}')
out.push('')

// ---- registration + cart harness ----
out.push('fn register_all(scope: &Scope, vm: &VirtualMachine) {')
out.push(...registrations)
out.push('    register_constants(scope, vm);')
out.push('}')
out.push('')

out.push(`thread_local! {
    static INTERPRETER: OnceCell<Interpreter> = OnceCell::new();
    static SCOPE: OnceCell<Scope> = OnceCell::new();
}

fn call_named(vm: &VirtualMachine, scope: &Scope, name: &str, args: Vec<PyObjectRef>) {
    if let Ok(f) = scope.globals.get_item(name, vm) {
        if f.is_callable() {
            if let Err(e) = f.call(vm::function::PosArgs::new(args), vm) {
                vm.print_exception(e);
            }
        }
    }
}

fn main() {
    let interpreter = Interpreter::without_stdlib(Default::default());
    INTERPRETER.with(|c| c.set(interpreter).ok().unwrap());
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            let scope = vm.new_scope_with_builtins();
            register_all(&scope, vm);

            let src = std::fs::read_to_string("main.py").unwrap_or_default();
            match vm.compile(&src, vm::compiler::Mode::Exec, "<cart>") {
                Ok(code) => {
                    if let Err(e) = vm.run_code_obj(code, scope.clone()) {
                        vm.print_exception(e);
                    }
                }
                Err(e) => {
                    let exc = e.into_pyexception(vm, Some(&src));
                    vm.print_exception(exc);
                }
            }

            SCOPE.with(|s| s.set(scope).ok().unwrap());
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "load", vec![]));
        });
    });
}

#[no_mangle]
pub extern "C" fn update() {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "update", vec![]));
        });
    });
}

#[no_mangle]
pub extern "C" fn unload() {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "unload", vec![]));
        });
    });
}

#[no_mangle]
pub extern "C" fn buttonDown(button: i32, player: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "buttonDown", vec![vm.ctx.new_int(button).into(), vm.ctx.new_int(player).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn buttonUp(button: i32, player: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "buttonUp", vec![vm.ctx.new_int(button).into(), vm.ctx.new_int(player).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn keyDown(key: i32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "keyDown", vec![vm.ctx.new_int(key).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn keyUp(key: i32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "keyUp", vec![vm.ctx.new_int(key).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn mouseDown(button: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "mouseDown", vec![vm.ctx.new_int(button).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn mouseUp(button: u32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "mouseUp", vec![vm.ctx.new_int(button).into()]));
        });
    });
}

#[no_mangle]
pub extern "C" fn mouseMoved(x: f32, y: f32) {
    INTERPRETER.with(|c| {
        c.get().unwrap().enter(|vm| {
            SCOPE.with(|s| call_named(vm, s.get().unwrap(), "mouseMoved", vec![vm.ctx.new_float(x as f64).into(), vm.ctx.new_float(y as f64).into()]));
        });
    });
}
`)

await writeFile('tools/docker/python-cart/src/main.rs', out.join('\n'))

// TYPE STUBS
//
// python carts get their API as globals from the RustPython runtime above, so
// there is nothing to import at runtime. carts/python/null0.pyi exists purely
// so an editor (pyright, mypy, ...) can complete & check a cart - the same job
// carts/lua/null0.lua does for LuaLS and carts/js/null0.d.ts does for JS.

// how an API type is spelled in a python stub
const pyTypes = {
  void: 'None',
  bool: 'bool',
  i32: 'int',
  u32: 'int',
  u64: 'int',
  f32: 'float',
  string: 'str',
  Image: 'Image',
  Font: 'Font',
  Sound: 'Sound',
  Tilemap: 'Tilemap',
  'Vector[]': 'list[Vector]',
  'i32[]': 'list[int]'
}

// enums cross as their int value, structs are plain dicts
seedTypes(pyTypes, { enums, structs }, { enumType: (name) => name, structType: (name) => name })

const pyMemberTypes = { i32: 'int', u32: 'int', u8: 'int', f32: 'float', string: 'str' }

const py = (type) => pyTypes[type] || type

// a `T[]` arg is followed by a count arg in the yml - the python binding reads
// the length off the list itself, so the cart never passes it
function pyParams(args) {
  const entries = Object.entries(args)
  const params = []
  for (let i = 0; i < entries.length; i++) {
    const [name, type] = entries[i]
    params.push(`${name}: ${py(type)}`)
    if (type.endsWith('[]')) {
      i++
    }
  }
  return params.join(', ')
}

const pyi = ['# null0 - type stubs for the null0 fantasy console', '#', '# GENERATED FILE - do not edit by hand. See tools/gen_cart_python.js', '#', '# The null0 API is available as plain globals in your cart - nothing to', '# import at runtime, same as the lua/js carts. This file is only here so', '# editors (anything pyright/Pylance-based) can complete & check your cart.', '#', '# Unlike lua and JS, python has no notion of ambient globals, so a checker', '# needs to be told the names exist. Put null0.pyi next to main.py and open', '# your cart with a type-checking-only import. The block never runs, so the', '# cart still just uses the globals at runtime:', '#', '#     TYPE_CHECKING = False', '#', '#     if TYPE_CHECKING:', '#         from null0 import *', '#', '#     # (this cart runtime is RustPython built without the stdlib, so do NOT', '#     # write `from typing import TYPE_CHECKING` - there is no typing module', '#     # to import. A plain module-level flag is what pyright looks for.)', '#', '#     def load():', '#         clear(BLUE)', '#         draw_circle(100, 100, 50, RED)', '', 'from typing import TypedDict', '']

pyi.push('# TYPES', '')

// the handle types are ints - an alias keeps the docs readable without making
// them a distinct type the checker would fight you over
for (const [name, { description }] of Object.entries(scalars)) {
  if (!['Image', 'Font', 'Sound', 'Tilemap'].includes(name)) {
    continue
  }
  pyi.push(`# ${description}`, `${name} = int`, '')
}

// enums cross as ints too
for (const [name, { description }] of Object.entries(enums)) {
  pyi.push(`# ${description}`, `${name} = int`, '')
}

for (const [name, { description, members }] of Object.entries(structs)) {
  pyi.push(`class ${name}(TypedDict):`, `    """${description}"""`)
  for (const [memberName, memberType] of Object.entries(members)) {
    pyi.push(`    ${memberName}: ${pyMemberTypes[memberType] || memberType}`)
  }
  pyi.push('')
}

for (const [apiName, apiObj] of Object.entries(api)) {
  if (!Object.keys(apiObj).length) {
    continue
  }
  pyi.push(`# ${apiName.toUpperCase()}`, '')
  for (const [funcName, { args, returns, description }] of Object.entries(apiObj)) {
    pyi.push(`def ${funcName}(${pyParams(args)}) -> ${py(returns)}:`, `    """${description}"""`, '    ...', '')
  }
}

pyi.push('# CONSTANTS', '')
for (const [name, def] of Object.entries(constants)) {
  if (def.description) {
    pyi.push(`# ${def.description}`)
  }
  pyi.push(`${name}: ${py(def.type)}`, '')
}

for (const [enumName, enumDef] of Object.entries(enums)) {
  pyi.push(`# ${enumDef.description}`)
  for (const [entryName] of Object.entries(enumDef.enums)) {
    pyi.push(`${entryName}: ${enumName}`)
  }
  pyi.push('')
}

pyi.push('# CALLBACKS', '#', '# Define the ones you need in main.py - the host skips any you leave out.', '#')
for (const [name, { args, description }] of Object.entries({
  load: { args: {}, description: 'Called once when the cart is loaded.' },
  update: { args: {}, description: 'Called on every frame.' },
  unload: { args: {}, description: 'Called when the cart is unloaded.' },
  ...callbacks
})) {
  pyi.push(`# ${description}`, `#     def ${name}(${Object.keys(args).join(', ')}): ...`)
}
pyi.push('')

await writeFile('carts/python/null0.pyi', pyi.join('\n').replace(/[ \t]+$/gm, ''))

// A pyright config so a cart typechecks against null0.pyi out of the box.
// null0 is a stub with no source module (the runtime supplies the names as
// globals), which is exactly what reportMissingModuleSource complains about.
await writeFile(
  'carts/python/pyrightconfig.json',
  JSON.stringify(
    {
      typeCheckingMode: 'standard',
      reportMissingModuleSource: 'none'
    },
    null,
    2
  ) + '\n'
)
