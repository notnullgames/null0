FetchContent_Declare(physfs
  # PhysFS fork with libretro VFS support
  # https://github.com/icculus/physfs/pull/83
  URL https://github.com/RobLoach/physfs/archive/refs/heads/libretro-support.zip
)
FetchContent_MakeAvailable(physfs)

FetchContent_MakeAvailable(physfs)
include_directories(${physfs_SOURCE_DIR}/src)
