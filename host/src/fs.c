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
  PHYSFS_stat(filename, &stat);
  if (stat.filesize == 0 || stat.filetype != PHYSFS_FILETYPE_REGULAR ) {
    *bytesRead = 0;
    fprintf(stderr, "Could not load file %s (size: %llu type: %d)\n", filename, stat.filesize, stat.filetype);
    return NULL;
  }

  PHYSFS_File *f = PHYSFS_openRead(filename);
  unsigned char *b = (unsigned char *)malloc(stat.filesize);
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
  PHYSFS_sint64 bytesWritten = PHYSFS_writeBytes(f, data, byteSize);
  PHYSFS_close(f);
  if (byteSize != bytesWritten) {
    return false;
  }
  return true;
}

bool fs_append_file(const char *filename, const void *data, uint32_t byteSize) {
  PHYSFS_File *f = PHYSFS_openAppend(filename);
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
  if (br != sizeof(uint32_t)) {
    return FILE_TYPE_UNKNOWN;
  }
  PHYSFS_close(f);
  return fs_parse_magic_bytes(magic_number);
}
