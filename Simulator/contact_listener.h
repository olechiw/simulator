#pragma once
#include <box2d/box2d.h>
#include "scene.h"

class ContactListener : public b2ContactListener
{
private:
	void BeginContact(b2Contact* contact) override {
		b2Fixture* fixture1 = contact->GetFixtureA();
		b2Fixture* fixture2 = contact->GetFixtureB();
		auto userData1 = reinterpret_cast<ObjectInfo*>(fixture1->GetBody()->GetUserData().pointer);
		auto userData2 = reinterpret_cast<ObjectInfo*>(fixture2->GetBody()->GetUserData().pointer);
		assert(userData1, "All physics bodies must have ObjectInfo attached");
		assert(userData2, "All physics bodies must have ObjectInfo attached");
		Scene.registerCollision(*userData1, *userData2);
	}
};