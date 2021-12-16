#pragma once
#include <list>
#include "scene.h"
#include "contact_listener.h"
#include "object_config.h"
#include "ability.h"
#include "circle.h"
#include "object_identifier.h"


class Nova : public Ability
{
private:
	ObjectConfig::collision collisionBits;

	std::unordered_map<ObjectIdentifier, std::shared_ptr<Circle>> projectiles;

	std::shared_ptr<b2World> world;
	std::shared_ptr<sf::RenderWindow> window;


public:
	Nova(std::shared_ptr<b2World> worldIn, ObjectConfig::collision collisionBitsIn) : world(worldIn), collisionBits(collisionBitsIn) {

	}

	void draw(sf::RenderWindow& window) const override {
		for (auto& proj : projectiles) {
			proj.second->draw(window);
		}
	}

	virtual void fire(int originX, int originY, int, int) override {
		std::vector<std::pair<int, int>> shots = {
			{20.f, 20.f},
			{-20.f, 20.f},
			{-20.f, -20.f},
			{20.f, -20.f}
		};
		for (const auto& shot : shots) {
			ObjectIdentifier projIdentifier(ObjectType::PlayerBullet);
			ObjectConfig projConfig;
			projConfig.Info = new ObjectIdentifier(projIdentifier);
			projConfig.Collision = this->collisionBits;
			projConfig.Elasticity = 1.001f;
			projConfig.InitialPosition = { originX + shot.first, originY + shot.second };
			auto circle = std::make_shared<Circle>(this->world, projConfig, 10.f, sf::Color::Blue);
			circle->getBody()->ApplyForceToCenter({ static_cast<float>(shot.first), static_cast<float>(shot.second) }, true);
			this->projectiles.emplace(projIdentifier, circle);
		}
	}

	virtual void onPhysicsUpdated() override {
		for (auto it = this->projectiles.begin(); it != projectiles.end();)
		{
			auto identifier = it->first;
			std::shared_ptr<std::unordered_set<ObjectIdentifier>> events = Scene.getCollisions(identifier);
			if (events && !events->empty()) {
				events->clear();
				// projectile lifetimes ?? 
				// spawn enemies
				// other fun stuff
				// Scene.freeObject(identifier);
				// it = this->projectiles.erase(it);
			}
			else {
				it->second->onPhysicsUpdated();
				it++;
			}

		}
	}
};

