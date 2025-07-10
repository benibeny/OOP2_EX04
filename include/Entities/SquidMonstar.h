#pragma once

#include "NormalMonstar.h"
#include "EventManager.h"


#define NORMALMONSTAR_SPEED 150.0f
#define NORMALMONSTAR_SPRITE "squid.png"
#define MAX_COLOR_CHANGE_TIME 5.0f

class SquidMonstar : public NormalMonstar
{
public:
	SquidMonstar();

	void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)override;
	void clicked(int damage, sf::Vector2f mousePos)override;

private:

	bool m_isBlue = false;
	float m_colorChangeTimer = 0.0f;
	float m_nextColorChangeThreshold = 0.0f;

};