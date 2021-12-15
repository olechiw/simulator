#pragma once
#include "renderable.h"
#include "contact_listener.h"
#include "SFML/Graphics.hpp"
#include "box2d//box2d.h"
#include "constants.h"

class Character : public Renderable, public CollisionHandler
{
public:
	Character(b2World* world, int x, int y);
	~Character();
	void moveToPosition(int x, int y);
	void stopMoving();
	const sf::Vector2f& getPosition() const;
private:
	b2Body* body;
	b2World* world;
	sf::CircleShape shape;
	static constexpr int RadiusPixels = 15;
	static constexpr float MoveSpeed = 30.f;
public:
	// Inherited via collisionhandler
	void collideWith(b2Fixture* other) override;

	// Inherited via Renderable
	void render(sf::RenderWindow& window) override;
	void onPhysicsUpdated() override;
};

