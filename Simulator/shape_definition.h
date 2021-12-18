#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
struct ShapeDefinition
{
	std::shared_ptr<sf::Shape> shape;
	std::shared_ptr<b2Shape> b2Shape;
};