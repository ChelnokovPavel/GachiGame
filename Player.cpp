#include "Player.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "Math.h"

namespace ApplesGame {

	void InitPlayer(Player& player, Resource* resource)
	{
		SetDefaultPlayerPosition(player);
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = -1;
		player.shape.setRadius(PLAYER_SIZE / 2.f);
		player.shape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);

		player.sprite.setTexture(resource->playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	};

	void SetDefaultPlayerPosition(Player& player)
	{
		player.position.x = SCREEN_WIDTH / 2.f;
		player.position.y = SCREEN_HEIGHT / 2.f;
		player.sprite.setPosition(player.position.x, player.position.y);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		// Right
		if (player.playerDirection == 0)
		{
			SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
		}
		// Left
		else if (player.playerDirection == 2)
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		}
		window.draw(player.sprite);
	}

}
