FetchContent_Declare(microui
  URL https://github.com/rxi/microui/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(microui)

if (NOT TARGET microui)
  add_library(microui STATIC ${microui_SOURCE_DIR}/src/microui.c)
  target_include_directories(microui PUBLIC ${microui_SOURCE_DIR}/src)
endif()
