#include "shopSlot.h"



ShopSlot::ShopSlot(const int price ,std::unique_ptr<Command> command,const std::string& spriteSheetName,const int row,bool hasMax)
	:Clickable(std::move(command), spriteSheetName, row), m_spriteSheetRows(row), m_row(0), m_price(price), m_hasMax(hasMax)
{}

void ShopSlot::onClick()
{
	if (!m_isMaxBought)
	{

		m_command->execute();

		if (m_hasMax)
		{
			m_row++;
			if (m_row >= m_spriteSheetRows)
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




void ShopSlot::setMaxSprite()
{
	ResourceManager& resource = ResourceManager::getInstance();
	resource.loadSpriteSheet(MAX_SPRITE_SHEET, 1, 1);
	resource.setSpriteTextureFromSheet(m_sprite, MAX_SPRITE_SHEET, 0, 0);
}


void ShopSlot::updateSlotSpriteRow()
{
	ResourceManager& resource = ResourceManager::getInstance();
	resource.setSpriteTextureFromSheet(m_sprite, m_spriteName, 0, m_row);
}