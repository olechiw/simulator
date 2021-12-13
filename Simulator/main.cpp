#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>

#include "constants.h"
#include "ball.h"

const auto screenSize = 500.f;

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
    fixtureDef.filter.categoryBits = Constants::wallCategory;
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

int main()
{
    b2Vec2 gravity(0.f, 0.f); // No gravity
    b2World world(gravity);
    
    createScreenEdges(world);

    std::vector<Ball> balls;
    std::vector<sf::Color> colors = {
        sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::White, sf::Color::Magenta, sf::Color::Yellow
    };

    sf::RenderWindow window(sf::VideoMode(screenSize, screenSize), "Simulator");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                auto pos = event.mouseButton;
                balls.emplace_back(world, pos.x, pos.y, colors[std::rand() % colors.size()]);
                balls.back().getBody()->ApplyForceToCenter(b2Vec2(3, 3), true);
                balls.emplace_back(world, pos.x, pos.y, colors[std::rand() % colors.size()]);
                balls.back().getBody()->ApplyForceToCenter(b2Vec2(-3, 3), true);
                balls.emplace_back(world, pos.x, pos.y, colors[std::rand() % colors.size()]);
                balls.back().getBody()->ApplyForceToCenter(b2Vec2(-3, -3), true);
                balls.emplace_back(world, pos.x, pos.y, colors[std::rand() % colors.size()]);
                balls.back().getBody()->ApplyForceToCenter(b2Vec2(3, -3), true);
            }
        }

        world.Step(Constants::timeStep, Constants::velocityIterations, Constants::positionIterations);
        window.clear();
        for (Ball& ball : balls) {
            auto& shape = ball.getShape();
            // std::cout << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
            window.draw(ball.getShape());
        }
        window.display();
    }

    return 0;
}