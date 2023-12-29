// Null0 host - filesystem - generated 2023-12-29T02:43:33.872Z
#pragma once

#include <stdint.h>
#include <stdbool.h>

// Read a file from cart
unsigned char* null0_file_read(char* filename, uint32_t* bytesRead) {
  *bytesRead = 0;
  return NULL;
}

// Write a file to persistant storage
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize) {
  return false;
}

// Embed memory as a file
bool null0_file_embed(char* filename, unsigned char* data, uint32_t byteSize) {
  return false;
}