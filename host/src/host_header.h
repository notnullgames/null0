// setup utils and structures for host
// this will only be included in host.c

#include "host.h"
#include <time.h>
#ifdef _WIN32
#  include <sys/timeb.h>
#else
#  include <sys/time.h>
#endif
#include "exists_next_to_executable.h"
#include <ctype.h>

static pntr_app *null0_app;

static cvector_vector_type(pntr_image *) images;
static cvector_vector_type(pntr_font *) fonts;
static cvector_vector_type(pntr_sound *) sounds;
static cvector_vector_type(cute_tiled_map_t *) tilemaps;

// host-side allocations in cart memory, freed by cart_gc() after the current
// cart callback (load/update/event) returns
static cvector_vector_type(uint32_t) cart_allocations;

// allocate memory in the cart, tracked so cart_gc() can free it later
uint32_t cart_alloc_tracked(size_t size) {
  uint32_t ptr = cart_malloc(size);
  cvector_push_back(cart_allocations, ptr);
  return ptr;
}

// free everything the host allocated in cart memory since the last callback.
// this means host-returned pointers (struct/string returns) are only valid
// until the current cart callback returns - carts must copy what they need
void cart_gc() {
  for (size_t i = 0; i < cvector_size(cart_allocations); i++) {
    cart_free(cart_allocations[i]);
  }
  cvector_clear(cart_allocations);
}

