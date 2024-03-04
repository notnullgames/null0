FetchContent_Declare(
  pntr
  GIT_REPOSITORY https://github.com/robloach/pntr.git
  GIT_TAG master
  GIT_PROGRESS 1
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(pntr)
include_directories(${pntr_SOURCE_DIR})