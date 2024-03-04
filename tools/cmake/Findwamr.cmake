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