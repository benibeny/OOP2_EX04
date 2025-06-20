#pragma once

class CommandButton 
{
public:
    virtual ~CommandButton() = default;
    virtual void execute() = 0;
};