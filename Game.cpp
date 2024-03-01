#include "Game.h"

namespace ApplesGame {

	void InitGame(Game& game, Resource* resource)
	{
		game.state = StartScreen;
		game.resource = resource;
		// UI init
		InitUI(game.UI, game.resource);
		// Music init
		game.resource->music.setVolume(5.f);
		// Sound init
		game.eatSound.setBuffer(game.resource->eatSoundBuffer);
		game.collisionSound.setBuffer(game.resource->collisionSoundBuffer);
		// init player
		InitPlayer(game.player, game.resource);
		// init rock
		for (int i = 0; i < NUM_ROCKS; i++)
		{
			InitRock(game.rocks[i], game.resource);
		}
	}

	void RestartGame(Game& game)
	{
		// init apples
		if (HasGameSetting(game, GameSettingsBits::randomAppleCount)) game.numApples = rand() % NUM_APPLES + 1;
		else  game.numApples = NUM_APPLES;

		Apple* apples = new Apple[game.numApples];
		game.apples = apples;
		for (int i = 0; i < game.numApples; i++)
		{
			InitApple(game.apples[i], game.resource);
		}
		game.player.playerDirection = -1;
		if (game.state == Gameplay) game.resource->music.play();
		game.player.playerSpeed = INITIAL_SPEED;
		game.numEatenApples = 0;
		// Restart player position
		SetDefaultPlayerPosition(game.player);
		// Clear array
		for (int i = 0; i < NUM_ROCKS; i++)
		{
			game.rocks[i].position.x = 0;
			game.rocks[i].position.y = 0;
		}
		for (int i = 0; i < game.numApples; i++)
		{
			game.apples[i].position.x = 0;
			game.apples[i].position.y = 0;
		}
		// Get new positions
		// For rocks
		for (int i = 0; i < NUM_ROCKS; i++)
		{
			game.rocks[i].position = GetGameObjectPosition(game);
			SetRockPosition(game.rocks[i]);
		}
		// For apples
		for (int i = 0; i < game.numApples; i++)
		{
			game.apples[i].position = GetGameObjectPosition(game);
			SetApplePosition(game.apples[i]);
		}
	}

	void UpdateGame(Game& game)
	{
		float deltaTime = game.Clock.restart().asSeconds();

		if (game.player.playerDirection == 0)
		{
			game.player.position.x += game.player.playerSpeed * deltaTime;
		}
		else if (game.player.playerDirection == 1)
		{
			game.player.position.y -= game.player.playerSpeed * deltaTime;
		}
		else if (game.player.playerDirection == 2)
		{
			game.player.position.x -= game.player.playerSpeed * deltaTime;
		}
		else if (game.player.playerDirection == 3)
		{
			game.player.position.y += game.player.playerSpeed * deltaTime;
		}

		if (game.state == Gameplay)
		{
			if (CheckBorderCollision(game.player.position, PLAYER_SIZE))
			{
				delete[] game.apples;
				game.state = GameOver;
				game.collisionSound.play();
				game.resource->music.stop();
			}

			for (int i = 0; i < NUM_ROCKS; i++)
			{
				if (CheckCircleCirlceCollision(
					game.player.position.x, game.player.position.y, game.player.shape.getRadius(),
					game.rocks[i].position.x, game.rocks[i].position.y, game.rocks[i].internalShape.getRadius()
				))
				{
					delete[] game.apples;
					game.state = GameOver;
					game.collisionSound.play();
					game.resource->music.stop();
				}
			}
			for (int i = 0; i < game.numApples; i++)
			{
				if (CheckCircleCirlceCollision(
					game.player.position.x, game.player.position.y, game.player.shape.getRadius(),
					game.apples[i].position.x, game.apples[i].position.y, game.apples[i].shape.getRadius()
				))
				{
					game.numEatenApples++;
					game.eatSound.play();
					if (HasGameSetting(game, GameSettingsBits::infiniteApple))
					{
						game.apples[i].position = Position{-255, -255};
						game.apples[i].shape.setPosition(game.apples[i].position.x, game.apples[i].position.y);
						if (game.numApples == game.numEatenApples)
						{
							delete[] game.apples;
							game.state = StartScreen;
							game.resource->music.stop();
						}
					}
					else
					{
						game.apples[i].position = GetGameObjectPosition(game);
						game.apples[i].shape.setPosition(game.apples[i].position.x, game.apples[i].position.y);
					}
					if (HasGameSetting(game, GameSettingsBits::acceleratePlayer)) game.player.playerSpeed += 15;
				}
			}
		}


	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		window.clear();
		switch (game.state)
		{
			case StartScreen:
				DrawStartScreen(game, window);
				break;
			case Gameplay:
				DrawGameplay(game, window);
				break;
			case GameOver:
				DrawGameOver(game, window);
				break;
		}
		window.display();
	}

