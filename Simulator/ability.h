#pragma once
#include <SFML/Graphics.hpp>
#include "simulated.h"
#include "drawable.h"

class Ability : public Simulated, public Drawable
{
public:
	virtual ~Ability() = default;
	virtual void fire(int originX, int originY, int directionX, int directionY) = 0;
};

