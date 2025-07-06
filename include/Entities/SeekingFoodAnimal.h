#pragma once
#include "Animal.h"


class SeekingFoodAnimal : public Animal 
{
public:

	SeekingFoodAnimal(sf::Vector2f pos, float speed, std::string textuerName, const int sheetRows, const int sheetCols, const int animationRow);

protected:
	virtual bool tryToEat(GameObject& food) = 0;
	GameObject* findClosestFood(const std::vector<GameObject*> foodItems);
	void moveTowardFood(const GameObject* food);
	virtual bool seekFood(const std::list<std::unique_ptr<GameObject>>& foodItems);
};