#include "game.h"

Game::Game(shared_ptr<sf::RenderWindow> windowIn) : window(windowIn)
{
	// todo: screen size somewhere else
	auto& screenSize = Configuration::getInstance().getScreenSize();

	b2Vec2 gravity(0.f, 0.f); // No gravity
	this->world = std::make_shared<b2World>(gravity);
	this->contactEventStore = std::make_shared<ContactEventStore>();
	this->contactListener = std::make_shared<ContactListener>(contactEventStore);
	this->world->SetContactListener(this->contactListener.get());
	this->createScreenEdges(screenSize.x, screenSize.y);

	this->character = std::make_shared<Character>(world, contactEventStore, screenSize.x / 2, screenSize.y / 2);
	this->enemies = std::make_shared<Enemies>(world, contactEventStore);

	this->fpsCounter = std::make_shared<FPSCounter>(0, 0);

	this->inputState = std::make_shared<InputState>(this->window);
}

void Game::createScreenEdges(unsigned int width, unsigned int height) {
	b2BodyDef edgeBodyDefinition;
	edgeBodyDefinition.position.Set(0.f, 0.f);
	b2Body* edgeBody = world->CreateBody(&edgeBodyDefinition);
	edgeBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(new ObjectIdentifier(ObjectType::ScreenEdge));
	b2EdgeShape edgeShape;

	b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
	b2Vec2 lowerRightCorner = b2Vec2(width / PhysicsConstants::pixelsPerMeter, 0);
	b2Vec2 upperLeftCorner = b2Vec2(0, height / PhysicsConstants::pixelsPerMeter);
	b2Vec2 upperRightCorner = b2Vec2(width / PhysicsConstants::pixelsPerMeter, height / PhysicsConstants::pixelsPerMeter);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &edgeShape;
	fixtureDef.density = 0;
	fixtureDef.filter.categoryBits = BitMasks::ScreenEdge;
	fixtureDef.filter.maskBits = BitMasks::MatchAll;
	edgeShape.SetTwoSided(lowerLeftCorner, lowerRightCorner);
	edgeBody->CreateFixture(&fixtureDef);
	edgeShape.SetTwoSided(lowerRightCorner, upperRightCorner);
	edgeBody->CreateFixture(&fixtureDef);
	edgeShape.SetTwoSided(upperRightCorner, upperLeftCorner);
	edgeBody->CreateFixture(&fixtureDef);
	edgeShape.SetTwoSided(upperLeftCorner, lowerLeftCorner);
	edgeBody->CreateFixture(&fixtureDef);
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
		inputState->handleEvent(event);
	}
	this->character->handleInput(*this->inputState.get());
}

void Game::updatePhysics()
{
	if (physicsClock.getElapsedTime().asSeconds() > PhysicsConstants::timeStep) {
		world->Step(PhysicsConstants::timeStep, PhysicsConstants::velocityIterations, PhysicsConstants::positionIterations);
		character->onPhysicsUpdated();
		enemies->onPhysicsUpdated();
		physicsClock.restart();
	}
}

void Game::updateScreen()
{
	this->window->clear();
	this->character->draw(*this->window.get());
	this->enemies->draw(*this->window.get());
	this->fpsCounter->draw(*this->window.get());
	this->window->display();
}