#pragma once
#include "State.h"
class Seed_Player :
    public State
{
private:
    void ToIdle();
public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    Seed_Player();
    virtual ~Seed_Player();
};

