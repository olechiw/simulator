#pragma once
#include "box2d/box2d.h"

class CollisionHandler
{
public:
	virtual ~CollisionHandler() {}
	CollisionHandler(bool trackCollision, long long identifier);
	virtual void collideWith(b2Fixture* otherBody);
	const long long identifier;
	const bool trackCollision;
};

extern long long GetFixtureIdentifier(b2Fixture* fixture);

class ContactListener : public b2ContactListener
{
private:
	void BeginContact(b2Contact* contact) override;
};