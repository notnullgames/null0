cmake_minimum_required(VERSION 3.18)

project(null0
  DESCRIPTION "null0 game engine"
  HOMEPAGE_URL "https://github.com/konsumer/null0"
  VERSION 0.0.1
  LANGUAGES C
)

include(FetchContent)
set(FETCHCONTENT_QUIET 0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

# These options will change what is built, and what libraries are used

if(EMSCRIPTEN)
  option(CARTS "Build Demo Null0 Carts" FALSE)
else()
  option(SDL "Use SDL in hosts (Choose SDL or RAYLIB)" TRUE)
  option(RAYLIB "Use Raylib in hosts (Choose SDL or RAYLIB)" FALSE)
  option(CARTS "Build Demo Null0 Carts" TRUE)
endif()

option(TESTS "Unit tests" FALSE)
option(LIBRETRO "Build Null0 libretro Host" FALSE)
option(HOST "Build Null0 Host" TRUE)

# this is used to output options
macro(message_bool _NAME _VALUE)
  if(${_VALUE})
    message(STATUS "  ${_NAME}: enabled")
  else()
    message(STATUS "  ${_NAME}: disabled")
  endif()
endmacro()

if (LIBRETRO)
  set(PNTR_APP_LIBRETRO ON)
endif()

# wamr is used in libretro & native runtimes
if ((HOST OR LIBRETRO) AND NOT EMSCRIPTEN)
  find_package(wamr REQUIRED)
endif()

# check some invalid combos

if(EMSCRIPTEN AND LIBRETRO)
  message(FATAL_ERROR "Do not build libretro core in emscripten. It will not turn out right.")
endif()

if (NOT EMSCRIPTEN AND (NOT (SDL OR RAYLIB)))
  message(FATAL_ERROR "You must set SDL or RAYLIB.")
endif()

if (SDL AND RAYLIB)
  message(FATAL_ERROR "You must set SDL or RAYLIB, not both.")
endif()

# shared defines for the API
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/null0_api/src)

# core API will be built with any runtime
if (LIBRETRO OR HOST OR TESTS)
  if (SDL)

    # SDL
    set(SDL_SHARED FALSE)
    set(SDL2_SHARED FALSE)
    set(SDL_STATIC TRUE)
    set(SDL_TEST FALSE)
    set(SDL_TESTS FALSE)
    set(INTERFACE_SDL2_SHARED false)
    set(SDL2_DISABLE_UNINSTALL TRUE)
    set(SDL2_DISABLE_INSTALL TRUE)
    set(SDL_INSTALL_TESTS FALSE)
    set(SDL2_LIBRARIES SDL2::SDL2-static)
    #set(SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2main)

    # SDL_mixer
    set(SDL2MIXER_VORBIS STB)
    set(SDL2MIXER_INSTALL OFF)
    set(SDL2MIXER_DEPS_SHARED OFF)
    set(SDL2MIXER_VENDORED OFF)
    set(SDL2MIXER_SAMPLES OFF)
    set(SDL2MIXER_CMD OFF)
    set(SDL2MIXER_FLAC OFF)
    set(SDL2MIXER_MOD OFF)
    set(SDL2MIXER_MP3 OFF)
    set(SDL2MIXER_MIDI_NATIVE OFF)
    set(SDL2MIXER_OPUS OFF)
    set(SDL2MIXER_OPUS_SHARED OFF)
    set(SDL2MIXER_MIDI_FLUIDSYNTH OFF)
    set(SDL2MIXER_MP3_MPG123 OFF)
    set(SDL2MIXER_MP3_DRMP3 OFF)
    set(SDL2MIXER_MOD_XMP OFF)
    set(SDL2MIXER_MOD_MODPLUG OFF)
    set(SDL2MIXER_FLAC_DRFLAC OFF)
    set(SDL2MIXER_FLAC_LIBFLAC OFF)
    set(SDL2MIXER_VORBIS_VORBISFILE ON)
    set(SDL2MIXER_WAVPACK OFF)
    set(SDL2MIXER_SAMPLES_INSTALL OFF)
    set(SDL2MIXER_BUILD_SHARED_LIBS OFF)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    add_definitions(-DPNTR_APP_SDL -DPNTR_PIXELFORMAT_ARGB)
    include_directories(${SDL2_INCLUDE_DIR}/..)
  endif()

  if (RAYLIB)
    find_package(raylib REQUIRED)
    add_definitions(-DPNTR_APP_RAYLIB -DPNTR_PIXELFORMAT_RGBA)
  endif()

  if (EMSCRIPTEN)
    add_definitions(-DPNTR_APP_WEB -DPNTR_PIXELFORMAT_RGBA)
  endif()

  set(PHYSFS_ARCHIVE_7Z FALSE)
  set(PHYSFS_ARCHIVE_GRP FALSE)
  set(PHYSFS_ARCHIVE_HOG FALSE)
  set(PHYSFS_ARCHIVE_ISO9660 FALSE)
  set(PHYSFS_ARCHIVE_MVL FALSE)
  set(PHYSFS_ARCHIVE_QPAK FALSE)
  set(PHYSFS_ARCHIVE_SLB FALSE)
  set(PHYSFS_ARCHIVE_VDF FALSE)
  set(PHYSFS_ARCHIVE_CSM FALSE)
  set(PHYSFS_ARCHIVE_WAD FALSE)
  set(PHYSFS_BUILD_STATIC TRUE)
  set(PHYSFS_BUILD_SHARED FALSE)
  set(PHYSFS_BUILD_TEST FALSE)
  set(PHYSFS_BUILD_DOCS FALSE)
  set(PHYSFS_DISABLE_INSTALL TRUE)
  set(PHYSFS_TARGETNAME_UNINSTALL "phys-uninstall")

  find_package(pntr REQUIRED)
  find_package(pntr_app REQUIRED)
  find_package(physfs REQUIRED)
  add_subdirectory(null0_api)
endif()

if (HOST)
  add_subdirectory(host)
endif()

if (CARTS)
  add_subdirectory(cart/c)
endif()

if (TESTS)
  add_subdirectory(test)
endif()


message(STATUS "Null0 will built with the following options:")
message_bool("Web host" HOST AND EMSCRIPTEN)
message_bool("Native host" HOST AND (NOT EMSCRIPTEN))
message_bool("Libretro host" LIBRETRO)
message_bool("Example carts" CARTS)
message_bool("Unit tests" TESTS)
message_bool("Hosts use Raylib" RAYLIB)
message_bool("Hosts use SDL" SDL)
