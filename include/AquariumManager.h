#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entities/Fish.h"
#include "Entities/Food.h"
#include "CollisionHandler.h"

//class Fish;

class AquariumManager
{
public:
	AquariumManager(sf::Vector2u windowSize);
	

	void handleMouseClick(const sf::Vector2f mousePos);
	void addEatable(std::unique_ptr<Eatable> eatable);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	//added
	static int getCoins(); // Add this line to the public section

private:
	bool isColliding(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
	bool handleCoinAndMonster(const sf::Vector2f mousePos);
	void destroyEaten();
	void checkCollisions(std::unique_ptr<Eatable>& eatable);
	std::unique_ptr<Money> checkProduceMoney(std::unique_ptr<Eatable>& eatable);
	//all with things out money
	std::vector<std::unique_ptr<Eatable>> m_eatables;


	static int m_coins;

	int m_maxFoodSpawned = 1;
	int m_foodCount = 0;

	sf::Vector2u m_windowSize;
};