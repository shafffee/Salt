add_library(EntryPoint EntryPoint.h EntryPoint.cpp)

target_include_directories(EntryPoint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(EntryPoint PUBLIC
    Application Window
)