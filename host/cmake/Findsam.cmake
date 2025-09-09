# Fetch SAM (Software Automatic Mouth) TTS library
FetchContent_Declare(sam
  URL https://github.com/vidarh/SAM/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(sam)

include_directories(${sam_SOURCE_DIR}/src)

# Create SAM library target - include all needed files but handle conflicts
add_library(sam STATIC
  ${sam_SOURCE_DIR}/src/createtransitions.c
  ${sam_SOURCE_DIR}/src/debug.c
  ${sam_SOURCE_DIR}/src/processframes.c
  ${sam_SOURCE_DIR}/src/reciter.c
  ${sam_SOURCE_DIR}/src/render.c
  ${sam_SOURCE_DIR}/src/sam.c
)

target_compile_definitions(sam PRIVATE
    Init=SAM_Init
    Render=SAM_Render
    debug=sam_debug_var
)

# Add a source file that defines the debug variable
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/sam_debug.c "int sam_debug_var = 0;\n")
target_sources(sam PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/sam_debug.c)