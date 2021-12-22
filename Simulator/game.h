#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>

#include "character.h"
#include "input_state.h"
#include "ability.h"
#include "enemies.h"
#include "contact_event_store.h"
using std::shared_ptr;

class Game
{
public:
	Game(shared_ptr<sf::RenderWindow> window);

	void run();

private:
	void updateInput();

	void updatePhysics();

	void updateScreen();

	void createScreenEdges(unsigned int width, unsigned int height);

	sf::Clock physicsClock;

	std::shared_ptr<InputState> inputState;



	std::shared_ptr<ContactEventStore> contactEventStore;
	std::shared_ptr<ContactListener> contactListener;

	std::shared_ptr<b2World> world;

	std::shared_ptr<Character> character;
	std::shared_ptr<Enemies> enemies;

	std::shared_ptr<sf::RenderWindow> window;

};