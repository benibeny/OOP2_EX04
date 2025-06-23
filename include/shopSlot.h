#pragma once

#include "Commands/Command.h"
#include "Clickable.h"
#include <memory>


#define MAX_SPRITE_SHEET "max.jpeg"


class ShopSlot : public Clickable
{
public:
	ShopSlot(const int price ,std::unique_ptr<Command> command,const std::string& spriteSheetName, const int row);
	virtual void onClick() override;
	
	int getPrice() const { return m_price; }
	bool isMaxBought() const { return m_isMaxBought; }

private:
	void setMaxSprite();
	void updateSlotSpriteRow();

	int m_spriteSheetRows;
	int m_row;

	int m_price;

	bool m_isMaxBought = false;
};