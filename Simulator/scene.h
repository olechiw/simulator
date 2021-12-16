#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "object_identifier.h"
#include "constants.h"

class SceneType
{
public:
	void registerCollision(ObjectIdentifier a, ObjectIdentifier b) {
		if (!this->collisions[a])
			this->collisions[a] = std::make_shared<std::unordered_set<ObjectIdentifier>>();
		if (!this->collisions[b])
			this->collisions[b] = std::make_shared<std::unordered_set<ObjectIdentifier>>();

		this->collisions[a]->insert(b);
		this->collisions[b]->insert(a);
	}

	// May return nullptr
	std::shared_ptr<std::unordered_set<ObjectIdentifier>> getCollisions(ObjectIdentifier identifier) {
		std::shared_ptr<std::unordered_set<ObjectIdentifier>> objectEvents = this->collisions[identifier];
		return objectEvents;
	}

	void freeObject(ObjectIdentifier object) {
		this->collisions.erase(object);
	}

private:
	std::unordered_map < ObjectIdentifier, std::shared_ptr < std::unordered_set<ObjectIdentifier> > > collisions;
};

static SceneType Scene;