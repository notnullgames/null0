// this is the native C runtime for null0

// TODO: figure out screen-scaling (scale 320x240 to any size) & fullscreen
// TODO: configurable input-mapping
// TODO: handle other string-types (non-assemblyscript)
// TODO: safe writable support for persistant data
// TODO: I changed how fonts work, need to update runtime
// TODO: Need to unload things

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "wasm3.h"
#include "m3_env.h"
#include "raylib.h"
#include "physfs.h"
#include <libgen.h>

#define RLUNICODE_IMPLEMENTATION
#include "rlunicode.h"

int map_keys[12] = {
  KEY_X,           // A
  KEY_Z,           // B
  KEY_S,           // X
  KEY_A,           // Y
  KEY_Q,           // L1
  KEY_W,           // R1
  KEY_ENTER,       // START
  KEY_LEFT_SHIFT,  // SELECT
  KEY_LEFT,        // LEFT
  KEY_RIGHT,       // RIGHT
  KEY_UP,          // UP
  KEY_DOWN         // DOWN
};

int map_gamepad[12] = {
  GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, // A
  GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // B
  GAMEPAD_BUTTON_RIGHT_FACE_UP,    // X
  GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // Y
  GAMEPAD_BUTTON_LEFT_TRIGGER_1,  // L1
  GAMEPAD_BUTTON_RIGHT_TRIGGER_1, // L2
  GAMEPAD_BUTTON_MIDDLE_RIGHT,    // START
  GAMEPAD_BUTTON_MIDDLE_LEFT,     // SELECT
  GAMEPAD_BUTTON_LEFT_FACE_LEFT,  // LEFT
  GAMEPAD_BUTTON_LEFT_FACE_RIGHT, // RIGHT
  GAMEPAD_BUTTON_LEFT_FACE_UP,    // UP
  GAMEPAD_BUTTON_LEFT_FACE_DOWN   // DOWN
};

char *asset_prefix;

static M3Environment* env;
static M3Runtime* runtime;
static M3Module* module;
bool shouldExit = false;

// this is the resource-counter, so every resource has a unique ID
uint32_t r = 0;

// These are the resources, each in their own array
// TODO: is there a better way to do these arrays?
// TODO: do more pointers
Texture2D resources_images[1024];
Music resources_music[1024];
Sound resources_sound[1024];
Font resources_fonts[1024];
int currentMusic = 0;

// throw a fatal error
static void null0_fatal_error(char* func, char* msg) {
  fprintf(stderr, "FATAL: %s - %s\n", func, msg);
  exit(1);
}

// all wasm3 functions return same sort of error-pattern, so this wraps that
static void null0_check_wasm3 (M3Result result) {
  if (result) {
    M3ErrorInfo info;
    m3_GetErrorInfo(runtime, &info);
    char *message;
    sprintf(message, "%s - %s", result, info.message);
    null0_fatal_error("wasm", message);
  }
}

// this checks the general state of the runtime, to make sure there are no errors lingering
static void null0_check_wasm3_is_ok () {
  M3ErrorInfo error;
  m3_GetErrorInfo(runtime, &error);
  if (error.result) {
    char *message;
    sprintf(message, "%s - %s", error.result, error.message);
    null0_fatal_error("wasm", message);
  }
}

// THESE LOOSELY CAME FROM raylib-physfs

/**
 * Reports the last PhysFS error to raylib's TraceLog.
 *
 * @param detail Any additional detail to append to the reported error.
 *
 * @see PHYSFS_getLastErrorCode()
 *
 * @internal
 */
void TracePhysFSError(const char* detail) {
    int errorCode = PHYSFS_getLastErrorCode();
    if (errorCode == PHYSFS_ERR_OK) {
        TraceLog(LOG_WARNING, TextFormat("PHYSFS: %s", detail));
    } else {
        const char* errorMessage = PHYSFS_getErrorByCode(errorCode);
        TraceLog(LOG_WARNING, TextFormat("PHYSFS: %s (%s)", errorMessage, detail));
    }
}

