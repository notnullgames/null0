// setup utils and structures for host
// this will only be included in host.c

#include "host.h"
#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <minwinbase.h>   // FILETIME
  #include <sysinfoapi.h>   // GetSystemTimeAsFileTime
#else
  #include <sys/time.h>
#endif
#include "exists_next_to_executable.h"

static pntr_app *null0_app;

static cvector_vector_type(pntr_image *) images;
static cvector_vector_type(pntr_font *) fonts;
static cvector_vector_type(pntr_sound *) sounds;

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
  uint32_t ret = cart_malloc(size);
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
  uint32_t ret = cart_malloc(sizeof(CartColor));
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
  uint32_t dest = cart_malloc(size);
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

  add_image(app->screen);
  add_font(pntr_load_font_default());

  bool ret = cart_init(app, wasmBytes, wasmSize);
  if (cartBytes) free(cartBytes);
  free(wasmBytes);
  return ret;
}

bool host_update(pntr_app *app) {
  cart_update();
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
}

// called from carts: these are lil wrappers/helpers to put things in right shape
// return unix-time, in ms
uint64_t null0_current_time() {
#ifdef _WIN32
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  ULARGE_INTEGER uli;
  uli.LowPart = ft.dwLowDateTime;
  uli.HighPart = ft.dwHighDateTime;
  // Convert from 100-ns intervals since 1601-01-01 to ms since 1970-01-01
  const uint64_t EPOCH_DIFF_MS = 11644473600000ULL;
  return (uli.QuadPart / 10000ULL) - EPOCH_DIFF_MS;
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  uint64_t milliseconds = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return milliseconds;
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

