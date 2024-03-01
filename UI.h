#pragma once
#include "Math.h"
#include "Resource.h"

namespace sf
{
	class RectangleShape;
	class Text;
}

namespace ApplesGame {

	struct UI {
		const float checBoxSize = 32.f;
		sf::Sprite billyStartSceenSprite;
		sf::RectangleShape checkBox;
		sf::RectangleShape infoPanel;
		sf::RectangleShape gameOverScreen;
		sf::Text text;
	};

	void InitUI(UI& UI, Resource* resource);

}
