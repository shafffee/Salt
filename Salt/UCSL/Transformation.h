#include <glm/glm.hpp>
#include <stb_image.h>

#include "Logging.h"
#include "Core.h"
#include "ECS.h"
#include "Utils.h"
#include "Renderer.h"
#include "Input.h"

//      C_TRANSFORMATION
//component that is used for any transformations: position, size, rotation, etc.
struct c_transformation {
public:

    // position | pos | x,y,z
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3& pos = position;
    float& x = pos.x;
    float& y = pos.y;
    float& z = pos.z;

    //  size | scale | width,height,depth
    glm::vec3 size = glm::vec3(1.0f);
    float& width = size.x;
    float& height = size.y;
    float& depth = size.z;
    glm::vec3& scale = size;

    // rotation | rot | roll,pitch,yaw
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3& rot = rotation;
    float& roll = rot.x;
    float& pitch = rot.y;
    float& yaw = rot.z;

    glm::mat4 getTransformationMatrix(){
        // Position matrix (translation)
         glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
            
        // Rotation Matrix from euler
        glm::mat4 rotationMatrix = glm::eulerAngleXYZ(
            glm::radians(rotation.x),
            glm::radians(rotation.y),
            glm::radians(rotation.z)
        );
            
        // Scale matrix
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
            
        //Matrix multiplication
        return translationMatrix * rotationMatrix * scaleMatrix;
    }
};
inline static salt::ECS::Component<c_transformation> C_TRANSFORMATION;