#include "enemies.h"

Enemies::Enemies(std::shared_ptr<b2World> worldIn) : world(worldIn)
{
}

void Enemies::onPhysicsUpdated()
{
	if (spawnClock.getElapsedTime().asSeconds() >= spawnTime && objects.size() < maxObjects)
	{
		spawnClock.restart();
		ObjectIdentifier identifier(ObjectType::Enemy);
		ObjectConfig config;
		config.InitialPosition = { (rand() % 400) + 50.f, (rand() % 400) + 50.f };
		config.Collision = { BitMasks::Enemy, BitMasks::PlayerBullet };
		config.Elasticity = 0.f;
		config.Info = new ObjectIdentifier(identifier);
		auto square = std::make_shared<Shape>(this->world, config, MakePolygon(10, sf::Color::Red, 4));
		this->objects.push_back({ identifier, square });
	}
	for (auto it = this->objects.begin(); it != this->objects.end();)
	{
		auto events = Scene.getCollisions(it->first);
		if (events && !events->empty())
		{
			events->clear();
			Scene.freeObject(it->first);
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