	void DrawStartScreen(Game& game, sf::RenderWindow& window)
	{
		const int txtCount = 3;
		float textRigthBorder;
		float textCenter;
		std::string txtArr[txtCount]{
			"PRESS 1. Random dumbbell count (1-20)",
			"PRESS 2. Finite number of apples",
			"PRESS 3. Acceleration after lifting the weight"
		};

		game.UI.text.setFillColor(sf::Color::White);

		window.draw(game.UI.billyStartSceenSprite);

		game.UI.text.setString(" Billy GYM\nAdventure");
		game.UI.text.setOrigin(game.UI.text.getGlobalBounds().width / 2.f, game.UI.text.getGlobalBounds().height / 2.f);
		game.UI.text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f));
		window.draw(game.UI.text);

		game.UI.text.setString("PRESS SPACE TO START");
		game.UI.text.setOrigin(game.UI.text.getGlobalBounds().width / 2.f, game.UI.text.getGlobalBounds().height / 2.f);
		game.UI.text.setPosition(sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f));
		window.draw(game.UI.text);

		for (int i = 0; i < txtCount; i++)
		{
			game.UI.text.setString(txtArr[i]);
			game.UI.text.setOrigin(game.UI.text.getGlobalBounds().width / 2.f, game.UI.text.getGlobalBounds().height / 2.f);
			game.UI.text.setPosition(sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * (0.7f + i * 0.1f)));
			textRigthBorder = game.UI.text.getPosition().x + game.UI.text.getGlobalBounds().width * 0.5f + 32;
			textCenter = game.UI.text.getPosition().y;
			game.UI.checkBox.setPosition(sf::Vector2f(textRigthBorder, textCenter));
			if (game.gameMode & 1 << i)
			{
				game.UI.checkBox.setFillColor(sf::Color(255, 255, 255));
			}
			else
			{
				game.UI.checkBox.setFillColor(sf::Color(0, 0, 0));
			}
			window.draw(game.UI.checkBox);
			window.draw(game.UI.text);
		}
	}

	void DrawGameplay(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.UI.infoPanel);
		std::string txt;
		if (HasGameSetting(game, GameSettingsBits::infiniteApple)) txt = "Left: " + std::to_string(game.numApples - game.numEatenApples);
		else txt = "Gym score: " + std::to_string(game.numEatenApples);
		game.UI.text.setString(txt);
		game.UI.text.setFillColor(sf::Color::Black);
		game.UI.text.setOrigin(0, 0);
		game.UI.text.setPosition(sf::Vector2f(10.f, 0.f));
		window.draw(game.UI.text);

		game.UI.text.setString("For movement use arrows on keyboard");
		game.UI.text.setPosition(sf::Vector2f(SCREEN_WIDTH - 550.f, 0.f));
		window.draw(game.UI.text);

		game.player.shape.setPosition(game.player.position.x, game.player.position.y);
		game.player.sprite.setPosition(game.player.position.x, game.player.position.y);

		DrawPlayer(game.player, window);
		for (int i = 0; i < NUM_ROCKS; i++)
		{
			window.draw(game.rocks[i].mainShape);
		}
		for (int i = 0; i < game.numApples; i++)
		{
			window.draw(game.apples[i].shape);
		}
	}

	void DrawGameOver(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.UI.gameOverScreen);

		game.UI.text.setFillColor(sf::Color::White);

		game.UI.text.setString("GAME OVER!");
		game.UI.text.setOrigin(game.UI.text.getGlobalBounds().width / 2.f, game.UI.text.getGlobalBounds().height / 2.f);
		game.UI.text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f));
		window.draw(game.UI.text);

		game.UI.text.setString("PRESS \"SPACE\" TO RESTART OR \"ENTER\" TO EXIT THE START SCREEN");
		game.UI.text.setOrigin(game.UI.text.getGlobalBounds().width / 2.f, game.UI.text.getGlobalBounds().height / 2.f);
		game.UI.text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT * 0.6f));
		window.draw(game.UI.text);
	}	

	void HandleInput(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}

		if (game.state == Gameplay)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				game.player.playerDirection = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				game.player.playerDirection = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				game.player.playerDirection = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				game.player.playerDirection = 3;
			}
		}

		if (sf::Event::KeyReleased)
		{
			if (game.state == StartScreen)
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					SwitchGameSetting(game, GameSettingsBits::randomAppleCount);
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					SwitchGameSetting(game, GameSettingsBits::infiniteApple);
				}
				else if (event.key.code == sf::Keyboard::Num3)
				{
					SwitchGameSetting(game, GameSettingsBits::acceleratePlayer);

				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					game.state = Gameplay;
					RestartGame(game);
				}
			}
			else if (game.state == GameOver)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					game.collisionSound.stop();
					game.state = Gameplay;
					RestartGame(game);
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					game.collisionSound.stop();
					game.state = StartScreen;
				}
			}
		}

	}

	Position GetGameObjectPosition(const Game& game)
	{
		bool wasCollision;
		float maxSize = std::max({ PLAYER_SIZE, APPLE_SIZE, ROCK_SIZE });
		Position position;
		while (true)
		{
			wasCollision = false;
			position.x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
			position.y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
			if (IsTherePlayerNearby(position, maxSize, game.player))
			{
				if (!CheckBorderCollision(position, maxSize))
				{
					for (int i = 0; i < game.numRocks; i++)
					{
						if (!IsThereRockNearby(position, maxSize, game.rocks[i]))
						{
							wasCollision = true;
							break;
						}
					}
					if (!wasCollision)
					{
						for (int i = 0; i < game.numApples; i++)
						{
							if (!IsThereAppleNearby(position, maxSize, game.apples[i]))
							{
								wasCollision = true;
								break;
							}
						}
					}
					if (!wasCollision) return position;
				}
			}
		}
	}

	// Проверка значений
	bool HasGameSetting(Game& game, int setting)
	{
		return game.gameMode & setting;
	}

	// Смена значения на противоположное

	void SwitchGameSetting(Game& game, int setting)
	{
		game.gameMode = game.gameMode ^ setting;
	}

}
