#include "Entities/Pirana.h"
#include "SoundManager.h"


Pirana::Pirana(sf::Vector2f pos)
	:Fish(pos, PIRANA_SPEED, MOVE_ONE_DIRC_SPRITE_NAME, 5, MAX_FRAMES, 4, TURNING_SPRITE_NAME)
{
	ResourceManager::getInstance().loadSpriteSheet(TURNING_SPRITE_NAME, MAX_FRAMES, 5);
	ResourceManager::getInstance().loadSpriteSheet("smalldie.png", 10, 5);

	m_sprite.setScale(1.2f, 1.2f);

	m_random.seed(std::random_device{}());
}


void Pirana::update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)
{

	if (updateDeathAnimation(deltaTime)) 
	{
		return;
	}

	handleHungerTimer(deltaTime);
	move(windowSize, deltaTime, foodItems);

	shouldProduceMoney(deltaTime);

	updateAnimation(deltaTime);
}




void Pirana::foodEatenIncrement(std::pair<int, int> foodValue)
{
	m_health += 50; //pirana hunger
	SoundManager::getInstance().play("alienEat");
}


void Pirana::shouldProduceMoney(float deltaTime)
{
	if (m_coinTimer >= m_maxCoinTimer && m_health > m_fishStartHunger)
	{
		sf::Vector2f center = m_sprite.getPosition() + sf::Vector2f(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
		m_coinTimer = 0;
		EventManager::getInstance().notifyCreateMoney(int(getProducedMoneyType()), center);
	}
	m_coinTimer += deltaTime;// Update coin timer
}


Money::Moneytype Pirana::getProducedMoneyType()
{
	return Money::Moneytype::Diamond;
}








bool Pirana::tryToEat(GameObject& food)
{
	return food.canBeEatenBy(*this);
}


bool Pirana::canBeEatenBy(const NormalMonstar& monster)
{
	return true; // Pirana can be eaten by any NormalMonstar
}

int Pirana::getDeathRow() const 
{
	return 4;  
}
