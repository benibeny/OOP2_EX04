#include "EggShopSlot.h"

EggShopSlot::EggShopSlot(const int price, std::unique_ptr<Command> command, const std::string& spriteSheetName, const int row)
	:ShopSlot(price, std::move(command), spriteSheetName, row)
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
		}
		

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