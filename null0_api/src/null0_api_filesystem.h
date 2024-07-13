// This is the null0 API filesystem functions

#pragma once

#include <libgen.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "physfs.h"

#ifdef PNTR_APP_LIBRETRO
// TODO: Wrap this into a pntr_app_libretro_environ_cb() function.
extern static retro_environment_t environ_cb;
#endif

char** null0_file_list_array;

const char* null0_writable_dir;

// intialize filesystem
bool null0_init_filesystem(pntr_app* app) {
  #ifdef PNTR_APP_LIBRETRO
  if (!PHYSFS_init(environ_cb)) {
  #else
  if (!PHYSFS_init(app->argv != NULL ? app->argv[0] : NULL)) {
  #endif
    printf("Could not init filesystem.\n");
    return false;
  }

  // Mount the current working directory, so that we're able to load the app->argv[1] file.
  PHYSFS_mount(".", NULL, 1);

  unsigned int size;
  void* cart_data = pntr_app_load_arg_file(app, &size);

  if (app->argc > 0) {
    // TODO: Find the base directory of the app->argv[0] current file.
    null0_writable_dir = app->argv[0];
  }
  else {
    null0_writable_dir = PHYSFS_getBaseDir();
  }

  printf("Stuff: %s\n", app->argv[0]);

  if (cart_data == NULL) {
    // Mount the directory itself.
    if (!PHYSFS_mount(app->argv[0], NULL, 0)) {
      PHYSFS_deinit();
      printf("Could not mount directory.\n");
      return false;
    }
  }
  else {
    // Mount the cart data.
    int success = PHYSFS_mountMemory(cart_data, size, NULL, "cart.zip", NULL, 0);
    pntr_unload_memory(cart_data);
    if (success == 0) {
      PHYSFS_deinit();
      printf("Could not mount cart data.\n");
      return false;
    }
  }

  // put null0_writable_dir at end of search-path (so user can overwrite any files)
  if (!PHYSFS_mount(null0_writable_dir, NULL, 1)) {
    printf("Could not mount write-dir.\n");
    // Don't error out, just report the error.
  }

  if (!PHYSFS_setWriteDir(null0_writable_dir)) {
    printf("Could not set write-dir.\n");
    // Don't error out, just report the error
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
  return pntr_physfs_load_file((const char*)filename, bytesRead);
}

// Write a file to persistant storage
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize) {
  return pntr_physfs_save_file((const char*)filename, data, byteSize);
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
const char* null0_get_write_dir() {
  return null0_writable_dir;
}
