#include "Screens/HelpScreen.h"
#include "Game.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include <iostream>

HelpScreen::HelpScreen() {
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        std::cerr << "Failed to load font for HelpScreen.\n";
    }

    if (!backgroundTexture.loadFromFile("talkshow.jpg")) {
        std::cerr << "Failed to load help background image.\n";
    }

    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
    backgroundSprite.setScale(
        winSize.x / (float)backgroundTexture.getSize().x,
        winSize.y / (float)backgroundTexture.getSize().y
    );

    unsigned int fontSize = static_cast<unsigned int>(winSize.y * 0.03f);
    float lineSpacing = fontSize + 10.f;

    // X positions per column (centered alignment)
    float fishX = winSize.x * 0.5f;
    float enemyX = winSize.x * 0.25f;
    float coinX = winSize.x * 0.75f;

    // Fish section
    std::vector<std::string> fish = {
        " Fish",
        "- Feed them to keep them alive",
        "- Click anywhere to produce food",
        "- Different fish produce different coins",
        "- If they starve, they die",
        "- Fish can be killed by enemy",
        "- If all fish die, you lose!"
    };

    for (size_t i = 0; i < fish.size(); ++i) {
        sf::Text line;
        line.setFont(font);
        line.setString(fish[i]);
        line.setCharacterSize(fontSize);
        line.setFillColor(sf::Color::Black);
        line.setOutlineColor(sf::Color::White);
        line.setOutlineThickness(2.f);

        sf::FloatRect bounds = line.getLocalBounds();
        line.setOrigin(bounds.width / 2.f, 0.f);
        line.setPosition(fishX, winSize.y * 0.1f + i * lineSpacing);
        fishLines.push_back(line);
    }

    // Enemy section
    std::vector<std::string> enemies = {
        " Enemies",
        "- Appear randomly during the game",
        "- Click rapidly to defeat them",
        "- Some enemies are stronger than others",
        "- If not stopped, they kill your fish!",
        "- Enemies become stronger over time, plan ahead"
    };

    for (size_t i = 0; i < enemies.size(); ++i) {
        sf::Text line;
        line.setFont(font);
        line.setString(enemies[i]);
        line.setCharacterSize(fontSize);
        line.setFillColor(sf::Color::Black);
        line.setOutlineColor(sf::Color::White);
        line.setOutlineThickness(2.f);

        sf::FloatRect bounds = line.getLocalBounds();
        line.setOrigin(bounds.width / 2.f, 0.f);
        line.setPosition(enemyX, winSize.y * 0.5f + i * lineSpacing);
        enemyLines.push_back(line);
    }

    // Coins section
    std::vector<std::string> money = {
        " Coins",
        "- Fish drop coins over time",
        "- Click to collect coins",
        "- Coins and food disappear if reach the ground",
        "- Use coins to purchase upgrades and progress",
        "- Every food cost 5$"
    };

    for (size_t i = 0; i < money.size(); ++i) {
        sf::Text line;
        line.setFont(font);
        line.setString(money[i]);
        line.setCharacterSize(fontSize);
        line.setFillColor(sf::Color::Black);
        line.setOutlineColor(sf::Color::White);
        line.setOutlineThickness(2.f);

        sf::FloatRect bounds = line.getLocalBounds();
        line.setOrigin(bounds.width / 2.f, 0.f);
        line.setPosition(coinX, winSize.y * 0.5f + i * lineSpacing);
        moneyLines.push_back(line);
    }

    // Footer text
    footerText.setFont(font);
    footerText.setString("Press ESC to return to the main menu");
    footerText.setCharacterSize(static_cast<unsigned int>(fontSize * 0.9f));
    footerText.setFillColor(sf::Color::Black);
    footerText.setOutlineColor(sf::Color::White);
    footerText.setOutlineThickness(2.f);

    sf::FloatRect footerBounds = footerText.getLocalBounds();
    footerText.setOrigin(footerBounds.width / 2.f, 0.f);
    footerText.setPosition(winSize.x / 2.f, winSize.y - footerBounds.height - 15.f);

}

void HelpScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        ScreenManager::getInstance().switchScreen(ScreenType::MainMenu);
    }
}

void HelpScreen::update(float) {
    // No animation or timed updates
}

void HelpScreen::render(sf::RenderWindow& window) {
    if (backgroundTexture.getSize().x == 0 || font.getInfo().family.empty())
        return;

    window.draw(backgroundSprite);

    for (const auto& line : fishLines)
        window.draw(line);
    for (const auto& line : enemyLines)
        window.draw(line);
    for (const auto& line : moneyLines)
        window.draw(line);

    window.draw(footerText);

}
