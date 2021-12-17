#include "character.h"
#include "math.h"
#include <iostream>

Character::Character(std::shared_ptr<b2World> worldIn, int x, int y) : world(worldIn)
{
    ObjectConfig circleConfig;
    circleConfig.Collision.CategoryBits = BitMasks::Character;
    circleConfig.Collision.MaskBits = BitMasks::EnemyBullet | BitMasks::ScreenEdge;
    circleConfig.Info = new ObjectIdentifier(ObjectType::Character);
    circleConfig.InitialPosition = { static_cast<float>(x), static_cast<float>(y) };
    circleConfig.Elasticity = 0.f;
    this->shape = std::make_shared<Shape>(worldIn, circleConfig, MakeCircle(Character::RadiusPixels, sf::Color::White));
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
    auto direction = Math::pointAngleRadians(pos.x, pos.y, x, y);
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
    this->shape->getBody()->SetLinearVelocity(speed);
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
