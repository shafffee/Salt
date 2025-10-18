add_library(Application Application.h Application.cpp Clock.h)

target_include_directories(Application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Application PUBLIC
    Input Window ECS Logging Renderer
)