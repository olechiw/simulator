#pragma once
class Simulated
{
public:
	virtual ~Simulated() = default;
	virtual void onPhysicsUpdated() = 0;
};