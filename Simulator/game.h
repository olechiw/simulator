#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "character.h"
#include "ability.h"

class Game
{
public:
	struct GameResult
	{

	};

	template<typename T>
	void setAbility(std::shared_ptr<T> ability)
	{
		this->activeAbility = std::static_pointer_cast<Ability>(ability);
	}

	GameResult run()
	{
		// event handling
		// drawing different shapes easily
	}
private:
	// std::shared_ptr<Player>
	std::shared_ptr<Ability> activeAbility
	// std::shared_ptr<
};