add_library(Window Window.h Window.cpp)

target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Window PRIVATE glad)
target_link_libraries(Window PRIVATE glfw)
target_link_libraries(Window PRIVATE glm)