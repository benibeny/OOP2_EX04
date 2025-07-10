#pragma once
#include "Screens/Screen.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Commands/Command.h"
#include "Game.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include <iostream>
#include "Commands/SwitchBackgroundCommand.h"
#include "ResourceManager.h"

// HelpScreen: displays help or instructions to the player
class HelpScreen : public Screen {
public:
    HelpScreen();
    ~HelpScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void toggleBackground();

    virtual void setActive(bool active)override;
	virtual void reset() override;

private:
	void setUpUI(std::string fileName);

    sf::Font m_font;
    
    sf::Sprite m_backgroundSprite;
    sf::Text m_footerText;

    std::unique_ptr<Button> m_switchBackgroundButton;
    int m_backgroundIndex = 0;

};