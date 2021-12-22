#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>

using std::unordered_set;
using std::shared_ptr;

class InputState
{
public:
	InputState(shared_ptr<sf::RenderWindow> window);
	void handleEvent(sf::Event event);
	bool leftButtonPressed() const;
	bool rightButtonPressed() const;
	bool keyPressed(const sf::Keyboard::Key& keyCode) const;
	sf::Vector2i getMousePosition() const;
private:
	bool leftButton = false;
	bool rightButton = false;
	unordered_set<sf::Keyboard::Key> keys;
	shared_ptr <sf::RenderWindow> window;

	void handleMouseEvents(const sf::Event& event);
	void handleKeyboardEvents(const sf::Event& event);
};

