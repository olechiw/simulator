#include "contact_listener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixture1 = contact->GetFixtureA();
	b2Fixture* fixture2 = contact->GetFixtureB();
	auto userData1 = reinterpret_cast<BodyUserData*>(fixture1->GetBody()->GetUserData().pointer);
	auto userData2 = reinterpret_cast<BodyUserData*>(fixture2->GetBody()->GetUserData().pointer);
	if (userData1 && userData1->collisionHandler) {
		userData1->collisionHandler->collideWith(fixture2);
	} 
	if (userData2 && userData2->collisionHandler) {
		userData2->collisionHandler->collideWith(fixture1);
	}
}

long long GetFixtureIdentifier(b2Fixture* fixture) {
	auto ptr = reinterpret_cast<BodyUserData*>(fixture->GetBody()->GetUserData().pointer);
	return (ptr) ? ptr->identifier : 0;
}