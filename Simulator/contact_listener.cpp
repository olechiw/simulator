#include "contact_listener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixture1 = contact->GetFixtureA();
	b2Fixture* fixture2 = contact->GetFixtureB();
	auto userData1 = reinterpret_cast<CollisionHandler*>(fixture1->GetBody()->GetUserData().pointer);
	auto userData2 = reinterpret_cast<CollisionHandler*>(fixture2->GetBody()->GetUserData().pointer);
	if (userData1 && userData1->trackCollision) {
		userData1->collideWith(fixture2);
	} 
	if (userData2 && userData2->trackCollision) {
		userData2->collideWith(fixture1);
	}
}

long long GetFixtureIdentifier(b2Fixture* fixture) {
	auto ptr = reinterpret_cast<CollisionHandler*>(fixture->GetBody()->GetUserData().pointer);
	return (ptr) ? ptr->identifier : 0;
}

CollisionHandler::CollisionHandler(bool trackCollisionIn, long long identifierIn): trackCollision(trackCollisionIn), identifier(identifierIn)
{

}

void CollisionHandler::collideWith(b2Fixture*) { }
