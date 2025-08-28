# My libs
add_subdirectory(Logging/)
add_subdirectory(ECS/)
add_subdirectory(Utils/)
add_subdirectory(Renderer/)
add_subdirectory(Core/)
add_subdirectory(Input/)


# Vendor
add_subdirectory(Vendor/glfw-3.4)
find_package(OpenGL REQUIRED)
add_subdirectory(Vendor/glad)
add_subdirectory(Vendor/glm)
add_subdirectory(Vendor/stb_image)
add_subdirectory(Vendor/assimp)

add_library(Salt Salt.h Salt.cpp)

target_include_directories(Salt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Salt PUBLIC 
	OpenGL::GL glfw glad glm::glm-header-only stb_image assimp
	Logging ECS Utils Renderer Core Input)