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

option(NATIVE_RUNTIME "Build native runtime for running carts" TRUE)
option(EXAMPLES_NATIVE "Build native demo executables" TRUE)
option(IWASM_NATIVE "Build native iwasm extension" TRUE)

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
set(PHYSFS_DISABLE_INSTALL TRUE)
set(PHYSFS_BUILD_TEST FALSE)
set(PHYSFS_BUILD_DOCS FALSE)
set(PHYSFS_BUILD_STATIC TRUE)
set(PHYSFS_BUILD_SHARED FALSE)

FetchContent_Declare(
  physfs
  GIT_REPOSITORY https://github.com/icculus/physfs.git
  GIT_TAG main
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(physfs)
include_directories(${physfs_SOURCE_DIR}/src)

set(BUILD_EXAMPLES 0) # don't build the supplied examples
set(BUILD_GAMES    0) # don't build the supplied example games
set(VALIDATE_WORKSPACE_SKIPPED_SDK_FRAMEWORKS "OpenGL")
FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
  GIT_TAG "master"
  GIT_PROGRESS 1
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(raylib)
include_directories(${RAYLIB_SOURCE_DIR})

FetchContent_Declare(
  pntr
  GIT_REPOSITORY https://github.com/robloach/pntr.git
  GIT_TAG master
  GIT_PROGRESS 1
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(pntr)
include_directories(${pntr_SOURCE_DIR})


FetchContent_Declare(
  pntr_app
  GIT_REPOSITORY https://github.com/robloach/pntr_app.git
  GIT_TAG master
  GIT_PROGRESS 1
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
  GIT_PROGRESS 1
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(wamr)
include (${wamr_SOURCE_DIR}/build-scripts/runtime_lib.cmake)

# all other cmake files can import from src/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# shared lib for null0 API (no WAMR)
add_library(null0api src/lib.c src/sfx_gen.c)
target_link_libraries(null0api raylib pntr pntr_app physfs-static)

if (NATIVE_RUNTIME OR IWASM_NATIVE)
  add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})
endif(NATIVE_RUNTIME OR IWASM_NATIVE) 


if (NATIVE_RUNTIME)
  add_executable(${PROJECT_NAME} src/main.c )
  target_link_libraries(${PROJECT_NAME} PUBLIC null0api vmlib)
endif(NATIVE_RUNTIME)

if (IWASM_NATIVE)
  add_library(iwasm_null0 src/main_iwasm.c)
  target_link_libraries(iwasm_null0 PUBLIC null0api vmlib)
endif(IWASM_NATIVE)

if (EXAMPLES_NATIVE)
  add_subdirectory(examples)
endif(EXAMPLES_NATIVE)
