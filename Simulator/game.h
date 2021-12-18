#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "character.h"
#include "mouse_state.h"
#include "ability.h"
#include "enemies.h"
#include "contact_event_store.h"

using std::shared_ptr;

class Game
{
public:
	Game(shared_ptr<b2World> world, shared_ptr<sf::RenderWindow> window, shared_ptr<ContactEventStore> contactStore);

	void run();

	template<typename T>
	void setAbility(std::shared_ptr<T> ability)
	{
		this->activeAbility = std::static_pointer_cast<Ability>(ability);
	}

	static constexpr float abilityRate = .1f;


private:
	void updateInput();

	void updatePhysics();

	void updateScreen();

	sf::Clock abilityClock;
	sf::Clock physicsClock;

	MouseState mouseState;
	std::shared_ptr<Character> character;
	std::shared_ptr<Enemies> enemies;
	std::shared_ptr<Ability> activeAbility;
	std::shared_ptr<ContactEventStore> contactStore;
	std::shared_ptr<b2World> world;
	std::shared_ptr<sf::RenderWindow> window;

};