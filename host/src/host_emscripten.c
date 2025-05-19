// this is the emscripten-specific implementation of host

#ifdef EMSCRIPTEN

#include "host.h"
#include <emscripten.h>

EM_JS(bool, cart_init, (unsigned char *wasmBytes, unsigned int wasmSize), {
  return Module.cart_callback_init(wasmBytes, wasmSize);
});

EM_JS(bool, cart_update, (void), {
  if (Module?.cart?.update) {
    Module.cart.update();
  }
  return true;
});

void cart_event(pntr_app_event *event) {
  // TODO: map events to cart function-cals
  printf("event\n");
}

bool cart_close() {
  // close doesn't really do anything, in emscripten-host
  return true;
}

EM_JS(unsigned int, copy_memory_to_cart, (void *host_pointer, unsigned int size), {
  const ret = Module.cart.malloc(size);
  const cartMem = new Uint8Array(Module.cart.memory.buffer);
  cartMem.set(Module.HEAPU8.subarray(host_pointer, host_pointer + size), ret);
  return ret;
});

EM_JS(void, emscripten_copy_memory_from_cart, (unsigned int cart_pointer, void *ret, unsigned int size), {
  const mem = new Uint8Array(Module.cart.memory.buffer).subarray(cart_pointer, cart_pointer + size);
  Module.HEAPU8.set(mem, ret);
});

void *copy_memory_from_cart(unsigned int cart_pointer, unsigned int size) {
  void *ret = pntr_load_memory(size);
  emscripten_copy_memory_from_cart(cart_pointer, ret, size);
  return ret;
}

EM_JS(unsigned int, cart_strlen, (unsigned int cart_pointer), {
  const max_string_size = 1024 * 1024 * 1024;
  const b = new Uint8Array(Module.cart.memory.buffer).slice(cart_pointer, cart_pointer + max_string_size);
  let len = 0;
  while (len++ < max_string_size) {
    if (b[len] == 0) {
      return len;
    }
  }
  return 0;
});

#endif // EMSCRIPTEN
