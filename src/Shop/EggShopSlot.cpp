#include "Shop/EggShopSlot.h"

EggShopSlot::EggShopSlot(int currentRow, const int price, std::unique_ptr<Command> command, const std::string& spriteSheetName, const int row)
	:ShopSlot(price, std::move(command), spriteSheetName, row, currentRow)
{

}



void EggShopSlot::onClick()
{
	if (m_currentBoughtEggs < m_maxEggs)
	{
		m_currentRow++;
		m_currentBoughtEggs++;
		if (m_currentBoughtEggs % 3 == 0)
		{
			m_currentBoughtEggs = 0;
			m_command->execute();
		}
		

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