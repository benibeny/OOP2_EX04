#include "Entities/GoldFish.h"


GoldFish::GoldFish(sf::Vector2f pos)
	:Fish(pos, GOLDFISH_SPEED, MOVE_ONE_DIRC_SPRITE_NAME,5, MAX_FRAMES,2, TURNING_SPRITE_NAME),
	m_fishSize(Size::Small)
{
	ResourceManager::getInstance().loadSpriteSheet(TURNING_SPRITE_NAME, MAX_FRAMES, 5);
	ResourceManager::getInstance().loadSpriteSheet("smalldie.png", 10, 5); //add 10 frames, 5 rows 

	m_sprite.setScale(0.8f, 0.8f);

	m_random.seed(std::random_device{}());
}


void GoldFish::update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)
{
	if (updateDeathAnimation(deltaTime)) 
	{
		return;
	}
	updateFishSize();
	handleHungerTimer(deltaTime);
	move(windowSize, deltaTime, foodItems);
	
	shouldProduceMoney(deltaTime);
	
	updateAnimation(deltaTime);
}





void GoldFish::shouldProduceMoney(float deltaTime)
{
	if (m_fishSize != Size::Small && m_coinTimer >= m_maxCoinTimer && m_health > m_fishStartHunger)
	{
		sf::Vector2f center = m_sprite.getPosition() + sf::Vector2f(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
		m_coinTimer = 0;
		EventManager::getInstance().notifyCreateMoney(int(getProducedMoneyType()), center);
	}
	m_coinTimer += deltaTime;// Update coin timer
}


Money::Moneytype GoldFish::getProducedMoneyType()
{
	if (m_fishSize == Size::Medium)
	{
		return Money::Moneytype::Silver;
	}
	else if (m_fishSize == Size::Large)
	{
		return Money::Moneytype::Gold;
	}

	return Money::Moneytype::Invalid;
}


void GoldFish::updateFishSize()
{
	Size newSize = m_fishSize;
	int foodEaten = getFoodEaten();
	if (foodEaten >= BAR_REACH_LARGE_FISH_SIZE && newSize != Size::Large)
	{
		newSize = Size::Large;
	}
	else if( foodEaten >= BAR_REACH_MEDIUM_FISH_SIZE && foodEaten < BAR_REACH_LARGE_FISH_SIZE && newSize != Size::Medium)
	{
		newSize = Size::Medium;
	}
	
	if (newSize != m_fishSize)
	{
		m_fishSize = newSize;
		float scale = (int)m_fishSize / 10.0f;

		sf::Vector2f currPos = m_sprite.getPosition();
		sf::Vector2f currScale = m_sprite.getScale();
		
		float newScaleX = (currScale.x < 0) ? -scale : scale;


		m_sprite.setScale(newScaleX, scale);
		m_sprite.setPosition(currPos);
	}
	
}


bool GoldFish::tryToEat(GameObject& food)
{
	return food.canBeEatenBy(*this);
}

bool GoldFish::canBeEatenBy(const Pirana& pirana)
{
	return m_fishSize == Size::Small;
}

bool GoldFish::canBeEatenBy(const NormalMonstar& monster)
{
	return true;
}


int GoldFish::getDeathRow() const 
{
	if (m_fishSize == Size::Small)
		return 0;
	else if (m_fishSize == Size::Medium)
		return 1;
	else // Size::Large
		return 2;
}
