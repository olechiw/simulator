#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball(b2World& world, unsigned int x = 0, unsigned int y = 0, const sf::Color color = sf::Color::Red);
	~Ball();
	b2Body* getBody();
	const sf::CircleShape& getShape();
	static constexpr int RadiusPixels = 10;
private:
	b2Body* body;
	sf::CircleShape shape;
};

