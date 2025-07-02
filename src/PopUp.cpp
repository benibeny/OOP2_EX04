#include "PopUp.h"

PopUp::PopUp(std::string titleName, std::string spriteName)
	: m_visible(false)
{
	ResourceManager &resource= ResourceManager::getInstance();
		
	resource.loadSpriteSheet(spriteName,1,1);
	resource.setSpriteTextureFromSheet(m_background, spriteName, 0, 0);
	
	m_title.setFont(resource.getGameFont());
	m_title.setString(titleName);
	m_title.setCharacterSize(Game::BASE_FONT_SIZE);
}

void PopUp::addButtons(std::unique_ptr<Button> button)
{
	m_buttons.emplace_back(std::move(button));
}

void PopUp::setUp()
{
	sf::RenderWindow& window = Game::getInstance().getWindow();
	sf::Vector2u windowSize = window.getSize();


	const sf::Texture* backgroundTexture = m_background.getTexture();
	m_background.setScale(
		(static_cast<float>(windowSize.x) / backgroundTexture->getSize().x) * 0.5f,
		(static_cast<float>(windowSize.y) / backgroundTexture->getSize().y) * 0.5f
	);

	m_background.setPosition(
		(windowSize.x - m_background.getGlobalBounds().width) / 2.f,
		(windowSize.y - m_background.getGlobalBounds().height) / 2.f
	);

	m_title.setPosition(
		(m_background.getPosition().x + m_background.getGlobalBounds().width / 2.f - m_title.getLocalBounds().width / 2.f),
		m_background.getPosition().y * 1.1f
	);
}


void PopUp::render(sf::RenderWindow& window)
{
	if (m_visible)
	{
		window.draw(m_background);
		window.draw(m_title);
		for (const auto& button : m_buttons)
		{
			button->draw(window);
		}
	}
}

void PopUp::handleMouseClick(const sf::Vector2f& mousePos)
{

}


void PopUp::handleMouseHover(const sf::Vector2f& mousePos)
{

}

void PopUp::setVisible(bool visible)
{
	m_visible = visible;
}

bool PopUp::isVisible() const
{
	return m_visible;
}
