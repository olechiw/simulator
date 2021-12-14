#pragma once
#include <SFML/Graphics.hpp>
class Renderable
{
public:
	virtual ~Renderable();
	// Render is called an arbitrary number of times
	virtual void render(sf::RenderWindow& window) = 0;
	// UpdatePhysics is called when the physics engine has updated
	virtual void onPhysicsUpdated() = 0;
	virtual bool isDestroyed();
protected:
	void destroy();
	bool destroyed = false;
};

