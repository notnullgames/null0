#include "fs.h"

// load a file from native filesystem
unsigned char *fs_load_file_real(const char *filename, unsigned int *bytesRead) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    *bytesRead = 0;
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  size_t size = (size_t)ftell(file);
  fseek(file, 0, SEEK_SET);

  if (size <= 0) {
    fclose(file);
    *bytesRead = 0;
    return NULL;
  }

  unsigned char *data = (unsigned char *)malloc(size * sizeof(unsigned char));
  if (data == NULL) {
    fclose(file);
    *bytesRead = 0;
    return NULL;
  }

  // Read the file
  unsigned int bytes =
    (unsigned int)fread(data, sizeof(unsigned char), size, file);
  fclose(file);
  *bytesRead = bytes;

  return data;
}

// load a file from physfs filesystem
unsigned char *fs_load_file(const char *filename, uint32_t *bytesRead) {
  PHYSFS_Stat stat = {};
  if (!PHYSFS_stat(filename, &stat)) {
    *bytesRead = 0;
    fprintf(stderr, "Could not find file %s (%s)\n", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    return NULL;
  }

  if (stat.filesize == 0 || stat.filetype != PHYSFS_FILETYPE_REGULAR) {
    *bytesRead = 0;
    fprintf(stderr, "Could not load file %s (size: %llu type: %d)\n", filename, stat.filesize, stat.filetype);
    return NULL;
  }

  PHYSFS_File *f = PHYSFS_openRead(filename);
  if (f == NULL) {
    *bytesRead = 0;
    fprintf(stderr, "Could not read file %s (%s)\n", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    return NULL;
  }

  unsigned char *b = (unsigned char *)malloc(stat.filesize);
  if (b == NULL) {
    *bytesRead = 0;
    PHYSFS_close(f);
    return NULL;
  }

  PHYSFS_sint64 br = PHYSFS_readBytes(f, b, stat.filesize);
  *bytesRead = br;
  PHYSFS_close(f);
  return b;
}

// save a file to native filesystem
bool fs_save_file_real(const char *filename, const void *data, uint32_t byteSize) {
  if (filename == NULL || data == NULL) {
    return false;
  }
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    return false;
  }

  size_t count = fwrite(data, sizeof(unsigned char), byteSize, file);

  if (count <= 0) {
    fclose(file);
    return false;
  }

  if (count != (size_t)byteSize) {
    fclose(file);
    return false;
  }

  return fclose(file) == 0;
}

// save a file to physfs filesystem
bool fs_save_file(const char *filename, const void *data, uint32_t byteSize) {
  PHYSFS_File *f = PHYSFS_openWrite(filename);
  if (f == NULL) {
    fprintf(stderr, "Could not write file %s (%s)\n", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    return false;
  }
  PHYSFS_sint64 bytesWritten = PHYSFS_writeBytes(f, data, byteSize);
  PHYSFS_close(f);
  if (byteSize != bytesWritten) {
    return false;
  }
  return true;
}

bool fs_append_file(const char *filename, const void *data, uint32_t byteSize) {
  PHYSFS_File *f = PHYSFS_openAppend(filename);
  if (f == NULL) {
    fprintf(stderr, "Could not append to file %s (%s)\n", filename, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    return false;
  }
  PHYSFS_sint64 bytesWritten = PHYSFS_writeBytes(f, data, byteSize);
  PHYSFS_close(f);
  if (byteSize != bytesWritten) {
    return false;
  }
  return true;
}

// just detect filetype from first 4 bytes
DetectFileType fs_parse_magic_bytes(uint32_t magic_number) {
  switch (magic_number) {
  case 0x4034b50: // ZIP
    return FILE_TYPE_ZIP;

  case 0x6d736100: // WASM
    return FILE_TYPE_WASM;

  case 0x89504E47: // PNG
    return FILE_TYPE_PNG;

  // JPEG variants
  case 0xe0ffd8ff: // JPEG/JFIF
  case 0xe1ffd8ff: // JPEG/Exif
  case 0xeeffd8ff: // JPEG/SPIFF
  case 0xfeffd8ff: // JPEG/COM
    return FILE_TYPE_JPEG;

  case 0x46464952: // WAV ("RIFF")
    return FILE_TYPE_WAV;

  case 0x5367674f: // OGG ("OggS")
    return FILE_TYPE_OGG;

  // MP3 variants
  case 0x03334449: // MP3 with ID3v2.3
  case 0x02334449: // MP3s with ID3v2.2
  case 0x04334449: // MP3 with ID3v2.4
    return FILE_TYPE_MP3;

  case 0x00010000: // TTF font
    return FILE_TYPE_TTF;

  case 0x4F54544F: // OTF font
    return FILE_TYPE_OTF;

  case 0x47494638:
    return FILE_TYPE_GIF;
  }

  // if bytes are not 4-length signatures, check other things
  unsigned char b[4] = {};
  memcpy(&b, &magic_number, 4);
  if (b[0] == 0x42 && b[1] == 0x4D) {
    return FILE_TYPE_BMP;
  }

  return FILE_TYPE_UNKNOWN;
}

// detect file-type from native filesystem file
DetectFileType fs_detect_type_real(const char *filename) {
  struct stat sb;

  if (stat(filename, &sb) != 0) {
    return FILE_TYPE_UNKNOWN;
  }
  if (S_ISDIR(sb.st_mode)) {
    return FILE_TYPE_DIR;
  }

  uint32_t magic_number = 0;
  FILE *file = fopen(filename, "rb");
  if (!file) {
    return FILE_TYPE_UNKNOWN;
  }
  fread(&magic_number, sizeof(uint32_t), 1, file);
  fclose(file);

  return fs_parse_magic_bytes(magic_number);
}

// detect file-type from physfs filesystem file
DetectFileType fs_detect_type(const char *filename) {
  PHYSFS_File *f = PHYSFS_openRead(filename);
  if (!f) {
    return FILE_TYPE_UNKNOWN;
  }
  uint32_t magic_number = 0;
  PHYSFS_sint64 br =
    PHYSFS_readBytes(f, (unsigned char *)&magic_number, sizeof(uint32_t));
  PHYSFS_close(f);
  if (br != sizeof(uint32_t)) {
    return FILE_TYPE_UNKNOWN;
  }
  return fs_parse_magic_bytes(magic_number);
}


// get the short-name of cart, using filename ("/carts/simple_lua.null0" -> "simple_lua")
char *fs_get_cart_name(const char *filename) {
  if (filename == NULL) {
    return NULL;
  }

  // just the name, without any directories
  const char *name = filename;
  for (const char *c = filename; *c != '\0'; c++) {
    if (*c == '/' || *c == '\\') {
      name = c + 1;
    }
  }

  // ... and without the extension
  const char *dot = strrchr(name, '.');
  size_t length = dot == NULL || dot == name ? strlen(name) : (size_t)(dot - name);
  if (length == 0) {
    return NULL;
  }

  char *out = (char *)malloc(length + 1);
  if (out == NULL) {
    return NULL;
  }
  memcpy(out, name, length);
  out[length] = '\0';
  return out;
}

// get the real location of write-dir
char *fs_get_write_dir() {
  return (char *)PHYSFS_getWriteDir();
}

// point the write-dir at a per-cart directory in the user's pref-dir, and
// mount it, so a cart can save files (save_image, and friends) and load them
// again later. it's mounted last, so files in the cart itself still win
bool fs_set_write_dir(const char *cartFilename) {
  char *cartName = fs_get_cart_name(cartFilename);
  if (cartName == NULL) {
    return false;
  }

  const char *writeDir = PHYSFS_getPrefDir("null0", cartName);
  free(cartName);

  if (writeDir == NULL) {
    fprintf(stderr, "Could not find anywhere to save files (%s)\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    return false;
  }

  if (!PHYSFS_setWriteDir(writeDir)) {
    fprintf(stderr, "Could not save files in %s (%s)\n", writeDir, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    return false;
  }

  return PHYSFS_mount(writeDir, NULL, 1) != 0;
}

// Check if executable has embedded cart data
bool fs_has_embedded_cart(const char *exe_path) {
    FILE *file = fopen(exe_path, "rb");
    if (!file) {
        return false;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    
    if (file_size < 22) { // Minimum size for EOCD record
        fclose(file);
        return false;
    }
    
    // Search for End of Central Directory signature (0x06054b50)
    // We need to scan backwards from the end since there might be comments
    long search_start = file_size - 22; // Minimum EOCD size
    long search_end = file_size - 65536; // Maximum comment size is 65535
    if (search_end < 0) search_end = 0;
    
    for (long pos = search_start; pos >= search_end; pos--) {
        fseek(file, pos, SEEK_SET);
        uint32_t signature;
        
        if (fread(&signature, sizeof(uint32_t), 1, file) != 1) {
            continue;
        }
        
        if (signature == 0x06054b50) { // End of central directory signature
            fclose(file);
            return true;
        }
    }
    
    fclose(file);
    return false;
}

// Mount executable with embedded cart data
bool fs_mount_embedded_cart(const char *exe_path) {
    
    if (!fs_has_embedded_cart(exe_path)) {
        return false;
    }
    
    // PhysFS can directly mount executables with appended zip data
    if (PHYSFS_mount(exe_path, NULL, 1) == 0) {
        return false;
    }
    
    return true;
}

// Get size of embedded cart data (0 if none)
size_t fs_get_embedded_cart_size(const char *exe_path) {
    if (!fs_has_embedded_cart(exe_path)) {
        return 0;
    }
    
    FILE *file = fopen(exe_path, "rb");
    if (!file) return 0;
    
    // Read the End of Central Directory Record
    fseek(file, -22, SEEK_END); // EOCD is 22 bytes minimum
    
    uint32_t signature;
    uint16_t disk_number;
    uint16_t central_dir_disk;
    uint16_t num_entries_this_disk;
    uint16_t num_entries_total;
    uint32_t central_dir_size;
    uint32_t central_dir_offset;
    uint16_t comment_length;
    
    fread(&signature, 4, 1, file);
    if (signature != 0x06054b50) {
        fclose(file);
        return 0;
    }
    
    fread(&disk_number, 2, 1, file);
    fread(&central_dir_disk, 2, 1, file); 
    fread(&num_entries_this_disk, 2, 1, file);
    fread(&num_entries_total, 2, 1, file);
    fread(&central_dir_size, 4, 1, file);
    fread(&central_dir_offset, 4, 1, file);
    fread(&comment_length, 2, 1, file);
    
    fclose(file);
    
    // Calculate zip size: from start of zip to end of file
    long file_size;
    file = fopen(exe_path, "rb");
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fclose(file);
    
    // ZIP starts at central_dir_offset minus central_dir_size
    // This gives us the approximate size of the appended zip data
    size_t zip_size = file_size - central_dir_offset;
    
    return zip_size;
}