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

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

# These options will change what is built, and what libraries are used

option(LIBRETRO "Build Null0 libretro Host" FALSE)
option(SDL "Use SDL in hosts (Choose SDL or RAYLIB)" TRUE)
option(RAYLIB "Use Raylib in hosts (Choose SDL or RAYLIB)" FALSE)
option(CARTS "Build Demo Null0 Carts" TRUE)
option(TESTS "Unit tests" TRUE)


# this is used to output options
macro(message_bool _NAME _VALUE)
  if(${_VALUE})
    message(STATUS "  ${_NAME}: enabled")
  else()
    message(STATUS "  ${_NAME}: disabled")
  endif()
endmacro()

# set some defaults for if this is running in emcmake or cmake
if (EMSCRIPTEN)
  option(NATIVE "Build Null0 NATIVE Host" FALSE)
else()
  option(NATIVE "Build Null0 NATIVE Host" TRUE)
endif()

if (LIBRETRO)
  set(PNTR_APP_LIBRETRO ON)
endif()

if (SDL)
  find_package(SDL2 REQUIRED)
  include_directories(${SDL2_INCLUDE_DIRS})
  add_definitions(-DPNTR_APP_SDL)
endif()

if (RAYLIB)
  find_package(raylib REQUIRED)
  add_definitions(-DPNTR_APP_RAYLIB)
endif()

# wamr is used in libretro & native runtimes
if (NATIVE OR LIBRETRO)
  find_package(wamr REQUIRED)
endif()

# check some invalid combos

if(EMSCRIPTEN)
  if (LIBRETRO)
    message(FATAL_ERROR "Do not build libretro core in emscripten. It will not turn out right.")
  endif()
  if (NATIVE)
    message(FATAL_ERROR "Do not build web runtime in emscripten. A web host will be built for you, if you disable NATIVE.")
  endif()
endif()

if (NOT (SDL OR RAYLIB))
  message(FATAL_ERROR "You must set SDL or RAYLIB.")
endif()

if (SDL AND RAYLIB)
  message(FATAL_ERROR "You must set SDL or RAYLIB, not both.")
endif()

# shared defines for the API
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/null0_api/src)

# core API will be built with any runtime
if (EMSCRIPTEN OR LIBRETRO OR NATIVE OR TESTS)
  find_package(pntr REQUIRED)
  find_package(pntr_app REQUIRED)
  find_package(physfs REQUIRED)
  add_subdirectory(null0_api)
endif()

if (EMSCRIPTEN)
  add_subdirectory(web)
endif()

if (NATIVE)
  add_subdirectory(native)
endif()

if (CARTS)
  add_subdirectory(cart/c)
endif()

if (TESTS)
  add_subdirectory(test)
endif()


message(STATUS "Null0 will built with the following options:")
message_bool("Web host" EMSCRIPTEN)
message_bool("Native host" NATIVE)
message_bool("Libretro host" LIBRETRO)
message_bool("Example carts" CARTS)
message_bool("Unit tests" TESTS)
message_bool("Hosts use Raylib" RAYLIB)
message_bool("Hosts use SDL" SDL)

