#pragma once
#include "UiElement.h"
#include "Commands/CommandShopBar/CommandShopBar.h"
#include <memory>

#define COLOMS 2
#define SELCETED_COLOM 1
#define UNSELCETED_COLOM 0

#define MAX_SPRITE_SHEET "max.jpeg"


class ShopSlot : public UiElement
{
public:
	ShopSlot(std::unique_ptr<CommandShopBar> command,std::string& spriteSheetName, const int row);
	void onClick();
	void changeHoverSprite(bool isHover);
	

private:
	void setMaxSprite();

	int m_spriteSheetRows;
	int m_row;

	bool m_isMaxBought = false;

	std::unique_ptr<CommandShopBar> m_command;
};