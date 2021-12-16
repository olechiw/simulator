#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "object_identifier.h"
#include "constants.h"

struct ObjectInfo
{
	const ObjectIdentifier identifier;
	const ObjectType type;
};

class SceneType
{
public:
	void registerCollision(ObjectInfo a, ObjectInfo b) {
		if (!this->collisions[a.identifier])
			this->collisions[a.identifier] = std::make_shared<std::unordered_set<ObjectIdentifier>>();
		if (!this->collisions[b.identifier])
			this->collisions[b.identifier] = std::make_shared<std::unordered_set<ObjectIdentifier>>();

		this->collisions[a.identifier]->insert(b);
		this->collisions[b.identifier]->insert(a);
	}

	// May return nullptr
	std::shared_ptr<std::unordered_set<ObjectInfo>> getCollisions(ObjectIdentifier identifier) {
		std::shared_ptr<std::unordered_set<ObjectInfo>> objectEvents = this->collisions[identifier];
		return objectEvents;
	}

	void freeObject(ObjectIdentifier object) {
		this->collisions.erase(object);
	}

private:
	std::unordered_map < ObjectIdentifier, std::shared_ptr < std::unordered_set<ObjectInfo> > > collisions;
};

static SceneType Scene;