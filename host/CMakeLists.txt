SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(physfs REQUIRED)
FIND_PACKAGE(pntr REQUIRED)
FIND_PACKAGE(pntr_app REQUIRED)
FIND_PACKAGE(pntr_app_sfx REQUIRED)
FIND_PACKAGE(pntr_tiled REQUIRED)
FIND_PACKAGE(microui REQUIRED)
FIND_PACKAGE(pntr_microui REQUIRED)
FIND_PACKAGE(sam REQUIRED)

FILE(GLOB SRC_FILES src/*.c)
IF (ANDROID)
  # android loads the host as a library (libnull0.so) from a NativeActivity
  add_library(host SHARED ${SRC_FILES})
ELSE()
  add_executable(host ${SRC_FILES})
ENDIF()
set_target_properties(host PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
TARGET_LINK_LIBRARIES(host physfs-static pntr pntr_app microui pntr_microui sam)

IF (EMSCRIPTEN)
  ADD_COMPILE_DEFINITIONS(PNTR_APP_WEB)
  ADD_COMPILE_DEFINITIONS(EMSCRIPTEN)
  SET(CMAKE_EXECUTABLE_SUFFIX ".mjs")
  TARGET_LINK_OPTIONS(host PRIVATE
    -sFORCE_FILESYSTEM
    -sEXPORTED_RUNTIME_METHODS=FS,HEAPU8
    -sASSERTIONS=1
    -sASYNCIFY
    -sALLOW_MEMORY_GROWTH=1
    -sINITIAL_MEMORY=104857600
    -sSINGLE_FILE=1
  )
ELSE()
  FIND_PACKAGE(raylib REQUIRED)
  ADD_COMPILE_DEFINITIONS(PNTR_APP_RAYLIB)
  FIND_PACKAGE(wamr REQUIRED)
  TARGET_LINK_LIBRARIES(host vmlib raylib)
  IF (ANDROID)
    TARGET_LINK_LIBRARIES(host android log)
    # the NativeActivity entry point lives in a static lib, so keep it
    TARGET_LINK_OPTIONS(host PRIVATE -u ANativeActivity_onCreate)
    TARGET_INCLUDE_DIRECTORIES(host PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)
  ENDIF()
ENDIF()

