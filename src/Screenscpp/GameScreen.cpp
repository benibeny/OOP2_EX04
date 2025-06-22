#include "Screens/GameScreen.h"


GameScreen::GameScreen()
    :m_aquariumManager(Game::getInstance().getWindow().getSize())
{
    setUpUi();
    m_aquariumManager.addEatable(std::make_unique<GoldFish>(sf::Vector2f(200.f, 200.f)));
    m_aquariumManager.addEatable(std::make_unique<GoldFish>(sf::Vector2f(300.f, 300.f)));
   
}

void GameScreen::handleEvent(const sf::Event& event) 
{
    if (event.type == sf::Event::Resized) 
    {
        // Re-center and resize text when window size changes
        /*sf::Vector2u newSize(event.size.width, event.size.height);
        float widthRatio = newSize.x / 800.0f;
        unsigned int newCharSize = static_cast<unsigned int>(Game::BASE_FONT_SIZE * widthRatio);
        if (newCharSize < 5) newCharSize = 5;
        text.setCharacterSize(newCharSize);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        text.setPosition(newSize.x / 2.0f, newSize.y / 2.0f);*/
    }
    else if (event.type == sf::Event::KeyPressed) 
    {
        if (event.key.code == sf::Keyboard::Escape) 
        {
            // Press ESC to return to the main menu
            ScreenManager::getInstance().switchScreen(new MenuScreen());
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed) 
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            m_aquariumManager.handleMouseClick(mousePos);
        }
	}
}

void GameScreen::update(float deltaTime) 
{
	sf::Vector2u winSize = Game::getInstance().getWindow().getSize();

    m_aquariumManager.update(deltaTime);
    
  

}

void GameScreen::render(sf::RenderWindow& window) 
{
    // Draw gameplay elements (for now, just the message text)
	
	m_shopBarManager.draw(window);
	window.draw(m_background);

    m_aquariumManager.draw(window);
}


void GameScreen::setUpUi()
{
    sf::Vector2u winSize = Game::getInstance().getWindow().getSize();

    if (!m_backgroundTexture.loadFromFile("aquarium1.jpg"))
    {
        std::cerr << "Failed to load background image!\n";
    }


	float slotSize = winSize.x / 11.0f;// 11 slots in the shop bar
	m_shopBarManager.initialize(slotSize);




 

    float aquariumHeight = winSize.y - slotSize;
    
    m_background.setPosition(0, slotSize);
	m_background.setScale(sf::Vector2f(static_cast<float>(winSize.x) / m_backgroundTexture.getSize().x,
                                                      aquariumHeight / m_backgroundTexture.getSize().y));
    m_background.setTexture(m_backgroundTexture);


}