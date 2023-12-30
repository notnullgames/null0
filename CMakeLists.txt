cmake_minimum_required(VERSION 3.18)
project(null0
  DESCRIPTION "null0 game engine"
  HOMEPAGE_URL "https://github.com/konsumer/null0"
  VERSION 0.0.1
  LANGUAGES C
)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CFLAGS "${CMAKE_CFLAGS} -Wno-deprecated-opengl")

option(NATIVE_RUNTIME "Build native runtime for running carts" TRUE)
option(EXAMPLES_NATIVE "Build native demo executables" TRUE)


set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
  GIT_TAG "master"
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(raylib)
include_directories(${RAYLIB_SOURCE_DIR})


FetchContent_Declare(
  pntr
  GIT_REPOSITORY https://github.com/robloach/pntr.git
  GIT_TAG master
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(pntr)
include_directories(${pntr_SOURCE_DIR})


FetchContent_Declare(
  pntr_app
  GIT_REPOSITORY https://github.com/robloach/pntr_app.git
  GIT_TAG master
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(pntr_app)
include_directories(${pntr_app_SOURCE_DIR}/include)


string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} WAMR_BUILD_PLATFORM)
set (WAMR_BUILD_INTERP 1)
set (WAMR_BUILD_FAST_INTERP 0)
set (WAMR_BUILD_AOT 0)
set (WAMR_BUILD_LIBC_BUILTIN 1)
set (WAMR_BUILD_LIBC_WASI 1)
set (WAMR_BUILD_SIMD 1)
FetchContent_Declare(
  wamr
  GIT_REPOSITORY https://github.com/bytecodealliance/wasm-micro-runtime.git
  GIT_TAG main
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(wamr)
include (${wamr_SOURCE_DIR}/build-scripts/runtime_lib.cmake)

# all other cmake files can import from src/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# shared lib for null0 API (no WAMR)
add_library(null0api src/lib.c src/sfx_gen.c src/ini.c)
target_link_libraries(null0api raylib pntr pntr_app)

if (NATIVE_RUNTIME)
  add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})
  add_executable(${PROJECT_NAME} src/main.c )
  target_link_libraries(${PROJECT_NAME} PUBLIC null0api vmlib)
endif(NATIVE_RUNTIME)

if (EXAMPLES_NATIVE)
  add_subdirectory(examples/c)
endif(EXAMPLES_NATIVE)

