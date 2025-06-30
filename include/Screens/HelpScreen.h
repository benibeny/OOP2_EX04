#pragma once
#include "Screens/Screen.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Commands/Command.h"

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
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text footerText;

    std::unique_ptr<Button> switchBackgroundButton;
    int m_backgroundIndex = 0;

};