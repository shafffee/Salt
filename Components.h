#pragma once
#include "Salt.h"

class sprite_comp {
public:
	float x = 0;
	float y = 0;
	float width = 1;
	float height = 1;
	Sprite* sprite;
};
inline static salt::ECS::Component<sprite_comp> SPRITE_COMP;

class char2Dcontrols_comp {
public:
	float x = 0;
	float y = 0;
	float speed = 1.0f;
};
inline static salt::ECS::Component<char2Dcontrols_comp> CHAR2DCONTROLS_COMP;


class bullet_comp {
public:
	float x = 0;
	float y = 0;
	float speed = 1.0f;
};
inline static salt::ECS::Component<bullet_comp> BULLET_COMP;
