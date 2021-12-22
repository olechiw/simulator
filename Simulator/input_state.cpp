#include "input_state.h"

void InputState::handleMouseEvents(const sf::Event& event)
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

void InputState::handleKeyboardEvents(const sf::Event& event)
{
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        this->keys.insert(event.key.code);
    }
    else if (event.type == sf::Event::EventType::KeyReleased)
    {
        this->keys.erase(event.key.code);
    }
}

InputState::InputState(shared_ptr<sf::RenderWindow> windowIn) : window(windowIn)
{
}

void InputState::handleEvent(sf::Event event)
{
    this->handleKeyboardEvents(event);
    this->handleMouseEvents(event);
}

bool InputState::leftButtonPressed() const
{
    return this->leftButton;
}

bool InputState::rightButtonPressed() const
{
    return this->rightButton;
}

bool InputState::keyPressed(const sf::Keyboard::Key& keyCode) const
{
    return this->keys.find(keyCode) != this->keys.end();
}

sf::Vector2i InputState::getMousePosition() const
{
    return sf::Mouse::getPosition(*this->window.get());
}
