FetchContent_Declare(physfs
  URL https://github.com/icculus/physfs/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(physfs)

FetchContent_MakeAvailable(physfs)
include_directories(${physfs_SOURCE_DIR}/src)
