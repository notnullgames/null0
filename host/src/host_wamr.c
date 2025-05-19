// this is the wamr-specific implementation of host

#ifndef EMSCRIPTEN

#include "host.h"

cvector_vector_type(NativeSymbol) null0_native_symbols = NULL;

static wasm_exec_env_t exec_env;
static wasm_module_inst_t module_inst;

static uint32_t stack_size = 1024 * 1024 * 10; // 10 MB
static uint32_t heap_size = 1024 * 1024 * 10;  // 10 MB

static wasm_module_t module = NULL;
static wasm_module_inst_t module_inst = NULL;
static wasm_exec_env_t exec_env = NULL;
static wasm_function_inst_t cart_callback_unload = NULL;
static wasm_function_inst_t cart_callback_update = NULL;
static wasm_function_inst_t cart_callback_buttonDown = NULL;
static wasm_function_inst_t cart_callback_buttonUp = NULL;
static wasm_function_inst_t cart_callback_keyDown = NULL;
static wasm_function_inst_t cart_callback_keyUp = NULL;
static wasm_function_inst_t cart_callback_mouseDown = NULL;
static wasm_function_inst_t cart_callback_mouseUp = NULL;
static wasm_function_inst_t cart_callback_mouseMoved = NULL;

static int callback_args[2];
static float callback_float_args[2];

bool cart_init(unsigned char *wasmBytes, unsigned int wasmSize) {
  char error_buf[128];

  RuntimeInitArgs init_args;
  memset(&init_args, 0, sizeof(RuntimeInitArgs));
  init_args.mem_alloc_type = Alloc_With_System_Allocator;
  init_args.max_thread_num = 1;

  // Initialize the WAMR runtime
  if (!wasm_runtime_full_init(&init_args)) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "init: runtime");
    return false;
  }

  if (!wasm_runtime_register_natives("null0", null0_native_symbols, cvector_size(null0_native_symbols))) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "init: register");
    return false;
  }

  // Load WASM module
  module = wasm_runtime_load(wasmBytes, wasmSize, error_buf, sizeof(error_buf));
  if (!module) {
    pntr_app_log(PNTR_APP_LOG_ERROR, error_buf);
    wasm_runtime_destroy();
    return false;
  }

  // Instantiate the module
  module_inst = wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, sizeof(error_buf));
  if (!module_inst) {
    pntr_app_log(PNTR_APP_LOG_ERROR, error_buf);

    wasm_runtime_unload(module);
    wasm_runtime_destroy();
    return false;
  }

  // Create execution environment
  exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);
  if (!exec_env) {
    pntr_app_log(PNTR_APP_LOG_ERROR, wasm_runtime_get_exception(module_inst));

    wasm_runtime_deinstantiate(module_inst);
    wasm_runtime_unload(module);
    wasm_runtime_destroy();
    return false;
  }

  wasm_function_inst_t cart_callback_load = wasm_runtime_lookup_function(module_inst, "load");
  cart_callback_unload = wasm_runtime_lookup_function(module_inst, "unload");
  cart_callback_update = wasm_runtime_lookup_function(module_inst, "update");
  cart_callback_buttonDown = wasm_runtime_lookup_function(module_inst, "buttonDown");
  cart_callback_buttonUp = wasm_runtime_lookup_function(module_inst, "buttonUp");
  cart_callback_keyDown = wasm_runtime_lookup_function(module_inst, "keyDown");
  cart_callback_keyUp = wasm_runtime_lookup_function(module_inst, "keyUp");
  cart_callback_mouseDown = wasm_runtime_lookup_function(module_inst, "mouseDown");
  cart_callback_mouseUp = wasm_runtime_lookup_function(module_inst, "mouseUp");
  cart_callback_mouseMoved = wasm_runtime_lookup_function(module_inst, "mouseMoved");

  wasm_application_execute_main(module_inst, 0, NULL);

  if (cart_callback_load != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_load, 0, NULL)) {
      // not fatal, but this will help with troubleshooting
      pntr_app_log(PNTR_APP_LOG_ERROR, wasm_runtime_get_exception(module_inst));
    }
  }

  // TODO: setup WASI?

  return true;
}

