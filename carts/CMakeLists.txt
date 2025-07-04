# build for carts
# essentially, anything that uses C should default to all wasi-sdk stuff

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
set(CMAKE_C_LINK_FLAGS "-Wl,--initial-memory=655360")
set(CMAKE_CXX_LINK_FLAGS "")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

# anything that adds itself as dependency to this can be built with target=carts
add_custom_target(carts)

# this is the QuickJS runtime for javascript carts
add_executable(cart-js c/js/main.c c/js/libunicode.c c/js/cutils.c c/js/libbf.c c/js/libregexp.c c/js/quickjs.c c/js/quickjs-libc.c c/js/qjscalc.c)
target_compile_definitions(cart-js PRIVATE
    CONFIG_VERSION="wasi"
    _WASI_EMULATED_SIGNAL
    CONFIG_BIGNUM=y
)
target_include_directories(cart-js PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/c")

# this will build a C cart, by name
function (BUILD_CART_C name)
  set(CART_DIR "${CMAKE_CURRENT_SOURCE_DIR}/c/${name}")
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_c_temp/")
  add_executable(${name}_c_wasm "${CART_DIR}/main.c")
  target_include_directories(${name}_c_wasm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/c")
  add_custom_target(cart_c_${name} ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${name}_c_wasm>" "${CART_TEMP}/main.wasm"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CART_DIR}" "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.c"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.h"
    COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "../${name}_c.null0" --format=zip .
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
    DEPENDS ${name}_c_wasm
    COMMENT "Creating cart ${name}_c.null0"
  )
  add_dependencies(carts cart_c_${name})
endfunction()

# this will build a JS cart, by name
function (BUILD_CART_JS name)
  set(CART_DIR "${CMAKE_CURRENT_SOURCE_DIR}/js/${name}")
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_js_temp/")
  add_custom_target(cart_js_${name} ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:cart-js>" "${CART_TEMP}/main.wasm"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CART_DIR}" "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "../${name}_js.null0" --format=zip .
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
    DEPENDS cart-js 
    COMMENT "Creating cart ${name}_js.null0"
  )
  add_dependencies(carts cart_js_${name})
endfunction()

# this will build a Nelua cart, by name
set(NELUA_CFLAGS "-I ${CMAKE_CURRENT_SOURCE_DIR}/c")
function (BUILD_CART_NELUA name)
  set(CART_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nelua/${name}")
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_nelua_temp/")
  add_custom_target(cart_nelua_${name} ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CART_DIR}" "${CART_TEMP}"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.nelua"
    COMMAND nelua --cache-dir "${CART_TEMP}/nelua_cache" --cflags=${NELUA_CFLAGS} -L "${CMAKE_CURRENT_SOURCE_DIR}/nelua" "${CMAKE_CURRENT_SOURCE_DIR}/nelua/${name}/main.nelua" -r --cc "${CMAKE_C_COMPILER}" -o "${CART_TEMP}/main.wasm"
    COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "../${name}_nelua.null0" --format=zip .
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
    COMMENT "Creating cart ${name}_nelua.null0"
    VERBATIM
  )
  add_dependencies(carts cart_nelua_${name})
endfunction()

BUILD_CART_C("colorbars")
BUILD_CART_C("example")
BUILD_CART_C("gradient")
BUILD_CART_C("input")
BUILD_CART_C("issue6")
BUILD_CART_C("wasi_demo")

BUILD_CART_JS("demo")
BUILD_CART_JS("input")
BUILD_CART_JS("issue6")

BUILD_CART_NELUA("basic")
BUILD_CART_NELUA("colorbars")
