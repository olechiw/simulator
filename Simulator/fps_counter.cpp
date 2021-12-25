#include "fps_counter.h"

FPSCounter::FPSCounter(int posXIn, int posYIn) : frames(0), text()
{
	if (this->font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
	{
		text.setFont(this->font);
	}
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	text.setString("0");
	text.setPosition(posXIn, posYIn);
}

void FPSCounter::draw(sf::RenderWindow& window)
{
	this->frames++;
	if (this->clock.getElapsedTime().asSeconds() > FPSCounter::UpdateTime)
	{
		this->clock.restart();
		this->text.setString(std::to_string(this->frames / FPSCounter::UpdateTime));
		this->frames = 0;
	}
	window.draw(this->text);
}
