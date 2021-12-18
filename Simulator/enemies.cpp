#include "enemies.h"

Enemies::Enemies(shared_ptr<b2World> worldIn, shared_ptr<ContactEventStore> contactStoreIn) : world(worldIn), contactStore(contactStoreIn)
{
}

static sf::Vector2f getRandomPosition(const sf::Vector2u& screenSize)
{
	return {
		static_cast<float>(rand() % static_cast<int>(screenSize.x - 100) + 50),
		static_cast<float>(rand() % static_cast<int>(screenSize.y - 100) + 50)
	};
}

void Enemies::onPhysicsUpdated()
{
	if (spawnClock.getElapsedTime().asSeconds() >= spawnTime && objects.size() < maxObjects)
	{
		auto& screenSize = Configuration::getInstance().getScreenSize();
		spawnClock.restart();
		ObjectIdentifier identifier(ObjectType::Enemy);
		ObjectConfig config;
		config.initialPosition = getRandomPosition(screenSize);
		config.collisionBits = { BitMasks::Enemy, BitMasks::PlayerBullet };
		config.elasticity = 0.f;
		config.identifier = new ObjectIdentifier(identifier);
		auto square = std::make_shared<Shape>(this->world, config, MakePolygon(15.f, sf::Color::Red, 4));
		this->objects.push_back({ identifier, square });
	}
	for (auto it = this->objects.begin(); it != this->objects.end();)
	{
		auto events = contactStore->popEvents(it->first);
		if (events.beginContactEvents && !events.beginContactEvents->empty())
		{
			contactStore->freeObject(it->first);
			it = this->objects.erase(it);
		}
		else {
			it++;
		}
	}
}

void Enemies::draw(sf::RenderWindow& window) const
{
	for (auto& obj : this->objects)
	{
		obj.second->draw(window);
	}
}
