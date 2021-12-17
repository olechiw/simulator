#pragma once
#include <list>
#include "scene.h"
#include "contact_listener.h"
#include "object_config.h"
#include "ability.h"
#include "shape.h"
#include "object_identifier.h"
#include <queue>
#include <iostream>


class Nova : public Ability
{
private:
	ObjectConfig::collision collisionBits;

	std::deque < std::pair<ObjectIdentifier, std::shared_ptr<Shape>>> projectiles;

	std::shared_ptr<b2World> world;
	std::shared_ptr<sf::RenderWindow> window;

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
		Scene.freeObject(obj);
	}

public:
	Nova(std::shared_ptr<b2World> worldIn, ObjectConfig::collision collisionBitsIn) : world(worldIn), collisionBits(collisionBitsIn) {

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
			auto circle = std::make_shared<Shape>(this->world, projConfig, MakeCircle(10.f, sf::Color::Green));
			circle->getBody()->SetLinearVelocity({ static_cast<float>(shot.first*speed), static_cast<float>(shot.second*speed) });
			addProjectile(projIdentifier, circle);
		}
	}

	virtual void onPhysicsUpdated() override {
		for (auto it = this->projectiles.begin(); it != projectiles.end();)
		{
			auto identifier = it->first;
			std::shared_ptr<std::unordered_set<ObjectIdentifier>> events = Scene.getCollisions(identifier);
			bool projValid = true;
			if (events && !events->empty()) {
				this->cleanup(it->first);
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

