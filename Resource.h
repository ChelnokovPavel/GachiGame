#pragma once
#include "Settings.h"
#include <fstream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace ApplesGame {

	struct Resource {
		int* scores;
		std::string* names;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Texture billySuccess;
		sf::Texture gameOverBackground;
		sf::Texture checkMark;
		sf::SoundBuffer eatSoundBuffer;
		sf::SoundBuffer collisionSoundBuffer;
		sf::Font font;
		sf::Music music;
	};

	void InitResource(Resource* resource);
	std::string* CreateNamesArr(int readRowCount = 2000);

}
