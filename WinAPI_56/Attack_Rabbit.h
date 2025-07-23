#pragma once
#include "State.h"
class Attack_Rabbit :
    public State
{
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    Attack_Rabbit();
    ~Attack_Rabbit();
};

