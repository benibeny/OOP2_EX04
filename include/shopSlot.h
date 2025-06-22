#pragma once

#include "Commands/Command.h"
#include "Clickable.h"
#include <memory>


#define MAX_SPRITE_SHEET "max.jpeg"


class ShopSlot : public Clickable
{
public:
	ShopSlot(std::unique_ptr<Command> command,const std::string& spriteSheetName, const int row);
	virtual void onClick() override;
	
	

private:
	void setMaxSprite();

	int m_spriteSheetRows;
	int m_row;

	bool m_isMaxBought = false;
};