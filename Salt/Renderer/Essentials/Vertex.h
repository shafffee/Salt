#pragma once
#include <glm/glm.hpp>

//Vertex is sent to GPU
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};