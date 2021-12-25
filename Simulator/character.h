#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.h"
#include "shape.h"
#include "simulated.h"
#include "math.h"
#include "circle_provider.h"
#include "ability.h"
#include "polygon_provider.h"
#include "projectile_behavior.h"
#include "projectile_ability.h"
#include "input_state.h"

using std::shared_ptr;

class Character : public Simulated, Drawable
{
public:
	Character(shared_ptr<b2World> world, shared_ptr<ContactEventStore> contactEventStoreIn, int x, int y);
	void handleInput(const InputState& inputState);
	void draw(sf::RenderWindow& window) override;
	void onPhysicsUpdated() override;
private:
	shared_ptr<b2World> world;
	shared_ptr<Shape> shape;
	shared_ptr<ContactEventStore> contactEventStore;
	shared_ptr<Ability> activeAbility;

	sf::Clock abilityClock;

	static constexpr int RadiusPixels = 15;
	static constexpr float MoveSpeed = 10.f;
	static constexpr float AbilityRate = .3f;

	void handleMovement(const InputState& inputState);
	void handleAbility(const InputState& inputState);
	void stopMoving();
};

