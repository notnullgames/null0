#ifdef EMSCRIPTEN
#include <emscripten.h>
#include "host.h"

EM_JS(bool, cart_init, (pntr_app *app, unsigned char *wasmBytes, unsigned int wasmSize), {
  return Module.cart_callback_init(wasmBytes, wasmSize);
});

EM_JS(void, cart_update, (), {
  Module?.cart?.update && Module.cart.update();
});

EM_JS(void, cart_buttonDown, (pntr_app_gamepad_button button, unsigned int player), {
  Module?.cart?.buttonDown && Module.cart.buttonDown(button, player);
});

EM_JS(void, cart_buttonUp, (pntr_app_gamepad_button button, unsigned int player), {
  Module?.cart?.buttonUp && Module.cart.buttonUp(button, player);
});

EM_JS(void, cart_keyDown, (pntr_app_key key), {
  Module?.cart?.keyDown && Module.cart.keyDown(key);
});

EM_JS(void, cart_keyUp, (pntr_app_key key), {
  Module?.cart?.keyUp && Module.cart.keyUp(key);
});

EM_JS(void, cart_mouseDown, (pntr_app_mouse_button button), {
  Module?.cart?.mouseDown && Module.cart.mouseDown(button);
});

EM_JS(void, cart_mouseUp, (pntr_app_mouse_button button), {
  Module?.cart?.mouseUp && Module.cart.mouseUp(button);
});

EM_JS(void, cart_mouseMoved, (float x, float y), {
   Module?.cart?.mouseMoved && Module.cart.mouseMoved(x, y);
});


EM_JS(uint32_t, cart_malloc, (size_t size), {
  return Module.cart.malloc(size);
});

EM_JS(void, cart_free, (uint32_t ptr), {
  Module.cart.free(ptr);
});

EM_JS(void, mem_to_cart, (uint32_t dest, void* src, size_t size), {
  const cartMem = new Uint8Array(Module.cart.memory.buffer);
  cartMem.set(Module.HEAPU8.slice(src, src+size), dest);
});

EM_JS(void, mem_from_cart, (void* dest, uint32_t src, size_t size), {
  const cartMem = new Uint8Array(Module.cart.memory.buffer);
  Module.HEAPU8.set(cartMem.slice(src, src+size), dest);
});

EM_JS(size_t, cart_strlen, (unsigned int cart_pointer), {
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