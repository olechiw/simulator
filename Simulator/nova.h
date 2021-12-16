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
public:
	Nova(ObjectConfig::collision collisionBits) {
	}
private:
	ObjectConfig::collision collisionBits;

	std::unordered_map<ObjectIdentifier, std::shared_ptr<Circle>> projectiles;

	std::shared_ptr<b2World> world;
	std::shared_ptr<sf::RenderWindow> window;


public:
	Nova(std::shared_ptr<b2World> worldIn, std::shared_ptr<sf::RenderWindow> windowIn) : world(worldIn), window(windowIn) {

	}

	void render() {
		for (auto& proj : projectiles) {
			proj.second->render(*this->window.get());
		}
	}

	virtual void fire(int originX, int originY, int, int) override {
		std::vector<std::pair<int, int>> shots = {
			{10, 10},
			{-10, 10},
			{-10, -10},
			{10, -10}
		};
		for (const auto& shot : shots) {
			ObjectIdentifier projIdentifier;
			ObjectConfig projConfig;
			projConfig.Info = new ObjectInfo {
				projIdentifier,
				PlayerBullet
			};
			projConfig.Collision = this->collisionBits;
			projConfig.Elasticity = 1.001;
			projConfig.InitialPosition = { originX + shot.first, originY + shot.second };
			auto circle = std::make_shared<Circle>(this->world, projConfig, 15, sf::Color::Blue);
			circle->getBody()->ApplyForceToCenter({ shot.first, shot.second }, true);
			this->projectiles.emplace(projIdentifier, circle);
		}
	}

	virtual void onPhysicsUpdated() override {
		for (auto it = this->projectiles.begin(); it != projectiles.end();)
		{
			auto identifier = it->first;
			std::shared_ptr<std::vector<ObjectInfo>> events = Scene.getCollisions(identifier);
			if (events && !events->empty()) {
				events->clear();
				Scene.freeObject(identifier);
				it = this->projectiles.erase(identifier);
			}
			else {
				it++;
			}

		}
	}
};

