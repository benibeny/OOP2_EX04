#include "shopSlot.h"
#include "ShopSlot.h"


ShopSlot::ShopSlot(std::unique_ptr<CommandShopBar> command, std::string& spriteSheetName,const int row)
	:UiElement(spriteSheetName, row, COLOMS), m_spriteSheetRows(row), m_row(0), m_command(std::move(command))
{

}

void ShopSlot::onClick()
{
	if (!m_isMaxBought && m_command->execute())
	{
		m_row++;
		if (m_row >= m_spriteSheetRows)
		{
			m_isMaxBought = true;
			setMaxSprite();
		}
	}
}


void ShopSlot::changeHoverSprite(bool isHover)
{
	int col = UNSELCETED_COLOM;
	if (isHover)
	{
		col = SELCETED_COLOM;
	}
	ResourceManager& resource = ResourceManager::getInstance();
	resource.setSpriteTextureFromSheet(m_sprite, m_spriteName, col, m_row);
}

void ShopSlot::setMaxSprite()
{
	ResourceManager& resource = ResourceManager::getInstance();
	resource.loadSpriteSheet(MAX_SPRITE_SHEET, 1, 1);
	resource.setSpriteTextureFromSheet(m_sprite, MAX_SPRITE_SHEET, 0, 0);
}