#pragma once

class ObjectIdentifier {
public:
	ObjectIdentifier()
	{
		identifier = NextIdentifier++;
	}
	
	ObjectIdentifier &operator=(ObjectIdentifier& other) {
		this->identifier = other.identifier;
	}

	bool operator==(const ObjectIdentifier& other) const {
		return other.identifier == this->identifier;
	}
private:
	static size_t NextIdentifier;
	size_t identifier;
	friend struct std::hash<ObjectIdentifier>;
};

namespace std {
	template<typename ObjectIdentifier>
	struct hash {
		size_t operator()(const ObjectIdentifier& in) const noexcept {
			return in.identifier;
		}
	};
}