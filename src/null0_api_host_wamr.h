// this is the WAMR native host functionality

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