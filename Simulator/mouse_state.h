#pragma once
#include <SFML/Graphics.hpp>
class MouseState
{
public:
	void handleMouseEvents(sf::Event event);
	bool leftButtonPressed();
	bool rightButtonPressed();
private:
	bool leftButton = false;
	bool rightButton = false;
};

