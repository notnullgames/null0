// this is the wamr-specific implementation of host

#ifndef EMSCRIPTEN

#include "host.h"

bool cart_init(unsigned char *wasmBytes, unsigned int wasmSize) {
  // TODO
  return true;
}

bool cart_update() {
  // TODO
  return true;
}

bool cart_close() {
  // TODO
  return true;
}

void cart_event(pntr_app_event *event) {
  // TODO
}

unsigned int copy_memory_to_cart(void *host_pointer, unsigned int size) {
  // TODO
  return 0;
}

void *copy_memory_from_cart(unsigned int cart_pointer, unsigned int size) {
  // TODO
  return 0;
}

unsigned int cart_strlen(unsigned int cart_pointer) {
  // TODO
  return 0;
}

#endif // !EMSCRIPTEN
