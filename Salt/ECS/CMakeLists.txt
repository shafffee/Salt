add_library(ECS Entity.h Component.h System.h ECS_params.h ECS.h System.cpp)

target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ECS PRIVATE Logging)