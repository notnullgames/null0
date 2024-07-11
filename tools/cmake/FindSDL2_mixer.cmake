FetchContent_Declare(SDL2MixerSource
  URL https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.8.0.zip
)

FetchContent_MakeAvailable(SDL2MixerSource)
#include_directories(${sdl2mixersource_SOURCE_DIR}/include)
