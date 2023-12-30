// simple native example of logging

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

// embedded file example
unsigned int byteSize = 12;
unsigned char* data[] = { 0x68,0x65,0x6c,0x6c,0x6f,0x20,0x77,0x6f,0x72,0x6c,0x64,0x0a };

void cart_main() {
  null0_trace("Hello from filesystem.");

  unsigned int bytesRead = 0;
  
  // here is an example of a regular read, no special permissions
  unsigned char* cyberBytes;
  cyberBytes = null0_file_read("/cart/cyber.txt", &bytesRead);
  if (bytesRead != 0) {
    null0_trace("read %d bytes from cyber.txt.", bytesRead);
  } else {
    null0_trace("could not read cyber.txt.");
  }

  // here is an embedded-file, also no special permissions
  unsigned int bytesRead2;
  bool ok = null0_file_embed("hello.txt", (unsigned char *) &data, byteSize);
  unsigned char* bytes2 = null0_file_read("hello.txt", &bytesRead2);
  if (ok) {
    null0_trace("hello.txt (%d):\n%s", bytesRead2, (char*)bytes2);
  } else {
    null0_trace("hello.txt not embedded.");
  }

}


bool Init(pntr_app* app) {
  if (!null0_load_cart("examples/cart/c/filesystem")) {
    null0_trace("Could not load examples/cart/c/filesystem as root-filesystem!");
    null0_unload();
    return false;
  }
  
  cart_main();
  
  // exit after init
  null0_unload();
  return false;
}


pntr_app Main(int argc, char* argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif
  return (pntr_app){
      .width = 320,
      .height = 240,
      .title = "null0",
      .init = Init,
      .fps = 60};
}