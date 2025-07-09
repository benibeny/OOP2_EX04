#include "Entities/GameObject.h"


GameObject::GameObject(sf::Vector2f pos, const std::string& spriteName, const int sheetRows, const int sheetCols, const int animationRow,int spriteReduction)
	: m_spriteName(spriteName), m_shouldDestroy(false), m_sheetCols(sheetCols), m_animationTimer(0.f), m_animationFrame(0), m_sheetRowIndex(animationRow), m_isSpriteLoaded(false), m_spriteReduction(spriteReduction)
{
	ResourceManager& resourceManager = ResourceManager::getInstance();
	resourceManager.loadSpriteSheet(spriteName, sheetCols, sheetRows);
	resourceManager.setSpriteTextureFromSheet(m_sprite, spriteName, m_animationFrame, animationRow, m_spriteReduction);
	

	sf::Vector2f scale = m_sprite.getScale();
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	sf::Vector2f center(bounds.width * scale.x / 2.f, bounds.height * scale.y / 2.f);

	m_sprite.setPosition(pos.x - center.x,pos.y - center.y);

	if (m_sprite.getTexture()) 
	{
		m_isSpriteLoaded = true;
	}
}



void GameObject::draw(sf::RenderWindow& window)
{
	if (m_isSpriteLoaded) 
	{
		window.draw(m_sprite);
	}
	else 
	{
		std::cout << "Sprite not loaded: " << m_spriteName << std::endl;
	}
}

bool GameObject::isDestroyed() const
{
	return m_shouldDestroy;
}

void GameObject::setDestroyed(bool destroyed)
{
	m_shouldDestroy = destroyed;
}


void GameObject::updateAnimation(float deltaTime)
{
	m_animationTimer += deltaTime;
	if (m_animationTimer >= 0.2f) // Adjust the speed of the animation here
	{
		m_animationTimer = 0.f;
		m_animationFrame = (m_animationFrame + 1) % m_sheetCols; // Loop through frames
		ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, m_spriteName, m_animationFrame, m_sheetRowIndex,m_spriteReduction);
	}
	
}

sf::FloatRect GameObject::getBounds() const
{
	if (m_isSpriteLoaded)
	{
		return m_sprite.getGlobalBounds();
	}
	return sf::FloatRect();
}


sf::Vector2f GameObject::getPosition() const
{
	if (m_isSpriteLoaded)
	{
		return m_sprite.getPosition();
	}
	return sf::Vector2f(0.f, 0.f);
}


sf::Vector2f GameObject::getCenter() const
{
	if (m_isSpriteLoaded)
	{
		sf::FloatRect bounds = m_sprite.getGlobalBounds();
		return sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	}
	return sf::Vector2f(0.f, 0.f);
	
}

bool GameObject::canBeEatenBy(const Fish& gameObject) const
{
	return false;
}

bool GameObject::canBeEatenBy(const GoldFish& goldFish)
{
	return false;
}

bool GameObject::canBeEatenBy(const Pirana& pirana)
{
	return false;
}

bool GameObject::canBeEatenBy(const NormalMonstar& monster)
{
	return false;
}

bool GameObject::canBeEatenBy(const Money& money)
{
	return false;
}

bool GameObject::canBeEatenBy(const Food& food)
{
	return false;
}
bool GameObject::canBeEatenBy(const HelperSeekCoin& food)
{
	return false;
}