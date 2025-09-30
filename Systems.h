#pragma once
#include "Salt.h"

/*
void bulletFlight(salt::ECS::Entity e)
{

	int speed = 5;
	e.component<position_comp>(POSITION)->y -= salt::pix_y(speed);
	salt::Renderer::drawSprite(e.component<position_comp>(POSITION)->x, e.component<position_comp>(POSITION)->y, salt::pix_x(2), salt::pix_y(1), salt::Color("#FFFF00"));
	if (e.component<position_comp>(POSITION)->y < 0) e.destroy();

}

inline static salt::ECS::System BULLET(&bulletFlight, POSITION);
*/

void sprite_sys(salt::ECS::Entity e)
{
    e.component<sprite_comp>(SPRITE_COMP)->sprite->setPosition({
        e.component<sprite_comp>(SPRITE_COMP)->x,
        e.component<sprite_comp>(SPRITE_COMP)->y,
        -1
    });
    e.component<sprite_comp>(SPRITE_COMP)->sprite->setScale({
        e.component<sprite_comp>(SPRITE_COMP)->width,
        e.component<sprite_comp>(SPRITE_COMP)->height,
        -1
    });

	salt::Renderer::draw(e.component<sprite_comp>(SPRITE_COMP)->sprite);
}

inline static salt::ECS::System SPRITE_SYS(&sprite_sys, SPRITE_COMP);


void char2Dcontrols_sys(salt::ECS::Entity e)
{
    float speed = e.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->speed;
    if (salt::Input::IsKeyPressed(SALT_KEY_A)) e.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->x -= speed;
    if (salt::Input::IsKeyPressed(SALT_KEY_D)) e.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->x += speed;
    if (salt::Input::IsKeyPressed(SALT_KEY_W)) e.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->y += speed;
    if (salt::Input::IsKeyPressed(SALT_KEY_S)) e.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->y -= speed;
}

inline static salt::ECS::System CHAR2DCONTROLS_SYS(&char2Dcontrols_sys, CHAR2DCONTROLS_COMP);
