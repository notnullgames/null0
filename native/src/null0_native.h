// this provides the WAMR host functions for null0 API

#pragma once

#include "null0_api_wamr.h"

bool null0_native_init(char* filename) {
  // setup main null0 runtime
  if (!null0_init(filename)) {
    return false;
  }

  // setup WAMR specific host using /main.wasm
  return null0_init_wamr();
}

void null0_native_event(pntr_app_event* event) {
  null0_event_wamr(event);
}

bool null0_native_update(pntr_app* app, pntr_image* screen) {
  if (!null0_update(app, screen)) {
    return false;
  }
  return null0_update_wamr();
}

void null0_native_unload() {}
