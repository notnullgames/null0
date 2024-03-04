#include <null0.h>

// embedded file example
u32 byteSize = 12;
u8 data[] = { 0x68,0x65,0x6c,0x6c,0x6f,0x20,0x77,0x6f,0x72,0x6c,0x64,0x0a };

int main() {
  u32 bytesRead1;
  // reading normal files takes no special permissions
  u8* bytes1 = file_read("assets/cyber.txt", &bytesRead1);
  // this makes it a proper null-terminated string
  bytes1[bytesRead1] = 0;
  trace("cyber.txt (%d):\n%s", bytesRead1, (char*)bytes1);

  // here is an embedded-file, also no special permissions
  u32 bytesRead2;
  bool ok = file_embed("hello.txt", (unsigned char *) &data, byteSize);
  u8* bytes2 = file_read("hello.txt", &bytesRead2);
  if (ok) {
    trace("hello.txt (%d):\n%s", bytesRead2, (char*)bytes2);
  } else {
    trace("hello.txt not embedded.");
  }

  // these require file_write permission in cart.yml
  u32 bytesRead3;
  bool ok2 = file_write("write/testwrite.txt", (unsigned char *) &data, byteSize);
  u8* bytes3 = file_read("write/testwrite.txt", &bytesRead3);
  if (ok2) {
    trace("testwrite.txt (%d):\n%s", bytesRead3, (char*)bytes3);
  } else {
    trace("testwrite.txt not written.");
  }
  
  return 0;
}
