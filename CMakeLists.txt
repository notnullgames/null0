cmake_minimum_required(VERSION 3.18)

project(null0
  DESCRIPTION "null0 game engine"
  HOMEPAGE_URL "https://github.com/konsumer/null0"
  VERSION 0.0.1
  LANGUAGES C
)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

if(POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
endif()

if(POLICY CMP0169)
  cmake_policy(SET CMP0169 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0169 NEW)
endif()

# enable colors for ninja
set(CMAKE_COLOR_DIAGNOSTICS ON)

# everyone wants to make an "uninstall" target
set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS 1)

include(FetchContent)
# set(FETCHCONTENT_QUIET OFF)

add_subdirectory(host)
add_subdirectory(carts)