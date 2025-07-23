#pragma once
#include "State.h"
class Die_Rabbit :
    public State
{
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

    void DestroyRabbit();
public:
    Die_Rabbit();
    ~Die_Rabbit();
};

