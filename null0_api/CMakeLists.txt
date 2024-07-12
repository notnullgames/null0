add_library(null0_api src/main.c)

if (NULL0_HOST_TYPE_RAYLIB)
  target_link_libraries(null0_api raylib pntr pntr_app physfs-static)
endif()

if (NULL0_HOST_TYPE_SDL)
  target_link_libraries(null0_api ${SDL2_LIBRARIES} pntr pntr_app physfs-static)
endif()

if (NULL0_HOST_TYPE_WEB)
  target_link_libraries(null0_api pntr pntr_app physfs-static)
endif()

if (NULL0_HOST_TYPE_RETRO)
  find_package(libretrocommon QUIET)
  
  add_library(libretro-audio ${libretrocommon_SOURCE_DIR}/audio/audio_mixer.c ${libretrocommon_SOURCE_DIR}/audio/conversion/float_to_s16.c ${libretrocommon_SOURCE_DIR}/memmap/memalign.c)
  target_include_directories(libretro-audio PRIVATE
    ${libretrocommon_SOURCE_DIR}
    ${libretrocommon_SOURCE_DIR}/include
  )

  target_link_libraries(null0_api
    pntr
    pntr_app
    physfs-static
    libretro-audio
  )
  target_include_directories(null0_api PRIVATE
    ${libretrocommon_SOURCE_DIR}/include
  )
endif()