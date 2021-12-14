#include "scene.h"

void Scene::dispatchPhysicsUpdate()
{
	for (auto& renderable : this->objects) {
		renderable->onPhysicsUpdated();
	}
}

void Scene::render(sf::RenderWindow& window)
{
	for (auto it = this->objects.begin(); it != this->objects.end();) {
		if (it->get()->isDestroyed()) {
			it = this->objects.erase(it);
		}
		else {
			it->get()->render(window);
			it++;
		}
	}
}

void Scene::clear() {
	this->objects.clear();
}

Scene& Scene::getInstance()
{
	static Scene s;
	return s;
}
