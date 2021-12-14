#include "ball.h"
#include "constants.h"
#include <iostream>


Ball::Ball(b2World* worldIn, unsigned int x, unsigned int y, const sf::Color color) : world(worldIn)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / Constants::pixelsPerMeter, y / Constants::pixelsPerMeter);

    this->body = world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;
    dynamicBox.m_radius = Ball::RadiusPixels / Constants::pixelsPerMeter;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.001;
    fixtureDef.filter.categoryBits = Constants::projectilesCategory;
    fixtureDef.filter.maskBits = Constants::projectilesCategory;

    this->body->CreateFixture(&fixtureDef);

    this->shape.setFillColor(color);
    this->shape.setRadius(Ball::RadiusPixels);
    this->shape.setOrigin(Ball::RadiusPixels, Ball::RadiusPixels);
}

Ball::~Ball()
{
    this->world->DestroyBody(this->body);
}

b2Body* Ball::getBody()
{
    return this->body;
}

const sf::CircleShape& Ball::getShape()
{
    auto& pos = this->body->GetPosition();
    // std::cout << pos.x << " " << pos.y << std::endl;
    this->shape.setPosition(pos.x * Constants::pixelsPerMeter, pos.y * Constants::pixelsPerMeter);
    return this->shape;
}
