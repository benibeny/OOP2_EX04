#include "Managers/ShopBarManager.h"
#include "Managers/SoundManager.h"

ShopBarManager::ShopBarManager(int level)
	:m_OptionButton(Clickable(std::make_unique<CommandOptions>(), MENUBACKGROUND)),m_slotSize(0.0f)
{
	int eggPrice = 250, eggRow = 0;
	for (int i = 1; i < level; i++)
	{
		eggPrice *= 2;
		eggRow += 3;
		
	}


	m_shopSlots.emplace_back(std::make_unique<ShopSlot>(100, std::make_unique<CommandBuyGoldFish>(), GOLDFISHSLOT, GOLDFISHROW,0, false));
	m_shopSlots.emplace_back(std::make_unique<ShopSlot>(200,std::make_unique<CommandBuyFoodTier>(), FOODSLOT, FOODROW));
	m_shopSlots.emplace_back(std::make_unique<ShopSlot>(300,std::make_unique<CommandBuyFoodAmount>(), NUMBERFOODSLOT, NUMBERFOODROW));
	m_shopSlots.emplace_back(std::make_unique<ShopSlot>(1000,std::make_unique<CommandBuyPirana>(), PIRANASLOT, PIRANAROW,0, false));
	m_shopSlots.emplace_back(std::make_unique<ShopSlot>(1000,std::make_unique<CommandBuyWeapon>(), WEPONSLOT, WEPONROW));
	m_shopSlots.emplace_back(std::make_unique<ShopSlot>(1500, std::make_unique<CommandBuyHelper>(), HELPERSLOT, HELPERROW, 0, false));
	m_shopSlots.emplace_back(std::make_unique<EggShopSlot>(eggRow,eggPrice,std::make_unique<CommandBuyEgg>(level+1), EGGSSLOT, EGGSROW));

}

void ShopBarManager::registerToEventManager() 
{
	EventManager& manager = EventManager::getInstance();
	
	auto moneyChange = [this](int moneyValue)
		{
			m_moneyDisplay.changeMoney(moneyValue);
		};
	manager.subscribeToMoneyChange(moneyChange);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromMoneyChange(moneyChange); }
		});

	auto tryBuyFood = [this]()
		{
			if (m_moneyDisplay.getMoney() >= FOOD_COST) 
			{
				m_moneyDisplay.changeMoney(-FOOD_COST);
				return true;
			}
			SoundManager::getInstance().play("buzzer");
			return false;
		};
	manager.subscribeToTryBuyFood(tryBuyFood);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromTryBuyFood(); }
		});
}

void ShopBarManager::initialize(float slotSize)
{
	sf::Vector2u windowSize = Game::getInstance().getWindow().getSize();

	for(int i = 0; i < m_shopSlots.size(); ++i)
	{
		m_shopSlots[i]->setPosition(sf::Vector2f(i * slotSize, 0));
		m_shopSlots[i]->setSize(slotSize, slotSize);

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
		if(slot->isMouseOver(mousePos))
		{
			int slotPrice = slot->getPrice();
			if (m_moneyDisplay.getMoney() >= slotPrice && !slot->isMaxBought())
			{
				m_moneyDisplay.changeMoney(-slotPrice);
				slot->onClick();
			}
			else if (m_moneyDisplay.getMoney() < slotPrice) 
			{
				SoundManager::getInstance().play("buzzer");
			}

			
		}
		else if (m_OptionButton.isMouseOver(mousePos)) 
		{
			m_OptionButton.onClick();
		}
	}
}

void ShopBarManager::handleMouseHover(const sf::Vector2f& mousePos)
{
	for (auto& slot : m_shopSlots)
	{

		bool isOver = slot->isMouseOver(mousePos);
		slot->changeHoverSprite(isOver);
	}
	
	bool isOverOptionButton = m_OptionButton.isMouseOver(mousePos);
	m_OptionButton.changeHoverSprite(isOverOptionButton);
}


void ShopBarManager::draw(sf::RenderWindow& window) const
{
	for(const auto& slot : m_shopSlots)
	{
		slot->draw(window);
	}
	m_OptionButton.draw(window);
	m_moneyDisplay.draw(window);
}


void ShopBarManager::reset(int level)
{
	int eggRow = 0;
	for (int i = 1; i < level; i++)
	{
		eggRow += 3;
	}

	for (int i = 0; i < m_shopSlots.size()-1; ++i)
	{
		m_shopSlots[i]->reset(0);
	}
	m_shopSlots.back()->reset(eggRow);
	m_moneyDisplay.reset();
}


void ShopBarManager::unRegisterFromEventManager()
{

	for (auto& subscription : m_eventSubscriptions)
	{
		subscription.unsubscribe();
	}
	m_eventSubscriptions.clear();
}