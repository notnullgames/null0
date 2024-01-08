// simple native example of logging

// settings for pntr
#define PNTR_APP_RAYLIB
#define PNTR_PIXELFORMAT_RGBA
#define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#define PTNR_NO_STB_IMAGE_RESIZE_IMPLEMENTATION

#include "null0_api.h"

// embedded file example
unsigned int embedSize = 6;
unsigned char embedData[6] = {0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x0a};

void cart_main() {
  null0_trace("Hello from filesystem.");

  // here is an example of a regular read
  unsigned int bytesRead = 0;
  unsigned char* cyberBytes = null0_file_read("cyber.txt", &bytesRead);
  if (bytesRead != 0) {
    null0_trace("read %d bytes from cyber.txt:\n%s", bytesRead, (char*)cyberBytes);
  } else {
    null0_trace("could not read cyber.txt.");
  }

  // here is an embedded (written) file
  if (null0_file_write("hello.txt", &embedData, embedSize)) {
    unsigned int bytesReadEmbed;
    unsigned char* embedBytes = null0_file_read("hello.txt", &bytesReadEmbed);
    printf("read embeded hello.txt (%d): %s\n", bytesReadEmbed, (char*)embedBytes);
  } else {
    printf("hello.txt not embedded.\n");
  }

  // here is how to append a file
  if (null0_file_append("log.txt", "a\n", 2)) {
    unsigned int bytesReadAppend;
    unsigned char* appendBytes = null0_file_read("log.txt", &bytesReadAppend);
    appendBytes[bytesReadAppend - 1] = 0;
    printf("read embeded log.txt (%d): %s\n", bytesReadAppend, (char*)appendBytes);
  } else {
    printf("hello.txt not embedded.\n");
  }

  // list files
  char** i;
  printf("Here are the files:\n");
  for (i = null0_file_list("/"); *i != NULL; i++) {
    printf("  %s\n", *i);
  }
}

bool Init(pntr_app* app) {
  if (!null0_load_cart("examples/filesystem")) {
    printf("Could not initialize with examples/filesystem\n");
    null0_unload();
    return false;
  }
  cart_main();
  return true;
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