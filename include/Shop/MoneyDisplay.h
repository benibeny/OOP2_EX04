#pragma once

#include "UI/UiElement.h"
#include "Commands/Command.h"

#define MONEY_DISPLAY_SPRITE "moneyBackground.jpg"
#define MONEY_START 200

class MoneyDisplay : public UiElement
{
public:
	
	MoneyDisplay();

	int getMoney() const;
	void changeMoney(int amount);

	void updateMoneyText();

	void reset();

	void setPosition(const sf::Vector2f& position) override;
	void draw(sf::RenderWindow& window)const override;

private:

	int m_money;
	sf::Text m_moneyText;
};