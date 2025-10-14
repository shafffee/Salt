add_library(Core Application.h Application.cpp Core.h EntryPoint.h EntryPoint.cpp Window.h)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Core PRIVATE Logging)
target_link_libraries(Core PRIVATE Renderer)
target_link_libraries(Core PRIVATE ECS)
target_link_libraries(Core PRIVATE Input)
target_link_libraries(Core PRIVATE Utils)
target_link_libraries(Core PRIVATE glad)
target_link_libraries(Core PRIVATE glfw)
target_link_libraries(Core PRIVATE glm)