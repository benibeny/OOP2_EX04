#pragma once
#include "Screens/Screen.h"
#include <SFML/Graphics.hpp>
#include "AquariumManager.h"
#include "Entities/GoldFish.h"
#include "Entities/Money.h"
#include "Game.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include <iostream>

#include "Entities/Fish.h"
// GameScreen: represents the main gameplay screen (Insaniquarium game area)
class GameScreen : public Screen 
{
public:
    GameScreen();
    ~GameScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

	void setUpUi();
private:
	//for the shop bar
    sf::Font m_font;
    sf::Text m_money;
    sf::RectangleShape m_shopBar;
	sf::Texture m_shopBarTexture;


	sf::Sprite m_background;
    sf::Texture m_backgroundTexture;


	AquariumManager m_aquariumManager;
 
};
