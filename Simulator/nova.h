#pragma once
#include <list>
#include "contact_event_store.h"
#include "contact_listener.h"
#include "object_config.h"
#include "ability.h"
#include "shape.h"
#include "object_identifier.h"
#include <queue>
#include <iostream>

using std::shared_ptr;

class Nova : public Ability
{
private:
	ObjectConfig::collision collisionBits;

	std::deque < std::pair<ObjectIdentifier, std::shared_ptr<Shape>>> projectiles;
	std::unordered_map< ObjectIdentifier, bool> projectileHasBounced;

	shared_ptr<b2World> world;
	shared_ptr<ContactEventStore> contactStore;

	constexpr static size_t maximumProjectiles = 200;
	constexpr static float dist = 20.f;
	constexpr static float speed = 3.5f;

	void addProjectile(ObjectIdentifier obj, std::shared_ptr<Shape> proj)
	{
		this->projectiles.push_front({ obj, proj });
		if (this->projectiles.size() > maximumProjectiles)
		{
			std::cout << this->projectiles.size() << std::endl;
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
	Nova(std::shared_ptr<b2World> worldIn, ObjectConfig::collision collisionBitsIn, shared_ptr<ContactEventStore> contactStoreIn) : world(worldIn), collisionBits(collisionBitsIn), contactStore(contactStoreIn) {

	}

	void draw(sf::RenderWindow& window) const override {
		for (auto& proj : this->projectiles) {
			proj.second->draw(window);
		}
	}

	virtual void fire(int originX, int originY, int, int) override {
		std::vector<std::pair<int, int>> shots = {
			{1, 1},
			{-1, 1},
			{-1, -1},
			{1, -1}
		};
		for (const auto& shot : shots) {
			ObjectIdentifier projIdentifier(ObjectType::PlayerBullet);
			ObjectConfig projConfig;
			projConfig.Info = new ObjectIdentifier(projIdentifier);
			projConfig.Collision = this->collisionBits;
			projConfig.Elasticity = 1.001f;
			projConfig.InitialPosition = { originX + shot.first*dist, originY + shot.second*dist };
			auto circle = std::make_shared<Shape>(this->world, projConfig, MakePolygon(10.f, sf::Color::Green, 3));
			circle->getBody()->SetLinearVelocity({ static_cast<float>(shot.first*speed), static_cast<float>(shot.second*speed) });
			addProjectile(projIdentifier, circle);
		}
	}

	virtual void onPhysicsUpdated() override {
		for (auto it = this->projectiles.begin(); it != projectiles.end();)
		{
			auto identifier = it->first;
			auto events = contactStore->popEvents(identifier);
			bool destroyProjectile = false;
			if (events.beginContactEvents) {
				for (auto& event : *events.beginContactEvents.get()) 
				{
					if (event.getType() == ObjectType::Enemy)
					{
						destroyProjectile = true;
						break;
					}
					if (event.getType() == ObjectType::ScreenEdge)
					{
						if (projectileHasBounced[identifier])
						{
							destroyProjectile = true;
							break;
						}
					}
				}
			}
			if (events.endContactEvents) {
				for (auto& event : *events.endContactEvents.get())
				{
					if (event.getType() == ObjectType::ScreenEdge)
					{
						projectileHasBounced[identifier] = true;
						break;
					}
				}
			}
			



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

