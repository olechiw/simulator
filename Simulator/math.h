#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
namespace Math
{
	constexpr float pi = 3.14159265358979323846f;
	extern float pointAngleRadians(int x1, int y1, int x2, int y2);
	extern sf::Vector2f angleVector(int x1, int y1, int x2, int y2);
}