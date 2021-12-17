#pragma once
#include "contact_listener.h"
#include "object_config.h"
#include "SFML/Graphics.hpp"

struct ObjectConfig {
	struct CollisionBits {
		int16_t CategoryBits;
		int16_t MaskBits;
	} collisionBits;
	sf::Vector2f initialPosition;
	float elasticity = 1.001f;
	ObjectIdentifier *identifier;
};