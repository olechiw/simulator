#pragma once
#include "shape_definition_provider.h"
#include "math.h"
#include "constants.h"

class CircleProvider : public ShapeDefinitionProvider
{
public:
	CircleProvider(int radiusPixels, sf::Color color);
	ShapeDefinition get() const override;
private:
	int radiusPixels;
	sf::Color color;
};

