FetchContent_Declare(
  pntr_app
  GIT_REPOSITORY https://github.com/robloach/pntr_app.git
  GIT_TAG master
  GIT_PROGRESS 1
  GIT_SHALLOW 1
)
FetchContent_MakeAvailable(pntr_app)
include_directories(${pntr_app_SOURCE_DIR}/include)