#pragma once
#include "Entities/HelperSeekCoin.h"
#include <SFML/Graphics.hpp>


#define HELPER_SNAIL_SPRITE "Snail.gif"
#define HELPER_SNAIL_SPEED 50.0f

class HelperSnail : public HelperSeekCoin
{
public:
	HelperSnail();
	void move(sf::Vector2u& windowSize, float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems) override;
private:

};