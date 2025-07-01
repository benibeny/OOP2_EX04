//#include "Entities/OctopusHelper.h"
//#include "Entities/Money.h"
//#include "EventManager.h"
//#include <limits>
//#include <cmath>
//
//OctopusHelper::OctopusHelper(sf::Vector2f pos)
//    : Helper(pos, 100.f, "clyde.png", 1, 10, 0)
//{
//    m_sprite.setScale(1.3f, 1.3f);
//    ResourceManager::getInstance().loadSpriteSheet("clyde.png", 10, 1);
//}
//
//void OctopusHelper::performHelperAbility(const std::list<std::unique_ptr<GameObject>>& objects) {
//    GameObject* closestMoney = nullptr;
//    float closestDist = std::numeric_limits<float>::max();
//    sf::Vector2f center = getCenter();
//
//    for (const auto& obj : objects) {
//        if (!obj || obj->isDestroyed()) continue;
//        auto* money = dynamic_cast<Money*>(obj.get());
//        if (!money) continue;
//
//        sf::Vector2f diff = money->getCenter() - center;
//        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
//
//        if (dist < closestDist) {
//            closestDist = dist;
//            closestMoney = money;
//        }
//    }
//
//    if (closestMoney) {
//        sf::Vector2f direction = closestMoney->getCenter() - center;
//        float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//        if (mag > 0.f)
//            m_velocity = (direction / mag) * m_speed;
//
//        if (closestDist < 40.f) { // Collect money if close enough
//            closestMoney->clicked(0, getPosition());
//        }
//    }
//    else {
//        moveRandomly(0.1f); // fallback
//    }
//}
