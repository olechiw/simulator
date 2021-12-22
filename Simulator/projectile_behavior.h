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

// Return a vector of newly created shapes
using SpawnBehavior = std::function < vector<shared_ptr<Shape>>(sf::Vector2i origin, sf::Vector2i direction, std::shared_ptr<b2World> world)>;

namespace ProjectileBehaviors
{
	extern CollisionBehavior destroyAfterContacts(int maxContacts, ObjectType type);
	extern SpawnBehavior spawnInDirection(
		int distance,
		ObjectConfig defaultConfig,
		ObjectType objectType,
		std::shared_ptr<ShapeDefinitionProvider> shapeDefinition,
		float speed);

	extern SpawnBehavior spawnInNova(
		int distance,
		ObjectConfig defaultConfig,
		ObjectType objectType,
		shared_ptr<ShapeDefinitionProvider> shapeDefinition,
		float speed);
}

CollisionBehavior operator+(const CollisionBehavior& first, const CollisionBehavior& second);