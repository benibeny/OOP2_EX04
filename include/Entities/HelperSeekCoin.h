#pragma once
#include "SeekingFoodAnimal.h"
#include <SFML/Graphics.hpp>




class HelperSeekCoin : public SeekingFoodAnimal
{
public:
	HelperSeekCoin(std::string spriteSheet,float speed);

	bool tryToEat(GameObject& food) override;


	bool canBeEatenBy(const NormalMonstar& monster);

	void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize);
	virtual void move(sf::Vector2u& windowSize, float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems);
private:

};