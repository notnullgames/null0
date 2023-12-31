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

    char realpath[MAX_PATH_STRING_SIZE];
    string_replace(filename, "/cart/write/", "");
    snprintf(realpath, MAX_PATH_STRING_SIZE, "%s%s", null0_config.write_dir, filename);

    // printf("(host) reading written file: %s\n", realpath);

    FILE* fp = fopen(realpath, "rb");
    fseek(fp, 0, SEEK_END);
    long filelen = ftell(fp);
    *bytesRead = (uint32_t) filelen;
    rewind(fp);
    char* buffer = (char *)malloc(filelen * sizeof(char));
    fread(buffer, filelen, 1, fp);
    fclose(fp);
    return buffer;
  }

  // printf("(host) read request: %s\n", filename);

  // loop through null0_embedded_files looking for file
  size_t i;
  for (i = 0; i < cvector_size(null0_embedded_files); ++i) {
    if (string_equals(null0_embedded_files[i]->filename, filename)) {
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
  *bytesRead = outSize;

  return out;
}

// Write a file to persistant storage
bool null0_file_write(char* fname, unsigned char* data, uint32_t byteSize) {
  char filename[MAX_PATH_STRING_SIZE];

  if (fname[0] == '/') {
    snprintf(filename, MAX_PATH_STRING_SIZE, "%s%s", "/cart", fname);
  } else {
    snprintf(filename, MAX_PATH_STRING_SIZE, "%s%s", "/cart/", fname);
  }

  // check for write/ (requires permission)
  if (string_starts_with(filename, "/cart/write/")) {
    if (!null0_config.can_write) {
      printf("Cannot write to %s (need permission.)\n", filename);
      return false;
    }
  } else {
    printf("Cannot write to %s outside of write/\n", filename);
    return false;
  }

  // write to assetsys write dir (replace /cart/write/ with null0_config.write_dir)
  char realpath[MAX_PATH_STRING_SIZE];
  string_replace(filename, "/cart/write/", "");
  snprintf(realpath, MAX_PATH_STRING_SIZE, "%s%s", null0_config.write_dir, filename);
  // printf("(host) writing to real file: %s\n", realpath);
  
  FILE* hs = fopen(realpath, "w");
  fwrite(data, byteSize, 1, hs);
  fclose(hs);
  
  return true;
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
  if (string_equals(filename, "/cart/cart.ini")) {
    printf("Cannot write to cart.ini.\n");
    return false;
  }

  // don't allow them to mess with entrypoint
  if (string_equals(filename, "/cart/main.wasm")) {
    printf("Cannot write to main.wasm.\n");
    return false;
  }

  // don't allow them to mess with /write/
  if (string_starts_with(filename, "/cart/write/")) {
    printf("Use file_write() to write to peristant-data (write/)\n");
    return false;
  }

  Null0FileData* f = malloc(sizeof(Null0FileData));
  f->size = byteSize;
  f->data = malloc(byteSize);
  strncpy(f->filename, filename, strlen(filename));
  memcpy(f->data, data, byteSize);
  // printf("(host) embedded %s (%d): %s\n", f->filename, f->size, (char*) f->data);

  cvector_push_back(null0_embedded_files, f);
  return true;
}