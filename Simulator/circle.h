#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "contact_listener.h"
#include "body_user_data.h"
#include "renderable.h"
#include "constants.h"
#include "object_config.h"

class Circle : public SceneObject
{
public:
	Circle(std::shared_ptr<b2World> world, const ObjectConfig &objectConfig, int radiusPixels = 10, const sf::Color color = sf::Color::Red);
	~Circle();
	b2Body* getBody() override;
	const sf::Vector2f& getPosition() const;
protected:
	void destroy() override;
private:
	b2Body* body;
	sf::CircleShape shape;
	std::shared_ptr<b2World> world;
	int bounced = 0;

public:
	// Inherited via SceneObject
	virtual void render(sf::RenderWindow& window) override;
	virtual void onPhysicsUpdated() override;
};

