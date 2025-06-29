#include "Clickable.h"

Clickable::Clickable(std::unique_ptr<Command> Command, const std::string& spriteName,  const int rows, const int currentRow)
	:UiElement(spriteName, rows, COLOMS, currentRow), m_command(std::move(Command)), m_currentRow(currentRow)
{

}

void Clickable::changeHoverSprite(bool isHover)
{
	int col = UNSELCETED_COLOM;
	if (isHover)
	{
		col = SELCETED_COLOM;
	}
	ResourceManager& resource = ResourceManager::getInstance();
	resource.setSpriteTextureFromSheet(m_sprite, m_spriteName, col, m_currentRow);
}


void Clickable::onClick()
{
	m_command->execute();
}