#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "drawable.h"
class FPSCounter : public Drawable
{
public:
	FPSCounter(int posX, int posY);
	// Inherited via Drawable
	virtual void draw(sf::RenderWindow& window) override;
private:
	sf::Text text;
	int frames;
	sf::Clock clock;
	sf::Font font;

	constexpr static float UpdateTime = .5f;
};

