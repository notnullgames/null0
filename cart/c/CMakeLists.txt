# build for carts

cmake_minimum_required (VERSION 3.18)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

set(CMAKE_SYSTEM_NAME WASI)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR wasm32)
set(triple wasm32-wasi)

# When building from source, WASI_SDK_PREFIX represents the generated directory
if(NOT WASI_SDK_PREFIX)
    set(WASI_SDK_PREFIX /opt/wasi-sdk)
endif()

set(CMAKE_C_COMPILER ${WASI_SDK_PREFIX}/bin/clang${WASI_HOST_EXE_SUFFIX})
set(CMAKE_CXX_COMPILER ${WASI_SDK_PREFIX}/bin/clang++${WASI_HOST_EXE_SUFFIX})
set(CMAKE_ASM_COMPILER ${WASI_SDK_PREFIX}/bin/clang${WASI_HOST_EXE_SUFFIX})
set(CMAKE_AR ${WASI_SDK_PREFIX}/bin/llvm-ar${WASI_HOST_EXE_SUFFIX})
set(CMAKE_RANLIB ${WASI_SDK_PREFIX}/bin/llvm-ranlib${WASI_HOST_EXE_SUFFIX})
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_ASM_COMPILER_TARGET ${triple})

# use only sysroot
set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
set(CMAKE_C_LINK_FLAGS "")
set(CMAKE_CXX_LINK_FLAGS "")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

function(BUILDCART name)
  add_executable(${name} ${name}/main.c)
  add_custom_command(
    TARGET ${name}
    POST_BUILD
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/buildcart.sh"
    ARGS "${CMAKE_CURRENT_BINARY_DIR}/${name}.null0" "${CMAKE_CURRENT_BINARY_DIR}/${name}.wasm" "${CMAKE_CURRENT_SOURCE_DIR}/${name}"
  )
endfunction()

BUILDCART("colorbars")
BUILDCART("draw")
BUILDCART("filesystem")
BUILDCART("hello")
BUILDCART("input")
BUILDCART("justlog")
BUILDCART("sound")
BUILDCART("tracker")
BUILDCART("flappybird")
BUILDCART("typesizes")
