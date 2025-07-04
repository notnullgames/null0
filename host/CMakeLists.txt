SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(physfs REQUIRED)
FIND_PACKAGE(pntr REQUIRED)
FIND_PACKAGE(pntr_app REQUIRED)

FILE(GLOB SRC_FILES src/*.c)
add_executable(host ${SRC_FILES})
set_target_properties(host PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
TARGET_LINK_LIBRARIES(host physfs-static pntr pntr_app)

IF (EMSCRIPTEN)
  ADD_COMPILE_DEFINITIONS(PNTR_APP_WEB)
  SET(CMAKE_EXECUTABLE_SUFFIX ".mjs")
  TARGET_LINK_OPTIONS(host PRIVATE -sFORCE_FILESYSTEM -sEXPORTED_RUNTIME_METHODS=FS,HEAPU8 -sASSERTIONS=1 -sASYNCIFY -sALLOW_MEMORY_GROWTH=1)
ELSE()
  FIND_PACKAGE(raylib REQUIRED)
  ADD_COMPILE_DEFINITIONS(PNTR_APP_RAYLIB)
  FIND_PACKAGE(wamr REQUIRED)
  TARGET_LINK_LIBRARIES(host vmlib raylib)
ENDIF()

