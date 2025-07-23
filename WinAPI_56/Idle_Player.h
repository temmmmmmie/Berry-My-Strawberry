#pragma once
#include "State.h"

class Idle_Player :
    public State
{
private:


public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    Idle_Player();
    virtual ~Idle_Player();
};

