#include "Commands/CommandFunction.h"
#include <iostream>


void CommandFunction::execute()
{
	if (m_func)
	{
		m_func();
	}
}

CommandFunction::CommandFunction(std::function<void()> func)
    :m_func(func)
{}
