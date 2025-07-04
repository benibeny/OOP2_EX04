#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <SFML/System/Vector2.hpp>

class GameObject;

class GameObjectFactory {
public:
    using Creator = std::function<std::unique_ptr<GameObject>(const sf::Vector2f&)>;

    static void registerType(const std::string& type, Creator creator);
    static std::unique_ptr<GameObject> create(const std::string& type,
        const sf::Vector2f& pos);

    static void registerGameObjectTypes();

private:
    static std::unordered_map<std::string, Creator>& getRegistry();
};
