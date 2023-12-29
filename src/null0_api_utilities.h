// Null0 host - utilities - generated 2023-12-29T06:49:42.328Z
#pragma once

#include <stdint.h>

// Log a string
void null0_trace(char* str) {}

// Get system-time (ms) since unix epoch
uint64_t null0_current_time() {}

// Get the change in time (seconds) since the last update run
float null0_delta_time() {}

// Get a random integer between 2 numbers
int32_t null0_random_int(int32_t min, int32_t max) {}