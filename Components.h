#pragma once
#include "ECS.h"


class position_comp {
public:
	float x = 0;
	float y = 0;
};
inline static salt::ECS::Component<position_comp> POSITION;
