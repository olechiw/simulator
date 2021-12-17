#include "math.h"
namespace Math
{
	float pointAngleRadians(int x1, int y1, int x2, int y2) {
		int x = x1 - x2;
		int y = y2 - y1;
		return std::atan(static_cast<float>(y) / x);
	}

	sf::Vector2f angleVector(int x1, int y1, int x2, int y2) {
		float angle = pointAngleRadians(x1, y1, x2, y2);
		sf::Vector2f vector = {
			std::cos(angle),
			std::sin(angle)
		};
		if (x1 > x2 && vector.x > 0)
			vector.x *= -1;
		if (x1 < x2 && vector.x < 0)
			vector.x *= -1;
		if (y1 > y2 && vector.y > 0)
			vector.y *= -1;
		if (y1 < y2 && vector.y < 0)
			vector.y *= -1;
		return vector;
	}
}
