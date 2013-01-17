add_executable(centron centron.cpp)
add_subdirectory(lib)
target_link_libraries(centron SDL SDL_image SDL_ttf SDL_mixer centron-log)