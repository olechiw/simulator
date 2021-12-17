#include "character.h"
#include "math.h"
#include <iostream>

Character::Character(std::shared_ptr<b2World> worldIn, int x, int y) : world(worldIn)
{
    ObjectConfig circleConfig;
    circleConfig.collisionBits.CategoryBits = BitMasks::Character;
    circleConfig.collisionBits.MaskBits = BitMasks::EnemyBullet | BitMasks::ScreenEdge;
    circleConfig.identifier = new ObjectIdentifier(ObjectType::Character);
    circleConfig.initialPosition = { static_cast<float>(x), static_cast<float>(y) };
    circleConfig.elasticity = 0.f;
    this->shape = std::make_shared<Shape>(worldIn, circleConfig, MakePolygon(Character::RadiusPixels, sf::Color::White, 3));
}

void Character::moveToPosition(int x, int y)
{
    sf::Vector2i pos = {
        static_cast<int>(this->shape->getBody()->GetPosition().x * PhysicsConstants::pixelsPerMeter),
        static_cast<int>(this->shape->getBody()->GetPosition().y * PhysicsConstants::pixelsPerMeter)
    };
    if (abs(pos.x - x) < 3 && abs(pos.y - y) < 3) {
        this->stopMoving();
        return;
    }
    auto direction = Math::angleVector(pos.x, pos.y, x, y);
    direction.x = direction.x * Character::MoveSpeed;
    direction.y = direction.y * Character::MoveSpeed;
    this->shape->getBody()->SetLinearVelocity({ direction.x, direction.y });
}

void Character::stopMoving()
{
    this->shape->getBody()->SetLinearVelocity(b2Vec2(0, 0));
}

void Character::draw(sf::RenderWindow& window) const
{
    this->shape->draw(window);
}

const sf::Vector2f& Character::getPosition() const
{
    return this->shape->getPosition();
}

void Character::onPhysicsUpdated()
{
    this->shape->onPhysicsUpdated();
}
