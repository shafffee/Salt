add_library(Renderer Camera.h Material.h Material.cpp Renderer.h Renderer.cpp Renderer_params.h Color.h
	Mesh.h Mesh.cpp Model.h Model.cpp Texture.h Texture.cpp Sprite.h Sprite.cpp Text.h Text.cpp Font.h Font.cpp
	Essentials/Essentials.h Essentials/IndexBuffer.h Essentials/Shader.h Essentials/Vertex.h Essentials/VertexArray.h Essentials/VertexBuffer.h
)

target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Essentials)
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Vendor/assimp/include/)
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Vendor/freetype-2.14.1/include/)


target_link_libraries(Renderer PUBLIC Logging)
target_link_libraries(Renderer PUBLIC Utils)
target_link_libraries(Renderer PUBLIC Input)
target_link_libraries(Renderer PUBLIC glad)
target_link_libraries(Renderer PUBLIC glfw)
target_link_libraries(Renderer PUBLIC glm)
target_link_libraries(Renderer PUBLIC Core)
target_link_libraries(Renderer PUBLIC stb_image)
target_link_libraries(Renderer PUBLIC freetype)