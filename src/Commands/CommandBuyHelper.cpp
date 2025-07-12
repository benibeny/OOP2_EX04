#include "Commands/CommandBuyHelper.h"
#include "GameObjectFactory.h" 

void CommandBuyHelper::execute()
{
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    int randomHelper = rand() % HELPER_NUMBER;
    std::string helperType;

    switch (randomHelper)
    {
    case 0:
        helperType = "Helper_Jellyfish";
        break;
    case 1:
        helperType = "Helper_Snail";
        break;
    default:
        return;
    }

    auto helper = GameObjectFactory::getInstance().create(helperType, { 0.f, 0.f });
    if (helper)
    {
        EventManager::getInstance().notifyBuyAnimal(std::move(helper));
    }
}