// add an image to loaded images
uint32_t add_image(pntr_image *image) {
  if (image == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(images);
  cvector_push_back(images, image);
  return id;
}

// add a font to loaded fonts
uint32_t add_font(pntr_font *font) {
  if (font == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(fonts);
  cvector_push_back(fonts, font);
  return id;
}

// add a sound to loaded sounds
uint32_t add_sound(pntr_sound *sound) {
  if (sound == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(sounds);
  cvector_push_back(sounds, sound);
  return id;
}

// add a tilemap to loaded tilemaps
uint32_t add_tilemap(cute_tiled_map_t *tilemap) {
  if (tilemap == NULL) {
    return 0;
  }
  uint32_t id = cvector_size(tilemaps);
  cvector_push_back(tilemaps, tilemap);
  return id;
}

// get an image by handle, NULL (with a warning) if out of range
pntr_image *get_image(uint32_t id) {
  if (id >= (uint32_t)cvector_size(images)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid image handle: %u", id);
    return NULL;
  }
  return images[id];
}

// get a font by handle, NULL (with a warning) if out of range
pntr_font *get_font(uint32_t id) {
  if (id >= (uint32_t)cvector_size(fonts)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid font handle: %u", id);
    return NULL;
  }
  return fonts[id];
}

// get a sound by handle, NULL (with a warning) if out of range
pntr_sound *get_sound(uint32_t id) {
  if (id >= (uint32_t)cvector_size(sounds)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid sound handle: %u", id);
    return NULL;
  }
  return sounds[id];
}

// get a tilemap by handle, NULL (with a warning) if out of range
cute_tiled_map_t *get_tilemap(uint32_t id) {
  if (id >= (uint32_t)cvector_size(tilemaps)) {
    pntr_app_log_ex(PNTR_APP_LOG_ERROR, "null0: invalid tilemap handle: %u", id);
    return NULL;
  }
  return tilemaps[id];
}

// pntr_tiled blends layer->tintcolor into the tint when drawing object
// layers, but cute_tiled leaves tintcolor 0 when the layer has no tint, and
// pntr_tiled_color(0) is opaque black - default missing tints to white
static void null0_tiled_fix_layer_tints(cute_tiled_layer_t *layer) {
  while (layer != NULL) {
    if (layer->tintcolor == 0) {
      layer->tintcolor = 0xFFFFFFFF;
    }
    null0_tiled_fix_layer_tints(layer->layers);
    layer = layer->next;
  }
}

// load a Tiled map, fixing up missing layer tints (see above)
cute_tiled_map_t *null0_load_tiled(const char *filename) {
  cute_tiled_map_t *map = pntr_load_tiled(filename);
  if (map != NULL) {
    null0_tiled_fix_layer_tints(map->layers);
  }
  return map;
}

// get the gid of a tile in a layer (by index) of a tilemap
int null0_tile_get_tile(cute_tiled_map_t *map, int layer, int column, int row) {
  cute_tiled_layer_t *l = pntr_tiled_layer_from_index(map, layer);
  if (l == NULL) {
    return 0;
  }
  return pntr_layer_tile(l, column, row);
}

// set the gid of a tile in a layer (by index) of a tilemap
void null0_tile_set_tile(cute_tiled_map_t *map, int layer, int column, int row, int gid) {
  cute_tiled_layer_t *l = pntr_tiled_layer_from_index(map, layer);
  if (l == NULL) {
    return;
  }
  pntr_set_layer_tile(l, column, row, gid);
}

// get a copy of a tile's image, so the cart can unload it like any other image
pntr_image *null0_tile_image(cute_tiled_map_t *map, int gid) {
  pntr_image *tileImage = pntr_tiled_tile_image(map, gid);
  if (tileImage == NULL) {
    return NULL;
  }
  return pntr_image_copy(tileImage);
}

// render a whole tilemap to a new image
pntr_image *null0_gen_image_tiled(cute_tiled_map_t *map) {
  return pntr_gen_image_tiled(map, PNTR_WHITE);
}

// SAM TTS function - generates WAV data from text
// sets byteLength and returns pointer to WAV bytes
char* sam_tts_sound(char* text, bool phonetic, int pitch, int speed, int throat, int mouth, bool sing, unsigned int* byteLength) {
    if (text == NULL || byteLength == NULL) return NULL;
    
    // Prepare input string (SAM expects uppercase)
    char input[512];
    int len = strlen(text);
    if (len >= 500) len = 499; // Leave room for terminator and bracket
    
    int i;
    for (i = 0; i < len; i++) {
        input[i] = toupper((int)text[i]);
    }
    input[i] = '\0';
    
    // Set SAM parameters
    SetPitch((unsigned char)pitch);
    SetSpeed((unsigned char)speed); 
    SetMouth((unsigned char)mouth);
    SetThroat((unsigned char)throat);
    
    if (sing) {
        EnableSingmode();
    }
    
    // Handle phonetic vs text input
    if (!phonetic) {
        strcat(input, "[");
        if (!TextToPhonemes((unsigned char*)input)) {
            return NULL;
        }
    } else {
        strcat(input, "\x9b");
    }
    
    // Generate speech
    SetInput(input);
    if (!SAMMain()) {
        return NULL;
    }
    
    // Get the raw audio buffer
    char* rawBuffer = GetBuffer();
    int rawLength = GetBufferLength() / 50; // SAM divides by 50 for WAV output
    
    if (rawBuffer == NULL || rawLength <= 0) {
        return NULL;
    }
    
    // Calculate WAV file size
    unsigned int wavSize = 44 + rawLength; // WAV header (44 bytes) + data
    char* wavData = (char*)malloc(wavSize);
    if (wavData == NULL) {
        return NULL;
    }
    
    // Build WAV header
    char* ptr = wavData;
    
    // RIFF header
    memcpy(ptr, "RIFF", 4); ptr += 4;
    unsigned int filesize = rawLength + 36;
    memcpy(ptr, &filesize, 4); ptr += 4;
    memcpy(ptr, "WAVE", 4); ptr += 4;
    
    // Format chunk
    memcpy(ptr, "fmt ", 4); ptr += 4;
    unsigned int fmtlength = 16;
    memcpy(ptr, &fmtlength, 4); ptr += 4;
    unsigned short format = 1; // PCM
    memcpy(ptr, &format, 2); ptr += 2;
    unsigned short channels = 1;
    memcpy(ptr, &channels, 2); ptr += 2;
    unsigned int samplerate = 22050;
    memcpy(ptr, &samplerate, 4); ptr += 4;
    memcpy(ptr, &samplerate, 4); ptr += 4; // bytes/second
    unsigned short blockalign = 1;
    memcpy(ptr, &blockalign, 2); ptr += 2;
    unsigned short bitspersample = 8;
    memcpy(ptr, &bitspersample, 2); ptr += 2;
    
    // Data chunk
    memcpy(ptr, "data", 4); ptr += 4;
    memcpy(ptr, &rawLength, 4); ptr += 4;
    memcpy(ptr, rawBuffer, rawLength);
    
    *byteLength = wavSize;
    return wavData;
}

// wrapper around SAM TTS function to return a sound int
pntr_sound* null0_tts_sound(char* text, bool phonetic, int pitch, int speed, int throat, int mouth, bool sing) {
  if (pitch == 0) {
    pitch = 64;
  }
  if (speed == 0) {
    speed = 72;
  }
  if (throat == 0) {
    throat = 128;
  }
  if (mouth == 0) {
    mouth = 128;
  }
  unsigned int byteLength = 0;
  char* wavData = sam_tts_sound(text, phonetic, pitch, speed, throat, mouth, sing, &byteLength);
  pntr_sound* sound = pntr_load_sound_from_memory(PNTR_APP_SOUND_TYPE_WAV, (unsigned char*)wavData, byteLength);
  // pntr_unload_memory(wavData);
  return sound;
}

// wrapper around pntr_app_sfx_sound
pntr_sound* null0_sfx_sound(SfxParams* params) {
  return pntr_app_sfx_sound(null0_app, params);
}

typedef enum SfxPresetType {
  SFX_COIN,
  SFX_LASER,
  SFX_EXPLOSION,
  SFX_POWERUP,
  SFX_HURT,
  SFX_JUMP,
  SFX_SELECT,
  SFX_SYNTH
} SfxPresetType;


// generate randomized SfxParams
SfxParams null0_sfx_generate(int type) {
  SfxParams sp = {};
  switch (type) {
    case SFX_COIN:
      pntr_app_sfx_gen_pickup_coin(null0_app, &sp);
      break;
    case SFX_LASER:
      pntr_app_sfx_gen_laser_shoot(null0_app, &sp);
      break;
    case SFX_EXPLOSION:
      pntr_app_sfx_gen_explosion(null0_app, &sp);
      break;
    case SFX_POWERUP:
      pntr_app_sfx_gen_powerup(null0_app, &sp);
      break;
    case SFX_HURT:
      pntr_app_sfx_gen_hit_hurt(null0_app, &sp);
      break;
    case SFX_JUMP:
      pntr_app_sfx_gen_jump(null0_app, &sp);
      break;
    case SFX_SELECT:
      pntr_app_sfx_gen_blip_select(null0_app, &sp);
      break;
    case SFX_SYNTH:
      pntr_app_sfx_gen_synth(null0_app, &sp);
      break;
    default:
      pntr_app_sfx_gen_pickup_coin(null0_app, &sp);
      break;
  }
  return sp;
}

// copy a string from cart to host
char *copy_string_from_cart(uint32_t cart_pointer) {
  uint32_t size = cart_strlen(cart_pointer) + 1;
  char *ret = malloc(size);
  mem_from_cart(ret, cart_pointer, size);
  return ret;
}

// copy a string from host to cart
uint32_t copy_string_to_cart(char *host_pointer) {
  uint32_t size = strlen(host_pointer) + 1;
  uint32_t ret = cart_alloc_tracked(size);
  mem_to_cart(ret, (void *)host_pointer, size);
  return ret;
}

// copy a color from cart to host
pntr_color copy_color_from_cart(uint32_t colorPtr) {
  CartColor c = {};
  mem_from_cart(&c, colorPtr, sizeof(CartColor));
  pntr_color ret = pntr_new_color(c.r, c.g, c.b, c.a);
  return ret;
}

// copy a color form host to cart
uint32_t copy_color_to_cart(pntr_color color) {
  CartColor *c = malloc(sizeof(CartColor));
  c->r = color.rgba.r;
  c->g = color.rgba.g;
  c->b = color.rgba.b;
  c->a = color.rgba.a;
  uint32_t ret = cart_alloc_tracked(sizeof(CartColor));
  mem_to_cart(ret, c, sizeof(CartColor));
  return ret;
}

// Allocate & copy memory from cart to host
void *copy_memory_from_cart(uint32_t src, uint32_t size) {
  void *dest = malloc(size);
  mem_from_cart(dest, src, size);
  return dest;
}

// Allocate & copy memory from host to cart
uint32_t copy_memory_to_cart(void *src, uint32_t size) {
  uint32_t dest = cart_alloc_tracked(size);
  mem_to_cart(dest, src, size);
  return dest;
}

bool host_init(pntr_app *app) {
  // First try to find embedded cart in executable
  char* exe_path = get_executable_path();
  bool has_embedded = exe_path && fs_has_embedded_cart(exe_path);

  if (has_embedded && !app->argFile) {
    // Use embedded cart
    app->argFile = strdup(exe_path);
  } else {
    // Fallback to external file
    char* main_path = file_exists_next_to_executable("main.null0");
    if (!app->argFile && main_path) {
      app->argFile = strdup(main_path);
    }
    free(main_path);
  }
  
  if (exe_path) free(exe_path);

  if (!app->argFile) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "Usage: null <CART>");
    return false;
  }

  null0_app = app;

  if (!PHYSFS_init("/")) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "Could not start filesystem.");
    return false;
  }

  uint32_t cartSize = 0;
  unsigned char *cartBytes = NULL;
  uint32_t wasmSize = 0;
  unsigned char *wasmBytes = NULL;

  // Check if we're using embedded cart
  if (has_embedded) {
    // Mount the executable as PhysFS archive
    if (!fs_mount_embedded_cart(app->argFile)) {
      PHYSFS_deinit();
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not mount embedded cart.");
      return false;
    }
    
    // Load main.wasm from mounted archive
    wasmBytes = fs_load_file("main.wasm", &wasmSize);
    if (wasmSize == 0) {
      PHYSFS_deinit();
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load main.wasm from embedded cart.");
      return false;
    }
  } else {
    // Original external file logic
    cartBytes = fs_load_file_real(app->argFile, &cartSize);

    if (!cartSize) {
      if (cartBytes) {
        free(cartBytes);
      }
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load cart.");
      return false;
    }

    DetectFileType cartType = fs_parse_magic_bytes(*(uint32_t *)cartBytes);

    if (cartType == FILE_TYPE_ZIP) {
      if (!PHYSFS_mountMemory(cartBytes, cartSize, NULL, "cart.zip", NULL, 1)) {
        PHYSFS_deinit();
        free(cartBytes);
        pntr_app_log(PNTR_APP_LOG_ERROR, "Could not mount cart.");
        return false;
      }
      wasmBytes = fs_load_file("main.wasm", &wasmSize);
      if (wasmSize == 0) {
        free(cartBytes);
        pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load main.wasm.");
        return false;
      }
    } else if (cartType == FILE_TYPE_WASM) {
      wasmSize = cartSize;
      wasmBytes = cartBytes;
    } else {
      free(cartBytes);
      pntr_app_log(PNTR_APP_LOG_ERROR, "Only wasm/zip cart-files are supported.");
      return false;
    }
  }

  // give the cart somewhere to save things (save_image, and friends)
  fs_set_write_dir(app->argFile);

  add_image(app->screen);
  add_font(pntr_load_font_default());

  // there is no "default tilemap", so reserve handle 0 as invalid
  cvector_push_back(tilemaps, (cute_tiled_map_t *)NULL);

  bool ret = cart_init(app, wasmBytes, wasmSize);
  // NOTE: Do NOT free cartBytes here! PHYSFS_mountMemory keeps a pointer to it.
  // It will be freed when PHYSFS_deinit() is called at shutdown.
  // if (cartBytes) free(cartBytes);
  free(wasmBytes);
  cart_gc();
  return ret;
}

