#include "Screens/GameScreen.h"


GameScreen::GameScreen(int level)
	:m_aquariumManager(Game::getInstance().getWindow().getSize()), m_isActive(false), m_currentLevel(level)
    ,m_shopBarManager(level),m_popUpMenu("Memu","popUp.png")
{
    m_popUpMenu.addButtons(std::make_unique<Button>("Continue", ResourceManager::getInstance().getGameFont(), std::make_unique<CommandFunction>([this]() { m_popUpMenu.setVisible(false); })));
    m_popUpMenu.addButtons(std::make_unique<Button>("Reset", ResourceManager::getInstance().getGameFont(), std::make_unique<CommandFunction>([this]() { reset(); })));
    /*m_popUpMenu.addButtons(std::make_unique<Button>("Mute", ResourceManager::getInstance().getGameFont(), std::make_unique<CommandFunction>([this]() { m_popUpMenu.setVisible(false); })));
    m_popUpMenu.addButtons(std::make_unique<Button>("Mute", ResourceManager::getInstance().getGameFont(), std::make_unique<ToggleMuteCommand>([this]() { m_popUpMenu.setVisible(false); })));
        */
    updateBackground();
    setUpUi();
}

GameScreen::~GameScreen()
{
    EventManager::getInstance().cleanUp();
	unRegisterEvents();

}


void GameScreen::registerEvents()
{
	m_aquariumManager.registerToEventManager();
	m_shopBarManager.registerToEventManager();
}


void GameScreen::handleEvent(const sf::Event& event)
{

    if (event.type == sf::Event::Resized) 
    {
        sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        Game::getInstance().getWindow().setView(sf::View(visibleArea));
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
            if (m_popUpMenu.isVisible())
            {
                m_popUpMenu.handleMouseClick(mousePos);
			}
            else if (mousePos.y <= m_shopBarManager.getSlotSize())
            {
                m_shopBarManager.handleMouseClick(mousePos);
            }
            else
            {
                m_aquariumManager.handleMouseClick(mousePos);
            }
            
        }
	}
    else if(event.type == sf::Event::MouseMoved) 
    {
        sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
        if (m_popUpMenu.isVisible() /*&& m_popUpMenu.handleMouseClick(mousePos)*/)
        {
            return;
        }
        else if (mousePos.y <= m_shopBarManager.getSlotSize() + 20)
        {
            m_shopBarManager.handleMouseHover(mousePos);
        }
        
	}
}

void GameScreen::update(float deltaTime) 
{
    if (!m_popUpMenu.isVisible())
    {
        m_aquariumManager.update(deltaTime);
    }
  

}

void GameScreen::render(sf::RenderWindow& window) 
{
    // Draw gameplay elements (for now, just the message text)
	
	
	window.draw(m_background);

    m_aquariumManager.draw(window);

	m_popUpMenu.render(window);
    m_shopBarManager.draw(window);
    
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

    
    m_popUpMenu.setUp();

    updateBackground();
 
}


void GameScreen::updateBackground()
{
	std::string backgroundFile = "aquarium" + std::to_string(m_currentLevel) + ".jpg";

   

    ResourceManager& resourceManager = ResourceManager::getInstance();
    resourceManager.loadSpriteSheet(backgroundFile, 1, 1);
    resourceManager.setSpriteTextureFromSheet(m_background, backgroundFile, 0, 0);
}

void GameScreen::unRegisterEvents()
{
    EventManager& manager = EventManager::getInstance();
    m_aquariumManager.unRegisterFromEventManager();
	m_shopBarManager.unRegisterFromEventManager();
}


void GameScreen::setActive(bool active)
{
	m_isActive = active;
    if (active)
    {
        setUpUi();
		//m_popUpMenu.setVisible(true);
        registerEvents();
    }
    else 
    {
		unRegisterEvents();
    }
}

void GameScreen::reset()
{
    m_aquariumManager.reset();
    m_shopBarManager.reset(m_currentLevel);
}