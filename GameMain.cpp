// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)
#include "Game.h"

int main()
{
	using namespace ApplesGame;
	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Billy gym adventure");

	Resource* resource = new Resource;
	InitResource(resource);
	Game game;
	InitGame(game, resource);

	while (window.isOpen())
	{
		HandleInput(game, window);
		UpdateGame(game);
		DrawGame(game, window);
	}

	delete resource;

	return 0;
}
