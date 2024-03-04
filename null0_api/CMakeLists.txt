add_library(null0_api src/main.c src/sfx_gen.c)

# TODO: check for emscripten

if (RAYLIB)
  target_link_libraries(null0_api raylib pntr pntr_app physfs-static)
endif()

if (SDL)
  target_link_libraries(null0_api SDL2::SDL2-static pntr pntr_app physfs-static)
endif()