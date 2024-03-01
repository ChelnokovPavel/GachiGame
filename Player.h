#pragma once
#include "Math.h"
#include "Resource.h"
#include "Settings.h"

namespace sf
{
	class CircleShape;
	class Sprite;
}

namespace ApplesGame {

	struct Player {
		int playerDirection;
		const float size = PLAYER_SIZE;
		float playerSpeed;
		Position position;
		sf::Sprite sprite;
		sf::CircleShape shape;
	};

	void InitPlayer(Player& player, Resource* resource);
	void SetDefaultPlayerPosition(Player& player);
	void DrawPlayer(Player& player, sf::RenderWindow& window);

}
