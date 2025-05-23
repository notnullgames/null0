// this is the API for each null0 host to implement

#ifndef NULL0_HOST_H_
#define NULL0_HOST_H_

#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_VARGS
#define PNTR_ENABLE_TTF
#define PNTR_ENABLE_UTF8
#define PNTR_ENABLE_MATH
#define PNTR_ENABLE_JPEG
#define PNTR_PIXELFORMAT_RGBA
#define PNTR_LOAD_FILE fs_load_file
#define PNTR_SAVE_FILE fs_save_file

#include "fs.h"
#include "pntr_app.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"

// these are specifric to each host-type
#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
#include <wasm_export.h>
#endif

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
} CartColor;

/// these are specific to each host (wamr/emscripten)

// Initialize a cart
bool cart_init(unsigned char *wasmBytes, unsigned int wasmSize);

// Update a cart
bool cart_update();

// Close a cart
bool cart_close();

// process an event (keyboard/mouse/joystick)
void cart_event(pntr_app_event *event);

// returns cart-pointer (unsigned int) for a host-pointer
unsigned int copy_memory_to_cart(void *host_pointer, unsigned int size);

// returns host-pointer for a cart-pointer
void *copy_memory_from_cart(unsigned int cart_pointer, unsigned int size);

// get length of string in cart
unsigned int cart_strlen(unsigned int cart_pointer);

/// these are derived (implemented in host.c)

// copy a string from cart to host, returns host-pointer
char *copy_string_from_cart(unsigned int cart_pointer);

// copy a string from host to cart, returns cart-pointer
unsigned int copy_string_to_cart(char *host_pointer);

// get an image
pntr_image *get_image(unsigned int id);

// set a cart image from host
unsigned int add_image(pntr_image *image, const char* name);

// set a cart font from host
unsigned int add_font(pntr_font *font, const char* name);

// get a color from cart
pntr_color copy_color_from_cart(unsigned int colorPtr);

// set cart-color
unsigned intcopy_color_to_cart(pntr_color color);

// cart input-specific callbacks
void cart_buttonDown(pntr_app_gamepad_button button, unsigned int player);
void cart_buttonUp(pntr_app_gamepad_button button, unsigned int player);
void cart_keyDown(pntr_app_key key);
void cart_keyUp(pntr_app_key key);
void cart_mouseDown(pntr_app_mouse_button button);
void cart_mouseUp(pntr_app_mouse_button button);
void cart_mouseMoved(float x, float y);

/// host-specific macro for each host-type

#ifdef EMSCRIPTEN
#define HOST_FUNCTION(ret_type, name, params, ...)   \
  EMSCRIPTEN_KEEPALIVE ret_type host_##name params { \
    __VA_ARGS__                                      \
  }
#endif // EMSCRIPTEN

#ifndef EMSCRIPTEN
extern cvector_vector_type(NativeSymbol) null0_native_symbols;

#define EXPAND_PARAMS(...) , ##__VA_ARGS__
#define HOST_FUNCTION(ret_type, name, params, ...)                                       \
  ret_type host_##name(wasm_exec_env_t exec_env EXPAND_PARAMS params){                   \
    __VA_ARGS__};                                                                        \
  static void __attribute__((constructor)) _register_##name() {                          \
    if (null0_native_symbols == NULL) {                                                  \
      null0_native_symbols = NULL; /* Initialize if needed */                            \
    }                                                                                    \
    cvector_push_back(null0_native_symbols, ((NativeSymbol){#name, host_##name, NULL})); \
  }
#endif

#endif // NULL0_HOST_H_
