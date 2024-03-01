#pragma once
#include "Math.h"
#include "Resource.h"
#include "Settings.h"

namespace sf
{
	class CircleShape;
}

namespace ApplesGame {

	struct Rock {
		const float size = ROCK_SIZE;
		Position position;
		sf::CircleShape mainShape;
		sf::CircleShape internalShape;
	};

	void InitRock(Rock& rock, Resource* resource);
	void SetRockPosition(Rock& rock);

}