bool cart_update() {
  if (cart_callback_update != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_update, 0, NULL)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
  return true;
}

bool cart_close() {
  if (cart_callback_unload != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_unload, 0, NULL)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }

  if (exec_env) {
    wasm_runtime_destroy_exec_env(exec_env);
    exec_env = NULL;
  }

  if (module_inst) {
    wasm_runtime_deinstantiate(module_inst);
    module_inst = NULL;
  }

  if (module) {
    wasm_runtime_unload(module);
    module = NULL;
  }

  wasm_runtime_destroy();
  return true;
}

// allocate some memory in cart
static uint32_t cart_malloc(uint32_t size) {
  void **p_native_addr = NULL;
  return (uint32_t)wasm_runtime_module_malloc(module_inst, (uint64_t)size, p_native_addr);
}

// free some memory in cart
static void cart_free(uint32_t ptr) {
  wasm_runtime_module_free(module_inst, (uint64_t)ptr);
}

unsigned int copy_memory_to_cart(void *hostPtr, unsigned int size) {
  unsigned int cartPtr = cart_malloc(size);
  void *cartHostPtr = wasm_runtime_addr_app_to_native(module_inst, (uint64_t)cartPtr);
  memcpy(cartHostPtr, hostPtr, size);
  return cartPtr;
}

void *copy_memory_from_cart(unsigned int cartPtr, unsigned int size) {
  void *cartHostPtr = wasm_runtime_addr_app_to_native(module_inst, (uint64_t)cartPtr);
  void *hostPtr = malloc(size);
  memcpy(hostPtr, cartHostPtr, size);
  return hostPtr;
}

unsigned int cart_strlen(unsigned int cartPtr) {
  void *cartHostPtr = wasm_runtime_addr_app_to_native(module_inst, (uint64_t)cartPtr);
  return strlen(cartHostPtr);
}

// copy a host-pointer to cart when you already have a cart-pointer
void copy_to_cart_with_pointer(uint32_t cartPtr, void *hostPtr, uint32_t size) {
  void *cartHostPtr = wasm_runtime_addr_app_to_native(module_inst, (uint64_t)cartPtr);
  memcpy(cartHostPtr, hostPtr, size);
}

// copy a host-pointer to cart when you already have a cart-pointer
void copy_from_cart_with_pointer(void *hostPtr, uint32_t cartPtr, uint32_t size) {
  void *cartHostPtr = wasm_runtime_addr_app_to_native(module_inst, (uint64_t)cartPtr);
  memcpy(hostPtr, cartHostPtr, size);
}

void cart_buttonDown(pntr_app_gamepad_button button, unsigned int player) {
  callback_args[0] = button;
  callback_args[1] = player;
  if (cart_callback_buttonDown != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_buttonDown, 2, callback_args)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
}

void cart_buttonUp(pntr_app_gamepad_button button, unsigned int player) {
  callback_args[0] = button;
  callback_args[1] = player;
  if (cart_callback_buttonUp != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_buttonUp, 2, callback_args)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
}

void cart_keyDown(pntr_app_key key) {
  callback_args[0] = key;
  if (cart_callback_keyDown != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_keyDown, 1, callback_args)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
}

void cart_keyUp(pntr_app_key key) {
  callback_args[0] = key;
  if (cart_callback_keyUp != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_keyUp, 1, callback_args)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
}

void cart_mouseDown(pntr_app_mouse_button button) {
  callback_args[0] = button;
  if (cart_callback_mouseDown != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_mouseDown, 1, callback_args)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
}

void cart_mouseUp(pntr_app_mouse_button button) {
  callback_args[0] = button;
  if (cart_callback_mouseUp != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_mouseUp, 1, callback_args)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
}

void cart_mouseMoved(float x, float y) {
  callback_float_args[0] = x;
  callback_float_args[1] = y;
  if (cart_callback_mouseMoved != NULL) {
    if (!wasm_runtime_call_wasm(exec_env, cart_callback_mouseMoved, 2, callback_float_args)) {
      // not fatal, but warn about it
      pntr_app_log(PNTR_APP_LOG_WARNING, wasm_runtime_get_exception(module_inst));
    }
  }
}

#endif // !EMSCRIPTEN
