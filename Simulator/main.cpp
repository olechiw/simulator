#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>

#include "constants.h"
#include "contact_listener.h"
#include "ball.h"
#include "screen_edge.h"
#include "scene.h"
#include "mouse_state.h"
#include "character.h"

const auto screenSize = 500.f;
const auto speed = 10.f;
const auto attackSpeed = .1f;

const std::vector<sf::Color> colors = {
    sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::Magenta, sf::Color::Yellow
};

void fire(b2World& world, sf::RenderWindow& window, const Character &character) {
    auto& scene = Scene::getInstance();
    const auto& pos = character.getPosition();

    auto ball = std::make_shared<Ball>(&world, pos.x + 10, pos.y + 10, colors[std::rand() % colors.size()]);
    scene.addObject(ball);
    ball->getBody()->ApplyForceToCenter(b2Vec2(-speed, speed), true);

    ball = std::make_shared<Ball>(&world, pos.x - 10, pos.y + 10, colors[std::rand() % colors.size()]);
    scene.addObject(ball);
    ball->getBody()->ApplyForceToCenter(b2Vec2(speed, speed), true);

    ball = std::make_shared<Ball>(&world, pos.x - 10, pos.y - 10, colors[std::rand() % colors.size()]);
    scene.addObject(ball);
    ball->getBody()->ApplyForceToCenter(b2Vec2(-speed, -speed), true);

    ball = std::make_shared<Ball>(&world, pos.x + 10, pos.y - 10, colors[std::rand() % colors.size()]);
    scene.addObject(ball);
    ball->getBody()->ApplyForceToCenter(b2Vec2(speed, -speed), true);
}

int main()
{
    auto& scene = Scene::getInstance();
    b2Vec2 gravity(0.f, 0.f); // No gravity
    b2World world(gravity);

    ContactListener contactListener;
    world.SetContactListener(&contactListener);
    
    createScreenEdges(&world, screenSize, screenSize);

    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(screenSize), static_cast<unsigned int>(screenSize)), "Simulator");

    sf::Clock fireClock;

    sf::Clock physicsClock;

    sf::Clock fpsClock;

    MouseState mouseState;

    auto character = std::make_shared<Character>(&world, 250, 250);
    scene.addObject(character);

    float frameNumber = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            mouseState.handleMouseEvents(event);
        }
        if (mouseState.leftButtonPressed()) {
            auto pos = sf::Mouse::getPosition(window);
            character->moveToPosition(pos.x, pos.y);
        }
        else {
            character->stopMoving();
        }
        if (mouseState.rightButtonPressed() && fireClock.getElapsedTime().asSeconds() > attackSpeed) {
            fire(world, window, *character.get());
            fireClock.restart();
        }

        if (physicsClock.getElapsedTime().asSeconds() > PhysicsConstants::timeStep) {
            world.Step(PhysicsConstants::timeStep, PhysicsConstants::velocityIterations, PhysicsConstants::positionIterations);
            scene.dispatchPhysicsUpdate();
            physicsClock.restart();
        }
        window.clear();
        scene.render(window);
        window.display();



        frameNumber++;
        if (fpsClock.getElapsedTime().asSeconds() > 1.f) {
            std::cout << frameNumber / fpsClock.getElapsedTime().asSeconds() << std::endl;
            fpsClock.restart();
            frameNumber = 0;
        }
    }
    scene.clear();

    return 0;
}