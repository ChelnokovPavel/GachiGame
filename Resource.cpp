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

		// Массивы имен и очков
		resource->names = CreateNamesArr();
		int* scores = new int[SCOREBOARD_SIZE];
		for (int i = 0; i < SCOREBOARD_SIZE - 1; i++)
		{
			scores[i] = rand() % 200;
		}
		scores[SCOREBOARD_SIZE - 1] = 0;
		resource->scores = scores;
	}

	std::string* CreateNamesArr(int readRowCount)
	{
		std::ifstream file(RESOURCES_PATH + "names.txt");
		std::string* readFile = new std::string[readRowCount];
		std::string* namesArr = new std::string[SCOREBOARD_SIZE];
		for (int i = 0; i < readRowCount; i++)
		{
			getline(file, readFile[i]);
		}
		file.close();
		int* rndArr = new int[SCOREBOARD_SIZE - 1];
		for (int i = 0; i < SCOREBOARD_SIZE - 1; i++)
		{
			rndArr[i] = rand() % readRowCount;
		}
		std::sort(rndArr, rndArr + SCOREBOARD_SIZE - 1);
		for (int i = 0; i < SCOREBOARD_SIZE - 1; i++)
		{
			namesArr[i] = readFile[rndArr[i]];
		}
		namesArr[SCOREBOARD_SIZE - 1] = "Player";
		delete[] readFile;
		delete[] rndArr;
		return namesArr;
	}

}
