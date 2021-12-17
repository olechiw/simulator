#include "object_identifier.h"

size_t ObjectIdentifier::NextIdentifier = 0;

ObjectIdentifier::ObjectIdentifier(const ObjectType& typeIn)
{
	identifier = NextIdentifier++;
	this->type = typeIn;
}

const ObjectType& ObjectIdentifier::getType() const {
	return this->type;
}

ObjectIdentifier& ObjectIdentifier::operator=(ObjectIdentifier& other) {
	this->identifier = other.identifier;
	return *this;
}

bool ObjectIdentifier::operator==(const ObjectIdentifier& other) const {
	return other.identifier == this->identifier;
}

ObjectIdentifier& ObjectIdentifier::operator=(const ObjectIdentifier& other) {
	this->identifier = other.identifier;
	this->type = other.type;
	return *this;
}

size_t ObjectIdentifier::getIdentifier() const {
	return this->identifier;
}