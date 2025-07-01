#pragma once
#include "Entities/Animal.h"

class Helper : public Animal {
public:
    Helper(sf::Vector2f pos, float speed, const std::string& textureName, int sheetRows, int sheetCols, int animationRow);

    void update(float deltaTime, const std::list<std::unique_ptr<GameObject>>& objects, sf::Vector2u& windowSize) override;
    virtual void performHelperAbility(const std::list<std::unique_ptr<GameObject>>& objects) = 0;

protected:
    float m_animationTimer = 0.0f;
    int m_animationFrame = 0;
    int m_maxFrames = 0;
    std::string m_textureName;
    int m_animationRow;
};
