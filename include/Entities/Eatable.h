#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Eatable
{
public:
	enum class Type
	{
		Food,
		GoldFish,
		Money,

	};


	virtual void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getCenter() const;

	bool isEaten() const;
	void setEaten(bool eaten) ;
	Type getType() const;

	void updateAnimation(float deltaTime);
	void setPosition(const sf::Vector2f& position);
	virtual void update(float deltaTime, const std::vector <std::unique_ptr<Eatable>>& foodItems, sf::Vector2u& windowSize) = 0;


	Eatable(Type myType, sf::Vector2f pos, const std::string& spritename,const int sheetRows,const int sheetCols,const int animationRow, int spriteReduction = 0);
	virtual ~Eatable() = default;

protected:
	Type m_type;


	bool m_isSpriteLoaded;

	sf::Sprite m_sprite;
	std::string m_spriteName;

	bool m_isEaten;
	int m_sheetCols;
	int m_sheetRowIndex;
	float m_animationTimer;
	int m_animationFrame;


	int m_spriteReduction; // Reduction in size for the sprite

	
	

};