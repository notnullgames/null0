// Null0 host - filesystem - generated 2023-12-29T06:49:42.371Z
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assetsys.h"

// Read a file from cart
unsigned char* null0_file_read(char* fname, uint32_t* bytesRead) {
  *bytesRead = 0;

  char filename[MAX_PATH_STRING_SIZE];

  if (fname[0] == '/') {
    snprintf(filename, MAX_PATH_STRING_SIZE, "%s%s", "/cart", fname);
  } else {
    snprintf(filename, MAX_PATH_STRING_SIZE, "%s%s", "/cart/", fname);
  }

  // check for write/ (requires permission)
  if (string_starts_with(filename, "/cart/write/")) {
    if (!null0_config.can_write) {
      printf("Cannot read %s (need write permission.)\n", filename);
      return NULL;
    }
  }

  // loop through null0_embedded_files looking for file
  size_t i;
  for (i = 0; i < cvector_size(null0_embedded_files); ++i) {
    if (strncmp(null0_embedded_files[i]->filename, filename, strlen(filename)) == 0) {
      *bytesRead = null0_embedded_files[i]->size;
      return null0_embedded_files[i]->data;
    }
  }

  // Load the file information from assetsys.
  assetsys_file_t file;
  if (assetsys_file(null0_fs, filename, &file) != 0) {
    // printf("Could not get info for %s.\n", filename);
    return NULL;
  }

  // Find out the size of the file.
  int size = assetsys_file_size(null0_fs, file);
  if (size <= 0) {
    // printf("Could not get size of %s.\n", filename);
    return NULL;
  }

  // Create the memory buffer.
  unsigned char* out = malloc(size);
  if (out == NULL) {
    // printf("Could not malloc %s.\n", filename);
    return NULL;
  }

  // Load the file into the buffer.
  int outSize = 0;
  if (assetsys_file_load(null0_fs, file, &outSize, (void*)out, size) != 0) {
    free(out);
    // printf("Could not load %s into buffer.\n", filename);
    return NULL;
  }

  // Save how many bytes were read.
  if (bytesRead != NULL) {
    *bytesRead = outSize;
  }

  // printf("file read: %s\n", filename);

  return out;
}

// Write a file to persistant storage
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize) {
  // check for write/ (requires permission)
  if (string_starts_with(filename, "write/")) {
    if (!null0_config.can_write) {
      printf("Cannot write to %s (need permission.)\n", filename);
      return false;
    }
  } else {
    printf("Cannot write to %s outside of write/\n", filename);
    return false;
  }

  // write to assetsys write dir
  char* path = malloc(MAX_PATH_STRING_SIZE);
  int l = strlen(null0_config.write_dir);
  int f = strlen(filename);
  strncpy(path, null0_config.write_dir, l);
  strncpy(path + l, filename + 6, f);

  FILE* hs = fopen(path, "w");
  fwrite(data, byteSize, 1, hs);
  fclose(hs);
  free(path);
}

// Embed memory as a file
bool null0_file_embed(char* fname, unsigned char* data, uint32_t byteSize) {
  char filename[MAX_PATH_STRING_SIZE];

  if (fname[0] == '/') {
    snprintf(filename, MAX_PATH_STRING_SIZE, "%s%s", "/cart", fname);
  } else {
    snprintf(filename, MAX_PATH_STRING_SIZE, "%s%s", "/cart/", fname);
  }

  // don't allow them to mess with permissions
  if (strncmp(filename, "/cart/cart.ini", strlen("/cart/cart.ini")) == 0) {
    printf("Cannot write to cart.ini.\n");
    return false;
  }

  // don't allow them to mess with entrypoint
  if (strncmp(filename, "/cart/main.wasm", strlen("/cart/main.wasm")) == 0) {
    printf("Cannot write to main.wasm.\n");
    return false;
  }

  // don't allow them to mess with /write/
  if (strncmp(filename, "/cart/write/", strlen("/cart/write/")) == 0) {
    printf("Use file_write() to write to peristant-data.\n");
    return false;
  }

  Null0FileData* f = malloc(sizeof(Null0FileData));
  f->size = byteSize;
  f->data = malloc(byteSize);
  strncpy(f->filename, filename, strlen(filename));
  memcpy(f->data, data, byteSize);

  cvector_push_back(null0_embedded_files, f);
  return true;
}