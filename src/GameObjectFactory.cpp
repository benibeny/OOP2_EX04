#include "GameObjectFactory.h"
#include "Entities/GoldFish.h"
#include "Entities/Pirana.h"
#include "Entities/NormalMonstar.h"
#include "Entities/Food.h"
#include "Entities/Money.h"


std::unordered_map<std::string, GameObjectFactory::Creator>& GameObjectFactory::getRegistry() {
    static std::unordered_map<std::string, Creator> registry;
    return registry;
}

void GameObjectFactory::registerType(const std::string& type, Creator creator) {
    getRegistry()[type] = std::move(creator);
}

std::unique_ptr<GameObject> GameObjectFactory::create(const std::string& type,
    const sf::Vector2f& pos) {
    auto it = getRegistry().find(type);
    if (it != getRegistry().end()) {
        return it->second(pos);
    }
    return nullptr;
}



void GameObjectFactory::registerGameObjectTypes() 
{
    GameObjectFactory::registerType("GoldFish", [](const sf::Vector2f& pos) {
        return std::make_unique<GoldFish>(pos);
        });
    GameObjectFactory::registerType("Pirana", [](const sf::Vector2f& pos) {
        return std::make_unique<Pirana>(pos);
        });
    GameObjectFactory::registerType("NormalMonstar", [](const sf::Vector2f& pos) {
        return std::make_unique<NormalMonstar>();
        });
    //GameObjectFactory::registerType("Helper", [](const sf::Vector2f& pos, float speed, const std::string& tex) {
    //    return std::make_unique<Helper>(pos, speed, tex, 2, 4, 0); // You can adapt args here});
    GameObjectFactory::registerType("Food", [](const sf::Vector2f& pos) {
        return std::make_unique<Food>(Food::Foodtype::Medium, pos);
        });
    // Register different money types
    GameObjectFactory::registerType("Money_Silver", [](const sf::Vector2f& pos) {
        return std::make_unique<Money>(Money::Moneytype::Silver, pos);
        });
    GameObjectFactory::registerType("Money_Gold", [](const sf::Vector2f& pos) {
        return std::make_unique<Money>(Money::Moneytype::Gold, pos);
        });
    GameObjectFactory::registerType("Money_Diamond", [](const sf::Vector2f& pos) {
        return std::make_unique<Money>(Money::Moneytype::Diamond, pos);
        });

    // Register different food types
    GameObjectFactory::registerType("Food_Worst", [](const sf::Vector2f& pos) {
        return std::make_unique<Food>(Food::Foodtype::Worst, pos);
        });
    GameObjectFactory::registerType("Food_Medium", [](const sf::Vector2f& pos) {
        return std::make_unique<Food>(Food::Foodtype::Medium, pos);
        });
    GameObjectFactory::registerType("Food_Best", [](const sf::Vector2f& pos) {
        return std::make_unique<Food>(Food::Foodtype::Best, pos);
        });

}
