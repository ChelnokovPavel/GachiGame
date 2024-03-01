#pragma once
#include "Math.h"
#include "Resource.h"
#include "Settings.h"

namespace sf
{
	class CircleShape;
}

namespace ApplesGame {

	struct Apple {
		const float size = APPLE_SIZE;
		Position position;
		sf::CircleShape shape;
	};

	void InitApple(Apple& apple, Resource* resource);
	void SetApplePosition(Apple& apple);

}
