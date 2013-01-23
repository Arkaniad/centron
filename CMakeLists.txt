#file(REMOVE_RECURSE bin/*)
cmake_minimum_required(VERSION 2.6)
project(centron-engine)
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

#file(INSTALL src/centron PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION bin/)
#file(INSTALL src/res/button.png DESTINATION bin/res/)
#file(INSTALL src/res/background.bmp DESTINATION bin/res/)
