// this implements shared filesystem functions

#ifndef NULL0_FS_H_
#define NULL0_FS_H_

#include <libgen.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "physfs.h"

#include "pntr.h" // for pntr_load_memory

// these are the supported filetypes we can detect
// see fs_parse_magic_bytes()
typedef enum {
  FILE_TYPE_UNKNOWN,
  FILE_TYPE_ZIP,
  FILE_TYPE_WASM,
  FILE_TYPE_PNG,
  FILE_TYPE_JPEG,
  FILE_TYPE_BMP,
  FILE_TYPE_GIF,
  FILE_TYPE_WAV,
  FILE_TYPE_OGG,
  FILE_TYPE_MP3,
  FILE_TYPE_TTF,
  FILE_TYPE_OTF,
  FILE_TYPE_DIR
} DetectFileType;

// called to unload filesystem
void fs_unload();

// load a file from native filesystem
unsigned char *fs_load_file_real(const char *filename, unsigned int *bytesRead);

// load a file from physfs filesystem
unsigned char *fs_load_file(const char *filename, uint32_t *bytesRead);

// save a file to native filesystem
bool fs_save_file_real(const char *filename, const void *, uint32_t byteSize);

// save a file to physfs filesystem
bool fs_save_file(const char *filename, const void *, uint32_t byteSize);

// append to a file in physfs filesystem
bool fs_append_file(const char *filename, const void *data, uint32_t byteSize);

// just detect filetype from first 4 bytes
DetectFileType fs_parse_magic_bytes(uint32_t magic_number);

// detect file-type from native filesystem file
DetectFileType fs_detect_type_real(const char *filename);

// detect file-type from physfs filesystem file
DetectFileType fs_detect_type(const char *filename);

// get the short-name of cart, using filename
char *fs_get_cart_name(const char *filename);

#endif // NULL0_FS_H_
