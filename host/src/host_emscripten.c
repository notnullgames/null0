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

bool cart_close() {
  // close doesn't really do anything, in emscripten-host
  return true;
}

EM_JS(void, copy_memory_to_cart_pointer, (unsigned int ret, void *host_pointer, unsigned int size), {
  const cartMem = new Uint8Array(Module.cart.memory.buffer);
  cartMem.set(Module.HEAPU8.subarray(host_pointer, host_pointer + size), ret);
});

EM_JS(void, copy_memory_from_cart_pointer, (unsigned int ret, void *host_pointer, unsigned int size), {
                                                                                                        // TODO
                                                                                                      });

EM_JS(unsigned int, cart_malloc, (unsigned int size), {
  return Module.cart.malloc(size);
});

unsigned int copy_memory_to_cart(void *host_pointer, unsigned int size) {
  unsigned int ret = cart_malloc(size);
  copy_memory_to_cart_pointer(ret, host_pointer, size);
  return ret;
}

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

EM_JS(void, cart_buttonDown, (pntr_app_gamepad_button button, unsigned int player), {
  if (Module?.cart?.buttonDown){
    Module.cart.buttonDown(button, player)
  }
});

EM_JS(void, cart_buttonUp, (pntr_app_gamepad_button button, unsigned int player), {
  if (Module?.cart?.buttonUp){
    Module.cart.buttonUp(button, player)
  }
});

EM_JS(void, cart_keyDown, (pntr_app_key key), {
  if (Module?.cart?.keyDown){
    Module.cart.keyDown(key)
  }
});

EM_JS(void, cart_keyUp, (pntr_app_key key), {
  if (Module?.cart?.keyUp){
    Module.cart.keyUp(key)
  }
});

EM_JS(void, cart_mouseDown, (pntr_app_mouse_button button), {
  if (Module?.cart?.mouseDown){
    Module.cart.mouseDown(button)
  }
});

EM_JS(void, cart_mouseUp, (pntr_app_mouse_button button), {
  if (Module?.cart?.mouseUp){
    Module.cart.mouseUp(button)
  }
});

EM_JS(void, cart_mouseMoved, (float x, float y), {
  if (Module?.cart?.mouseMoved){
    Module.cart.mouseMoved(x, y)
  }
});

#endif // EMSCRIPTEN
