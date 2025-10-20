#pragma once

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

    union {
        glm::vec3 position;
        glm::vec3 pos;
        
        // Anonymous struct (compiler extension - check your compiler support)
        struct {
            float x, y, z;
        };
    };

    //  size | scale | width,height,depth
    union {
        glm::vec3 size;
        glm::vec3 scale;
        
        // Anonymous struct (compiler extension - check your compiler support)
        struct {
            float width, height, depth;
        };
    };

    // rotation | rot | roll,pitch,yaw
    union {
        glm::vec3 rotation;
        glm::vec3 rot;
        
        // Anonymous struct (compiler extension - check your compiler support)
        struct {
            float roll, pitch, yaw;
        };
    };

    c_transformation() : position(0.0f), size(1.0f), rotation(0.0f) {}

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