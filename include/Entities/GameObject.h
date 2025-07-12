#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <list>

#include "Managers/ResourceManager.h"
#include <iostream>

class GoldFish;
class Pirana;
class NormalMonstar;
class Money;
class Food;
class Fish;
class HelperSeekCoin;


class GameObject
{
public:
	virtual void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getCenter() const;

	bool isDestroyed() const;
	virtual void setDestroyed(bool destroyed);
	virtual void clicked(int damage, sf::Vector2f mousePos) {};
	
	
	virtual void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize) = 0;


	GameObject(sf::Vector2f pos, const std::string& spritename,const int sheetRows,const int sheetCols,const int animationRow, int spriteReduction = 0);
	virtual ~GameObject() = default;

	//double dispatch - defult all false.
	virtual bool canBeEatenBy(const Fish& fish) const;
	virtual bool canBeEatenBy(const GoldFish& goldFish);
	virtual bool canBeEatenBy(const Pirana& pirana);
	virtual bool canBeEatenBy(const NormalMonstar& monster);
	virtual bool canBeEatenBy(const Money& money);
	virtual bool canBeEatenBy(const Food& food);
	virtual bool canBeEatenBy(const HelperSeekCoin& food);


	
protected:
	virtual void updateAnimation(float deltaTime);



	bool m_isSpriteLoaded;

	sf::Sprite m_sprite;
	std::string m_spriteName;

	bool m_shouldDestroy;
	int m_sheetCols;
	int m_sheetRowIndex;
	float m_animationTimer;
	int m_animationFrame;


	int m_spriteReduction; // Reduction in size for the sprite
};