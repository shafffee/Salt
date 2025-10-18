add_library(Window Window.h Window.cpp)

target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Window PUBLIC glad)
target_link_libraries(Window PUBLIC glfw)