#include "math.h"
namespace Math
{
	float pointAngleRadians(int x1, int y1, int x2, int y2) {
		int x = x1 - x2;
		int y = y2 - y1;
		return std::atan(static_cast<float>(y) / x);
	}
}
