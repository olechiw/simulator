#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <box2d/box2d.h>
#include <memory>

#include "game.h"
#include "screen_edge.h"
#include "nova.h"
#include "gun.h"
#include "configuration.h"
#include "projectile_behavior.h"

using std::shared_ptr;

int main()
{
    b2Vec2 gravity(0.f, 0.f); // No gravity
    auto world = std::make_shared<b2World>(gravity);

    Configuration::getInstance().setScreenSize({ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height });
    
    auto contactStore = std::make_shared<ContactEventStore>();
    ContactListener contactListener(contactStore);
    world->SetContactListener(&contactListener);
    auto& screenSize = Configuration::getInstance().getScreenSize();
    createScreenEdges(world, screenSize.x, screenSize.y);

    shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Simulator", sf::Style::None);

    using ProjectileBehaviors::destroyAfterContacts;
    auto projBehavior = destroyAfterContacts(0, ObjectType::Enemy) + destroyAfterContacts(3, ObjectType::ScreenEdge);

    shared_ptr<Nova> ability = std::make_shared<Nova>(world, ObjectConfig::CollisionBits{ BitMasks::PlayerBullet, BitMasks::Enemy | BitMasks::ScreenEdge }, contactStore, projBehavior);

    Game game(world, window, contactStore);
    game.setAbility(ability);
    game.run();

    return 0;
}