bool host_update(pntr_app *app) {
  cart_update();
  cart_gc();
  return true;
}

// this maps keys to joystick buttons (for non-libretro)
static pntr_app_gamepad_button cart_map_key(pntr_app_key key) {
  switch (key) {
  case PNTR_APP_KEY_UP:
    return PNTR_APP_GAMEPAD_BUTTON_UP;
  case PNTR_APP_KEY_DOWN:
    return PNTR_APP_GAMEPAD_BUTTON_DOWN;
  case PNTR_APP_KEY_LEFT:
    return PNTR_APP_GAMEPAD_BUTTON_LEFT;
  case PNTR_APP_KEY_RIGHT:
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
  case PNTR_APP_KEY_Q:
    return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
  case PNTR_APP_KEY_W:
    return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
  case PNTR_APP_KEY_Z:
    return PNTR_APP_GAMEPAD_BUTTON_B;
  case PNTR_APP_KEY_X:
    return PNTR_APP_GAMEPAD_BUTTON_A;
  case PNTR_APP_KEY_A:
    return PNTR_APP_GAMEPAD_BUTTON_Y;
  case PNTR_APP_KEY_S:
    return PNTR_APP_GAMEPAD_BUTTON_X;
  case PNTR_APP_KEY_LEFT_SHIFT:
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  case PNTR_APP_KEY_RIGHT_SHIFT:
    return PNTR_APP_GAMEPAD_BUTTON_SELECT;
  case PNTR_APP_KEY_ENTER:
    return PNTR_APP_GAMEPAD_BUTTON_START;
  default:
    return PNTR_APP_GAMEPAD_BUTTON_UNKNOWN;
  }
}

