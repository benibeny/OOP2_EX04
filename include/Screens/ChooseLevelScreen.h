#pragma once
#include "Screens/Screen.h"
#include "Managers/ResourceManager.h"
#include "Commands/StartLevelCommand.h"
#include "Managers/EventManager.h"
#include "UI/Button.h"
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

    void registerEvents();
    void setUpUi();

	virtual void setActive(bool active)override;
	virtual void reset() override;
private:
    std::vector<Button> m_buttons;

	int m_currentAmountOfLevels = 1;
    sf::Sprite m_backgroundSprite;
};
