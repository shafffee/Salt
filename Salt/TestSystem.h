#pragma once
#include <iostream>
#include <ECS\Entity\EntityPack.h>

void moveSystem(uint16_t e) {
	float* posx = (salt::ECS::entities.getEntity(e)->getComponent("position")->getField<float*>("x"));
	float* posy = (salt::ECS::entities.getEntity(e)->getComponent("position")->getField<float*>("y"));
	float* speedx = (salt::ECS::entities.getEntity(e)->getComponent("speed")->getField<float*>("x"));
	float* speedy = (salt::ECS::entities.getEntity(e)->getComponent("speed")->getField<float*>("y"));


	if (*posx < 0) {
		//std::cout << "hit "<<*posx<<" "<<*posy<<" "<<*speedx<<" "<<*speedy << std::endl;
		if(*speedx < 0) *speedx = -*speedx;
	}
	if (*posx > 1) {
		//std::cout << "hit " << *posx << " " << *posy << " " << *speedx << " " << *speedy << std::endl;
		if (*speedx > 0) *speedx = -*speedx;
	}
	
	if (*posy < 0) {
		//std::cout << "hit " << *posx << " " << *posy << " " << *speedx << " " << *speedy << std::endl;
		if (*speedy < 0) *speedy = -*speedy;
	}
	if (*posy > 1) {
		//std::cout << "hit " << *posx << " " << *posy << " " << *speedx << " " << *speedy << std::endl;
		if (*speedy >0) *speedy = -*speedy;
	}

	*posx += *speedx;
	*posy += *speedy;

	salt::Renderer::drawSprite(*posx, *posy, salt::pix_x(100), salt::pix_y(100), "smile", Color(*posx * 230, *posx * 230, *posy * 200, 255));
}