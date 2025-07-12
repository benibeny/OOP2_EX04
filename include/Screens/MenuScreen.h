#pragma once
#include "Screens/Screen.h"
#include "UI/Button.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include "Commands/Command.h"
#include "Commands/QuitGameCommand.h"
#include "Commands/SwitchBackgroundCommand.h"
#include "Commands/CommandToggleMute.h"
#include "Commands/CommandSwitchScreen.h"
#include "Managers/ScreenManager.h"
#include "Managers/ResourceManager.h"

// MenuScreen: the main menu screen with a background and interactive buttons
class MenuScreen : public Screen {
public:
    MenuScreen();
    ~MenuScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void setUpUi();

    virtual void setActive(bool active)override;
	virtual void reset() override;
private:
    sf::RectangleShape backgroundRect;
    std::vector<Button> buttons;

    sf::Sprite m_backgroundSprite;
};
