// Null0 host - filesystem - generated 2023-12-29T06:49:42.371Z
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Read a file from cart
unsigned char* null0_file_read(char* filename, uint32_t* bytesRead) {
  // check for write/ (requires permission)
  if (string_starts_with(filename, "write/")) {
    if (!null0_can_write) {
      *bytesRead = 0;
      printf("Cannot read %s (need write permission.)\n", filename);
      return NULL;
    }
  }

  // loop through null0_embedded_files looking for file
  size_t i;
  for (i = 0; i < cvector_size(null0_embedded_files); ++i) {
    if (null0_embedded_files[i]->filename == filename) {
      *bytesRead = null0_embedded_files[i]->size;
      return null0_embedded_files[i]->data;
    }
  }

  // Load the file information from assetsys.
  assetsys_file_t file;
  if (assetsys_file(null0_fs, filename, &file) != 0) {
    printf("Could not get info for %s.\n", filename);
    return NULL;
  }

  // Find out the size of the file.
  int size = assetsys_file_size(null0_fs, file);
  if (size <= 0) {
    printf("Could not get size of %s.\n", filename);
    return NULL;
  }

  // Create the memory buffer.
  unsigned char* out = malloc(size);
  if (out == NULL) {
    printf("Could not malloc %s.\n", filename);
    return NULL;
  }

  // Load the file into the buffer.
  int outSize = 0;
  if (assetsys_file_load(null0_fs, file, &outSize, (void*)out, size) != 0) {
    free(out);
    printf("Could not load %s into buffer.\n", filename);
    return NULL;
  }

  // Save how many bytes were read.
  if (bytesRead != NULL) {
    *bytesRead = outSize;
  }

  return out;
}

// Write a file to persistant storage
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize) {
  // check for write/ (requires permission)
  if (string_starts_with(filename, "write/")) {
    if (!null0_can_write) {
      printf("Cannot write to %s (need permission.)\n", filename);
      return false;
    }
  } else {
    printf("Cannot write to %s outside of write/\n", filename);
    return false;
  }
  // TODO: write to assetsys write dir
}

// Embed memory as a file
bool null0_file_embed(char* filename, unsigned char* data, uint32_t byteSize) {
  // don't allow them to mess with permissions
  if (strncmp(filename, "cart.yml", strlen(filename)) == 0) {
    printf("Cannot write to cart.yml.\n");
    return false;
  }
  Null0FileData* f = malloc(sizeof(Null0FileData));
  f->filename = filename;
  f->size = byteSize;
  f->data = data;
  cvector_push_back(null0_embedded_files, f);
  return true;
}