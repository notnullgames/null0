#include "host.h"

// global app-object for pntr_app stuff
pntr_app *null0_app;

bool Init(pntr_app *app) {
  if (app == NULL) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "app not set.");
    return false;
  }

  null0_app = app;

  if (app->argFile == NULL || app->argFile[0] == '\0') {
    pntr_app_log(PNTR_APP_LOG_ERROR, "Usage: null <CART>");
    return false;
  }

  unsigned int cartSize = 0;
  unsigned char *cartBytes = fs_load_file_real(app->argFile, &cartSize);

  if (cartBytes == NULL || cartSize == 0) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load cart.");
    return false;
  }

  if (!PHYSFS_init("/")) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "Could not start filesystem.");
    return false;
  }

  DetectFileType cartType = fs_parse_magic_bytes(*(uint32_t *)cartBytes);

  unsigned int wasmSize = 0;
  unsigned char *wasmBytes = NULL;

  if (cartType == FILE_TYPE_ZIP) {
    if (!PHYSFS_mountMemory(cartBytes, cartSize, NULL, "cart.zip", NULL, 1)) {
      PHYSFS_deinit();
      pntr_unload_memory(cartBytes);
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not mount cart.");
      return false;
    }
    wasmBytes = fs_load_file("main.wasm", &wasmSize);
    if (wasmSize == 0) {
      pntr_unload_memory(cartBytes);
      pntr_app_log(PNTR_APP_LOG_ERROR, "Could not load main.wasm.");
      return false;
    }
  } else if (cartType == FILE_TYPE_WASM) {
    wasmSize = cartSize;
    wasmBytes = cartBytes;
  } else {
    pntr_unload_memory(cartBytes);
    pntr_app_log(PNTR_APP_LOG_ERROR, "Only wasm/zip cart-files are supported.");
    return false;
  }

  // screen is image:0
  add_image(app->screen, "screen");

  // default is font:0
  add_font(pntr_load_font_default(), "default");

  if (!cart_init(wasmBytes, wasmSize)) {
    pntr_unload_memory(cartBytes);
    pntr_app_log(PNTR_APP_LOG_ERROR, "Could not start cart.");
    return 1;
  }
  pntr_unload_memory(cartBytes);
  pntr_unload_memory(wasmBytes);

  return true;
}

bool Update(pntr_app *app, pntr_image *screen) {
  cart_update();
  return true;
}

void Event(pntr_app *app, pntr_app_event *event) {
  cart_event(event);
}

void Close(pntr_app *app) {
  cart_close();
}

pntr_app Main(int argc, char *argv[]) {
#ifdef PNTR_APP_RAYLIB
  SetTraceLogLevel(LOG_WARNING);
#endif
  return (pntr_app){
    .width = 640,
    .height = 480,
    .title = "null0",
    .init = Init,
    .update = Update,
    .event = Event,
    .close = Close,
    .fps = 60};
}
