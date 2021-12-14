#pragma once
namespace Constants {
	constexpr float timeStep = 1.f / 144.f;
	constexpr float pixelsPerMeter = 100.f;
	constexpr int velocityIterations = 8;
	constexpr int positionIterations = 3;

	constexpr auto projectilesCategory = 0x002;
	constexpr auto wallCategory = 0x004;

	namespace Identifiers {
		constexpr long long Projectile = 1;
		constexpr long long Edge = 1 << 1;
		constexpr long long Character = 1 << 2;
		constexpr long long Enemy = 1 << 3;
	}
}