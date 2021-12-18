#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include "object_identifier.h"
#include "shape.h"
#include "object_config.h"
#include "contact_event_store.h"
#include "shape_definition_provider.h"

using std::unordered_map;
using std::vector;
using std::shared_ptr;

// return true if the behavior destroys the object
using CollisionBehavior = std::function<bool(const ContactEventStore::ContactEvents&)>;


using SpawnBehavior = std::function < vector<shared_ptr<Shape>>(sf::Vector2i origin, sf::Vector2i direction, std::shared_ptr<b2World> world)>;

namespace ProjectileBehaviors
{
	extern CollisionBehavior destroyAfterContacts(int maxContacts, ObjectType type)
	{
		static unordered_map<ObjectIdentifier, unordered_map<ObjectType, int>> contactCounter;
		return [=](const ContactEventStore::ContactEvents& events) {
			if (events.beginContactEvents)
			{
				for (auto& event : *events.beginContactEvents.get())
				{
					if (event.getType() == type)
					{
						if (contactCounter[events.objectIdentifier][type] >= maxContacts)
						{
							contactCounter.erase(events.objectIdentifier);
							return true;
						}
					}
				}
			}
			if (events.endContactEvents)
			{
				for (auto& event : *events.endContactEvents.get())
				{
					if (event.getType() == type)
					{
						contactCounter[events.objectIdentifier][type]++;
						// Only count up once per iteration
						break;
					}
				}
			}
			return false;
		};
	}

	extern SpawnBehavior spawnInDirection(
		int distance,
		ObjectConfig defaultConfig,
		ObjectType objectType,
		std::shared_ptr<ShapeDefinitionProvider> shapeDefinition,
		float speed)
	{
		return [=](sf::Vector2i origin, sf::Vector2i direction, std::shared_ptr<b2World> world) {
			vector<shared_ptr<Shape>> shapes;

			ObjectConfig config = defaultConfig;
			config.identifier = std::make_shared<ObjectIdentifier>(objectType);
			auto projVector = Math::angleVector(origin.x, origin.y, direction.x, direction.y);
			config.initialPosition = { origin.x + static_cast<int>(projVector.x * distance), origin.y + static_cast<int>(projVector.y * distance) };

			auto shape = std::make_shared<Shape>(world, config, shapeDefinition->get());

			auto projAngle = Math::pointAngleRadians(origin.x, origin.y, direction.x, direction.y);
			shape->getBody()->SetTransform(
				shape->getBody()->GetPosition(), projAngle
			);
			shape->getBody()->SetLinearVelocity({ projVector.x * speed, projVector.y * speed });

			shapes.push_back(shape);

			return shapes;
		};
	}

	extern SpawnBehavior spawnInNova(
		int distance,
		ObjectConfig defaultConfig,
		ObjectType objectType,
		shared_ptr<ShapeDefinitionProvider> shapeDefinition,
		float speed)
	{
		static const std::vector<sf::Vector2i> directions = {
			{1, 1}, {-1, 1}, {-1, -1}, {1, -1} 
		};
		return [=](sf::Vector2i origin, sf::Vector2i direction, std::shared_ptr<b2World> world) {
			vector<shared_ptr<Shape>> shapes;

			for (const auto& direction : directions)
			{
				ObjectConfig config = defaultConfig;
				config.identifier = std::make_shared<ObjectIdentifier>(objectType);
				config.initialPosition = { origin.x + distance * direction.x, origin.y + distance * direction.y };

				auto shape = std::make_shared<Shape>(world, config, shapeDefinition->get());
				shape->getBody()->SetTransform(
					shape->getBody()->GetPosition(), Math::pointAngleRadians(0, 0, direction.x, direction.y)
				);
				auto directionVector = Math::angleVector(0, 0, direction.x, direction.y);
				shape->getBody()->SetLinearVelocity({ directionVector.x * speed, directionVector.y * speed });
				shapes.push_back(shape);
			}
			
			return shapes;
		};
	}
}

CollisionBehavior operator+(const CollisionBehavior& first, const CollisionBehavior& second)
{
	return [=](const ContactEventStore::ContactEvents& events) {
		return first(events) || second(events);
	};
}