#pragma once
#include "Screens/Screen.h"
#include "ResourceManager.h"
#include "Commands/StartLevelCommand.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

#define CHOOSE_SCREEN_BACKGROUND "selectorback.jpg"
#define MAX_LEVELS 4


class ChooseLevelScreen : public Screen 
{
public:
    ChooseLevelScreen();
    ~ChooseLevelScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

	virtual void setActive(bool active)override;
private:
    //sf::Font font;
    std::vector<Button> m_buttons;

	int m_currentAmountOfLevels = 2;
    sf::Sprite m_backgroundSprite;
};
