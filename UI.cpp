#include "UI.h"

namespace ApplesGame {

	void InitUI(UI& UI, Resource* resource)
	{
		// Init text
		UI.text.setFont(resource->font);

		// init start screen
		UI.billyStartSceenSprite.setTexture(resource->billySuccess);
		UI.billyStartSceenSprite.setPosition(SCREEN_WIDTH / 2.f - 80, SCREEN_HEIGHT / 8.f);
		UI.checkBox.setSize(sf::Vector2f(UI.checBoxSize, UI.checBoxSize));
		UI.checkBox.setFillColor(sf::Color::Black);
		UI.checkBox.setOutlineColor(sf::Color::White);
		UI.checkBox.setOutlineThickness(3.f);
		UI.checkBox.setOrigin(UI.checBoxSize / 2, UI.checBoxSize / 2);
		UI.checkBox.setTexture(&resource->checkMark);
		UI.checkBox.setFillColor(sf::Color(255, 255, 255));

		// init info panel
		UI.infoPanel.setSize(sf::Vector2f(SCREEN_WIDTH, INFO_PANEL_SIZE));
		UI.infoPanel.setFillColor(sf::Color(192, 192, 192));

		// Init game over screen
		UI.gameOverScreen.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		UI.gameOverScreen.setFillColor(sf::Color(100, 100, 100));
		UI.gameOverScreen.setTexture(&resource->gameOverBackground);

	}

}
