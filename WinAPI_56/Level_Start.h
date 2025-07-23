#pragma once
#include "Level.h"
class Level_Start :
    public Level
{
private:
    bool LockClick;
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void End() override;

public:
    Level_Start();
    virtual ~Level_Start();
};

