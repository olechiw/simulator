#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>

const auto screenSize = 500.f;
const auto circleRadius = 10.f;

constexpr int32 velocityIterations = 8;
constexpr int32 positionIterations = 3;
constexpr float timeStep = 1.f / 60.f;
constexpr float pixelsPerMeter = 100.f;


int main()
{
    b2Vec2 gravity(0.f, 0.f); // No gravity
    b2World world(gravity);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(250.f / pixelsPerMeter, 250.f / pixelsPerMeter);
    b2Body* body = world.CreateBody(&bodyDef);
    b2CircleShape dynamicBox;
    dynamicBox.m_radius = circleRadius / pixelsPerMeter;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.001f;
    body->CreateFixture(&fixtureDef);

    
    
    b2BodyDef edgeBodyDefinition;
    edgeBodyDefinition.position.Set(0.f, 0.f);
    b2Body* edgeBody = world.CreateBody(&edgeBodyDefinition);
    b2EdgeShape edgeShape;

    b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
    b2Vec2 lowerRightCorner = b2Vec2(screenSize / pixelsPerMeter, 0);
    b2Vec2 upperLeftCorner = b2Vec2(0, screenSize / pixelsPerMeter);
    b2Vec2 upperRightCorner = b2Vec2(screenSize / pixelsPerMeter, screenSize / pixelsPerMeter);
    
    edgeShape.SetTwoSided(lowerLeftCorner, lowerRightCorner);
    edgeBody->CreateFixture(&edgeShape, 0);
    edgeShape.SetTwoSided(lowerRightCorner, upperRightCorner);
    edgeBody->CreateFixture(&edgeShape, 0);
    edgeShape.SetTwoSided(upperRightCorner, upperLeftCorner);
    edgeBody->CreateFixture(&edgeShape, 0);
    edgeShape.SetTwoSided(upperLeftCorner, lowerLeftCorner);
    edgeBody->CreateFixture(&edgeShape, 0);
    

    std::cout << upperRightCorner.x << " " << upperRightCorner.y << std::endl;

    
    

    b2Vec2 initialForce(5.f, 4.f);
    body->ApplyForceToCenter(initialForce, false);

    sf::RenderWindow window(sf::VideoMode(screenSize, screenSize), "Simulator");
    sf::CircleShape circleImage;
    circleImage.setFillColor(sf::Color::Red);
    circleImage.setRadius(circleRadius);
    circleImage.setOrigin(circleRadius, circleRadius);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();

        std::cout << position.x * pixelsPerMeter << " " << position.y * pixelsPerMeter << std::endl;

        circleImage.setPosition(position.x * pixelsPerMeter, screenSize - (position.y * pixelsPerMeter));

        window.clear();
        window.draw(circleImage);
        window.display();
    }

    world.DestroyBody(body);
    // world.DestroyBody(edgeBody);

    return 0;
}