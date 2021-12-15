#pragma once
namespace PhysicsConstants {
	constexpr float timeStep = 1.f / 144.f;
	constexpr float pixelsPerMeter = 100.f;
	constexpr int velocityIterations = 8;
	constexpr int positionIterations = 3;
}

namespace Identifiers {
		constexpr long long Projectile = 1;
		constexpr long long ScreenEdge = 1 << 1;
		constexpr long long Character = 1 << 2;
		constexpr long long Enemy = 1 << 3;
}

namespace BitMasks {
	constexpr int16_t PlayerBullet = 1;
	constexpr int16_t EnemyBullet = 1 << 1;
	constexpr int16_t Character = 1 << 2;
	constexpr int16_t Enemy = 1 << 3;
	constexpr int16_t ScreenEdge = 1 << 4;

	constexpr int16_t MatchAll = static_cast<int16_t>((1 << 16) - 1);
}