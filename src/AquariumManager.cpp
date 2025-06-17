#include "AquariumManager.h"


AquariumManager::AquariumManager(sf::Vector2u windowSize) 
	: m_windowSize(windowSize) 
{}


void AquariumManager::handleMouseClick(const sf::Vector2f mousePos)
{
	
	if (m_maxFoodSpawned > m_foodCount) 
	{
		m_eatables.push_back(std::make_unique<Food>(Food::Foodtype::Worst, mousePos));
		m_foodCount++;
	}
	
}

void AquariumManager::addEatable(std::unique_ptr<Eatable> eatable)
{
	if (eatable)
	{
		m_eatables.push_back(std::move(eatable));
	}
}


void AquariumManager::update(float deltaTime)
{
	std::vector<std::unique_ptr<Money>> coinsToAdd;
	for(auto& eatable : m_eatables)
	{
		if (eatable)
		{
			eatable->update(deltaTime, m_eatables, m_windowSize);
			checkCollisions(eatable);

			std::unique_ptr<Money> currentMoney =checkProduceMoney(eatable);
			if (currentMoney) 
			{
				coinsToAdd.push_back(std::move(currentMoney));
			}
		}
	}


	m_eatables.insert(m_eatables.end(), std::make_move_iterator(coinsToAdd.begin()), std::make_move_iterator(coinsToAdd.end()));
	destroyEaten();
}


void AquariumManager::draw(sf::RenderWindow& window)
{
	
	for (std::unique_ptr<Eatable>& eatable : m_eatables)
	{
		if (eatable)
		{
			eatable->draw(window);
		}
	}
}

void AquariumManager::destroyEaten()
{
	int foodCount = 0;
	int moneyCount = 0;

	for (const auto& eatable : m_eatables) 
	{
		if (eatable->isEaten())
		{
			if (typeid(*eatable) == typeid(Food))
			{
				foodCount++;
			}
			/*else if (typeid(*eatable) == typeid(Coin))
			{

			}*/
		}
	}

	m_eatables.erase(std::remove_if(m_eatables.begin(), m_eatables.end(),
		[](const std::unique_ptr<Eatable>& eatable)
		{
			return eatable->isEaten();
		}), m_eatables.end());

	m_foodCount -= foodCount;
}

//maybe a problem
//void AquariumManager::destroyEaten()
//{
//	int foodRemoved = 0;
//
//	auto newEnd = std::remove_if(m_eatables.begin(), m_eatables.end(),
//		[&foodRemoved](const std::unique_ptr<Eatable>& eatable)
//		{
//			if (eatable->isEaten()) 
//			{
//				if (eatable->getType() == Eatable::Type::Food) 
//				{
//					++foodRemoved;
//				}
//				return true;
//			}
//			return false;
//		});
//	m_eatables.erase(newEnd, m_eatables.end());
//	m_foodCount -= foodRemoved;
//}


void AquariumManager::checkCollisions(std::unique_ptr<Eatable>& eatable)
{
	for(std::unique_ptr<Eatable>& otherEatable : m_eatables)
	{
		if (otherEatable && eatable != otherEatable && eatable->getBounds().intersects(otherEatable->getBounds()))
		{
			processCollision(*eatable, *otherEatable);
		}
	}
}

std::unique_ptr<Money> AquariumManager::checkProduceMoney(std::unique_ptr<Eatable>& eatable)
{
	//TODO fix this typeid 
	if (typeid(*eatable) == typeid(GoldFish)) 
	{

		Fish* fish = static_cast<Fish*>(eatable.get());
		Money::Moneytype moneyToproduce = fish->shouldProduceMoney();
		if (moneyToproduce != Money::Moneytype::Invalid)
		{
			return std::make_unique<Money>(moneyToproduce, fish->getCenter());
			
		}
	}
	return nullptr; // No money produced in this case
}
