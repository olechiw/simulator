#pragma once
#include "shape_definition_provider.h"
#include "math.h"
#include "constants.h"

class PolygonProvider : public ShapeDefinitionProvider
{
public:
	PolygonProvider(float radius, sf::Color color, int numberOfSides);
	ShapeDefinition get() const override;
private:
	float radiusPixels;
	sf::Color color;
	int numberOfSides;
};