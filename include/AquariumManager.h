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

private:
	void destroyEaten();
	void checkCollisions(std::unique_ptr<Eatable>& eatable);
	std::unique_ptr<Money> checkProduceMoney(std::unique_ptr<Eatable>& eatable);
	//all with things out money
	std::vector<std::unique_ptr<Eatable>> m_eatables;


	int m_maxFoodSpawned = 1;
	int m_foodCount = 0;

	sf::Vector2u m_windowSize;
};