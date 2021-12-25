#pragma once
#include <list>
#include "contact_event_store.h"
#include "contact_listener.h"
#include "object_config.h"
#include "ability.h"
#include "shape.h"
#include "object_identifier.h"
#include "projectile_behavior.h"
#include <queue>
#include <iostream>

using std::shared_ptr;

class ProjectileAbility : public Ability
{
private:
	std::deque < std::pair<ObjectIdentifier, std::shared_ptr<Shape>>> projectiles;

	shared_ptr<b2World> world;
	shared_ptr<ContactEventStore> contactStore;
	CollisionBehavior collisionBehavior;
	SpawnBehavior spawnBehavior;

	constexpr static size_t maximumProjectiles = 200;

	void addProjectile(ObjectIdentifier obj, std::shared_ptr<Shape> proj)
	{
		this->projectiles.push_front({ obj, proj });
		if (this->projectiles.size() > maximumProjectiles)
		{
			auto& toFree = this->projectiles.back();
			toFree.second->destroy();
			this->cleanup(toFree.first);
			this->projectiles.pop_back();
		}
	}

	void cleanup(ObjectIdentifier obj)
	{
		contactStore->freeObject(obj);
	}

public:
	ProjectileAbility(std::shared_ptr<b2World> worldIn, shared_ptr<ContactEventStore> contactStoreIn, CollisionBehavior collisionBehaviorIn, SpawnBehavior spawnBehaviorIn) :
		world(worldIn), 
		contactStore(contactStoreIn), 
		collisionBehavior(collisionBehaviorIn),
		spawnBehavior(spawnBehaviorIn) {

	}

	void draw(sf::RenderWindow& window) override {
		for (auto& proj : this->projectiles) {
			proj.second->draw(window);
		}
	}

	virtual void fire(int originX, int originY, int targetX, int targetY) override {
		
		for (auto proj : this->spawnBehavior({ originX, originY }, { targetX, targetY }, this->world)) {
			assert(proj);
			this->addProjectile(proj->getObjectIdentifier(), proj);
		}
	}

	virtual void onPhysicsUpdated() override {
		for (auto it = this->projectiles.begin(); it != projectiles.end();)
		{
			ObjectIdentifier identifier = it->first;
			auto events = this->contactStore->popEvents(identifier);
			bool destroyProjectile = this->collisionBehavior(events);

			if (destroyProjectile)
			{
				this->cleanup(identifier);
				it = this->projectiles.erase(it);
			}
			else
			{
				it->second->onPhysicsUpdated();
				it++;
			}
		}
	}
};

