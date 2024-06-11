add_executable(${PROJECT_NAME} src/main.c )

if(NOT EMSCRIPTEN)
  add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})
  target_link_libraries(${PROJECT_NAME} null0_api vmlib)
endif()

if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".mjs")
  target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=@${CMAKE_CURRENT_SOURCE_DIR}/functions.txt)
  target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_RUNTIME_METHODS=FS)
  target_link_options(${PROJECT_NAME} PRIVATE -sFORCE_FILESYSTEM)
endif()

target_link_libraries(${PROJECT_NAME} null0_api)
