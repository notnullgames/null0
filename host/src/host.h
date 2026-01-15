#ifndef NULL0_HOST_H_
#define NULL0_HOST_H_


#define CVECTOR_LOGARITHMIC_GROWTH
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_MATH
#define PNTR_ENABLE_VARGS
#define PNTR_ENABLE_TTF
#define PNTR_ENABLE_UTF8
#define PNTR_ENABLE_MATH
#define PNTR_ENABLE_JPEG
#define PNTR_CUTE_PNG
#define PNTR_PIXELFORMAT_RGBA
#define PNTR_LOAD_FILE fs_load_file
#define PNTR_SAVE_FILE fs_save_file

#include "fs.h"
#include "pntr_app.h"
#include "pntr_app_sfx.h"
#include "sam.h"
#include "reciter.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cvector.h"

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
} CartColor;

// These are wrappers around the lifecycle of host
bool host_init(pntr_app *app);
bool host_update(pntr_app *app);
void host_event(pntr_app_event *event);
void host_close();

// These are callbacks in user's cart
bool cart_init(pntr_app *app, unsigned char *wasmBytes, unsigned int wasmSize);
void cart_update();
void cart_buttonDown(pntr_app_gamepad_button button, unsigned int player);
void cart_buttonUp(pntr_app_gamepad_button button, unsigned int player);
void cart_keyDown(pntr_app_key key);
void cart_keyUp(pntr_app_key key);
void cart_mouseDown(pntr_app_mouse_button button);
void cart_mouseUp(pntr_app_mouse_button button);
void cart_mouseMoved(float x, float y);

// Free memory in cart
void cart_free(uint32_t ptr);

// Allocate memory in cart
uint32_t cart_malloc(size_t size);

// Using pointer, copy memory to cart from host
void mem_to_cart(uint32_t dest, void *src, size_t size);

// Using pointer, copy memory from cart to host
void mem_from_cart(void *dest, uint32_t src, size_t size);

// Get the length of a string in cart-memory
size_t cart_strlen(uint32_t ptr);

// copy a string from cart to host
char *copy_string_from_cart(unsigned int cart_pointer);

// Copy a string from host to cart
unsigned int copy_string_to_cart(char *host_pointer);

// Copy a color from cart to host
pntr_color copy_color_from_cart(unsigned int colorPtr);

// Copy a color form host to cart
unsigned int copy_color_to_cart(pntr_color color);

// Returns host-pointer for a cart-pointer
void *copy_memory_from_cart(unsigned int cart_pointer, unsigned int size);

// Returns cart-pointer (unsigned int) for a host-pointer
unsigned int copy_memory_to_cart(void *host_pointer, unsigned int size);

// Add an image to loaded images
unsigned int add_image(pntr_image *image);

// Add a font to loaded fonts
unsigned int add_font(pntr_font *font);

#ifdef EMSCRIPTEN
#include <emscripten.h>

#define HOST_FUNCTION(ret_type, name, params, ...)   \
  EMSCRIPTEN_KEEPALIVE ret_type host_##name params { \
    __VA_ARGS__                                      \
  }
#endif // EMSCRIPTEN

#ifndef EMSCRIPTEN
#include <wasm_export.h>

extern cvector_vector_type(NativeSymbol) null0_native_symbols;

#define EXPAND_PARAMS(...) , ##__VA_ARGS__
#define HOST_FUNCTION(ret_type, name, params, ...)                                       \
  ret_type host_##name(wasm_exec_env_t exec_env EXPAND_PARAMS params){                   \
    __VA_ARGS__};                                                                        \
  static void __attribute__((constructor)) _register_##name() {                          \
    cvector_push_back(null0_native_symbols, ((NativeSymbol){#name, host_##name, NULL})); \
  }
#endif

#endif // NULL0_HOST_H_
