#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>

#include "character.h"
#include "input_state.h"
#include "ability.h"
#include "enemies.h"
#include "contact_event_store.h"
#include "fps_counter.h"
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

	shared_ptr<InputState> inputState;

	shared_ptr<ContactEventStore> contactEventStore;
	shared_ptr<ContactListener> contactListener;

	shared_ptr<b2World> world;

	shared_ptr<Character> character;
	shared_ptr<Enemies> enemies;

	shared_ptr<FPSCounter> fpsCounter;

	shared_ptr<sf::RenderWindow> window;

};