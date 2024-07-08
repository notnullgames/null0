add_library(null0_api src/main.c src/sfx_gen.c)

# TODO: check for emscripten

if (RAYLIB)
  target_link_libraries(null0_api raylib pntr pntr_app physfs-static)
endif()

if (SDL)
  message("SDL libs: ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}")
  target_link_libraries(null0_api ${SDL2_LIBRARIES} pntr pntr_app physfs-static)
endif()

if (EMSCRIPTEN)
  target_link_libraries(null0_api pntr pntr_app physfs-static)
endif()