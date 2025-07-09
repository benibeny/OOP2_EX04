#pragma once
#include "ResourceManager.h"
#include "Entities/GameObject.h"

#include <SFML/Graphics.hpp>
#include "EventManager.h"


#define MONEY_SPRITE_SHEET_NAME "Money.png"


class Money : public GameObject
{
public:

	enum class Moneytype
	{
		Silver,
		Gold,
		Diamond = 3,//index for the sprite in the sprite sheet
		Invalid = -1
	};

	Money(Moneytype moneyType, const sf::Vector2f pos);
	
	void clicked(int damage =0 , sf::Vector2f mousePos = sf::Vector2f(0.0f,0.0f)) override;
	void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize) override;
	int getMoneyValue() const { return m_moneyValue; }

	bool canBeEatenBy(const HelperSeekCoin& helperJellyfish)override;

private:
	void checkTouchedFloor(sf::Vector2u& windowSize, float deltaTime);

	static constexpr float TIME_ON_FLOOR = 1.5f;
	const sf::Vector2f m_velocity = sf::Vector2f(0.0f, 50.0f);

	bool m_touchedFloor = false;
	float m_floorTimer = 0;
	int m_moneyValue;
	Moneytype m_moneyType;

	
};