cmake_minimum_required(VERSION 3.18)

project(null0
  DESCRIPTION "null0 game engine"
  HOMEPAGE_URL "https://github.com/konsumer/null0"
  VERSION 0.0.1
  LANGUAGES C
)

include(FetchContent)
# set(FETCHCONTENT_QUIET OFF)

set(CMAKE_BUILD_TYPE Release)
cmake_policy(SET CMP0077 NEW)
cmake_policy(SET CMP0135 NEW)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

# CARTS=ON/OFF
# HOST_TYPE=OFF/WEB/RAYLIB/SDL/RETRO

find_package(null0 REQUIRED)
