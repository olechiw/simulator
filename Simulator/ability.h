#pragma once
#include <SFML/Graphics.hpp>
#include "event_consumer.h"

class Ability : public EventConsumer
{
public:
	virtual ~Ability() = default;
	virtual void fire(int originX, int originY, int directionX, int directionY) = 0;
};

