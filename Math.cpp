#include "Apple.h"
#include "Math.h"
#include "Player.h"
#include "Rock.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame {

	bool CheckBorderCollision(const Position position, float Size)
	{
		// left
		if (position.x < 0.f + PLAYER_SIZE / 2.f) return true;
		// top
		else if (position.y < 0.f + PLAYER_SIZE / 2.f + INFO_PANEL_SIZE) return true;
		// right
		else if (position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH) return true;
		// down
		else if (position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT) return true;
		return false;
	}

	bool CheckCircleCirlceCollision(
		float firstCircleX, float firstCircleY, float firstCircleRadius,
		float secondCircleX, float secondCircleY, float secondCircleRadius
	) {

		// get distance between the circle's centers
		// use the Pythagorean Theorem to compute the distance
		float distX = firstCircleX - secondCircleX;
		float distY = firstCircleY - secondCircleY;
		float distance = sqrt((distX * distX) + (distY * distY));

		// if the distance is less than the sum of the circle's
		// radii, the circles are touching!
		if (distance <= firstCircleRadius + secondCircleRadius) {
			return true;
		}
		return false;
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		float width = desiredWidth / spriteRect.width;
		float height = desiredHeight / spriteRect.height;
		sprite.setScale(width, height);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	bool IsTherePlayerNearby(const Position position, float maxGameObjectSize, const Player player)
	{
		if (
			((position.x > player.position.x + (player.size / 2.f) + maxGameObjectSize) || (position.x < player.position.x - (player.size / 2.f) - maxGameObjectSize)) ||
			((position.y > player.position.y + (player.size / 2.f) + maxGameObjectSize) || (position.y < player.position.y - (player.size / 2.f) - maxGameObjectSize))
			) return true;
		return false;
	}

	bool IsThereAppleNearby(const Position position, float maxGameObjectSize, const Apple apple)
	{
		if (
			((position.x > apple.position.x + (apple.size / 2.f) + maxGameObjectSize) || (position.x < apple.position.x - (apple.size / 2.f) - maxGameObjectSize)) ||
			((position.y > apple.position.y + (apple.size / 2.f) + maxGameObjectSize) || (position.y < apple.position.y - (apple.size / 2.f) - maxGameObjectSize))
			) return true;
		return false;
	}

	bool IsThereRockNearby(const Position position, float maxGameObjectSize, const Rock rock)
	{
		if (
			((position.x > rock.position.x + (rock.size / 2.f) + maxGameObjectSize) || (position.x < rock.position.x - (rock.size / 2.f) - maxGameObjectSize)) ||
			((position.y > rock.position.y + (rock.size / 2.f) + maxGameObjectSize) || (position.y < rock.position.y - (rock.size / 2.f) - maxGameObjectSize))
			) return true;
		return false;
	}

	void SortScoreboard(int* scores, std::string* names)
	{
		int length = SCOREBOARD_SIZE - 1;
		while (true)
		{
			bool swapped = false;
			for (int i = 0; i < length; i++)
			{
				if (scores[i] < scores[i + 1])
				{
					std::swap(scores[i], scores[i + 1]);
					std::swap(names[i], names[i + 1]);
					swapped = true;
				}
			}
			if (swapped == false)
				break;
		}
	}

}
