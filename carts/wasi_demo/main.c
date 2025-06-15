#include "../null0.h"

int main() {
  printf("hello from WASI\n");

  FILE *file = fopen("assets/cyber.txt", "r");
  if (file) {
    printf("could read file\n");
  }else{
    printf("could not read file\n");
  }

  return 0;
}
