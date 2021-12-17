#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "drawable.h"
#include "event_consumer.h"
#include "scene.h"
#include "shape.h"

class Enemies : public Drawable, public EventConsumer
{
public:
	Enemies(std::shared_ptr<b2World> world);
	void onPhysicsUpdated() override;
	void draw(sf::RenderWindow& window) const override;
private:
	std::shared_ptr<b2World> world;
	sf::Clock spawnClock;
	static constexpr float spawnTime = 1.f;
	static constexpr size_t maxObjects = 4;
	std::list<std::pair<ObjectIdentifier, std::shared_ptr<Shape>>> objects;
};

