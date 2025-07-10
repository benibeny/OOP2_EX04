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
#include "Commands/CommandFunction.h"
#include "Commands/CommandToggleMute.h"
#include "Commands/CommandSwitchScreen.h"
#include "PopUp.h"
#include <iostream>
#include <functional>

#include "Entities/Fish.h"
// GameScreen: represents the main gameplay screen (Insaniquarium game area)
class GameScreen : public Screen 
{
public:
    GameScreen(int lvl);
    ~GameScreen() override;

	
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

	virtual void setActive(bool active) override;
	virtual void reset() override;

	void setUpUi();

private:
	void registerEvents();
	void updateBackground();
	void unRegisterEvents();

	int m_currentLevel;
    bool m_isActive;
	bool m_firstTime;

	sf::Sprite m_background;

	ShopBarManager m_shopBarManager;
	AquariumManager m_aquariumManager;
	PopUp m_popUpMenu;

};
