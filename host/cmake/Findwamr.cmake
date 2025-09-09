string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} WAMR_BUILD_PLATFORM)
set (WAMR_BUILD_INTERP 1)
set (WAMR_BUILD_DEBUG_INTERP 0)
set (WAMR_BUILD_FAST_INTERP 1)
set (WAMR_BUILD_AOT 0)
set (WAMR_BUILD_LIBC_BUILTIN 0)
set (WAMR_BUILD_LIBC_WASI 0)
if(NOT DEFINED WAMR_BUILD_SIMD)
  set (WAMR_BUILD_SIMD 1)
endif()
set (WAMR_BUILD_REF_TYPES 1)

FetchContent_Declare(wamr
  URL https://github.com/bytecodealliance/wasm-micro-runtime/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(wamr)
include (${wamr_SOURCE_DIR}/build-scripts/runtime_lib.cmake)
