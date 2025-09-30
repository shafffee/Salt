add_library(UCSL UCSL.h Transformation.h Model.h UCSL.cpp)

target_include_directories(UCSL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(UCSL PRIVATE
    OpenGL::GL glfw glad glm::glm-header-only stb_image     #vendor
    unit assimp zlib                                        #assimp
    Logging ECS Utils Renderer Core Input                  #my things
)