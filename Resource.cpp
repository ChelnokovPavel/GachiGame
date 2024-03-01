#include "Resource.h"
#include <cassert>

namespace ApplesGame {

	void InitResource(Resource* resource)
	{
		// Текстуры
		assert(resource->playerTexture.loadFromFile(RESOURCES_PATH + "Billy.png"));
		assert(resource->appleTexture.loadFromFile(RESOURCES_PATH + "Dumbbell.png"));
		assert(resource->rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
		assert(resource->gameOverBackground.loadFromFile(RESOURCES_PATH + "GameOverBackground.png"));
		assert(resource->billySuccess.loadFromFile(RESOURCES_PATH + "BillySuccess.png"));
		assert(resource->checkMark.loadFromFile(RESOURCES_PATH + "Mark.png"));

		// Звуки
		assert(resource->eatSoundBuffer.loadFromFile(RESOURCES_PATH + "Eat.wav"));
		assert(resource->collisionSoundBuffer.loadFromFile(RESOURCES_PATH + "Collision.wav"));
		assert(resource->music.openFromFile(RESOURCES_PATH + "Music.ogg"));

		// Шрифты
		assert(resource->font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Black.ttf"));
	}

}
