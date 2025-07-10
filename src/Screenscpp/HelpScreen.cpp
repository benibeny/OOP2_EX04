#include "Screens/HelpScreen.h"


HelpScreen::HelpScreen()
{
    setUpUI("talkshow.png");

    sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
    unsigned int fontSize = static_cast<unsigned int>(winSize.y * 0.03f);
    float lineSpacing = fontSize + 10.f;


    // Footer text
    m_footerText.setFont(m_font);
    m_footerText.setString("Press ESC to return to the main menu");
    m_footerText.setCharacterSize(static_cast<unsigned int>(fontSize * 0.9f));
    m_footerText.setFillColor(sf::Color::Black);
    m_footerText.setOutlineColor(sf::Color::White);
    m_footerText.setOutlineThickness(2.f);

    sf::FloatRect footerBounds = m_footerText.getLocalBounds();
    m_footerText.setPosition(15.f, 50.f);



    auto command = std::make_unique<SwitchBackgroundCommand>(this);
    m_switchBackgroundButton = std::make_unique<Button>("next", m_font, std::move(command));
    m_switchBackgroundButton->setRelativePosition(0.5f, 0.95f);
    m_switchBackgroundButton->resize(winSize);

}


void HelpScreen::handleEvent(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Escape) 
    {
        ScreenManager::getInstance().switchScreen(ScreenType::MainMenu);
    }
    else if (event.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        Game::getInstance().getWindow().setView(sf::View(visibleArea));
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
    {
        float x = static_cast<float>(event.mouseButton.x);
        float y = static_cast<float>(event.mouseButton.y);
        if (m_switchBackgroundButton && m_switchBackgroundButton->contains(x, y)) {
            m_switchBackgroundButton->onClick();
        }
    }
}

void HelpScreen::update(float)
{
    if (m_switchBackgroundButton) 
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Game::getInstance().getWindow());
        bool isHovering = m_switchBackgroundButton->contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        m_switchBackgroundButton->setHover(isHovering);
        sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
        m_switchBackgroundButton->resize(winSize);
    }
}


void HelpScreen::render(sf::RenderWindow& window) 
{
    window.draw(m_backgroundSprite);
    window.draw(m_footerText);

    if (m_switchBackgroundButton)
        m_switchBackgroundButton->draw(window);

}

void HelpScreen::toggleBackground() 
{

    // Move to next background index
    m_backgroundIndex = (m_backgroundIndex + 1) % 4; // assuming 4 backgrounds

    std::string fileName;
    switch (m_backgroundIndex) {
    case 0: fileName = "talkshow.png"; break;
    case 1: fileName = "tips0.png"; break;
    case 2: fileName = "tips1.png"; break;
    case 3: fileName = "tips2.png"; break;
    }

	setUpUI(fileName);
}


void HelpScreen::setUpUI(std::string fileName)
{
    ResourceManager& resManager = ResourceManager::getInstance();

    m_font = resManager.getGameFont();

    resManager.loadSpriteSheet(fileName, 1, 1);
    resManager.setSpriteTextureFromSheet(m_backgroundSprite, fileName, 0, 0);

    const sf::Texture* backgroundTexture = m_backgroundSprite.getTexture();

    sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
    m_backgroundSprite.setScale(
        winSize.x / (float)backgroundTexture->getSize().x,
        winSize.y / (float)backgroundTexture->getSize().y
    );
}


void HelpScreen::setActive(bool active)
{
    m_isActive = active;
}

void HelpScreen::reset() {}

