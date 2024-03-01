#pragma once

namespace ApplesGame
{
	struct Player;
	struct Apple;
	struct Rock;
}

namespace sf
{
	class Sprite;
}

struct Vector2D
{
	float x = 0.f;
	float y = 0.f;
};

typedef Vector2D Position;

namespace ApplesGame {

	bool CheckBorderCollision(const Position position, float Size);
	bool CheckCircleCirlceCollision(
		float firstCircleX, float firstCircleY, float firstCircleRadius,
		float secondCircleX, float secondCircleY, float secondCircleRadius
	);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	bool IsTherePlayerNearby(const Position position, float maxGameObjectSize, const Player player);
	bool IsThereAppleNearby(const Position position, float maxGameObjectSize, const Apple apple);
	bool IsThereRockNearby(const Position position, float maxGameObjectSize, const Rock rock);

}
