#pragma once
#include "Level.h"
class Level_Tutorial :
    public Level
{
private:
    bool LockClick;
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void End() override;
public:
    Level_Tutorial();
    virtual ~Level_Tutorial();
};

