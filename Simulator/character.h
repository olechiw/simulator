#pragma once
#include "renderable.h"
#include "contact_listener.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "circle.h"
#include "scene.h"

class Character
{
public:
	Character(std::shared_ptr<b2World> world, std::shared_ptr<CollisionHandler> collisionHandler, int x, int y);
	void moveToPosition(int x, int y);
	void stopMoving();
	const sf::Vector2f& getPosition() const;
private:
	std::shared_ptr<b2World> world;
	std::shared_ptr<Circle> shape;
	static constexpr int RadiusPixels = 15;
	static constexpr float MoveSpeed = 4.f;
};

