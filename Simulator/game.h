#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "character.h"
#include "mouse_state.h"
#include "ability.h"
#include "enemies.h"

using std::shared_ptr;

class Game
{
public:
	Game(shared_ptr<b2World> world, shared_ptr<sf::RenderWindow> window): window(window), world(world)
	{
		// todo: screen size somewhere else
		this->character = std::make_shared<Character>(world, 250, 250);
		this->enemies = std::make_shared<Enemies>(world);
	}

	template<typename T>
	void setAbility(std::shared_ptr<T> ability)
	{
		this->activeAbility = std::static_pointer_cast<Ability>(ability);
	}

	static constexpr float abilityRate = .1f;

	void run()
	{
		while (this->window->isOpen()) {
			updateInput();
			updatePhysics();
			updateScreen();
		}
	}
private:
	void updateInput()
	{
		sf::Event event;
		while (this->window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				this->window->close();
				return;
			}
			mouseState.handleMouseEvents(event);
		}

		if (!mouseState.rightButtonPressed() && mouseState.leftButtonPressed()) {
			auto pos = sf::Mouse::getPosition(*window.get());
			character->moveToPosition(pos.x, pos.y);
		}
		else {
			character->stopMoving();
		}
		if (mouseState.rightButtonPressed() && abilityClock.getElapsedTime().asSeconds() > abilityRate) {
			if (abilityClock.getElapsedTime().asSeconds() > abilityRate) {
				auto pos = sf::Mouse::getPosition(*window.get());
				this->activeAbility->fire(static_cast<int>(this->character->getPosition().x), static_cast<int>(this->character->getPosition().y), pos.x, pos.y);
			}
			abilityClock.restart();
		}
	}

	void updatePhysics()
	{
		if (physicsClock.getElapsedTime().asSeconds() > PhysicsConstants::timeStep) {
			world->Step(PhysicsConstants::timeStep, PhysicsConstants::velocityIterations, PhysicsConstants::positionIterations);
			activeAbility->onPhysicsUpdated();
			character->onPhysicsUpdated();
			enemies->onPhysicsUpdated();
			physicsClock.restart();
		}
	}

	void updateScreen()
	{
		this->window->clear();
		this->character->draw(*this->window.get());
		this->activeAbility->draw(*this->window.get());
		this->enemies->draw(*this->window.get());
		this->window->display();
	}

	sf::Clock abilityClock;
	sf::Clock physicsClock;

	MouseState mouseState;
	std::shared_ptr<Character> character;
	std::shared_ptr<Enemies> enemies;
	std::shared_ptr<Ability> activeAbility;
	std::shared_ptr<b2World> world;
	std::shared_ptr<sf::RenderWindow> window;

};