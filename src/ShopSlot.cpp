#include "shopSlot.h"



ShopSlot::ShopSlot(std::unique_ptr<Command> command,const std::string& spriteSheetName,const int row)
	:Clickable(std::move(command),spriteSheetName, row), m_spriteSheetRows(row), m_row(0)
{

}

void ShopSlot::onClick()
{
	/*if (!m_isMaxBought && m_command->execute())
	{
		m_row++;
		if (m_row >= m_spriteSheetRows)
		{
			m_isMaxBought = true;
			setMaxSprite();
		}
	}*/
}




void ShopSlot::setMaxSprite()
{
	ResourceManager& resource = ResourceManager::getInstance();
	resource.loadSpriteSheet(MAX_SPRITE_SHEET, 1, 1);
	resource.setSpriteTextureFromSheet(m_sprite, MAX_SPRITE_SHEET, 0, 0);
}