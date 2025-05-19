FetchContent_Declare(tsf
  URL https://github.com/schellingb/TinySoundFont/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(tsf)
include_directories(${tsf_SOURCE_DIR})
