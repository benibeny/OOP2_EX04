#include "shopSlot.h"



ShopSlot::ShopSlot(const int price ,std::unique_ptr<Command> command,const std::string& spriteSheetName,const int row,const int currRow, bool hasMax)
	:Clickable(std::move(command), spriteSheetName, row, currRow), m_spriteSheetRows(row), m_price(price), m_hasMax(hasMax)
{}

void ShopSlot::onClick()
{
	if (!m_isMaxBought)
	{

		m_command->execute();

		if (m_hasMax)
		{
			m_currentRow++;
			if (m_currentRow >= m_spriteSheetRows)
			{
				m_isMaxBought = true;
				setMaxSprite();
			}
			else
			{
				updateSlotSpriteRow();
			}
		}
	}
}


void ShopSlot::reset(int currRow)
{
	m_currentRow = currRow;
	m_isMaxBought = false;
	updateSlotSpriteRow();
}


void ShopSlot::setMaxSprite()
{
	ResourceManager& resource = ResourceManager::getInstance();
	resource.loadSpriteSheet(MAX_SPRITE_SHEET, 1, 1);
	resource.setSpriteTextureFromSheet(m_sprite, MAX_SPRITE_SHEET, 0, 0);
}


void ShopSlot::updateSlotSpriteRow()
{
	ResourceManager& resource = ResourceManager::getInstance();
	resource.setSpriteTextureFromSheet(m_sprite, m_spriteName, 0, m_currentRow);
}


bool ShopSlot::isMouseOver(const sf::Vector2f& mousePosition) const
{
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	bounds.left += bounds.width * 0.1f;
	bounds.top += bounds.height * 0.1f;
	bounds.width *= 0.8f;
	bounds.height *= 0.8f;

	return bounds.contains(mousePosition);
}