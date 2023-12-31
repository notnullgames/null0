cmake_minimum_required(VERSION 3.18)
project(null0-native-examples
  DESCRIPTION "null0 game engine native examples"
  HOMEPAGE_URL "https://github.com/konsumer/null0"
  VERSION 0.0.1
  LANGUAGES C
)

add_executable(demo-justlog justlog.c)
target_link_libraries(demo-justlog PUBLIC null0api)

add_executable(demo-filesystem filesystem.c)
target_link_libraries(demo-filesystem PUBLIC null0api)

add_executable(demo-draw draw.c)
target_link_libraries(demo-draw PUBLIC null0api)