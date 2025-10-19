add_library(Core Core.h Core.cpp)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# My libs
add_subdirectory(Application/)
add_subdirectory(EntryPoint/)
add_subdirectory(Ticks/)
add_subdirectory(Window/)

target_link_libraries(Core PUBLIC
    Application EntryPoint Ticks Window                  #core things
)