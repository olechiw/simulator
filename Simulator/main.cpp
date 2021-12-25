#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <box2d/box2d.h>
#include <memory>

#include "game.h"
using std::shared_ptr;

int main()
{
    Configuration::getInstance().setScreenSize({ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height });

    shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Simulator");
    
    Game game(window);
    game.run();

    return 0;
}