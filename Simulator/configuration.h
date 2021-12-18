#pragma once
#include <SFML/Graphics.hpp>
class Configuration
{
private:
	sf::Vector2u screenSize = { 1920, 1080 };
public:
	static Configuration& getInstance()
	{
		static Configuration c;
		return c;
	}


	const sf::Vector2u& getScreenSize()
	{
		return this->screenSize;
	}

	void setScreenSize(sf::Vector2u screenSizeIn)
	{
		this->screenSize = screenSizeIn;
	}
};