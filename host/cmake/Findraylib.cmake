FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
)
if(ANDROID)
  set(PLATFORM Android CACHE STRING "" FORCE)
endif()
FetchContent_MakeAvailable(raylib)
