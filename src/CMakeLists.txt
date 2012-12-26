add_executable(centron centron.cpp  centron_OnCleanup.cpp  centron_OnEvent.cpp  centron_OnInit.cpp  centron_OnLoop.cpp  centron_OnRender.cpp)
target_link_libraries(centron SDL)
