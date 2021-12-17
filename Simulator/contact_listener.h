#pragma once
#include <box2d/box2d.h>
#include "contact_event_store.h"

class ContactListener : public b2ContactListener
{
public:
	ContactListener(std::shared_ptr<ContactEventStore> contactStore);
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
private:
	std::shared_ptr<ContactEventStore> contactStore;
	void handleContact(b2Contact* contact, ContactEventStore::ContactType type);
};