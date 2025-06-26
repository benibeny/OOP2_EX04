#include "Screens/GameScreen.h"


GameScreen::GameScreen()
	:m_aquariumManager(Game::getInstance().getWindow().getSize()), m_isActive(false), m_currentLevel(1)
{

    updateBackground();
    setUpUi();
    m_aquariumManager.addEatable(std::make_unique<GoldFish>(sf::Vector2f(200.f, 200.f)));
    m_aquariumManager.addEatable(std::make_unique<GoldFish>(sf::Vector2f(300.f, 300.f)));

    registerEvents();
	
   
}

GameScreen::~GameScreen()
{
    EventManager::getInstance().cleanUp();
}


void GameScreen::registerEvents()
{
    EventManager& manager = EventManager::getInstance();

    manager.subscribeToNextLevel([this]()
        {
			m_currentLevel++;
            updateBackground();
        });
}


void GameScreen::handleEvent(const sf::Event& event)
{

    if (event.type == sf::Event::Resized) 
    {
		setUpUi();
    }
    else if (event.type == sf::Event::KeyPressed) 
    {
        if (event.key.code == sf::Keyboard::Escape) 
        {
            // Press ESC to return to the main menu
            ScreenManager::getInstance().switchScreen(ScreenType::MainMenu);
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed) 
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            if (mousePos.y <= m_shopBarManager.getSlotSize())
            {
                m_shopBarManager.handleMouseClick(mousePos);
            }
            else
            {
                m_aquariumManager.handleMouseClick(mousePos);
            }
            
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

	

	float slotSize = winSize.x / 9.0f;// 9 slots in the shop bar
	m_shopBarManager.initialize(slotSize);

    float aquariumHeight = winSize.y - slotSize;
    
	const sf::Texture* texture = m_background.getTexture();

    m_background.setPosition(0, slotSize);
    if (texture)
    {
        m_background.setScale(sf::Vector2f(static_cast<float>(winSize.x) / texture->getSize().x,
            aquariumHeight / texture->getSize().y));
    }

    
	

    updateBackground();
 
}


void GameScreen::updateBackground()
{
	std::string backgroundFile = "aquarium" + std::to_string(m_currentLevel) + ".jpg";

   

    ResourceManager& resourceManager = ResourceManager::getInstance();
    resourceManager.loadSpriteSheet(backgroundFile, 1, 1);
    resourceManager.setSpriteTextureFromSheet(m_background, backgroundFile, 0, 0);
}
