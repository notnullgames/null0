FetchContent_Declare(pntr_app_sfx
  URL https://github.com/konsumer/pntr_app_sfx/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(pntr_app_sfx)
include_directories(${pntr_app_sfx_SOURCE_DIR})
