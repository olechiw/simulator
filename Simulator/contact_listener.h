#pragma once
#include <box2d/box2d.h>
#include "scene.h"

class ContactListener : public b2ContactListener
{
private:
	void BeginContact(b2Contact* contact) override {
		b2Fixture* fixture1 = contact->GetFixtureA();
		b2Fixture* fixture2 = contact->GetFixtureB();
		auto userData1 = reinterpret_cast<ObjectIdentifier*>(fixture1->GetBody()->GetUserData().pointer);
		auto userData2 = reinterpret_cast<ObjectIdentifier*>(fixture2->GetBody()->GetUserData().pointer);
		assert(userData1);
		assert(userData2);
		Scene.registerCollision(*userData1, *userData2);
	}
};