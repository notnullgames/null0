// this defines the API of the null0 game-engine

#pragma once

#include <dirent.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cfgpath.h"
#include "ini.h"

#define MAX_PATH_STRING_SIZE 127

// use null0 file-functions (defined in null0_api_filesystem) for pntr
unsigned char* null0_file_read(char* filename, uint32_t* bytesRead);
bool null0_file_write(char* filename, unsigned char* data, uint32_t byteSize);

#define PNTR_LOAD_FILE null0_file_read
#define PNTR_SAVE_FILE null0_file_write

// make sure importing pntr will implement it, too
#define PNTR_IMPLEMENTATION
#define PNTR_APP_IMPLEMENTATION
#include <pntr.h>
#include <pntr_app.h>

// use zip as dir
#define STRPOOL_IMPLEMENTATION
#define ASSETSYS_IMPLEMENTATION
#include "assetsys.h"

// growable arrays
#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"

// this is use for embedded files
typedef struct {
  char* filename;
  size_t size;
  unsigned char* data;
} Null0FileData;

// this is the global app-config
// this could be merged with the other shared globals, too
typedef struct {
  char name[127];
  bool can_write;
  bool can_http;
  char write_dir[MAX_PATH_STRING_SIZE];
} Null0CartConfig;

// return true if 1 string starts with another
#define string_starts_with(string_to_check, prefix) (strncmp(string_to_check, prefix, ((sizeof(prefix) / sizeof(prefix[0])) - 1)) ? 0 : ((sizeof(prefix) / sizeof(prefix[0])) - 1))

// string replace, in -place
void strreplace(char* string, const char* find, const char* replaceWith) {
  if (strstr(string, find) != NULL) {
    char* temporaryString = malloc(strlen(strstr(string, find) + strlen(find)) + 1);
    strcpy(temporaryString, strstr(string, find) + strlen(find));
    *strstr(string, find) = '\0';
    strcat(string, replaceWith);
    strcat(string, temporaryString);
    free(temporaryString);
  }
}

// setup shared globals
Null0CartConfig null0_config;
cvector_vector_type(Null0FileData*) null0_embedded_files;
cvector_vector_type(pntr_font*) null0_fonts;
cvector_vector_type(pntr_image*) null0_images;
cvector_vector_type(pntr_sound*) null0_sounds;
assetsys_t* null0_fs;
pntr_app* null0_app;
pntr_image* null0_screen;

// these are to simplify bindings
uint32_t null0_add_image(pntr_image* image) {
  uint32_t id = cvector_size(null0_images);
  cvector_push_back(null0_images, image);
  return id;
}

uint32_t null0_add_sound(pntr_sound* sound) {
  uint32_t id = cvector_size(null0_sounds);
  cvector_push_back(null0_sounds, sound);
  return id;
}

uint32_t null0_add_font(pntr_font* font) {
  uint32_t id = cvector_size(null0_fonts);
  cvector_push_back(null0_fonts, font);
  return id;
}

#include "null0_api_utilities.h"

#include "null0_api_colors.h"
#include "null0_api_filesystem.h"
#include "null0_api_graphics.h"
#include "null0_api_input.h"
#include "null0_api_sound.h"

// map keys to buttons
int null0_button_map_key(int key) {
  if (key == PNTR_APP_KEY_UP) {
    return PNTR_APP_GAMEPAD_BUTTON_UP;
  }
  if (key == PNTR_APP_KEY_DOWN) {
    return PNTR_APP_GAMEPAD_BUTTON_DOWN;
  }
  if (key == PNTR_APP_KEY_LEFT) {
    return PNTR_APP_GAMEPAD_BUTTON_LEFT;
  }
  if (key == PNTR_APP_KEY_RIGHT) {
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
  }
  if (key == PNTR_APP_KEY_Q) {
    return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
  }
  if (key == PNTR_APP_KEY_W) {
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
  }
  if (key == PNTR_APP_KEY_Z) {
    return PNTR_APP_GAMEPAD_BUTTON_B;
  }
  if (key == PNTR_APP_KEY_X) {
    return PNTR_APP_GAMEPAD_BUTTON_A;
  }
  if (key == PNTR_APP_KEY_A) {
    return PNTR_APP_GAMEPAD_BUTTON_Y;
  }
  if (key == PNTR_APP_KEY_S) {
    return PNTR_APP_GAMEPAD_BUTTON_X;
  }
  if (key == PNTR_APP_KEY_LEFT_SHIFT || key == PNTR_APP_KEY_RIGHT_SHIFT) {
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  }
  if (key == PNTR_APP_KEY_ENTER) {
    return PNTR_APP_GAMEPAD_BUTTON_START;
  }
  return -1;
}

