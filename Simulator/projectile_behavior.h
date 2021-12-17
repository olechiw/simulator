#pragma once
#include <functional>
#include <unordered_map>
#include "object_identifier.h"
#include "contact_event_store.h"

// return true if the behavior destroys the object
using ProjectileBehavior = std::function<bool(const ContactEventStore::ContactEvents&)>;
using std::unordered_map;

namespace ProjectileBehaviors
{
	extern ProjectileBehavior destroyAfterContacts(int maxContacts, ObjectType type)
	{
		static unordered_map<ObjectIdentifier, unordered_map<ObjectType, int>> contactCounter;
		return [=](const ContactEventStore::ContactEvents& events) {
			if (events.beginContactEvents)
			{
				for (auto& event : *events.beginContactEvents.get())
				{
					if (event.getType() == type)
					{
						if (contactCounter[events.objectIdentifier][type] >= maxContacts)
						{
							contactCounter.erase(events.objectIdentifier);
							return true;
						}
					}
				}
			}
			if (events.endContactEvents)
			{
				for (auto& event : *events.endContactEvents.get())
				{
					if (event.getType() == type)
					{
						contactCounter[events.objectIdentifier][type]++;
						// Only count up once per iteration
						break;
					}
				}
			}
			return false;
		};
	}
}

ProjectileBehavior operator+(const ProjectileBehavior& first, const ProjectileBehavior& second)
{
	return [=](const ContactEventStore::ContactEvents& events) {
		return first(events) || second(events);
	};
}