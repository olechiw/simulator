#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>>
#include <list>
#include <unordered_set>
#include "body_user_data.h"

class SceneObject
{
public:
	virtual ~SceneObject();
	// Render is called an arbitrary number of times
	virtual void render(sf::RenderWindow& window) = 0;

	// Dispatch collision event
	virtual void onPhysicsUpdated()
	{

	}
	virtual bool isDestroyed();
	virtual b2Body* getBody();
protected:
	std::unordered_set<BodyUserData*> registeredCollisions;
	virtual void onCollision(BodyUserData* collidedWith)
	{

	}
};


bool SceneObject::isDestroyed()
{
	return this->destroyed;
}

b2World* SceneObject::getBody()
{
	return nullptr;
}

void SceneObject::destroy()
{
	this->destroyed = true;
}

SceneObject::~SceneObject() {}