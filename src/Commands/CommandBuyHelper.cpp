#include "Commands/CommandBuyHelper.h"

void CommandBuyHelper::execute()
{
	static bool seeded = false;

	if (!seeded) {
		srand(static_cast<unsigned int>(time(nullptr)));
		seeded = true;
	}

	int randomHelper = rand() % HELPER_NUMBER; // Randomly choose a helper (0, 1, or 2)
	std::unique_ptr<GameObject> helper;

	switch (randomHelper) 
	{
		case 0:
			helper = std::make_unique<HelperJellyfish>();
			break;
		case 1:
			helper = std::make_unique<HelperSnail>();//adir
			break;
		
		default:
			return; // Should never happen
	}

	EventManager::getInstance().notifyBuyAnimal(std::move(helper));
}