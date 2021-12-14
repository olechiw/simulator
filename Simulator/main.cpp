#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>

#include "constants.h"
#include "contact_listener.h"
#include "ball.h"
#include "screen_edge.h"
#include "scene.h"

const auto screenSize = 500.f;
const auto speed = 10.f;
const auto attackSpeed = .1f;

const std::vector<sf::Color> colors = {
    sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::White, sf::Color::Magenta, sf::Color::Yellow
};

void fire(b2World& world, sf::RenderWindow& window) {
    auto& scene = Scene::getInstance();
    auto pos = sf::Mouse::getPosition(window);

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

    float frameNumber = 0;

    bool mousePressed = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Right) {
                    mousePressed = false;
                    scene.clear();
                }
                else {
                    if (fireClock.getElapsedTime().asSeconds() > attackSpeed) {
                        fire(world, window);
                        fireClock.restart();
                    }
                    mousePressed = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mousePressed = false;
            }
        }
        if (mousePressed && fireClock.getElapsedTime().asSeconds() > attackSpeed) {
            fire(world, window);
            fireClock.restart();
        }

        if (physicsClock.getElapsedTime().asSeconds() > Constants::timeStep) {
            world.Step(Constants::timeStep, Constants::velocityIterations, Constants::positionIterations);
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