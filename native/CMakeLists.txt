add_executable(${PROJECT_NAME} src/main.c )
add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})

target_link_libraries(${PROJECT_NAME} null0_api vmlib)