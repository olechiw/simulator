#include "ball.h"
#include "constants.h"
#include <iostream>


Ball::Ball(b2World* worldIn, int x, int y, const sf::Color color) : world(worldIn)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / PhysicsConstants::pixelsPerMeter, y / PhysicsConstants::pixelsPerMeter);

    this->body = world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;
    dynamicBox.m_radius = Ball::RadiusPixels / PhysicsConstants::pixelsPerMeter;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.001;
    fixtureDef.filter.categoryBits = BitMasks::PlayerBullet;
    fixtureDef.filter.maskBits = BitMasks::Enemy | BitMasks::ScreenEdge | BitMasks::PlayerBullet;

    this->body->CreateFixture(&fixtureDef);

    BodyUserData* bodyUserData = new BodyUserData{
        Identifiers::Character,
        this
    };
    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(bodyUserData);

    this->shape.setFillColor(color);
    this->shape.setRadius(Ball::RadiusPixels);
    this->shape.setOrigin(Ball::RadiusPixels, Ball::RadiusPixels);
    this->onPhysicsUpdated();
}

Ball::~Ball()
{
    this->world->DestroyBody(this->body);
}

void Ball::collideWith(b2Fixture* other)
{
    auto identifier = GetFixtureIdentifier(other);
    if (identifier == Identifiers::ScreenEdge) {
        this->destroy();
    }
}

b2Body* Ball::getBody()
{
    return this->body;
}


void Ball::render(sf::RenderWindow& window)
{
    window.draw(this->shape);
}

void Ball::onPhysicsUpdated()
{
    auto& pos = this->body->GetPosition();
    this->shape.setPosition(pos.x * PhysicsConstants::pixelsPerMeter, pos.y * PhysicsConstants::pixelsPerMeter);
}
