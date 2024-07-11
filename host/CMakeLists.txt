if (NULL0_HOST_TYPE_RETRO)
  add_library(${PROJECT_NAME}_libretro src/main.c)
  find_package(libretrocommon QUIET)
  target_link_libraries(${PROJECT_NAME}_libretro
    null0_api
    vmlib
    physfs-static
  )

  target_include_directories(${PROJECT_NAME}_libretro PRIVATE
    ${libretrocommon_SOURCE_DIR}/include
  )
else()
  if (NULL0_HOST_TYPE_SDL OR NULL0_HOST_TYPE_RAYLIB OR NULL0_HOST_TYPE_WEB)
    add_executable(${PROJECT_NAME} src/main.c)
      if(NULL0_HOST_TYPE_WEB)
        set(CMAKE_EXECUTABLE_SUFFIX ".mjs")
        target_link_options(${PROJECT_NAME} PRIVATE -sFORCE_FILESYSTEM -sEXPORTED_RUNTIME_METHODS=FS,stringToUTF8 -sEXPORTED_FUNCTIONS=@${CMAKE_CURRENT_SOURCE_DIR}/functions.txt)
        target_link_libraries(${PROJECT_NAME} null0_api)
      else()
        target_link_libraries(${PROJECT_NAME} null0_api vmlib)
      endif()
  endif()
endif()
