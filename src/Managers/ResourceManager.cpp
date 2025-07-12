#include "Managers/ResourceManager.h"
#include <iostream>

bool ResourceManager::loadTexture(const std::string& filename)
{
	sf::Texture texture;
	if (texture.loadFromFile(filename))
	{
		m_textures[filename] = texture;
		return true;
	}
	else
	{
		return false;
	}
}


ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

sf::Texture* ResourceManager::getTexture(const std::string& filename)
{
	auto it = m_textures.find(filename);
	if (it != m_textures.end())
	{
		return &it->second;
	}
	else
	{
		loadTexture(filename);
		return &m_textures[filename];
	}
}


bool ResourceManager::loadSpriteSheet(const std::string& fileName, const int col, const int row, float frameWidth, float frameHeight)
{
	if (!loadTexture(fileName))
	{
		return false;
	}

	const sf::Texture* texture = getTexture(fileName);
	if (!texture)
	{
		return false;
	}

	if( col <= 0 || row <= 0 || frameWidth < 0 || frameHeight < 0)
	{
		return false;
	}

	if (frameWidth == 0 || frameHeight == 0) 
	{
		frameHeight = float(texture->getSize().y) / row;
		frameWidth = float(texture->getSize().x) / col;
	}

	m_spriteSheets[fileName] = SpriteSheetInfo
	{
		col,
		row,
		frameWidth,
		frameHeight
	};
}


void ResourceManager::setSpriteTextureFromSheet(sf::Sprite& sprite, const std::string& filename, int col, int row, int reduction)
{
	const auto texture = getTexture(filename);
	const auto it = m_spriteSheets.find(filename);

	if(!texture || it == m_spriteSheets.end())
	{
		return; // Texture or sprite sheet not found
	}

	const auto& info = it->second;

	if(col < 0 || col >= info.columns || row < 0 || row >= info.rows)
	{
		return; // Invalid column or row
	}

	sprite.setTexture(*texture);
	sprite.setTextureRect(getFrameRect(info, col, row, reduction));

}




sf::IntRect ResourceManager::getFrameRect(const SpriteSheetInfo& info, int col, int row, int reduction) const
{
	sf::IntRect startRect = sf::IntRect(col * info.frameWidth,
							row * info.frameHeight,
							info.frameWidth ,
							info.frameHeight);


	int offsetX = reduction /2;
	sf::IntRect newRect = sf::IntRect(startRect.left + offsetX,
									  startRect.top + offsetX, 
									  startRect.width - reduction,
									  startRect.height - reduction);
	return newRect;
}


sf::Font& ResourceManager::getGameFont()
{
	if(m_gameFont.getInfo().family.empty())
	{
		loadGameFont();
	}
	return m_gameFont;
}

void ResourceManager::loadGameFont()
{
	m_gameFont.loadFromFile(GAME_FONT);
}
