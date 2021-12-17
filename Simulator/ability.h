#pragma once
#include <SFML/Graphics.hpp>
#include "event_consumer.h"
#include "drawable.h"

class Ability : public EventConsumer, public Drawable
{
public:
	virtual ~Ability() = default;
	virtual void fire(int originX, int originY, int directionX, int directionY) = 0;
};

