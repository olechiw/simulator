#pragma once
#include <unordered_set>
#include "constants.h"


class ObjectIdentifier {
public:
	ObjectIdentifier(const ObjectType& typeIn);

	const ObjectType& getType() const;
	
	ObjectIdentifier& operator=(ObjectIdentifier& other);

	bool operator==(const ObjectIdentifier& other) const;
	
	ObjectIdentifier& operator=(const ObjectIdentifier& other);

	size_t getIdentifier() const;
private:
	static size_t NextIdentifier;
	ObjectType type;
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
