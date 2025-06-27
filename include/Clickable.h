#pragma once 

#include "UiElement.h"
#include "Commands/Command.h"
#include <memory>

#define COLOMS 2
#define SELCETED_COLOM 1
#define UNSELCETED_COLOM 0

class Clickable : public UiElement
{
public:
	Clickable(std::unique_ptr<Command> command , const std::string& spriteName, const int rows = 1 ,const int currentRow = 0);
	virtual ~Clickable() = default;

	virtual void onClick();
	void changeHoverSprite(bool isHover);


protected:
	std::unique_ptr<Command> m_command;

	int m_currentRow;

};
