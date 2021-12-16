#include "character.h"
#include "math.h"
#include "body_user_data.h"
#include <iostream>

Character::Character(std::shared_ptr<b2World> worldIn, std::shared_ptr<CollisionHandler> collisionHandler, int x, int y) : world(worldIn)
{
    ObjectConfig circleConfig;
    circleConfig.Collision.CategoryBits = BitMasks::Character;
    circleConfig.Collision.MaskBits = BitMasks::EnemyBullet | BitMasks::ScreenEdge;
    circleConfig.Identifier = ObjectTypes::Character;
    circleConfig.CollisionHandler = collisionHandler;
    circleConfig.InitialPosition = { x, y };
    circleConfig.Elasticity = 0.f;
    this->shape = std::shared_ptr<Circle>(new Circle(worldIn, circleConfig, Character::RadiusPixels, sf::Color::White));
    Scene::getInstance().addObject(this->shape);
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
    this->shape->getBody()->SetLinearVelocity(speed);
}

void Character::stopMoving()
{
    this->shape->getBody()->SetLinearVelocity(b2Vec2(0, 0));
}

const sf::Vector2f& Character::getPosition() const
{
    return this->shape->getPosition();
}