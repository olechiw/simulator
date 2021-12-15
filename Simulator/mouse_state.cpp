#include "mouse_state.h"
#include <iostream>
void MouseState::handleMouseEvents(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return;
    }
    bool clicked = (event.type == sf::Event::MouseButtonPressed);

    if (event.mouseButton.button == sf::Mouse::Button::Right) {
        this->rightButton = clicked;
    }
    else if (event.mouseButton.button == sf::Mouse::Button::Left) {
        this->leftButton = clicked;
    }
}

bool MouseState::leftButtonPressed()
{
    return this->leftButton;
}

bool MouseState::rightButtonPressed()
{
    return this->rightButton;
}
