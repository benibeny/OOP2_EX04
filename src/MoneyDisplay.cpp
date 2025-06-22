#include "MoneyDisplay.h"


MoneyDisplay::MoneyDisplay() 
	:UiElement(MONEY_DISPLAY_SPRITE,1,1), m_money(MONEY_START)
{
	m_moneyText.setFont(ResourceManager::getInstance().getGameFont());
	m_moneyText.setCharacterSize(20);
	m_moneyText.setFillColor(sf::Color::Green);
}


int MoneyDisplay::getMoney() const 
{ 
	return m_money;
}


void MoneyDisplay::addMoney(int amount)
{
	m_money += amount; updateMoneyText();
}


void MoneyDisplay::subtractMoney(int amount)
{ 
	m_money -= amount; updateMoneyText();
}


void MoneyDisplay::updateMoneyText() 
{
	m_moneyText.setString("$" + std::to_string(m_money));
	sf::FloatRect textBounds = m_moneyText.getLocalBounds();
	m_moneyText.setPosition(m_position.x + (m_size.x - textBounds.width) / 2.0f,
							m_position.y + (m_size.y - textBounds.height) / 2.0f);
}