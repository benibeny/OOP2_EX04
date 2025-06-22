#pragma once

#include "shopSlot.h"
#include "Game.h"
#include "MoneyDisplay.h"

#include "Commands/CommandBuyGoldFish.h"
#include "Commands/CommandOptions.h"

#include <memory>
#include <vector>


#define MONEYBACKGROUND "moneyBackground.jpg"

#define FOODSLOT "foodSlot.png"
#define FOODROW 2

#define GOLDFISHSLOT "goldFishSlot.png"
#define GOLDFISHROW 1

#define PIRANASLOT "PiranaSlot.png"
#define PIRANAROW 1

#define NUMBERFOODSLOT "numberFoodSlot.png"
#define NUMBERFOODROW 8

#define WEPONSLOT "weponSlot.png"
#define WEPONROW 10


#define MAXSLOTS 7




class ShopBarManager
{
public:
	ShopBarManager();
	
	void initialize(float slotSize);
	void handleClick(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window) const;
private:
	std::vector<ShopSlot> m_shopSlots;


	MoneyDisplay m_moneyDisplay;
	Clickable m_OptionButton;

	float m_slotSize ;	
};