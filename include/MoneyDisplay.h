#pragma once

#include "UiElement.h"
#include "Commands/Command.h"

#define MONEY_DISPLAY_SPRITE "moneyBackground.jpg"
#define MONEY_START 200 

class MoneyDisplay : public UiElement
{
public:
	
	MoneyDisplay();

	int getMoney() const;
	void addMoney(int amount);
	void subtractMoney(int amount);
	void updateMoneyText();

private:

	int m_money = 0;
	sf::Text m_moneyText;
};