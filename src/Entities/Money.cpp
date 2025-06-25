#include "Entities/Money.h"

Money::Money(Moneytype moneyType, const sf::Vector2f pos)
	:GameObject(Type::Money, pos, MONEY_SPRITE_SHEET_NAME, 6, 10, int(moneyType),40), m_moneyType(moneyType)
{
	m_sprite.setScale(1.5f, 1.5f);

	switch (moneyType)
	{
	case Moneytype::Silver:
		m_moneyValue = 10;
		break;

	case Moneytype::Gold:
		m_moneyValue = 20;
		break;

	case Moneytype::Diamond:
		m_moneyValue = 50;
		break;

	default:
		m_moneyValue = 0;
		break;
	}

	
	
}


void Money::update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)
{
	if (!m_shouldDestroy)
	{
		if (!m_touchedFloor)
		{
			sf::Vector2f currentPos = getPosition();
			sf::Vector2f newPos = currentPos + m_velocity * deltaTime;

			setPosition(newPos);
		}
		
		updateAnimation(deltaTime);
		checkTouchedFloor(windowSize, deltaTime);

	}
}


void Money::checkTouchedFloor(sf::Vector2u& windowSize, float deltaTime)
{
	

	sf::Vector2f position = m_sprite.getPosition();
	sf::FloatRect bounds = m_sprite.getGlobalBounds();


	float sandBarHeight = windowSize.y / 10.0f;



	if (position.y + bounds.height > (windowSize.y - sandBarHeight))
	{
		m_floorTimer += deltaTime;
		m_touchedFloor = true;

		if (m_floorTimer >= TIME_ON_FLOOR)
		{
			m_shouldDestroy = true;
		}
	}

}


void Money::clicked(int damage, sf::Vector2f mousePos)
{
	setDestroyed(true);
	EventManager::getInstance().notifyMoneyClick(getMoneyValue());
}