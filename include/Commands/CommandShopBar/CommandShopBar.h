#pragma once	

class CommandShopBar
{
public:
    virtual ~CommandShopBar() = default;
    virtual bool execute() = 0;
};