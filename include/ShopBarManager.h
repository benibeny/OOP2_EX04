#pragma once

#include "shopSlot.h"
#include "Game.h"
#include "MoneyDisplay.h"
#include "EventManager.h"

#include "Commands/CommandBuyGoldFish.h"
#include "Commands/CommandBuyFoodTier.h"
#include "Commands/CommandBuyFoodAmount.h"
#include "Commands/CommandBuyPirana.h"
#include "Commands/CommandOptions.h"
#include "Commands/CommandBuyWeapon.h"
#include "Commands/CommandBuyEgg.h"
#include "Commands/CommandBuyOctopusHelper.h"
#include "EggShopSlot.h"


#include <memory>
#include <vector>


#define MONEYBACKGROUND "moneyBackground.jpg"
#define MENUBACKGROUND "menu_slots.png" 

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

#define EGGSSLOT "eggs.png"
#define EGGSROW 12

#define HELPERSLOT "eggwalter.png"
#define HELPERROW 0


#define MAXSLOTS 7

#define FOOD_COST 5


class ShopBarManager
{
public:
	ShopBarManager(int level);
	
	void initialize(float slotSize);
	void handleMouseClick(const sf::Vector2f& mousePos);
	void handleMouseHover(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window) const;
	float getSlotSize() const { return m_slotSize; }
	void reset(int level);

	void unRegisterFromEventManager();
	void registerToEventManager();

private:
	//std::vector<ShopSlot> m_shopSlots;
	std::vector<std::unique_ptr<ShopSlot>> m_shopSlots;


	MoneyDisplay m_moneyDisplay;
	Clickable m_OptionButton;

	float m_slotSize ;	


	struct EventSubscription
	{
		std::function<void()> unsubscribe;
	};

	std::vector<EventSubscription> m_eventSubscriptions;
};