#pragma once
#include "State.h"
class Potion_Player :
    public State
{
private:
    void ToIdle();
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    Potion_Player();
    virtual ~Potion_Player();
};

