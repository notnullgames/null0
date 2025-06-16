#include "../null0.h"
#include <sys/stat.h>

long get_file_size_stat(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return -1; // Error getting file info
}

int main() {
  printf("hello from WASI\n");

  long filesize = get_file_size_stat("assets/cyber.txt");
  printf("filesize: %lu\n", filesize);
  FILE *file = fopen("assets/cyber.txt", "r");

  if (file && filesize) {
    char* data = malloc(filesize);
    // this beach-balls
    fgets(data, filesize, file);
    fclose(file);
    printf("file: %s\n", data);
    free(data);
  } else {
    printf("no file/filesize!\n");
  }

  return 0;
}
