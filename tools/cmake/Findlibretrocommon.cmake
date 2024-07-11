# libretro-common
include(FetchContent)
FetchContent_Declare(
    libretrocommon
    GIT_REPOSITORY https://github.com/libretro/libretro-common.git
    GIT_TAG b274f73
    GIT_SHALLOW 1
)
FetchContent_MakeAvailable(libretrocommon)