#pragma once

#include "Commands/Command.h"
#include "Clickable.h"
#include <memory>


#define MAX_SPRITE_SHEET "max.jpeg"


class ShopSlot : public Clickable
{
public:
	ShopSlot(const int price ,std::unique_ptr<Command> command,const std::string& spriteSheetName, const int row, const int currRow = 0, bool hasMax = true);
	virtual ~ShopSlot() = default;

	virtual void onClick() override;
	
	int getPrice() const { return m_price; }
	bool isMaxBought() const { return m_isMaxBought; }

protected:
	void setMaxSprite();
	void updateSlotSpriteRow();

	int m_spriteSheetRows;
	

	int m_price;

	bool m_hasMax;
	bool m_isMaxBought = false;

};