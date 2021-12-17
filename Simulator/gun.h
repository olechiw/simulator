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

class Gun : public Ability
{
private:
	ObjectConfig::CollisionBits collisionBits;

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
	Gun(std::shared_ptr<b2World> worldIn, ObjectConfig::CollisionBits collisionBitsIn, shared_ptr<ContactEventStore> contactStoreIn) : world(worldIn), collisionBits(collisionBitsIn), contactStore(contactStoreIn) {

	}

	void draw(sf::RenderWindow& window) const override {
		for (auto& proj : this->projectiles) {
			proj.second->draw(window);
		}
	}

	virtual void fire(int originX, int originY, int targetX, int targetY) override {
		sf::Vector2f angleVector = Math::angleVector(originX, originY, targetX, targetY);
		auto angle = Math::pointAngleRadians(originX, originY, targetX, targetY);
		ObjectIdentifier projIdentifier(ObjectType::PlayerBullet);
		ObjectConfig projConfig;
		projConfig.identifier = new ObjectIdentifier(projIdentifier);
		projConfig.collisionBits = this->collisionBits;
		projConfig.elasticity = 1.001f;
		projConfig.initialPosition = { originX + angleVector.x * dist, originY + angleVector.y * dist };
		auto circle = std::make_shared<Shape>(this->world, projConfig, MakePolygon(10.f, sf::Color::Green, 3));
		circle->getBody()->SetLinearVelocity({ static_cast<float>(angleVector.x * speed), static_cast<float>(angleVector.y * speed) });
		circle->getBody()->SetTransform(circle->getBody()->GetPosition(), angle - (Math::pi / 2.f));
		addProjectile(projIdentifier, circle);
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

