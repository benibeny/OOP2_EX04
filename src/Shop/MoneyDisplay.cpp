#include "Shop/MoneyDisplay.h"


MoneyDisplay::MoneyDisplay() 
	:UiElement(MONEY_DISPLAY_SPRITE,1,1), m_money(MONEY_START)
{
	m_moneyText.setFont(ResourceManager::getInstance().getGameFont());
	m_moneyText.setCharacterSize(20);
	m_moneyText.setFillColor(sf::Color::Green);

	updateMoneyText();
}


int MoneyDisplay::getMoney() const 
{ 
	return m_money;
}


void MoneyDisplay::changeMoney(int amount)
{
	m_money += amount;
	updateMoneyText();
}

void MoneyDisplay::setSize(const float width, const float height)
{
	UiElement::setSize(width, height);

	unsigned int fontSize = static_cast<unsigned int>(height * 0.6f);
	m_moneyText.setCharacterSize(fontSize);


	updateMoneyText();  
}


void MoneyDisplay::updateMoneyText() 
{
	m_moneyText.setString("$" + std::to_string(m_money));
	sf::FloatRect textBounds = m_moneyText.getLocalBounds();

	m_moneyText.setOrigin(textBounds.left + textBounds.width / 2.f,
		textBounds.top + textBounds.height / 2.f);
	m_moneyText.setPosition(m_position.x + m_size.x / 2.f,
		m_position.y + m_size.y / 2.f);
}


void MoneyDisplay::draw(sf::RenderWindow& window)const
{
	UiElement::draw(window);
	window.draw(m_moneyText);
}

void MoneyDisplay::setPosition(const sf::Vector2f& position)
{
	UiElement::setPosition(position);
	updateMoneyText();
}

void MoneyDisplay::reset()
{
	m_money = MONEY_START;
	updateMoneyText();
}