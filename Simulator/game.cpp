#include "game.h"

Game::Game(shared_ptr<b2World> world, shared_ptr<sf::RenderWindow> window, shared_ptr<ContactEventStore> contactStore) : window(window), world(world), contactStore(contactStore)
{
	// todo: screen size somewhere else
	auto& screenSize = Configuration::getInstance().getScreenSize();
	this->character = std::make_shared<Character>(world, screenSize.x / 2, screenSize.y / 2);
	this->enemies = std::make_shared<Enemies>(world, contactStore);
}

void Game::run()
{
	while (this->window->isOpen()) {
		updateInput();
		updatePhysics();
		updateScreen();
	}
}

void Game::updateInput()
{
	sf::Event event;
	while (this->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
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

void Game::updatePhysics()
{
	if (physicsClock.getElapsedTime().asSeconds() > PhysicsConstants::timeStep) {
		world->Step(PhysicsConstants::timeStep, PhysicsConstants::velocityIterations, PhysicsConstants::positionIterations);
		activeAbility->onPhysicsUpdated();
		character->onPhysicsUpdated();
		enemies->onPhysicsUpdated();
		physicsClock.restart();
	}
}

void Game::updateScreen()
{
	this->window->clear();
	this->character->draw(*this->window.get());
	this->activeAbility->draw(*this->window.get());
	this->enemies->draw(*this->window.get());
	this->window->display();
}