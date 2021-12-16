#pragma once
#include <unordered_set>
#include "constants.h"


class ObjectIdentifier {
public:
	ObjectIdentifier(const ObjectType::ObjectType& typeIn)
	{
		identifier = NextIdentifier++;
		this->type = typeIn;
	}

	const ObjectType::ObjectType& getType() const {
		return this->type;
	}
	
	ObjectIdentifier &operator=(ObjectIdentifier& other) {
		this->identifier = other.identifier;
	}

	bool operator==(const ObjectIdentifier& other) const {
		return other.identifier == this->identifier;
	}

	size_t getIdentifier() const {
		return this->identifier;
	}
private:
	static size_t NextIdentifier;
	ObjectType::ObjectType type;
	size_t identifier;
};

namespace std
{
	template<>
	struct hash<ObjectIdentifier> {
		size_t operator()(const ObjectIdentifier& in) const noexcept {
			return in.getIdentifier();
		}
	};
}