void host_event(pntr_app_event *event) {
  // TODO: it would be cool to handle wheel, DnD, cheat & save events as well
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN) {
    cart_mouseDown(event->mouseButton);
  }
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP) {
    cart_mouseUp(event->mouseButton);
  }
  if (event->type == PNTR_APP_EVENTTYPE_MOUSE_MOVE) {
    cart_mouseMoved(event->mouseX, event->mouseY);
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN) {
    cart_buttonDown(event->gamepadButton, event->gamepad);
  }
  if (event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP) {
    cart_buttonUp(event->gamepadButton, event->gamepad);
  }

  // these are fired & also mapped to button-events
  if (event->type == PNTR_APP_EVENTTYPE_KEY_DOWN) {
    cart_keyDown(event->key);
#ifndef PNTR_APP_LIBRETRO
    pntr_app_gamepad_button b = cart_map_key(event->key);
    if (b != PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
      cart_buttonDown(b, 9999);
    }
#endif
  }
  if (event->type == PNTR_APP_EVENTTYPE_KEY_UP) {
    cart_keyUp(event->key);
#ifndef PNTR_APP_LIBRETRO
    pntr_app_gamepad_button b = cart_map_key(event->key);
    if (b != PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
      cart_buttonUp(b, 9999);
    }
#endif
  }
  cart_gc();
}

