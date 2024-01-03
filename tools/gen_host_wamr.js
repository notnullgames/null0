// This will generate the C WAMR native wasm host-interface

import { glob } from 'glob'
import YAML from 'yaml'
import { readFile, writeFile } from 'fs/promises'

function typeMap (arg) {
  switch (arg) {
    case 'u32': return 'uint32_t'
    case 'u32*': return 'uint32_t*'
    case 'i32': return 'int32_t'
    case 'u64': return 'uint64_t'
    case 'f32': return 'float'
    case 'Color': return 'uint32_t'
    case 'Image': return 'uint32_t'
    case 'Vector': return 'pntr_vector'
    case 'Vector*': return 'pntr_vector*'
    case 'Rectangle': return 'pntr_rectangle'
    case 'Sound': return 'uint32_t'
    case 'Dimensions': return 'pntr_vector'
    case 'ImageFilter': return 'pntr_filter'
    case 'Font': return 'uint32_t'
    case 'Key': return 'pntr_app_key'
    case 'GamepadButton': return 'pntr_app_gamepad_button'
    case 'MouseButton': return 'pntr_app_mouse_button'
    case 'bytes': return 'unsigned char*'
    case 'string': return 'char*'
    case 'SfxParams': return 'uint32_t'
    default: return arg
  }
}

function genHostApi (name, { description, returns, args }) {
  const out = []
  const aw = { exec_env: 'wasm_exec_env_t', ...args }
  out.push(`\n// ${description}`)
  out.push(`static ${typeMap(returns)} wamr_null0_${name}(${Object.keys(aw).map(a => `${typeMap(aw[a])} ${a}`).join(', ')}) {
  ${returns !== 'void' ? 'return ' : ''}null0_${name}(${Object.keys(args).join(', ')});
}`)

  return out
}

const out = [`// Null0 WAMR native host - generated ${(new Date()).toISOString()}`, `
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

`]

for (const f of await glob('api/*.yml')) {
  const api_name = f.replace(/^api\/(.+)\.yml$/g, '$1')
  const api = YAML.parse(await readFile(f, 'utf8'))
  out.push('')
  out.push(`// ${api_name.toUpperCase()}`)
  for (const name of Object.keys(api)) {
    out.push(genHostApi(name, api[name]).join('\n'))
  }
}

out.push(`
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
`)

await writeFile('src/null0_api_host_wamr.h', out.join('\n'))
