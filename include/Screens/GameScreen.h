#pragma once
#include "Screens/Screen.h"
#include <SFML/Graphics.hpp>
#include "AquariumManager.h"
#include "Entities/GoldFish.h"
#include "Entities/Money.h"
#include "Game.h"
#include "ScreenManager.h"
#include "ShopBarManager.h"
#include "EventManager.h"
#include <iostream>
#include <functional>

#include "Entities/Fish.h"
// GameScreen: represents the main gameplay screen (Insaniquarium game area)
class GameScreen : public Screen 
{
public:
    GameScreen(int lvl);
    ~GameScreen() override;

	void registerEvents();
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

	void setActive(bool active) override;
	

	void setUpUi();
private:
	void updateBackground();

	void unRegisterEvents();

	int m_currentLevel;
    bool m_isActive;

	sf::Sprite m_background;
    //sf::Texture m_backgroundTexture;
	std::function<void()> m_onNextLevelCallback;

	ShopBarManager m_shopBarManager;
	AquariumManager m_aquariumManager;
 
};
