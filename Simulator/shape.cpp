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

    this->body->GetUserData().pointer = reinterpret_cast<uintptr_t>(objectConfig.identifier);

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

void Shape::destroy()
{
    this->destroyed = true;
    delete reinterpret_cast<ObjectIdentifier*>(this->body->GetUserData().pointer);
    this->world->DestroyBody(this->body);
}

bool Shape::isDestroyed() const
{
    return this->destroyed;
}


void Shape::draw(sf::RenderWindow& window) const
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

ShapeDefinition MakeCircle(float radiusPixels, sf::Color color)
{
    ShapeDefinition result = {
        std::make_shared<sf::CircleShape>(radiusPixels),
        std::make_shared<b2CircleShape>()
    };
    result.shape->setFillColor(color);
    result.shape->setOrigin(radiusPixels, radiusPixels);
    result.b2Shape->m_radius = radiusPixels / PhysicsConstants::pixelsPerMeter;
    return result;
}

ShapeDefinition MakePolygon(float radius, sf::Color color, int size)
{
    auto polygon = std::make_shared<b2PolygonShape>();
    ShapeDefinition result = {
        std::make_shared<sf::CircleShape>(radius, size),
        polygon
    };
    result.shape->setFillColor(color);
    result.shape->setOrigin(radius, radius);
    
    b2Vec2* vertices = new b2Vec2[size];
    for (int i = 0; i < size; ++i)
    {
        float angle = (2.f * i * static_cast<float>(Math::pi) / size) + Math::pi / 2.f;
        vertices[i] = {
            radius * std::cos(angle) / PhysicsConstants::pixelsPerMeter,
            radius * std::sin(angle) / PhysicsConstants::pixelsPerMeter
        };
    }
    polygon->Set(vertices, size);
    delete[] vertices;
    return result;
}
