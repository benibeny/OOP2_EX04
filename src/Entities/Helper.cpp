
#include "Entities/Helper.h"
#include "ResourceManager.h"

Helper::Helper(sf::Vector2f pos, float speed, const std::string& textureName, int sheetRows, int sheetCols, int animationRow)
    : Animal(pos, speed, textureName, sheetRows, sheetCols, animationRow),
    m_textureName(textureName), m_animationRow(animationRow), m_maxFrames(sheetCols) {

    ResourceManager::getInstance().loadSpriteSheet(textureName, sheetCols, sheetRows);
}

void Helper::update(float deltaTime, const std::list<std::unique_ptr<GameObject>>& objects, sf::Vector2u& windowSize) 
{
    performHelperAbility(objects);

    sf::Vector2f pos = getPosition() + m_velocity * deltaTime;
    setPosition(pos);
    bounceOffWalls(windowSize);

    // simple looped animation
    m_animationTimer += deltaTime;
    if (m_animationTimer > 0.15f) {
        ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, m_textureName, m_animationFrame, m_animationRow);
        m_animationFrame = (m_animationFrame + 1) % m_maxFrames;
        m_animationTimer = 0.0f;
    }
}
