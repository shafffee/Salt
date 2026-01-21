add_library(Console Console.h Console.cpp ConsoleTools/ConsoleEntity.cpp ConsoleTools/ConsoleEntity.h ConsoleTools/FPS_Counter.h)

target_include_directories(Console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleTools)

target_link_libraries(Console PRIVATE
    OpenGL::GL glfw glad glm::glm-header-only stb_image     #vendor
    unit assimp zlib                                        #assimp
    Logging ECS Utils Renderer Core Input                  #my things
)
target_link_libraries(Console PRIVATE UCSL)
