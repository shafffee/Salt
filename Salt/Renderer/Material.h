#include <glm/glm.hpp>


struct Material {
  glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
  glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
  glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
  float shininess = 0.25f;

  

  Material() {};
  Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
    ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {};

};