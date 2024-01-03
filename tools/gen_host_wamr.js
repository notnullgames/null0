// This will generate the C WAMR native wasm host-interface

import { glob } from 'glob'
import YAML from 'yaml'
import { readFile, writeFile } from 'fs/promises'

const api = {}
for (const f of await glob('api/*.yml')) {
  const api_name = f.replace(/^api\/(.+)\.yml$/g, '$1')
  api[api_name] = YAML.parse(await readFile(f, 'utf8'))
}

const wamrMap = {
  i32: 'i',
  f32: 'f',
  f64: 'F',
  i64: 'I',
  bool: 'i',
  'SfxrParams*': '*',
  'Rectangle*': '*',
  Image: 'i',
  Font: 'i',
  Sound: 'i',
  'Color*': '*',
  string: '$',
  'Vector*': '*',
  'Dimensions*': '*',
  Key: 'i',
  GamepadButton: 'i',
  MouseButton: 'i',
  bytes: '*',
  void: ''
}

const retMap = {
  Image: 'u32',
  Font: 'u32',
  Sound: 'u32',
  'Color*': 'pntr_color*'
}

const indent = (str, numOfIndents = 1) => str.split('\n').map(l => ' '.repeat(numOfIndents * 2) + l.trim()).join('\n') + '\n'

// get the signature-string for wasm wrapper
const wamr_params = func => {
  return `(${Object.values(func.args).map(a => wamrMap[a]).join('')})` + wamrMap[func.returns]
}

let code = ''

// map types in api to C types
function mapType (type) {
  if (['Font', 'Sound', 'Image'].includes(type)) {
    return 'u32'
  }
  if (type === 'Dimensions*') {
    return 'Null0Dimensions*'
  }
  if (type === 'SfxrParams*') {
    return 'Null0SfxrParams*'
  }
  if (type === 'string') {
    return 'char*'
  }
  if (type === 'bytes') {
    return 'u8*'
  }
  if (type === 'Color*') {
    return 'pntr_color*'
  }
  if (type === 'MouseButton') {
    return 'pntr_app_mouse_button'
  }
  if (type === 'GamepadButton') {
    return 'pntr_app_gamepad_button'
  }
  if (type === 'Key') {
    return 'pntr_app_key'
  }
  if (type === 'ImageFilter') {
    return 'pntr_filter'
  }
  if (type === 'Rectangle*') {
    return 'pntr_rectangle*'
  }
  if (type === 'Vector*') {
    return 'pntr_vector*'
  }
  return type
}

const symbols = []

for (const type of Object.keys(api)) {
  code += `\n/////////// ${type.toUpperCase()} ///////////\n\n\n`
  for (const fun of Object.keys(api[type])) {
    symbols.push(`{ "${fun}", ${fun}_wasmimport, "${wamr_params(api[type][fun])}" }`)
    const args = { exec_env: 'wasm_exec_env_t', ...api[type][fun].args }
    code += `// ${api[type][fun].description}
static ${mapType(api[type][fun].returns)} ${fun}_wasmimport(${Object.keys(args).map(a => `${mapType(args[a])} ${a}`).join(', ')}) {
  return null0_${fun}(${Object.keys(api[type][fun].args).join(', ')});
}

`
  }
}

const out = `// generated null0 WAMR (wasm host) wrapper

#pragma once

#include "null0_api.h"
#include "wasm_c_api.h"
#include "wasm_export.h"

wasm_exec_env_t exec_env;
wasm_module_inst_t module_inst;

wasm_function_inst_t cart_update = NULL;
wasm_function_inst_t cart_buttonUp = NULL;
wasm_function_inst_t cart_buttonDown = NULL;
wasm_function_inst_t cart_keyUp = NULL;
wasm_function_inst_t cart_keyDown = NULL;

${code}
static NativeSymbol native_symbols[] = {
${indent(symbols.join(',\n'))}};

// this makes iwasm --native-lib option work
uint32_t get_native_lib(char** p_module_name, NativeSymbol** p_native_symbols) {
  *p_module_name = "null0";
  *p_native_symbols = native_symbols;
  return sizeof(native_symbols) / sizeof(NativeSymbol);
}

bool null0_init_wamr(char* filename) {
  if (filename == NULL) {
    return false;
  }
  
  if (!null0_load_cart(filename)) {
    return false;
  }

  unsigned int bytesRead = 0;
  unsigned char* wasmBytes;

  wasmBytes = null0_file_read("/main.wasm", &bytesRead);

  return true;
}


// call when an event happens
void null0_event_wamr(pntr_app_event* event) {
}

// call on each frame
bool null0_upate_wamr(pntr_app* app, pntr_image* screen) {
  null0_update(app, screen);
  return true;
}

// call when your game exits
void null0_unload_wamr() {
  null0_unload();
}
`

await writeFile('src/null0_api_host_wamr.h', out)
