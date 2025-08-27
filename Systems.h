#pragma once
#include "ECS.h"


/*
void bulletFlight(salt::ECS::Entity e)
{

	int speed = 5;
	e.component<position_comp>(POSITION)->y -= salt::pix_y(speed);
	salt::Renderer::drawSprite(e.component<position_comp>(POSITION)->x, e.component<position_comp>(POSITION)->y, salt::pix_x(2), salt::pix_y(1), salt::Color("#FFFF00"));
	if (e.component<position_comp>(POSITION)->y < 0) e.destroy();

}

inline static salt::ECS::System BULLET(&bulletFlight, POSITION);

void char2Dcontrols(salt::ECS::Entity e)
{

	int speed = 3;
	if (salt::Input::IsKeyPressed(SALT_KEY_A)) e.component<position_comp>(POSITION)->x -= salt::pix_x(speed);
	if (salt::Input::IsKeyPressed(SALT_KEY_D)) e.component<position_comp>(POSITION)->x += salt::pix_x(speed);
	if (salt::Input::IsKeyPressed(SALT_KEY_W)) e.component<position_comp>(POSITION)->y -= salt::pix_y(speed);
	if (salt::Input::IsKeyPressed(SALT_KEY_S)) e.component<position_comp>(POSITION)->y += salt::pix_y(speed);

	if (salt::Input::IsKeyPressed(SALT_KEY_SPACE)) {

		salt::ECS::Entity bullet1(POSITION, BULLET);
		bullet1.component<position_comp>(POSITION)->x = e.component<position_comp>(POSITION)->x+ salt::pix_x(10);
		bullet1.component<position_comp>(POSITION)->y = e.component<position_comp>(POSITION)->y+ salt::pix_y(40);

		salt::ECS::Entity bullet2(POSITION, BULLET);
		bullet2.component<position_comp>(POSITION)->x = e.component<position_comp>(POSITION)->x+ salt::pix_x(90);
		bullet2.component<position_comp>(POSITION)->y = e.component<position_comp>(POSITION)->y + salt::pix_y(40);
	}

	salt::Renderer::drawSprite(e.component<position_comp>(POSITION)->x, e.component<position_comp>(POSITION)->y, salt::pix_x(100), salt::pix_y(100), "jet", "#FFFFFF");
}

inline static salt::ECS::System CHAR_CONTROLS(&char2Dcontrols, POSITION);

*/