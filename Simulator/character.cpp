#include "character.h"

Character::Character(shared_ptr<b2World> worldIn, shared_ptr<ContactEventStore> contactEventStoreIn, int x, int y) : contactEventStore(contactEventStoreIn), world(worldIn)
{
    ObjectConfig circleConfig;
    circleConfig.collisionBits.CategoryBits = BitMasks::Character;
    circleConfig.collisionBits.MaskBits = BitMasks::EnemyBullet | BitMasks::ScreenEdge;
    circleConfig.identifier = std::make_shared<ObjectIdentifier>(ObjectType::Character);
    circleConfig.initialPosition = { x, y };
    circleConfig.elasticity = 0.f;
    
    CircleProvider circle(Character::RadiusPixels, sf::Color::White);
    this->shape = std::make_shared<Shape>(worldIn, circleConfig, circle.get());


    using ProjectileBehaviors::destroyAfterContacts;
    auto projBehavior = destroyAfterContacts(0, ObjectType::Enemy) + destroyAfterContacts(3, ObjectType::ScreenEdge);

    ObjectConfig defaultConfig;
    defaultConfig.elasticity = 1.001f;
    defaultConfig.collisionBits = {
        BitMasks::PlayerBullet,
        BitMasks::ScreenEdge | BitMasks::Enemy
    };
    shared_ptr<ShapeDefinitionProvider> triangleProvider = std::make_shared<PolygonProvider>(15.f, sf::Color::Green, 3);
    auto gunDirection = ProjectileBehaviors::spawnInDirection(30, defaultConfig, ObjectType::PlayerBullet, triangleProvider, 10.f);
    this->activeAbility = std::make_shared<ProjectileAbility>(world, ObjectConfig::CollisionBits{ BitMasks::PlayerBullet, BitMasks::Enemy | BitMasks::ScreenEdge }, this->contactEventStore, projBehavior, gunDirection);

}

void Character::handleInput(const InputState& inputState)
{
    this->handleMovement(inputState);
    this->handleAbility(inputState);
}

void Character::handleAbility(const InputState& inputState)
{
    if (inputState.leftButtonPressed() && abilityClock.getElapsedTime().asSeconds() > Character::AbilityRate) {
        auto mousePosition = inputState.getMousePosition();
        auto &bodyPosition = this->shape->getBody()->GetPosition();
        this->activeAbility->fire(
            static_cast<int>(bodyPosition.x * PhysicsConstants::pixelsPerMeter),
            static_cast<int>(bodyPosition.y * PhysicsConstants::pixelsPerMeter), 
            mousePosition.x, 
            mousePosition.y);
        abilityClock.restart();
    }
}

void Character::handleMovement(const InputState& inputState)
{
    using sf::Keyboard;
    if (!(inputState.keyPressed(Keyboard::W) || inputState.keyPressed(Keyboard::A) || inputState.keyPressed(Keyboard::S) || inputState.keyPressed(Keyboard::D)))
    {
        this->stopMoving();
        return;
    }
    auto direction = Math::angleVector(
        0, 0, -1 * inputState.keyPressed(Keyboard::A) + inputState.keyPressed(Keyboard::D), -1 * inputState.keyPressed(Keyboard::W) + inputState.keyPressed(Keyboard::S)
    );
    this->shape->getBody()->SetLinearVelocity({ direction.x * MoveSpeed, direction.y * MoveSpeed });
}

void Character::stopMoving()
{
    this->shape->getBody()->SetLinearVelocity(b2Vec2(0, 0));
}

void Character::draw(sf::RenderWindow& window) const
{
    this->shape->draw(window);
    this->activeAbility->draw(window);
}

void Character::onPhysicsUpdated()
{
    this->shape->onPhysicsUpdated();
    this->activeAbility->onPhysicsUpdated();
}
