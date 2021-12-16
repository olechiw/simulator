#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "contact_listener.h"
#include "scene.h"
#include "constants.h"
#include "object_config.h"

class Circle
{
public:
	Circle(std::shared_ptr<b2World> world, const ObjectConfig &objectConfig, float radiusPixels = 10.f, const sf::Color color = sf::Color::Red);
	~Circle();
	b2Body* getBody();
	const sf::Vector2f& getPosition() const;
private:
	b2Body* body;
	sf::CircleShape shape;
	std::shared_ptr<b2World> world;
	int bounced = 0;
	bool destroyed = false;
public:
	void draw(sf::RenderWindow& window) const;
	void onPhysicsUpdated();
	bool isDestroyed() const;
	void destroy();
};

