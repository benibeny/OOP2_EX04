#pragma once
#include "ResourceManager.h"
#include "Entities/Eatable.h"
#include <SFML/Graphics.hpp>


#define MONEY_SPRITE_SHEET_NAME "Money.png"

class Money : public Eatable
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
	
	
	void update(float deltaTime, const std::vector <std::unique_ptr<Eatable>>& foodItems, sf::Vector2u& windowSize) override;
	int getMoneyValue() const { return m_moneyValue; }
private:
	void checkTouchedFloor(sf::Vector2u& windowSize, float deltaTime);

	bool m_touchedFloor = false;
	float m_floorTimer = 0;
	static constexpr float TIME_ON_FLOOR = 1.5f;

	const sf::Vector2f m_velocity = sf::Vector2f(0.0f, 50.0f);

	int m_moneyValue;

	Moneytype m_moneyType;
};