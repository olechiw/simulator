#pragma once
#include "contact_listener.h"
#include "object_config.h"
#include "SFML/Graphics.hpp"

struct ObjectConfig {
	struct collision {
		int16_t CategoryBits;
		int16_t MaskBits;
	} Collision;
	sf::Vector2i InitialPosition;
	float Elasticity = 1.001f;
	ObjectInfo *Info;
};