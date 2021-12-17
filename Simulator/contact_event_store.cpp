#include "contact_event_store.h"

void ContactEventStore::registerContact(ObjectIdentifier a, ObjectIdentifier b, ContactType type) {
	auto& collisions = type == ContactType::Begin ? this->beginContactEvents : this->endContactEvents;
	if (!collisions[a])
		collisions[a] = std::make_shared<std::unordered_set<ObjectIdentifier>>();
	if (!collisions[b])
		collisions[b] = std::make_shared<std::unordered_set<ObjectIdentifier>>();

	collisions[a]->insert(b);
	collisions[b]->insert(a);
}

ContactEventStore::ContactEvents ContactEventStore::popEvents(ObjectIdentifier identifier)
{
	ContactEvents result = {
		identifier,
		this->beginContactEvents[identifier],
		this->endContactEvents[identifier]
	};
	this->beginContactEvents.erase(identifier);
	this->endContactEvents.erase(identifier);
	return result;
}

void ContactEventStore::freeObject(ObjectIdentifier object) {
	this->beginContactEvents.erase(object);
	this->endContactEvents.erase(object);
}