#include "shape.h"

Shape::Shape(std::shared_ptr<b2World> worldIn, const ObjectConfig& objectConfig, const ShapeDefinition& shapeDefinition) : world(worldIn)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(objectConfig.initialPosition.x / PhysicsConstants::pixelsPerMeter, objectConfig.initialPosition.y / PhysicsConstants::pixelsPerMeter);

    this->body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = shapeDefinition.b2Shape.get();
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = objectConfig.elasticity;
    fixtureDef.filter.categoryBits = objectConfig.collisionBits.CategoryBits;
    fixtureDef.filter.maskBits = objectConfig.collisionBits.MaskBits;
    this->body->CreateFixture(&fixtureDef);

    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(objectConfig.identifier.get());
    this->objectIdentifier = objectConfig.identifier;

    this->shape = shapeDefinition.shape;
    this->onPhysicsUpdated();
}

Shape::~Shape()
{
    if (!this->isDestroyed()) {
        this->destroy();
    }
}

b2Body* Shape::getBody()
{
    return this->body;
}

const sf::Vector2f& Shape::getPosition() const
{
    return this->shape->getPosition();
}

const ObjectIdentifier& Shape::getObjectIdentifier() const
{
    return *this->objectIdentifier.get();
}

void Shape::destroy()
{
    this->destroyed = true;
    this->world->DestroyBody(this->body);
}

bool Shape::isDestroyed() const
{
    return this->destroyed;
}


void Shape::draw(sf::RenderWindow& window)
{
    window.draw(*this->shape.get());
}

void Shape::onPhysicsUpdated()
{
    auto& pos = this->body->GetPosition();
    this->shape->setPosition(pos.x * PhysicsConstants::pixelsPerMeter, pos.y * PhysicsConstants::pixelsPerMeter);
    auto angle = this->body->GetAngle();
    this->shape->setRotation(angle * 180.f / static_cast<float>(Math::pi));
}