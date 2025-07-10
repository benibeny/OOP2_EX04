#pragma once
#include "Screens/Screen.h"
#include "Game.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include <SFML/Graphics.hpp>

#define GAME_OVER_SCREEN "gameOver.jpg"

class GameOverScreen : public Screen 
{
public:
    GameOverScreen();



    virtual void handleEvent(const sf::Event& event)override;
    virtual void update(float deltaTime)override;
    virtual void render(sf::RenderWindow& window)override;
    virtual void setActive(bool active)override;
    virtual void reset()override;
    
private:
    void setUpUi();

    sf::Sprite m_backgroundSprite;
	float m_timer = 0.0f;
    static  constexpr int DEATH_TIME = 3.0f;

};