/**
 * Determine if a file exists in the search path.
 *
 * @param fileName Filename in platform-independent notation.
 *
 * @return True if the file exists, false otherwise.
 *
 * @see DirectoryExistsInPhysFS()
 */
bool FileExistsInPhysFS(const char* fileName) {
    PHYSFS_Stat stat;
    if (PHYSFS_stat(fileName, &stat) == 0) {
        return false;
    }
    return stat.filetype == PHYSFS_FILETYPE_REGULAR;
}


/**
 * Loads the given file as a byte array from PhysFS (read).
 *
 * @param fileName The file to load.
 * @param bytesRead An unsigned integer to save the bytes that were read.
 *
 * @return The file data as a pointer. Make sure to use UnloadFileData() when finished using the file data.
 *
 * @see UnloadFileData()
 */
unsigned char* LoadFileDataFromPhysFS(const char* fileName, unsigned int* bytesRead) {
    if (!FileExistsInPhysFS(fileName)) {
        TraceLog(LOG_WARNING, TextFormat("PHYSFS: Tried to load unexisting file '%s'", fileName));
        *bytesRead = 0;
        return 0;
    }

    // Open up the file.
    void* handle = PHYSFS_openRead(fileName);
    if (handle == 0) {
        TracePhysFSError(fileName);
        *bytesRead = 0;
        return 0;
    }

    // Check to see how large the file is.
    int size = PHYSFS_fileLength(handle);
    if (size == -1) {
        *bytesRead = 0;
        PHYSFS_close(handle);
        TraceLog(LOG_WARNING, TextFormat("PHYSFS: Cannot determine size of file '%s'", fileName));
        return 0;
    }

    // Close safely when it's empty.
    if (size == 0) {
        PHYSFS_close(handle);
        *bytesRead = 0;
        return 0;
    }

    // Read the file, return if it's empty.
    void* buffer = MemAlloc(size);
    int read = PHYSFS_readBytes(handle, buffer, size);
    if (read < 0) {
        *bytesRead = 0;
        MemFree(buffer);
        PHYSFS_close(handle);
        TracePhysFSError(fileName);
        return 0;
    }

    // Close the file handle, and return the bytes read and the buffer.
    PHYSFS_close(handle);
    *bytesRead = read;
    return buffer;
}

/**
 * Load an image from PhysFS.
 *
 * @param fileName The filename to load from the search paths.
 *
 * @return The loaded image on success. An empty Image otherwise.
 */
Image LoadImageFromPhysFS(const char* fileName) {
    unsigned int bytesRead;
    unsigned char* fileData = LoadFileDataFromPhysFS(fileName, &bytesRead);
    if (bytesRead == 0) {
        struct Image output;
        output.data = 0;
        output.width = 0;
        output.height = 0;
        return output;
    }

    // Load from the memory.
    const char* extension = GetFileExtension(fileName);
    Image image = LoadImageFromMemory(extension, fileData, bytesRead);
    UnloadFileData(fileData);
    return image;
}

/**
 * Load a texture from PhysFS.
 *
 * @param fileName The filename to load from the search paths.
 *
 * @return The loaded texture on success. An empty texture otherwise.
 *
 * @see LoadImageFromPhysFS()
 */
