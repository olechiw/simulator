#include "enemies.h"

Enemies::Enemies(shared_ptr<b2World> worldIn, shared_ptr<ContactEventStore> contactStoreIn) : world(worldIn), contactEventStore(contactStoreIn)
{
	using ProjectileBehaviors::destroyAfterContacts;
	auto projBehavior = destroyAfterContacts(0, ObjectType::Character) + destroyAfterContacts(0, ObjectType::ScreenEdge);

	ObjectConfig defaultConfig;
	defaultConfig.elasticity = 1.001f;
	defaultConfig.collisionBits = {
		BitMasks::EnemyBullet,
		BitMasks::ScreenEdge | BitMasks::Character | BitMasks::PlayerBullet
	};
	shared_ptr<ShapeDefinitionProvider> shapeProvider = std::make_shared<PolygonProvider>(
		15.f,
		sf::Color::Yellow,
		6);
	auto gunDirection = ProjectileBehaviors::spawnInNova(
		15.f,
		defaultConfig,
		ObjectType::EnemyBullet,
		shapeProvider,
		9.f);
	this->ability = std::make_shared<ProjectileAbility>(
		this->world,
		this->contactEventStore,
		projBehavior,
		gunDirection);
}

static sf::Vector2i getRandomPosition(const sf::Vector2u& screenSize)
{
	return {
		rand() % (static_cast<int>(screenSize.x) - 100) + 50,
		rand() % (static_cast<int>(screenSize.y) - 100) + 50
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
		config.identifier = std::make_shared<ObjectIdentifier>(identifier);
		PolygonProvider squareProvider(15.f, sf::Color::Red, 4);
		auto square = std::make_shared<Shape>(this->world, config, squareProvider.get());
		this->objects.push_back({ identifier, square });
	}

	this->ability->onPhysicsUpdated();

	if (fireClock.getElapsedTime().asSeconds() >= Enemies::fireTime)
	{
		fireClock.restart();
		for (auto& object : this->objects)
		{
			auto& pos = object.second->getBody()->GetPosition();
			this->ability->fire(pos.x * PhysicsConstants::pixelsPerMeter, pos.y * PhysicsConstants::pixelsPerMeter, 0, 0);
		}
	}

	for (auto it = this->objects.begin(); it != this->objects.end();)
	{
		auto events = contactEventStore->popEvents(it->first);
		if (events.beginContactEvents && !events.beginContactEvents->empty())
		{
			contactEventStore->freeObject(it->first);
			it = this->objects.erase(it);
		}
		else {
			it++;
		}
	}
}

void Enemies::draw(sf::RenderWindow& window)
{
	for (auto& obj : this->objects)
	{
		obj.second->draw(window);
	}
	this->ability->draw(window);
}
