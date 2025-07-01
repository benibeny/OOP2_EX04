#pragma once
#include "Entities/Helper.h"

class OctopusHelper : public Helper 
{
public:
    OctopusHelper(sf::Vector2f pos);
    void performHelperAbility(const std::list<std::unique_ptr<GameObject>>& objects) override;
};
