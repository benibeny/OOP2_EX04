#include "Entities/SeekingFoodAnimal.h"

SeekingFoodAnimal::SeekingFoodAnimal(sf::Vector2f pos, float speed, std::string textuerName, const int sheetRows, const int sheetCols, const int animationRow)
	: Animal(pos, speed ,textuerName, sheetRows, sheetCols, animationRow)
{}



bool SeekingFoodAnimal::seekFood(const std::list<std::unique_ptr<GameObject>>& foodItems)
{
    bool foundFood = false;
    //pointer to pointer to avoid copying the vector
    std::vector<GameObject*> filteredFood;

    for (const auto& foodItem : foodItems)
    {
        if (foodItem && !foodItem->isDestroyed() && tryToEat(*foodItem)) 
        {
            filteredFood.push_back(foodItem.get());
        }
    }

    if (!filteredFood.empty()) 
    {
        const GameObject* foundClosestFood = findClosestFood(filteredFood);

        moveTowardFood(foundClosestFood);
        foundFood = true;
    }
    
    return foundFood;
}


GameObject* SeekingFoodAnimal::findClosestFood(const std::vector<GameObject*> foodItems)
{
	if (foodItems.empty())
	{
		return nullptr;
	}

	GameObject* closestFood = nullptr;
	float closestDistance = std::numeric_limits<float>::max();
	sf::Vector2f fishCenter = getCenter();	
	
	for(GameObject* foodItem : foodItems)
	{
		if (foodItem) 	
		{
			sf::Vector2f foodCenter = foodItem->getCenter();
			sf::Vector2f diffrence = foodCenter - fishCenter;

			float distance = std::sqrt(diffrence.x * diffrence.x + diffrence.y * diffrence.y);

			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestFood = foodItem;
			}
		}
	}
	return closestFood;	

}


void SeekingFoodAnimal::moveTowardFood(const GameObject* food)
{
	sf::Vector2f fishCenter = getCenter();
	sf::Vector2f foodCenter = food->getCenter();
	sf::Vector2f direction = foodCenter - fishCenter;

	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude > 0)
	{
		direction /= magnitude;
		m_velocity = direction * m_speed;
	}
}