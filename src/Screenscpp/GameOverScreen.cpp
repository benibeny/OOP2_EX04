#include "Screens/GameOverScreen.h"



GameOverScreen::GameOverScreen() 
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    resourceManager.loadSpriteSheet(GAME_OVER_SCREEN, 1, 1);
    resourceManager.setSpriteTextureFromSheet(m_backgroundSprite, GAME_OVER_SCREEN, 0, 0);

	setUpUi();
}



void GameOverScreen::handleEvent(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        ScreenManager::getInstance().switchScreen(ScreenType::MainMenu);
    }
    else if (event.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        Game::getInstance().getWindow().setView(sf::View(visibleArea));
		setUpUi();
    }
}


void GameOverScreen::update(float deltaTime) 
{
	m_timer += deltaTime;
    if (m_timer >= DEATH_TIME)
    {
        m_timer = 0.f; // Reset timer after switching screens
        ScreenManager::getInstance().switchScreen(ScreenType::MainMenu);
    }
}

void GameOverScreen::render(sf::RenderWindow& window) 
{
	window.draw(m_backgroundSprite);
}

void GameOverScreen::setActive(bool active)
{
	m_isActive = active;
	setUpUi();
    m_timer = 0.f;
}

void GameOverScreen::reset() 
{

}

void GameOverScreen::setUpUi()
{
    sf::RenderWindow& window = Game::getInstance().getWindow();
    sf::Vector2u windowSize = window.getSize();

    const sf::Texture* backgroundTexture = m_backgroundSprite.getTexture();
    m_backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture->getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture->getSize().y
    );

}