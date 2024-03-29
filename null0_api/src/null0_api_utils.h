// This is the null0 API utiity functions

#pragma once

#include <stdarg.h>
#include <time.h>

// max-size for trace messages
#ifndef NULL0_TRACE_SIZE
#define NULL0_TRACE_SIZE 1024 * 10
#endif
char null0_traceBuffer[NULL0_TRACE_SIZE];

// Log a string (using printf-style)
void null0_trace(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(null0_traceBuffer, NULL0_TRACE_SIZE, format, args);
  va_end(args);
  printf("%s\n", null0_traceBuffer);
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