cmake_minimum_required(VERSION 2.6)
project(centron)
set (centron-engine_VERSION_MAJOR 0)
set (centron-engine_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/src/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")
find_package(SDL)
set(CMAKE_CXX_FLAGS "-O2 -Wall -ggdb")

add_subdirectory(src)


