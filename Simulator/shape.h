#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "contact_listener.h"
#include "scene.h"
#include "constants.h"
#include "object_config.h"
#include "drawable.h"
#include "math.h"

struct ShapeDefinition
{
	std::shared_ptr<sf::Shape> shape;
	std::shared_ptr<b2Shape> b2Shape;
};

extern ShapeDefinition MakeCircle(float radiusPixels, sf::Color color);

extern ShapeDefinition MakePolygon(float length, sf::Color color, int size);

class Shape : public Drawable
{
public:
	Shape(std::shared_ptr<b2World> world, const ObjectConfig &objectConfig, const ShapeDefinition& shapeDefinition);
	~Shape();
	b2Body* getBody();
	const sf::Vector2f& getPosition() const;
private:
	b2Body* body;
	ShapeDefinition shapeDefinition;
	std::shared_ptr<sf::Shape> shape;
	std::shared_ptr<b2World> world;
	int bounced = 0;
	bool destroyed = false;
public:
	void draw(sf::RenderWindow& window) const override;
	void onPhysicsUpdated();
	bool isDestroyed() const;
	void destroy();
};

