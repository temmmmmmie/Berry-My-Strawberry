#pragma once
#include "State.h"
class Interact_Player :
    public State
{
private:
    void ToIdle();
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    Interact_Player();
    virtual ~Interact_Player();
};

