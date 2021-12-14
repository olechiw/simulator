#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>

#include "constants.h"
#include "ball.h"

const auto screenSize = 500.f;
const auto speed = 10.f;
const auto attackSpeed = .1f;

void createScreenEdges(b2World& world) {
    b2BodyDef edgeBodyDefinition;
    edgeBodyDefinition.position.Set(0.f, 0.f);
    b2Body* edgeBody = world.CreateBody(&edgeBodyDefinition);
    b2EdgeShape edgeShape;

    b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
    b2Vec2 lowerRightCorner = b2Vec2(screenSize / Constants::pixelsPerMeter, 0);
    b2Vec2 upperLeftCorner = b2Vec2(0, screenSize / Constants::pixelsPerMeter);
    b2Vec2 upperRightCorner = b2Vec2(screenSize / Constants::pixelsPerMeter, screenSize / Constants::pixelsPerMeter);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &edgeShape;
    fixtureDef.density = 0;
    fixtureDef.filter.categoryBits = Constants::projectilesCategory;
    fixtureDef.filter.maskBits = Constants::projectilesCategory;
    edgeShape.SetTwoSided(lowerLeftCorner, lowerRightCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(lowerRightCorner, upperRightCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(upperRightCorner, upperLeftCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(upperLeftCorner, lowerLeftCorner);
    edgeBody->CreateFixture(&fixtureDef);
}

const std::vector<sf::Color> colors = {
    sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::White, sf::Color::Magenta, sf::Color::Yellow
};

void fire(std::vector<std::shared_ptr<Ball>>& balls, b2World& world, sf::RenderWindow& window) {
    auto pos = sf::Mouse::getPosition(window);
    balls.push_back(std::make_shared<Ball>(&world, pos.x + 10, pos.y + 10, colors[std::rand() % colors.size()]));
    balls.back()->getBody()->ApplyForceToCenter(b2Vec2(speed, speed), true);
    balls.push_back(std::make_shared<Ball>(&world, pos.x - 10, pos.y + 10, colors[std::rand() % colors.size()]));
    balls.back()->getBody()->ApplyForceToCenter(b2Vec2(-speed, speed), true);
    balls.push_back(std::make_shared<Ball>(&world, pos.x - 10, pos.y - 10, colors[std::rand() % colors.size()]));
    balls.back()->getBody()->ApplyForceToCenter(b2Vec2(-speed, -speed), true);
    balls.push_back(std::make_shared<Ball>(&world, pos.x + 10, pos.y - 10, colors[std::rand() % colors.size()]));
    balls.back()->getBody()->ApplyForceToCenter(b2Vec2(speed, -speed), true);
}

int main()
{
    b2Vec2 gravity(0.f, 0.f); // No gravity
    b2World world(gravity);
    
    createScreenEdges(world);

    std::vector<std::shared_ptr<Ball>> balls;

    sf::RenderWindow window(sf::VideoMode(screenSize, screenSize), "Simulator");

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
                    balls.clear();
                }
                else {
                    if (fireClock.getElapsedTime().asSeconds() > attackSpeed) {
                        fire(balls, world, window);
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
            fire(balls, world, window);
            fireClock.restart();
        }

        if (physicsClock.getElapsedTime().asSeconds() > Constants::timeStep) {
            world.Step(Constants::timeStep, Constants::velocityIterations, Constants::positionIterations);
            physicsClock.restart();
        }
        window.clear();
        for (auto& ball : balls) {
            window.draw(ball->getShape());
        }
        window.display();
        frameNumber++;
        if (fpsClock.getElapsedTime().asSeconds() > 1.f) {
            std::cout << frameNumber / fpsClock.getElapsedTime().asSeconds() << std::endl;
            fpsClock.restart();
            frameNumber = 0;
        }
    }

    return 0;
}