FetchContent_Declare(SDL2Source
  URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.30.5.zip
)

FetchContent_MakeAvailable(SDL2Source)
#include_directories(${SDL2Source_SOURCE_DIR})
