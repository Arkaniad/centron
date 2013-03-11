add_executable(centron main.cpp)

add_library(centron-engine centron.cpp)
add_library(centron-log log.cpp)
add_library(centron-graphics graphics.cpp)
add_library(centron-resources resources.cpp)
add_library(centron-util util.cpp)
add_library(centron-timer timer.cpp)
add_library(centron-starfield starfield.cpp)
add_library(centron-drawable drawable.cpp)

target_link_libraries(centron SDL SDL_image SDL_ttf SDL_mixer centron-engine centron-util centron-timer centron-log centron-graphics centron-resources centron-starfield centron-drawable)
