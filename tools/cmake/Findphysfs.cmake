FetchContent_Declare(
  physfs
  GIT_REPOSITORY https://github.com/icculus/physfs.git
  GIT_TAG main
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(physfs)
include_directories(${physfs_SOURCE_DIR}/src)
