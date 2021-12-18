#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "drawable.h"
#include "simulated.h"
#include "contact_event_store.h"
#include "shape.h"
#include "configuration.h"
#include "polygon_provider.h"

using std::shared_ptr;
using std::list;
using std::pair;

class Enemies : public Drawable, public Simulated
{
public:
	Enemies(shared_ptr<b2World> world, shared_ptr<ContactEventStore> contactStore);
	void onPhysicsUpdated() override;
	void draw(sf::RenderWindow& window) const override;
private:
	static constexpr float spawnTime = 1.f;
	static constexpr size_t maxObjects = 4;

	shared_ptr<b2World> world;
	shared_ptr<ContactEventStore> contactStore;

	sf::Clock spawnClock;
	list<pair<ObjectIdentifier, shared_ptr<Shape>>> objects;
};