Texture2D LoadTextureFromPhysFS(const char* fileName) {
    Image image = LoadImageFromPhysFS(fileName);
    if (image.data == 0) {
        Texture2D output = { 0 };
        output.id = 0;
        output.format = 0;
        output.width = 0;
        output.height = 0;
        return output;
    }
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

/**
 * Load font from PhysFS.
 *
 * @param fileName The file name to load from the PhysFS mount paths.
 *
 * @return The Font object, or an empty Font object on failure.
 *
 * @see UnloadFont()
 */
Font LoadFontFromPhysFS(const char* fileName, int fontSize, int *fontChars, int charsCount) {
    unsigned int bytesRead;
    unsigned char* fileData = LoadFileDataFromPhysFS(fileName, &bytesRead);
    if (bytesRead == 0) {
        struct Font output;
        output.baseSize = 0;
        output.glyphCount = 0;
        output.glyphPadding = 0;
        output.glyphs = 0;
        output.recs = 0;
        return output;
    }

    // Load from the memory.
    const char* extension = GetFileExtension(fileName);
    Font font = LoadFontFromMemory(extension, fileData, bytesRead, fontSize, fontChars, charsCount);
    UnloadFileData(fileData);
    return font;
}

/**
 * Load wave data from PhysFS.
 *
 * @param fileName The file name to load from the PhysFS mount paths.
 *
 * @return The Wave object, or an empty Wave object on failure.
 *
 * @see UnloadWave()
 */
Wave LoadWaveFromPhysFS(const char* fileName) {
    unsigned int bytesRead;
    unsigned char* fileData = LoadFileDataFromPhysFS(fileName, &bytesRead);
    if (bytesRead == 0) {
        struct Wave output;
        output.data = 0;
        return output;
    }

    // Load from the memory.
    const char* extension = GetFileExtension(fileName);
    Wave wave = LoadWaveFromMemory(extension, fileData, bytesRead);
    UnloadFileData(fileData);
    return wave;
}

/**
 * Load module music from PhysFS.
 *
 * @param fileName The file name to load from the PhysFS mount paths.
 *
 * @return The Music object, or an empty Music object on failure.
 *
 * @see UnloadMusic()
 */
Music LoadMusicStreamFromPhysFS(const char* fileName) {
    unsigned int bytesRead;
    unsigned char* fileData = LoadFileDataFromPhysFS(fileName, &bytesRead);
    if (bytesRead == 0) {
        struct Music output;
        output.ctxData = 0;
        output.stream.buffer = 0;
        return output;
    }

    // Load from the memory.
    const char* extension = GetFileExtension(fileName);
    Music music = LoadMusicStreamFromMemory(extension, fileData, bytesRead);
    UnloadFileData(fileData);
    return music;
}

/**
 * Load sound data from PhysFS.
 *
 * @param fileName The file name to load from the PhysFS mount paths.
 *
 * @return The Sound object, or an empty Sound object on failure.
 *
 * @see UnloadSound()
 */
Sound LoadSoundFromPhysFS(const char* fileName) {
  return LoadSoundFromWave(LoadWaveFromPhysFS(fileName));
}

// EXPORTS
static M3Function* cart_init;
static M3Function* cart_update;
static M3Function* cart_loaded;
static M3Function* cart_buttonUp;
static M3Function* cart_buttonDown;

// IMPORTS

// Fatal error
static m3ApiRawFunction (null0_abort) {
  m3ApiGetArgMem(const uint16_t *, _message);
  int _lmessage = (*(_message-2) / 2);
  char message[_lmessage];
  ConvertUTF16ToUTF8(_message, message, _lmessage);

  m3ApiGetArgMem(const uint16_t *, _fileName);
  int _lfileName = (*(_fileName-2) / 2);
  char fileName[_lfileName];
  ConvertUTF16ToUTF8(_fileName, fileName, _lfileName);

  m3ApiGetArg(uint16_t, lineNumber);
  m3ApiGetArg(uint16_t, columnNumber);

  char* msg;
  sprintf(msg, "%s at %s:%d:%d", message, fileName, lineNumber, columnNumber);
  null0_fatal_error("cart", msg);

  m3ApiSuccess();
}

// Log a string
static m3ApiRawFunction (null0_log) {
  m3ApiGetArgMem(const uint16_t *, _message);
  int _lmessage = (*(_message-2) / 2);
  char message[_lmessage];
  ConvertUTF16ToUTF8(_message, message, _lmessage);

  printf("%s\n", message);

  m3ApiSuccess();
}

// Get the frames-per-second
static m3ApiRawFunction (null0_getFPS) {
  m3ApiReturnType (uint16_t);

  uint16_t fps = GetFPS();

  m3ApiReturn(fps);
}

// Clear screen with a color
static m3ApiRawFunction (null0_cls) {
  m3ApiGetArg(uint32_t, color);

  ClearBackground(GetColor(color));

  m3ApiSuccess();
}

// Set the title of the window
static m3ApiRawFunction (null0_setTitle) {
  m3ApiGetArgMem(const uint16_t *, _title);
  int _ltitle = (*(_title-2) / 2);
  char title[_ltitle];
  ConvertUTF16ToUTF8(_title, title, _ltitle);

  SetWindowTitle(title);

  m3ApiSuccess();
}

// Load an image
static m3ApiRawFunction (null0_loadImage) {
  m3ApiReturnType (uint32_t);

  m3ApiGetArgMem(const uint16_t *, _fileName);
  int _lfileName = (*(_fileName-2) / 2);
  char fileName[_lfileName];
  ConvertUTF16ToUTF8(_fileName, fileName, _lfileName);

  r++;
  resources_images[r] = LoadTextureFromPhysFS(fileName);

  m3ApiReturn(r);
}

// Draw an image
static m3ApiRawFunction (null0_drawImage) {
  m3ApiGetArg(uint32_t, id);
  m3ApiGetArg(int16_t, x);
  m3ApiGetArg(int16_t, y);

  DrawTexture(resources_images[id], x, y, WHITE);

  m3ApiSuccess();
}

// Get width for an image
static m3ApiRawFunction (null0_imageWidth) {
  m3ApiReturnType (uint16_t);

  m3ApiGetArg(uint32_t, id);

  uint16_t retval = resources_images[id].width;

  m3ApiReturn(retval);
}

// Get height for an image
static m3ApiRawFunction (null0_imageHeight) {
  m3ApiReturnType (uint16_t);

  m3ApiGetArg(uint32_t, id);

  uint16_t retval = resources_images[id].height;

  m3ApiReturn(retval);
}

// Load a mod music file
static m3ApiRawFunction (null0_loadMusic) {
  m3ApiReturnType (uint32_t);

  m3ApiGetArgMem(const uint16_t *, _fileName);
  int _lfileName = (*(_fileName-2) / 2);
  char fileName[_lfileName];
  ConvertUTF16ToUTF8(_fileName, fileName, _lfileName);

  r++;
  resources_music[r] = LoadMusicStreamFromPhysFS(fileName);
  resources_music[r].looping = true;

  m3ApiReturn(r);
}

// Load a sound file
static m3ApiRawFunction (null0_loadSound) {
  m3ApiReturnType (uint32_t);

  m3ApiGetArgMem(const uint16_t *, _fileName);
  int _lfileName = (*(_fileName-2) / 2);
  char fileName[_lfileName];
  ConvertUTF16ToUTF8(_fileName, fileName, _lfileName);

  r++;
  resources_sound[r] = LoadSoundFromPhysFS(fileName);

  m3ApiReturn(r);
}

// Play a sound file
static m3ApiRawFunction (null0_playSound) {
  m3ApiGetArg(uint32_t, id);

  PlaySound(resources_sound[id]);

  m3ApiSuccess();
}

// check if a sound is playing
static m3ApiRawFunction (null0_soundPlaying) {
  m3ApiReturnType (bool);

  m3ApiGetArg(uint32_t, id);

  m3ApiReturn(IsSoundPlaying(resources_sound[id]));
}

// Play a mod music file
static m3ApiRawFunction (null0_playMusic) {
  m3ApiGetArg(uint32_t, id);

  currentMusic = id;
  PlayMusicStream(resources_music[id]);

  m3ApiSuccess();
}

// Stop the mod music
static m3ApiRawFunction (null0_stopMusic) {
  m3ApiGetArg(uint32_t, id);

  StopMusicStream(resources_music[id]);

  m3ApiSuccess();
}

// Draw text on the screen
static m3ApiRawFunction (null0_loadFont) {
  m3ApiReturnType (uint32_t);
  
  m3ApiGetArgMem(const uint16_t *, _fileName);
  int _lfileName = (*(_fileName-2) / 2);
  char fileName[_lfileName];
  ConvertUTF16ToUTF8(_fileName, fileName, _lfileName);

  r++;
  resources_fonts[r] = LoadFontFromPhysFS(fileName);

  m3ApiReturn(r);
}

// Draw text on the screen
// TODO: this seems to be crashing update()
static m3ApiRawFunction (null0_drawText) {
  // text:string, x:i16, y: i16, color: u32, size: u16, font:u32
  m3ApiGetArgMem(const uint16_t *, _text);
  m3ApiGetArg(int16_t, x);
  m3ApiGetArg(int16_t, y);
  m3ApiGetArg(uint32_t, _color);
  m3ApiGetArg(uint16_t, size);
  m3ApiGetArg(uint32_t, id);

  int _ltext = (*(_text-2) / 2);
  char text[_ltext];
  ConvertUTF16ToUTF8(_text, text, _ltext);

  Color color = GetColor(_color);

  if (id == 0) {
    DrawText(text, x, y, size, color);
  } else {
    DrawTextEx(resources_fonts[id], text, (Vector2){ x, y }, size, 0, color);
  }

  m3ApiSuccess();
}

// Draw a single frame from a spritesheet
static m3ApiRawFunction (null0_drawSprite) {
  m3ApiGetArg(uint32_t, id);
  m3ApiGetArg(uint16_t, frame);
  m3ApiGetArg(uint16_t, width);
  m3ApiGetArg(uint16_t, height);
  m3ApiGetArg(uint16_t, x);
  m3ApiGetArg(uint16_t, y);

  Texture2D texture = resources_images[id];
  uint16_t columns = texture.width / width;
  uint16_t frameX = ((frame % columns) * width);
  uint16_t frameY = ((frame / columns) * height);
  Rectangle sourceRec = { frameX, frameY, width, height };
  Vector2 position = { x, y };

  DrawTextureRec(texture, sourceRec, position, WHITE);

  m3ApiSuccess();
}

static m3ApiRawFunction (null0_exit) {
  shouldExit = true;
  m3ApiSuccess();
}

// load a wasm binary buffer
void null0_load_cart_wasm (u8* wasmBuffer, int byteLength) {
  env = m3_NewEnvironment();
  runtime = m3_NewRuntime (env, 1024, NULL);
  null0_check_wasm3(m3_ParseModule (env, &module, wasmBuffer, byteLength));
  null0_check_wasm3(m3_LoadModule(runtime, module));

  // IMPORTS
  m3_LinkRawFunction(module, "env", "null0_cls", "v(i)", &null0_cls);
  m3_LinkRawFunction(module, "env", "null0_setTitle", "v(i)", &null0_setTitle);
  m3_LinkRawFunction(module, "env", "null0_loadImage", "i(i)", &null0_loadImage);
  m3_LinkRawFunction(module, "env", "null0_drawImage", "v(iii)", &null0_drawImage);
  m3_LinkRawFunction(module, "env", "null0_imageWidth", "i(i)", &null0_imageWidth);
  m3_LinkRawFunction(module, "env", "null0_imageHeight", "i(i)", &null0_imageHeight);
  m3_LinkRawFunction(module, "env", "null0_loadSound", "i(i)", &null0_loadSound);
  m3_LinkRawFunction(module, "env", "null0_playSound", "v(i)", &null0_playSound);
  m3_LinkRawFunction(module, "env", "null0_soundPlaying", "i(i)", &null0_soundPlaying);
  m3_LinkRawFunction(module, "env", "null0_loadMusic", "i(i)", &null0_loadMusic);
  m3_LinkRawFunction(module, "env", "null0_playMusic", "v(i)", &null0_playMusic);
  m3_LinkRawFunction(module, "env", "null0_stopMusic", "v(i)", &null0_stopMusic);
  m3_LinkRawFunction(module, "env", "null0_drawSprite", "v(iiiiii)", &null0_drawSprite);
  m3_LinkRawFunction(module, "env", "null0_getFPS", "i()", &null0_getFPS);
  m3_LinkRawFunction(module, "env", "null0_drawText", "v(iiii)", &null0_drawText);
  m3_LinkRawFunction(module, "env", "null0_loadFont", "i(iii)", &null0_loadFont);
  m3_LinkRawFunction(module, "env", "null0_log", "v(i)", &null0_log);
  m3_LinkRawFunction(module, "env", "null0_exit", "v()", &null0_exit);
  m3_LinkRawFunction(module, "env", "abort", "v(iiii)", &null0_abort);
  
  null0_check_wasm3_is_ok();

  // EXPORTS
  m3_FindFunction(&cart_init, runtime, "init");
  m3_FindFunction(&cart_update, runtime, "update");
  m3_FindFunction(&cart_loaded, runtime, "loaded");
  m3_FindFunction(&cart_buttonUp, runtime, "buttonUp");
  m3_FindFunction(&cart_buttonDown, runtime, "buttonDown");
}

// detect if this is a zip file
bool null0_detect_zip(char* filename) {
  unsigned char bytes[4];
  FILE* fp=fopen(filename, "r");
  if (!fp) {
    null0_fatal_error("file", "read - Cannot read file.");
  }
  fread(&bytes, 4, 1, fp);
  fclose(fp);
  return (bytes[0] == 0x50 && bytes[1] == 0x4b && bytes[2] == 0x03 && bytes[3] == 0x04);
}

int main (int argc, char **argv) {
  PHYSFS_init(argv[0]);

  if (null0_detect_zip(argv[1])) {
    // zip file, so add to search-path
    PHYSFS_mount(argv[1], NULL, 0);
  } else {
    // not zip, so add the dir of the wasm file to search-path
    PHYSFS_mount(dirname(argv[1]), NULL, 0);
  }

  if (!FileExistsInPhysFS("cart.wasm")) {
    null0_fatal_error("cart", "no cart.wasm!");
  }

  PHYSFS_File* wasmFile = PHYSFS_openRead("cart.wasm");
  PHYSFS_uint64 wasmLen = PHYSFS_fileLength(wasmFile);
  u8* wasmBuffer[wasmLen];
  PHYSFS_sint64 bytesRead = PHYSFS_readBytes(wasmFile, wasmBuffer, wasmLen);
  if (bytesRead == -1) {
    char* err;
    sprintf(err, "Error opening cart.wasm: %s", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    null0_fatal_error("file", err);
  }

  null0_load_cart_wasm (wasmBuffer, wasmLen);
  
  // disable raylib debugging output
  SetTraceLogLevel(LOG_ERROR);

  InitWindow(320, 240, "null0");
  InitAudioDevice();
  SetTargetFPS(60);

  if (cart_init) {
    null0_check_wasm3(m3_CallV(cart_init));
  } else {
    printf("cart: no init.\n");
  }

  // this ensures loaded is called after init
  // they are synchronous, so all of these should already be loaded.
  // in async places (javascript) these would be called in the loader
  if (cart_loaded) {
    for (int i=0; i<=r; i++) {
      m3_CallV (cart_loaded, i);
    }
  }

  double delta = 0;

  while (!WindowShouldClose() && !shouldExit) {
    delta = GetFrameTime();

    if (cart_buttonDown) {
      for (uint8_t i=0; i< 12; i++) {
        if (IsKeyPressed(map_keys[i])) {
          m3_CallV (cart_buttonDown, i);
        }
        if (IsGamepadAvailable(0)) {
          if (IsGamepadButtonPressed(0, map_gamepad[i])) {
            m3_CallV (cart_buttonDown, i);
          }
        }
      }
    }
    if (cart_buttonUp) {
      for (uint8_t i=0; i< 12; i++) {
        if (IsKeyReleased(map_keys[i])) {
          m3_CallV (cart_buttonUp, i);
        }
        if (IsGamepadAvailable(0)) {
          if (IsGamepadButtonReleased(0, map_gamepad[i])) {
            m3_CallV (cart_buttonUp, i);
          }
        }
      }
    }

    BeginDrawing();
    
    if (cart_update) {
      m3_CallV (cart_update, delta);
      UpdateMusicStream(resources_music[currentMusic]);
    }

    EndDrawing();
  }
  // TODO: free all resources
  
  CloseAudioDevice(); 
  CloseWindow();

  return 0;
}