// called from carts: these are lil wrappers/helpers to put things in right shape
// return unix-time, in ms
uint64_t null0_current_time() {
#ifdef _WIN32
  struct _timeb tb;
  _ftime64_s(&tb);
  return (uint64_t)tb.time * 1000ULL + (uint64_t)tb.millitm;
#else
  struct timespec ts;
  if (timespec_get(&ts, TIME_UTC) == TIME_UTC) {
    return (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)(ts.tv_nsec / 1000000ULL);
  }
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (uint64_t)tv.tv_sec * 1000ULL + (uint64_t)(tv.tv_usec / 1000ULL);
#endif
}

pntr_vector null0_mouse_position() {
  pntr_vector ret = {
    .x = pntr_app_mouse_x(null0_app),
    .y = pntr_app_mouse_y(null0_app)};
  return ret;
}

pntr_vector null0_measure_image(pntr_image *image) {
  pntr_vector ret = {
    .x = image->width,
    .y = image->height};
  return ret;
}

void null0_draw_rectangle_thick_rounded(pntr_image *dst, int32_t x, int32_t y, int32_t width, int32_t height, int32_t cornerRadius, int32_t thickness, pntr_color color) {
  pntr_draw_rectangle_thick_rounded(dst, x, y, width, height, cornerRadius, cornerRadius, cornerRadius, cornerRadius, thickness, color);
}

