#pragma once
class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void draw(sf::RenderWindow& window) const = 0;
};

