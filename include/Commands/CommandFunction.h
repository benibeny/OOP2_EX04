#pragma once

#include "Command.h"
#include <functional>

class CommandFunction: public Command
{
public:
	CommandFunction(std::function<void()> func);

	void execute() override;

private:
	std::function<void()> m_func;
};