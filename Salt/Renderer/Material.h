#include <glm/glm.hpp>


struct Material {
  glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 diffuse = glm::vec3(0.55f, 0.55f, 0.55f);
  glm::vec3 specular = glm::vec3(0.70f, 0.70f, 0.70f);
  float shininess = 0.25f;

  Material() {};
  Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
    ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {};
};