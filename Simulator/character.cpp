#include "character.h"
#include "math.h"
#include <iostream>

Character::Character(b2World* worldIn, int x, int y) : world(worldIn)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / PhysicsConstants::pixelsPerMeter, y / PhysicsConstants::pixelsPerMeter);

    this->body = this->world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;
    dynamicBox.m_radius = Character::RadiusPixels / PhysicsConstants::pixelsPerMeter;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.001;
    fixtureDef.filter.categoryBits = BitMasks::Character;
    fixtureDef.filter.maskBits = BitMasks::Enemy | BitMasks::ScreenEdge;

    this->body->CreateFixture(&fixtureDef);

    BodyUserData* bodyUserData = new BodyUserData {
        Identifiers::Character,
        this
    };
    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(bodyUserData);

    this->shape.setFillColor(sf::Color::White);
    this->shape.setRadius(Character::RadiusPixels);
    this->shape.setOrigin(Character::RadiusPixels, Character::RadiusPixels);
    this->onPhysicsUpdated();
}

void Character::moveToPosition(int x, int y)
{
    /*
    sf::Vector2i pos = {
        static_cast<int>(this->body->GetPosition().x * PhysicsConstants::pixelsPerMeter),
        static_cast<int>(this->body->GetPosition().y * PhysicsConstants::pixelsPerMeter)
    };
    if (abs(pos.x - x) < 3 && abs(pos.y - y) < 3) {
        this->stopMoving();
        return;
    }
    auto direction = Math::pointAngleRadians(pos.x, pos.y, x, y);
    // std::cout << pos.x - x << "\t" << pos.y - y << "\t" << std::atan(static_cast<float>(pos.y - y) / pos.x - x) * 180 / Math::pi << std::endl;
    std::cout << direction * 180.0 / Math::pi << std::endl;
    b2Vec2 speed;
    speed.x = std::cos(direction) * Character::MoveSpeed;
    speed.y = std::sin(direction) * Character::MoveSpeed;
    if (x > pos.x && speed.x < 0)
        speed.x *= -1;
    if (x < pos.x && speed.x > 0)
        speed.x *= -1;
    if (y > pos.y && speed.y < 0)
        speed.y *= -1;
    if (y < pos.y && speed.y > 0)
        speed.y *= -1;
    this->body->SetLinearVelocity(speed);
    */
    body->SetTransform(b2Vec2(x / PhysicsConstants::pixelsPerMeter, y / PhysicsConstants::pixelsPerMeter), body->GetAngle());
}

void Character::stopMoving()
{
    this->body->SetLinearVelocity(b2Vec2(0, 0));
}

const sf::Vector2f& Character::getPosition() const
{
    return this->shape.getPosition();
}

void Character::collideWith(b2Fixture* other)
{
}

Character::~Character()
{
    delete reinterpret_cast<BodyUserData*>(this->body->GetUserData().pointer);
    this->world->DestroyBody(this->body);
}

void Character::render(sf::RenderWindow& window)
{
    window.draw(this->shape);
}

void Character::onPhysicsUpdated()
{
    auto& pos = this->body->GetPosition();
    this->shape.setPosition(pos.x * PhysicsConstants::pixelsPerMeter, pos.y * PhysicsConstants::pixelsPerMeter);
}