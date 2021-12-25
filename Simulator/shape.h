#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

#include "contact_listener.h"
#include "object_identifier.h"
#include "constants.h"
#include "object_config.h"
#include "drawable.h"
#include "shape_definition.h"
#include "simulated.h"
#include "math.h"




class Shape : public Drawable, public Simulated
{
public:
	Shape(std::shared_ptr<b2World> world, const ObjectConfig &objectConfig, const ShapeDefinition& shapeDefinition);
	~Shape();
	b2Body* getBody();
	const sf::Vector2f& getPosition() const;
	const ObjectIdentifier& getObjectIdentifier() const;
private:
	b2Body* body;
	ShapeDefinition shapeDefinition;
	std::shared_ptr<sf::Shape> shape;
	std::shared_ptr<b2World> world;
	int bounced = 0;
	bool destroyed = false;
	std::shared_ptr<ObjectIdentifier> objectIdentifier;
public:
	void draw(sf::RenderWindow& window) override;
	void onPhysicsUpdated() override;
	bool isDestroyed() const;
	void destroy();
};

