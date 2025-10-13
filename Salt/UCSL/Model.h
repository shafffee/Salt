#include <glm/glm.hpp>
#include <stb_image.h>

#include "Logging.h"
#include "Core.h"
#include "ECS.h"
#include "Utils.h"
#include "Renderer.h"
#include "Input.h"

//      C_MODEL
//component that is used for any transformations: position, size, rotation, etc.
struct c_model {
public:
    
    //model
    Model* model = nullptr;
    Sprite* sprite = nullptr;
    Text* text = nullptr;

    //layer
    int layer = 0;
};
inline static salt::ECS::Component<c_model> C_MODEL;

// system to draw model with transformation applied ( requires C_MODEL and C_TRANSFORMATION ) 
void s_draw(salt::ECS::Entity e)
{

    if(e.component<c_model>(C_MODEL)->model){
            //setting transformation to model
        e.component<c_model>(C_MODEL)->model->setPosition(
                e.component<c_transformation>(C_TRANSFORMATION)->position
        );
        e.component<c_model>(C_MODEL)->model->setScale(
                e.component<c_transformation>(C_TRANSFORMATION)->scale
        );
        e.component<c_model>(C_MODEL)->model->setRotation(
                e.component<c_transformation>(C_TRANSFORMATION)->rotation
        );

        salt::Renderer::draw(e.component<c_model>(C_MODEL)->model, e.component<c_model>(C_MODEL)->layer);
    
    }

    if(e.component<c_model>(C_MODEL)->sprite){
        //setting transformation to model
        e.component<c_model>(C_MODEL)->sprite->setPosition(
                e.component<c_transformation>(C_TRANSFORMATION)->position
        );
        e.component<c_model>(C_MODEL)->sprite->setScale(
                e.component<c_transformation>(C_TRANSFORMATION)->scale
        );
        e.component<c_model>(C_MODEL)->sprite->setRotation(
                e.component<c_transformation>(C_TRANSFORMATION)->rotation
        );

        salt::Renderer::draw(e.component<c_model>(C_MODEL)->sprite, e.component<c_model>(C_MODEL)->layer);
    
    }

    if(e.component<c_model>(C_MODEL)->text){
        //setting transformation to model
        e.component<c_model>(C_MODEL)->text->setPosition(
                e.component<c_transformation>(C_TRANSFORMATION)->position
        );
        e.component<c_model>(C_MODEL)->text->setScale(
                e.component<c_transformation>(C_TRANSFORMATION)->scale
        );
        e.component<c_model>(C_MODEL)->text->setRotation(
                e.component<c_transformation>(C_TRANSFORMATION)->rotation
        );

        salt::Renderer::draw(e.component<c_model>(C_MODEL)->text, e.component<c_model>(C_MODEL)->layer);
    
    }
}

inline static salt::ECS::System S_DRAW(&s_draw, C_MODEL|C_TRANSFORMATION);