add_executable(test_colors test_colors.c)
add_executable(test_sound test_sound.c)

if (RAYLIB)
  target_link_libraries(test_colors raylib pntr pntr_app)
  target_link_libraries(test_sound raylib pntr pntr_app)
endif()

if (SDL)
  target_link_libraries(test_colors ${SDL2_LIBRARIES} pntr pntr_app)
  target_link_libraries(test_sound ${SDL2_LIBRARIES} pntr pntr_app)
endif()



