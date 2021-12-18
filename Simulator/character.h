#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "shape.h"
#include "simulated.h"
#include "math.h"
#include "circle_provider.h"

using std::shared_ptr;

class Character : public Simulated, Drawable
{
public:
	Character(shared_ptr<b2World> world, int x, int y);
	void moveToPosition(int x, int y);
	void stopMoving();
	void draw(sf::RenderWindow& window) const override;
	const sf::Vector2f& getPosition() const;
	void onPhysicsUpdated() override;
private:
	shared_ptr<b2World> world;
	shared_ptr<Shape> shape;
	static constexpr float RadiusPixels = 15.f;
	static constexpr float MoveSpeed = 10.f;
};

