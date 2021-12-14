#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "contact_listener.h"
#include "renderable.h"

class Ball : private CollisionHandler, public Renderable
{
public:
	Ball(b2World* world, unsigned int x = 0, unsigned int y = 0, const sf::Color color = sf::Color::Red);
	~Ball();
	b2Body* getBody();
	static constexpr int RadiusPixels = 10;
private:
	b2Body* body;
	sf::CircleShape shape;
	b2World* world;
	int bounced = 0;

public:
	// Inherited via collisionhandler
	void collideWith(b2Fixture* other) override;

	// Inherited via Renderable
	virtual void render(sf::RenderWindow& window) override;
	virtual void onPhysicsUpdated() override;
};

