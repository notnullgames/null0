// what a host call costs, for deciding how much of an API can be per-frame

#include "null0.h"

int main() {
  u64 t0, t1;
  volatile i32 sum = 0;

  // scalar in, scalar out
  t0 = current_time();
  for (i32 i = 0; i < 100000; i++) {
    sum += key_down(KEY_SPACE);
  }
  t1 = current_time();
  printf("100k key_down       : %llu ms\n", (unsigned long long)(t1 - t0));

  // struct return: allocates in cart memory, freed at the end of the callback
  t0 = current_time();
  for (i32 i = 0; i < 100000; i++) {
    Vector* p = mouse_position();
    sum += p->x;
  }
  t1 = current_time();
  printf("100k mouse_position : %llu ms\n", (unsigned long long)(t1 - t0));

  // a cart-side loop, for scale
  t0 = current_time();
  for (i32 i = 0; i < 100000; i++) {
    sum += i;
  }
  t1 = current_time();
  printf("100k cart-side adds : %llu ms\n", (unsigned long long)(t1 - t0));

  fflush(stdout);
  return 0;
}

void update() {}
