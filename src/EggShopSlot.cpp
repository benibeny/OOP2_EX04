#include "EggShopSlot.h"

EggShopSlot::EggShopSlot(int currentRow, const int price, std::unique_ptr<Command> command, const std::string& spriteSheetName, const int row)
	:ShopSlot(price, std::move(command), spriteSheetName, row, currentRow)
{

}



void EggShopSlot::onClick()
{
	if (m_currentBoughtEggs < m_maxEggs)
	{
		m_currentBoughtEggs++;
		if (m_currentBoughtEggs % 3 == 0)
		{
			m_command->execute();
			m_price *= 2;
		}
		

		
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