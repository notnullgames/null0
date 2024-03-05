// This is the null0 API filesystem functions

#pragma once

#include <libgen.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "physfs.h"

char** null0_file_list_array;

char* null0_writable_dir;

// intialize filesystem
bool null0_init_filesystem(char* cart) {
  if (!PHYSFS_init("null0")) {
    printf("Could not init filesystem.\n");
    return false;
  }
  char* cartName = strtok(basename(cart), ".");

  if (strlen(cartName) > 127) {
    printf("Name is too long.\n");
    return false;
  }

  char pathname[134];
  snprintf(pathname, 134, "null0-%s", cartName);

  null0_writable_dir = PHYSFS_getPrefDir("null0", pathname);

  if (!PHYSFS_mount(cart, NULL, 1)) {
    PHYSFS_deinit();
    printf("Could not mount filesystem.\n");
    return false;
  }

  // put null0_writable_dir at end of search-path (so user can overwrite any files)
  if (!PHYSFS_mount(null0_writable_dir, NULL, 1)) {
    PHYSFS_deinit();
    printf("Could not mount write-dir.\n");
    return false;
  }

  if (!PHYSFS_setWriteDir(null0_writable_dir)) {
    PHYSFS_deinit();
    printf("Could not set write-dir.\n");
    return false;
  }

  return true;
}

// unload the filesystem
void null0_unload_filesystem() {
  PHYSFS_deinit();
  PHYSFS_freeList(null0_file_list_array);
}

// Get info about a single file
PHYSFS_Stat null0_file_info(char* filename) {
  PHYSFS_Stat stat;
  PHYSFS_stat(filename, &stat);
  return stat;
}

// Read a file from cart
unsigned char* null0_file_read(char* filename, uint32_t* bytesRead) {
  PHYSFS_File* f = PHYSFS_openRead(filename);
  PHYSFS_Stat i = null0_file_info(filename);

  unsigned char* b = (unsigned char*)malloc(i.filesize);
  PHYSFS_sint64 br = PHYSFS_readBytes(f, b, i.filesize);
  *bytesRead = br;
  PHYSFS_close(f);
  return b;
}

// Write a file to persistant storage
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize) {
  PHYSFS_File* f = PHYSFS_openWrite(filename);
  PHYSFS_sint64 bytesWritten = PHYSFS_writeBytes(f, data, byteSize);
  PHYSFS_close(f);
  if (byteSize != bytesWritten) {
    return false;
  }
  return true;
}

// Write a file to persistant storage, appending to the end
bool null0_file_append(char* filename, unsigned char* data, uint32_t byteSize) {
  PHYSFS_File* f = PHYSFS_openAppend(filename);
  PHYSFS_sint64 bytesWritten = PHYSFS_writeBytes(f, data, byteSize);
  PHYSFS_close(f);
  if (byteSize != bytesWritten) {
    return false;
  }
  return true;
}

// Get list of files in a directory
char** null0_file_list(char* dir) {
  null0_file_list_array = PHYSFS_enumerateFiles(dir);
  return null0_file_list_array;
}

// Get the user's writable dir (where file writes or appends go)
char* null0_get_write_dir() {
  return null0_writable_dir;
}
