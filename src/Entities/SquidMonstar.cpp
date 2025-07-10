#include "Entities/SquidMonstar.h"


SquidMonstar::SquidMonstar()
	:NormalMonstar(NORMALMONSTAR_SPEED, NORMALMONSTAR_SPRITE, 5,200)
{
	std::uniform_real_distribution<float> interval(2.0f, MAX_COLOR_CHANGE_TIME);
	m_nextColorChangeThreshold = interval(m_random);
}


void SquidMonstar::update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)
{
	m_colorChangeTimer += deltaTime;
	if (m_colorChangeTimer >= m_nextColorChangeThreshold)
	{
		m_isBlue = !m_isBlue;
		m_colorChangeTimer = 0.0f;
		std::uniform_real_distribution<float> interval(2.0f, MAX_COLOR_CHANGE_TIME);
		m_nextColorChangeThreshold = interval(m_random);

		if (m_isBlue)
		{
			m_sheetRowIndex = 2; // Blue color
		}
		else
		{
			m_sheetRowIndex = 0; // Default color
		}
	}

	NormalMonstar::update(deltaTime, foodItems, windowSize);
}

void SquidMonstar::clicked(int damage, sf::Vector2f mousePos) 
{
	if (m_isBlue)
	{
		damage *= -1;
	}

	NormalMonstar::clicked(damage, mousePos);
}