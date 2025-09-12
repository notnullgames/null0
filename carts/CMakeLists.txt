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

function(BUILD_CART_NIM name)
  set(CART_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nim/${name}")
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_nim_temp/")
  add_custom_target(cart_nim_${name} ALL
      COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${CART_DIR}" "${CART_TEMP}"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.nim"
      # COMMAND CC=${CMAKE_C_COMPILER} nim c --cc:env -d:release -d:wasi -d:useMalloc --cpu:wasm32 --os:any --passC:"-D_WASI_EMULATED_SIGNAL" --passL:"-lwasi-emulated-signal" --passL:"-Wl,--allow-undefined" -o:${CART_TEMP}/main.wasm --path:${CART_DIR}/../ --import:null0 ${CART_DIR}/main.nim
      COMMAND CC=${CMAKE_C_COMPILER} nim c --threads:off --noMain --cc:env -d:release -d:wasi -d:useMalloc --cpu:wasm32 --os:any --passC:"-D_WASI_EMULATED_SIGNAL" --passL:"-lwasi-emulated-signal" --passL:"-Wl,--allow-undefined" -o:${CART_TEMP}/main.wasm ${CART_DIR}/main.nim
      COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "../${name}_nim.null0" --format=zip .
      # COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
      COMMENT "Creating cart ${name}_nim.null0"
      VERBATIM
    )
    add_dependencies(carts cart_nim_${name})
endfunction()

# this will build a Rust cart, by name
function(BUILD_CART_RUST name)
  set(CART_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rust/examples/${name}")
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_rust_temp/")
  
  # Check if the Rust project directory exists
  if(NOT EXISTS "${CART_DIR}/Cargo.toml")
    message(WARNING "Rust cart '${name}' not found at ${CART_DIR} - skipping")
    return()
  endif()
  
  add_custom_target(cart_rust_${name} ALL
      COMMAND ${CMAKE_COMMAND} -E chdir "${CART_DIR}" cargo build --target wasm32-unknown-unknown --release
      COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
      COMMAND ${CMAKE_COMMAND} -E copy "${CART_DIR}/target/wasm32-unknown-unknown/release/${name}.wasm" "${CART_TEMP}/main.wasm"
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${CART_DIR}" "${CART_TEMP}"
      COMMAND ${CMAKE_COMMAND} -E remove_directory "${CART_TEMP}/src"
      COMMAND ${CMAKE_COMMAND} -E remove_directory "${CART_TEMP}/target"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/Cargo.toml"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/Cargo.lock"
      COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "../${name}_rust.null0" --format=zip .
      COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
      COMMENT "Creating cart ${name}_rust.null0"
      VERBATIM
    )
    add_dependencies(carts cart_rust_${name})
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

# this will build an AssemblyScript cart, by name
function(BUILD_CART_AS name)
  set(CART_DIR "${CMAKE_CURRENT_SOURCE_DIR}/as/${name}")
  set(CART_TEMP "${CMAKE_CURRENT_BINARY_DIR}/${name}_as_temp/")
  
  # Check if the AssemblyScript project directory exists
  if(NOT EXISTS "${CART_DIR}/main.ts")
    message(WARNING "AssemblyScript cart '${name}' not found at ${CART_DIR} - skipping")
    return()
  endif()
  
  add_custom_target(cart_as_${name} ALL
      # Build the AssemblyScript project first
      COMMAND ${CMAKE_COMMAND} -E chdir "${CART_DIR}" npx asc main.ts --target release --exportRuntime --bindings esm --use abort= -o main.wasm
      
      # Create temp directory
      COMMAND ${CMAKE_COMMAND} -E make_directory "${CART_TEMP}"
      
      # Copy the compiled WASM file as main.wasm
      COMMAND ${CMAKE_COMMAND} -E copy "${CART_DIR}/main.wasm" "${CART_TEMP}/main.wasm"
      
      # Copy any non-source files (assets, etc.)
      COMMAND ${CMAKE_COMMAND} -E copy_directory "${CART_DIR}" "${CART_TEMP}"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/*.ts"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/package.json"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/asconfig.json"
      COMMAND ${CMAKE_COMMAND} -E rm -f "${CART_TEMP}/build.sh"
      
      # Create the cart package
      COMMAND ${CMAKE_COMMAND} -E chdir "${CART_TEMP}" ${CMAKE_COMMAND} -E tar "cf" "../${name}_as.null0" --format=zip .
      COMMAND ${CMAKE_COMMAND} -E rm -rf "${CART_TEMP}"
      
      COMMENT "Creating cart ${name}_as.null0"
      VERBATIM
    )
    add_dependencies(carts cart_as_${name})
endfunction()

BUILD_CART_C("colorbars")
BUILD_CART_C("example")
BUILD_CART_C("gradient")
BUILD_CART_C("input")
BUILD_CART_C("wasi_demo")
BUILD_CART_C("speak")
BUILD_CART_C("sfx")

BUILD_CART_JS("demo")
BUILD_CART_JS("input")

BUILD_CART_NELUA("basic")
BUILD_CART_NELUA("colorbars")
BUILD_CART_NIM("simple")

BUILD_CART_RUST("simple")

BUILD_CART_AS("simple")

