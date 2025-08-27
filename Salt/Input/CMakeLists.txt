add_library(Input Input.h Input.cpp Keycodes.h Mousecodes.h)

target_include_directories(Input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Input PRIVATE Logging)
target_link_libraries(Input PRIVATE glfw)
target_link_libraries(Input PRIVATE Core)
target_link_libraries(Input PRIVATE glad)