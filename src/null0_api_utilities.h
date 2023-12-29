// Null0 host - utilities - generated 2023-12-29T06:49:42.328Z
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <time.h>

// Log a string
void null0_trace(char* str) {
  printf("%s\n", str);
}

// Get system-time (ms) since unix epoch
uint64_t null0_current_time() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  return t.tv_sec * 1000 + (t.tv_nsec + 500000) / 1000000;
}

// Get the change in time (seconds) since the last update run
float null0_delta_time() {
  return pntr_app_delta_time(null0_app);
}

// Get a random integer between 2 numbers
int32_t null0_random_int(int32_t min, int32_t max) {
  return pntr_app_random(null0_app, min, max);
}
