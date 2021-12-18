#pragma once
#include <SFML/Graphics.hpp>

#include "contact_listener.h"
#include "object_config.h"

struct ObjectConfig {
	struct CollisionBits {
		int16_t CategoryBits;
		int16_t MaskBits;
	} collisionBits;
	sf::Vector2i initialPosition;
	float elasticity = 1.001f;
	std::shared_ptr<ObjectIdentifier> identifier;
};