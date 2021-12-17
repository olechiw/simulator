#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>
#include <memory>

#include "game.h"
#include "screen_edge.h"
#include "nova.h"
#include "gun.h"
#include "projectile_behavior.h"

const auto screenSize = 500.f;
const auto screenSizeInt = static_cast<unsigned int>(screenSize);
const auto speed = 10.f;
const auto attackSpeed = .1f;

using std::shared_ptr;

int main()
{
    b2Vec2 gravity(0.f, 0.f); // No gravity
    auto world = std::make_shared<b2World>(gravity);

    
    auto contactStore = std::make_shared<ContactEventStore>();
    ContactListener contactListener(contactStore);
    world->SetContactListener(&contactListener);
    
    createScreenEdges(world, screenSizeInt, screenSizeInt);

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(screenSizeInt, screenSizeInt), "Simulator");

    using ProjectileBehaviors::destroyAfterContacts;
    auto projBehavior = destroyAfterContacts(0, ObjectType::Enemy) + destroyAfterContacts(3, ObjectType::ScreenEdge);

    std::shared_ptr<Nova> ability = std::make_shared<Nova>(world, ObjectConfig::CollisionBits{ BitMasks::PlayerBullet, BitMasks::Enemy | BitMasks::ScreenEdge }, contactStore, projBehavior);

    Game game(world, window, contactStore);
    game.setAbility(ability);
    game.run();

    return 0;
}