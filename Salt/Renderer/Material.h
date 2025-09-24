#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

struct Material {
  glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f,1.0f);

  Texture texture;

  Material() {};
  Material(glm::vec4 color, Texture texture) :
    color(color), texture(texture) {};

  void passToShader(salt::Shader &shader);

};