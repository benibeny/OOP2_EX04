#pragma once
#include "Screens/Screen.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

// MenuScreen: the main menu screen with a background and interactive buttons
class MenuScreen : public Screen {
public:
    MenuScreen();
    ~MenuScreen() override = default;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    virtual void setActive(bool active)override;
	virtual void reset() override;
private:
    sf::RectangleShape backgroundRect;
    //sf::Font font;
    std::vector<Button> buttons;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};
