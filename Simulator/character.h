#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "shape.h"
#include "scene.h"
#include "event_consumer.h"
#include "contact_listener.h"


class Character : public EventConsumer, Drawable
{
public:
	Character(std::shared_ptr<b2World> world, int x, int y);
	void moveToPosition(int x, int y);
	void stopMoving();
	void draw(sf::RenderWindow& window) const override;
	const sf::Vector2f& getPosition() const;
	void onPhysicsUpdated() override;
private:
	std::shared_ptr<b2World> world;
	std::shared_ptr<Shape> shape;
	static constexpr float RadiusPixels = 15.f;
	static constexpr float MoveSpeed = 4.f;
};

