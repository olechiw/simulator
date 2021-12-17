#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include "object_identifier.h"
#include "constants.h"

using ContactEventSet = std::shared_ptr<std::unordered_set<ObjectIdentifier>>;


class ContactEventStore
{
public:
	enum class ContactType
	{
		Begin,
		End
	};

	struct ContactEvents
	{
		ObjectIdentifier objectIdentifier;
		ContactEventSet beginContactEvents;
		ContactEventSet endContactEvents;
	};

	void registerContact(ObjectIdentifier a, ObjectIdentifier b, ContactType type);

	ContactEvents popEvents(ObjectIdentifier identifier);
	void freeObject(ObjectIdentifier object);

private:
	using ContactEventMap = std::unordered_map <ObjectIdentifier, ContactEventSet>;
	ContactEventMap beginContactEvents;
	ContactEventMap endContactEvents;

};