// get the basename of a file path, without extension
char* basename_without_extension(const char* path) {
  char* base = strrchr(path, '/');
  if (base == NULL) {
    return path;
  }
  base++;
  char* ext = strrchr(base, '.');
  if (ext != NULL) {
    *ext = '\0';
  }
  return base;
}

// turn string representing bool into a bool
bool parse_string_as_bool(const char* str) {
  switch (*str) {
    case '0':
      return false;
    case '1':
      return true;
    case 'y':
    case 'Y':
      return true;
    case 't':
    case 'T':
      return true;
    case 'o':
    case 'O':
      if (strcasecmp(str, "on") == 0) {
        return true;
      }
      return false;
    case 'n':
    case 'N':
      return false;
    case 'f':
    case 'F':
      return false;
  }
}

// used with ini_parse_string to parse cart ini
static int null0_config_handler(void* user, const char* section, const char* name, const char* value) {
  Null0CartConfig* pconfig = (Null0CartConfig*)user;

#define config_name_match(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

  if (config_name_match("", "name")) {
    strreplace(value, "/", "_");
    strncpy(null0_config.name, value, sizeof(null0_config.name));
    get_user_config_folder(null0_config.write_dir, MAX_PATH_STRING_SIZE, null0_config.name);
  }

  if (config_name_match("permissions", "write")) {
    null0_config.can_write = parse_string_as_bool(value);
  }

  if (config_name_match("permissions", "http")) {
    null0_config.can_http = parse_string_as_bool(value);
  }
}

// call when an event happens
void null0_event(pntr_app_event* event) {
}

// initialize structures & load a cart (wasm or zip file)
bool null0_load_cart(char* filename) {
  bool isZip = false;
  bool isWasm = false;
  bool isDir = false;

  DIR* dirptr;
  if (access(filename, F_OK) != -1) {
    if ((dirptr = opendir(filename)) != NULL) {
      isDir = true;
    } else {
      FILE* fptr1 = fopen(filename, "r");
      char str[4];
      if (fptr1 == NULL) {
        printf("Could not open file.\n");
        return false;
      }
      fread(str, 4, 1, fptr1);
      fclose(fptr1);
      isZip = memcmp(str, "PK\3\4", 4) == 0;
      isWasm = memcmp(str, "\0asm", 4) == 0;
    }
  } else {
    printf("Could not open file.\n");
    return false;
  }

  if (!isDir && !isZip && !isWasm) {
    printf("Unknown filetype.\n");
    return false;
  }

  null0_fs = assetsys_create(0);

  if (isWasm) {
    assetsys_mount(null0_fs, dirname(filename), "/cart");
  } else {
    assetsys_mount(null0_fs, filename, "/cart");
  }

  strncpy(null0_config.name, basename_without_extension(filename), 127);
  null0_config.can_write = false;
  null0_config.can_http = false;
  null0_config.write_dir[0] = 0;

  // read config
  uint32_t bytesReadConfig = 0;
  unsigned char* configBytes = null0_file_read("/cart/cart.ini", &bytesReadConfig);
  if (bytesReadConfig != 0) {
    ini_parse_string((const char*)configBytes, null0_config_handler, (void*)&null0_config);
  }

  printf("name: %s\nwrite: %s (%s)\nhttp: %s\n", null0_config.name, null0_config.can_write ? "Y" : "N", null0_config.write_dir, null0_config.can_http ? "Y" : "N");

  // allow reading the write-dir
  if (null0_config.can_write) {
    assetsys_mount(null0_fs, null0_config.write_dir, "/write");
  }

  // default font is 0
  null0_add_font(pntr_load_font_default());

  // image 0 is screen
  null0_add_image(null0_screen);

  return true;
}

// call on each frame to update things
void null0_update(pntr_app* app, pntr_image* screen) {
  null0_app = app;
  null0_screen = screen;
}

// call when you are ready to quit, to unload things
void null0_unload() {
  // unload null0_fonts
  // unload null0_images
  // unload null0_sounds
  // unload null0_embedded_files

  assetsys_destroy(null0_fs);
}
