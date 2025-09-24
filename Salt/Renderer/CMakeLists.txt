add_library(Renderer Camera.h Material.h Material.cpp Renderer.h Renderer.cpp Renderer_params.h Color.h
	Mesh.h Mesh.cpp Model.h Model.cpp Texture.h Texture.cpp 
	Essentials/Essentials.h Essentials/IndexBuffer.h Essentials/Shader.h Essentials/Vertex.h Essentials/VertexArray.h Essentials/VertexBuffer.h
)

target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Essentials)
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Vendor/assimp/include/)


target_link_libraries(Renderer PRIVATE Logging)
target_link_libraries(Renderer PRIVATE Utils)
target_link_libraries(Renderer PRIVATE Input)
target_link_libraries(Renderer PRIVATE glad)
target_link_libraries(Renderer PRIVATE glfw)
target_link_libraries(Renderer PRIVATE glm)
target_link_libraries(Renderer PRIVATE Core)
target_link_libraries(Renderer PRIVATE stb_image)