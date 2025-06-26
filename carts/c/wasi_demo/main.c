#include "null0.h"
#include <sys/stat.h>

long get_file_size_stat(const char *filename) {
  struct stat st;
  if (stat(filename, &st) == 0) {
    return st.st_size;
  }
  return -1; // Error getting file info
}

int main() {
  printf("hello from WASI\n");

  long filesize = get_file_size_stat("cyber.txt");
  printf("filesize: %lu\n", filesize);
  FILE *file = fopen("cyber.txt", "r");

  if (file && filesize) {
    char *data = malloc(filesize + 1); // +1 for null terminator
    size_t bytes_read = fread(data, 1, filesize, file);
    data[bytes_read] = '\0'; // Null terminate the string
    printf("file: %s\n", data);
    free(data);
  } else {
    printf("no file/filesize!\n");
  }

  fclose(file);

  return 0;
}
