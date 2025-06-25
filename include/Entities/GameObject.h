#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <list>

#include "ResourceManager.h"
#include <iostream>

class GameObject
{
public:
	enum class Type
	{
		Food,
		GoldFish,
		Money,
		Monster,

	};


	virtual void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getCenter() const;

	bool isDestroyed() const;
	virtual void setDestroyed(bool destroyed) ;
	Type getType() const;

	virtual void clicked(int damage, sf::Vector2f mousePos) {};

	void updateAnimation(float deltaTime);
	void setPosition(const sf::Vector2f& position);
	virtual void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize) = 0;


	GameObject(Type myType, sf::Vector2f pos, const std::string& spritename,const int sheetRows,const int sheetCols,const int animationRow, int spriteReduction = 0);
	virtual ~GameObject() = default;

protected:
	Type m_type;


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