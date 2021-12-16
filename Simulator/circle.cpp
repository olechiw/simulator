#include "circle.h"

Circle::Circle(std::shared_ptr<b2World> worldIn, const ObjectConfig& objectConfig, float radiusPixels, const sf::Color color) : world(worldIn)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(objectConfig.InitialPosition.x / PhysicsConstants::pixelsPerMeter, objectConfig.InitialPosition.y / PhysicsConstants::pixelsPerMeter);

    this->body = world->CreateBody(&bodyDef);

    b2CircleShape dynamicBox;
    dynamicBox.m_radius = radiusPixels / PhysicsConstants::pixelsPerMeter;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = objectConfig.Elasticity;
    fixtureDef.filter.categoryBits = objectConfig.Collision.CategoryBits;
    fixtureDef.filter.maskBits = objectConfig.Collision.MaskBits;

    this->body->CreateFixture(&fixtureDef);

    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(objectConfig.Info);

    this->shape.setFillColor(color);
    this->shape.setRadius(radiusPixels);
    this->shape.setOrigin(radiusPixels, radiusPixels);
    this->onPhysicsUpdated();
}

Circle::~Circle()
{
    if (!this->isDestroyed()) {
        this->destroy();
    }
}

b2Body* Circle::getBody()
{
    return this->body;
}

const sf::Vector2f& Circle::getPosition() const
{
    return this->shape.getPosition();
}

void Circle::destroy()
{
    this->destroyed = true;
    delete reinterpret_cast<ObjectIdentifier*>(this->body->GetUserData().pointer);
    this->world->DestroyBody(this->body);
}

bool Circle::isDestroyed() const
{
    return this->destroyed;
}


void Circle::draw(sf::RenderWindow& window) const
{
    window.draw(this->shape);
}

void Circle::onPhysicsUpdated()
{
    auto& pos = this->body->GetPosition();
    this->shape.setPosition(pos.x * PhysicsConstants::pixelsPerMeter, pos.y * PhysicsConstants::pixelsPerMeter);
}