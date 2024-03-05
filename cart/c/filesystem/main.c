#include <null0.h>

int main() {
  char types[4][10] = {
      "Regular",
      "Directory",
      "Symlink",
      "Other"};

  FileInfo f = file_info("assets/cyber.txt");
  trace("filesize: %lld, type: %s, read-only: %s", f.filesize, types[f.filetype], f.readonly ? "yes" : "no");
  trace("mod: %lld, create: %lld, access: %lld", f.modtime, f.createtime, f.accesstime);

  u32 bytesRead = 0;
  char* bytes = file_read("assets/cyber.txt", &bytesRead);
  trace("%u bytes read", bytesRead);
  trace("cyber: %s", bytes);

  bool ok = file_write("out.txt", "THIS IS A TEST.", 16);
  trace("write: %s", ok ? "good" : "no");

  return 0;
}
