#include "Apple.h"
#include "Player.h"
#include "Resource.h"
#include "Rock.h"
#include "UI.h"

namespace sf
{
	class Clock;
	class Sound;
}

namespace ApplesGame {

	enum GameState
	{
		StartScreen = 0,
		Gameplay = 1,
		GameOver = 2
	};

	enum GameSettingsBits {
		defaultGameMode = 0,
		randomAppleCount = 1, // то же самое что и 1 << 0
		infiniteApple = 1 << 1,
		acceleratePlayer = 1 << 2,
		Max = 7 // Максимальная маска = 7 (000, 001, 010, 100, 101, 110, 111)
	};

	struct Game {
		GameState state;
		int gameMode = GameSettingsBits::defaultGameMode;
		int numEatenApples = 0;
		int numApples = 0;
		const int numRocks = NUM_ROCKS;
		sf::Clock Clock;
		Apple* apples;
		Player player;
		Rock rocks[NUM_ROCKS];
		sf::Sound eatSound;
		sf::Sound collisionSound;
		Resource* resource;
		UI UI;
	};

	void InitGame(Game& game, Resource* resource);
	void RestartGame(Game& game);
	void UpdateGame(Game& game);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DrawStartScreen(Game& game, sf::RenderWindow& window);
	void DrawGameplay(Game& game, sf::RenderWindow& window);
	void DrawGameOver(Game& game, sf::RenderWindow& window);
	void HandleInput(Game& game, sf::RenderWindow& window);
	Position GetGameObjectPosition(const Game& game);
	bool HasGameSetting(Game& game, int setting);
	void SwitchGameSetting(Game& game, int setting);

}
