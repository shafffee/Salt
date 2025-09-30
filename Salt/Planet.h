#include "Salt.h"

#define ROTATION_SPEED 0.5

//spin
void s_spin(salt::ECS::Entity e)
{
    float angle = e.component<c_transformation>(C_TRANSFORMATION)->rot.z;
    angle+=ROTATION_SPEED;
    e.component<c_transformation>(C_TRANSFORMATION)->rot = {angle/3,angle/2,angle};
}

inline static salt::ECS::System S_SPIN(&s_spin, C_TRANSFORMATION);

//shoots bullet with the center on x, y
salt::ECS::Entity createPlanetEntity(){
    salt::ECS::Entity planet( 
                            C_MODEL  | C_TRANSFORMATION, 
                            S_DRAW   | S_SPIN
    );

    //pos
    planet.component<c_transformation>(C_TRANSFORMATION)->x = 0;
    planet.component<c_transformation>(C_TRANSFORMATION)->y = 0;
    planet.component<c_transformation>(C_TRANSFORMATION)->z = -2;


    //size
    //planet.component<c_transformation>(C_TRANSFORMATION)->width = BULLET_SIZE_X;
    //planet.component<c_transformation>(C_TRANSFORMATION)->height = BULLET_SIZE_Y;

    //model
    planet.component<c_model>(C_MODEL)->model = new Model("./res/low-poly-planet-earth/Planet.fbx");
    planet.component<c_model>(C_MODEL)->layer = -1;

    return planet;
}