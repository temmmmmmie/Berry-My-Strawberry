#pragma once
#include "State.h"
class Water_Player :
    public State
{
private:
    void ToIdle();
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    Water_Player();
    virtual ~Water_Player();
};

