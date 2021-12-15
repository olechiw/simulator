#pragma once
#include "box2d/box2d.h"



class CollisionHandler
{
public:
	virtual ~CollisionHandler() = default;
	virtual void collideWith(b2Fixture* other) = 0;
};

struct BodyUserData
{
	const long long identifier;
	CollisionHandler* const collisionHandler;
};

extern long long GetFixtureIdentifier(b2Fixture* fixture);

class ContactListener : public b2ContactListener
{
private:
	void BeginContact(b2Contact* contact) override;
};