#pragma once
#include "renderable.h"
#include <list>
class Scene
{
public:
	void dispatchPhysicsUpdate();
	void render(sf::RenderWindow &window);
	template <typename T>
	void addObject(T object);
	void clear();
	static Scene& getInstance();
private:
	std::list<std::shared_ptr<Renderable>> objects;
};

template <typename T>
void Scene::addObject(T object)
{
	this->objects.push_back(std::static_pointer_cast<Renderable>(object));
}