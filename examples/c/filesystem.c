// simple native example of file read/write

#include "null0_api.h"

int main(int argc, char* argv[]) {
  printf("args: %d\n", argc);

  // use this dir are root
  null0_load_cart("./examples/cart/c/filesystem/");

  null0_trace("Hello from filesystem.");

  // null0_unload();
  return 0;
}