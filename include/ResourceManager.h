#pragma once

#include <map>
#include <sfml/Graphics.hpp>

class ResourceManager
{
public:
	bool loadTexture(const std::string& filename);


	static ResourceManager& getInstance();

	//return a pointer to the texture if it exists, otherwise load it and return a pointer to the newly loaded texture
	sf::Texture* getTexture(const std::string& filename);
	bool loadSpriteSheet(const std::string& fileName,const int col,const int row,int frameWidth = 0,int frameHeight = 0);
	void setSpriteTextureFromSheet(sf::Sprite& sprite,
							      const std::string& filename,
								  int col,int row, int reduction = 0);

private:
	ResourceManager() = default;
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;


	struct SpriteSheetInfo
	{
		int columns;
		int rows;
		int frameWidth;
		int frameHeight;
		int totalFrames;
	};

	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, SpriteSheetInfo> m_spriteSheets;

	sf::IntRect getFrameRect(const SpriteSheetInfo& info, int col, int row, int reduction) const;
	
};