#include "Screens/MenuScreen.h"


MenuScreen::MenuScreen() 
{
    sf::RenderWindow& window = Game::getInstance().getWindow();
    sf::Vector2u size = window.getSize();
    window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y))));

    
	ResourceManager& resourceManager = ResourceManager::getInstance();
	resourceManager.loadSpriteSheet("titlescreen.jpg", 1, 1);
	resourceManager.setSpriteTextureFromSheet(m_backgroundSprite, "titlescreen.jpg", 0, 0);

    sf::Font& m_font = ResourceManager::getInstance().getGameFont();
    

    sf::Vector2u winSize = window.getSize();
    

    // Create menu buttons with their respective commands
    buttons.emplace_back("Start Adventure", m_font, std::make_unique<CommandSwitchScreen>(ScreenType::ChooseLevelScreen));
    buttons.emplace_back("Help", m_font, std::make_unique<CommandSwitchScreen>(ScreenType::HelpScreen));
    buttons.emplace_back("Quit Game", m_font, std::make_unique<QuitGameCommand>());
    buttons.emplace_back("Mute", m_font, std::make_unique<ToggleMuteCommand>());
    

    // Set normalized positions for each button (centered horizontally, spaced vertically)
    float startY = 0.5f;
    float stepY = 0.2f;

    for (size_t i = 0; i < buttons.size() - 1; ++i)
    {
        float posY = startY + i * stepY;
        buttons[i].setRelativePosition(0.5f, posY);
        buttons[i].setBaseCharacterSize(Game::BASE_FONT_SIZE);
        buttons[i].resize(winSize);
    }

    buttons.back().setRelativePosition(0.1f, 0.95f);
    buttons.back().setBaseCharacterSize(Game::BASE_FONT_SIZE - 4);
    buttons.back().resize(winSize);

    setUpUi();

}


void MenuScreen::setUpUi()
{
    sf::Vector2u windowSize = Game::getInstance().getWindow().getSize();
    // Adjust background size
    const sf::Texture* backgroundTexture = m_backgroundSprite.getTexture();

    sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
    m_backgroundSprite.setScale(
        winSize.x / (float)backgroundTexture->getSize().x,
        winSize.y / (float)backgroundTexture->getSize().y
    );

    // Adjust button layout
    for (auto& btn : buttons) 
    {
        btn.resize(windowSize);
    }
}

void MenuScreen::handleEvent(const sf::Event& event) 
{
    if (event.type == sf::Event::Resized) 
    {
        // Adjust SFML view to match new window size
        sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        Game::getInstance().getWindow().setView(sf::View(visibleArea));

        setUpUi();
    }
    else if (event.type == sf::Event::MouseMoved) 
    {
        // Update hover state for each button based on mouse position
        float mouseX = static_cast<float>(event.mouseMove.x);
        float mouseY = static_cast<float>(event.mouseMove.y);
        for (auto& btn : buttons) {
            bool hovering = btn.contains(mouseX, mouseY);
            btn.setHover(hovering);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) 
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            float mouseX = static_cast<float>(event.mouseButton.x);
            float mouseY = static_cast<float>(event.mouseButton.y);
            // Check which button was clicked and execute its action
            for (auto& btn : buttons) 
            {
                if (btn.contains(mouseX, mouseY)) 
                {
                    btn.onClick();
                    break;  // Only trigger one button action on click
                }
            }
        }
    }
}



void MenuScreen::render(sf::RenderWindow& window) 
{
    // Draw background and then all buttons
    window.draw(m_backgroundSprite);
    for (auto& btn : buttons) {
        btn.draw(window);
    }
}



void MenuScreen::setActive(bool active)
{
    setUpUi();
    m_isActive = active;
}

void MenuScreen::reset() {}
void MenuScreen::update(float /*deltaTime*/){}