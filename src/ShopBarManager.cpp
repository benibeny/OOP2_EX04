#include "ShopBarManager.h"

ShopBarManager::ShopBarManager()
	:m_OptionButton(Clickable(std::make_unique<CommandOptions>(), MENUBACKGROUND)),m_slotSize(0.0f)
{
	m_shopSlots.emplace_back(ShopSlot(100, std::make_unique<CommandBuyGoldFish>(), GOLDFISHSLOT, GOLDFISHROW, false));
	m_shopSlots.emplace_back(ShopSlot(200,std::make_unique<CommandBuyFoodTier>(), FOODSLOT, FOODROW));
	m_shopSlots.emplace_back(ShopSlot(300,std::make_unique<CommandBuyFoodAmount>(), NUMBERFOODSLOT, NUMBERFOODROW));
	m_shopSlots.emplace_back(ShopSlot(1000,std::make_unique<CommandBuyPirana>(), PIRANASLOT, PIRANAROW, false));
	m_shopSlots.emplace_back(ShopSlot(1000,std::make_unique<CommandBuyWeapon>(), WEPONSLOT, WEPONROW));
	m_shopSlots.emplace_back(ShopSlot(10,std::make_unique<CommandBuyGoldFish>(), GOLDFISHSLOT, GOLDFISHROW));
	m_shopSlots.emplace_back(EggShopSlot(1000,std::make_unique<CommandBuyEgg>(), WEPONSLOT, WEPONROW));

	registerToEventManager();
}

void ShopBarManager::registerToEventManager() 
{
	EventManager& eventManager = EventManager::getInstance();
	eventManager.subscribeToMoneyClick([this](int moneyValue)
		{
			m_moneyDisplay.addMoney(moneyValue);

		});
}

void ShopBarManager::initialize(float slotSize)
{
	sf::Vector2u windowSize = Game::getInstance().getWindow().getSize();

	for(int i = 0; i < m_shopSlots.size(); ++i)
	{
		m_shopSlots[i].setPosition(sf::Vector2f(i * slotSize, 0));
		m_shopSlots[i].setSize(slotSize, slotSize);

	}
	float endOfSlots = m_shopSlots.size() * slotSize;
	float optionMoneyWidth = windowSize.x - endOfSlots;
	m_OptionButton.setPosition(sf::Vector2f(endOfSlots, 0));
	m_OptionButton.setSize(optionMoneyWidth, slotSize/2);


	m_moneyDisplay.setSize(optionMoneyWidth, slotSize / 2);
	m_moneyDisplay.setPosition(sf::Vector2f(endOfSlots, slotSize / 2));
	

	m_slotSize = slotSize;

}

void ShopBarManager::handleMouseClick(const sf::Vector2f& mousePos)
{
	for (auto& slot : m_shopSlots)
	{
		if(slot.isMouseOver(mousePos))
		{
			int slotPrice = slot.getPrice();
			if (m_moneyDisplay.getMoney() >= slotPrice && !slot.isMaxBought())
			{
				slot.onClick();
				m_moneyDisplay.subtractMoney(slotPrice);
			}
			
		}
	}
}

void ShopBarManager::draw(sf::RenderWindow& window) const
{
	for(const auto& slot : m_shopSlots)
	{
		slot.draw(window);
	}
	m_OptionButton.draw(window);
	m_moneyDisplay.draw(window);
}
