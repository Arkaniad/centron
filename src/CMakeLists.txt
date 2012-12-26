add_library(centron centron.cpp)
add_executable(test_engine test.cpp)
target_link_libraries(test_engine centron)
