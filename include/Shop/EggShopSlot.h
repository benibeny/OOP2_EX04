#pragma once

#include "Shop/shopSlot.h"


class EggShopSlot : public ShopSlot
{
public:
	EggShopSlot(int currentRow,const int price, std::unique_ptr<Command> command, const std::string& spriteSheetName, const int row);

	void onClick()override;

private:
	int m_currentBoughtEggs = 0;
	constexpr static int m_maxEggs = 12;
};
