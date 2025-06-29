#include "Screens/ChooseLevelScreen.h"

ChooseLevelScreen::ChooseLevelScreen()
{
	sf::RenderWindow& window = Game::getInstance().getWindow();
	sf::Vector2u windowSize = window.getSize();

	ResourceManager& resourceManager = ResourceManager::getInstance();
	resourceManager.loadSpriteSheet(CHOOSE_SCREEN_BACKGROUND,1,1);
	resourceManager.setSpriteTextureFromSheet(m_backgroundSprite, CHOOSE_SCREEN_BACKGROUND, 0, 0);

	const sf::Texture* backgroundTexture = m_backgroundSprite.getTexture();
	m_backgroundSprite.setScale(
		static_cast<float>(windowSize.x) / backgroundTexture->getSize().x,
		static_cast<float>(windowSize.y) / backgroundTexture->getSize().y
	);

	sf::Font& font = resourceManager.getGameFont();

	for (int i = 0; i < MAX_LEVELS; i++)
	{
		m_buttons.emplace_back("Level " + std::to_string(i + 1), font, std::make_unique<StartLevelCommand>(i+1));
		float xPos = 0.75f;
		float yPos = 0.18f + i * 0.21f;
		m_buttons[i].setRelativePosition(xPos, yPos);
		m_buttons[i].setBaseCharacterSize(Game::BASE_FONT_SIZE);
		m_buttons[i].resize(windowSize);
		m_buttons[i].setColor(sf::Color::Transparent);
	}


	
}

void ChooseLevelScreen::render(sf::RenderWindow& window)
{
	window.draw(m_backgroundSprite);
	for (int i = 0; i< m_currentAmountOfLevels; i++)
	{
		m_buttons[i].draw(window);
	}


}


void ChooseLevelScreen::handleEvent(const sf::Event& event)
{
	if (event.type== sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left)
	{
		float mouseX = static_cast<float>(event.mouseButton.x);
		float mouseY = static_cast<float>(event.mouseButton.y);
		for (int i = 0; i < m_currentAmountOfLevels; i++)
		{
			if (m_buttons[i].contains(mouseX, mouseY))
			{
				m_buttons[i].onClick();
				break;
			}
		}
	}
	else if( event.type == sf::Event::MouseMoved)
	{
		float mouseX = static_cast<float>(event.mouseMove.x);
		float mouseY = static_cast<float>(event.mouseMove.y);
		for (int i = 0; i < m_currentAmountOfLevels; i++)
		{
			bool isHovering = m_buttons[i].contains(mouseX, mouseY);
			m_buttons[i].setHover(isHovering);
		}
	}

}



void ChooseLevelScreen::update(float deltaTime)
{
}