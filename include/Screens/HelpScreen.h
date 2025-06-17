#pragma once
#include "Screens/Screen.h"
#include <SFML/Graphics.hpp>

// HelpScreen: displays help or instructions to the player
class HelpScreen : public Screen {
public:
    HelpScreen();
    ~HelpScreen() override = default;
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
private:
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<sf::Text> fishLines;
    std::vector<sf::Text> enemyLines;
    std::vector<sf::Text> moneyLines;
    sf::Text footerText;

};
