// this will generate null0_api/src/null0_api_wamr.h

import { glob } from 'glob'
import YAML from 'yaml'
import { readFile } from 'node:fs/promises'
import { basename } from 'node:path'

function generateWamrWrapper (name, description, returns, args) {
  return `// ${description}
static void wamr_null0_${name}(wasm_exec_env_t exec_env, SOME ARGS) {
  return null0_${name}(SOME ARGS);
}`
}

/*
'i': i32
'I': i64
'f': f32
'F': f64
'r': externref (has to be the value of a uintptr_t variable)
'*': the parameter is a buffer address in WASM application
'~': the parameter is the byte length of WASM buffer as referred by preceding argument "*". It must follow after '*', otherwise, registration will fail
'$': the parameter is a string in WASM application
*/
function generateWasmSig (name, returns, args) {
  // TODO: this is a stub
  // if it returns struct, insert that as * to first param
  // pointers are *
  // string is $, buffer+len (like arrays) is *~
  // otherwise figure out i/I/f/F
  let sigString = ''
  if (returns !== 'void') {
    sigString = `(${Object.values(args).map(a => 'i').join('')})i`
  } else {
    sigString = `(${Object.values(args).map(a => 'i').join('')})`
  }
  return `{"${name}", wamr_null0_${name}, "${sigString}"}`
}

const functions = []
const wasmsigs = []

for (const f of await glob('api/*.yml')) {
  const apiName = basename(f, '.yml')
  const api = YAML.parse(await readFile(f, 'utf8'))
  functions.push('')
  functions.push(`// ${apiName.toUpperCase()}`)
  for (const name of Object.keys(api)) {
    functions.push(generateWamrWrapper(name, api[name].description, api[name].returns, api[name].args))
    wasmsigs.push(generateWasmSig(name, api[name].returns, api[name].args))
  }
}

console.log(`
// this is the WAMR wrapper, for loading wasm on native

#include "null0_api.h"
#include "wasm_c_api.h"
#include "wasm_export.h"

wasm_exec_env_t exec_env;
wasm_module_inst_t module_inst;

// these callbacks are from the cart
wasm_function_inst_t cart_update = NULL;
wasm_function_inst_t cart_unload = NULL;
wasm_function_inst_t cart_buttonUp = NULL;
wasm_function_inst_t cart_buttonDown = NULL;
wasm_function_inst_t cart_keyUp = NULL;
wasm_function_inst_t cart_keyDown = NULL;

// over the WASM barrier I use RGBA always, so this converts in/out

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Null0WasmColor;

void color_from_pntr_to_wasm(pntr_color c, Null0WasmColor* colorOut) {
  colorOut->r = c.rgba.r;
  colorOut->g = c.rgba.g;
  colorOut->b = c.rgba.b;
  colorOut->a = c.rgba.a;
}

pntr_color color_from_wasm_to_pntr(Null0WasmColor c) {
  return pntr_new_color(c.r, c.g, c.b, c.a);
}
${functions.join('\n\n')}

static NativeSymbol null0_native_symbols[] = {
  ${wasmsigs.join(',\n  ')}
};

RuntimeInitArgs null0_init_args() {
  RuntimeInitArgs init_args;
  memset(&init_args, 0, sizeof(RuntimeInitArgs));

  static char global_heap_buf[512 * 1024];
  uint32_t stack_size = 8092, heap_size = 8092;

  init_args.mem_alloc_type = Alloc_With_Pool;
  init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
  init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

  init_args.n_native_symbols = sizeof(null0_native_symbols) / sizeof(NativeSymbol);
  init_args.native_module_name = "null0";
  init_args.native_symbols = null0_native_symbols;

  return init_args;
}

// setup WAMR host
bool null0_init_wamr() {
  unsigned int bytesRead = 0;
  unsigned char* wasmBytes;

  wasmBytes = null0_file_read("/main.wasm", &bytesRead);

  if (wasmBytes == NULL) {
    printf("Could not read main.wasm\\n");
    return false;
  }

  RuntimeInitArgs init_args = null0_init_args();

  if (!wasm_runtime_full_init(&init_args)) {
    printf("Init runtime environment failed.\\n");
    return false;
  }

  uint32_t stack_size = 8092, heap_size = 8092;
  unsigned long wasmSize = (unsigned long)bytesRead;
  char error_buf[128];

  error_buf[0] = 0;
  wasm_module_t module = wasm_runtime_load(wasmBytes, wasmSize, error_buf, sizeof(error_buf));
  if (error_buf[0] != 0) {
    printf("load - %s\\n", error_buf);
    return false;
  }

  error_buf[0] = 0;
  module_inst = wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, sizeof(error_buf));
  if (error_buf[0] != 0) {
    printf("instantiate - %s\\n", error_buf);
    return false;
  }

  exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);

  cart_update = wasm_runtime_lookup_function(module_inst, "update", NULL);
  cart_buttonUp = wasm_runtime_lookup_function(module_inst, "buttonUp", NULL);
  cart_buttonDown = wasm_runtime_lookup_function(module_inst, "buttonDown", NULL);
  cart_keyUp = wasm_runtime_lookup_function(module_inst, "keyUp", NULL);
  cart_keyDown = wasm_runtime_lookup_function(module_inst, "keyDown", NULL);

  wasm_application_execute_main(module_inst, 0, NULL);

  return true;
}

// call cart's update
bool null0_update_wamr() {
  if (cart_update != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_update, 0, NULL)) {
      printf("%s\\n", wasm_runtime_get_exception(module_inst));
    }
  }
  return true;
}

// call cart's unload
void null0_unload_wamr() {
  if (cart_unload != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_unload, 0, NULL)) {
      printf("%s\\n", wasm_runtime_get_exception(module_inst));
    }
  }
  null0_unload();
}


`)
