cmake_minimum_required(VERSION 3.18)

project(null0
  DESCRIPTION "null0 game engine"
  HOMEPAGE_URL "https://github.com/konsumer/null0"
  VERSION 0.0.1
  LANGUAGES C
)

# options:

# CARTS=ON/OFF
# HOST_TYPE=OFF/WEB/RAYLIB/SDL/RETRO

set(CMAKE_BUILD_TYPE Release)
cmake_policy(SET CMP0077 NEW)
# cmake_policy(SET CMP0135 NEW)

# everyone wants to make an "uninstall" target
set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS 1)

include(FetchContent)
# set(FETCHCONTENT_QUIET OFF)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")
find_package(null0 REQUIRED)
