#include "contact_listener.h"

ContactListener::ContactListener(std::shared_ptr<ContactEventStore> contactStoreIn) : contactStore(contactStoreIn)
{
}

void ContactListener::BeginContact(b2Contact* contact) {
	this->handleContact(contact, ContactEventStore::ContactType::Begin);
}

void ContactListener::EndContact(b2Contact* contact)
{
	this->handleContact(contact, ContactEventStore::ContactType::End);
}

void ContactListener::handleContact(b2Contact* contact, ContactEventStore::ContactType type)
{
	b2Fixture* fixture1 = contact->GetFixtureA();
	b2Fixture* fixture2 = contact->GetFixtureB();
	auto userData1 = reinterpret_cast<ObjectIdentifier*>(fixture1->GetBody()->GetUserData().pointer);
	auto userData2 = reinterpret_cast<ObjectIdentifier*>(fixture2->GetBody()->GetUserData().pointer);
	assert(userData1);
	assert(userData2);
	this->contactStore->registerContact(*userData1, *userData2, type);
}
